#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "image.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Image image;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:

    void on_spinBoxCols_valueChanged(int arg1);

    void on_spinBoxRows_valueChanged(int arg1);

    void on_horizontalSliderIter_valueChanged(int value);

    void on_actionOpen_triggered();

    int loadImage(const QString &filePath);

    void on_pushButtonBasic_clicked();

    void on_radioShapeRect_clicked();

    void on_radioShapeCross_clicked();

    void on_radioShapeEllipse_clicked();

    void on_radioErode_clicked();

    void on_radioDilate_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
