#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include "main_head.h"
#include "figureprocessing.h"

typedef char filename_t[PATH_LEN];

out_t file_scan_parameters(int &peaks, int &ribs, FILE *file_name);

#endif // FILEPROCESSING_H
