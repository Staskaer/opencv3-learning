/*
*ѧϰ�������Ĵ�����ʹ��
*ʹ�ù켣������alphaͨ�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

//ȫ�ֱ�������
const int MAX_ALPHA_VALUE = 100;

void show_bar(int bar, void *temp)
{
    double alpha_value, beta_value;
    alpha_value = double(bar) / MAX_ALPHA_VALUE;
    //��Ŀ��ֵȥ������ֵ�õ�����
    beta_value = 1.0 - alpha_value;
    //��һ�������

    //���û������л�ȡ���ݵ�����
    Mat **tuple = (Mat **)temp;
    //temp��ָ��ָ�������һ��ָ��
    Mat pic1 = *tuple[0];
    Mat pic2 = *tuple[1];
    Mat dst = *tuple[2];

    addWeighted(pic1, alpha_value, pic2, beta_value, 0., dst);
    imshow("result", dst);

    //getTrackbarPos((char *)temp, "image_show");
    //����������ش����й켣������ֵ
    //���ã�
}

int main(int argc, char *argv[], char **env)
{
    //�Ȼ�ȡͼ��
    Mat pic1 = imread("left.jpg", IMREAD_COLOR), pic2 = imread("right.jpg", IMREAD_COLOR), dst;
    vector<Mat *> tup = {&pic1, &pic2, &dst};
    //��ͼ��ָ�봫��

    //�����ʼֵ
    int bar = 70;
    //Ϊ���������ʹ�������
    char name[50];
    sprintf(name, "͸��ֵ %d", MAX_ALPHA_VALUE);
    namedWindow("image_show");

    createTrackbar(name, "image_show", &bar, 100, show_bar, tup.data());
    /*
    *����������Դ����켣��
    *��һ�������ǹ켣�����֣��ڶ��������ǹ켣�������Ĵ���
    *�����������ǹ켣����ʼֵ����һ��int *����
    *���ĸ������ǻ������ֵ����Сֵʼ����0
    *����������ǻص�����ָ�룬ÿ�λ���仯����ִ�лص�����
    *�ص����������� void xxxx(int ,void *)���ͻ�null����
    *�ص�������һ�������ǻ���λ�ã��ڶ����������û�����(�����棬������������)
    *�������������û����ݣ��ᴫ�ݸ��ص������ĵڶ�������
    */
    waitKey(-1);
    destroyAllWindows();
}