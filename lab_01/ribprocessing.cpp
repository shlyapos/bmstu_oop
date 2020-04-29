#include "ribprocessing.h"
#include "operations.h"

out_t rib_allocate(rib_t &r, int n)
{
    out_t error = EXIT_OK;

    r = (rib_t)malloc(n * sizeof(rib_peak_t));

    if (!r)
    {
        error = ERROR_ALLOCATE;
    }

    return error;
}

void rib_clear(rib_t &r)
{
    free(r);
    r = nullptr;
}

out_t rib_read_file(rib_peak_t &r, FILE *fp)
{
    out_t error = EXIT_OK;
    int scan_out = fscanf(fp, "%s%s", r.peak1, r.peak2);

    if (scan_out != 2)
    {
        error = ERROR_FILE_DATA;
    }

    return error;
}

void rib_draw(coord_t p1, coord_t p2, canvas_t *s)
{
    QPen ribpen(Qt::black);
    ribpen.setWidth(2);

    s->addLine(p1.x, p1.y, p2.x, p2.y, ribpen);
}
