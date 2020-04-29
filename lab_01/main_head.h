#ifndef MAIN_HEAD_H
#define MAIN_HEAD_H

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsView>
#include <QDoubleValidator>

typedef enum
{
    PATH_LEN    = 100,
    PEAK_LEN    = 10,
    DISTANCE    = 1000
} param_t;

typedef enum
{
    EXIT_OK,
    EXIT_ERROR          = 1,
    ERROR_FILE_OPEN     = -1,
    ERROR_FILE_EMPTY    = -2,
    ERROR_FILE_DATA     = -3,
    ERROR_ALLOCATE      = -4,
    EMPTY_FILE_PATH     = -5,
    ERROR_FILE_FEW_DATA = -6,
    ERROR_MOVE_X_EMPTY  = -7,
    ERROR_MOVE_Y_EMPTY  = -8,
    ERROR_MOVE_Z_EMPTY  = -9,
    ERROR_ROT_X_EMPTY   = -10,
    ERROR_ROT_Y_EMPTY   = -11,
    ERROR_ROT_Z_EMPTY   = -12,
    ERROR_SCALE_X_EMPTY = -13,
    ERROR_SCALE_Y_EMPTY = -14,
    ERROR_SCALE_Z_EMPTY = -15,
    ERROR_FIGURE_EMPTY  = -16,
    ERROR_PEAK_NAME     = -17
} out_t;

#endif // MAIN_HEAD_H
