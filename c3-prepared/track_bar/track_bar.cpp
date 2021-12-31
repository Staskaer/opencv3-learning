/*
*学习滑块条的创建和使用
*使用轨迹条控制alpha通道混合
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

//全局变量声明
const int MAX_ALPHA_VALUE = 100;

void show_bar(int bar, void *temp)
{
    double alpha_value, beta_value;
    alpha_value = double(bar) / MAX_ALPHA_VALUE;
    //用目标值去除以总值得到比例
    beta_value = 1.0 - alpha_value;
    //另一个做差即可

    //从用户变量中获取传递的数组
    Mat **tuple = (Mat **)temp;
    //temp是指向指针数组的一个指针
    Mat pic1 = *tuple[0];
    Mat pic2 = *tuple[1];
    Mat dst = *tuple[2];

    addWeighted(pic1, alpha_value, pic2, beta_value, 0., dst);
    imshow("result", dst);

    //getTrackbarPos((char *)temp, "image_show");
    //这个函数返回窗口中轨迹条的数值
    //有用！
}

int main(int argc, char *argv[], char **env)
{
    //先获取图像
    Mat pic1 = imread("left.jpg", IMREAD_COLOR), pic2 = imread("right.jpg", IMREAD_COLOR), dst;
    vector<Mat *> tup = {&pic1, &pic2, &dst};
    //将图像指针传递

    //滑块初始值
    int bar = 70;
    //为滑块命名和创建滑块
    char name[50];
    sprintf(name, "透明值 %d", MAX_ALPHA_VALUE);
    namedWindow("image_show");

    createTrackbar(name, "image_show", &bar, 100, show_bar, tup.data());
    /*
    *这个函数可以创建轨迹条
    *第一个参数是轨迹条名字，第二个参数是轨迹条依附的窗口
    *第三个参数是轨迹条初始值，是一个int *类型
    *第四个参数是滑块最大值，最小值始终是0
    *第五个参数是回调函数指针，每次滑块变化都会执行回调函数
    *回调函数必须是 void xxxx(int ,void *)类型或null类型
    *回调函数第一个参数是滑块位置，第二个参数是用户数据(见下面，即第六个参数)
    *第六个参数是用户数据，会传递给回调函数的第二个参数
    */
    waitKey(-1);
    destroyAllWindows();
}