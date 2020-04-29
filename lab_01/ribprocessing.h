#ifndef RIBPROCESSING_H
#define RIBPROCESSING_H

#include "main_head.h"
#include "peakprocessing.h"

typedef struct
{
    peak_name_t peak1;
    peak_name_t peak2;
} rib_peak_t;

typedef rib_peak_t *rib_t;

out_t rib_allocate(rib_t &r, int n);
void rib_clear(rib_t &r);
void rib_draw(coord_t p1, coord_t p2, canvas_t *s);
out_t rib_read_file(rib_peak_t &r, FILE *fp);

#endif // RIBPROCESSING_H
