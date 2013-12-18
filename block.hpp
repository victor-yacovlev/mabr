#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "alignment.hpp"
#include "region.hpp"

#include <string>

namespace mabr {

class block
        : public region<alignment,string,string,char>
{
public:
    explicit block(const alignment & src, size_t xs_, size_t xe_);
    explicit block(const block & src, size_t xs_, size_t xe_);
    explicit block(const alignment & src);
    explicit block(const block & other);

    enum type { Minus = 0x00, Plus = 0xFF, PlusType1 = 0x0F, PlusType2 = 0xF0 };

    string get_column(size_t index) const;
    string get_row(size_t index) const;

    type get_type() const;
    void set_type(type t);

    bool is_good_row(size_t index) const;
    void set_good_row(size_t index, bool value);

    void print_html(ostream &stream) const;

private:
    type type_;
    vector<bool> good_rows_;

};


}

#endif // BLOCK_HPP
