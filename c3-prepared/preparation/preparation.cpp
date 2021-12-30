//记录opencv c++编程的基本操作
//读取图片，Mat数组，显示
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    Mat pic(320, 640, 0, Scalar(100));
    //创建空mat数组

    Mat image = imread("lena.jpg", IMREAD_COLOR);
    /*
    *imread函数：第一个是路径
    *第二个参数flag有多个取值，可以传入int或定义的枚举
    *多个位用 | 隔开
    *IMREAD_ANYCOLOR | IMREAD_ANYDEPTH 是传入无损图像
    *flags传入负值可以载入alpha通道，默认是不载入的
    */

    imshow("show", image);
    waitKey(-1);
    destroyAllWindows();
    /*
    *imshow函数第一个参数是输出窗口的id
    *如果窗口是默认值创建的，则显示原始尺寸，否则将进行缩放
    *缩放原则：uint8 -- 原始尺寸
    *uint16或uint32 -- 将[0，255*256]映射到[0,255]
    *float32 -- 将[0,1]映射到[0，255]
    */

    system("pause");
}