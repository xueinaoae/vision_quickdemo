#include<detectcolor.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace quick_demo{
    Mat detect_color(Mat &image){
        //检测蓝色物品并绘制
        Mat img_a ,img_b,img_c;
        image.copyTo(img_a);
        cvtColor(image,img_b,COLOR_BGR2HSV);
        img_b.copyTo(img_c);
        inRange(img_b,Scalar(105,170,46),Scalar(112,255,255),img_b);
        Mat kernel, kernel_d;
        kernel=getStructuringElement(1,Size(3,15));
        kernel_d=getStructuringElement(1,Size(20,20));
        morphologyEx(img_b,img_b,0,kernel_d,Point(-1,-1),2);
        morphologyEx(img_b,img_b,1,kernel,Point(-1,-1),5);
        vector<vector<Point>> contours;
        vector<Vec4i> value;
        findContours(img_b,contours,value,3,2,Point());
        for(int i=0;i<contours.size();i++){
            RotatedRect m_rect=minAreaRect(contours[i]);
            Point2f a_point[4];
            m_rect.points(a_point);
            for(int j=0;j<4;j++){
                if(j==3){

                    line(img_a,a_point[j],a_point[0],Scalar(255,0,0),2,8);
                    break;
                }
                line(img_a,a_point[j],a_point[j+1],Scalar(255,0,0),2,8);       
        }
        //检测绿色物品并绘制
        inRange(img_c,Scalar(70,75,46),Scalar(85,255,255),img_c);
        Mat kernel_a,kernel_c;
        kernel_a=getStructuringElement(1,Size(3,20));
        kernel_c=getStructuringElement(1,Size(20,20));
        morphologyEx(img_c,img_c,0,kernel_c,Point(-1,-1),1);
        morphologyEx(img_c,img_c,1,kernel_a,Point(-1,-1),4);
        vector<vector<Point>> contours_a;
        vector<Vec4i> value_a;
        findContours(img_c,contours_a,value_a,3,2,Point());
        for(int i=0;i<contours_a.size();i++){
            RotatedRect b_rect=minAreaRect(contours_a[i]);
            Point2f b_point[4];
            b_rect.points(b_point);
            for(int j=0;j<4;j++){
                if(j==3){
                    line(img_a,b_point[j],b_point[0],Scalar(0,255,0),2,8);
                    break;
                }
                line(img_a,b_point[j],b_point[j+1],Scalar(0,255,0),2,8);       
             }
        return img_a;
    
        }
        }
    }
}