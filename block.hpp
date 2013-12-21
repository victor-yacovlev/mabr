#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "alignment.hpp"

#include <string>

namespace mabr {

class block
{
public /*types*/:
    enum type { Minus, Plus, PlusType1, PlusType2, MinusType1, MinusType2 };

public /*fields*/:
    size_t xs;
    size_t xe;
    const alignment * ref;
    type tp;
    vector<bool> used_rows;

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

    void print_xml(ostream &stream) const;

};


}

#endif // BLOCK_HPP
