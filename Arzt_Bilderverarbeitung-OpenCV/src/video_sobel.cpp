#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


int main(int argc, char* argv[]) {

    cv::VideoCapture cap(0);

    if(!cap.isOpened()) {
        std::cerr << "Capture Device ID cannot be opened." << std::endl;
        return -1;
    }

    cv::namedWindow("video", cv::WINDOW_AUTOSIZE);

    for(;;)
    {
        cv::Mat frame;
        cap >> frame;

        cv::Mat gray;
        cv::cvtColor(frame, gray, CV_BGR2GRAY);

        cv::Mat sobelx;
        cv::Sobel(gray, sobelx, CV_8U, 1, 0);

        cv::imshow("video", sobelx);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
}
