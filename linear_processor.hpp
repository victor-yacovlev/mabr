#pragma once
#ifndef LINEAR_PROCESSOR_HPP
#define LINEAR_PROCESSOR_HPP

#include "block.hpp"
#include "amino_group.hpp"

#include <list>
#include <string>
#include <utility>
#include <vector>

namespace mabr {

using block_list = std::list<block>;

class linear_processor {
public:
    explicit linear_processor(float R = 3.0f);

    block_list run(const block & root) const;

private:
    using group_mask = std::pair<const amino_group*, mask>;
    using group_iterator = std::vector<amino_group>::const_iterator;
    using group_list = std::list<group_mask>;

    struct opened_block {
        size_t  start;
        mask    fence;
        std::string  consensus;

        inline opened_block(const size_t start_, const mask &fence_, const std::string &consensus_)
            : start(start_), fence(fence_), consensus(consensus_) {}
    };

    using oblock_list = std::list<opened_block>;
    using obl_it = oblock_list::iterator;

    void process_column(const size_t index,
                        const std::string & column,
                        oblock_list & blocks,
                        block_list & result_blocks,
                        const block & parent_block
                        ) const;

    void process_column_for_block(const size_t index,
                                  const std::string & column,
                                  const opened_block & cblock,
                                  oblock_list & blocks,
                                  block_list & result_blocks,
                                  const block & parent_block
                                  ) const;

    void open_new_block(const size_t start,
                        const mask & fence,
                        const std::string & consensus,
                        oblock_list & blocks) const;



    group_list find_all_groups(const std::string & column) const;
    group_mask find_most_significant_group(const std::string & column) const;

    std::vector<amino_group> _amino_groups;
};

}

#endif // LINEAR_PROCESSOR_HPP
