#include "ex7.h"

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

void ex7::Run()
{
	// 명세화를 할 이미지 (ex : leana
	Mat img = OpenImageDialog();
	// 명세화에 사용될 히스토그램을 추출할 이미지
	Mat imgForHistogram = OpenImageDialog();

	HistogramSpecification(img, imgForHistogram);
	waitKey();
}
void ex7::CalcHistogram(Mat image, Mat& histogram, int bins, int range_max)
{
	histogram = Mat(bins, 1, CV_32F, Scalar(0));

	float gap = (float)range_max / bins;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			auto workPixel = image.at<uchar>(i, j);
			int idx = (int)workPixel / gap);
			histogram.at<float>(idx)++;
		}
	}
}

void ex7::GetHistogramImage(Mat histogram, Mat& histogramImage, Size size)
{

	histogramImage = Mat(size, CV_8U, Scalar(255));

	float gap = (float)(histogramImage.cols / histogram.rows);
	normalize(histogram, histogram, 0, histogramImage.rows, NORM_MINMAX);

	for (int i = 0; i < histogram.rows; i++) {
		float sx = i * gap;
		float ex = (i + 1) * gap;

		Point2f pt_lb(sx, 0), pt_rt(ex, histogram.at<float>(i));

		if (pt_rt.y > 0)
			rectangle(histogramImage, pt_lb, pt_rt, Scalar(0), -1);
	}
	flip(histogramImage, histogramImage, 0);
}

float ex7::CalcCumulativeFrequency(Mat histogram, Mat& histogramSum)
{
	float sum = 0;
	for (int i = 0; i < histogram.rows; i++) {
		sum += histogram.at<float>(i);
		histogramSum.at<float>(i) = sum;
	}
	return sum;

}

void ex7::CalcNormalizedCumulativeFrequency(Mat histogram, Mat& histogramSum)
{
	histogramSum = Mat(histogram.rows, 1, CV_32F, Scalar(0))
}