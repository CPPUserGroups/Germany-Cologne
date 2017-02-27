#include <opencv2/core/core.hpp>
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

        cv::imshow("video", frame);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
}
