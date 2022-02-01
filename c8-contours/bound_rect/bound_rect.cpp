/*
 * ���ļ�ѧϰ���ʹ�ö���ν�ͼ���Χ
 * ���ò�ͬ����״ȥ��϶�ά�㼯�ĺ���
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void bound_rect(Mat points, Mat &img);   //�þ���ȥ���
void bound_rect_r(Mat points, Mat &img); //����ת�ľ���ȥ���
void min_circle(Mat points, Mat &img);   //��Բȥ���
void fit_ellipse(Mat points, Mat &img);  //����Բȥ���

void on_do(int type, void *);

int main()
{

    RNG &rng = theRNG();
    //���̰߳�ȫ��һ������
    Mat img(600, 600, CV_8UC3);
    vector<Mat *> data = {&img};
    namedWindow("img");
    int type = 0;
    createTrackbar("type", "img", &type, 3, on_do, data.data());
    //��������

    while (1)
    {
        //�ȳ�ʼ����
        char key;
        int count = (unsigned)rng % 100 + 10;
        vector<Point> points;

        for (int i = 0; i < count; i++)
        {
            Point point;
            point.x = rng.uniform(img.cols / 4, img.cols / 4 * 3);
            point.y = rng.uniform(img.rows / 4, img.rows / 4 * 3);

            points.push_back(point);
        }

        //���Ƶ�
        img = Scalar::all(0);
        for (auto point : points)
            circle(img, point, 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

        //��ʾ���ûص�����
        Mat p = (Mat)points;
        data[1] = &p;
        on_do(type, data.data());

        key = waitKey();
        if (key == 27)
            break;
    }
}

void bound_rect(Mat points, Mat &img)
{
    Rect rect = boundingRect(points);
    /*
     * �˺���ʱѰ����С��Χ�ľ��εĺ���
     * ����һ�����룬Ϊ�㼯��������mat��vector
    */

    rectangle(img, rect, Scalar(123, 42, 84), 2);
    imshow("img", img);
}

void bound_rect_r(Mat points, Mat &img)
{

    RotatedRect rect = minAreaRect(points);
    /*
     * ͬ��ֻ��һ������㼯
     * ��Ҫ�������mat����ֻ��������
    */

    Point2f vex[4];
    rect.points(vex);

    for (int i = 0; i < 4; i++)
    {
        line(img, vex[i], vex[(i + 1) % 4], Scalar(123, 31, 186), 2, LINE_AA);
    }
    imshow("img", img);
}

void min_circle(Mat points, Mat &img)
{
    Point2f center;
    float r;
    minEnclosingCircle(points, center, r);
    /*
     * Ѱ����СԲ
     * ���롢Բ�ġ��뾶
    */

    circle(img, center, r, Scalar(123, 54, 185), 2, LINE_AA);
    imshow("img", img);
}

void fit_ellipse(Mat points, Mat &img)
{
    RotatedRect box = fitEllipse(points);
    /*
     * ����Բ���
    */
    ellipse(img, box, Scalar(54, 74, 63));
    imshow("img", img);
}

void on_do(int type, void *meta)
{
    Mat img = *((Mat **)meta)[0], points = *((Mat **)meta)[1];
    switch (type)
    {
    case 0:
        bound_rect(points, img);
        break;
    case 1:
        bound_rect_r(points, img);
        break;
    case 2:
        min_circle(points, img);
        break;
    case 3:
        fit_ellipse(points, img);
        break;
    }
}