/*
 * 图像修补
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, mask;
Point previous_point(-1, -1);

static void on_mouse(int event, int x, int y, int flags, void *)
{
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        //左键抬起
        previous_point = Point(-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        //左键按下
        previous_point = Point(x, y);
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    //左键移动按下
    {
        Point pt(x, y);
        if (previous_point.x < 0)
            previous_point = pt;

        //绘制白色线（掩模和图像同时绘制）
        //这种掩模的处理方式很有用
        line(mask, previous_point, pt, Scalar::all(255), 5, LINE_AA);
        line(img, previous_point, pt, Scalar::all(255), 5, LINE_AA);
        previous_point = pt;
        imshow("img", img);
    }
}

int main()
{
    Mat src = imread("lena.jpg", IMREAD_COLOR);
    img = src.clone();
    mask = Mat::zeros(img.size(), CV_8U);

    imshow("img", img);

    setMouseCallback("img", on_mouse, 0);

    while (1)
    {
        char c = waitKey(0);

        if (c == 27)
            break;

        if (c == '2')
        {
            //恢复原图
            mask = Scalar::all(0);
            src.copyTo(img);
            imshow("img", img);
        }

        if (c == '1')
        //图像修补
        {
            Mat inpaint_img;
            inpaint(img, mask, inpaint_img, 3, INPAINT_TELEA);
            /*
             * 修复函数，但是效果不太好
             * 第一个参数是原图像
             * 第二个参数是修复掩模，其中非0区域为修复区域
             * 第三个参数是输出
             * 第四个参数是修复参考半径
             * 第五个参数是修复算法
             * 有INPAINT_TELEA和INPAINT_NS两种
            */
            imshow("inpaint", inpaint_img);
        }
    }
}