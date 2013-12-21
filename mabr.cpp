#include "mabr.hpp"
extern "C" {
#include "mabr-c.h"
#include <string.h>
#include <stdlib.h>
}

#include "matrix.hpp"
#include "processor.hpp"
#include "blocktree.hpp"

#include <list>
#include <iostream>

namespace mabr {

static processor* processor_ = 0;
static list<void*> c_ptrs_;
static blocktree* result_ = 0;
static alignment* alignment_ = 0;

extern void initialize(
        float thereshold_column,
        float thereshold_row,
        size_t thereshold_width,
        size_t thereshold_height,
        size_t thereshold_square,
        AjPMatrixf matrixx
        )
{
    matrix mx = matrix(matrixx);
    processor_ = new processor(
                mx, thereshold_column, thereshold_row,
                thereshold_width, thereshold_height,
                thereshold_square
                );
}

extern void finalize()
{
    if (processor_) delete processor_;
    if (result_) delete result_;
    if (alignment_) delete alignment_;

    typedef list<void*>::const_iterator ptrit;
    for (ptrit it=c_ptrs_.begin(); it!=c_ptrs_.end(); ++it) {
        void * ptr = *it;
        if (ptr) free(ptr);
    }
    c_ptrs_.clear();

}

extern void process(const alignment * al)
{
    if (!processor_) return;

    result_ = processor_->run(al);
}

extern void print_result_as_xml(ostream &stream)
{
    stream << "<?xml version='1.0' encoding='ASCII'?>" << endl;
    stream << "<mabr>" << endl;
    stream << "<decomposition>" << endl;
    if (processor_) {
        result_->print_xml(stream);
    }
    stream << "</decomposition>" << endl;
    alignment_->print_xml(stream);
    stream << "</mabr>" << endl;
}


} // end namespace mabr


/* Plain C wrappers */

extern "C" void mabr_initialize(float thereshold_column,
                                float thereshold_row,
                                size_t thereshold_width,
                                size_t thereshold_height,
                                size_t thereshold_square,
                                AjPMatrixf matrix)
{
    mabr::initialize(
                thereshold_column, thereshold_row,
                thereshold_width, thereshold_height,
                thereshold_square,
                matrix
                );
}

extern "C" void mabr_finalize() { mabr::finalize(); }

extern "C" void mabr_process(AjPSeqall input) {
    mabr::alignment_ = new mabr::alignment(input);
    mabr::process(mabr::alignment_);
}

extern "C" void mabr_print_result_as_xml() {mabr::print_result_as_xml(std::cout); }
