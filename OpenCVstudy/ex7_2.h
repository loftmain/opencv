#pragma once
#pragma once
#include "ex7.h"

class ex7_2
{
public:
	// �׽�Ʈ �ڵ�
	static void Run();

	// �̵�� ���͸�
	static Mat MedianFiltering(Mat image, int maskSize);
	// ������
	static Mat Embossing(Mat image);
	// ������ ����ũ ó��
	static Mat ConvolutionMask(Mat image, Mat mask);

	// ���޽� ���� ����
	static Mat AddImpulseNoise(Mat image);
};
