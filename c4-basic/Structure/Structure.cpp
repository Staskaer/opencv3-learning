/*
*本文件学习基础图像容器Mat,和一系列的基本数据结构的使用
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void mat(void);    //mat介绍
void point(void);  //point点结构介绍
void scalar(void); //scalar颜色类的说明
void size(void);   //size类说明
void rect(void);   //rect矩形类
void cvt(void);    //颜色转换方法cvtcolor

int main(int argc, char *argv[])
{
     cvt();
}

void mat(void)
{
     /*
    *mat类的一些说明
    *mat类的内部结构是由一个矩阵头（包含矩阵尺寸，存储方法，地址等信息）
    *和一个指向存储矩阵的指针组成。矩阵头通常是常值，而矩阵本身则不一定
    *每个mat的矩阵头不会改变，共享同一个矩阵。
    *即只改变矩阵指针，不复制矩阵本身

    *当不再需要矩阵本身时，由最后一个mat矩阵头负责回收内存
    *类似于智能指针
    */

     Mat A, C;                             //此处只创建矩阵头
     A = imread("lena.jpg", IMREAD_COLOR); //为矩阵分配内存
     Mat B(A);                             //共享矩阵(拷贝构造函数)
     C = A;
     rectangle(C, Rect(0, 0, 200, 200), Scalar(255, 255, 0));
     //在c上的更改体现在A上

     Mat F, G; //此时F,G的改变不会作用于A
     F = A.clone();
     A.copyTo(G);
     rectangle(F, Rect(200, 200, 300, 300), Scalar(255, 123, 255));
     rectangle(G, Rect(200, 200, 300, 300), Scalar(255, 123, 255));

     imshow("A", A);
     imshow("F", F);
     imshow("G", G);

     /******************
    ***Mat结构的初始化***
    ******************/

     Mat m(2, 2, CV_8UC3, Scalar(0, 255, 0));
     cout << "使用cout输出 ：\n"
          << m; //输出运算符只对二维数组有效

     //创建超过两维数组，但不知道有什么用
     int sz[] = {2, 2, 2}; //这个数组指定维数的尺寸
     Mat n(3, sz, CV_8UC3, Scalar::all(123));

     //使用create方法时不能初始化值，只能开辟空间
     m.create(2, 2, CV_8UC(2));
     cout << endl
          << "create方法： \n"
          << m << endl;

     //也可以使用matlab风格创建特殊的矩阵
     Mat matlab1 = Mat::eye(4, 4, CV_64F);
     Mat matlab2 = Mat::ones(4, 4, CV_32F);
     Mat matlab3 = Mat::zeros(4, 4, CV_8UC1);
     cout << "matlab风格，eye，ones，zeros" << endl
          << matlab1 << endl
          << matlab2 << endl
          << matlab3 << endl;

     //小括号方式初始化，实际上是重载了<<和，运算符
     Mat s = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
     cout << "s : \n"
          << s << endl;

     //行列可以单独复制
     Mat clone = s.row(1).clone();
     cout << "clone\n"
          << clone << endl;

     /****************************
    **mat数组的填充方法和输出格式**
    ****************************/

     //使用随机数填充
     Mat r = Mat(3, 10, CV_8UC3);
     randu(r, Scalar::all(0), Scalar::all(255));
     cout << "\n\n\nr---c++\n"
          << r;

     //输出python风格
     cout << "\nr---python\n"
          << format(r, Formatter::FMT_PYTHON);

     //matlab风格
     cout << "\nr---matlab\n"
          << format(r, Formatter::FMT_MATLAB);

     waitKey(-1);
}

void point(void)
{
     /*
     * opencv中点有多种组织形式
     * 其中point是point2i的typedef，均为point_<int>
     * 有二维点和三维点，三维点不知道是干嘛的
     * 有.x  .y的属性
     */

     //二维点
     Point2f p2(6, 2);
     cout << "\n p2 \n"
          << p2;

     //三维点
     Point3d p3(2, 5, 6);
     cout << "\n p3 \n"
          << p3;

     //基于mat的vector
     vector<float> v{1, 2, 3};
     cout << "\nvector on mat \n"
          << Mat(v);

     //用vector存放点坐标
     vector<Point2f> points(5);
     for (auto &point : points)
     {
          point = Point2f((float)rand(), (float)rand());
          cout << point << endl;
     }

     system("pause");
}

void scalar(void)
{
     /*
     * scalar类是颜色类，有4个元素，是vec4x的一个变种
     * Scalar是Scalar_<double>的typedef
     * 
    */
     Mat pic(100, 200, CV_8UC3, Scalar(0, 225, 123));
     imshow("pic", pic);
     waitKey(-1);
     destroyAllWindows();
}

void size(void)
{
     /*
     * Size类是存储尺寸的
     * 一般使用size（width,height）
    */
     Mat pic = imread("lena.jpg", IMREAD_COLOR);
     rectangle(pic, Rect(Point(0, 0), Point(100, 100)), Scalar(0, 255, 0), 1);
     rectangle(pic, Rect(Point(0, 0), Point(100, 100)) + Size(100, 100), Scalar(0, 255, 255), 2);
     imshow("pic", pic);
     waitKey(-1);
     system("pause");
}

void rect(void)
{
     /*
     * rect类的成员变量有tl,br,width,height等
     * 可以结合Point(),和Size()进行平移和缩放
    */
}

void cvt(void)
{
     Mat pic = imread("lena.jpg", IMREAD_COLOR);
     cvtColor(pic, pic, COLOR_BGR2RGB);
     imshow("hsv", pic);
     //imshow函数只能按照bgr解释通道
     waitKey(-1);
     destroyAllWindows();
}