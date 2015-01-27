/**
 * ORB
 * brief sample code demonstrating ORB keypoint extraction and matching
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

/// Global Variables
const int DELAY_CAPTION = 2000; /// 2 seconds

cv::Mat image_full, image_template, dst;
char window_name[] = "ORB Demo";

/// Function headers
int display_caption( const char* caption );
int display_dst( int delay );
int orb_demo();
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

	/// Create a window to display results
	cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE );

	if( display_caption( "Full Image" ) != 0 ) 
		return -1;

	dst = image_full.clone();
	if( display_dst( DELAY_CAPTION ) != 0 )
		return -1;

	if( display_caption( "Template Image" ) != 0 ) 
		return -1;

	dst = image_template.clone();
	if( display_dst( DELAY_CAPTION ) != 0 )
		return -1;
  
	if( display_caption( "Computing ORB Matches" ) != 0 ) 
		return -1;

	orb_demo();
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
	dst = cv::Mat::zeros( image_full.size(), image_full.type() );
	cv::putText( dst, caption,
		cv::Point( image_full.cols/4, image_full.rows/2),
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
 * @function orb_demo
 */
int orb_demo()
{ 
	try
	{
		std::vector<cv::KeyPoint> templ_keypoints, full_keypoints;
		cv::Mat templ_descriptors, full_descriptors;
		std::vector<cv::DMatch> matches;

        /// Detection and Extraction
        #ifdef OPENCV_NEW
        cv::Ptr<cv::ORB> orb_detector = cv::ORB::create();
        #else
        cv::Ptr<cv::ORB> orb_detector = cv::ORB::create("ORB");
        #endif
		orb_detector->detect(image_full, full_keypoints);
		if(full_keypoints.empty())
		{
			std::cout << "No valid keypoints found for full image. Aborting." << std::endl;
			return -1;
		}

		orb_detector->detect(image_template, templ_keypoints);
		if(templ_keypoints.empty())
		{
			std::cout << "No valid keypoints found for template image. Aborting." << std::endl;
			return -1;
		}

		orb_detector->compute(image_full, full_keypoints, full_descriptors);
		orb_detector->compute(image_template, templ_keypoints, templ_descriptors);

		/// Matching
		std::cout << "Computing the match..." << std::endl;
		cv::BFMatcher matcher(cv::NORM_HAMMING);
		matcher.match(templ_descriptors, full_descriptors, matches);

		/// Quick calculation of max and min distances between keypoints
		double max_dist = 0; double min_dist = 1000;
		for( int i = 0; i < templ_descriptors.rows; ++i )
		{ 
			double dist = matches[i].distance;
			if( dist < min_dist ) min_dist = dist;
			if( dist > max_dist ) max_dist = dist;
		}
	
		std::vector< cv::DMatch > good_matches;
		std::vector<cv::Point2f> first;
		std::vector<cv::Point2f> second;

		for( int i = 0; i < templ_descriptors.rows; ++i )
		{ 
			if( matches[i].distance < max_dist/10.0 )
			{
				good_matches.push_back(matches[i]); 
				first.push_back( templ_keypoints[ matches[i].queryIdx ].pt );
				second.push_back( full_keypoints[ matches[i].trainIdx ].pt );
			}
		}

		/// Draw only "good" matches
		//cv::drawKeypoints(image_template, templ_keypoints, image_template);
		//cv::drawKeypoints(image_full, full_keypoints, image_full);
		cv::Mat img_matches;
		cv::drawMatches( image_template, templ_keypoints, image_full, full_keypoints,
			   good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
			   std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

		/// Show detected matches
		cv::imshow( window_name, img_matches );
		cv::waitKey(0);
		return 0;
	}
	catch(cv::Exception &ex)
	{
		std::cout << "Got exception: " << ex.what() << std::endl;
		return -1;
	}
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
	std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
	std::cout << "Usage: cv_orb_d /path/to/full/image /path/to/template/image" << std::endl; 
	#else
	std::cout << "Usage: cv_orb /path/to/full/image /path/to/template/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
