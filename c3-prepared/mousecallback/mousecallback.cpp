/*
*本文件学习使用鼠标操作
*/

//鼠标回调也是通过设置回调函数实现的
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

//鼠标回调函数
void mouse_callback(int event, int x, int y, int flags, void *params);
//绘制矩形框函数
void draw_rect(Mat &, Rect);
void show_text();

Rect rectangle_g;
/*
*Rect 是矩形对象，（x,y,w,h）构建矩形
*有size，area，tl,br,width,height,contains(Point(x,y))
*分别表示尺寸，面积，左上坐标，右下坐标，宽，高，和点的包含
*可以用&，|对矩形求交和并
*rect + Point(x,y)平移
*rect + size(size)缩放
*/

bool draw_flag = false;
//绘制的标记

RNG g_rng(123456);
//RNG类是opencv里C++的随机数产生器。
//next可以产生下一个随机数
//uniform 可以返回指定范围随机数
//gaussian可以返回高斯随机数
//fill可以填充矩阵

int main()
{
    rectangle_g = Rect(-1, -1, 0, 0);
    Mat src(600, 800, CV_8UC3), temp;
    src.copyTo(temp);
    src = Scalar::all(0);
    //scalar代表各个通道的初始值，相当于元组

    namedWindow("callback");
    setMouseCallback("callback", mouse_callback, (void *)&src);
    //设置窗口回调函数，第三个参数同样是用户数据

    while (true)
    {
        src.copyTo(temp);
        if (draw_flag)
            //此处是为了实时显示轨迹
            draw_rect(temp, rectangle_g);
        imshow("callback", temp);

        if (waitKey(10) == 27)
            break;
    }
    return 0;
}

void mouse_callback(int event, int x, int y, int flags, void *params)
{
    //鼠标回调函数,flags似乎是鼠标不同操作时返回不同的值

    Mat &img = *(Mat *)params;

    switch (event)
    {
    case EVENT_MOUSEMOVE:
        //鼠标移动
        {
            if (draw_flag)
            {
                rectangle_g.width = x - rectangle_g.x;
                rectangle_g.height = y - rectangle_g.y;
            }
        }
        break;

    case EVENT_LBUTTONDOWN:
        //左键按下
        {
            draw_flag = true;
            rectangle_g = Rect(x, y, 0, 0);
            //记录起始位置
        }
        break;

    case EVENT_LBUTTONUP:
        //左键抬起
        draw_flag = false;
        if (rectangle_g.width < 0)
        {
            //x轴反方向移动
            rectangle_g.x += rectangle_g.width;
            rectangle_g.width *= -1;
        }

        if (rectangle_g.height < 0)
        {
            //y轴反方向移动
            rectangle_g.y += rectangle_g.height;
            rectangle_g.height *= -1;
        }

        draw_rect(img, rectangle_g);

        break;
    }
}

void draw_rect(Mat &img, Rect box)
{
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}