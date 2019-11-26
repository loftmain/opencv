#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <string.h>

using namespace cv;
using namespace std;

Mat OpenImageDialog()
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

	Mat image = Mat();
	if (GetOpenFileNameA(&ofn)) {
		image = imread(name, IMREAD_GRAYSCALE);
		if (image.empty()) {
			cout << "파일 읽기 실패" << endl;
			exit(1);
		}
	}
	else {
		cout << "파일 지정 오류" << endl;
		exit(1);
	}
	return image;
}
void MirrorHorizontal(Mat img, Mat& dst)
{
	dst = Mat(img.size(), img.type(), Scalar(0));

	//목적 영상 순회 - 역방향 사상
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			//중심선을 기준으로 반전
			dst.at<uchar>(i, j) = img.at<uchar>(i, -(j - (img.cols - 1)));
		}
	}
}

void MirrorVertical(Mat img, Mat& dst)
{
	dst = Mat(img.size(), img.type(), Scalar(0));
	//목적 영상 순회 - 역방향 사상
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			dst.at<uchar>(i, j) = img.at<uchar>(-(i - (img.rows - 1)), j);
		}
	}
}
uchar BilinearValue(Mat img, double x, double y) {
	if (x >= img.cols - 1)x--;
	if (y >= img.rows - 1)y--;

	//4개 화소
	Point pt((int)x, (int)y);
	int lt = img.at<uchar>(pt),
		lb = img.at<uchar>(pt + Point(0, 1)),
		rt = img.at<uchar>(pt + Point(1, 0)),
		rb = img.at<uchar>(pt + Point(1, 1));

	//거리 비율
	double alpha = y - pt.y, //y축
		beta = x - pt.x;//x축

	int M1 = lt + (int)cvRound(alpha * (lb - lt));
	int M2 = rt + (int)cvRound(alpha * (rb - rt));
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	//실수에서 uchar 형으로 변환
	return saturate_cast<uchar>(P);
}
void RotationPoint(Mat img, Mat& dst, Point pt, double dgree) {
	double radian = dgree / 180 * CV_PI;
	double sinVal = sin(radian);
	double cosVal = cos(radian);

	Rect rect(0, 0, img.cols, img.rows);

	dst = Mat(img.size(), img.type(), Scalar(0));

	//목적ㅁ영상 순회-영방향 사상
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			//회전 변환
			double x = (j - pt.x) * cosVal + (i - pt.y) * sinVal + pt.x;
			double y = -(j - pt.x) * sinVal + (i - pt.y) * cosVal + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = BilinearValue(img, x, y);
		}
	}
}
void Run()
{
	auto img = OpenImageDialog();

	Mat mirrorImgH, mirrorImgV, rotationImg;

	MirrorHorizontal(img, mirrorImgH);
	MirrorVertical(img, mirrorImgV);
	RotationPoint(img, rotationImg, Point(img.cols / 2, img.rows / 2), 30);

	imshow("미러 - 수평", mirrorImgH);
	imshow("미러 - 수직", mirrorImgV);
	imshow("기준점 회전", rotationImg);

	waitKey();
}
int main() {
	Run();
	return 0;
}