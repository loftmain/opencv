#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <string.h>
#include <iostream>
using namespace cv;
using namespace std;

class ex11
{
public:
	// �׽�Ʈ �ڵ�
	static void Run();
	// ������ �д� ���̾�α� ȣ��
	static string OpenFileDialog();
	// ������ �д� ���̾�α� ȣ��
	static Mat OpenImageDialog();

	static bool CheckMatch(Mat img, Point start, Mat mask, int mode = 0);

	// ħ��
	static void Erosion(Mat img, Mat& dst, Mat mask);
	// ��â
	static void Dilation(Mat img, Mat& dst, Mat mask);
	// ����
	static void Opening(Mat img, Mat& dst, Mat mask);
	// ����
	static void Closing(Mat img, Mat& dst, Mat mask);

	// ����
	static uchar CheckMatch2(Mat img, Point start, Mat mask, int mode = 0);
	static void ErosionGray(Mat img, Mat& dst, Mat mask);
	static void DilationGray(Mat img, Mat& dst, Mat mask);
};
void ex11::Dilation(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point maskHalf = mask.size() / 2;
	for (int i = maskHalf.y; i < img.rows - maskHalf.y; i++) {
		for (int j = maskHalf.x; j < img.cols - maskHalf.x; j++) {
			Point start = Point(j, i) - maskHalf;

			bool check = CheckMatch(img, start, mask, 1);
			dst.at<uchar>(i, j) = (check) ? 0 : 255;

		}
	}
}

void ex11::Opening(Mat img, Mat& dst, Mat mask)
{
	Mat dst1;
	ErosionGray(img, dst1, mask);
	DilationGray(dst1, dst, mask);

}

void ex11::Closing(Mat img, Mat& dst, Mat mask)
{
	Mat dst1;
	DilationGray(img, dst1, mask);
	ErosionGray(dst1, dst, mask);

}
Mat ex11::OpenImageDialog()
{
	auto fileName = OpenFileDialog();
	Mat image = imread(fileName, IMREAD_GRAYSCALE);
	if (image.empty()) {
		cout << "���� �б� ����" << endl;
		exit(1);
	}
	return image;
}
string ex11::OpenFileDialog()
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

	string strName;
	if (GetOpenFileNameA(&ofn)) {
		strName = name;
	}

	return strName;
}

bool ex11::CheckMatch(Mat img, Point start, Mat mask, int mode)
{
	for (int u = 0; u < mask.rows; u++)
	{
		for (int v = 0; v < mask.cols; v++)
		{
			Point pt(v, u);

			int m = mask.at<uchar>(pt);

			int p = img.at<uchar>(start + pt);

			bool ch = (p == 255);

			if ((m == 1) && (ch == mode))
				return false;
			// �迭�� retrun �ϰ� �ִ� �ּҷ� �ٲ��ָ� ��
		}
	}
	return true;
}
