/*
 * ���ļ�ѧϰѰ������������
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

Mat img = imread("home.jpg", IMREAD_COLOR), gray, dst;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
int thres = 80;
RNG rng(123456);

void on_thres_change(int, void *);

int main(int argc, char *argv[])
{
    namedWindow("img", WINDOW_AUTOSIZE);
    system("color 1f");

    cvtColor(img, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    createTrackbar("thres", "img", &thres, 255, on_thres_change);
    on_thres_change(0, 0);
    waitKey(-1);
}

void on_thres_change(int, void *)
{
    Canny(gray, dst, thres, thres * 2, 3);

    findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    /*
     * Ѱ�������ĺ���
     * ��һ�����������룬Ҫ�Ƕ�ֵ���ĻҶ�ͼ��
     * �ڶ���������������ÿ��������һ����������vector<vector<Point>>���ͣ�
     * �����������ǿ�ѡ����������������������˽ṹ����һ����Ԫ��
     * ����hierarchy[i][0-3]�ֱ��Ӧ��һ����ǰһ����������Ƕ����
     * ���ĸ���������������ģʽ
     * RETR_EXTERNAL -- ֻ���������֣���hierarchy[i][2-3]Ϊ-1
     * RETR_LIST -- ��ȡ����������������list�У����������ȼ���ϵ
     * RETR_CCOMP -- ��ȡ������������������֯�ṹΪ˫��ṹ�����Ϊ�߽磬�ڲ�Ϊ�ף�
     * RETR_TREE -- ��ȡ������������������״�ṹ
     * ������������������Ʒ���
     * CHAIN_APPROX_SIMPLE -- ѹ��ˮƽ����ֱ���Խ��߷���ֻ���������յ�����
     * CHAIN_APPROX_NONE -- ��ȡ����ÿ�����أ������������ز����1
     * CHAIN_APPROX_TC89_L1��CHAIN_APPROX_TC89_KCOS -- ���ƽ��㷨
     * ������������ÿ��������ƫ��ֵ������roi����ȡ������������ͼ���з���ʱ�õ�
    */

    Mat drawing = Mat::zeros(dst.size(), CV_8UC3);

    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        /*
         * ��һ�����������
         * �ڶ���������ȫ�������ļ���
         * �����������ǻ��Ƶ���������Ϊ��ֵʱ������������
         * ���ĸ�������������ɫ
         * ����������Ǵ�ϸ
         * �������������ߵ�����
         * 8/4 -- 8/4��ͨ��
         * LINE_AA -- �������
         * ���߸�����ʱ���˽ṹ
         * �ڰ˸�����ʱ���Ƶ��������ȼ�
         * �ھŸ�����ʱ��ƫ��ֵ
        */
    }
    imshow("img", drawing);
}