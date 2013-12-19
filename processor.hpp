#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "alignment.hpp"
#include "matrix.hpp"
#include "block.hpp"
#include "blocktree.hpp"

#include <list>

namespace mabr {

using namespace std;

class processor {
public:

    explicit processor(const matrix & mx,
                       const float thereshold_column,
                       const float thereshold_row);

    blocktree * run(const alignment * al);

private:
    
    void run_stage(blocktree * root) const;

    list<block> split_into_vertical_blocks(const block & root) const;
    list<block> split_into_horizontal_blocks(const block & root) const;

    float average_pairwise_score(const string & str) const;
    float column_score(const string & str) const;
    float column_score_linear_time(const string & str) const;
    float column_score_quadratic_time(const string & str) const;

    bool check_for_good_rows(block & bl) const;

    matrix matrix_;
    float thereshold_column_;
    float thereshold_row_;
};

}

#endif // PROCESSOR_HPP
