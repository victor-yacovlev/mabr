#include "linear_processor.hpp"

namespace mabr {

linear_processor::linear_processor(float R)
    : amino_groups_(amino_group_factory::create(R))
{

}

list<block> linear_processor::run(const block & root) const
{
    fences_list fence_candidates;

    list<block> result;
    for (size_t index = 0u; index < root.width(); index++) {
        const string column = root.get_column(index);
        const critical_set cset = make_critical_set(column);

    }
    return result;
}

linear_processor::critical_set linear_processor::make_critical_set(const string &column) const
{
    critical_set result;
    for (group_iterator it=amino_groups_.begin(); it!=amino_groups_.end(); ++it) {
        const amino_group & group = *it;
        mask m = group.meaningful_for(column);
        if (m) {
            result.push_back(make_pair(group, m));
        }
    }
    return result;
}


}
