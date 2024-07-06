#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencv2/opencv.hpp>
#include <QMainWindow>
#include <QPixMap>
#include <QImage>
#include <QString>
#include <QObject>
#include <QSlider>
#include <QFileDialog>
#include <QPushButton>

#include "petri.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    petri::Petri& petri;


    cv::Mat* img = nullptr;
private slots:
    void circleColonies(); 
    void selectImg();
};

#endif // MAINWINDOW_H
