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

#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <QThread>
#include <QString>
#include <QImage>
#include <QVector>
#include <QRgb>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <cstring>
#include <string>

class ProcessingThread : public QThread
{
    Q_OBJECT
private:
    QString *filename;
    QImage *input, *output;
    cv::Mat img_hsv, img_gray;
    std::vector<cv::Point> object;
    QVector<QRgb> gray_color_table;
    int output_state, hmin, hmax, smin, smax, minarea, epsilon, threshold1, threshold2;
    virtual void run();
    cv::Mat* qtToCv(QImage *image);
    QImage* cvToQt(cv::Mat* mat);

public:
    explicit ProcessingThread(QObject *parent = 0);
    void setInput(QString *filename);
    QImage* getOutput();
signals:

public slots:
    void setOutputState(int output_state) {this->output_state = output_state; start();}
    void setHMin(int hmin) {this->hmin = hmin; start();}
    void setHMax(int hmax) {this->hmax = hmax; start();}
    void setSMin(int smin) {this->smin = smin; start();}
    void setSMax(int smax) {this->smax = smax; start();}
    void setMinArea(int minarea) {this->minarea = minarea; start();}
    void setEpsilon(int epsilon) {this->epsilon = epsilon; start();}
    void setThreshold1(int threshold1) {this->threshold1 = threshold1; start();}
    void setThreshold2(int threshold2) {this->threshold2 = threshold2; start();}

};

#endif // PROCESSINGTHREAD_H
