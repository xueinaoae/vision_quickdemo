#include<detectcolor.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<fmt/core.h>
using namespace cv;
using namespace std;


namespace detect::color{
    std::string To_string(const ColorType &string_tpye){
        switch (string_tpye)
        {
        case ColorType::Green:{
            return "Green";

        }
        
        case ColorType::Blue:{

            return "Blue";
        }
        }

    }
    //绘制
    Mat draw_contours(const Mat &image,Scalar &down,Scalar &up){
        Mat img_a ,img_b,img_c;
        image.copyTo(img_a);
        vector<vector<Point>> contours;
          vector<Vec4i> value;
        cvtColor(image,img_b,COLOR_BGR2HSV);
        inRange(img_b,down,up,img_b);
        Mat kernel, kernel_d;
        kernel=getStructuringElement(1,Size(3,15));
        kernel_d=getStructuringElement(1,Size(20,20));
        morphologyEx(img_b,img_b,0,kernel_d,Point(-1,-1),2);
        morphologyEx(img_b,img_b,1,kernel,Point(-1,-1),5);
        findContours(img_b,contours,value,3,2,Point());
        for(int i=0;i<contours.size();i++){
            double area;
            RotatedRect m_rect=minAreaRect(contours[i]);
            Point2f a_point[4];
            m_rect.points(a_point);
            area=contourArea(contours[i]);
            if (area>5000){
                for(int j=0;j<4;j++){
                    if(j==3){
                        line(img_a,a_point[j],a_point[0],Scalar(255,255,255),2,8);
                        break;
                    }
                    line(img_a,a_point[j],a_point[j+1],Scalar(255,255,255),2,8);       
                }
            }
        }
        return img_a;
    }
    Mat detect_color(const Mat &image,const ColorType &color_type){
        Scalar down,up;
        Mat back_img;
        if(color_type==ColorType::Blue){   
            down=Scalar(105,170,46);
            up=Scalar(112,255,255);
            back_img=draw_contours(image,down,up);
        }
        if(color_type==ColorType::Green){ 
            down=Scalar(70,75,46);
            up=Scalar(85,255,255);
            back_img=draw_contours(image,down,up);
        }
        return back_img;
    }
    int hue,fullity,value,range_hue,range_fullity,range_value;
    // Scalar hsv_up,hsv_lower;
    Scalar hsv_lower=Scalar(hue,fullity,value);
    Scalar hsv_up=Scalar(hue+range_hue,fullity+range_fullity,value+range_value);
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
    void bar_detectcolor(Mat &image){
        Mat back_img;
        namedWindow("show_b",WINDOW_AUTOSIZE);
        createTrackbar("hue","show_b",&hue,255-range_hue,Change_hue);
        createTrackbar("fullity","show_b",&fullity,255-range_fullity,Change_fullity);
        createTrackbar("range_hue","show_b",&range_hue,255,Change_range_hue);
        createTrackbar("range_fullity","show_b",&range_fullity,255,Change_range_fullity);
        createTrackbar("range_value","show_b",&range_value,255,Change_range_value);
        back_img=draw_contours(image,hsv_lower,hsv_up);
        imshow("show_b",back_img);
    }

}