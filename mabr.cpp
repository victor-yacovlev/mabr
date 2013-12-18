#include "mabr.hpp"
extern "C" {
#include "mabr-c.h"
#include <string.h>
#include <stdlib.h>
}

#include "matrix.hpp"
#include "processor.hpp"

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
        AjPMatrixf matrixx
        )
{
    matrix mx = matrix(matrixx);
    processor_ = new processor(mx, thereshold_column, thereshold_row);
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

    result_ = processor_->run(*al);
}

extern void print_result(ostream &stream)
{
    if (!processor_) return;

    const blocktree::list_type & res = result_->children;
    typedef blocktree::list_type::const_iterator cit;
    for (cit it = res.begin(); it != res.end(); ++it) {
        const blocktree * node = *it;
        const block & ref = node->d;
        ref.print(stream);
    }
}

extern void print_result_as_html(ostream &stream)
{
    stream << "<html><head><style type='text/css'>" << endl <<
              ".data {"
              "display: block;"
              "font-family: monospace;"
              "font-size: 12pt;"
              "}" << endl <<
              ".region {"
              "display: inline-table;"
              "margin-top: 0.5cm;"
              "margin-bottom: 0.5cm;"
              "margin-left: 1pt;"
              "margin-right: 1pt;"
              "padding: 0;"
              "border-left: 1pt solid black;"
              "}" << endl <<
              ".region_row {"
              "display: table-row;"
              "}" << endl <<
              ".region_column {"
              "display: table-cell;"
              "text-align: center;"
              "}" << endl <<
              ".plus {"
              "background-color: lightsalmon;"
              "}" << endl <<
              ".plus1 {"
              "background-color: lightblue;"
              "}" << endl <<
              ".plus2 {"
              "background-color: lightgreen;"
              "}" << endl <<
              "</style></head>"
              "<body>" << endl;
    if (processor_) {
        stream << "<div class='data'>" << endl;
        const blocktree::list_type & res = result_->children;
        typedef blocktree::list_type::const_iterator cit;
        for (cit it = res.begin(); it != res.end(); ++it) {
            const blocktree * node = *it;
            const block & ref = node->d;
            ref.print_html(stream);
        }
        stream << "</div>" << endl;
    }
    stream << "</body></html>" << endl;
}


} // end namespace mabr


/* Plain C wrappers */

extern "C" void mabr_initialize(float thereshold_column,
                                float thereshold_row,
                                AjPMatrixf matrix)
{
    mabr::initialize(thereshold_column, thereshold_row, matrix);
}

extern "C" void mabr_finalize() { mabr::finalize(); }

extern "C" void mabr_process(AjPSeqall input) {
    mabr::alignment_ = new mabr::alignment(input);
    mabr::process(mabr::alignment_);
}

extern "C" void mabr_print_result() {mabr::print_result(std::cout); }
extern "C" void mabr_print_result_as_html() {mabr::print_result_as_html(std::cout); }
