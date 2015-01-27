/**
 * Conversions
 * brief sample code demonstrating OpenCV conversion types
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Defines depending of OpenCV version installed (2.4.x or 3.x)
#ifdef OPENCV_OLD	/// 2.4.x version
const int GRAY_CONV = CV_BGR2GRAY;
const int HSV_CONV  = CV_BGR2HSV;
const int HLS_CONV  = CV_BGR2HLS;
const int LAB_CONV  = CV_BGR2Lab;
const int YUV_CONV  = CV_BGR2YUV;
#else				/// 3.x - github version
const int GRAY_CONV = cv::COLOR_BGR2GRAY;
const int HSV_CONV  = cv::COLOR_BGR2HSV;
const int HLS_CONV  = cv::COLOR_BGR2HLS;
const int LAB_CONV  = cv::COLOR_BGR2Lab;
const int YUV_CONV  = cv::COLOR_BGR2YUV;
#endif

/// Global Variables
int DELAY_CAPTION = 2000; /// 2 seconds
cv::Mat src, dst;
char window_name[] = "Conversions Demo";

/// Function headers
int display_caption( const char* caption );
int display_dst( int delay );
void show_help(const std::string &message = "");

/**
 * function main
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

	/// Create a window to display results
	cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE );

	if( display_caption( "Original Image" ) != 0 ) 
		return 0;

	dst = src.clone();
	if( display_dst( DELAY_CAPTION ) != 0 )
		return 0;
  
	/// Applying Grayscale conversion
	if( display_caption( "Gray Scale Image" ) != 0 )
		return 0;

	cv::cvtColor(src, dst, GRAY_CONV);
	if( display_dst( DELAY_CAPTION ) != 0 )
		return 0;

	/// Applying HSV conversion
	if( display_caption( "HSV Image" ) != 0 )
		return 0;

	cv::cvtColor(src, dst, HSV_CONV);
	if( display_dst( DELAY_CAPTION ) != 0 )
		return 0;

	/// Applying HLS conversion
	if( display_caption( "HLS Image" ) != 0 )
		return 0;

	cv::cvtColor(src, dst, HLS_CONV);
	if( display_dst( DELAY_CAPTION ) != 0 )
		return 0;

	/// Applying Lab conversion
	if( display_caption( "Lab Image" ) != 0 )
		return 0;

	cv::cvtColor(src, dst, LAB_CONV);
	if( display_dst( DELAY_CAPTION ) != 0 )
		return 0;

	/// Applying YUV conversion
	if( display_caption( "YUV Image" ) != 0 )
		return 0;

	cv::cvtColor(src, dst, YUV_CONV);
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
	std::cout << "Usage: cv_conversions_d /path/to/image" << std::endl; 
	#else
	std::cout << "Usage: cv_conversions /path/to/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
