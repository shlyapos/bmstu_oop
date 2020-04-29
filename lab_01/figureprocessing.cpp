#include "figureprocessing.h"
#include "fileprocessing.h"
#include "actiondifinition.h"
#include "peakprocessing.h"
#include "ribprocessing.h"
#include "peakarray.h"
#include "ribarray.h"

figure_t figure_init()
{
    figure_t figure;

    figure.peak_numb = 0;
    figure.peaks = nullptr;

    figure.rib_numb = 0;
    figure.ribs = nullptr;

    return figure;
}

void figure_assign(figure_t &f1, figure_t &f2)
{
    f1.rib_numb = f2.rib_numb;
    f1.ribs = f2.ribs;

    f1.peak_numb = f2.peak_numb;
    f1.peaks = f2.peaks;
}

out_t figure_read_file(figure_t &f, char *file)
{
    out_t error = EXIT_OK;
    figure_t fig_tmp = figure_init();

    FILE *fp = fopen(file, "r");

    if (!fp)
    {
        error = ERROR_FILE_OPEN;
    }
    else
    {
        error = file_scan_parameters(fig_tmp.peak_numb, fig_tmp.rib_numb, fp);

        if (!error)
        {
            error = figure_allocate(fig_tmp);
        }
        if (!error)
        {
            error = peak_array_read_file(fig_tmp.peaks, fig_tmp.peak_numb, fp);

            if (!error)
            {
                error = rib_array_read_file(fig_tmp.ribs, fig_tmp.rib_numb, fp);
            }
        }

        fclose(fp);

        if (error)
        {
            figure_clear(fig_tmp);
        }
        else
        {
            figure_clear(f);
            figure_assign(f, fig_tmp);
        }
    }
    return error;
}

out_t figure_allocate(figure_t &f)
{
    out_t error = EXIT_OK;

    error = peak_allocate(f.peaks, f.peak_numb);

    if (!error)
    {
        error = rib_allocate(f.ribs, f.rib_numb);
    }

    if (error)
    {
        peak_clear(f.peaks);
        rib_clear(f.ribs);
    }

    return error;
}

out_t figure_clear(figure_t &f)
{
    out_t error = EXIT_OK;

    peak_clear(f.peaks);
    rib_clear(f.ribs);

    return error;
}


out_t figure_draw(figure_t f, scene_t s)
{
    out_t error = EXIT_OK;

    s.canvas->clear();

    error = rib_array_draw(f.ribs, f.rib_numb, f.peaks, f.peak_numb, s);

    if (!error)
    {
        error = peak_array_draw(f.peaks, f.peak_numb, s);
    }

    return error;
}


// Figure's actions
out_t figure_move(figure_t &f, convers_t c)
{
    out_t error = peak_array_move(f.peaks, f.peak_numb, c);
    return error;
}

out_t figure_rotate(figure_t &f, convers_t c)
{
    out_t error = peak_array_rotate(f.peaks, f.peak_numb, c);
    return error;
}

out_t figure_scale(figure_t &f, convers_t c)
{
    out_t error = peak_array_scale(f.peaks, f.peak_numb, c);
    return error;
}
