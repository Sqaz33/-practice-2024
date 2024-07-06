#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencv2/opencv.hpp>
#include <QMainWindow>
#include <QPixMap>
#include <QImage>
#include <QString>
#include <QObject>
#include <QSlider>

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

    //TODO:
    //---------------------------------------------------------------------------------------------------
    cv::Mat* img = new cv::Mat(cv::imread("D:/Practice-2024/cppSln/src/q120404-01.jpg", cv::IMREAD_COLOR));
    //---------------------------------------------------------------------------------------------------

private slots:
    void circleColonies(); 
};

#endif // MAINWINDOW_H
