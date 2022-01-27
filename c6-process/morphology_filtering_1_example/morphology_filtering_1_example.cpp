/*
 * 膨胀和腐蚀的综合例子
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void change(int p, void *temp);

Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
int type = 0, kernal = 3, iteration = 1;
int main()
{

    namedWindow("show", 1);

    createTrackbar("dilate/erode", "show", &type, 1, change);
    createTrackbar("kernal", "show", &kernal, 30, change);
    createTrackbar("iteration", "show", &iteration, 5, change);

    imshow("show", img);
    waitKey(-1);
}
void change(int p, void *temp)
{
    Mat element = getStructuringElement(MORPH_RECT, Size(kernal + 1, kernal + 1));
    if (type)
        erode(img, dst, element, Point(-1, -1), iteration);
    else
        dilate(img, dst, element, Point(-1, -1), iteration);
    imshow("show", dst);
}
