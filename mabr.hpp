#ifndef MABR_HPP
#define MABR_HPP

extern "C" {
#include <ajmatrices.h>
#include <ajseqdata.h>
}

#include "alignment.hpp"

#include <deque>
#include <ostream>


namespace mabr {

using namespace std;

extern void initialize(
        float thereshold_column,
        float thereshold_row,
        size_t thereshold_width,
        size_t thereshold_height,
        size_t thereshold_square,
        AjPMatrixf matrix
        );

extern void process(const alignment * al);

extern void print_result_as_xml(ostream & stream);

extern void finalize();

}

#endif // MABR_HPP
