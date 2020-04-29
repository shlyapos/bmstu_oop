#include "peakarray.h"
#include "operations.h"
#include "peakprocessing.h"

out_t peak_array_move(peak_t &p, int n, convers_t c)
{
    out_t error = EXIT_OK;

    if (!p)
    {
        error = ERROR_FIGURE_EMPTY;
    }

    if (!error)
    {
        for (int i = 0; i < n; i++)
        {
            peak_move(p[i], c);
        }
    }
    return error;
}

out_t peak_array_rotate(peak_t &p, int n, convers_t c)
{
    out_t error = EXIT_OK;

    if (!p)
    {
        error = ERROR_FIGURE_EMPTY;
    }

    if (!error)
    {
        for (int i = 0; i < n; i++)
        {
            peak_rotate(p[i], c);
        }
    }
    return error;
}

out_t peak_array_scale(peak_t &p, int n, convers_t c)
{
    out_t error = EXIT_OK;

    if (!p)
    {
        error = ERROR_FIGURE_EMPTY;
    }

    if (!error)
    {
        for (int i = 0; i < n; i++)
        {
            peak_scale(p[i], c);
        }
    }
    return error;
}

out_t peak_array_draw(peak_t p, int n, scene_t s)
{
    coord_t tmp;
    out_t error = EXIT_OK;

    if (!p)
    {
        error = ERROR_FIGURE_EMPTY;
    }

    if (!error)
    {
        for (int i = 0; i < n; i++)
        {
            tmp = p[i];
            transfer_into_2d(tmp, s.width, s.height);
            peak_draw(tmp, s.canvas);
        }
    }
    return error;
}


out_t peak_array_read_file(peak_t &p, int peaks, FILE *fp)
{
    out_t error = EXIT_OK;
    int i = 0;

    for(i = 0; (i < peaks) && !feof(fp) && (!error); i ++)
    {
        error = peak_read_file(p[i], fp);
    }

    if (i != peaks)
    {
        error = ERROR_FILE_DATA;
    }

    return error;
}
