#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "alignment.hpp"

#include <string>

namespace mabr {

class block
{
public /*types*/:
    enum type { Minus = 0x00, Plus = 0xFF, PlusType1 = 0x0F, PlusType2 = 0xF0 };

public /*fields*/:
    size_t ys;
    size_t ye;
    size_t xs;
    size_t xe;
    const alignment * ref;
    type tp;
    vector<bool> good_rows;

public /*constructors*/:
    explicit block(const alignment * src, size_t xs_, size_t xe_);
    explicit block(const block & src, size_t xs_, size_t xe_);
    explicit block(const alignment * src);
    explicit block(const block & other);

public /*methods*/:
    bool valid() const;
    inline operator bool() const { return valid(); }

    size_t width() const;
    size_t height() const;

    char get(size_t y, size_t x) const;

    string get_column(size_t index) const;
    string get_row(size_t index) const;

    void print_html(ostream &stream) const;

};


}

#endif // BLOCK_HPP
