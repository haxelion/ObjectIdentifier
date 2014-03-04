#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPaintEvent>
#include <QComboBox>
#include <QSpinBox>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include "processingthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void save();
    void refreshDisplay();

private:
    Ui::MainWindow *ui;
    ProcessingThread processing_thread;
    QSize previous_size;
    virtual void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
