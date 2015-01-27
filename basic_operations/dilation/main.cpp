/**
 * Dilation
 * brief sample code demonstrating Dilation operation
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global variables
cv::Mat src, dilation_dst;

int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

/** Function Headers */
void erosion_demo( int, void* );
void dilation_demo( int, void* );
void show_help(const std::string &message = "");

/**
 * @function main
 */
int main(int argc, char **argv)
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

    /// Create windows
    cv::namedWindow( "Dilation Demo", cv::WINDOW_AUTOSIZE );

    /// Create Dilation Trackbar
    cv::createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
          &dilation_elem, max_elem,
		  dilation_demo );

    cv::createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
          &dilation_size, max_kernel_size,
          dilation_demo );

    /// Default start
    dilation_demo( 0, 0 );

    cv::waitKey(0);
    return 0;
}

/**
 * @function dilation_demo
 */
void dilation_demo( int, void* )
{
    int dilation_type = 0;
    switch(dilation_type)
	{
		case 0: dilation_type = cv::MORPH_RECT;    break;
		case 1: dilation_type = cv::MORPH_CROSS;   break;
		case 2: dilation_type = cv::MORPH_ELLIPSE; break;
		default: dilation_type = cv::MORPH_RECT;
	}

    cv::Mat element = cv::getStructuringElement( dilation_type,
                       cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       cv::Point( dilation_size, dilation_size ) );

    /// Apply the dilation operation
    cv::dilate( src, dilation_dst, element );
    cv::imshow( "Dilation Demo", dilation_dst );
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
	std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
	std::cout << "Usage: cv_dilation_d /path/to/image" << std::endl; 
	#else
	std::cout << "Usage: cv_dilation /path/to/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}