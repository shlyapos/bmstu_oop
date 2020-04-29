#ifndef FIGUREALLOCATE_H
#define FIGUREALLOCATE_H

#include "main_head.h"
#include "mainwindow.h"
#include "peakprocessing.h"
#include "ribprocessing.h"

typedef struct
{
    int peak_numb;
    int rib_numb;
    peak_t peaks;
    rib_t ribs;
} figure_t;

figure_t figure_init();
void figure_assign(figure_t &f1, figure_t &f2);
out_t figure_read_file(figure_t &f, char *file);
out_t figure_allocate(figure_t &f);
out_t figure_clear(figure_t &f);
out_t figure_draw(figure_t f, scene_t s);

out_t figure_move(figure_t &f, convers_t c);
out_t figure_rotate(figure_t &f, convers_t c);
out_t figure_scale(figure_t &f, convers_t c);

#endif // FIGUREALLOCATE_H
