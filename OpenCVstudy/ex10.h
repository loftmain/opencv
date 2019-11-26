#pragma once
#include "ex9.h"

class ex10
{
public:
	static void Run();
	static void MirrorHorizontal(Mat img, Mat& dst);
	static void MirrorVertical(Mat img, Mat& dst);
	static void RotationPoint(Mat img, Mat& dst, Point pt, double dgree);

};