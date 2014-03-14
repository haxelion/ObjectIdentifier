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
