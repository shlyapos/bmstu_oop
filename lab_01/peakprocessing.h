#ifndef PEAKPROCESSING_H
#define PEAKPROCESSING_H

#include "main_head.h"
#include "mainwindow.h"

typedef char peak_name_t[PEAK_LEN];

typedef struct
{
    float x;
    float y;
    float z;
} convers_t;

typedef struct
{
    peak_name_t name;
    float x;
    float y;
    float z;
} coord_t;

typedef coord_t *peak_t;

out_t peak_allocate(peak_t &p, int n);
void peak_clear(peak_t &p);
out_t peak_read_file(coord_t &p, FILE *fp);

void peak_move(coord_t &p, convers_t k);
void peak_rotate_axis(float &c1, float &c2, float a);
void peak_rotate_x(coord_t &peak, float angle);
void peak_rotate_y(coord_t &peak, float angle);
void peak_rotate_z(coord_t &peak, float angle);
void peak_rotate(coord_t &p, convers_t k);
void peak_scale(coord_t &p, convers_t k);
void peak_draw(coord_t p, canvas_t *s);

#endif // PEAKPROCESSING_H
