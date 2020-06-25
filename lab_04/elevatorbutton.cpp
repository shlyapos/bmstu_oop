#include "elevatorbutton.h"


// Constructor / Destructor
ElevatorButton::ElevatorButton(QWidget *parent) : QPushButton (parent)
{
    state = PASSIVE;
    numberFloor = 0;

    QObject::connect(this, SIGNAL(clicked()),           this, SLOT(slotPressProcessing()));
    QObject::connect(this, SIGNAL(signalResetButton()), this, SLOT(slotResetState()));
}

ElevatorButton::~ElevatorButton()
{  }


// Slots
void ElevatorButton::slotPressProcessing()
{
    if (this->state == PASSIVE)
    {
        this->state = PRESSED;
        this->setEnabled(false);

        emit signalRequestFloor(numberFloor);
    }
}

void ElevatorButton::slotResetState()
{
    if (this->state == PRESSED)
    {
        this->state = PASSIVE;
        this->setEnabled(true);
    }
}


// Other methods
void ElevatorButton::setFloorNumber(int floor)
{
    this->numberFloor = floor;
}
