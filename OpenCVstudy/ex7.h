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
	// 파일을 읽는 다이얼로그 호출
	static string OpenFileDialog();
	// 영상을 읽는 다이얼로그 호출
	static Mat OpenImageDialog();
	// 영상을 테이블을 참조하여 변환
	template<typename T>
	static Mat ConvertImageFromTable(Mat img, Mat table);
	// 테스트 코드 실행
	static void Run();

	// 영상의 히스토그램 생성
	static void CalcHistogram(Mat image, Mat& histogram, int bins, int range_max = 256);

	static void GetHistogramImage(Mat histogram, Mat& histogramImage, Size size = Size(256, 200));

	// CalcNormalizedCumulativeFrequency 의 누적합 부분 -> 이전 실습 코드를 사용하면 할 필요는 없음
	static float CalcCumulativeFrequency(Mat histogram, Mat& histogramSum);
	static void CalcNormalizedCumulativeFrequency(Mat histogram, Mat& histogramSum);

	// 영상으로 부터 명세화된 히스토그램 테이블 생성
	static void GetHistogramSpecificationTable(Mat image, Mat& lookupTable);

	// 히스토그램 명세화
	static void HistogramSpecification(Mat img, Mat imgForHistogram);


};
Mat ex7::OpenImageDialog()
{
	auto fileName = OpenFileDialog();
	Mat image = imread(fileName, IMREAD_GRAYSCALE);
	if (image.empty()) {
		cout << "파일 읽기 실패" << endl;
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
	ofn.lpstrFilter = "모든파일(*.*)\0*.*\0";
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