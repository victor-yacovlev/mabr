#ifndef REGION_HPP
#define REGION_HPP

#include <stddef.h>
#include <ostream>

namespace mabr {

using namespace std;

template <
        typename ContainerType,
        typename RowType,
        typename ColumnType,
        typename AtomType
>
struct region
{
    const ContainerType & ref;
    size_t ys;
    size_t ye;
    size_t xs;
    size_t xe;

    inline bool valid() const {
        return ys < ye && xs < xe;
    }

    inline operator bool() const { return valid(); }

    inline size_t width() const { return xe - xs; }
    inline size_t height() const { return ye - ys; }


    inline explicit region(const ContainerType & src, size_t xs_, size_t xe_):
        ref(src), ys(0), ye(src.size()), xs(xs_), xe(xe_) {}

    inline explicit region(const region & src, size_t xs_, size_t xe_):
        ref(src.ref), ys(0), ye(src.height()), xs(xs_), xe(xe_) {}

    inline explicit region(const ContainerType & src):
        ref(src), ys(0), ye(src.size()), xs(0), xe(src[0].size()) {}

    inline explicit region(const region & other):
        ref(other.ref), ys(other.ys), ye(other.ye), xs(other.xs), xe(other.xe) {}

    inline AtomType get(size_t y, size_t x) const
    {
        return ref.at(y+ys).at(x+xs);
    }

    inline RowType get_row(size_t y) const
    {
        RowType row;
        row.resize(width());
        for (size_t x=0u; x<width(); x++) {
            row[x] = get(y, x);
        }
        return row;
    }

    inline ColumnType get_column(size_t x) const
    {
        ColumnType column;
        column.resize(height());
        for (size_t y=0u; y<height(); y++) {
            column[y] = get(y, x);
        }
        return column;
    }

    inline virtual void print(ostream & stream) const
    {
        if (!valid()) return;

        stream << "{ xs = " << xs << "; xe = " << xe
               << "; ys = " << ys << "; ye = " << ye << "}" << endl;

        for (size_t y = ys; y<ye; y++) {
            for (size_t x = xs; x<xe; x++) {
                const AtomType & elem = ref.at(y).at(x);
                stream << elem;
            }
            stream << endl;
        }
        stream << endl;
    }

    inline virtual void print_html(ostream & stream) const
    {
        if (!valid()) return;

        stream << "<div class='region' ";
        stream << "xs='" << xs << "' ";
        stream << "xe='" << xe << "' ";
        stream << "ys='" << ys << "' ";
        stream << "ye='" << ye << "'>" << endl;
        for (size_t y = ys; y<ye; y++) {
            stream << "<div class='region_row'>";
            for (size_t x = xs; x<xe; x++) {
                const AtomType & elem = ref.at(y).at(x);
                stream << "<span class='region_column'>";
                stream << elem;
                stream << "</span>";
            }
            stream << "</div>" << endl;
        }
        stream << "</div>";
    }
};


}

#endif // REGION_HPP
