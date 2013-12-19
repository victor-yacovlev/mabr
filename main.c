#include "mabr-c.h"

#include <ajacd.h>

int main(int argc, char * argv[])
{
    AjPMatrixf  matrix = 0;
    AjPSeqall   alignment = 0;
    float       tcol = 0;
    float       trow = 0;

    embInit("mabr", argc, argv);

    matrix      = ajAcdGetMatrixf("datafile");
    tcol        = ajAcdGetFloat("tcol");
    trow        = ajAcdGetFloat("trow");
    alignment   = ajAcdGetSeqall("alignment");

    mabr_initialize(tcol, trow, matrix);

    mabr_process(alignment);
    mabr_print_result_as_html();

    mabr_finalize();
    embExit();
    return 0;
}
