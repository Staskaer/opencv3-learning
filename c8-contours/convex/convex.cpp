/*
 * 寻找图像的凸包
 * 凸包是几何上能够包围图像的凸多边形
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    RNG &rng = theRNG();
    //是线程安全的一个方法
    Mat img(600, 600, CV_8UC3);

    while (1)
    {
        char key;
        int count = (unsigned)rng % 100 + 3;
        vector<Point> points;

        for (int i = 0; i < count; i++)
        {
            Point point;
            point.x = rng.uniform(img.cols / 4, img.cols / 4 * 3);
            point.y = rng.uniform(img.rows / 4, img.rows / 4 * 3);

            points.push_back(point);
        }

        vector<int> hull;
        convexHull(Mat(points), hull, true);
        /*
         * 寻找凸包的函数
         * 第一个参数是二维点集，可以用Mat 或 vector
         * 第二个参数是找到的凸包
         * 第三个参数为true时输出为顺时针方向，否则为逆时针方向
         * 第四个参数时输出指示符
         * 当为true时返回所有凸包的点，否则为指数（默认true）
         * 当输出为vector时此项被忽略
        */

        img = Scalar::all(0);
        for (auto point : points)
            circle(img, point, 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

        //int hullcount = (int) hull.size();
        Point point0 = points[hull[hull.size() - 1]];

        for (auto x : hull)
        {
            Point point = points[x];
            line(img, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
            point0 = point;
        }

        imshow("img", img);
        key = waitKey();
        if (key == 27)
            break;
    }
}