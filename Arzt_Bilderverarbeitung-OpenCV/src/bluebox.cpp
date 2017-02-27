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
    image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR); 

    if(!image.data) {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // Here the result should be
    cv::Mat result;

    // -----------------------------------------------------------------------------
    // test 1 -> directly manipulate the RGB image
     int i, j;
    uchar r, g, b;

    for (int i = 0; i < image.rows; ++i) {
        // point to first pixel in row
        cv::Vec3b* pixel = image.ptr<cv::Vec3b>(i);

        for (int j = 0; j < image.cols; ++j) {
            r = pixel[j][2];
            g = pixel[j][1];
            b = pixel[j][0];
            //std::cout << "r: " << (uint16_t)r << " g: " << (uint16_t)g << " b: " << (uint16_t)b << std::endl;
            if(r < 30 && g < 60 && b > 90) {
              pixel[j][2] = 0;
              pixel[j][1] = 255;
              pixel[j][0] = 0;
           }
        }
    }

    result = image;

    // -----------------------------------------------------------------------------
    // test 2 -> convert to HSV and manipulate the Hue
    /* cv::Mat hsv_image;
    cv::cvtColor(image, hsv_image, CV_BGR2HSV);

    // split into channels (in this case HSV)
    cv::Mat channel[3];
    cv::split(hsv_image, channel); 

    // now we have a single channel to work with
    int i,j;
    uchar* p;
    for( i = 0; i < channel[0].rows; ++i)
    {
        p = channel[0].ptr<uchar>(i);
        for ( j = 0; j < channel[0].cols; ++j)
        {
            //std::cout << "h: " << (uint16_t)p[j] << std::endl;
            if(p[j] > 100 && p[j] < 120) {
                p[j] = 255;
            }
        }
    }

    // rebuild
    cv::Mat tmp;
    cv::merge(channel, 3, tmp);
    cv::cvtColor(tmp, result, CV_HSV2BGR); */

    // -----------------------------------------------------------------------------
    // show
    cv::imwrite("tmp.jpg", result);

    cv::namedWindow("Bluebox", cv::WINDOW_AUTOSIZE);
    cv::imshow("Bluebox", result);

    cv::waitKey(0);
    return 0;
}
