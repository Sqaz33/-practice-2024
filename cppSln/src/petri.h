#ifndef SRC_PETRI_H
#define SRC_PETRI_H

#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

#include <opencv2/opencv.hpp>



namespace petri {
    enum RoundColours {
        GREEN,
    };

    cv::Scalar roundColourToCVScalar(RoundColours colour);

    class Petri final {
    public:
        static Petri& getPetri() {
            static Petri pet;
            return pet;
        }
        
        // обрисовать круглые колонии
        int circleRoundColonies(
            const cv::Mat& img, 
            cv::Mat& outImg,
            int threshold,
            double circularityThresh = 0.3, 
            int gaussianKernelSize = 3,
            RoundColours colour = RoundColours::GREEN
        );
        //.... возможны еще методы обрисовки или их совмщение
        // enum AnalyzeMethod {
        //      LOOK_FOR_ROUND_COLUMNS,
        // };
    private:
        Petri() = default;
        Petri(const Petri& other) = delete;
        Petri& operator=(const Petri& other) = delete;
    };
} // namespace petri



#endif // SRC_PETRI_H