#include<detectcolor.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<vector>
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
    Mat detect_color(const Mat &image,const ColorType &color_type){
        //初始化变量
        Mat img_a ,img_b,img_c;
        Scalar color;
        image.copyTo(img_a);
        vector<vector<Point>> contours;
        cvtColor(image,img_b,COLOR_BGR2HSV);
        img_b.copyTo(img_c);
        //判断颜色并且提取轮廓
        if(color_type==ColorType::Blue){   
            inRange(img_b,Scalar(105,170,46),Scalar(112,255,255),img_b);
            Mat kernel, kernel_d;
            kernel=getStructuringElement(1,Size(3,15));
            kernel_d=getStructuringElement(1,Size(20,20));
            morphologyEx(img_b,img_b,0,kernel_d,Point(-1,-1),2);
            morphologyEx(img_b,img_b,1,kernel,Point(-1,-1),5);
            vector<Vec4i> value;
            findContours(img_b,contours,value,3,2,Point());
            color=Scalar(255,0,0);
        }
        if(color_type==ColorType::Green){ 
            inRange(img_c,Scalar(70,75,46),Scalar(85,255,255),img_c);
            Mat kernel_a,kernel_c;
            kernel_a=getStructuringElement(1,Size(3,20));
            kernel_c=getStructuringElement(1,Size(20,20));
            morphologyEx(img_c,img_c,0,kernel_c,Point(-1,-1),1);
            morphologyEx(img_c,img_c,1,kernel_a,Point(-1,-1),4);
            vector<Vec4i> value_a;
            findContours(img_c,contours,value_a,3,2,Point());
            color=Scalar(0,255,0);
        } 
            //绘制
        for(int i=0;i<contours.size();i++){
                double area;
                RotatedRect m_rect=minAreaRect(contours[i]);
                Point2f a_point[4];
                m_rect.points(a_point);
                area=contourArea(contours[i]);
                if (area>5000){
                    for(int j=0;j<4;j++){
                        if(j==3){
                            line(img_a,a_point[j],a_point[0],color,2,8);
                            break;
                        }
                        line(img_a,a_point[j],a_point[j+1],color,2,8);       
                    }
                }
            }
            return img_a;      
    }
}