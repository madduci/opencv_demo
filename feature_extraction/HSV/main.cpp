#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdio.h>



using namespace std;
using namespace cv;


int HSV_Histogram(Mat src, int nbins) {

	// resize and convert input image if necessary
	if (src.cols==0){
		cout << src << "not exit\n";
		return -1;
	}
	

	// Convert origional source image to HSV version 
	cvtColor(src, src, CV_BGR2HSV);
	
	// print the size of source image
	std::cout << "Size of image: " << src.cols << " " << src.rows << "\n\n";
	
	//show HSV version source image
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);
	
	// Using the same number of bins for all 3 channels
	int histSize[] = { nbins};

	// define range of values of the 3 channels (Hue, Saturation, Value)
	float range[] = { 0,256 };           //Saturation and Value range is from 0 to 255
	float hrange[] = { 0, 180 };	     // range for Hue is from 0 to 179
	const float* s_ranges = { range };
	const float* h_ranges = { hrange };

	
	//separate the HSV image into three channels (HSV)
	vector<Mat> hsv_planes;
	split(src, hsv_planes);
	
	// Computing the histogram from all 3 channels
	int channels[] = { 0, 1 };
	bool uniform = true;
	bool accumulate = false;
	
	Mat h_hist, s_hist,v_hist;
	
	calcHist(&hsv_planes[0], 1, 0, Mat(), h_hist, 1, histSize, &h_ranges, uniform, accumulate);
	calcHist(&hsv_planes[1], 1, 0, Mat(), s_hist, 1, histSize, &s_ranges, uniform, accumulate);
	calcHist(&hsv_planes[2], 1, 0, Mat(), v_hist, 1, histSize, &s_ranges, uniform, accumulate);
	
	cout << endl << ">>> Channel H: ";	
	for (int k = 0; k < nbins; k++) cout << h_hist.at<float>(k) << " ";
	cout << endl << ">>> Channel S: ";	
	for (int k = 0; k < nbins; k++) cout << s_hist.at<float>(k) << " ";
	cout << endl << ">>> Channel V: ";
	for (int k = 0; k < nbins; k++) cout << v_hist.at<float>(k) << " ";
	cout << endl;
	
	waitKey();
	return 0;
	
}
int main( int argc, char** argv ){
   Mat src = imread(argv[1]);
   if (!src.data) {
		std::cout << "Please provide a source image\n";
		return -1;
	}
	
	int nbins= atoi(argv[2]);
	
	HSV_Histogram(src,nbins);
	return 0;
}
