#include <iostream>
#include <string>
#include <vector>
#include <cmath>


#include <opencv2/opencv.hpp>



bool isCircleContour(const cv::Mat& contour, double circularityThreshold = 0.3) {
    // Calculate the perimeter of the contour
    double perimeter = cv::arcLength(contour, true);
    
    // Approximate the contour to a polygon
    std::vector<cv::Point> approx;
    cv::approxPolyDP(contour, approx, 0.02 * perimeter, true);
    
    // Calculate the area of the contour
    double area = cv::contourArea(contour);

    // If the approximated polygon has fewer than 5 vertices, it is not a circle
    if (approx.size() < 5) {
        return false;
    }

    // Find the minimum enclosing circle for the contour
    cv::Point2f center;
    float radius;
    cv::minEnclosingCircle(contour, center, radius);
    
    // Calculate the area of the enclosing circle
    double circleArea = CV_PI * std::pow(radius, 2);

    // Check the circularity
    return std::abs(1 - (area / circleArea)) < circularityThreshold;
}


int main() {
    cv::Mat img = cv::imread("D:/Practice-2024/cppSln/src/q120404-01.jpg", cv::IMREAD_COLOR);
    cv::Mat out = img;


    //filtring img
    int kernelSize = 13;
    cv::GaussianBlur(img, img, cv::Size(kernelSize, kernelSize), 0);


    if (img.channels() > 1) {
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    }
    cv::adaptiveThreshold(
        img,     
        img,         
        221,            
        cv::ADAPTIVE_THRESH_GAUSSIAN_C,
        cv::THRESH_BINARY,
        11,             
        2               
    );


    std::vector<cv::Mat> contours;
    cv::findContours(img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);



    cv::drawContours(out, contours, -1, (0, 100, 0), 2);

    contours.erase(std::remove_if(contours.begin(), contours.end(), 
        [](const auto& contour) {
            return !isCircleContour(contour, 0.3);
        }), 
        contours.end());

    // Create a window  
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    
    // Show the image in the window
    cv::imshow("Display Image", out);
    
    // Wait for a keystroke in the window
    cv::waitKey(0);
}