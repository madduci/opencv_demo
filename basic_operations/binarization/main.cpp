/**
 * Binarization
 * brief sample code demonstrating OpenCV binarization methods on an input image
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

cv::Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

/// Function headers
void threshold_demo( int, void* );
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

	/// Convert the image to Gray
	cv::cvtColor( src, src_gray, cv::COLOR_RGB2GRAY );

	/// Create Trackbar to choose type of Threshold
	cv::createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, threshold_demo );

	cv::createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, threshold_demo );

	std::cout << "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted" << std::endl;

	/// Call the function to initialize
	threshold_demo( 0, 0 );
	/// Wait until user finishes program
	while(true)
	{
		int c;
		c = cv::waitKey( 20 );
		if( (char)c == 27 )    /// If ESC is pressed, then quit
			break;
	}
	cv::waitKey(0);

	return 0;
}

/**
 * @function Threshold_Demo
 */
void threshold_demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  cv::threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

  cv::imshow( window_name, dst );
  
  switch(threshold_type)
  {
	case 0: std::cout << "Selected: " << "Binary Threshold" << std::endl; break;
	case 1: std::cout << "Selected: " << "Binary Inverted Threshold" << std::endl; break;
	case 2: std::cout << "Selected: " << "Truncate Threshold" << std::endl; break;
	case 3: std::cout << "Selected: " << "To Zero Threshold" << std::endl; break;
	case 4: std::cout << "Selected: " << "To Zero Inverted Threshold" << std::endl; break;
	default: std::cout << "Invalid Threshold type" << std::endl;
  }
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
	std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
	std::cout << "Usage: cv_binarization_d /path/to/image" << std::endl; 
	#else
	std::cout << "Usage: cv_binarization /path/to/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}