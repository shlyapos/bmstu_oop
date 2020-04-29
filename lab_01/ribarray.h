#ifndef RIBARRAY_H
#define RIBARRAY_H

#include "ribprocessing.h"

out_t rib_array_draw(rib_t r, int rn, peak_t p, int pn, scene_t s);
out_t rib_array_read_file(rib_t &r, int &ribs, FILE *fp);

#endif // RIBARRAY_H
