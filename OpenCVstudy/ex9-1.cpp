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

Mat ex9::OpenImageDialog()
{
	char name[MAX_PATH] = { 0, };
	OPENFILENAMEA ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "�������(*.*)\0*.*\0";
	ofn.lpstrFile = name;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	Mat image = Mat();
	if (GetOpenFileNameA(&ofn)) {
		image = imread(name, IMREAD_GRAYSCALE);
		if (image.empty()) {
			cout << "���� �б� ����" << endl;
			exit(1);
		}
	}
	else {
		cout << "���� ���� ����" << endl;
		exit(1);
	}
	return image;
}

void ex9::Translation(Mat img, Mat& dst, Point pt)
{
	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar());

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			Point dstPt(j, i);
			Point imgPt = dstPt - pt;

			if (rect.contains(imgPt))
				dst.at<uchar>(dstPt) = img.at<uchar>(imgPt);
		}
	}
}

void ex9::Scaling(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}

void ex9::ScalingNearest(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / (img.rows - 1);
	double ratioX = (double)size.width / (img.cols - 1);

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int x = (int)cvRound(j / ratioX);
			int y = (int)cvRound(i / ratioY);
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}

uchar ex9::BilinearValue(Mat img, double x, double y)
{
	if (x >= img.cols - 1) x--;
	if (y >= img.rows - 1) y--;

	Point pt((int)x, (int)y);
	int lt = img.at<uchar>(pt),
		lb = img.at<uchar>(pt + Point(0, 1)),
		rt = img.at<uchar>(pt + Point(1, 0)),
		rb = img.at<uchar>(pt + Point(1, 1));

	double
		alpha = y - pt.y,
		beta = x - pt.x;

	int M1 = lt + (int)cvRound(alpha * (lb - lt));
	int M2 = rt + (int)cvRound(alpha * (rb - rt));
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	return saturate_cast<char>(P);

}

void ex9::ScalingBilinear(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			double x = j / ratioX;
			double y = i / ratioY;

			dst.at<uchar>(i, j) = BilinearValue(img, x, y);
		}
	}
}

void ex9::Rotation(Mat img, Mat& dst, double dgree)
{
	double radian = dgree / 180 * CV_PI;
	double sinVal = sin(radian);
	double cosVal = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			double x = j * cosVal + i * sinVal;
			double y = -j * sinVal + i * cosVal;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = BilinearValue(img, x, y);

		}
	}
}

void ex9::Run()
{
	auto img = OpenImageDialog();

	Mat rotImg, transImg, scalingImg1, scalingImg2, scalingImg3;

	Translation(img, transImg, Point(20, 20));

	Scaling(img, scalingImg1, Size(1024, 1024));
	ScalingNearest(img, scalingImg2, Size(1024, 1024));
	ScalingBilinear(img, scalingImg3, Size(1024, 1024));

	Rotation(img, rotImg, 30);

	imshow("�̵�", transImg);
	imshow("�����ϸ� - ������", scalingImg1);
	imshow("�����ϸ� - ������", scalingImg2);
	imshow("�����ϸ� - �缱��", scalingImg3);
	imshow("ȸ��", rotImg);

	waitKey();
}

int main()
{
	ex9::Run();
	//ex7_2::Run();
}