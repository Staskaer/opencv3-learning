/*
*本文件主要是裁剪和合成的图像的操作
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char *argv[], char **env)
{
    Mat pic1 = imread("pp3.jpg", IMREAD_COLOR);
    Mat pic2 = imread("pp2.webp", IMREAD_COLOR);

    Mat imageROI;
    imageROI = pic2(Rect(0, 0, pic1.cols - 500, pic1.rows));
    pic1 = pic1(Range(0, pic1.rows), Range(0, pic1.cols - 500));
    //(x,y,w,h)

    //也可以
    //imageROI = pic2(Range(0, pic1.rows ), Range(0, pic1.cols - 500));
    //(y,h)(x,w)

    addWeighted(imageROI, 0.5, pic1, 0.3, 0., imageROI);
    //将两张图片混合，前四个参数是第一个张图，权重，第二张图，权重
    //第五个参数是gamma，代表图一二做和后添加的权值，不要太大
    //最后一个参数是输出

    imshow("roi", imageROI);
    waitKey(-1);
    destroyAllWindows();

    system("pause");
}