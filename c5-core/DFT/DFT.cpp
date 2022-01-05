/*
*���ļ�ѧϰ��ɢ����Ҷ�任
*/

/*========��ɢ����Ҷ�任ԭ��
*��ɢ����Ҷ�任��ͼ���ʱ����ת����Ƶ��
*��ʾת����ĸ���Ҷͼ����Ҫ�õ�����ͼ�����λͼ��
*���ڷ���ͼ������󲿷���Ҫ����Ϣ������ֻ��������
*������ͨ����任��ԭ������Ҫ��������ͼ��

*�任��Ŀ���ǰ�ԭʼͼ�������ȱ仯������Ĳ��ַֿ�
��ͨ�����Ҷ�ͼ����������зֱ𿴳ɲ�����ɢ��ֵ��
*���ȱ仯����Ե�Ƶ�������ף��仯����Ը�Ƶ��������
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void dft_test(void); //ʹ��dft

int main()
{
    Mat pic = imread("lena.jpg", 0);
    namedWindow("raw", 0);
    imshow("raw", pic);

    int m = getOptimalDFTSize(pic.rows);
    //�����������dft����ѳߴ�
    //���У��зֱ�����õ�dft��Ӧ�����гߴ磬��������size
    int n = getOptimalDFTSize(pic.cols);

    Mat padd;
    copyMakeBorder(pic, padd, 0, m - pic.rows, 0, n - pic.cols, BORDER_CONSTANT, Scalar::all(0));
    //�����������ͼ��߽磬Ŀ�������䵽���ĳߴ�
    //�м�4�������ֱ����top,bottom,left,right������ĳߴ�
    //���߸������Ǳ߽����ͣ�һ��ȡBORDER_CONSTANT
    //ʣ�µ���ɫһ����Ĭ��ֵ0

    //Ϊʵ���鲿����ռ�
    //��ԭ��ͼ���ϵ�ÿ��ֵ��dft���������ֵ��������ֵ�ܴ�Ҫ��float�洢
    Mat planes[] = {Mat_<float>(padd), Mat::zeros(padd.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI); //��planes�ϲ��ɶ�ͨ������

    dft(complexI, complexI);

    //�ٷֽ��ȥ,������ת���ɷ�ֵ
    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    //���������ǰ��������������ת���ɷ�ֵ
    Mat magnitudePic = planes[0];

    //����log�߶ȱ任,m = log(1+m)
    magnitudePic += Scalar::all(1);
    log(magnitudePic, magnitudePic);

    //���вü��ͷָ�ͼ��
    magnitudePic = magnitudePic(Rect(0, 0, magnitudePic.cols & -2, magnitudePic.rows & -2));

    int cx = magnitudePic.cols / 2;
    int cy = magnitudePic.rows / 2;

    Mat q0(magnitudePic, Rect(0, 0, cx, cy));   //����
    Mat q1(magnitudePic, Rect(cx, 0, cx, cy));  //����
    Mat q2(magnitudePic, Rect(0, cy, cx, cy));  //����
    Mat q3(magnitudePic, Rect(cx, cy, cx, cy)); //����

    Mat temp; //��������
    q0.copyTo(temp);
    q3.copyTo(q0);
    temp.copyTo(q3);

    q1.copyTo(temp);
    q2.copyTo(q1);
    temp.copyTo(q2);

    //��һ��
    normalize(magnitudePic, magnitudePic, 0, 1, NORM_MINMAX);

    imshow("dft", magnitudePic);

    waitKey(-1);
}
