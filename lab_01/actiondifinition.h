#ifndef ACTIONDIFINITION_H
#define ACTIONDIFINITION_H

#include "main_head.h"
#include "mainwindow.h"
#include "fileprocessing.h"

typedef enum
{
    ACTION_FILE_CLOSE   = -10,
    ACTION_FILE_OPEN    = -20,
    ACTION_DRAW         = -30,
    ACTION_MOVE         = -40,
    ACTION_ROTATE       = -50,
    ACTION_SCALE        = -60
} action_type_t;

typedef struct
{
    action_type_t act_type;
    filename_t file;
    scene_t scene;
    convers_t c;
} action_t;

action_t action_file_open_init(filename_t name);
action_t action_file_close_init();
action_t action_draw_init(scene_t s);
action_t action_move_init(convers_t k);
action_t action_rotate_init(convers_t k);
action_t action_scale_init(convers_t k);

#endif // ACTIONDIFINITION_H
