/*          
 * 学习漫水填充算法
 *漫水填充就是选择一个像素，然后将所有和这个点颜色相同的像素全部替换成新的颜色
 * 类似魔棒
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg"), mask;
    mask = Mat::zeros(img.rows + 2, img.cols + 2, CV_8UC1);
    //此处掩模要大一点
    imshow("raw", img);
    Rect ccomp;
    floodFill(img, mask, Point(50, 50), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20), FLOODFILL_FIXED_RANGE | 8);
    /* 
     * 满水填充算法参数：
     * 第一个是操作图像，第二个是掩模
     * 第三个是取样点
     * 第四个是新绘制像素的颜色
     * 第五个是可选参数，设置绘制区域最小的矩形值
     * 第六个是允许的颜色之差最大负值
     * 第七个是允许的颜色之差最大正值
     * 第八个是操作位标识符：
     * 低八位（0--7位）控制算法连通性，可取4或8。
     * 4代表只考虑像素上下左右的连通区域，8额外增加对角线区域
     * 高八位（16--23位）可以取标识符或0
     * FLOODFILL_FIXED_RANGE：设置时考虑当前像素与种子像素之差，
     * 否则考虑相邻的像素与当前像素之差（即范围是浮动的）
     * FLOODFILL_MASK_ONLY：设置时只会在掩模中填充，不涉及原图像
     * 中间八位是掩模中填充的像素值，全为0时填充1
     * 
     * 可以用|进行设置多位
     */
    imshow("floodfill", img);
    waitKey(-1);
}