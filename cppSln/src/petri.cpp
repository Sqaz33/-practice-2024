#include "petri.h"

namespace {
    void filterImg(cv::Mat& img, int gaussianKernelSize) {
        cv::GaussianBlur(
            img, 
            img, 
            cv::Size(gaussianKernelSize, gaussianKernelSize), 
            0
        );
    }

    void thresholdImg(cv::Mat& img, int threshold) {
        if (img.channels() > 1) {
            cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        }
        cv::adaptiveThreshold(
            img,     
            img,         
            threshold,            
            cv::ADAPTIVE_THRESH_GAUSSIAN_C,
            cv::THRESH_BINARY,
            11,             
            2               
        );
    } 

    void getContoursByThresholdImg(const cv::Mat& img, std::vector<cv::Mat>& outContours) {
        cv::findContours(img, outContours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    }

    bool isCircleContour(const cv::Mat& contour, double circularityThreshold) {
        double perimeter = cv::arcLength(contour, true);
        
        // Апроксимация до полигона
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, 0.02 * perimeter, true);
        
        double area = cv::contourArea(contour);
        // Если меньше 5 вершин - это не окружность
        if (approx.size() < 5) {
            return false;
        }

        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contour, center, radius);
        double circleArea = CV_PI * std::pow(radius, 2);

        // Проверка на окружность
        return std::abs(1 - (area / circleArea)) < circularityThreshold;
    }
} // namespace


int petri::Petri::circleRoundColonies(
        const cv::Mat& img, 
        cv::Mat& outImg,
        int threshold,
        double circularityThresh,
        int gaussianKernelSize,
        RoundColours colour
) 
{ 
    //TODO: проверка на четность  gaussianKernelSize 
    cv::Mat copyImg = img.clone();
    // обработка
    filterImg(copyImg, gaussianKernelSize);
    thresholdImg(copyImg, threshold);

    std::vector<cv::Mat> contours;
    getContoursByThresholdImg(copyImg, contours);

    contours.erase(std::remove_if(contours.begin(), contours.end(), 
        [](const auto& contour) {
            return !isCircleContour(contour, 0.3);
        }), 
        contours.end()
    );

    outImg = img.clone();
    cv::drawContours(outImg, contours, -1, petri::roundColourToCVScalar(colour), 2);
    return contours.size();
}

cv::Scalar petri::roundColourToCVScalar(RoundColours colour) {
    static std::unordered_map<petri::RoundColours, cv::Scalar> scalars {
        {petri::GREEN, cv::Scalar(0,128,0)},
    };
    return scalars.at(colour);
}