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