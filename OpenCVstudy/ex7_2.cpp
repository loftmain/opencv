#include "ex7_2.h"

void ex7_2::Run()
{
	srand(time(0));
	Mat image = ex7::OpenImageDialog();
	Mat nImage = AddImpulseNoise(image);
	Mat medianResultImage = MedianFiltering(nImage, 3);
	imshow("노이즈가 추가된 이미지", nImage);
	imshow("미디안 필터링", medianResultImage);
	waitKey();

	Mat embImage = Embossing(image);

	imshow("원본 이미지", image);
	imshow("엠보싱", embImage);
	waitKey();
}
int main()
{
	ex7_2::Run();
}