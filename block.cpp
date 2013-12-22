#include "block.hpp"

#include <cassert>
#include <ostream>

namespace mabr {

bool block::valid() const
{
    if (!ref) return false;
    bool valid_x = xs < xe;
    bool valid_y = false;
    for (size_t i=0u; i<used_rows.size(); i++) {
        if (used_rows[i]) {
            valid_y = true;
            break;
        }
    }
    bool valid_type =
            Plus == tp ||
            Minus == tp ||
            PlusType1 == tp ||
            PlusType2 == tp ||
            MinusType1 == tp ||
            MinusType2 == tp ;

    if (Minus == tp || MinusType1 == tp || MinusType2 == tp)
        valid_y = true;
    return valid_x && valid_y && valid_type;
}

size_t block::width() const
{
    return xe - xs;
}

size_t block::height() const
{
    size_t result = 0u;
    for (size_t i=0u; i<used_rows.size(); i++) {
        if (used_rows[i]) {
            result ++;
        }
    }
    return result;
}

char block::get(size_t y, size_t x) const
{
    assert(valid());
    return ref->at(y).at(x+xs);
}

string block::get_column(size_t index) const
{
    assert(valid());
    string result(height(), '\0');
    for (size_t y=0; y<height(); y++) {
        result[y] = get(y, index);
    }
    return result;
}

string block::get_row(size_t index) const
{
    assert(valid());
    string result(width(), '\0');
    for (size_t x=0; x<width(); x++) {
        result[x] = get(index, x);
    }
    return result;
}

block::block(const alignment * src, size_t xs_, size_t xe_)
    : ref(src)
    , xs(xs_), xe(xe_)
    , tp(MinusType1)
    , used_rows(src->size(), true)
{}

block::block(const block &src, size_t xs_, size_t xe_)
    : ref(src.ref)
    , xs(xs_), xe(xe_), tp(src.tp)
    , used_rows(src.used_rows)
{}

block::block(const alignment * src)
    : ref(src)
    , xs(0), xe(src->length())
    , tp(MinusType1)
    , used_rows(src->size(), true)
{}

block::block(const block &other)
    : ref(other.ref)
    , xs(other.xs), xe(other.xe)
    , tp(other.tp)
    , used_rows(other.used_rows)
{}

void block::print_xml(ostream &stream) const
{
    if (!valid()) return;

    string typee;
    switch (tp) {
    case Plus:
        typee = "plus";
        break;
    case PlusType1:
        typee = "plus_type_1";
        break;
    case PlusType2:
        typee = "plus_type_2";
        break;
    case Minus:
        typee = "minus";
        break;
    case MinusType1:
        typee = "minus_type_1";
        break;
    case MinusType2:
        typee = "minus_type_2";
        break;
    }
    stream << "<block "
           << "type='" << typee << "' "
           << "xs='" << xs << "' "
           << "xe='" << xe << "' "
           << "rows='";
    bool add_space = false;
    for (size_t i=0u; i<used_rows.size(); i++) {
        if (used_rows[i]) {
            if (add_space) stream << ' ';
            add_space = true;
            stream << i;
        }
    }
    stream << "' />" << endl;
}


}
