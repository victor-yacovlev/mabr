#pragma once
#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "alignment.hpp"

#include <string>

namespace mabr {

struct block
{
    enum type { Minus, Plus, PlusType1, PlusType2, MinusType1, MinusType2 };

    size_t xs;
    size_t xe;
    const alignment * ref;
    type tp;
    std::vector<bool> used_rows;

    explicit block(const alignment * src, size_t xs_, size_t xe_);
    explicit block(const block & src, size_t xs_, size_t xe_);
    explicit block(const alignment * src);
    explicit block(const block & other);

    bool valid() const;
    inline operator bool() const { return valid(); }

    size_t width() const;
    size_t height() const;

    char get(size_t y, size_t x) const;

    std::string get_column(size_t index) const;
    std::string get_row(size_t index) const;

    void print_xml(std::ostream &stream) const;
};


}

#endif // BLOCK_HPP
