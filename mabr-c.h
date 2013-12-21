#ifndef MABR_H
#define MABR_H

#include <ajmatrices.h>
#include <ajseqdata.h>

extern void mabr_initialize(
        float thereshold_column,
        float thereshold_row,
        size_t thereshold_width,
        size_t thereshold_height,
        size_t thereshold_square,
        AjPMatrixf matrix
        );

extern void mabr_process(AjPSeqall input);

extern void mabr_print_result_as_xml();

extern void mabr_finalize();


#endif
