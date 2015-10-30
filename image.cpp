#include "image.h"
#include <QtWidgets>
#include <opencv/cv.hpp>

using namespace cv;

Image::Image()
{
    basicOperationType = -1;
    elementShape = -1;
}

void Image::setImage(QImage &img)
{
    image = img.convertToFormat(QImage::Format_RGB32);
    mat = Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
}

QImage Image::getImage()
{
    return image;
}

void Image::setElementShape(int shape)
{
    elementShape = shape;
}

void Image::setBasicOperationType(int operation)
{
    basicOperationType = operation;
}

void Image::setElementSize(Size size)
{
    elementSize = size;
}

int Image::getBasicOperationType()
{
    return basicOperationType;
}

int Image::getElementShape()
{
    return elementShape;
}

void Image::setElementAnchor(Point point)
{
    elementAnchor = point;
}

void Image::morphology()
{
    Mat element = getStructuringElement(elementShape, elementSize, elementAnchor);

    switch (getBasicOperationType()) {
    case 1:
        erode(mat, mat, element, elementAnchor, 1);
        break;
    case 0:
        dilate(mat, mat, element, elementAnchor, 1);
        break;
    }
}
