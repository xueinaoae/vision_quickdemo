#include "/home/mayuqi/桌面/vscode/src/vision_demo/include/quickdemo.h"
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

namespace quick_demo
{
void colorspace_demo(Mat &image)
{
    Mat gray,hsv;
    cvtColor(image,hsv,COLOR_BGR2HSV);
    cvtColor(image,gray,COLOR_BGR2GRAY);
    imshow("灰度",gray);
    imshow("HSV",hsv);
}
void creation_demo(Mat &image){
    Mat m1,m2,m3;
    //克隆
    m1=image.clone();
    //复制
    image.copyTo(m2);
    //赋值
    m3=image;
    //创建空白图像
    Mat m4;
    m4=Mat::zeros(Size(256,256),CV_8UC3);
    m4=Scalar(0,0,255);
    cout<<m4.rows<<m4.cols<<m4.channels()<<endl;
    cout<<m4<<endl;
    //克隆或者复制可以理解为深拷贝，重新创建一个内存地址，赋值只是指向同一个内存地址
    Mat m5;
    m4.copyTo(m5);
    m5=Scalar(0,255,0);
    imshow("m5",m5);
    imshow("m4",m4);
}
void pixel_demo(Mat&image){ 
    int w=image.cols;
    int h=image.rows;
    int dims=image.channels();
    for(int row=0;row<h;row++){
        for(int col=0;col<w;col++){
            if(dims==3){
                Vec3b bgr=image.at<uchar>(row,col);    
                image.at<Vec3b>(row,col)[0]=255-bgr[0]; 
                image.at<Vec3b>(row,col)[1]=255-bgr[1]; 
                image.at<Vec3b>(row,col)[2]=255-bgr[2]; 
            }                         
            }
        }
    imshow("输出",image); 
} 
void operators_demo(Mat &image){
    Mat m1;
    //加减乘除都可以，重载运算符
    m1=image+Scalar(100,100,100);
    imshow("m1",m1);
    //两个图像进行相加
    Mat m2=Mat::zeros(image.size(),image.type());
    m2=Scalar(2,2,2);
    Mat dst;
    //乘法 其他重载运算符使用类似
    multiply(m2,image,dst);
    imshow("dst",dst);
     int w=image.cols;
    int h=image.rows;
    int dims=image.channels();
    //add函数的本质,其他函数类似
    //subtract减法   divide除法  multiply乘法
    for(int row=0;row<h;row++){
        for(int col=0;col<w;col++){
            Vec3b p1=image.at<Vec3b>(row,col);
            Vec3b p2=m2.at<Vec3b>(row,col);
//saturate_cast,控制范围，防止溢出
            dst.at<Vec3b>(row,col)[0]=saturate_cast<uchar>(p1[0]+p2[0]);
            dst.at<Vec3b>(row,col)[1]=saturate_cast<uchar>(p1[1]+p2[1]);
            dst.at<Vec3b>(row,col)[2]=saturate_cast<uchar>(p1[2]+p2[2]);
        }
    }
}
static void back_assist(int lights,void* userdata){
    //解出userdata中的数据
    Mat image = *((Mat*)(userdata));
    //进行亮度调整
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
    dst=Scalar(lights,lights,lights);
    multiply(image,dst,m);
    imshow("1",m);

}
void bar_demo(Mat &image){
    int lights=50;
    namedWindow("调整窗口",WINDOW_AUTOSIZE);
    createTrackbar("调整亮度","调整窗口", &lights,100,back_assist,(void*)(&image));

}
void click_demo(Mat &image){  
    Mat dst=Mat::zeros(image.size(),image.type());
    while(true){
     

        int c=waitKey(100);
        if(c==27){
            cout<<"结束"<<endl;
            break;
        }
        else if(c==49){// 1  亮度加五十
            cout<<"亮度调整"<<endl;
            dst=Scalar(50,50,50);
            multiply(image,dst,dst);
        }
        else if(c==50){// 2 转换为灰度图
            cout<<"转化为灰度图"<<endl;
            cvtColor(image,dst,COLOR_BGR2GRAY);
        }
        imshow("1",dst);
    }
}
void create_rectangle(Mat &image){
    
    Mat dst=Mat::zeros(Size(256,256),CV_8UC3); 
    Mat dst2=Mat::zeros(Size(256,256),CV_8UC3); 
    //绘制矩形  两种方法  第一种是两个对角点   另一个是左上角的点和矩形长宽
    rectangle(dst,Point(1,1),Point(50,50),Scalar(255,0,0),-1,LINE_8,0);
    rectangle(dst2,Rect(20,20,50,50),Scalar(0,255,0),-1,LINE_8,0);
    imshow("1",dst);
    imshow("2",dst2);
    Mat dst3;
    //与 或 非 异或
    //运算的方法自己查
    bitwise_and(dst,dst2,dst3);
    // bitwise_or(dst,dst2,dst3);
    // bitwise_not(dst,dst3);
    // bitwise_xor(dst,dst2,dst3);
    imshow("3",dst3);
}
void channels_demo(Mat &image){
    //用vector容器是可以的，同时用数组也是可以的
    //分离通道
    vector<Mat> arr1;
    split(image,arr1);
    imshow("单1",arr1[0]);
    imshow("单2",arr1[1]);
    imshow("单3",arr1[2]);
    //融合
    Mat dst;
    merge(arr1,dst);
    imshow("融合",dst);
}
void videocapture(){
    VideoCapture video(0);
    Mat frame;
    while(1){
        video>>frame;
        if(frame.empty()){
            cout<<"失败"<<endl;
            break;
        }
        imshow("1",frame);
        int c=waitKey(0);
        if(c==49){
            cout<<"结束"<<endl;
            break;
        }
    }   
}
void computer_demo(Mat &image){
    float a[12]={1,2,3,4,5,6,12,11,10,10,2,1};
    //求最大值 最小值 位置 平均值   标准差
    Mat i1=Mat(3,4,CV_32FC1,a);
    double valmax,valmin;
    Point addr1,addr2;
    Scalar val1;
    // 求最大值 最小值 位置传入的必须是单通道的矩阵数据
    minMaxLoc(i1,&valmin,&valmax,&addr1,&addr2);
    //用mean求平均值可以是多通道
    val1= mean(i1);
    cout<<"最大值"<<valmax<<"最小值"<<valmin<<addr1<<addr2<<val1<<endl;
    //用meanstddev求平均值标准差可以是多通道
    Mat mymean ,mystddv;
    Mat i2=Mat{2,3,CV_32FC2,a};
    meanStdDev(i2,mymean,mystddv);
    cout<<mymean<<mystddv<<endl;
    //求最大值....多通道需要转换为单通道
    Mat i2_re=i2.reshape(1,4);
    minMaxLoc(i2_re,&valmin,&valmax,&addr1,&addr2);
    cout<<"最大值"<<valmax<<"最小值"<<valmin<<addr1<<addr2<<endl;

}
void compareimage(Mat & image,Mat & image2){
    //对两个单通道进行比较
    float a[12]={1,2,3,4,0,6,12,11,10,10,2,1};
    float b[12]={1,2,10,4,5,6,12,11,5,10,2,1};
    Mat imga,imgb,img1,img2;
    imga=Mat(3,4,CV_32FC1,a);
    imgb=Mat(3,4,CV_32FC1,b);
    max(imga,imgb,img1);
    min(imga,imgb,img2);
    imshow("max",img1);
    imshow("min",img2);
//对多通道进行比较
    Mat imgas,imgbs,img3,img4;
    imgas=Mat(2,3,CV_32FC2,a);
    imgbs=Mat(2,3,CV_32FC2,b);
    max(imgas,imgbs,img1);
    min(imgas,imgbs,img2);
    // 对两个彩色图进行比较
    //////
    //这边用resize需要进行图像尺寸的转换
    //////
    Mat myimage1,myimage2;
    resize(image,image,Size(512,512),0,0,INTER_AREA);//插值方法,缩小图像一般用INTER_AREA,放大图像一般用INTER_CUBIC
    resize(image2,image2,Size(512,512),0,0,INTER_AREA);
    max(image,image2,myimage1);
    min(image,image2,myimage2);
    imshow("对比1",myimage1);
    imshow("对比2",myimage2);
    //与掩摸进行比较
    //生成掩摸(掩摸的大小需要和比对的对象大小一样)
    Mat src1=Mat::zeros(image2.size(),CV_8UC3),src2;
    Rect rect(100,100,300,300);
    src1(rect)=Scalar(255,255,255);
    imshow("遮罩",src1);
    min(image2,src1,src2);
    imshow("遮罩2",src2);
    //与红色通道的淹摸进行比较
    Mat redsrc=Mat(image2.size(),CV_8UC3,Scalar(0,0,255));
    Mat src3;
    max(image2,redsrc,src3);
    imshow("遮罩2",src3);  
}
void imagethreshold(Mat &image ,Mat &myimage){
    Mat src1,src2,src3,src4,src6,src5;
    threshold(image,src1,125,255,THRESH_BINARY);
    threshold(image,src2,125,255,THRESH_BINARY_INV);
    threshold(image,src3,125,255,THRESH_TRUNC);
    threshold(image,src4,125,255,THRESH_TOZERO);
    imshow("1",src1);
    imshow("2",src2);
    imshow("3",src3);
    imshow("4",src4);
    //自适应二值化,传入的图像，必须是CV_8UC1,有分布均值法和高斯法
    adaptiveThreshold(myimage,src6,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,55,0);
    imshow("adapt",src6);
}
void LUTimage_demo(Mat &image){
    uchar lutfirst[256];
    for(int i=0;i<256;i++){
        if(i<=100){
            lutfirst[i]=0;
        }
        else if(i>100 && i<=200){
            lutfirst[i]=1;
        }
        else{
            lutfirst[i]=255;
        }
    }
    Mat Firstlut=Mat(1,256,CV_8UC1,lutfirst);
    uchar lutsecond[256];
    for(int i=0;i<256;i++){
        if(i<=100){
            lutfirst[i]=0;
        }
        else if(i>100 && i<=150){
            lutfirst[i]=100;
        }
        else if(i>150 && i<=200){
            lutfirst[i]=150;
        }
        else{
            lutfirst[i]=255;
        }
    }
    Mat Secondlut=Mat(1,256,CV_8UC1,lutsecond);
    char lutthird[256];
    for(int i=0;i<256;i++){
        if(i<=100){
            lutfirst[i]=100;
        }
        else if(i>100 && i<=200){
            lutfirst[i]=200;
        }
        else{
            lutfirst[i]=255;
        }
    }
    Mat Thirdlut=Mat(1,256,CV_8UC1,lutthird);
    //拥有三通道的lut矩阵
    vector<Mat> m;
    Mat MYLUT,src,src2,src3,gray;
    m.push_back(Firstlut);
    m.push_back(Secondlut);
    m.push_back(Thirdlut);
    merge(m,MYLUT);
    //用一层lut进行比较
    LUT(image,Firstlut,src);
    //灰度图比较
    cvtColor(image,gray,COLOR_BGR2GRAY);
    LUT(gray,Firstlut,src3);
    //用三层lut进行比较
    LUT(image, MYLUT,src2);
    imshow("输出1",src2);
    imshow("输出",src);
    imshow("gray",src3);
}
void  createpyramid_demo(Mat &  image){
    //创建高斯金字塔
    vector<Mat> Gauss,Lap;
    int level=3;
    Gauss.push_back(image);
    for(int i=0;i<level;i++){
        Mat gauss;
        pyrDown(Gauss[i],gauss);
        Gauss.push_back(gauss);
    }
    // 创建拉普拉斯金字塔

    for(int i=Gauss.size()-1;i>0;i--){ 
        Mat src1,src2,src3;
        if(i=Gauss.size()-1){
            cout<<"one"<<endl;
            pyrDown(Gauss[i],src1);
            pyrUp(src1,src2);
            src3=Gauss[i]-src2;
            Lap.push_back(src3);
            cout<<i<<endl;
        }
        pyrUp(Gauss[i],src1);
        src2=Gauss[i-1]-src1;
        Lap.push_back(src2);
    }
    for(int j=0;j<level+1;j++){
        string name=to_string(j);
        imshow("q"+name,Gauss[j]);
    }
    // imshow("测试",Lap[3]);
}
Point prePoint;
Point one;
Point two;
Point three;
Mat temp;
void mouse(int event,int x, int y,int flags,void* userdata){
    Mat image=*((Mat*)(userdata));
    Mat src1;
    src1=image.clone();
    // image.copyTo(src1);
    if(event==EVENT_LBUTTONDOWN){ 
        one.x=x;
        one.y=y;
        cout<<"初始位置x"<<one.x<<"初始位置y"<<one.y<<endl;
    }
    if(event==EVENT_LBUTTONUP){
        two.x=x;
        two.y=y;
        cout<<"末位置x"<<two.x<<"末始位置y"<<two.y<<endl;
        Rect rect(one,two);
        rectangle(image,rect,Scalar(0,0,255),2,8,0);
        one.x=0;
        one.y=0;
        // imshow("鼠标窗口",image);
        temp.copyTo(image);
        imshow("鼠标窗口1",image(rect));
        // imshow("鼠标窗口",image);

    }
    else if( event==EVENT_MOUSEMOVE){
        if(one.x>0 && one.y>0){
            three.x=x;
            three.y=y;
            Rect rect1(one,three);
            temp.copyTo(image);
            rectangle(image,rect1,Scalar(0,0,255),2,8,0);
            imshow("鼠标窗口",image);
        }
    }
}
void mouserespone(Mat &image){
    image.copyTo(temp);
    imshow("鼠标窗口",image);
    setMouseCallback("鼠标窗口",mouse,(void*)(&image));
    waitKey(0);
    destroyAllWindows();
}
void writemouse(int event,int x,int y,int flags,void* userdata){
    Mat image=*((Mat*)(userdata));
    image.copyTo(temp);
    if(event==EVENT_LBUTTONDOWN){
        one=Point(x,y);
        cout<<"初始位置x"<<one.x<<"初始位置y"<<one.y<<endl;       
    }
    if(event==EVENT_MOUSEMOVE){
        if(one.x>0 && one.y){
            three=Point(x,y);
            line(image,one,three,Scalar(0,0,255),2,8,0);
            imshow("写字窗口",image);
            temp.copyTo(image);
        }
    }
    if(event==EVENT_LBUTTONUP){
        two=Point(x,y);
        cout<<"末位置x"<<two.x<<"末始位置y"<<two.y<<endl;
        line(image,one,two,Scalar(0,0,255),2,8,0);  
        one=Point(0,0);
        imshow("写字窗口",image);
    }
}
void write_demo(Mat &image){
    imshow("写字窗口",WINDOW_AUTOSIZE);
    setMouseCallback("写字窗口",writemouse,(void*)(&image));
    imshow("写字窗口",image);
    waitKey(0); 
    destroyAllWindows;  
}
Mat createhistogram(Mat & image){
    //提取直方图的数据,在统计多通道的时候，分为单通道进行统计.
    Mat hist_b,hist_g,hist_r,img1,img2;
    //统计的通道
    const int channels[1]={0};
    //维度
    int dims=1;
    //像素灰度值的最大值
    int bins[1]={256};
    //灰度值的范围
    float ranges[2]={0,255};
    const float* linesize[1]={ranges};
    //统计的时候，掩摸如果是空，则会统计全部的像素
    calcHist(&image,1,channels,Mat(),hist_b,dims,bins,linesize);
    // 绘制直方图
    int hist_w=512 ;
    int hist_h=400;
    int step=cvRound(hist_w/bins[1]);
    // 将存储直方图数据的矩阵进行归一化、
    cout<<hist_b<<endl;
    // normalize(hist_b,hist_b,0,400,NORM_MINMAX);
    Mat board=Mat(hist_h,hist_w,CV_8UC3,Scalar(255,255,255));
    for(int i=0;i<256;i++){
        Point start1,end1,start2,end2,start3,end3;
        //折线图坐标
        // start1=Point(i*2,hist_h-cvRound(hist_b.at<float>(i)));
        // end1=Point((i+1)*2,hist_h-cvRound(hist_b.at<float>(i+1)));
        // start2=Point(i*2,hist_h-cvRound(hist_g.at<float>(i)));
        // end2=Point((i+1)*2,hist_h-cvRound(hist_g.at<float>(i+1)));
        // start3=Point(i*2,hist_h-cvRound(hist_r.at<float>(i)));
        // end3=Point((i+1)*2,hist_h-cvRound(hist_r.at<float>(i+1)));
        //矩形坐标
        start1=Point(i*2,hist_h);
        end1=Point((i+1)*2,hist_h-cvRound(hist_b.at<float>(i+1)-1)/15 );
        //单通道可以绘制矩形的直方图，以下三折线图实例
        // line(board,start1,end1,Scalar(255,0,0),1,8,0);
        // line(board,start2,end2,Scalar(0,255,0),1,8,0);
        // line(board,start3,end3,Scalar(0,0,255),1,8,0);
        //以下矩形实例
        rectangle(board,start1,end1,Scalar(255,0,0),-1);
        imshow("zhifangtu1",board);

    }
    return board;
    // imshow("直方图",board);

}
void comparehistdemo(Mat &image_1,Mat &image_2){
    double similarity;
    Mat src1,src2;
    image_1.convertTo(src1,CV_32F);
    image_2.convertTo(src2,CV_32F);
    //比较方法较多,每个相似的方法的比较都不一样
    similarity=compareHist(src1,src2,HISTCMP_CORREL);
    cout<<similarity<<endl;
} 
Mat imagebalance(Mat &image){
    Mat src,src1,src2;
    vector<Mat> img1;
    //rgb图像先分离通道然后进行均值化然后*合并通道
    split(image,img1);
    img1[0].convertTo(src1,CV_8UC1);
    equalizeHist(src1,src2);
    imshow("均值化后的图像",src2);
    return src2;
}
void histogrammatch(Mat &image,Mat &image1){
    int channels[1]={0};
    Mat hist_a,hist_b;
    float ranges[2]={0,256};
    const float *Ranges[1]={ranges};
    int bins[1]={256};
    int dims=1;
    calcHist(&image,1,channels,Mat(),hist_a,dims,bins,Ranges);
    calcHist(&image1,1,channels,Mat(),hist_b,dims,bins,Ranges);
    normalize(hist_a,hist_a,1,0,NORM_MINMAX,-1,Mat());
    normalize(hist_b,hist_b,1,0,NORM_MINMAX,-1,Mat());
    //计算累计概率
    float hist_a_1[256]={hist_a.at<float>(0)};
    float hist_b_1[256]={hist_b.at<float>(0)}; 
    for(int i=1;i<256;i++){
        hist_a_1[i]=hist_a_1[i-1]+hist_a.at<float>(i);
        hist_b_1[i]=hist_b_1[i-1]+hist_b.at<float>(i);   
    }
    //构建累计概率误差矩阵
    float diff[256][256];
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            diff[i][j]=fabs(hist_a_1[i]-hist_b_1[j]);
        }
    }
    //生产lut
    Mat lut(1,256,CV_8U);
    for(int i=0;i>256;i++){
        float min=diff[i][0];
        int index=0;
        for(int j=1;j<256;j++){
            if(min<diff[i][j]){
                min=diff[i][j];
                index=j;
            }
        }
        lut.at<uchar>(i)=index;
    }
    cout<<lut<<endl;
    Mat result,img,img1,img2;
    LUT(image,lut,result);
    img1=createhistogram(image);
    img2=createhistogram(image1);
    img=createhistogram(result);
    imshow("匹配后直方图",img);
    imshow("直方图1",img1);
    imshow("直方图2 ",img2);
    imshow("结果",result);
}
void bianyuanjiance(Mat &image){
    Mat kernel=(Mat_<float>(2,2)<<-1,0,0,1);
    Mat src1,src2,src3,src4,src5,src6,src7;
    filter2D(image,src1,CV_16S,kernel);
    convertScaleAbs(src1,src1);
    imshow("边缘检测",src1);
    //sobel检测
    Sobel(image,src2,CV_32F,1,0,3);
    Sobel(image,src3,CV_32F,0,1,3);
    src4=src2+src3;
    imshow("sobel边缘检测",src4);
    //scharr检测
    Scharr(image,src4,CV_32F,1,0);
    Scharr(image,src5,CV_32F,0,1);
    src6=src4+src5;
    imshow("scharr边缘检测",src6);
    //Laplacian检测
    Laplacian(image,src7,CV_32F,3);
    imshow("laplacia边缘检测",src7);
}
void draw(Mat point,Mat &image){
    for(int i=0;i<point.rows;i++){
        if(i=point.rows-1){
            Vec2i point1=point.at<Vec2i>(i);
            Vec2i point2=point.at<Vec2i>(0);
            line(image,point1,point2,Scalar(255,0,0),2,8);
            break;

        }
        Vec2i point1=point.at<Vec2i>(i);
        Vec2i point2=point.at<Vec2i>(i+1);
        line(image,point1,point2,Scalar(255,0,0),2,8);
    }
}
void contourscheck(Mat &image){
    Mat src ,kernel,src1,src2;
    kernel=getStructuringElement(0,Size(3,3));
    
    imshow("没有进行高斯的图像",image);
    image.copyTo(src);
    image.copyTo(src1);
    image.copyTo(src2);
    // morphologyEx(image,image,0,kernel);
    morphologyEx(image,image,1,kernel);
    cvtColor(image,image,COLOR_BGR2GRAY);
    GaussianBlur(image,image,Size(9,9),3,3);
    threshold(image,image,100,255,0);
    vector<Mat> contours;
    vector<Vec4i> array;
    findContours(image,contours,array,1,2);
    
    for(int i=0;i<array.size();i++){
         cout<<array[i]<<endl;
    }     
    drawContours(src,contours,-1,Scalar(255,0,0),2,8);
    imshow("展示",src);
    //轮阔多边形拟和
    Rect rect;
    for(int i=0;i<contours.size();i++){
        //绘制最大外接矩形
        rect=boundingRect(contours[i]);
        rectangle(src1,rect,Scalar(255,0,0),2,8);
        imshow("展示2",src1);
        Point2f point[4];
        Point2f point1;
        RotatedRect rrect=minAreaRect(contours[i]);
        //读取最小外接矩形的四个定点
        rrect.points(point);
        cout<<point<<endl;
        point1=rrect.center;
        //绘制旋转矩形
        // for(int i=0;i<4;i++){
        //     if(i=3){
        //         line(src2,point[i],point[0],Scalar(255,0,0),2,8);

        //     }
        //     line(src2,point[i],point[i+1],Scalar(255,0,0),2,8);
        // }
        Mat result;
        approxPolyDP(contours[i],result,4,true);
        draw(result,src2);
        imshow("展示3",src2);
    } 
}
void linecheck(Mat &image){
    Mat src,src1;
    vector<Vec2f> lines ,liness;
    cvtColor(image,src1,COLOR_RGB2GRAY);
    imshow("1",src1);
    GaussianBlur(src1,src,Size(3,3),3); 
    Canny(src,src,100,150,3);
    threshold(src,src,100,255,THRESH_BINARY);
    imshow("处理",src);
    HoughLines(src,lines,1,CV_PI/180,80,0,0);
    Point p1,p2;
    //绘制直线，原理照抄
    for(int i=0;i<lines.size();i++){
        float r=lines[i][0];
        float j=lines[i][1]; 
        double a=r*cos(j);
        double b=r*sin(j);
        Point p3;
        double x=r*cos(j);
        double y=r*sin(j);
        int lenth=max(image.rows,image.cols);
        p1.x=cvRound(x+lenth*(-b));
        p1.y=cvRound(y+lenth*a);
        p2.x=cvRound(x-lenth*(-b));
        p2.y=cvRound(y-lenth*a);
        line(image,p1,p2,Scalar(255,0,0),2,8);

    }
    imshow("2",image); 
}
Mat lvcheck(Mat &image){
    Mat src,src2;
    image.copyTo(src);
     cvtColor(src,src,COLOR_BGR2HSV);
     //70~99
    inRange(src,Scalar(70,43,46),Scalar(85,255,255),src2);
    Mat kernel=getStructuringElement(1,Size(3,3));
    morphologyEx(src2,src2,0,kernel,Point(-1,-1),12);
    Mat kernel1=getStructuringElement(1,Size(9,29));
    morphologyEx(src2,src2,1,kernel1,Point(-1,-1),3);
    vector<vector<Point>> contour;
    vector<Vec4i> value;
    findContours(src2,contour,value,3,2,Point());
    // drawContours(image,contour,-1,Scalar(255,0,0),1,8);
    for(int i=0;i<contour.size();i++){
        Rect rect=boundingRect(contour[i]);
        double area=contourArea(contour[i],false);
        if (area>10000){
            rectangle(image,rect,Scalar(255,0,0),1,8);
        }
        
    }
    return image;
}
Mat bluecheck(Mat &image){
    Mat src,src2;
    image.copyTo(src);
     cvtColor(src,src,COLOR_BGR2HSV);
     //70~99
    inRange(src,Scalar(105,150,46),Scalar(115,255,255),src2);
    Mat kernel=getStructuringElement(1,Size(3,3));
    morphologyEx(src2,src2,0,kernel,Point(-1,-1),7);
    // Mat kernel1=getStructuringElement(1,Size(9,29));
    // morphologyEx(src2,src2,1,kernel1,Point(-1,-1),10);
    vector<vector<Point>> contour;
    vector<Vec4i> value;
    findContours(src2,contour,value,3,2,Point());
    // drawContours(image,contour,-1,Scalar(255,0,0),1,8);
    for(int i=0;i<contour.size();i++){
        Rect rect=boundingRect(contour[i]);
        double area=contourArea(contour[i],false);
        if (area>10000){
            rectangle(image,rect,Scalar(255,0,0),1,8);
        }   
    }
    return src2;
}
Mat hun(Mat &image){
    Mat src,src2;
    image.copyTo(src);
    Mat msrc,msrc2;
    image.copyTo(msrc);
     cvtColor(src,src,COLOR_BGR2HSV);
     //70~99
    inRange(src,Scalar(105,150,46),Scalar(112,255,255),src2);
    Mat kernel=getStructuringElement(1,Size(3,3));
    morphologyEx(src2,src2,0,kernel,Point(-1,-1),7);
    // Mat kernel1=getStructuringElement(1,Size(9,29));
    // morphologyEx(src2,src2,1,kernel1,Point(-1,-1),7);
    vector<vector<Point>> contour;
    vector<Vec4i> value;
    findContours(src2,contour,value,3,2,Point());
    // drawContours(image,contour,-1,Scalar(255,0,0),1,8);
    for(int i=0;i<contour.size();i++){
        RotatedRect rect=minAreaRect(contour[i]);
        Point2f points[4];
        rect.points(points);
        double area=contourArea(contour[i],false);
        if (area>10000){
            for(int i=0;i<4;i++){
                if(i==3){
                    line(image,points[i],points[0],Scalar(255,0,0),2,8);
                    break;
                }
                line(image,points[i],points[i+1],Scalar(255,0,0),2,8);
            }
        } 
    }
     cvtColor(msrc,msrc,COLOR_BGR2HSV);
     //70~99
    inRange(msrc,Scalar(70,43,46),Scalar(85,255,255),msrc2);
    Mat mkernel=getStructuringElement(1,Size(3,3));
    morphologyEx(msrc2,msrc2,0,mkernel,Point(-1,-1),12);
    Mat mkernel1=getStructuringElement(1,Size(9,29));
    morphologyEx(msrc2,msrc2,1,mkernel1,Point(-1,-1),5);
    vector<vector<Point>> mcontour;
    vector<Vec4i> mvalue;
    findContours(msrc2,mcontour,mvalue,3,2,Point());
    // drawContours(image,mcontour,-1,Scalar(255,0,0),1,8);
    for(int i=0;i<mcontour.size();i++){
        RotatedRect rect1=minAreaRect(mcontour[i]);
        Point2f points1[4];
        rect1.points(points1);
        double area1=contourArea(mcontour[i],false);
        if (area1>10000){
            for(int i=0;i<4;i++){
                if(i==3){
                    line(image,points1[i],points1[0],Scalar(0,255,0),2,8);
                    break;
                }
                line(image,points1[i],points1[i+1],Scalar(0,255,0),2,8);
            }
        } 
    }
    return image;
   
}
} // namespace quick_demo
