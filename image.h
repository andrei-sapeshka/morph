#ifndef IMAGE_H
#define IMAGE_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

using namespace cv;

class Image
{
private:
    QImage image;
    Mat mat;

    int basicOperationType = -1;

    int elementShape = -1;
    Size elementSize;
    Point elementAnchor;


public:
    Image();
    void setImage(QImage &img);
    void setBasicOperationType(int operation);
    int getBasicOperationType();

    void setElementShape(int shape);
    int getElementShape();

    void setElementSize(Size size);
    void setElementAnchor(Point point);

    void morphology();




    QImage getImage();

};

#endif // IMAGE_H
