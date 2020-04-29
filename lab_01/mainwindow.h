#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main_head.h"
#include "ui_mainwindow.h"

typedef QGraphicsScene canvas_t;

typedef struct
{
    canvas_t *canvas;
    double width;
    double height;
}
scene_t;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initGraphicScene();

private:
    scene_t scene;
    void initButtonBind();
    void initLineEdits();
    void validateLineEdits();
    void outErrorMessage(out_t error);

private slots:
    void fileOpenButton();
    void drawFigureButton();
    void moveFigureButton();
    void rotateFigureButton();
    void scaleFigureButton();
};

#endif // MAINWINDOW_H
