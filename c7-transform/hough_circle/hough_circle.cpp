/*
 * 学习hough圆检测算法
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("detect_blob.png", IMREAD_COLOR);
    Mat gray, edge;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);

    vector<Vec3f> circles; //三个参数是x，y，r

    HoughCircles(gray, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
    /*
     * 前两个是输入输出，其中输出是三元组
     * 第三个参数是检测方法，只有梯度能用
     * 第四个参数dp是用来检测圆心累加器图像分辨率于输入图像之比倒数（？）
     * 当dp = 1时，累加器和输入图像分辨率相同；dp = 2时，累加器的分辨率只有一半
     * 第五个参数时圆心之间最小距离
     * 第六个参数是内部canny边缘检测算法高阈值，低阈值是高阈值的一半
     * 第七个参数是梯度法的参数，越小则能检测更多圆，越大检测的圆越接近完美
     * 第八个参数是圆最小半径
     * 第九个参数圆最大半径
     * 
     * 另外，此函数只适合找到圆心，不适合计算半径0
    */

    for (auto x : circles)
    {
        Point center(cvRound(x[0]), cvRound(x[1]));
        int r = cvRound(x[2]);

        circle(img, center, r, Scalar(0, 255, 255), 2);
    }
    imshow("img", img);
    waitKey(-1);
}