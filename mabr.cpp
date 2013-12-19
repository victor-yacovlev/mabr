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

extern void print_result_as_html(ostream &stream)
{
    stream << "<html><head><style type='text/css'>" << endl <<
              ".data {"
              "display: block;"
              "font-family: monospace;"
              "font-size: 12pt;"
              "}" << endl <<
              ".tree_node {"
              "display: inline-table;"
              "margin: 0;"
              "padding: 0;"
              "}" << endl <<
              ".tree_node_row {"
              "display: table-row;"
              "margin: 0;"
              "padding: 0;"
              "}" << endl <<
              ".tree_node_column {"
              "display: table-column;"
              "margin: 0;"
              "padding: 0;"
              "}" << endl <<
              ".tree_element {"
              "display: table-cell;"
              "margin: 0;"
              "padding: 0;"
              "}" << endl <<
              ".block {"
              "display: inline-table;"
              "border: 1pt solid darkgray;"
              "padding: 0;"
              "}" << endl <<
              ".block_row {"
              "display: table-row;"
              "padding: 0;"
              "margin: 0;"
              "}" << endl <<
              ".block_column {"
              "display: table-cell;"
              "text-align: center;"
              "padding: 1pt;"
              "margin: 0;"
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
        result_->print_html(stream);
        stream << "</div>" << endl;
    }
    stream << "</body></html>" << endl;
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

extern "C" void mabr_print_result_as_html() {mabr::print_result_as_html(std::cout); }
