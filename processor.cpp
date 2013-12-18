#include "processor.hpp"

#include <ctype.h>
#include <cassert>

namespace mabr {

static const string Alphabet(" ARNDCQEGHILKMFPSTWYVBZX");
static const float Space_vs_Other = -4.0f;

processor::processor(const matrix &mx,
                     const float thereshold_column,
                     const float thereshold_row)
    : matrix_(mx)
    , thereshold_column_(thereshold_column)
    , thereshold_row_(thereshold_row)
{

}

blocktree * processor::run(const alignment & al)
{    
    block root_block(al);
    blocktree * root = new blocktree(root_block);
    split_into_vertical_blocks(root);
    return root;
}

void processor::split_into_vertical_blocks(blocktree * root)
{

    criterion current_column_criterion;
    criterion last_block_criterion;

    deque<size_t> starts;
    deque<criterion> possible_pluses;

    for (size_t i = 0u; i<root->d.width(); i++) {
        const string column_data = root->d.get_column(i);
        current_column_criterion = vertical_bound_criterion(column_data);
        bool border =
                0u==i ||
                i > 0u && current_column_criterion != last_block_criterion;

        if (border) {
            starts.push_back(i);
            possible_pluses.push_back(current_column_criterion);
        }
        last_block_criterion = current_column_criterion;
    }

    for (size_t i=0u; i<starts.size(); i++) {
        const size_t start = starts[i];
        const size_t end = i<starts.size()-1
                ? starts[i+1] : root->d.width();
        current_column_criterion = possible_pluses[i];
        block bl(root->d, start, end);
        if (bl.valid()) {
            // calculate block type
            bool has_low_score_column = GoodScore != current_column_criterion;
            bool has_low_score_row =
                    Gap == current_column_criterion ||
                    ! check_for_good_rows(bl);
            block::type bt = block::Plus;
            if (has_low_score_column && has_low_score_row)
                bt = block::Minus;
            else if (has_low_score_row)
                bt = block::PlusType1;
            else if (has_low_score_column)
                bt = block::PlusType2;

            if (Gap == current_column_criterion)
                bt = block::Minus;

            bl.set_type(bt);

            // push block to result
            root->add(bl);
        }
    }
}

bool processor::check_for_good_rows(block &bl)
{
    bool result = true;
    for (size_t y=0u; y<bl.height(); y++) {
        float score_sum = 0.0f;
        for (size_t x=0u; x<bl.width(); x++) {
            for (size_t i=0u; i<bl.height(); i++) {
                const char a = bl.get(y, x);
                if (i != y) {
                    const char b = bl.get(i, x);
                    float score = matrix_.value(a, b);
                    score_sum += score;
                }
            }
        }
        float average = score_sum / (bl.height() - 1);
        bool good_row = average > thereshold_row_;
        bl.set_good_row(y, good_row);
        result = result && good_row;
    }
    return result;
}

processor::criterion processor::vertical_bound_criterion(const string & column) const
{
    bool has_blank = false;
    for (size_t i=0; i<column.length(); i++) {
        const char ch = column[i];
        if (ch=='-' || ch=='.' || ch==' ') {
            has_blank = true;
            break;
        }
    }

    if (has_blank) {
        return Gap;
    }

    float score = column_score(column);
    return score <= thereshold_column_ ? LowScore : GoodScore;
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
                float current = 0.0f;
                if (a=='-' || b=='-' || a=='.' || b=='.' || a==' ' || b==' ') {
                    current = Space_vs_Other;
                }
                else {
                    current = matrix_.value(a, b);
                }
                summ += current;
            }
        }
    }
    float result = summ / count;
    return result;
}

float processor::column_score(const string & str) const
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
            float score = 0.0f;
            if ( 0u == i ) {
                score = Space_vs_Other;
            }
            else {
                const char a = Alphabet[i];
                const char b = Alphabet[j];
                score = matrix_.value(a, b);
            }
            nonEqualSum += N[i] * N[j] * score;
        }
    }

    for (size_t i=1u; i<Alphabet.length(); i++) {
        const char a = Alphabet[i];
        const float score = matrix_.value(a, a);
        equalSum += (N[i] * (N[i]-1) / 2) * score;
    }

    const float result = nonEqualSum + equalSum;

    return result;
}





}
