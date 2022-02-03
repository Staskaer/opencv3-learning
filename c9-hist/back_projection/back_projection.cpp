/*
 * 反向投影
 * 由于直方图可以看成是一个概率函数，位某个像素属于某个纹理的概率
 * 反向投影是一种记录给定图像中像素点如何适应直方图模型的像素分布
 * 即先计算某一特征的直方图，然后使用模型去寻找图像中存在该特征的方法
 * 
 * 先使用模型图像建立直方图
 * 然后对测试图像的每个像素p(i,j)，获取色调数据并找到该色调(hij,sij)在直方图的bin的位置
 * 然后根据bin的数值将其存储在反射投影图像中
 * 对每个像素重复以上步骤，得到全部的反射投影图像
 * 
 * 可以用于在较大的输入图像中来查找较小的模板图像定位模板图像的位置
 * 
 * 可以把反向投影图像看成是二维浮点数组、二维矩阵、单通道浮点图像
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, hsv, dst, hue;
int bins = 30;

void on_bin_change(int, void *);

int main()
{
    img = imread("left.jpg", IMREAD_COLOR);
    cvtColor(img, hsv, COLOR_BGR2HSV);

    hue.create(hsv.size(), hsv.depth());
    int ch[] = {0, 0};
    mixChannels(&hsv, 1, &hue, 1, ch, 1);
    /*
     * 通道复制函数
     * 由输入参数复制某通道到输出参数的特定通道中
     * 参数分别是输入矩阵，矩阵数目，输出矩阵，矩阵数目，fromto数组，fromto数组的大小-1
    */

    namedWindow("img", WINDOW_AUTOSIZE);
    createTrackbar("bins", "img", &bins, 180, on_bin_change, 0);
    on_bin_change(0, 0);

    imshow("img", img);
    waitKey(-1);
}

void on_bin_change(int, void *)
{
    MatND hist;
    int hist_size = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float *ranges = {hue_range};

    calcHist(&hue, 1, 0, Mat(), hist, 1, &hist_size, &ranges, true, false);
    /*
     * 计算直方图
    */
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    /*
     * 归一化函数
    */

    MatND backproj;
    calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);
    /*
     * 计算反向投影
     * 第一个参数是输入的图像（代比较的图），可以是数组集，但必须同尺寸和深度
     * 第二个参数是输入数组尺寸
     * 第三个参数是需要统计的通道的索引（从0开始）
     * 第四个参数是输入直方图
     * 第五个参数是目标反向投影阵列，必须为单通道
     * 第六个参数是每一维数值的取值范围
     * 第七个参数是缩放因子
     * 第八个参数是直方图是否均匀标志位
    */

    imshow("img", backproj);

    //绘制直方图
    int w = 400, h = 400;
    int bin_w = cvRound((double)w / hist_size);
    Mat hist_img = Mat::zeros(w, h, CV_8UC3);

    for (int i = 0; i < bins; i++)
    {
        rectangle(hist_img, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
    }
    imshow("hist", hist_img);
}