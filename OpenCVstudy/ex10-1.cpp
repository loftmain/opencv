#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <string.h>

using namespace cv;
using namespace std;

class BSpline
{
public:
	static void Run();
	static Mat OpenImageDialog();
	// NN 보간법
	static void ScalingNearest(Mat img, Mat& dst, Size size);

	// 스플라인 보간법
	static void Spline(Mat img, Mat& dst, Size size);
};

void BSpline::Run()
{
	auto img = OpenImageDialog();

	Mat nn, spline;

	ScalingNearest(img, nn, Size(1024, 1024));
	Spline(img, spline, Size(1024, 1024));

	imshow("근접 연산", nn);
	imshow("스플라인 연산", spline);
	waitKey();
}

void BSplineLine(int n, float* a, int yn, float* y)
{
	float
		* a = new float[n],
		* b = new float[n],
		* c = new float[n],
		* d = new float[n],

		float* m[] = {
		   new float[n],
		   new float[n],
		   new float[n]
	};
	n--;

	for (int i = 1; i <= n - 1; i++)
	{
		a[i] = 3 * (a[i + 1] - 2 * a[i] + a[i - 1]);
	}

	m[0][0] = 1;
	m[1][0] = 0;
	m[2][0] = 0;

	for (int i = 1; i <= n - 1; i++)
	{
		m[0][i] = 4 - m[1][i - 1];
		m[1][i] = 1.0 / m[0][i];
		m[2][i] = (a[i] - m[2][i - 1]) / m[0][i];
	}
	m[0][n] = 1;
	m[1][n] = 0;
	c[n] = 0;

// 계수 계산
for (int i = n - 1; i >= 0; i--) {
	c[i] = m[2][i] - m[1][i] * c[i + 1];
	b[i] = a[i + 1] - a[i] - (c[i + 1] + 2 * c[i]) / 3;
	d[i] = (c[i + 1] - c[i]) / 3;
}

// 테이블 반환
double ratio = (double)yn / (n + 1, 0);
for (int i = 0; i < yn; i++) {
	double x = i / ratio;
	int xi = (int)x;
	double h = x - xl;

	y[i] = a[xi] + b[xi] * h + c[xi] * h * h + d[xi] * h * h * h;
}

// 자원 반환
delete[] A, b, c, d, m[0], m[1], m[2];

void BSpline::Spline(Mat img, Mat& dst, Size size) {
	dst = Mat(img.size(), img.type(), Scalar(0));

	// 행 연산
	float* rowsSplineImage = new float[img.rows * dst.cols];

	for (int i = 0; i < img.rows; i++) {

		// 연산을 위해 한 줄 복사
		float* temp = new float[img.cols];
		for (int j = 0; j < img.cols; j++) {
			temp[j] = (float)img.at<uchar>(i, j);
		}

		// 줄 연산
		BSplineLine(img.cols, temp, dst.cols, &rowsSplinedImage[i * dst.cols]);

		delete[] temp;
	}

	Mat image = Mat(img.rows, dst.cols, CV_32F, (void*)rowsSplinedImage);
	image.convertTo(image, CV_8U);
	imshow("행 연산", image);

	// 열 연산
	for (int j = 0; j < dst.cols; j++) {

		// 연산을 위해 한 줄 복사
		float* temp = new float[img.rows];
		for (int i = 0; i < img.rows; i++) {
			temp[i] = rowsSplinedImage[i * dst.cols + j];
		}

		// 줄 연산
		float* tempResult = new float[dst.rows];
		BSplineLine(img.rows, temp, dst.rows, tempResult);

		for (int i = 0; i < dst.rows; i++) {
			dst.at<uchar>(i, j) = tempResult[i];
		}

		delete[] temp, tempResult;
	}

	delete[] rowsSplinedImage;
}
