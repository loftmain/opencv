#include "ex11.h"




void ex11::Erosion(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(1));

	Point maskHalf = mask.size() / 2;
	for (int i = maskHalf.y; i < img.rows - maskHalf.y; i++) {
		for (int j = maskHalf.x; j < img.cols - maskHalf.x; j++) {
			Point start = Point(j, i) - maskHalf;

			bool check = CheckMatch(img, start, mask, 0);
			dst.at<uchar>(i, j) = (check) ? 255 : 0;

		}
	}
}

void ex11::ErosionGray(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(1));

	Point maskHalf = mask.size() / 2;
	for (int i = maskHalf.y; i < img.rows - maskHalf.y; i++) {
		for (int j = maskHalf.x; j < img.cols - maskHalf.x; j++) {
			Point start = Point(j, i) - maskHalf;

			uchar check = CheckMatch2(img, start, mask, 0);
			dst.at<uchar>(i, j) = check;

		}
	}
}

uchar ex11::CheckMatch2(Mat img, Point start, Mat mask, int mode)
{
	int a = 0; //���ϱ� ���� ����
	int b = 255; //���ϱ� ���� ����
	for (int u = 0; u < mask.rows; u++)
	{
		for (int v = 0; v < mask.cols; v++)
		{
			Point pt(v, u);
			int m = mask.at<uchar>(pt);
			int p = img.at<uchar>(start + pt);

			if  (a < p) // �ִ밪
				a = p;
			if (b > p)  // �ּҰ�
				b = p;
		}
	}
	if (mode == 1) //��â
		return a;
	
	return b; //ħ��
}
void ex11::DilationGray(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point maskHalf = mask.size() / 2;
	for (int i = maskHalf.y; i < img.rows - maskHalf.y; i++) {
		for (int j = maskHalf.x; j < img.cols - maskHalf.x; j++) {
			Point start = Point(j, i) - maskHalf;

			uchar check = CheckMatch2(img, start, mask, 1);
			dst.at<uchar>(i, j) = check;

		}
	}
}

void ex11::Run()
{
	Mat img = ex11::OpenImageDialog();
	Mat dst1, dst2, dst3, dst4, dst5, dst6, dst7;

	// ���⼭���ʹ� ������ �׽�Ʈ �ڵ��Դϴ�.
	// ������ ����ũ
	uchar data3[] = {
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};
	Mat mask3(3, 3, CV_8UC1, data3);
	
	// �ǽ�
	ErosionGray(img, dst1, (Mat)mask3);
	DilationGray(img, dst2, (Mat)mask3);
	Opening(img, dst3, (Mat)mask3);
	Closing(img, dst4, (Mat)mask3);
	imshow("����", img);
	imshow("ħ�� (�����)", dst1);
	imshow("��â (�����)", dst2);
	imshow("����", dst3);
	imshow("����", dst4);
	waitKey();
}
int main() {
	ex11 a = ex11();
	a.Run();
	return 0;
}