#ifndef BLOCKTREE_HPP
#define BLOCKTREE_HPP

#include "block.hpp"

#include <list>
#include <ostream>

namespace mabr {

using namespace std;

class blocktree
{
public /*types*/:
    enum direction { Unimportant, Horizontal, Vertical };

public /*fields*/:
    block d;
    list<blocktree*> children;

public /*constructors*/:
    explicit blocktree(const block & src);

public /*destructor*/:
    ~blocktree();

public /*methods*/:
    void add(const block & data);
    void add_all(const list<block> & data);
    bool valid() const; // For debug puproses only

    void print_html(ostream &stream) const;
    direction get_first_level_blocks_direction() const;

};

}

#endif // BLOCKTREE_HPP
