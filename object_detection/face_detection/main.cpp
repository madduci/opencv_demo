/**
 * Face Detection
 * brief sample code demonstrating Face Detection using Haar features
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
std::string face_cascade_name = "test_data/haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
char window_name[] = "Face detection";

/// Function headers
void detectAndDisplay( cv::Mat &frame );
void show_help(const std::string &message = "");

/**
 * function main
 */
int main(int argc, char **argv)
{
    if(argc < 2)
	{
		show_help("Not enough parameters given."); 
		return 0;
	}
	
	std::string image_file(argv[1]);
	if(image_file.find_last_of(".jpg") == std::string::npos && image_file.find_last_of(".png") == std::string::npos)
	{
		show_help("No valid file format given for first argument.");
		return -1;
	}

    /// Load the image
	cv::Mat image = cv::imread(image_file, 1 );
	if(!image.data)
	{
		show_help("Input image not valid.");
		return -1;
	}

	/// Load the cascades
	if( !face_cascade.load( face_cascade_name ) ){ std::cout << "--(!)Error loading face cascade" << std::endl; return -1; };
    /// Apply the classifier to the frame
    detectAndDisplay(image);

	cv::waitKey(0);
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( cv::Mat &frame )
{
	std::cout << "Running the face detector..." << std::endl;

    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;

    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );

    /// Detect faces
	std::cout << "Detecting faces..." << std::endl;
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 10, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	for (auto face:faces)
	{
		cv::Point center( face.x + face.width/2, face.y + face.height/2 );
		cv::ellipse( frame, center, cv::Size( face.width/2, face.height/2 ), 0, 0, 360, cv::Scalar( 0, 255, 0 ), 4, 8, 0 );
	}
	/// Show what you got
    cv::imshow( window_name, frame );
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
	std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
	std::cout << "Usage: cv_face_detection_d /path/to/image" << std::endl; 
	#else
	std::cout << "Usage: cv_face_detection /path/to/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
