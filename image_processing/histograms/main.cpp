/**
 * Histograms
 * brief sample code demonstrating usage of Histograms 
 * author Michele Adduci <adducimi@informatik.hu-berlin.de>
 * based on OpenCV Tutorials
 */

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
static int brightness = 100;
static int contrast = 100;
cv::Mat image;

/// Function headers
void updateBrightnessContrast( int /*arg*/, void* );
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

    cv::namedWindow("image", 0);
    cv::namedWindow("histogram", 0);

    cv::createTrackbar("brightness", "image", &brightness, 200, updateBrightnessContrast);
    cv::createTrackbar("contrast", "image", &contrast, 200, updateBrightnessContrast);

    updateBrightnessContrast(0, 0);
    cv::waitKey();

    return 0;
}


/**
 * @function updateBrightnessContrast
 */
void updateBrightnessContrast( int /*arg*/, void* )
{
    int histSize = 64;
    int _brightness = brightness - 100;
    int _contrast = contrast - 100;

    /*
     * The algorithm is by Werner D. Streidt
     * (http://visca.com/ffactory/archives/5-99/msg00021.html)
     */
    double a, b;
    if( _contrast > 0 )
    {
        double delta = 127.*_contrast/100;
        a = 255./(255. - delta*2);
        b = a*(_brightness - delta);
    }
    else
    {
        double delta = -128.*_contrast/100;
        a = (256.-delta*2)/255.;
        b = a*_brightness + delta;
    }

    cv::Mat gray, dst, hist;
	if(image.channels() > 1)
	{
		#ifdef OPENCV_NEW
		cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		#else
		cv::cvtColor(image, gray, CV_BGR2GRAY);
		#endif
		gray.convertTo(dst, CV_8U, a, b);
	}
	else
		image.convertTo(dst, CV_8U, a, b);	
    
    cv::imshow("image", dst);
	/// Compute histograms
    cv::calcHist(&dst, 1, 0, cv::Mat(), hist, 1, &histSize, 0);
	/// Init the target image with white color
    cv::Mat histImage = cv::Mat(200, 320, CV_8U, cv::Scalar::all(255));
	/// Normalize the histograms to be as big as histImage rows
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, CV_32F);
	/// Approximate the values to next integer
    int binW = cvRound((double)histImage.cols/histSize);
	/// Draw the histogram as a series of rectangles
    for( int i = 0; i < histSize; ++i )
        cv::rectangle( histImage, cv::Point(i*binW, histImage.rows),
                   cv::Point((i+1)*binW, histImage.rows - cvRound(hist.at<float>(i))),
                   cv::Scalar::all(0), -1, 8, 0 );
    cv::imshow("histogram", histImage);
}

/**
 * @function show_help
 */
void show_help(const std::string &message)
{
	std::cout << "Error: " << message << std::endl << std::endl;
    #ifdef DEBUG_MODE
	std::cout << "Usage: cv_histograms_d /path/to/image" << std::endl; 
	#else
	std::cout << "Usage: cv_histograms /path/to/image" << std::endl; 
	#endif
	std::cout << "Extensions supported: *.jpg, *.png" << std::endl;
}
