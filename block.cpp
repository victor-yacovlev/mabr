#include "block.hpp"

#include <ctype.h>

namespace mabr {


string block::get_column(size_t index) const
{
    string result(height(), '\0');
    for (size_t y=0; y<height(); y++) {
        result[y] = get(y, index);
    }
    return result;
}

string block::get_row(size_t index) const
{
    string result(width(), '\0');
    for (size_t x=0; x<width(); x++) {
        result[x] = get(index, x);
    }
    return result;
}

block::block(const alignment &src, size_t xs_, size_t xe_)
    : region<alignment,string,string,char>(src, xs_, xe_)
    , type_(Minus)
    , good_rows_(src.size(), false)
{}

block::block(const alignment &src)
    : region<alignment,string,string,char>(src)
    , type_(Minus)
    , good_rows_(src.size(), false)
{}

block::block(const block &other)
    : region<alignment,string,string,char>(other)
    , type_(other.type_)
    , good_rows_(other.good_rows_)
{}

void block::print_html(ostream &stream) const
{
    if (!valid()) return;
    string clazz = "";
    switch (type_) {
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
    stream << "<div class='region " << clazz << "' ";
    stream << "xs='" << xs << "' ";
    stream << "xe='" << xe << "' ";
    stream << "ys='" << ys << "' ";
    stream << "ye='" << ye << "'>" << endl;
    for (size_t y = ys; y<ye; y++) {
        stream << "<div class='region_row'>";
        for (size_t x = xs; x<xe; x++) {
            const char elem = ref.at(y).at(x);
            stream << "<span class='region_column'>";
            stream << elem;
            stream << "</span>";
        }
        stream << "</div>" << endl;
    }
    stream << "</div>";
}

void block::set_type(type t)
{
    type_ = t;
}

block::type block::get_type() const
{
    return type_;
}

bool block::is_good_row(size_t index) const
{
    return good_rows_[index];
}

void block::set_good_row(size_t index, bool value)
{
    good_rows_[index] = value;
}


}
