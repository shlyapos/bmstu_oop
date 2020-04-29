#include "operations.h"
#include "peakprocessing.h"
#include "ribprocessing.h"

out_t take_peak_by_name(coord_t &pnt, peak_t p, int n, peak_name_t name)
{
    out_t error = EXIT_OK;
    bool is_exist = false;

    for (int i = 0; i < n; i++)
    {
        if (!strcmp(p[i].name, name))
        {
            is_exist = true;
            pnt = p[i];
        }
    }

    if (!is_exist)
    {
        error = ERROR_PEAK_NAME;
    }

    return error;
}


float take_2d_view_x(float c, float z, double screen)
{
    float new_c = (screen / 2) + ((c * DISTANCE) / (z + DISTANCE));
    return new_c;
}

float take_2d_view_y(float c, float z, double screen)
{
    float new_c = (screen / 2) + ((c * DISTANCE) / (z + DISTANCE) * -1);
    return new_c;
}

void transfer_into_2d(coord_t &p, double width, double height)
{
    p.x = take_2d_view_x(p.x, p.z, width);
    p.y = take_2d_view_y(p.y, p.z, height);
}
