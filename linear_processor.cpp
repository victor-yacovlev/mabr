#include "linear_processor.hpp"

namespace mabr {

linear_processor::linear_processor(float R)
    : amino_groups_(amino_group_factory::create(R))
{

}

block_list linear_processor::run(const block & root) const
{    
    oblock_list blocks;
    block_list result;
    for (size_t k=0u; k<root.width(); k++) {
        const string column = root.get_column(k);
        process_column(k, column, blocks, result, root);
    }
    return list<block>();
}

void linear_processor::process_column(
        const size_t index,
        const string &column,
        oblock_list &blocks,
        block_list & result_blocks,
        const block & parent_block
        ) const
{
    if (blocks.empty()) {
        group_mask gr = find_most_significant_group(column);
        if (gr.first && gr.second) {
            // if not empty mask
            open_new_block(index, gr.second, column, blocks);
        }
    }
    else {
        for (obl_it it = blocks.begin(); it!=blocks.end(); ++it) {
            process_column_for_block(index, column, *it, blocks, result_blocks, parent_block);
        }
    }
}

void linear_processor::process_column_for_block(
        const size_t index,
        const string &column,
        const opened_block &cblock,
        oblock_list &blocks,
        block_list &result_blocks,
        const block &parent_block
        ) const
{
    group_mask gr = find_most_significant_group(column);
    const mask & z = cblock.fence;
    const mask & v = gr.second;
    const mask p = v & z;
    if (p != z) {

    }
}


void linear_processor::open_new_block(
        const size_t start,
        const mask &fence,
        const string &consensus,
        oblock_list &blocks
        ) const
{
    opened_block block(start, fence, consensus);
    blocks.push_back(block);
}

linear_processor::group_list linear_processor::find_all_groups(const string &column) const
{
    group_list result;
    for (group_iterator it=amino_groups_.begin(); it!=amino_groups_.end(); ++it) {
        const amino_group & group = *it;
        mask m = group.meaningful_for(column);
        if (m) {
            const amino_group *ptr = &group;
            result.push_back(make_pair(ptr, m));
        }
    }
    return result;
}

linear_processor::group_mask linear_processor::find_most_significant_group(const string &column) const
{
    const group_list all = find_all_groups(column);
    if (all.empty()) {
        const amino_group* null_pointer = 0;
        return make_pair(null_pointer, mask(column.length()));
    }
    group_list::const_iterator most;
    unsigned most_value = 0u;
    for (group_list::const_iterator it=all.begin(); it!=all.end(); ++it) {
        const group_mask & gl = *it;
        const mask & m = gl.second;
        const unsigned sz = m.sum();
        if (0u == most_value || sz > most_value) {
            most = it;
            most_value = sz;
        }
    }
    group_mask result = *most;
    return result;
}


}
