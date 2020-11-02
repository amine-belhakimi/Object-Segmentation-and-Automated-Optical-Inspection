#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include "DisplayWindow.h"

using namespace cv;
using namespace std;

shared_ptr<DisplayWindow> window;


static Scalar randomColor(RNG& rng)
{
	auto icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

Mat calculateLightPattern(Mat img)
{
	Mat pattern;
	// Basic and effective way to calculate the light pattern from one image
	blur(img, pattern, Size(img.cols / 3, img.cols / 3));
	cout << "wtf is that ?"<< img.cols << endl;
	return pattern;
}

Mat removeLight(Mat img, Mat pattern)
{
	Mat aux;
		// Require change our image to 32 float for division
		Mat img32, pattern32;
		img.convertTo(img32, CV_32F);
		pattern.convertTo(pattern32, CV_32F);
		// Divide the imabe by the pattern
		aux = 1 - (img32 / pattern32);
		// Convert 8 bits format
		aux.convertTo(aux, CV_8U, 255);
	//equalizeHist( aux, aux );
	return aux;
}

Mat ConnectedComponents(Mat img)
{
	// Use connected components to divide our possibles parts of images 
	Mat labels;
	auto num_objects = connectedComponents(img, labels);
	// Check the number of objects detected
	if (num_objects < 2) {
		cout << "No objects detected" << endl;
		return labels;
	}
	else {
		cout << "Number of objects detected: " << num_objects - 1 << endl;
	}
	// Create output image coloring the objects
	Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
	RNG rng(0xFFFFFFFF);
	for (auto i = 1; i < num_objects; i++) {
		Mat mask = labels == i;
		output.setTo(randomColor(rng), mask);
	}
	return output;
}


int main(int argc, const char** argv) {

	window = make_shared<DisplayWindow>("Main window", 2, 2);
	
	// Load image to process 
	String img_file = "data/test_noise.pgm";
	Mat img = imread(img_file, 0);
	if (img.data == NULL) {
		cout << "Error loading image " << img_file << endl;
		return 0;
	}
	else {
		cout << "super !";
	}


	Mat img_noise;
	medianBlur(img, img_noise, 3);

	// Load image to process
	String light_pattern_file = "data/light.pgm";
	Mat light_pattern = imread(light_pattern_file, 0);


	medianBlur(light_pattern, light_pattern, 3);

	Mat img_no_light;
	img_noise.copyTo(img_no_light);

	img_no_light = removeLight(img_noise, light_pattern);


	// Binarize image for segment
	Mat img_thr,img_thr_detect;
	threshold(img_no_light, img_thr, 30, 255, THRESH_BINARY);
	

	img_thr_detect=ConnectedComponents(img_thr);

	window->add_image("original", img);
	window->add_image("denoised", img_noise);
	window->add_image("segmented", img_thr);
	window->add_image("denoised", img_thr_detect);

	window->show();
	waitKey(0);
	
	
	return 0;

}
