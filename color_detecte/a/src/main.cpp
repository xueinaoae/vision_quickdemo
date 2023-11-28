#include<fmt/core.h>
#include<detectcolor.h>
#include<google_logger.h>
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main(int argc,char* argv[]){
    namedWindow("展示",WINDOW_AUTOSIZE);
    GLOG::configure::glogcreate  my_glog(argv[0]);
    std::string filepath="../video/hun.mp4";
    std::string color=detect::color::To_string(detect::color::ColorType::Green);
    VideoCapture cap(filepath);
    if(cap.isOpened()){
        LOG(INFO)<<fmt::format("\n===============================================================\n"
                    "project_name:{}\n""video_path:{}\n""color:{}\n" 
                    "==============================================================="
                    ,"detector_color",
                    filepath,
                    color  
        );
        while (1)
        {

            Mat frame,img;
            cap.read(frame);
            if(frame.empty()){
                std::cout<<"读取失败"<<std::endl;
                LOG(INFO)<<"finshed";
                break;
            }
            detect::color::ColorType type= detect::color::ColorType::Green;
            img=detect::color::detect_color(frame,type);
            imshow("展示",img);
            //循环十次输出一次日志;
            LOG_EVERY_N(INFO,10)<<fmt::format("成功检测到{}",color);
            waitKey(0);    
         }
    }
    else{
        LOG(ERROR)<<fmt::format("open   {}   is   failure",filepath);
    }
    return 0;
}

