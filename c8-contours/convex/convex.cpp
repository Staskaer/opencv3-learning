/*
 * Ѱ��ͼ���͹��
 * ͹���Ǽ������ܹ���Χͼ���͹�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    RNG &rng = theRNG();
    //���̰߳�ȫ��һ������
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
         * Ѱ��͹���ĺ���
         * ��һ�������Ƕ�ά�㼯��������Mat �� vector
         * �ڶ����������ҵ���͹��
         * ����������Ϊtrueʱ���Ϊ˳ʱ�뷽�򣬷���Ϊ��ʱ�뷽��
         * ���ĸ�����ʱ���ָʾ��
         * ��Ϊtrueʱ��������͹���ĵ㣬����Ϊָ����Ĭ��true��
         * �����Ϊvectorʱ�������
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