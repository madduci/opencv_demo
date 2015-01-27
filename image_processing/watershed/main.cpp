/**
 * Watershed
 * brief sample code demonstrating Watershed segmentation algorithm
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
cv::Mat src, dst;
char window_name[] = "Watershed Demo";
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
    src = cv::imread(image_file, 1);
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

    /// Performs the thresholding step
    cv::Mat img_binary, img_foreground, img_background;
    cv::threshold(src_gray, img_binary, 0, 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);

    /// Remove noise - image opening
    cv::Mat kernel = cv::Mat::ones(3,3,CV_8UC1);
    cv::morphologyEx(img_binary, img_binary, cv::MORPH_OPEN, kernel, cv::Point(-1,-1), 2);

    if( display_caption( "Open Morphology operator" ) != 0 )
        return 0;

    dst = img_binary.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Perform dilation to extract background
    cv::dilate(img_binary, img_background, kernel, cv::Point(-1,-1), 3);

    if( display_caption( "Background" ) != 0 )
        return 0;

    dst = img_background.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Finding foreground area
    #ifdef OPENCV_NEW
    cv::distanceTransform(img_binary, img_foreground, cv::DIST_L2, 5);
    #else
    cv::distanceTransform(img_binary, img_foreground, CV_DIST_L1, 5);
    #endif

    if( display_caption( "Distance transform" ) != 0 )
        return 0;

    dst = img_foreground.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Thresholding the foreground
    double min_val = 0.0, max_val = 0.0;
    cv::minMaxIdx(img_foreground, &min_val, &max_val); //find the max and min value in the image
    img_foreground.convertTo(img_foreground, CV_8UC1); //reconvert to unsigned int values
    cv::threshold(img_foreground, img_foreground, 0.7*max_val, 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);

    if( display_caption( "Foreground" ) != 0 )
        return 0;

    dst = img_foreground.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Perform Image subtraction to find unknown region
    cv::Mat unknown_region;
    cv::subtract(img_background, img_foreground, unknown_region);

    if( display_caption( "Unknown Region" ) != 0 )
        return 0;

    dst = unknown_region.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
        return 0;

    /// Marker labelling
    cv::Mat markers;
    int num_components = 0;

    #ifdef OPENCV_NEW
    num_components = cv::connectedComponents(img_foreground, markers);
    #else
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img_foreground, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0], num_components++ )
        cv::drawContours(markers, contours, idx, cv::Scalar::all(num_components+1), -1, 8, hierarchy, INT_MAX);
    #endif

    /// Add 1 to all labels so that sure foreground is not 0, but 1
    markers = markers+1;

    /// Now, mark the region of unknown with zero
    for(int i = 0; i < markers.rows; ++i)
        for(int j = 0; j < markers.cols; ++j)
            if(markers.at<unsigned int>(i,j) == 255)
                markers.at<unsigned int>(i,j) = 0;

    /// Run the Watershed algorithm
    cv::watershed(src, markers);

    /// Paint the Watershed image
    std::vector<cv::Vec3b> colorTab;
    for(int i = 0; i < num_components; ++i)
    {
        int b = cv::theRNG().uniform(0, 255);
        int g = cv::theRNG().uniform(0, 255);
        int r = cv::theRNG().uniform(0, 255);

        colorTab.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    cv::Mat wshed(markers.size(), CV_8UC3);

    for(int i = 0; i < markers.rows; ++i)
        for(int j = 0; j < markers.cols; ++j)
        {
            int index = markers.at<int>(i,j);
            if( index == -1 )
                wshed.at<cv::Vec3b>(i,j) = cv::Vec3b(255,255,255);
            else if( index <= 0 || index > num_components )
                wshed.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
            else
                wshed.at<cv::Vec3b>(i,j) = colorTab[index - 1];
        }

    if( display_caption( "Watershed result" ) != 0 )
        return 0;

    dst = wshed.clone();
    if( display_dst( 0 ) != 0 )
        return 0;

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
	std::cout << "Usage: cv_watershed_d /path/to/image" << std::endl; 
	#else
	std::cout << "Usage: cv_watershed /path/to/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
