/**
 * Canny Edge
 * brief sample code demonstrating usage of Canny Edge detector
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
static int min_threshold = 100;
static int max_threshold = 200;
cv::Mat image;

/// Function headers
void canny( int /*arg*/, void* );
void show_help(const std::string &message = "");

/**
 * function main
 */
int main( int argc, const char** argv )
{
    if(argc < 2)
    {
        show_help("Not enough parameters given.");
        return -1;
    }

    std::string image_file("");
    /// Iterate over the arguments passed through the command line
    for(int i = 1; i < argc; ++i)
    {
        std::string input_file(argv[i]);
        if(input_file.find_last_of(".jpg") != std::string::npos || input_file.find_last_of(".png") != std::string::npos)
        {
            image_file = input_file;
        }
        else
            show_help();
    }

    if(image_file.length() == 0)
    {
        show_help("No valid file format given.");
        return(-1);
    }

    /// Load the source image
    image = cv::imread(image_file);
    if(!image.data)
    {
        show_help("Image not valid.");
        return(-1);
    }

    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("canny", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("min", "canny", &min_threshold, 255, canny);
    cv::createTrackbar("max", "canny", &max_threshold, 255, canny);

    canny(0, 0);
    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}


/**
 * @function canny
 */
void canny( int /*arg*/, void* )
{
    cv::Mat canny;
    cv::Canny(image, canny, min_threshold, max_threshold);
    cv::imshow("canny", canny);
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
    std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
    std::cout << "Usage: cv_canny_d /path/to/image" << std::endl;
    #else
    std::cout << "Usage: cv_canny /path/to/image" << std::endl;
    #endif
    std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
