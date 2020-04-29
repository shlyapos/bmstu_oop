#include "peakprocessing.h"
#include "main_head.h"
#include "actiondifinition.h"
#include "operations.h"

out_t peak_allocate(peak_t &p, int n)
{
    out_t error = EXIT_OK;

    p = (peak_t)malloc(n * sizeof(coord_t));

    if (!p)
    {
        error = ERROR_ALLOCATE;
    }

    return error;
}

void peak_clear(peak_t &p)
{
    free(p);
    p = nullptr;
}

out_t peak_read_file(coord_t &p, FILE *fp)
{
    out_t error = EXIT_OK;
    int scan_out = fscanf(fp, "%s%f%f%f", p.name, &p.x, &p.y, &p.z);

    if (scan_out != 4)
    {
        error = ERROR_FILE_DATA;
    }

    return error;
}


void peak_move(coord_t &p, convers_t k)
{
    p.x += k.x;
    p.y += k.y;
    p.z += k.z;
}


void peak_rotate_axis(float &c1, float &c2, float a)
{
    float tmp1 = c1;
    float tmp2 = c2;

    c1 = tmp1 * cos(a) - tmp2 * sin(a);
    c2 = tmp1 * sin(a) + tmp2 * cos(a);
}

void peak_rotate_x(coord_t &peak, float angle)
{
    angle *= M_PI / 180;

    peak_rotate_axis(peak.y, peak.z, angle);
}

void peak_rotate_y(coord_t &peak, float angle)
{
    angle *= M_PI / 180;

    peak_rotate_axis(peak.x, peak.z, angle);
}

void peak_rotate_z(coord_t &peak, float angle)
{
    angle *= M_PI / 180;

    peak_rotate_axis(peak.x, peak.y, angle);
}

void peak_rotate(coord_t &p, convers_t k)
{
    peak_rotate_x(p, k.x);
    peak_rotate_y(p, k.y);
    peak_rotate_z(p, k.z);
}


void peak_scale(coord_t &p, convers_t k)
{
    p.x *= k.x;
    p.y *= k.y;
    p.z *= k.z;
}

void peak_draw(coord_t p, canvas_t *s)
{
    // Radius
    int r = 2;

    QPen peakpen(Qt::red);
    peakpen.setWidth(3);

    s->addEllipse(p.x - r, p.y - r, (r * 2), (r * 2), peakpen);
}
