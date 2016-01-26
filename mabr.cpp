#include "mabr.hpp"
extern "C" {
#include "mabr-c.h"
#include <string.h>
#include <stdlib.h>
}

#include "matrix.hpp"
#include "processor.hpp"
#include "blocktree.hpp"

#include "linear_processor.hpp"

#include <iostream>
#include <list>

namespace mabr {

using std::list;
using std::string;
using std::endl;

static linear_processor* _linear_processor = nullptr;
static processor* _processor = nullptr;
static std::list<void*> _c_ptrs;
static blocktree* _result = nullptr;
static alignment* _alignment = nullptr;

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
    _processor = new processor(
                mx, thereshold_column, thereshold_row,
                thereshold_width, thereshold_height,
                thereshold_square
                );
    _linear_processor = new linear_processor;
}

extern void finalize()
{
    if (_processor) delete _processor;
    if (_result) delete _result;
    if (_alignment) delete _alignment;

    using ptrit = std::list<void*>::const_iterator;

    for (ptrit it=_c_ptrs.begin(); it!=_c_ptrs.end(); ++it) {
        void * ptr = *it;
        if (ptr) free(ptr);
    }
    _c_ptrs.clear();

}

extern void process(const alignment * al)
{
    if (!_processor) return;

    _result = _processor->run(al);
}

extern void print_result_as_xml(std::ostream &stream)
{
    stream << "<?xml version='1.0' encoding='ASCII'?>" << endl;
    stream << "<mabr>" << endl;
    stream << "<decomposition>" << endl;
    if (_processor) {
        _result->print_xml(stream);
    }
    stream << "</decomposition>" << endl;
    _alignment->print_xml(stream);
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
    mabr::_alignment = new mabr::alignment(input);
    mabr::process(mabr::_alignment);
}

extern "C" void mabr_print_result_as_xml() {mabr::print_result_as_xml(std::cout); }
