#include "fileprocessing.h"

out_t file_scan_parameters(int &peaks, int &ribs, FILE *file_name)
{
    out_t error = EXIT_OK;
    int scan_out;

    scan_out = fscanf(file_name, "%d%d", &peaks, &ribs);

    if (scan_out != 2)
    {
        error = ERROR_FILE_EMPTY;
    }

    return error;
}
