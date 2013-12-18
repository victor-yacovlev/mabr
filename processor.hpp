#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "region.hpp"
#include "alignment.hpp"
#include "matrix.hpp"
#include "block.hpp"
#include "basic_tree.hpp"

#include <deque>

namespace mabr {

using namespace std;

typedef basic_tree<block> blocktree;

class processor {
public:

    explicit processor(const matrix & mx,
                       const float thereshold_column,
                       const float thereshold_row);

    blocktree * run(const alignment & al);

private:

    enum criterion { GoodScore, LowScore, Gap };

    void split_into_vertical_blocks(blocktree * root);

    float average_pairwise_score(const string & str) const;
    float column_score(const string & str) const;
    criterion vertical_bound_criterion(const string & column) const;

    bool check_for_good_rows(block & bl);

    matrix matrix_;
    float thereshold_column_;
    float thereshold_row_;
};

}

#endif // PROCESSOR_HPP
