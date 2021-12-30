//��¼opencv c++��̵Ļ�������
//��ȡͼƬ��Mat���飬��ʾ
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
            //Vec4b �� Vec<uchar, 4>��typedef,��4��uchar
            //�����rgb������Vec3b,���ƵĻ���Vec3f��Vec3s
            //at����Ҫ���ϴ洢��������
            rgba[0] = UCHAR_MAX;
            //blueͨ�����ֵ
            rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
            //���Ƿ�ֹ����ĺ�����uint8��ucharͬ��С
            //������type_max��ת����type��max�����򲻱�
        }
}

int main()
{
    Mat pic(480, 640, CV_8UC4, Scalar());
    //CV_8UC4: 8λ��uint��4ͨ��
    //CV_[bit][U|S|F]C[channel] ����usf�ֱ����޷��ţ����ź͸���
    //Scalar(B,G,R,A):�ֱ��Ӧ��ɫ��alphaͨ����ͨ��0Ϊȫ͸��255Ϊ��͸
    create_alpha_mat(pic);
    //������mat����,��alphaͨ��

    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    //д�����
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
    *imread��������һ����·��
    *�ڶ�������flag�ж��ȡֵ�����Դ���int�����ö��
    *���λ�� | ����
    *IMREAD_ANYCOLOR | IMREAD_ANYDEPTH �Ǵ�������ͼ��
    *flags���븺ֵ��������alphaͨ����Ĭ���ǲ������
    */

    namedWindow("show", WINDOW_NORMAL);
    /*
    *WINDOW_AUTOSIZE��ʾ�Զ����ô�С���û����ܸ���
    *WINDOW_NORMAL��ʾ�û������ֶ����ô�С
    */

    imshow("show", image);
    waitKey(-1);
    destroyAllWindows();
    /*
    *imshow������һ��������������ڵ�id
    *���������Ĭ��ֵ�����ģ�����ʾԭʼ�ߴ磬���򽫽�������
    *����ԭ��uint8 -- ԭʼ�ߴ�
    *uint16��uint32 -- ��[0��255*256]ӳ�䵽[0,255]
    *float32 -- ��[0,1]ӳ�䵽[0��255]
    */

    system("pause");
}