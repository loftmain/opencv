#pragma once
#pragma once
#include "ex7.h"

class ex7_2
{
public:
	// 테스트 코드
	static void Run();

	// 미디안 필터링
	static Mat MedianFiltering(Mat image, int maskSize);
	// 엠보싱
	static Mat Embossing(Mat image);
	// 임의의 마스크 처리
	static Mat ConvolutionMask(Mat image, Mat mask);

	// 임펄스 잡음 생성
	static Mat AddImpulseNoise(Mat image);
};
