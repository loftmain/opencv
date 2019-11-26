#pragma once
#include "ex7.h"

class ex8
{
public:
	static void Run();
	static Mat ConvolutionMask(Mat image, Mat mask);

	static void RobertsMask(Mat image);
	static void PrewittMask(Mat image);
	static void SobelMask(Mat image);
};

void ex8::Run()
{
	Mat image = ex7::OpenImageDialog();
	RobertsMask(image);
	PrewittMask(image);
	//SobelMask(image);
	//LaplacianEdgeDetection(image);
}



Mat ex8::ConvolutionMask(Mat image, Mat mask)
{
	Mat result = Mat(image.size(), CV_32F, Scalar(0));
	Size mSize(mask.size());
	Point mSizeHalf = mSize / 2;

	Point minImageRange(mSizeHalf);
	Point maxImageRange(image.cols - mSizeHalf.x, image.rows - mSizeHalf.y);
	for (int y = minImageRange.y; y < maxImageRange.y; y++) {
		for (int x = minImageRange.x; x < maxImageRange.x; x++) {
			Point start = Point(x, y) - mSizeHalf;

			float sum = 0;
			for (int my = 0; my < mask.rows; my++) {
				for (int mx = 0; mx < mask.cols; mx++) {
					float maskValue = mask.at<float>(Point(mx, my));
					if (maskValue == 0)
						continue;
					float imagePixel = image.at<uchar>(Point(start.x + mx, start.y + my));
					sum += imagePixel * maskValue;
				}
			}

			result.at<float>(Point(x, y)) = sum;
		}
	}

	return result;
}

void ex8::RobertsMask(Mat image)
{
	float mask1[9] = {
		-1, 0, 0,
		0, 1, 0,
		0, 0, 0
	};
	float mask2[9] = {
		0, 0, -1,
		0, 1, 0,
		0, 0, 0
	};

	Mat maskV(3, 3, CV_32FC1, (void*)mask1),
		maskH(3, 3, CV_32FC1, (void*)mask2);
	auto verticalConvImage = ConvolutionMask(image, maskV);
	auto horizontalConvImage = ConvolutionMask(image, maskH);

	Mat totalConvImage;
	magnitude(verticalConvImage, horizontalConvImage, totalConvImage);

	verticalConvImage = abs(verticalConvImage);
	horizontalConvImage = abs(horizontalConvImage);

	totalConvImage.convertTo(totalConvImage, CV_8U);
	verticalConvImage.convertTo(horizontalConvImage, CV_8U);
	horizontalConvImage.convertTo(horizontalConvImage, CV_8U);

	imshow("원본", image);
	imshow("verticalConvImage", verticalConvImage);
	imshow("horizontalConvImage", horizontalConvImage);
	imshow("Total", totalConvImage);
	waitKey();
}

void ex8::PrewittMask(Mat image)
{
	float mask1[9] = {
		-1, 0, 1,
		-1, 0, 1,
		-1, 0, 1
	};
	float mask2[9] = {
		1, 1, 1,
		0, 0, 0,
		-1, -1, -1
	};

	Mat maskV(3, 3, CV_32FC1, (void*)mask1),
		maskH(3, 3, CV_32FC1, (void*)mask2);
	auto verticalConvImage = ConvolutionMask(image, maskV);
	auto horizontalConvImage = ConvolutionMask(image, maskH);

	Mat totalConvImage;
	magnitude(verticalConvImage, horizontalConvImage, totalConvImage);

	verticalConvImage = abs(verticalConvImage);
	horizontalConvImage = abs(horizontalConvImage);

	totalConvImage.convertTo(totalConvImage, CV_8U);
	verticalConvImage.convertTo(horizontalConvImage, CV_8U);
	horizontalConvImage.convertTo(horizontalConvImage, CV_8U);

	imshow("원본", image);
	imshow("verticalConvImage", verticalConvImage);
	imshow("horizontalConvImage", horizontalConvImage);
	imshow("Total", totalConvImage);
	waitKey();
}


void ex8::SobelMask(Mat image)
{
	float mask1[9] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	float mask2[9] = {
		1, 2, 1,
		0, 0, 0,
		-1, -2, -1
	};

	Mat maskV(3, 3, CV_32FC1, (void*)mask1),
		maskH(3, 3, CV_32FC1, (void*)mask2);
	auto verticalConvImage = ConvolutionMask(image, maskV);
	auto horizontalConvImage = ConvolutionMask(image, maskH);

	Mat totalConvImage;
	magnitude(verticalConvImage, horizontalConvImage, totalConvImage);

	verticalConvImage = abs(verticalConvImage);
	horizontalConvImage = abs(horizontalConvImage);

	totalConvImage.convertTo(totalConvImage, CV_8U);
	verticalConvImage.convertTo(horizontalConvImage, CV_8U);
	horizontalConvImage.convertTo(horizontalConvImage, CV_8U);

	imshow("원본", image);
	imshow("verticalConvImage", verticalConvImage);
	imshow("horizontalConvImage", horizontalConvImage);
	imshow("Total", totalConvImage);
	waitKey();
}

void ex8::SobelMask(Mat image)
{
	float mask1[9] = {
		0, -1, 0,
		-1, 4, -1,
		0, -1, 0
	};
	float mask2[9] = {
		1, 1, 1,
		1, -8, 1,
		1, 1, 1
	};

	Mat maskV(3, 3, CV_32FC1, (void*)mask1),
		maskH(3, 3, CV_32FC1, (void*)mask2);
	auto verticalConvImage = ConvolutionMask(image, maskV);
	auto horizontalConvImage = ConvolutionMask(image, maskH);

	Mat totalConvImage;
	magnitude(verticalConvImage, horizontalConvImage, totalConvImage);

	verticalConvImage = abs(verticalConvImage);
	horizontalConvImage = abs(horizontalConvImage);

	totalConvImage.convertTo(totalConvImage, CV_8U);
	verticalConvImage.convertTo(horizontalConvImage, CV_8U);
	horizontalConvImage.convertTo(horizontalConvImage, CV_8U);

	imshow("원본", image);
	imshow("verticalConvImage", verticalConvImage);
	imshow("horizontalConvImage", horizontalConvImage);
	imshow("Total", totalConvImage);
	waitKey();
}