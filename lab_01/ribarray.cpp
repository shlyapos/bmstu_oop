#include "ribarray.h"
#include "operations.h"

out_t rib_array_draw(rib_t r, int rn, peak_t p, int pn, scene_t s)
{
    out_t error = EXIT_OK;

    coord_t tmp1;
    coord_t tmp2;

    if (!r)
    {
        error = ERROR_FIGURE_EMPTY;
    }

    if (!error)
    {
        for (int i = 0; i < rn; i++)
        {
            error = take_peak_by_name(tmp1, p, pn, r[i].peak1);

            if (!error)
            {
                error = take_peak_by_name(tmp2, p, pn, r[i].peak2);
            }

            if (!error)
            {
                transfer_into_2d(tmp1, s.width, s.height);
                transfer_into_2d(tmp2, s.width, s.height);

                rib_draw(tmp1, tmp2, s.canvas);
            }
        }
    }
    return error;
}

out_t rib_array_read_file(rib_t &r, int &ribs, FILE *fp)
{
    out_t error = EXIT_OK;
    int i;

    for (i = 0; (i < ribs) && !feof(fp) && (!error); i ++)
    {
        error = rib_read_file(r[i], fp);
    }

    if (i != ribs)
    {
        error = ERROR_FILE_DATA;
    }

    return error;
}
