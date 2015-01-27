/**
 * Template Matching
 * brief sample code demonstrating Template Matching using Histograms
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
cv::Mat image_full, image_template, result;
int match_method = 0;
int max_Trackbar = 5;
char image_window[] = "Source Image";
char template_window[] = "Template Image";
char result_window[] = "Result";

/// Function headers
void template_matching(int, void*);
void show_help(const std::string &message = "");

/**
 * function main
 */
int main(int argc, char **argv)
{
	if(argc < 3)
	{
		show_help("Not enough parameters given."); 
		return 0;
	}
	
	std::string image_file_full(argv[1]), image_file_templ(argv[2]);

	if(image_file_full.find_last_of(".jpg") == std::string::npos && image_file_full.find_last_of(".png") == std::string::npos)
	{
		show_help("No valid file format given for first argument.");
		return -1;
	}

	if(image_file_templ.find_last_of(".jpg") == std::string::npos && image_file_templ.find_last_of(".png") == std::string::npos)
	{
		show_help("No valid file format given for second argument.");
		return -1;
	}

	/// Load the full image
	image_full = cv::imread(image_file_full, 1 );
	if(!image_full.data)
	{
		show_help("Full image not valid.");
		return -1;
	}

	/// Load the template image
	image_template = cv::imread(image_file_templ, 1 );
	if(!image_template.data)
	{
		show_help("Template image not valid.");
		return -1;
	}

	/// Create a window to display images
	cv::namedWindow( image_window, cv::WINDOW_AUTOSIZE );
	cv::namedWindow( template_window, cv::WINDOW_AUTOSIZE );
	cv::namedWindow( result_window, cv::WINDOW_AUTOSIZE );

	/// Create Trackbar
	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	cv::createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, template_matching );

	/// Initialize function
	template_matching(0,0);

	cv::waitKey(0);

	return 0;
}

/**
 * @function template_matching
 */
void template_matching(int, void*)
{
	/// Source image to display
    cv::Mat img_display;
	image_full.copyTo( img_display );

    /// Create the result matrix
	int result_cols =  image_full.cols - image_template.cols + 1;
    int result_rows = image_full.rows - image_template.rows + 1;
	result.create( result_rows, result_cols, CV_32FC1 );
	
	/// Do the Matching and Normalize
    cv::matchTemplate( image_full, image_template, result, match_method );
    cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal = 0.0f; 
	double maxVal = 0.0f; 
	cv::Point minLoc; 
	cv::Point maxLoc;
    cv::Point matchLoc;

    cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc );

    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED )
		matchLoc = minLoc;
    else
		matchLoc = maxLoc;

    /// Show me what you got
    cv::rectangle( img_display, matchLoc, cv::Point( matchLoc.x + image_template.cols , matchLoc.y + image_template.rows ), cv::Scalar(0, 255, 0), 2, 8, 0 );
    cv::rectangle( result, matchLoc, cv::Point( matchLoc.x + image_template.cols , matchLoc.y + image_template.rows ), cv::Scalar(0, 255, 0), 2, 8, 0 );

    cv::imshow( template_window, image_template );
	cv::imshow( image_window, img_display );
    cv::imshow( result_window, result );
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
	std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
	std::cout << "Usage: cv_matching_d /path/to/full/image /path/to/template/image" << std::endl; 
	#else
	std::cout << "Usage: cv_matching /path/to/full/image /path/to/template/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}