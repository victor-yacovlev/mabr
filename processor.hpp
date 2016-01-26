#pragma once
#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "alignment.hpp"
#include "matrix.hpp"
#include "block.hpp"
#include "blocktree.hpp"

#include <list>

namespace mabr {

class processor {
public:

    explicit processor(const matrix & mx,
                       const float thereshold_column,
                       const float thereshold_row,
                       const size_t thereshold_width,
                       const size_t thereshold_height,
                       const size_t thereshold_square
                       );

    blocktree * run(const alignment * al);

private:

    using node_iterator = std::list<blocktree*>::iterator;
    using block_list = std::list<block>;
    
    void run_stage(blocktree * root) const;

    void process_block(blocktree * root_node) const;
    void process_minus_type_1_block(blocktree * root_node) const;
    void process_minus_type_2_block(blocktree * root_node) const;


    block_list split_into_plus_and_minus_type_1_blocks(const block & bl) const;

    block_list split_into_vertical_blocks(const block & root) const;
    block_list split_into_horizontal_blocks(const block & root) const;

    float average_pairwise_score(const std::string & str) const;
    float column_score(const std::string & str) const;
    float column_score_linear_time(const std::string & str) const;
    float column_score_quadratic_time(const std::string & str) const;
    float relative_row_score(const block & bl, size_t index) const;

    bool check_for_good_rows(block & bl) const;

    bool should_split_into_vertical(const blocktree * node) const;
    bool should_split_into_horizontal(const blocktree * node) const;
    bool blocktree_done(const blocktree * node) const;
    bool block_done(const block & bl) const;
    bool accept_plus_block(const block & bl) const;
    bool accept_minus_block(const block & bl) const;

    matrix matrix_;
    float thereshold_column_;
    float thereshold_row_;

    size_t thereshold_width_;
    size_t thereshold_height_;
    size_t thereshold_square_;
};

}

#endif // PROCESSOR_HPP
