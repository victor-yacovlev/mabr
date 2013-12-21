#include "blocktree.hpp"

#include <cassert>

namespace mabr {

blocktree::blocktree(const block &src)
    : d(src)
{}

blocktree::~blocktree()
{
    typedef list<blocktree*>::iterator node_it;
    for (node_it it=children.begin(); it!=children.end(); ++it) {
        blocktree * ch = *it;
        if (ch) delete ch;
        *it = 0;
    }
    children.clear();
}

void blocktree::add(const block &data)
{
    blocktree * child = new blocktree(data);
    children.push_back(child);
}

void blocktree::add_all(const list<block> &data)
{
    typedef list<block>::const_iterator block_it;
    for (block_it it=data.begin(); it!=data.end(); ++it) {
        const block & element = *it;
        add(element);
    }
}

bool blocktree::valid() const
{
#if defined(NDEBUG) || defined(NO_DEBUG) || defined(_NDEBUG) || defined(_NO_DEBUG)
    return true;
#else
    if (!d.valid()) return false;
    typedef list<blocktree*>::const_iterator node_it;
    for (node_it it=children.begin();
         it!=children.end();
         ++it)
    {
        blocktree* child = *it;
        if (!child->valid())
            return false;
    }
    return true;
#endif
}

void blocktree::print_xml(ostream &stream) const
{
    if (!d.valid() && children.empty()) return;

    typedef list<blocktree*>::const_iterator node_it;

    if (children.size() > 1) {
        stream << "<group>" << endl;
        for (node_it it=children.begin(); it!=children.end(); ++it) {
            blocktree * node = *it;
            node->print_xml(stream);
        }
        stream << "</group>" << endl;
    }
    else if (children.size() == 1) {
        blocktree * elem = children.front();
        elem->print_xml(stream);
    }
    else {
        d.print_xml(stream);
    }
}

blocktree::direction blocktree::get_first_level_blocks_direction() const
{
    direction result = Unimportant;
    if (children.size() > 1) {
        const block & first = children.front()->d;
        const block & last = children.back()->d;
        if (first.xs == last.xs && first.xe == last.xe) {
            // the same X-coordinates
            result = Vertical;
        }
        else {
            result = Horizontal;
        }
    }
    return result;
}

}
