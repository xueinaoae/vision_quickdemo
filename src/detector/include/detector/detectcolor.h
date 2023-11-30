#pragma onec
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;

namespace detect::color{
enum ColorType{
    Green,Blue,self_defined
};
std::string To_string(const ColorType &string_type);
Mat detect_color(const Mat &image,const ColorType &color_type);
Mat  bar_detectcolor(const Mat &image);
}
//namespace detect::color