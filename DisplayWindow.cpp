#include "DisplayWindow.h"
#include <iostream>
using namespace std;

DisplayWindow::DisplayWindow(string window_title, int cols, int rows) :
    window_title{ "all processes" },cols{2},rows{2}
{
    this->window_title = window_title;
    this->cols = cols;
    this->rows = rows;
    this->c_width = 1280;
    this->c_height = 720;

    namedWindow(window_title, WINDOW_AUTOSIZE);
    this->final_image = Mat(this->c_height, this->c_width, CV_8UC3);
    imshow(this->window_title, this->final_image);
}

void DisplayWindow::add_image(string title, Mat image)
{
    this->titles.push_back(title);
    this->images.push_back(image);

}

void DisplayWindow::show()
{
    // Clean our canvas
    this->final_image.setTo(Scalar(20, 20, 20));

    // width and height of cell. add 10 px of padding between images
    int single_image_width = (c_width / cols);
    int single_image_height = (c_height / rows);
    cout << (this->images.size() )<< endl;
    int max_images = (this->images.size() > cols * rows) ? cols * rows : this->images.size();
    int i = 0;
    vector<string>::iterator titles_it = this->titles.begin();

    for (vector<Mat>::iterator it = this->images.begin(); it != this->images.end(); ++it)
    {
        string title = *titles_it;
        int cell_x = (single_image_width) * ((i) % cols);
        int cell_y = (single_image_height)*floor((i) / (float)cols);
        cout << "this is Y "<<cell_y << endl;
        Rect mask(cell_x, cell_y, single_image_width, single_image_height);

        //For each cell draw an image if exists
        Mat cell(this->final_image, mask);
        // resize image to cell size
        Mat resized;
        double cell_aspect = (double)single_image_width / (double)single_image_height;
        Mat img = *it;
        double img_aspect = (double)img.cols / (double)img.rows;
        double f = (cell_aspect < img_aspect) ? (double)single_image_width / (double)img.cols : (double)single_image_height / (double)img.rows;
        resize(img, resized, Size(0, 0), f, f);
        if (resized.channels() == 1) {
            cvtColor(resized, resized, COLOR_GRAY2BGR);
        }

        // Assign the image
        Mat sub_cell(this->final_image, Rect(cell_x, cell_y, resized.cols, resized.rows));
        resized.copyTo(sub_cell);
        putText(cell, title.c_str(), Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, LINE_AA);
        i++;
        ++titles_it;
        if (i == max_images)
            break;
    }

    // show image
    imshow(this->window_title, this->final_image);
}