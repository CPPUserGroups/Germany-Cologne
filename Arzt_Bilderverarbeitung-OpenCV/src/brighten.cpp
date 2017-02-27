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
 
    std::cout << "channels: " << image.channels() << std::endl;

    int i, j;
    uchar r, g, b;

    for (int i = 0; i < image.rows; ++i) {
        // point to first pixel in row 
        cv::Vec3b* pixel = image.ptr<cv::Vec3b>(i); 

        for (int j = 0; j < image.cols; ++j) {
            r = pixel[j][2];
            pixel[j][2] = r > 205 ? 255 : r + 50;
            g = pixel[j][1];
            pixel[j][1] = g > 205 ? 255 : g + 50;
            b = pixel[j][0];
            pixel[j][0] = b > 205 ? 255 : b + 50;
        }
    }

    cv::namedWindow( "Brighter", cv::WINDOW_AUTOSIZE );
    cv::imshow("Brighter", image);

    cv::waitKey(0);
    return 0;
}
