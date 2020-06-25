#include "controller.h"

// Constructor / Destructor
Controller::Controller(QWidget* parent) : QWidget (parent)
{
    layout = new QVBoxLayout;
    this->setLayout(layout);

    for (int i = 0; i < FLOOR_NUMB; i++)
    {
        buttons[i] = new ElevatorButton();
        buttons[i]->setText(QString::number(i + 1));
        buttons[i]->setFloorNumber(i);

        floorQueue[i] = false;

        layout->addWidget(dynamic_cast<QPushButton*>(buttons[i]));
        QObject::connect(buttons[i], SIGNAL(signalRequestFloor(int)), this, SLOT(slotAddFloorQueue(int)));
    }
}

Controller::~Controller()
{
    for (int i = 0; i < FLOOR_NUMB; i++)
    {
        delete buttons[i];
    }

    delete layout;
}


// Slots
void Controller::slotChangeFloor(int floor, direction_t d)
{
    currentFloor = floor;
    direction = d;
}

void Controller::slotAchieveFloor(int floor, direction_t d)
{
    if (state == BUSY)
    {
        currentFloor = floor;
        direction = d;
        floorQueue[floor] = false;

        emit buttons[floor]->signalResetButton();

        if (getNewFloor(floor))
        {
            emit signalSendFloor(floor);
        }
        else
        {
            state = FREE;
        }
    }
}

void Controller::slotAddFloorQueue(int floor)
{
    state = BUSY;
    floorQueue[floor] = true;

    getNewFloor(floor);
    emit signalSendFloor(floor);
}

// Other methods
bool Controller::getNewFloor(int& newFloor)
{
    int step = direction;

    if (direction == 0)
    {
        step = -1;
    }

    for (int i = currentFloor; i < FLOOR_NUMB && i >= 0; i += step)
    {
        if (floorQueue[i])
        {
            newFloor = i;
            return true;
        }
    }

    step *= -1;

    for (int i = currentFloor; i < FLOOR_NUMB && i >= 0; i += step)
    {
        if (floorQueue[i])
        {
            newFloor = i;
            return true;
        }
    }

    return false;
}
