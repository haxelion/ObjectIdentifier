#include "processingthread.h"

ProcessingThread::ProcessingThread(QObject *parent) :
    QThread(parent)
{
    this->filename = NULL;
    input = NULL;
    output = NULL;
    output_state = 3;
    hmin = 0;
    hmax = 180;
    smin = 0;
    smax = 255;
    threshold1 = 50;
    threshold2 = 50;
    minarea = 0;
    epsilon = 0;
    for (int i=0; i<256; i++)
        gray_color_table.push_back(qRgb(i,i,i));
}

void ProcessingThread::setInput(QString *filename)
{
    if(this->filename != NULL)
    {
        delete(this->filename);
        this->filename = NULL;
    }
    this->filename = new QString(*filename);
}

void ProcessingThread::run()
{
    if(filename == NULL)
        return;
    if(output != NULL)
    {
        delete output;
        output = NULL;
    }
    input = new QImage(QImage(*filename).convertToFormat(QImage::Format_RGB888));
    if(output_state == 0)
    {
        output = input;
        return;
    }
    cv::Mat *img = qtToCv(input);
    img_gray.create(img->rows, img->cols, CV_8UC1);
    std::vector<std::vector<cv::Point> > contours;
    cv::cvtColor(*img, img_hsv, cv::COLOR_RGB2HSV);
    for(int i = 0; i < img_hsv.total(); i++)
    {
        if(img_hsv.data[i*3]<hmin || img_hsv.data[i*3]>hmax || img_hsv.data[i*3+1]<smin || img_hsv.data[i*3+1]>smax)
            img_gray.data[i] = 0;
        else
            img_gray.data[i] = img->data[i*3+2];
    }
    if(output_state == 1)
    {
        output = cvToQt(&img_gray);
        delete img;
        delete input;
        return;
    }
    cv::blur(img_gray, img_gray, cv::Size(5,5));
    cv::Canny(img_gray, img_gray, threshold1, threshold2);
    cv::dilate(img_gray, img_gray, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)));
    if(output_state == 2)
    {
        output = cvToQt(&img_gray);
        delete img;
        delete input;
        return;
    }
    cv::findContours(img_gray, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for(int i = 0; i<contours.size(); i++)
    {
        if(cv::contourArea(contours[i])>minarea)
        {
            cv::approxPolyDP(contours[i], contours[i], epsilon, true);
            cv::drawContours(*img, contours, i, cv::Scalar(0,0,255),3, CV_AA);
            for(int j = 0; j<contours[i].size(); j++)
                cv::circle(*img, contours[i][j], 5, cv::Scalar(255,0,0), -1, CV_AA);
        }
    }
    if(output_state == 3)
        output = input;
    delete img;
}

QImage* ProcessingThread::getOutput()
{
    return output;
}

cv::Mat* ProcessingThread::qtToCv(QImage *image)
{
    cv::Mat *ret = NULL;
    if(image->format() == QImage::Format_Indexed8)
        ret = new cv::Mat(image->height(),image->width(),CV_8UC1, (void*)image->bits());
    else if(image->format() == QImage::Format_RGB888)
        ret = new cv::Mat(image->height(),image->width(),CV_8UC3, (void*)image->bits());
    return ret;
}

QImage* ProcessingThread::cvToQt(cv::Mat *mat)
{
    QImage *ret = NULL;
    if(mat->type() == CV_8UC1)
    {
        ret = new QImage((const uchar*)mat->data, mat->cols, mat->rows, mat->step, QImage::Format_Indexed8);
        ret->setColorTable(gray_color_table);
    }
    else if(mat->type() == CV_8UC3)
        ret = new QImage((const uchar*)mat->data, mat->cols, mat->rows, mat->step, QImage::Format_RGB888);
    return ret;
}
