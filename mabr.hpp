#ifndef MABR_HPP
#define MABR_HPP

extern "C" {
#include <ajmatrices.h>
#include <ajseqdata.h>
}

#include "alignment.hpp"
#include "region.hpp"

#include <deque>
#include <ostream>


namespace mabr {

using namespace std;

extern void initialize(
        float thereshold_column,
        float thereshold_row,
        AjPMatrixf matrix,
        AjPSeqall input
        );

extern void process();

extern void print_result(ostream & stream);
extern void print_result_as_html(ostream & stream);

extern void finalize();

}

#endif // MABR_HPP
