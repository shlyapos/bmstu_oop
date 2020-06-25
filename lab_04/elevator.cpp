#include "elevator.h"

// Constructor
Elevator::Elevator(QObject* parent) : QObject(parent)
{
    QObject::connect(&cabin, SIGNAL(signalFloorVisit(int, direction_t)),    &controller, SLOT(slotChangeFloor(int, direction_t)));
    QObject::connect(&cabin, SIGNAL(signalFloorAchieve(int, direction_t)),  &controller, SLOT(slotAchieveFloor(int, direction_t)));

    QObject::connect(&controller, SIGNAL(signalSendFloor(int)), &cabin, SLOT(slotBusy(int)));
}

QWidget* Elevator::getWidget()
{
    return &controller;
}
