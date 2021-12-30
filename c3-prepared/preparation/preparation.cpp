//记录opencv c++编程的基本操作
//读取图片，Mat数组，显示
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void create_alpha_mat(Mat &mat)
{
    for (int i = 0; i < mat.rows; i++)
        for (int j = 0; j < mat.cols; j++)
        {
            Vec4b &rgba = mat.at<Vec4b>(i, j);
            //Vec4b 是 Vec<uchar, 4>的typedef,有4个uchar
            //如果是rgb可以用Vec3b,类似的还有Vec3f，Vec3s
            //at函数要带上存储类型名称
            rgba[0] = UCHAR_MAX;
            //blue通道最大值
            rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
            //这是防止溢出的函数，uint8与uchar同大小
            //将超过type_max的转换成type的max，否则不变
        }
}

int main()
{
    Mat pic(480, 640, CV_8UC4, Scalar());
    //CV_8UC4: 8位，uint，4通道
    //CV_[bit][U|S|F]C[channel] 其中usf分别是无符号，符号和浮点
    //Scalar(B,G,R,A):分别对应颜色和alpha通道，通道0为全透，255为不透
    create_alpha_mat(pic);
    //创建空mat数组,带alpha通道

    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    //写入参数
    try
    {
        imwrite("alpha.png", pic, compression_params);
        imshow("alpha", pic);
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << '\n';
        cout << "err";
    }

    Mat image = imread("lena.jpg", IMREAD_COLOR);
    /*
    *imread函数：第一个是路径
    *第二个参数flag有多个取值，可以传入int或定义的枚举
    *多个位用 | 隔开
    *IMREAD_ANYCOLOR | IMREAD_ANYDEPTH 是传入无损图像
    *flags传入负值可以载入alpha通道，默认是不载入的
    */

    namedWindow("show", WINDOW_NORMAL);
    /*
    *WINDOW_AUTOSIZE表示自动设置大小，用户不能更改
    *WINDOW_NORMAL表示用户可以手动设置大小
    */

    imshow("show", image);
    waitKey(-1);
    destroyAllWindows();
    /*
    *imshow函数第一个参数是输出窗口的id
    *如果窗口是默认值创建的，则显示原始尺寸，否则将进行缩放
    *缩放原则：uint8 -- 原始尺寸
    *uint16或uint32 -- 将[0，255*256]映射到[0,255]
    *float32 -- 将[0,1]映射到[0，255]
    */

    system("pause");
}