#include "cabin.h"

// Constructor
Cabin::Cabin(QObject* parent)
{
    state = FREE;

    currentFloor = 0;
    targetFloor = 0;

    direction = STILL;

    QObject::connect(&doors,    SIGNAL(signalDoorClosed()),     this,   SLOT(slotMove()));
    QObject::connect(&timeMove, SIGNAL(timeout()),              this,   SLOT(slotMove()));
    QObject::connect(this,      SIGNAL(signalFloorAchieved()),  this,   SLOT(slotFree()));
    QObject::connect(this,      SIGNAL(signalMove()),           this,   SLOT(slotMove()));
    QObject::connect(this,      SIGNAL(signalFloorAchieved()),  &doors, SLOT(slotDoorOpening()));
}


// Slots
void Cabin::slotMove()
{
    if (state == MOVE)
    {
        state = MOVE;
        qDebug() << "Move from floor   " << currentFloor + 1;

        if (currentFloor < targetFloor)
        {
            direction = UP;
            currentFloor ++;
        }
        else
        {
            direction = DOWN;
            currentFloor --;
        }

        if (currentFloor == targetFloor)
        {
            emit signalFloorAchieved();
        }
        else
        {
            timeMove.start(TIME_FLOOR_MOVE);
        }
    }
    else if (state == BUSY)
    {
        state = MOVE;

        if (currentFloor == targetFloor)
        {
            emit signalFloorAchieved();
        }
        else
        {
            timeMove.start(TIME_FLOOR_MOVE);
        }

        emit signalFloorVisit(currentFloor, direction);
    }
}

void Cabin::slotBusy(int floor)
{
    if (state == FREE)
    {
        state = BUSY;
        targetFloor = floor;

        if (currentFloor == targetFloor)
        {
            emit signalFloorAchieved();
        }
        else
        {
            if (currentFloor < targetFloor)
            {
                direction = UP;
            }
            else
            {
                direction = DOWN;
            }

            emit signalMove();
        }
    }
}

void Cabin::slotFree()
{
    if (state == MOVE)
    {
        state = FREE;
        qDebug() << "Stop on the floor " << currentFloor + 1;

        emit signalFloorAchieve(currentFloor, direction);
    }
}
