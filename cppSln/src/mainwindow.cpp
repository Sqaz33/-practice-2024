#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace {
    QPixmap matToPixmap(const cv::Mat &mat) {
        // Check if the image is empty
        if (mat.empty()) {
            return QPixmap();
        }

        // Convert the cv::Mat to QImage
        QImage qImage;
        if (mat.type() == CV_8UC1) { // Grayscale image
            qImage = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        } else if (mat.type() == CV_8UC3) { // 3-channel color image (BGR)
            qImage = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
        } else if (mat.type() == CV_8UC4) { // 4-channel color image (BGRA)
            qImage = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        } else {
            // Unsupported format
            return QPixmap();
        }

        // Convert QImage to QPixmap
        return QPixmap::fromImage(qImage);
}
}

MainWindow::MainWindow(QWidget *parent) 
    : 
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    petri(petri::Petri::getPetri())
{
    ui->setupUi(this);

    // connectы
    connect(ui->horizontalSlider,
            &QSlider::valueChanged, 
            this, 
            &MainWindow::circleColonies
    );

    connect(ui->pushButton,
            &QPushButton::clicked, 
            this, 
            &MainWindow::selectImg
    );

    ui->horizontalSlider->setValue(150);

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::circleColonies() {
    ui->label_3->setText("Пороговое значение яркости пикселя: " + QString::number(ui->horizontalSlider->value()));
    if (img == nullptr) {
        return;
    }
    cv::Mat out;

    int coloniesCount = petri.circleRoundColonies(*img, out, ui->horizontalSlider->value());


    QPixmap map = matToPixmap(out);
    ui->label_2->setMaximumHeight(map.size().height());
    ui->label_2->setMaximumWidth(map.size().width());
    ui->label_2->setPixmap(map);

    ui->label->setText("Количество колоний: " + QString::number(coloniesCount));
}

void MainWindow::selectImg() {
    QString path = QFileDialog::getOpenFileName(
        this, 
        tr("Open Image"), 
        "D:/", 
        tr("Image Files (*.png *.jpg *.bmp)")
    );
    img = new cv::Mat(
        cv::imread(path.toStdString())
    );
    circleColonies();
}