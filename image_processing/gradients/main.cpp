/**
 * Gradients
 * brief sample code demonstrating the computation of image gradients
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
cv::Mat src, dst;
char window_name[] = "Gradients Demo";
int DELAY_CAPTION = 2000; /// 2 seconds

/// Function headers
int display_caption( const char* caption );
int display_dst( int delay );
void show_help(const std::string &message = "");

/**
 * @function main
 */
int main( int argc, char** argv )
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
    src = cv::imread(image_file, 1 );
    if(!src.data)
    {
        show_help("Image not valid.");
        return(-1);
    }

    /// Create a window to display results
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE );

    if( display_caption( "Original Image" ) != 0 )
        return 0;

    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Performs grayscale conversion
    cv::Mat src_gray;
    #ifdef OPENCV_NEW
    cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
    #else
    cv::cvtColor(src, src_gray, CV_BGR2GRAY);
    #endif

    /// Performs Sobel gradient on X axis
    if( display_caption( "Sobel Gradient X" ) != 0 )
        return 0;
    cv::Sobel(src_gray, dst, CV_64F, 1, 0, 5);

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Performs Sobel gradient on Y axis
    if( display_caption( "Sobel Gradient Y" ) != 0 )
        return 0;
    cv::Sobel(src_gray, dst, CV_64F, 0, 1, 5);

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Performs Scharr gradient on X axis
    if( display_caption( "Scharr Gradient X" ) != 0 )
        return 0;
    cv::Scharr(src_gray, dst, CV_64F, 1, 0, 5);

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Performs Scharr gradient on Y axis
    if( display_caption( "Scharr Gradient Y" ) != 0 )
        return 0;
    cv::Scharr(src_gray, dst, CV_64F, 0, 1, 5);

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Performs Laplacian gradient
    if( display_caption( "Laplacian Gradient" ) != 0 )
        return 0;
    cv::Laplacian(src_gray, dst, CV_64F);

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Performs Sobel X+Y
    cv::Mat sobel_x, sobel_y;
    if( display_caption( "Sobel X+Y" ) != 0 )
        return 0;
    cv::Sobel(src_gray, sobel_x, CV_64F, 1, 0, 5);
    cv::Sobel(src_gray, sobel_y, CV_64F, 0, 1, 5);
    cv::bitwise_and(sobel_x, sobel_y, dst);

    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Wait until user press a key
    display_caption( "End: Press a key!" );
    cv::waitKey(0);

    return 0;
}

/**
 * @function display_caption
 */
int display_caption( const char* caption )
{
    dst = cv::Mat::zeros( src.size(), src.type() );
    cv::putText( dst, caption,
        cv::Point( src.cols/4, src.rows/2),
        cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255) );

    cv::imshow( window_name, dst );
    int c = cv::waitKey( DELAY_CAPTION );
    if( c >= 0 ) { return -1; }
    return 0;
}

/**
 * @function display_dst
 */
int display_dst( int delay )
{
    cv::imshow( window_name, dst );
    int c = cv::waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
    std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
    std::cout << "Usage: cv_gradients_d /path/to/image" << std::endl;
    #else
    std::cout << "Usage: cv_gradients /path/to/image" << std::endl;
    #endif
    std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
