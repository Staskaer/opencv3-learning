/*
 * 本文件继续学习形态学变换
 * 包括开闭运算，形态学梯度，顶帽，黑帽
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, dst, grad;
int element_shape = MORPH_RECT; //元素结构形状
int max_iteration = 10;
int open_close_shift = 0;
int erode_dilate_shift = 0;
int top_black_shift = 0;

//全局函数
static void open_close(int, void *);
static void erode_dilate(int, void *);
static void top_black_hat(int, void *);

int main()
{
    img = imread("lena.jpg", IMREAD_COLOR);

    namedWindow("raw", 1);
    namedWindow("open_close", 1);
    namedWindow("top_black", 1);
    namedWindow("erode_dilate", 1);
    namedWindow("gradient", 1);

    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    morphologyEx(img, grad, MORPH_GRADIENT, element);
    //形态学梯度是膨胀图减去腐蚀图，凸显边缘
    imshow("raw", img);
    imshow("gradient", grad);

    open_close_shift = 9;
    erode_dilate_shift = 9;
    top_black_shift = 2;

    createTrackbar("iteration", "open_close", &open_close_shift, max_iteration * 2 + 1, open_close);
    createTrackbar("iteration", "top_black", &top_black_shift, 2 * max_iteration + 1, top_black_hat);
    createTrackbar("iteration", "erode_dilate", &erode_dilate_shift, 2 * max_iteration + 1, erode_dilate);

    while (1)
    {
        //轮询的方式获取按键
        int c;
        open_close(open_close_shift, 0);
        erode_dilate(erode_dilate_shift, 0);
        top_black_hat(top_black_shift, 0);

        c = waitKey(0);
        if ((char)c == 'q')
            break;
        else if ((char)c == 49)
            element_shape = MORPH_ELLIPSE;
        else if ((char)c == 50)
            element_shape = MORPH_RECT;
        else if ((char)c == 51)
            element_shape = MORPH_CROSS;
    }
}

void open_close(int, void *)
{
    //开运算和闭运算
    /*
     * 开运算是先腐蚀后膨胀
     * 可以消除细小的物体，在纤细点分离物体
     * 可以平滑较大物体的边界且不改变其面积
     * 
     * 闭运算是先膨胀后腐蚀
     * 可以排除小型黑洞
    */
    int offset = open_close_shift - max_iteration;
    int abs_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(element_shape, Size(abs_offset * 2 + 1, abs_offset * 2 + 1), Point(abs_offset, abs_offset));

    if (offset < 0)
        morphologyEx(img, dst, MORPH_OPEN, element);
    /*
         * 形态学变化函数
         * 前两个参数是输入输出
         * 第三个参数是类型
         * 有MORPH_OPEN/CLOSE,MORPH_TOPHAT/BLACKHAT,MORPH_ERODE/DILATE,MORPH_GRADIENT
         * 第四个参数一般是element获取到的数据，和erode类似
         * 第五个参数是锚点
         * 第六个参数是迭代次数
         * 第七、八个参数是边界类型，不用管
        */
    else
        morphologyEx(img, dst, MORPH_CLOSE, element);

    imshow("open_close", dst);
}

void erode_dilate(int, void *)
{
    //膨胀和腐蚀

    int offset = erode_dilate_shift - max_iteration;
    int abs_offset = offset > 0 ? offset : -offset;
    Mat element = getStructuringElement(element_shape, Size(abs_offset * 2 + 1, abs_offset * 2 + 1), Point(abs_offset, abs_offset));

    if (offset < 0)
        erode(img, dst, element);
    else
        dilate(img, dst, element);

    imshow("erode_dilate", dst);
}

void top_black_hat(int, void *)
{
    //顶帽黑帽
    /*
     * 顶帽是源图像与开运算之差，分离比临近点亮一些的斑点
     * 黑帽是源图像与闭运算之差，分离比临近点暗一些的斑点
    */

    int offset = top_black_shift - max_iteration;
    int abs_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(element_shape, Size(abs_offset * 2 + 1, abs_offset * 2 + 1), Point(abs_offset, abs_offset));

    if (offset < 0)
        morphologyEx(img, dst, MORPH_TOPHAT, element);
    else
        morphologyEx(img, dst, MORPH_BLACKHAT, element);

    imshow("top_black", dst);
}