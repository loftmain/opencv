#include "ex7_2.h"

void ex7_2::Run()
{
	srand(time(0));
	Mat image = ex7::OpenImageDialog();
	Mat nImage = AddImpulseNoise(image);
	Mat medianResultImage = MedianFiltering(nImage, 3);
	imshow("����� �߰��� �̹���", nImage);
	imshow("�̵�� ���͸�", medianResultImage);
	waitKey();

	Mat embImage = Embossing(image);

	imshow("���� �̹���", image);
	imshow("������", embImage);
	waitKey();
}
int main()
{
	ex7_2::Run();
}