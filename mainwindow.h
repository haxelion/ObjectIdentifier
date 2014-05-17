/*
This file is part of ObjectIdentifier.

ObjectIdentifier is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nagen is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright 2014 Charles Hubain <charles.hubain@haxelion.eu>
*/

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
