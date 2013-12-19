#include "processor.hpp"

#include <cassert>
#include <stdlib.h>
#include <deque>

namespace mabr {


static const string Alphabet(" ARNDCQEGHILKMFPSTWYVBZX");

processor::processor(const matrix &mx,
                     const float thereshold_column,
                     const float thereshold_row,
                     const size_t thereshold_width,
                     const size_t thereshold_height,
                     const size_t thereshold_square
                     )
    : matrix_(mx)
    , thereshold_column_(thereshold_column)
    , thereshold_row_(thereshold_row)
    , thereshold_width_(thereshold_width)
    , thereshold_height_(thereshold_height)
    , thereshold_square_(thereshold_square)
{

}

blocktree * processor::run(const alignment * al)
{    
    block root_block(al);
    blocktree * root = new blocktree(root_block);
    run_stage(root);
    return root;
}

void processor::run_stage(blocktree* root) const
{            
    assert(root->valid());

    typedef list<blocktree*>::iterator node_it;
    typedef list<block>::iterator block_it;

    block & root_block = root->d;
    list<block> vertical_blocks = split_into_vertical_blocks(root_block);
    assert(! vertical_blocks.empty());

    list<blocktree*> nodes_to_split_into_horizontal;
    list<blocktree*> nodes_to_process_recursively;

    if (vertical_blocks.size() > 1) {
        root->add_all(vertical_blocks);
        for (node_it it = root->children.begin();
             it != root->children.end();
             ++it)
        {
            blocktree * node = *it;
            assert(node->valid());
            if (!stop_split_into_horizontal(node)) {
                nodes_to_split_into_horizontal.push_back(node);
            }
        }
    }
    else {
        root->d = vertical_blocks.front();
        assert(root->valid());
        if (!stop_split_into_horizontal(root)) {
            nodes_to_split_into_horizontal.push_back(root);
        }
    }

    for (node_it it = nodes_to_split_into_horizontal.begin();
         it != nodes_to_split_into_horizontal.end();
         ++it)
    {
        blocktree* node_to_horizontal_split = *it;
        block & block_to_horizontal_split = node_to_horizontal_split->d;
        list<block> horizontal_blocks =
                split_into_horizontal_blocks(block_to_horizontal_split);
        assert(! horizontal_blocks.empty());
        if (horizontal_blocks.size() > 1) {
            node_to_horizontal_split->add_all(horizontal_blocks);
            for (node_it chk=node_to_horizontal_split->children.begin();
                 chk!=node_to_horizontal_split->children.end();
                 ++chk)
            {
                blocktree * node_candidate = *it;
                assert(node_candidate->valid());
                if (!stop_split_into_vertical(node_candidate)) {
                    nodes_to_process_recursively.push_back(node_candidate);
                }
            }
        }
        else {
            node_to_horizontal_split->d = horizontal_blocks.front();
            assert(node_to_horizontal_split->valid());
            if (!stop_split_into_vertical(node_to_horizontal_split)) {
                nodes_to_process_recursively.push_back(node_to_horizontal_split);
            }
        }
    }

    for (node_it it = nodes_to_process_recursively.begin();
         it!=nodes_to_process_recursively.end();
         ++it)
    {
        blocktree * node = *it;
        assert(node->valid());
        run_stage(node);
    }

}

bool processor::blocktree_done(const blocktree *node) const
{
    return block_done(node->d);
}

bool processor::stop_split_into_vertical(const blocktree *node) const
{
    return node->d.width() < 2 || blocktree_done(node);
}

bool processor::stop_split_into_horizontal(const blocktree *node) const
{
    return node->d.height() < 2 || blocktree_done(node);
}

bool processor::block_done(const block &bl) const
{
    bool min_size_reached = bl.width() < 2 && bl.height() < 2;
    bool type_reached = false;
    if (bl.tp == block::Plus)
        type_reached = accept_plus_block(bl);
    else if (bl.tp == block::Minus)
        type_reached = accept_minus_block(bl);
    return min_size_reached || type_reached;
}

bool processor::accept_plus_block(const block &) const
{
    return true;
}

bool processor::accept_minus_block(const block &bl) const
{
    bool width_reached = bl.width() <= thereshold_width_;
    bool height_reached = bl.height() <= thereshold_height_;
    size_t square = bl.width() * bl.height();
    bool square_reached = square <= thereshold_square_;
    return width_reached || height_reached || square_reached;
}

list<block> processor::split_into_vertical_blocks(const block & root) const
{
    list<block> result;

    if (root.width() < 2) {
        result.push_back(root);
        return result;
    }
    
    bool current_score_is_good;
    bool last_score_is_good;

    deque<size_t> starts;
    deque<bool> possible_pluses;

    for (size_t i = 0u; i<root.width(); i++) {
        const string column_data = root.get_column(i);
        current_score_is_good =
                column_score(column_data) > thereshold_column_;
        bool border =
                0u==i ||
                i > 0u && current_score_is_good != last_score_is_good;

        if (border) {
            starts.push_back(i);
            possible_pluses.push_back(current_score_is_good);
        }
        last_score_is_good = current_score_is_good;
    }

    for (size_t i=0u; i<starts.size(); i++) {
        const size_t start = starts[i];
        const size_t end = i<starts.size()-1
                ? starts[i+1] : root.width();
        current_score_is_good = possible_pluses[i];
        block bl(root, start, end);
        if (bl.valid()) {
            // calculate block type
            bool has_low_score_column = ! current_score_is_good;
            bool has_low_score_row = ! check_for_good_rows(bl);
            block::type bt = block::Plus;
            if (has_low_score_column && has_low_score_row)
                bt = block::Minus;
            else if (has_low_score_row)
                bt = block::PlusType1;
            else if (has_low_score_column)
                bt = block::PlusType2;

            bl.tp = bt;

            // push block to result
            result.push_back(bl);
        }
    }
    return result;
}

list<block> processor::split_into_horizontal_blocks(const block& root) const
{
    list<block> result;
    result.push_back(root); // TODO implement me
    return result;
}

float processor::relative_row_score(const block &bl, size_t index) const
{
    float score_sum = 0.0f;
    for (size_t x=0u; x<bl.width(); x++) {
        for (size_t i=0u; i<bl.height(); i++) {
            if (i != index) {
                const char a = bl.get(index, x);
                const char b = bl.get(i, x);
                float score = matrix_.value(a, b);
                score_sum += score;
            }
        }
    }
    unsigned scale = bl.width() * (bl.height() - 1);
    float average = score_sum / scale;
    return average;
}

bool processor::check_for_good_rows(block &bl) const
{
    bool result = true;
    for (size_t y=0u; y<bl.height(); y++) {
        float score = relative_row_score(bl, y);
        bool good_row = score > thereshold_row_;
        bl.good_rows[y] = good_row;
        result = result && good_row;
    }
    return result;
}


float processor::average_pairwise_score(const string &str) const
{
    size_t count = 0u;
    float summ = 0.0f;
    for (size_t i=0; i<str.length(); i++) {
        for (size_t j=0; j<str.length(); j++) {
            if (i!=j) {
                count += 1;
                const char a = str[i];
                const char b = str[j];
                float current = matrix_.value(a, b);
                summ += current;
            }
        }
    }
    float result = summ / count;
    return result;
}

float processor::column_score_quadratic_time(const string& str) const
{
    return column_score_linear_time(str); // TODO implement me
}

float processor::column_score(const string& str) const
{
    // There are two ways of calculate
    if (str.length() >= 20) {
        // complexity: O(20**2) + O(n)
        return column_score_linear_time(str);
    }
    else {
        // complexity: O(n**2)
        return column_score_quadratic_time(str);
    }
}


float processor::column_score_linear_time(const string & str) const
{
    vector<size_t> N(Alphabet.length()+1, 0u);
    for (size_t i=0u; i<str.length(); i++) {
        char symb = str[i];
        if ('.' == symb || '-' == symb)
            symb = ' ';
        size_t index = Alphabet.find(symb);
        assert(index != string::npos);
        N[index] += 1u;
    }
    float nonEqualSum = 0.0f;
    float equalSum = 0.0f;

    // TODO optimize me!
    for (size_t i=0u; i<Alphabet.length(); i++) {
        for (size_t j=i+1; j<Alphabet.length(); j++) {
            if (N[i] * N[j] > 0) {
                const char a = Alphabet[i];
                const char b = Alphabet[j];
                float score = matrix_.value(a, b);
                nonEqualSum += N[i] * N[j] * score;
            }
        }
    }

    for (size_t i=1u; i<Alphabet.length(); i++) {
        if (N[i] > 1) {
            const char a = Alphabet[i];
            const float score = matrix_.value(a, a);
            equalSum += (N[i] * (N[i] - 1)) / 2 * score;
        }
    }

    const float result = nonEqualSum + equalSum;
    const unsigned scale = ( str.length() * (str.length() - 1) ) / 2;
    const float normalized_result = result / scale;
    return normalized_result;
}





}
