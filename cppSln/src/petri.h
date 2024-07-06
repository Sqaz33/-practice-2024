#ifndef SRC_PETRI_H
#define SRC_PETRI_H

#include <string>

#include <opencv2/opencv.hpp>


namespace petri {
    class Petri {
    public:
        Petri() = default;
        ~Petri() = default; 




    private:
        cv::Mat loadImage(const std::string& fullPath);
        



    };

} // namespace petri



#endif