#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <string.h>

using namespace cv;
using namespace std;

class ex9
{
public:
	static void Run();

	static Mat OpenImageDialog();
	// ���� ��ġ �̵�
	static void Translation(Mat img, Mat& dst, Point pt);
	// ���� ���� ȸ�� ��ȯ
	static void Rotation(Mat img, Mat& dst, double dgree);

	// �⺻ ������
	static void Scaling(Mat img, Mat& dst, Size size);
	// NN ������
	static void ScalingNearest(Mat img, Mat& dst, Size size);
	// �缱�� ������
	static uchar BilinearValue(Mat img, double x, double y);
	static void ScalingBilinear(Mat img, Mat& dst, Size size);
};
