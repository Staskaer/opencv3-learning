/*
 * 使用shi-tomasi方法进行角点检测
 * 是harris方法的改进
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, gray;
int max_corner_num = 30;
int max_trackbar_num = 500;
RNG rng(123456);

void on_good_feature_to_track(int, void *);

int main()
{
    img = imread("test.jpg", IMREAD_COLOR);
    cvtColor(img, gray, COLOR_BGR2GRAY);
    namedWindow("dst", WINDOW_FREERATIO);
    createTrackbar("max_num", "dst", &max_corner_num, max_trackbar_num, on_good_feature_to_track, 0);

    imshow("dst", img);
    on_good_feature_to_track(0, 0);
    waitKey(-1);
}

void on_good_feature_to_track(int, void *)
{
    max_corner_num = max_corner_num > 1 ? max_corner_num : 1;

    //参数准备
    vector<Point2f> corners;
    double quality_level = 0.01; //角点检测能接受的最小特征值
    double min_distance = 10;    //角点直接最小距离
    int blocksize = 3;           //计算导数自相关矩阵时指定的邻域范围
    double k = 0.04;
    Mat copy = img.clone();

    goodFeaturesToTrack(gray, corners, max_corner_num, quality_level, min_distance, Mat(), blocksize, false, k);

    printf("角点检测数目 : %d \n", corners.size());

    //绘制角点
    int r = 4;
    for (auto p : corners)
        //circle(copy, p, r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, LINE_AA, 0);
        circle(copy, p, r, Scalar(0, 0, 255), -1, LINE_AA, 0);

    imshow("dst", copy);
}