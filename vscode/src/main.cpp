#include<iostream>
#include "/home/mayuqi/桌面/vscode/src/vision_demo/include/quickdemo.h"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
    Mat src = imread("/home/mayuqi/桌面/code/image/shouzhang.jpeg");
    Mat src2=imread("/home/mayuqi/桌面/code/image/2.png");
    Mat src3=imread("/home/mayuqi/桌面/code/image/1.JPG",IMREAD_GRAYSCALE);
    if (src.empty()||src2.empty()) {
        std::cout << "Not open file: " << "/home/mayuqi/公共的/1.JPG";
        return -1;
    }
    Mat img;
    // resize(src,src,Size(512,512));
    // qb.linecheck(src);
    // VideoCapture cap(0);
    VideoCapture cap("/home/mayuqi/桌面/code/video/hun.mp4");
    // VideoCapture cap(0);
    while(1){
        Mat frame;
        cap>>frame;
        // cap.read(frame);
        if(frame.empty()){
            cout<<"no"<<endl;
            break;
        }
        img=quick_demo::hun(frame);
        // img=qb.hun(frame);
        imshow("视频",img);
        waitKey(0);
    } 
    return 0; 
} 