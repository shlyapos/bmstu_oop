#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QDebug>

#define FLOOR_NUMB 6

typedef enum
{
    TIME_DOOR_PROC = 500,
    TIME_DOOR_WAIT = 500,
    TIME_FLOOR_MOVE = 1000
} status_timer_t;

typedef enum
{
    UP = 1,
    STILL = 0,
    DOWN = -1
} direction_t;

#endif // TIMER_H
