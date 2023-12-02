#include<detectcolor.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<fmt/core.h>
#include<mutex>
using namespace cv;
using namespace std;


namespace detect::color{
    std::string To_string(const ColorType &string_tpye){
      switch (string_tpye){
        case ColorType::Green:{
            return "Green";
        }
        case ColorType::Blue:{
            return "Blue";
        }
        case ColorType::self_defined:{
            return "self_defined";
        }
      }
    }
    //绘制
    Mat draw_contours(const Mat &image,Scalar down,Scalar up){
        //  to hsv
        Mat img_a ,img_b,img_c;
        image.copyTo(img_a);
        vector<vector<Point>> contours;
        vector<Vec4i> value;
        cvtColor(img_a,img_b,COLOR_BGR2HSV);
        inRange(img_b,down,up,img_b);
        //trackle image
        Mat kernel=getStructuringElement(1,Size(3,15));
        Mat kernel_d=getStructuringElement(1,Size(20,20));
        morphologyEx(img_b,img_b,0,kernel_d,Point(-1,-1),2);
        morphologyEx(img_b,img_b,1,kernel,Point(-1,-1),5);
        //handel contours
        findContours(img_b,contours,value,3,2,Point());
        for(int i = 0;i < contours.size(); i++){
            RotatedRect m_rect=minAreaRect(contours[i]);
            Point2f a_point[4];
            m_rect.points(a_point);
            double area=contourArea(contours[i]);
            if (area>5000) {
                for (int  j=0;j<4;j++) {
                    if (j==3) {
                      line(image,a_point[j],a_point[0],Scalar(255,255,255),2,8);
                      break;
                    }
                    line(image,a_point[j],a_point[j+1],Scalar(255,255,255),2,8);       
                }
            }
        }
        return image;
    }
    Mat detect_color(const Mat &image,const ColorType &color_type){
        Mat back_img;
        //select color and handle
        if (color_type==ColorType::Blue) {   
            Scalar down=Scalar(105,170,46);
            Scalar up=Scalar(112,255,255);
            back_img=draw_contours(image,down,up);
            imshow("blue",back_img);      
        }else if (color_type==ColorType::Green) { 
            Scalar down=Scalar(70,75,46);
            Scalar up=Scalar(85,255,255);  
            back_img=draw_contours(image,down,up);
            imshow("green",back_img);
        }else if (color_type==ColorType::self_defined){
            back_img=bar_detectcolor(image);
            imshow("self_defined",back_img);
        }
        return back_img;
    }

    static int hue,fullity,value,range_hue,range_fullity,range_value;
    static Scalar hsv_lower=Scalar(hue,fullity,value);
    static Scalar hsv_up=Scalar(hue+range_hue,fullity+range_fullity,value+range_value);
    static  void Change_value(int number_v,void*){
        hsv_lower=Scalar(hue,fullity,number_v);  
    }
    static  void Change_fullity(int number_f,void*){
        hsv_lower=Scalar(hue,number_f,value);  
    }
    static void Change_hue(int number_h,void* userdata){    
        hsv_lower=Scalar(number_h,fullity,value);               
    }
    static void Change_range_hue(int number_a,void*){
      
        hsv_up=Scalar(hue+number_a,fullity+range_fullity,value+range_value);
    }
    static void Change_range_fullity(int number_b,void*){
       
        hsv_up=Scalar(hue+range_hue,fullity+number_b,value+range_value);
    }
    static void Change_range_value(int number_c,void*){ 
        hsv_up=Scalar(hue+range_hue,fullity+range_fullity,value+number_c);
    }
    Mat bar_detectcolor(const Mat &image){
        Mat back_img;
        namedWindow("self_defined",WINDOW_AUTOSIZE);
        //create bar
        createTrackbar("hue","self_defined",&hue,255-range_hue,Change_hue);
        createTrackbar("fullity","self_defined",&fullity,255-range_fullity,Change_fullity);
        createTrackbar("range_hue","self_defined",&range_hue,255,Change_range_hue);
        createTrackbar("range_fullity","self_defined",&range_fullity,255,Change_range_fullity);
        createTrackbar("range_value","self_defined",&range_value,255,Change_range_value);
        //handle image
        return draw_contours(image,hsv_lower,hsv_up);
    }

}//namespace detect::color
void Filetrackle::InFile(){
        VideoWriter writer(filename,codes,Fps,size,Iscolor);
        while(1){
            if(!my_file.empty()){
                mutex_a.lock();
                writer.write(my_file.front());
	            my_file.erase(my_file.begin());
                cout<<"存储一次成功"<<endl;
                mutex_a.unlock();
            }else{
                cout<<"正在读取中"<<endl;
            }
        };
    
}