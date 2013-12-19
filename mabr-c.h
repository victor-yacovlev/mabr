#ifndef MABR_H
#define MABR_H

#include <ajmatrices.h>
#include <ajseqdata.h>

extern void mabr_initialize(
        float thereshold_column,
        float thereshold_row,
        AjPMatrixf matrix
        );

extern void mabr_process(AjPSeqall input);

extern void mabr_print_result_as_html();

extern void mabr_finalize();


#endif
