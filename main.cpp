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
using namespace cv;
using namespace std;

// OpenCV command line parser functions 
// Keys accepted by command line parser 
const char* keys =
{
  "{help h usage ? | | print this message}"
   "{@image || Image to process}"
   "{@lightPattern || Image light pattern to apply to image input}"
   "{lightMethod | 1 | Method to remove background light, 0 difference, 1 div }"
   "{segMethod | 1 | Method to segment: 1 connected Components, 2 connected components with stats, 3 find Contours }"
};


int main(int argc, const char** argv) {
	
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

	imshow("window", img);
	waitKey(0);

	Mat img_noise;
	medianBlur(img, img_noise, 3);

	imshow("window", img_noise);
	waitKey(0);

	
	
	
	return 0;

}
