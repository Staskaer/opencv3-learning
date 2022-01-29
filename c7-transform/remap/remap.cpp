/*
 * 重映射
 * 重映射与映射相对应，也十分类似
 * 映射是dst(x,y) = src(h(x),h(y))
 * 重映射是dst(x,y) = src(hx(x),hy(y))
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    Mat map_x, map_y;

    dst.create(img.size(), img.type());
    map_x.create(img.size(), CV_32FC1);
    map_y.create(img.size(), CV_32FC1);

    for (int j = 0; j < img.rows; j++)
        for (int i = 0; i < img.cols; i++)
        {
            map_x.at<float>(j, i) = static_cast<float>(i);
            map_y.at<float>(j, i) = static_cast<float>(img.rows - j);
        }

    remap(img, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
    /*
     * 重映射不支持就地操作
     * 前两个参数是输出输出
     * 第三个参数是map1，有两种表示对象
     * 第一种是(x,y)的映射
     * 第二种是CV_16SC2/CV_32FC1/CV_32FC2类型的x的值
     * 第四个参数是map2，会根据map1来选择
     * 当map1是(x,y)的映射时，map2是无效参数
     * 否则表示CV_16UC1/CV_32FC1类型的y
     * 第五个参数是插值方式
     * INTER_NEAREST -- 最邻近插值
     * INTER_LINEAR -- 双线性插值（默认值）
     * INTER_CUBIC -- 双三次样条插值
     * INTER_LANCZOS4 -- 那个插值
     * 第六个参数是边界模式
     * 第七个参数是常数边界使用的值
    */

    imshow("dst", dst);
    waitKey(-1);
}