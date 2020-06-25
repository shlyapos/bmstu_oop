#ifndef DOORS_H
#define DOORS_H

#include <QObject>

#include "timer.h"

class Doors : public QObject
{
    Q_OBJECT

    enum stateDoor
    {
        OPENED,
        CLOSED,
        OPENING,
        CLOSING
    };

public:
    explicit Doors();

signals:
    void signalDoorClosed();
    void signalDoorOpened();

public slots:
    void slotDoorOpen();
    void slotDoorClose();

private slots:
    void slotDoorOpening();
    void slotDoorClosing();

private:
    QTimer timeOpen;
    QTimer timeClose;
    QTimer timeWait;

    stateDoor state;
};

#endif // DOORS_H
