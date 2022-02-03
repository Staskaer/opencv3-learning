/*
 * 绘制直方图
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void calc_hist_2d();  //计算二维分布直方图
void calc_hist();     //计算一维分布直方图
void calc_hist_rgb(); //计算rgb三通道的分布直方图

int main()
{
    calc_hist_rgb();
}

void calc_hist_2d()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR);
    cvtColor(img, img, COLOR_BGR2HSV);

    int hue_bin_num = 30;        //设置直方图直条数目
    int saturation_bin_num = 32; //饱和度直方图直条数目
    int hist_size[] = {hue_bin_num, saturation_bin_num};

    float hue_range[] = {0, 180};        //设置色调变换范围
    float saturation_range[] = {0, 256}; //设置饱和度变化范围0-255
    const float *ranges[] = {hue_range, saturation_range};
    MatND hist;
    /*
     * MatND表示多维数组（大于等于三维）
     * 可以用Mat代替
    */
    int channels[] = {0, 1}; //第0和第1通道直方图

    calcHist(&img, 1, channels, Mat(), hist, 2, hist_size, ranges, true, false);
    /*
     * 计算一个或者多个阵列的直方图
     * 第一个参数是输入的数组或数组集（地址）（要求尺寸和深度相同）
     * 第二个参数是输入数组的个数，即第一个参数内有几张图像
     * 第三个参数是需要统计的通道的索引
     * 第四个参数是掩模（8位同尺寸）
     * 第五个参数是输出数组，是一个二维数组
     * 第六个参数是计算直方图的维度，必须是正数
     * 第七个参数是每个维度下的直方图尺寸
     * 第八个参数是每一个维度的取值范围
     * 第九个参数是指示直方图是否均匀的flag
     * 第十个参数是累计标识符，用于在多个阵列中计算单个直方图
    */

    double max_value = 0;
    minMaxLoc(hist, 0, &max_value, 0, 0);
    /*
     * 查找最大和最小值
     * 第一个参数是输入的直方图数组
     * 第二个参数是返回最小值的指针，若不返回则设为0
     * 第三个参数是返回最大值的指针，若不返回则设为0
     * 第四个参数是返回最小位置的指针
     * 第五个参数是返回最大位置的指针
     */
    int scale = 10;
    Mat hist_img = Mat::zeros(saturation_bin_num * scale, hue_bin_num * 10, CV_8UC3);

    for (int hue = 0; hue < hue_bin_num; hue++)
        for (int saturation = 0; saturation < saturation_bin_num; saturation++)
        {
            float bin_value = hist.at<float>(hue, saturation);
            int intensity = cvRound(bin_value * 255 / max_value);

            rectangle(hist_img, Point(hue * scale, saturation * scale), Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1), Scalar::all(intensity), FILLED);
        }

    imshow("img", hist_img);
    waitKey(-1);
}

void calc_hist()
{
    Mat img = imread("lena.jpg", 0);
    MatND hist;
    int dims = 1;
    float hranges[] = {0, 255};
    const float *ranges[] = {hranges};
    int size = 256;
    int channels = 0;
    int scale = 1;

    calcHist(&img, 1, &channels, Mat(), hist, dims, &size, ranges);
    //计算直方图

    Mat dst(size * scale, size, CV_8U, Scalar(0));

    double max_value = 0, min_value = 0;
    minMaxLoc(hist, &min_value, &max_value, 0, 0);

    int hpt = saturate_cast<int>(0.9 * size);
    for (int i = 0; i < 256; i++)
    {
        float bin_value = hist.at<float>(i);
        int real_value = saturate_cast<int>(bin_value * hpt / max_value);
        rectangle(dst, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - real_value), Scalar(255));
    }
    imshow("dst", dst);
    waitKey(-1);
}

void calc_hist_rgb()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR);

    // for (int i = 0; i < img.rows; i++)
    //     for (int j = 0; j < img.cols; j++)
    //         (img.at<Vec3b>(i, j))[0] = 0;
    //以上代码可以测试绘制是否正确（通过将某通道全部置为0）

    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0, 256};
    const float *ranges[] = {range};
    MatND hist_r, hist_g, hist_b;

    //先计算红色直方图
    int channels_r[] = {2};
    calcHist(&img, 1, channels_r, Mat(), hist_r, 1, hist_size, ranges, true, false);

    //计算绿色直方图
    int channels_g[] = {1};
    calcHist(&img, 1, channels_g, Mat(), hist_g, 1, hist_size, ranges, true, false);

    //计算蓝色直方图
    int channels_b[] = {0};
    calcHist(&img, 1, channels_b, Mat(), hist_b, 1, hist_size, ranges, true, false);

    //*******绘制
    double max_r = 0, max_b = 0, max_g = 0;
    minMaxLoc(hist_r, 0, &max_r, 0, 0);
    minMaxLoc(hist_g, 0, &max_g, 0, 0);
    minMaxLoc(hist_b, 0, &max_b, 0, 0);
    int scale = 1;
    int hist_height = 256;
    Mat dst = Mat::zeros(hist_height, bins * 3, CV_8UC3);

    //正式开始绘制
    for (int i = 0; i < bins; i++)
    {
        float value_r = hist_r.at<float>(i);
        float value_g = hist_g.at<float>(i);
        float value_b = hist_b.at<float>(i);

        //高度
        int intensity_r = cvRound(value_r * hist_height / max_r);
        int intensity_g = cvRound(value_g * hist_height / max_g);
        int intensity_b = cvRound(value_b * hist_height / max_b);

        //绘制矩形
        rectangle(dst, Point(i * scale, hist_height - 1), Point((i + 1) * scale - 1, hist_height - intensity_r), Scalar(0, 0, 255));
        rectangle(dst, Point((i + bins) * scale, hist_height - 1), Point((i + 1 + bins) * scale - 1, hist_height - intensity_g), Scalar(0, 255, 0));
        rectangle(dst, Point((i + 2 * bins) * scale, hist_height - 1), Point((i + 1 + 2 * bins) * scale - 1, hist_height - intensity_b), Scalar(255, 0, 0));
    }

    imshow("dst", dst);
    waitKey(-1);
}