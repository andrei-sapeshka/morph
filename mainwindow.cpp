#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"
#include "qdebug.h"
#include <QtWidgets>
#include <opencv2/opencv.hpp>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = Image();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxCols_valueChanged(int arg1)
{

}

void MainWindow::on_spinBoxRows_valueChanged(int arg1)
{

}

void MainWindow::on_horizontalSliderIter_valueChanged(int value)
{

}

int MainWindow::loadImage(const QString &filePath)
{
    QImage img(filePath);
    if (img.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(filePath)));
        setWindowFilePath(QString());
        ui->labelImage->setPixmap(QPixmap());
        ui->labelImage->adjustSize();
        return false;
    }
    image.setImage(img);

    ui->scrollAreaWidgetContents->setMinimumSize(img.size());
    ui->labelImage->setMinimumSize(img.size());
    ui->labelImage->setPixmap(QPixmap::fromImage(image.getImage()));
    return true;
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.first());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted && !loadImage(dialog.selectedFiles().first())) {};
}

void MainWindow::on_pushButtonBasic_clicked()
{
    if (image.getBasicOperationType() < 0) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr("Select basic operation."));
        return;
    }

    qDebug() << "basic operation type = " << image.getBasicOperationType() << endl;

    if (image.getElementShape() < 0) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr("Select element shape."));
        return;
    }

    qDebug() << "element shape = " << image.getElementShape() << endl;

    int cols = ui->spinBoxCols->value();
    int rows = ui->spinBoxRows->value();
    int x = ui->spinBoxAx->value();
    int y = ui->spinBoxAy->value();

    image.setElementSize(Size(cols, rows));
    image.setElementAnchor(Point(x, y));

    image.morphology();

    QImage img = image.getImage();
    ui->scrollAreaWidgetContents->setMinimumSize(img.size());
    ui->labelImage->setMinimumSize(img.size());
    ui->labelImage->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_radioShapeRect_clicked()
{
    image.setElementShape(MORPH_RECT);
}

void MainWindow::on_radioShapeCross_clicked()
{
    image.setElementShape(MORPH_CROSS);
}

void MainWindow::on_radioShapeEllipse_clicked()
{
    image.setElementShape(MORPH_ELLIPSE);
}

void MainWindow::on_radioErode_clicked()
{
    image.setBasicOperationType(1);
}

void MainWindow::on_radioDilate_clicked()
{
    image.setBasicOperationType(0);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QRect cr = contentsRect();
    QRect sr = ui->scrollArea->geometry();
    ui->scrollArea->setGeometry(QRect(sr.left(), sr.top(),
                                      cr.width() - sr.left() - 3,
                                      cr.height() - sr.top() - 50));
}
