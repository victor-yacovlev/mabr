#include "mabr-c.h"

#include <ajacd.h>

int main(int argc, char * argv[])
{
    AjPMatrixf  matrix = 0;
    AjPSeqall   alignment = 0;
    float       tcol = 0.0f;
    float       trow = 0.0f;
    ajuint      tbcol = 1u;
    ajuint      tbrow = 1u;
    ajuint      tbsquare = 6u;

    embInit("mabr", argc, argv);

    matrix      = ajAcdGetMatrixf("datafile");
    tcol        = ajAcdGetFloat("tcol");
    trow        = ajAcdGetFloat("trow");
    tbrow       = (ajuint) ajAcdGetInt("tbrow");
    tbcol       = (ajuint) ajAcdGetInt("tbcol");
    tbsquare    = (ajuint) ajAcdGetInt("tbsquare");
    alignment   = ajAcdGetSeqall("alignment");

    mabr_initialize(tcol, trow, tbcol, tbrow, tbsquare, matrix);

    mabr_process(alignment);
    mabr_print_result_as_html();

    mabr_finalize();
    embExit();
    return 0;
}
