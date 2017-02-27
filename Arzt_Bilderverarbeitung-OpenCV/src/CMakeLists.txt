cmake_minimum_required(VERSION 3.3)

# installed with brew on Mac OS X
include_directories("/usr/local/opt/opencv3/include")
link_directories("/usr/local/opt/opencv3/lib")

project(Bildverarbeitung-OpenCV)

set(OPENCVLIBS opencv_core opencv_imgcodecs opencv_imgproc opencv_highgui opencv_video opencv_videoio)

add_executable(readimg readimg.cpp)
target_link_libraries(readimg ${OPENCVLIBS})

add_executable(channels channels.cpp)
target_link_libraries(channels ${OPENCVLIBS})

add_executable(colormodel colormodel.cpp)
target_link_libraries(colormodel ${OPENCVLIBS})

add_executable(brighten brighten.cpp)
target_link_libraries(brighten ${OPENCVLIBS})

add_executable(sobel sobel.cpp)
target_link_libraries(sobel ${OPENCVLIBS})

add_executable(histograms histograms.cpp)
target_link_libraries(histograms ${OPENCVLIBS})

add_executable(bluebox bluebox.cpp)
target_link_libraries(bluebox ${OPENCVLIBS})

add_executable(video video.cpp)
target_link_libraries(video ${OPENCVLIBS})

add_executable(video_sobel video_sobel.cpp)
target_link_libraries(video_sobel ${OPENCVLIBS})

add_executable(video_diff video_diff.cpp)
target_link_libraries(video_diff ${OPENCVLIBS})
