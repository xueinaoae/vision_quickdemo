#pragma onec
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<mutex>
using namespace cv;
using namespace std;

namespace detect::color{
enum ColorType{
    Green,Blue,self_defined
};
std::string To_string(const ColorType &string_type);
Mat detect_color(const Mat &image,const ColorType &color_type);
Mat  bar_detectcolor(const Mat &image);
}
//namespace detect::color
class Filetrackle{
public:
    Filetrackle(const std::string Filename,double fps,bool iscolor,int code,const vector<Mat>File,Size size_a):filename(Filename),Fps(fps),Iscolor(iscolor),codes(code),my_file(File),size(size_a){};
    void InFile();
    vector<Mat> my_file;
    mutex mutex_a;
private:
    Size size;
    double Fps;
    int codes;
    bool Iscolor;
    std::string filename;
    
   
};
