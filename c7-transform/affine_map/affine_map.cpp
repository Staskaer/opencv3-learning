/*
 * 仿射变换
 * 即一个向量向量经过一次线性变换再经过一次平移变换
 * 成为另一个向量空间的过程
 * 保持了平直性（直线仍然是直线）和平行性（平行线依然平行）
 * 
 * 仿射变换可以表示为 向量*矩阵+向量 的形式
 * 可以看成是两幅图像之间的联系
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int agrc, char *argv[])
{
    system("color 1A");

    Point2f src_t[3], dst_t[3]; //这是仿射变换对应的三点

    Mat rot_mat(2, 3, CV_32FC1);
    Mat warp_mat(2, 3, CV_32FC1);
    Mat src, dst_warp, dst_warp_rot;
    src = imread("lena.jpg", IMREAD_COLOR);

    dst_warp = Mat::zeros(src.rows, src.cols, src.type());

    src_t[0] = Point2f(0, 0);
    src_t[1] = Point2f(static_cast<float>(src.cols - 1), 0);
    src_t[2] = Point2f(0, static_cast<float>(src.rows - 1));

    dst_t[0] = Point2f(static_cast<float>(src.cols * 0.0), static_cast<float>(src.rows * 0.33));
    dst_t[1] = Point2f(static_cast<float>(src.cols * 0.65), static_cast<float>(src.rows * 0.35));
    dst_t[2] = Point2f(static_cast<float>(src.cols * 0.15), static_cast<float>(src.rows * 0.6));

    warp_mat = getAffineTransform(src_t, dst_t);
    /*
     * 仿射变换需要用到三个点来确定变换矩阵
     * 此函数是已知变换两点求变换矩阵
     * 由于[a00,a01,a02;a10,a11,a12][1;x;y]（有偏置常数）
     * 所以变换矩阵是两行三列的
    */

    warpAffine(src, dst_warp, warp_mat, dst_warp.size());
    /*
     * 仿射变换函数dst(x,y) = src(a00 + a01 * x+a02 * y , a10 + a11 * x + a12 * y)
     * 第一个参数是输入，第二个参数是输出
     * 第三个参数是仿射变换矩阵（2*3）
     * 第四个参数是输出的尺寸
     * 第五个参数是插值方式（默认即可）
     * 第六个参数是边界模式
     * 第七个参数也是边界相关
    */

    //先缩放再旋转
    Point center = Point(dst_warp.cols / 2, dst_warp.rows / 2);
    double angle = -30.0;
    double scale = 0.8;

    rot_mat = getRotationMatrix2D(center, angle, scale);
    /*
     * 这个函数是计算二维旋转变化仿射矩阵
     * 第一个参数是旋转中心
     * 第二个参数旋转角度
     * 第三个参数缩放系数
     * 也可以用于仿射变换，因为二维平面旋转缩放矩阵是2*3的尺寸
    */

    warpAffine(dst_warp, dst_warp_rot, rot_mat, dst_warp.size());

    imshow("raw", src);
    imshow("warp", dst_warp);
    imshow("warp_rot", dst_warp_rot);
    waitKey(-1);
}
