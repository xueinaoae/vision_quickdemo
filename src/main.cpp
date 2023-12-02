#include<fmt/core.h>
#include<detectcolor.h>
#include<google_logger.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
using namespace cv;
using namespace std;

int main(int argc,char* argv[0]){
    vector<Mat> file;
    Mat frame,img;
    GLOG::configure::glogcreate("test");
    namedWindow("展示",WINDOW_AUTOSIZE);
    int filepath=0;
    string storagepath="/home/mayuqi/桌面/vision_quickdemo/video/video.avi";
    std::string color=detect::color::To_string(detect::color::ColorType::Green);
    VideoCapture cap(filepath);
    if (cap.isOpened()) {
    LOG(INFO)<<fmt::format("\n===============================================================\n"
                "project_name:{}\n""video_path:{}\n""color:{}\n" "storagepath\n"
                "==============================================================="
                ,"detector_color",
                filepath,
                color,
                storagepath
    );
    cap.read(frame);
    Filetrackle handlefile(storagepath,25,frame.type()==CV_8UC3,VideoWriter::fourcc('M', 'J', 'P', 'G'),file,frame.size());
    thread myjob(&Filetrackle::InFile,&handlefile);
    while (1)
    {
        cap.read(frame);
        if(frame.empty()){
            std::cout<<"读取失败"<<std::endl;
            LOG(INFO)<<"finshed";
            break;
        }
        img=detect::color::detect_color(frame,detect::color::ColorType::self_defined);
        imshow("self_defined",img);
        handlefile.mutex_a.lock();
        cout<<"读取一次成功"<<endl;
        handlefile.my_file.push_back(img);
        handlefile.mutex_a.unlock();
        waitKey(25);
       
        //循环十次输出一次日志;
        LOG_EVERY_N(INFO,10)<<fmt::format("成功检测到{}",color);
    }
    myjob.join();
    }else{
        LOG(ERROR)<<fmt::format("open   {}   is   failure",filepath);
    }
    
    
    return 0;
}

