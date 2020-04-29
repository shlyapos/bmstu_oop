#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "main_head.h"
#include "figureprocessing.h"

out_t take_peak_by_name(coord_t &pnt, peak_t p, int n, peak_name_t name);

float take_2d_view_x(float c, float z, double screen);
float take_2d_view_y(float c, float z, double screen);
void transfer_into_2d(coord_t &p, double width, double height);

#endif // OPERATIONS_H
