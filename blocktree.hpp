#pragma once
#ifndef BLOCKTREE_HPP
#define BLOCKTREE_HPP

#include "block.hpp"

#include <list>
#include <ostream>

namespace mabr {

struct blocktree
{
    enum direction { Unimportant, Horizontal, Vertical };

    block d;
    std::list<blocktree*> children;

    explicit blocktree(const block & src);

    ~blocktree();

    void add(const block & data);
    void add_all(const std::list<block> & data);
    bool valid() const; // For debug puproses only

    void print_xml(std::ostream &stream) const;
    direction get_first_level_blocks_direction() const;
};

}

#endif // BLOCKTREE_HPP
