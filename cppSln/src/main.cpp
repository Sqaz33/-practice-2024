#include <iostream>
#include <string>
#include <vector>

#include "petri.h"

#include <opencv2/opencv.hpp>

bool isCircleContour(const cv::Mat& contour) {
    double perimeter = cv::arcLength(contour, true);
    double approx = cv::
    
}

int main() {
    cv::Mat img = cv::imread("D:/cppPractice-2024/src/q120404-01.jpg", cv::IMREAD_COLOR);
    cv::Mat out = img;

    //filtring img
    // cv::Mat filtredImg;

    //filtring img
    int kernelSize = 13;
    cv::GaussianBlur(img, img, cv::Size(kernelSize, kernelSize), 0);


    if (img.channels() > 1) {
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    }
    cv::adaptiveThreshold(
        img,     
        img,         
        100,            
        cv::ADAPTIVE_THRESH_GAUSSIAN_C,
        cv::THRESH_BINARY,
        11,             
        2               
    );


    std::vector<cv::Mat> contours;
    cv::findContours(img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);



    cv::drawContours(out, contours, -1, (0, 100, 0), 2);


    
    // Create a window  
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    
    // Show the image in the window
    cv::imshow("Display Image", out);
    
    // Wait for a keystroke in the window
    cv::waitKey(0);
}