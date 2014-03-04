#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,&QAction::triggered, this, &MainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(&processing_thread, &ProcessingThread::finished, this, &MainWindow::refreshDisplay);
    connect(ui->stage_selector, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), &processing_thread, &ProcessingThread::setOutputState);
    connect(ui->hmin_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setHMin);
    connect(ui->hmax_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setHMax);
    connect(ui->smin_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setSMin);
    connect(ui->smax_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setSMax);
    connect(ui->threshold1_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setThreshold1);
    connect(ui->threshold2_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setThreshold2);
    connect(ui->minarea_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setMinArea);
    connect(ui->epsilon_input, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &processing_thread, &ProcessingThread::setEpsilon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    if(processing_thread.isRunning() == false)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *jpeg *.bmp)"));
        processing_thread.setInput(&fileName);
        processing_thread.start();
    }
}

void MainWindow::save()
{

}

void MainWindow::refreshDisplay()
{
    QImage *output = processing_thread.getOutput();
    if(output != NULL)
    {
        QPixmap pixmap = QPixmap::fromImage(output->scaled(ui->display->size(), Qt::KeepAspectRatio));
        ui->display->setPixmap(pixmap);
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    if(previous_size != ui->display->size())
    {
        previous_size = ui->display->size();
        refreshDisplay();
    }
    QMainWindow::paintEvent(e);
}
