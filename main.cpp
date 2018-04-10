#define _USE_MATH_DEFINES
#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>
using namespace cv;

int main(void) {
	Mat img = imread("baboon.jpg");
	if (img.empty()) {
		std::cout << " not found" << std::endl;
		return -1;
	}

	int k;
	double z;
	std::cout << "”z—ñ‚Ì”‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢" << std::endl;
	std::cin >> k;
	std::cout << "•ªŽU‚Ì’l‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢" << std::endl;
	std::cin >> z;

	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);
	Mat dst2 = Mat::zeros(img.rows, img.cols, CV_8UC3);

	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			double b = 0, g = 0, r = 0;
			for (int i = (k - 1) / 2; i < ((k - 1) / 2) + k; i++) {
				for (int j = (k - 1) / 2; j < ((k - 1) / 2) + k; j++) {

					int m = i - (k + 1) / 2;
					int n = j - (k + 1) / 2;
					double f = 1 / (2 * M_PI * pow(z, 2)) * (double)(exp(-(pow(n, 2) + pow(m, 2)) / (2 * pow(z, 2))));

					int s = y - i;
					int t = x - j;
					if (s < 0) {
						s = 0;
					}
					if (s >= img.rows) {
						s = img.rows - 1;
					}
					if (t < 0) {
						t = 0;
					}
					if (t >= img.cols) {
						t = img.cols - 1;
					}

					Vec3b tmp = img.at<Vec3b>(s, t);
					b += tmp[0] * f;
					g += tmp[1] * f;
					r += tmp[2] * f;
				}
			}
			dst.at<Vec3b>(y, x) = Vec3b(b, g, r);
		}
	}

	GaussianBlur(img, dst2, Size(3, 3), 1.5, 0);

	imshow("View", img);
	imshow("Filter", dst);
	imshow("Filter2", dst2);
	imwrite("Gaussian_Filter.jpg", dst);
	waitKey();

	return 0;
}