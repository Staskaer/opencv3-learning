/*
 * ѧϰʹ��canny/sobel/laplacian���Ӻ�scharr�˲������б�Ե���
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void canny_edge();     //canny����ʹ��
void sobel_edge();     //sobel����ʹ��
void laplacian_edge(); //laplacian����ʹ��
void scharr_filter();  //scharr�˲�����ʹ��

int main()
{
    scharr_filter();
}

void canny_edge()
{
    //ʹ��canny���Ӽ���Ե
    Mat img = imread("lena.jpg", IMREAD_COLOR), gray, mask, dst;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    blur(gray, mask, Size(3, 3));
    Canny(mask, mask, 3, 9, 3);
    /*
     * cannyֻ�����ڻҶ�ͼ����Ӧ�����˲�
    */
    img.copyTo(dst, mask);
    //copyTo����copyʱʹ����ģ
    imshow("img", dst);
    waitKey(-1);
}

void sobel_edge()
{
    /*
     * sobel������һ�����ڼ���Ե����ɢ����
     * ��ͼ���x��y�����Ϸֱ��󵼣�����ͼ��ͻ�����С�ĺ��������
     * Ȼ�󽫵����ϲ�
    */

    Mat img = imread("lena.jpg", IMREAD_COLOR), grad_x, grad_y, dst;
    Mat abs_grad_x, abs_grad_y;
    Sobel(img, grad_x, CV_16S, 1, 0);
    /*
     * ���㷨������������x,y�����ϵĵ���
     * ǰ����������������
     * ��������������ȣ�һ�������¶�Ӧ��ϵ
     * CV_8U --->-1/CV_16S/CV_32F/CV_64F
     * CV_16U/CV_16S --->-1/CV_32F/CV_64F
     * CV_32F --->-1/CV_32F/CV_64F
     * CV_64F --->-1/CV_64F
     * ���ġ����������dx��dy����x��y�����ϵĵ�������
     * �����������Ǻ˳ߴ�Ϊ1��3��5��7��һ��
     * ���߸��������������ӣ�һ�㲻����
     * �ڰ˸�������deltaֵ���Ǵ����dst֮ǰ��ʹ�õ�
     * �ھŸ������Ǳ߽磬����
     * 
     * һ�㶼��ksize*ksize����Ϊ�˳ߴ磬����ksize=1ʱ����ʱ��1*3�ľ����Ҳ����и�˹ģ��
     * һ����dx=1��dy=0������x�����ϵ�����dx=0��dy=1������y�����ϵĵ���
    */
    Sobel(img, grad_y, CV_16S, 0, 1);
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
    imshow("raw", img);
    imshow("x", abs_grad_x);
    imshow("y", abs_grad_y);
    imshow("dst", dst);
    waitKey(-1);
}

void laplacian_edge()
{
    /*
     * laplacian���Ӷ��壺laplace(f) = d2f/dx2 + d2f/dy2
     * ����ʹ����ͼ���ݶȣ������ڲ�����sobelʵ�ֵ�
    */

    Mat img = imread("lena.jpg", IMREAD_COLOR), gray, dst, absdst;
    GaussianBlur(img, gray, Size(3, 3), 0, 0);

    cvtColor(gray, gray, COLOR_BGR2GRAY);

    Laplacian(gray, dst, CV_16S, 3, 1, 0);
    /*
     * ǰ�����������������
     * �������������������ȣ�������Ķ�Ӧ��ϵ��ͬ��
     * ���ĸ�������ksize�����ڼ�����׵��˲����ĳߴ�
     * �����������scale����ѡ�ı�������
     * ������������delta���ڴ���dst֮ǰʹ��
     * ���߸������Ǳ߽�����
    */

    convertScaleAbs(dst, absdst);
    //��ȡ����ֵ���������ת����8λ

    imshow("dst", absdst);
    waitKey(-1);
}

void scharr_filter()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    Mat grad_x, grad_y, abs_grad_x, abs_grad_y;

    Scharr(img, grad_x, CV_16S, 1, 0, 1, 0); //x������
    /*
     * ǰ��������������������������
     * ���ĸ�������x�����ϵĵ�������
     * �������y�����ϵ�������
     * ����������������
     * ���߸���deltaֵ
     * �ڰ˸��±߽�
     */
    convertScaleAbs(grad_x, abs_grad_x);

    Scharr(img, grad_y, CV_16S, 0, 1, 1, 0); //y������
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

    imshow("x", abs_grad_x);
    imshow("y", abs_grad_y);
    imshow("dst", dst);
    waitKey(-1);
}