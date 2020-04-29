#ifndef PEAKARRAY_H
#define PEAKARRAY_H

#include "peakprocessing.h"

out_t peak_array_move(peak_t &p, int n, convers_t c);
out_t peak_array_rotate(peak_t &p, int n, convers_t c);
out_t peak_array_scale(peak_t &p, int n, convers_t c);
out_t peak_array_draw(peak_t p, int n, scene_t s);

out_t peak_array_read_file(peak_t &p, int peaks, FILE *fp);;

#endif // PEAKARRAY_H
