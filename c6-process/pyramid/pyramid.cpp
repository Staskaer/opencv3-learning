/*
 * ͼ�������
 * ͼ��������Ƕ�ߴ��﷽ʽ��һ��
 * ��Ҫ����ͼ��ָ��һ���Զ�ֱ��ʽ���ͼ�����Ч�ṹ
 * �������ĵײ��Ǹ߷ֱ��ʣ������ǵͷֱ��ʵĽ���
 * �и�˹��������������˹������
 * ǰ���������²����������������ϲ����ӵͷֱ���ͼ���ؽ�
 * 
 * ���������²�����ָͼ��ĳߴ磬������������෴�������߲��ǻ����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void resize_function();
void pyr_function();

int main()
{
    pyr_function();
}

void resize_function()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst1;

    resize(img, dst1, Size(img.cols * 2, img.rows * 2), 0, 0, INTER_NEAREST);
    /*
     * resize�����ǳߴ�任����
     * ǰ�����������������
     * �������Ǳ任�ĳߴ硢
     * ���ĵ�����x,y��������ߴ�
     * �����������ǲ�ֵ��ʽ
     * INSERT_NEAREST -- ���ڽ���ֵ
     * INSERT_LINEAR --���Բ�ֵ��Ĭ�ϣ�
     * INSERT_AREA -- �����ֵ
     * INSERT_CUBIC -- ����������ֵ
     * INSERT_LANCZOS4 -- lanczos��ֵ
     * ������С����������ֵ���Ŵ�������������ֵ�����������Բ�ֵ���죩
     * 
     * ���ÿ���resize(img,dst1,Size(purpose))
     * Ҳ����resize(img,dst1,Size(),fx,fy)
    */
    imshow("result", dst1);
    waitKey(-1);
}

void pyr_function()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst1, dst2;

    pyrUp(img, dst1, Size(img.cols * 2, img.rows * 2));
    /*
     * ���ϲ���
     * ��resize�ǳ�����
     * ���������������ͼ��ߴ�
    */
    imshow("dst1", dst1);
    pyrDown(dst1, dst2, Size(img.cols, img.rows));
    /*
     * ���²���
    */
    imshow("dst2", dst2);
    waitKey(-1);
}