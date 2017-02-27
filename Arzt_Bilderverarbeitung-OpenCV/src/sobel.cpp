#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


int main(int argc, char* argv[]) {
    if( argc != 2) {
     std::cout <<" Usage: read_img IMAGENAME" << std::endl;
     return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); 

    if(!image.data) {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
 
    cv::Mat sobelx;
    cv::Sobel(image, sobelx, CV_8U, 1, 0);
    cv::Mat sobely;
    cv::Sobel(image, sobely, CV_8U, 0, 1);

    cv::namedWindow( "Sobel X", cv::WINDOW_AUTOSIZE );
    cv::imshow("Sobel X", sobelx);
    cv::namedWindow( "Sobel Y", cv::WINDOW_AUTOSIZE );
    cv::imshow("Sobel Y", sobely);

    cv::waitKey(0);
    return 0;
}
