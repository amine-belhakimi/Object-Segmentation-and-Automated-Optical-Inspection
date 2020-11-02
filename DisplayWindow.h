#ifndef DisplayWindow_H_
#define DisplayWindow_H_

#include <string>
#include <iostream>
using namespace std;

// OpenCV includes
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

class DisplayWindow {

public:

	DisplayWindow(string window_name, int cols,int rows);
	void add_image(string title, Mat img);
	void show();
private:
    int cols;
    int rows;
    int c_width;
    int c_height;
    vector<string> titles;
    vector<Mat> images;
    Mat final_image;
    string window_title;
};
#endif
