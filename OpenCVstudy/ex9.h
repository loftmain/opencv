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
	// 평행 위치 이동
	static void Translation(Mat img, Mat& dst, Point pt);
	// 원점 기준 회전 변환
	static void Rotation(Mat img, Mat& dst, double dgree);

	// 기본 보간법
	static void Scaling(Mat img, Mat& dst, Size size);
	// NN 보간법
	static void ScalingNearest(Mat img, Mat& dst, Size size);
	// 양선형 보간법
	static uchar BilinearValue(Mat img, double x, double y);
	static void ScalingBilinear(Mat img, Mat& dst, Size size);
};
