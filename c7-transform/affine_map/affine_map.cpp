/*
 * ����任
 * ��һ��������������һ�����Ա任�پ���һ��ƽ�Ʊ任
 * ��Ϊ��һ�������ռ�Ĺ���
 * ������ƽֱ�ԣ�ֱ����Ȼ��ֱ�ߣ���ƽ���ԣ�ƽ������Ȼƽ�У�
 * 
 * ����任���Ա�ʾΪ ����*����+���� ����ʽ
 * ���Կ���������ͼ��֮�����ϵ
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int agrc, char *argv[])
{
    system("color 1A");

    Point2f src_t[3], dst_t[3]; //���Ƿ���任��Ӧ������

    Mat rot_mat(2, 3, CV_32FC1);
    Mat warp_mat(2, 3, CV_32FC1);
    Mat src, dst_warp, dst_warp_rot;
    src = imread("lena.jpg", IMREAD_COLOR);

    dst_warp = Mat::zeros(src.rows, src.cols, src.type());

    src_t[0] = Point2f(0, 0);
    src_t[1] = Point2f(static_cast<float>(src.cols - 1), 0);
    src_t[2] = Point2f(0, static_cast<float>(src.rows - 1));

    dst_t[0] = Point2f(static_cast<float>(src.cols * 0.0), static_cast<float>(src.rows * 0.33));
    dst_t[1] = Point2f(static_cast<float>(src.cols * 0.65), static_cast<float>(src.rows * 0.35));
    dst_t[2] = Point2f(static_cast<float>(src.cols * 0.15), static_cast<float>(src.rows * 0.6));

    warp_mat = getAffineTransform(src_t, dst_t);
    /*
     * ����任��Ҫ�õ���������ȷ���任����
     * �˺�������֪�任������任����
     * ����[a00,a01,a02;a10,a11,a12][1;x;y]����ƫ�ó�����
     * ���Ա任�������������е�
    */

    warpAffine(src, dst_warp, warp_mat, dst_warp.size());
    /*
     * ����任����dst(x,y) = src(a00 + a01 * x+a02 * y , a10 + a11 * x + a12 * y)
     * ��һ�����������룬�ڶ������������
     * �����������Ƿ���任����2*3��
     * ���ĸ�����������ĳߴ�
     * ����������ǲ�ֵ��ʽ��Ĭ�ϼ��ɣ�
     * �����������Ǳ߽�ģʽ
     * ���߸�����Ҳ�Ǳ߽����
    */

    //����������ת
    Point center = Point(dst_warp.cols / 2, dst_warp.rows / 2);
    double angle = -30.0;
    double scale = 0.8;

    rot_mat = getRotationMatrix2D(center, angle, scale);
    /*
     * ��������Ǽ����ά��ת�仯�������
     * ��һ����������ת����
     * �ڶ���������ת�Ƕ�
     * ��������������ϵ��
     * Ҳ�������ڷ���任����Ϊ��άƽ����ת���ž�����2*3�ĳߴ�
    */

    warpAffine(dst_warp, dst_warp_rot, rot_mat, dst_warp.size());

    imshow("raw", src);
    imshow("warp", dst_warp);
    imshow("warp_rot", dst_warp_rot);
    waitKey(-1);
}
