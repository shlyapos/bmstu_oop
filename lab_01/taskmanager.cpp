#include "taskmanager.h"
#include "actiondifinition.h"

out_t task_manager(action_t a)
{
    out_t error = EXIT_OK;
    static figure_t figure = figure_init();

    switch(a.act_type)
    {
    case ACTION_FILE_OPEN:
        error = figure_read_file(figure, a.file);
        break;
    case ACTION_FILE_CLOSE:
        error = figure_clear(figure);
        break;
    case ACTION_DRAW:
        error = figure_draw(figure, a.scene);
        break;
    case ACTION_MOVE:
        error = figure_move(figure, a.c);
        break;
    case ACTION_ROTATE:
        error = figure_rotate(figure, a.c);
        break;
    case ACTION_SCALE:
        error = figure_scale(figure, a.c);
        break;
    }
    return error;
}
