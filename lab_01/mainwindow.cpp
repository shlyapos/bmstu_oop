#include "mainwindow.h"
#include "taskmanager.h"
#include "actiondifinition.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initButtonBind();
    initGraphicScene();
    initLineEdits();

    validateLineEdits();
}

MainWindow::~MainWindow()
{
    out_t error = EXIT_OK;
    action_t action = action_file_close_init();

    error = task_manager(action);

    if (!error)
    {
        delete ui;
    }
}


void MainWindow::initButtonBind()
{
    connect(ui->btn_file_open, SIGNAL(released()), this, SLOT(fileOpenButton()));
    connect(ui->btn_draw_figure, SIGNAL(released()), this, SLOT(drawFigureButton()));
    connect(ui->btn_move, SIGNAL(released()), this, SLOT(moveFigureButton()));
    connect(ui->btn_rotate, SIGNAL(released()), this, SLOT(rotateFigureButton()));
    connect(ui->btn_scale, SIGNAL(released()), this, SLOT(scaleFigureButton()));
}

void MainWindow::initLineEdits()
{
    // For move
    ui->lned_move_x->setText("0");
    ui->lned_move_y->setText("0");
    ui->lned_move_z->setText("0");

    // For rotate
    ui->lned_angle_x->setText("0");
    ui->lned_angle_y->setText("0");
    ui->lned_angle_z->setText("0");

    // For scale
    ui->lned_scale_x->setText("1");
    ui->lned_scale_y->setText("1");
    ui->lned_scale_z->setText("1");
}

void MainWindow::validateLineEdits()
{
    QValidator *val = new QDoubleValidator();
    val->setLocale(QLocale(QLocale::English));

    ui->lned_move_x->setValidator(val);
    ui->lned_move_y->setValidator(val);
    ui->lned_move_z->setValidator(val);

    ui->lned_angle_x->setValidator(val);
    ui->lned_angle_y->setValidator(val);
    ui->lned_angle_z->setValidator(val);

    ui->lned_scale_x->setValidator(val);
    ui->lned_scale_y->setValidator(val);
    ui->lned_scale_z->setValidator(val);
}

void MainWindow::initGraphicScene()
{
    double width = ui->graphicsView->width();
    double height = ui->graphicsView->height();

    scene.canvas = new QGraphicsScene(this);
    scene.width = width;
    scene.height = height;

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignCenter);

    ui->graphicsView->setScene(scene.canvas);
//    ui->graphicsView->setSceneRect(0, 0, width, height);
}


void MainWindow::fileOpenButton()
{
    out_t error = EXIT_OK;

    action_t action;
    filename_t file_name;

    QString qpath = QFileDialog::getOpenFileName();

    if (qpath.isEmpty())
    {
        error = EMPTY_FILE_PATH;
    }

    if (!error)
    {
        strcpy(file_name, qpath.toStdString().c_str());

        action = action_file_open_init(file_name);
        error = task_manager(action);
    }

    if (error)
    {
        outErrorMessage(error);
    }
}

void MainWindow::drawFigureButton()
{
    out_t error = EXIT_OK;
    action_t action;

    action = action_draw_init(scene);

    error = task_manager(action);

    if (error)
    {
        outErrorMessage(error);
    }
}

void MainWindow::moveFigureButton()
{
    out_t error = EXIT_OK;

    action_t action;
    convers_t k;

    if (ui->lned_move_x->text().isEmpty())
        error = ERROR_MOVE_X_EMPTY;
    if (ui->lned_move_y->text().isEmpty())
        error = ERROR_MOVE_Y_EMPTY;
    if (ui->lned_move_z->text().isEmpty())
        error = ERROR_MOVE_Z_EMPTY;

    if (!error)
    {
        k.x = ui->lned_move_x->text().toFloat();
        k.y = ui->lned_move_y->text().toFloat();
        k.z = ui->lned_move_z->text().toFloat();

        action = action_move_init(k);
        error = task_manager(action);

        if (!error)
        {
            action = action_draw_init(scene);
            error = task_manager(action);
        }
    }

    if (error)
    {
        outErrorMessage(error);
    }
}

void MainWindow::rotateFigureButton()
{
    out_t error = EXIT_OK;
    action_t action;
    convers_t k;

    if (ui->lned_angle_x->text().isEmpty())
        error = ERROR_ROT_X_EMPTY;
    if (ui->lned_angle_y->text().isEmpty())
        error = ERROR_ROT_Y_EMPTY;
    if (ui->lned_angle_z->text().isEmpty())
        error = ERROR_ROT_Z_EMPTY;

    if (!error)
    {
        k.x = ui->lned_angle_x->text().toFloat();
        k.y = ui->lned_angle_y->text().toFloat();
        k.z = ui->lned_angle_z->text().toFloat();

        action = action_rotate_init(k);
        error = task_manager(action);

        if (!error)
        {
            action = action_draw_init(scene);
            error = task_manager(action);
        }
    }

    if (error)
    {
        outErrorMessage(error);
    }
}

void MainWindow::scaleFigureButton()
{
    out_t error = EXIT_OK;
    action_t action;
    convers_t k;

    if (ui->lned_scale_x->text().isEmpty())
        error = ERROR_SCALE_X_EMPTY;
    if (ui->lned_scale_y->text().isEmpty())
        error = ERROR_SCALE_Y_EMPTY;
    if (ui->lned_scale_z->text().isEmpty())
        error = ERROR_SCALE_Z_EMPTY;

    if (!error)
    {
        k.x = ui->lned_scale_x->text().toFloat();
        k.y = ui->lned_scale_y->text().toFloat();
        k.z = ui->lned_scale_z->text().toFloat();

        action = action_scale_init(k);
        error = task_manager(action);

        if (error == EXIT_OK)
        {
            action = action_draw_init(scene);
            error = task_manager(action);
        }
    }

    if (error)
    {
        outErrorMessage(error);
    }
}


void MainWindow::outErrorMessage(out_t error)
{
    switch(error)
    {
    case ERROR_FILE_OPEN:
        QMessageBox::warning(this, "Ошибка","Выбранный файл повреждён или не существует");
        break;
    case ERROR_FILE_EMPTY:
        QMessageBox::warning(this, "Ошибка","Выбранный файл пуст или содержит некорректные значения в peaks");
        break;
    case ERROR_FILE_DATA:
        QMessageBox::warning(this, "Ошибка","Выбранный файл содержит некорректные данные");
        break;
    case ERROR_FILE_FEW_DATA:
        QMessageBox::warning(this, "Ошибка","Выбранный файл содержит недостаточно данных");
        break;
    case ERROR_MOVE_X_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле перемещения по X");
        break;
    case ERROR_MOVE_Y_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле перемещения по Y");
        break;
    case ERROR_MOVE_Z_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле перемещения по Z");
        break;
    case ERROR_ROT_X_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле вращения по оси X");
        break;
    case ERROR_ROT_Y_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле вращения по оси Y");
        break;
    case ERROR_ROT_Z_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле вращения по оси Z");
        break;
    case ERROR_SCALE_X_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле масштабирования по оси X");
        break;
    case ERROR_SCALE_Y_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле масштабирования по оси Y");
        break;
    case ERROR_SCALE_Z_EMPTY:
        QMessageBox::warning(this, "Ошибка","Не заполнено поле масштабирования по оси Z");
        break;
    case ERROR_FIGURE_EMPTY:
        QMessageBox::warning(this, "Ошибка","Фигура не прочитана");
        break;
    default:
        break;
    }
}
