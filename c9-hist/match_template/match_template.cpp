/*
 * 模板匹配
 * 模板匹配是在一幅图像中寻找与另一幅待匹配图最可能匹配的部分
 * 如在一副人像中匹配人脸
 * 模板匹配不是基于直方图，而是在图像上滑动
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, template_img, dst;
int method = 0;

void on_match(int, void *); //模板匹配的回调函数

int main()
{
    img = imread("raw.jpg", 1);
    template_img = imread("template.png");

    namedWindow("raw", WINDOW_FREERATIO);
    namedWindow("dst", WINDOW_FREERATIO);

    createTrackbar("type", "raw", &method, 5, on_match, 0);

    on_match(0, 0);

    waitKey(-1);
}

void on_match(int, void *)
{
    Mat src;
    img.copyTo(src);

    //初始化结果输出矩阵
    int result_rows = img.rows - template_img.rows + 1;
    int result_cols = img.cols - template_img.cols + 1;
    dst.create(result_rows, result_cols, CV_32FC1);

    //匹配和标准化
    matchTemplate(src, template_img, dst, method);
    /*
     * 模板匹配函数
     * 第一个参数是待搜索图像
     * 第二个图像时搜索模板，和源图像有一样的数据结构类型
     * 第三个参数时输出图像，位32位单通道浮点
     * 如果图像尺寸W*H，模板尺寸w*h则结果为（W-w+1)*(H-h+1)
     * 第四个参数是匹配的方法，有6种
     * TM_SQDIFF -- 平方差匹配
     * TM_SQDIFF_NORMED -- 归一化平方差匹配
     * TM_CCORR -- 相关匹配
     * TM_CCORR_NORMED -- 归一化相关匹配
     * TM_CCOEFF -- 系数匹配
     * TM_CCOEFF_NORMED -- 归一化的系数匹配
    */
    normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());

    //定位最佳匹配位置
    double min_value, max_value;
    Point min_location, max_location, match_location;
    minMaxLoc(dst, &min_value, &max_value, &min_location, &max_location);

    //有的方法是数值越小越精准，有的则相反
    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
        match_location = min_location;
    else
        match_location = max_location;

    rectangle(src, match_location, Point(match_location.x + template_img.cols, match_location.y + template_img.rows), Scalar(0, 0, 255), 2, 8, 0);
    rectangle(dst, match_location, Point(match_location.x + template_img.cols, match_location.y + template_img.rows), Scalar(0, 0, 255), 8, 0);

    imshow("dst", dst);
    imshow("raw", src);
}