#ifndef CABIN_H
#define CABIN_H

#include <QObject>

#include "timer.h"
#include "doors.h"

class Cabin : public QObject
{
    Q_OBJECT

    enum stateCabin
    {
        MOVE,
        BUSY,
        FREE
    };

public:
    explicit Cabin(QObject* parent = nullptr);

signals:
    void signalFloorVisit(int floor, direction_t d);
    void signalFloorAchieve(int floor, direction_t d);

    void signalFloorAchieved();
    void signalMove();

public slots:
    void slotMove();
    void slotBusy(int floor);
    void slotFree();

private:
    int currentFloor = 0;
    int targetFloor;

    direction_t direction;
    stateCabin state;
    Doors doors;

    QTimer timeMove;
};

#endif // CABIN_H
