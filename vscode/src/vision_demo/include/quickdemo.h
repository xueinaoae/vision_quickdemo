#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
namespace quick_demo{
    void colorspace_demo(Mat &image);
    void creation_demo(Mat &image);
    void pixel_demo(Mat &image);
    void operators_demo(Mat &image);
    void click_demo(Mat &image);
    void bar_demo(Mat &image);
    void create_rectangle(Mat &image);
    void channels_demo(Mat &image);
    // void mixChannels_demo(Mat &image);
    void videocapture();
    void computer_demo(Mat &image);
    void compareimage(Mat & image,Mat & image2);
    void imagethreshold(Mat &image,Mat &myimage);
    void LUTimage_demo(Mat &image);
    void createpyramid_demo(Mat &image);
    void mouserespone(Mat &image);
    void write_demo(Mat &image);
    Mat createhistogram(Mat& image);
    void comparehistdemo(Mat &image_1,Mat &image_2);
    void histogrammatch(Mat &image,Mat &image1);
    Mat imagebalance(Mat &image);
    void bianyuanjiance(Mat &image);
    void tuxiangjuanji(Mat &image);
    void contourscheck(Mat &image);
    void draw(Mat point,Mat &image);
    void linecheck(Mat &image);
    Mat bluecheck(Mat &image);
    Mat lvcheck(Mat &image);
    Mat hun(Mat &image);
}