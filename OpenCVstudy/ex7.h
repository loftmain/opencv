#pragma once
#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <string.h>
#include <iostream>
using namespace cv;
using namespace std;

class ex7
{
public:
	// ������ �д� ���̾�α� ȣ��
	static string OpenFileDialog();
	// ������ �д� ���̾�α� ȣ��
	static Mat OpenImageDialog();
	// ������ ���̺��� �����Ͽ� ��ȯ
	template<typename T>
	static Mat ConvertImageFromTable(Mat img, Mat table);
	// �׽�Ʈ �ڵ� ����
	static void Run();

	// ������ ������׷� ����
	static void CalcHistogram(Mat image, Mat& histogram, int bins, int range_max = 256);

	static void GetHistogramImage(Mat histogram, Mat& histogramImage, Size size = Size(256, 200));

	// CalcNormalizedCumulativeFrequency �� ������ �κ� -> ���� �ǽ� �ڵ带 ����ϸ� �� �ʿ�� ����
	static float CalcCumulativeFrequency(Mat histogram, Mat& histogramSum);
	static void CalcNormalizedCumulativeFrequency(Mat histogram, Mat& histogramSum);

	// �������� ���� ��ȭ�� ������׷� ���̺� ����
	static void GetHistogramSpecificationTable(Mat image, Mat& lookupTable);

	// ������׷� ��ȭ
	static void HistogramSpecification(Mat img, Mat imgForHistogram);


};
Mat ex7::OpenImageDialog()
{
	auto fileName = OpenFileDialog();
	Mat image = imread(fileName, IMREAD_GRAYSCALE);
	if (image.empty()) {
		cout << "���� �б� ����" << endl;
		exit(1);
	}
	return image;
}
string ex7::OpenFileDialog()
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