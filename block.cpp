#include "block.hpp"

#include <cassert>
#include <ostream>

namespace mabr {

bool block::valid() const
{
    return ys < ye && xs < xe;
}

size_t block::width() const
{
    return xe - xs;
}

size_t block::height() const
{
    return ye - ys;
}

char block::get(size_t y, size_t x) const
{
    assert(valid());
    return ref->at(y+ys).at(x+xs);
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
    , ys(0), ye(src->size())
    , xs(xs_), xe(xe_)
    , tp(Minus)
    , good_rows(src->size(), false)
{}

block::block(const block &src, size_t xs_, size_t xe_)
    : ref(src.ref)
    , ys(0), ye(src.height())
    , xs(xs_), xe(xe_), tp(src.tp)
    , good_rows(src.good_rows)
{}

block::block(const alignment * src)
    : ref(src)
    , ys(0), ye(src->size())
    , xs(0), xe(src->length())
    , tp(Minus)
    , good_rows(src->size(), false)
{}

block::block(const block &other)
    : ref(other.ref)
    , ys(other.ys), ye(other.ye)
    , xs(other.xs), xe(other.xe)
    , tp(other.tp)
    , good_rows(other.good_rows)
{}

void block::print_html(ostream &stream) const
{
    if (!valid()) return;
    string clazz = "";
    switch (tp) {
    case Plus:
        clazz = "plus";
        break;
    case PlusType1:
        clazz = "plus1";
        break;
    case PlusType2:
        clazz = "plus2";
        break;
    case Minus:
        clazz = "minus";
        break;
    }
    stream << "<div class='block " << clazz << "' ";
    stream << "xs='" << xs << "' ";
    stream << "xe='" << xe << "' ";
    stream << "ys='" << ys << "' ";
    stream << "ye='" << ye << "'>" << endl;
    for (size_t y = ys; y<ye; y++) {
        stream << "<div class='block_row'>";
        for (size_t x = xs; x<xe; x++) {
            const char elem = ref->at(y).at(x);
            stream << "<span class='block_column'>";
            stream << elem;
            stream << "</span>";
        }
        stream << "</div>" << endl;
    }
    stream << "</div>";
}


}
