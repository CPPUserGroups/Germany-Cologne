#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


int main(int argc, char* argv[]) {
    if( argc != 2) {
     std::cout <<" Usage: read_img IMAGENAME" << std::endl;
     return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR); 

    if(!image.data) {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // split into channels (in this case RGB)
    cv::Mat channel[3];
    cv::split(image, channel);

    // show
    cv::namedWindow("Blue", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Green", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Red", cv::WINDOW_AUTOSIZE);

    cv::imshow("Blue", channel[0]);
    cv::imshow("Green", channel[1]);
    cv::imshow("Red", channel[2]);

    cv::waitKey(0);
    return 0;
}
