#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor / Destructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    layout = new QVBoxLayout;

    ui->centralWidget->setLayout(layout);
    layout->addWidget(elevator.getWidget());
}

MainWindow::~MainWindow()
{
    delete layout;
    delete ui;
}
