#include<fmt/core.h>
#include<detectcolor.h>
#include "glog/logging.h"
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
using namespace quick_demo;
int main(int argc,char **argv){
    google::InitGoogleLogging("detectcolor");  
    FLAGS_logtostderr=false;
    FLAGS_alsologtostderr=true;
    FLAGS_colorlogtostderr=true;
    google::SetLogDestination(google::GLOG_FATAL, "../src/log/FATAL");
    google::SetLogDestination(google::GLOG_ERROR, "../src/log/ERROR_"); 
    google::SetLogDestination(google::GLOG_WARNING, "../src/log/WARING_"); 
    google::SetLogDestination(google::GLOG_INFO, "../src/log/INFO_"); 
    VideoCapture cap("../video/hun.mp4");
    // VideoCapture cap(0);
    LOG(INFO) <<"项目名称"<<"detectcolor"<<"    "<< "detectcolor:" << "blue and green"<<"    "<<"视频路径"<<"../a/video/hun.mp4 ";
    fmt::print("视频路径{},检测颜色{}","../video/hun.mp4","BLUE AND GRNEE");
    while(1){
        Mat frame,img;
        cap>>frame;
        if(frame.empty()){
            cout<<"no"<<endl;
            break;
        }                 
        img=quick_demo::detect_color(frame);  
        LOG(INFO)<<"检测成功";
        imshow("detect",img);
        waitKey(0);
    }
    google::ShutdownGoogleLogging();
    
    return 0;
}

