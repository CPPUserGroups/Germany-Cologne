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

    cv::Mat old_frame;
    cap >> old_frame;

    for(;;)
    {
        cv::Mat frame;
        cap >> frame;

        cv::Mat diff_image;
        cv::absdiff(old_frame, frame, diff_image);


        old_frame = frame;

        cv::imshow("video", diff_image);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
}
