/*
*���ļ���Ҫ�ǲü��ͺϳɵ�ͼ��Ĳ���
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

    //Ҳ����
    //imageROI = pic2(Range(0, pic1.rows ), Range(0, pic1.cols - 500));
    //(y,h)(x,w)

    addWeighted(imageROI, 0.5, pic1, 0.3, 0., imageROI);
    //������ͼƬ��ϣ�ǰ�ĸ������ǵ�һ����ͼ��Ȩ�أ��ڶ���ͼ��Ȩ��
    //�����������gamma������ͼһ�����ͺ���ӵ�Ȩֵ����Ҫ̫��
    //���һ�����������

    imshow("roi", imageROI);
    waitKey(-1);
    destroyAllWindows();

    system("pause");
}