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

void blocktree::print_html(ostream &stream) const
{
    if (!d.valid() && children.empty()) return;

    typedef list<blocktree*>::const_iterator node_it;

    if (children.size() > 1) {
        stream << "<div class='tree_node'>";
        const string clazz =
                get_first_level_blocks_direction() == Horizontal
                ? string("tree_node_row")
                : string("tree_node_column");
        stream << "<div class='" << clazz << "'>";
        for (node_it it=children.begin(); it!=children.end(); ++it) {
            stream << "<div class='tree_element'>";
            blocktree * elem = *it;
            elem->print_html(stream);
            stream << "</div>";
        }
        stream << "</div>";
        stream << "</div>";
    }
    else if (children.size() == 1) {
        blocktree * elem = children.front();
        elem->print_html(stream);
    }
    else {
        d.print_html(stream);
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
            // assumes the same Y-coordinates
            assert(first.ys == last.ys);
            assert(first.ye == last.ye);
            result = Horizontal;
        }
    }
    return result;
}

}
