#ifndef LINEAR_PROCESSOR_HPP
#define LINEAR_PROCESSOR_HPP

#include "block.hpp"
#include "amino_group.hpp"

#include <list>
#include <string>
#include <vector>
#include <utility>

namespace mabr {

using namespace std;

typedef list<block> block_list;


class linear_processor {
public:
    explicit linear_processor(float R = 3.0f);

    block_list run(const block & root) const;

private:
    typedef pair<const amino_group*, mask> group_mask;
    typedef vector<amino_group>::const_iterator group_iterator;
    typedef list<group_mask> group_list;

    struct opened_block {
        size_t  start;
        mask    fence;
        string  consensus;

        inline opened_block(const size_t start_, const mask &fence_, const string &consensus_)
            : start(start_), fence(fence_), consensus(consensus_) {}
    };
    typedef list<opened_block> oblock_list;
    typedef oblock_list::iterator obl_it;

    void process_column(const size_t index,
                        const string & column,
                        oblock_list & blocks,
                        block_list & result_blocks,
                        const block & parent_block
                        ) const;

    void process_column_for_block(const size_t index,
                                  const string & column,
                                  const opened_block & cblock,
                                  oblock_list & blocks,
                                  block_list & result_blocks,
                                  const block & parent_block
                                  ) const;

    void open_new_block(const size_t start,
                        const mask & fence,
                        const string & consensus,
                        oblock_list & blocks) const;



    group_list find_all_groups(const string & column) const;
    group_mask find_most_significant_group(const string & column) const;

    vector<amino_group> amino_groups_;
};

}

#endif // LINEAR_PROCESSOR_HPP
