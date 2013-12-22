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

typedef list<block> blocklist;


class linear_processor {
public:
    explicit linear_processor(float R = 3.0f);

    list<block> run(const block & root) const;

private:
    typedef vector<amino_group>::const_iterator group_iterator;
    typedef pair<amino_group, mask> group_mask;
    typedef list<group_mask> critical_set;
    typedef critical_set::const_iterator critical_set_iterator;
    typedef pair<block, mask> fence;
    typedef list<fence> fences_list;
    typedef fences_list::iterator fences_iterator;

    critical_set make_critical_set(const string & column) const;

    vector<amino_group> amino_groups_;
};

}

#endif // LINEAR_PROCESSOR_HPP
