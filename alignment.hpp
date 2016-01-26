#pragma once
#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP
extern "C" {
#include <ajseqdata.h>
#include <ajseq.h>
}

#include <ostream>
#include <string>
#include <vector>

namespace  mabr {

struct alignment
        : public std::vector<std::string>
{
    explicit alignment(AjPSeqall source);
    size_t length() const;
    std::string get_column(size_t index) const;
    std::string get_row(size_t index) const;
    void print_xml(std::ostream & stream) const;
};

}

#endif // ALIGNMENT_HPP
