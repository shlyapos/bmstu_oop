#include "actiondifinition.h"

action_t action_file_open_init(filename_t name)
{
    action_t new_action;

    new_action.act_type = ACTION_FILE_OPEN;
    strcpy(new_action.file, name);

    return new_action;
}

action_t action_file_close_init()
{
    action_t new_action;

    new_action.act_type = ACTION_FILE_CLOSE;

    return new_action;
}

action_t action_draw_init(scene_t s)
{
    action_t new_action;

    new_action.act_type = ACTION_DRAW;
    new_action.scene = s;

    return new_action;
}

action_t action_move_init(convers_t k)
{
    action_t new_action;

    new_action.act_type = ACTION_MOVE;
    new_action.c = k;

    return new_action;
}

action_t action_rotate_init(convers_t k)
{
    action_t new_action;

    new_action.act_type = ACTION_ROTATE;
    new_action.c = k;

    return new_action;
}

action_t action_scale_init(convers_t k)
{
    action_t new_action;

    new_action.act_type = ACTION_SCALE;
    new_action.c = k;

    return new_action;
}
