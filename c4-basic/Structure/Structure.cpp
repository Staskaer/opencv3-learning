/*
*���ļ�ѧϰ����ͼ������Mat,��һϵ�еĻ������ݽṹ��ʹ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void mat(void);    //mat����
void point(void);  //point��ṹ����
void scalar(void); //scalar��ɫ���˵��
void size(void);   //size��˵��
void rect(void);   //rect������
void cvt(void);    //��ɫת������cvtcolor

int main(int argc, char *argv[])
{
     cvt();
}

void mat(void)
{
     /*
    *mat���һЩ˵��
    *mat����ڲ��ṹ����һ������ͷ����������ߴ磬�洢��������ַ����Ϣ��
    *��һ��ָ��洢�����ָ����ɡ�����ͷͨ���ǳ�ֵ������������һ��
    *ÿ��mat�ľ���ͷ����ı䣬����ͬһ������
    *��ֻ�ı����ָ�룬�����ƾ�����

    *��������Ҫ������ʱ�������һ��mat����ͷ��������ڴ�
    *����������ָ��
    */

     Mat A, C;                             //�˴�ֻ��������ͷ
     A = imread("lena.jpg", IMREAD_COLOR); //Ϊ��������ڴ�
     Mat B(A);                             //�������(�������캯��)
     C = A;
     rectangle(C, Rect(0, 0, 200, 200), Scalar(255, 255, 0));
     //��c�ϵĸ���������A��

     Mat F, G; //��ʱF,G�ĸı䲻��������A
     F = A.clone();
     A.copyTo(G);
     rectangle(F, Rect(200, 200, 300, 300), Scalar(255, 123, 255));
     rectangle(G, Rect(200, 200, 300, 300), Scalar(255, 123, 255));

     imshow("A", A);
     imshow("F", F);
     imshow("G", G);

     /******************
    ***Mat�ṹ�ĳ�ʼ��***
    ******************/

     Mat m(2, 2, CV_8UC3, Scalar(0, 255, 0));
     cout << "ʹ��cout��� ��\n"
          << m; //��������ֻ�Զ�ά������Ч

     //����������ά���飬����֪����ʲô��
     int sz[] = {2, 2, 2}; //�������ָ��ά���ĳߴ�
     Mat n(3, sz, CV_8UC3, Scalar::all(123));

     //ʹ��create����ʱ���ܳ�ʼ��ֵ��ֻ�ܿ��ٿռ�
     m.create(2, 2, CV_8UC(2));
     cout << endl
          << "create������ \n"
          << m << endl;

     //Ҳ����ʹ��matlab��񴴽�����ľ���
     Mat matlab1 = Mat::eye(4, 4, CV_64F);
     Mat matlab2 = Mat::ones(4, 4, CV_32F);
     Mat matlab3 = Mat::zeros(4, 4, CV_8UC1);
     cout << "matlab���eye��ones��zeros" << endl
          << matlab1 << endl
          << matlab2 << endl
          << matlab3 << endl;

     //С���ŷ�ʽ��ʼ����ʵ������������<<�ͣ������
     Mat s = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
     cout << "s : \n"
          << s << endl;

     //���п��Ե�������
     Mat clone = s.row(1).clone();
     cout << "clone\n"
          << clone << endl;

     /****************************
    **mat�������䷽���������ʽ**
    ****************************/

     //ʹ����������
     Mat r = Mat(3, 10, CV_8UC3);
     randu(r, Scalar::all(0), Scalar::all(255));
     cout << "\n\n\nr---c++\n"
          << r;

     //���python���
     cout << "\nr---python\n"
          << format(r, Formatter::FMT_PYTHON);

     //matlab���
     cout << "\nr---matlab\n"
          << format(r, Formatter::FMT_MATLAB);

     waitKey(-1);
}

void point(void)
{
     /*
     * opencv�е��ж�����֯��ʽ
     * ����point��point2i��typedef����Ϊpoint_<int>
     * �ж�ά�����ά�㣬��ά�㲻֪���Ǹ����
     * ��.x  .y������
     */

     //��ά��
     Point2f p2(6, 2);
     cout << "\n p2 \n"
          << p2;

     //��ά��
     Point3d p3(2, 5, 6);
     cout << "\n p3 \n"
          << p3;

     //����mat��vector
     vector<float> v{1, 2, 3};
     cout << "\nvector on mat \n"
          << Mat(v);

     //��vector��ŵ�����
     vector<Point2f> points(5);
     for (auto &point : points)
     {
          point = Point2f((float)rand(), (float)rand());
          cout << point << endl;
     }

     system("pause");
}

void scalar(void)
{
     /*
     * scalar������ɫ�࣬��4��Ԫ�أ���vec4x��һ������
     * Scalar��Scalar_<double>��typedef
     * 
    */
     Mat pic(100, 200, CV_8UC3, Scalar(0, 225, 123));
     imshow("pic", pic);
     waitKey(-1);
     destroyAllWindows();
}

void size(void)
{
     /*
     * Size���Ǵ洢�ߴ��
     * һ��ʹ��size��width,height��
    */
     Mat pic = imread("lena.jpg", IMREAD_COLOR);
     rectangle(pic, Rect(Point(0, 0), Point(100, 100)), Scalar(0, 255, 0), 1);
     rectangle(pic, Rect(Point(0, 0), Point(100, 100)) + Size(100, 100), Scalar(0, 255, 255), 2);
     imshow("pic", pic);
     waitKey(-1);
     system("pause");
}

void rect(void)
{
     /*
     * rect��ĳ�Ա������tl,br,width,height��
     * ���Խ��Point(),��Size()����ƽ�ƺ�����
    */
}

void cvt(void)
{
     Mat pic = imread("lena.jpg", IMREAD_COLOR);
     cvtColor(pic, pic, COLOR_BGR2RGB);
     imshow("hsv", pic);
     //imshow����ֻ�ܰ���bgr����ͨ��
     waitKey(-1);
     destroyAllWindows();
}