#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
int main()
{
	int A[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
	int B[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };
	int Gx, Gy;
	int e,f;
	int c = 0;
	int d = 0;
	Mat var3 = imread("images.jpg", 1);
	Mat var1(var3.rows, var3.cols, CV_8UC1, Scalar(0));
	Mat var2(var3.rows, var3.cols, CV_8UC1, Scalar(0));
	Mat var4(var3.rows, var3.cols, CV_8UC1, Scalar(0));
	Mat var5(var3.rows, var3.cols, CV_8UC1, Scalar(0));
	cvtColor(var3, var1, CV_BGR2GRAY);
	for (int i = 0; i < var1.rows; i++)
	{
		var2.at<uchar>(i, 0) = var1.at<uchar>(i, 0);
		var2.at<uchar>(i, var1.cols - 1) = var1.at<uchar>(i, var1.cols - 1);
		var5.at<uchar>(i, 0) = var1.at<uchar>(i, 0);
		var5.at<uchar>(i, var1.cols - 1) = var1.at<uchar>(i, var1.cols - 1);
		var4.at<uchar>(i, 0) = var1.at<uchar>(i, 0);
		var4.at<uchar>(i, var1.cols - 1) = var1.at<uchar>(i, var1.cols - 1);

	}
	for (int i = 0; i < var1.cols; i++)
	{
		var2.at<uchar>(0, i) = var1.at<uchar>(0, i);
		var2.at<uchar>(var1.rows - 1, i) = var1.at<uchar>(var1.rows - 1, i);

	}
	for (int i = 0; i < var1.rows - 1; i++){
		for (int j = 0; j < var1.cols - 1; j++)
		{
			Gx = 0; Gy = 0;
			c = 0;
			for (int m = i; m < var1.rows; m++, c++)
			{
				if (c < 3)
				{
					d = 0;
					for (int n = j; n < var1.cols; n++, d++)
					{
						if (d < 3)
						{
							if ((i + 1) < var1.rows && (j + 1) < var1.cols)
							{
								Gx += var1.at<uchar>(m, n) * A[m - i][n - j];
								Gy += var1.at<uchar>(m, n) * B[m - i][n - j];

							}
						}
					}
				}
			}
			var4.at<uchar>(i + 1, j + 1) = atan(Gx / Gy)/3.14*180;
			e = (int)sqrt(Gx*Gx + Gy*Gy);
			if (e > 255)
				var2.at<uchar>(i + 1, j + 1) = 255;
			else
				var2.at<uchar>(i + 1, j + 1) = e;
		}
	}
	for (int i = 1; i < var1.rows - 1; i++){
		for (int j = 1; j < var1.cols - 1; j++)
		{
			f = var4.at<uchar>(i, j);
			if (f>0 && f < 45/2)
			{
				if (f>var4.at<uchar>(i, j - 1) && f>var4.at<uchar>(i, j + 1))
					var5.at<uchar>(i, j) = 255;
				else

					var5.at<uchar>(i, j) = 0;
			}
			else if (f>45/2 && f < 135/2)
			{
				if (f>var4.at<uchar>(i+1, j - 1) && f>var4.at<uchar>(i-1, j + 1))
					var5.at<uchar>(i, j) = 255;
				else

					var5.at<uchar>(i, j) = 0;
			}
			else if (f>135/2 && f < 225/2)
			{
				if (f>var4.at<uchar>(i - 1, j ) && f>var4.at<uchar>(i + 1, j ))
					var5.at<uchar>(i, j) = 255;
				else

					var5.at<uchar>(i, j) = 0;
			}
			else
			{
				if (f>var4.at<uchar>(i - 1, j-1) && f>var4.at<uchar>(i + 1, j+1))
					var5.at<uchar>(i, j) = 255;
				else

					var5.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("window1", var1);
	imshow("window2", var2);
	imshow("window3", var3);
	//imshow("window4", var4);
	imshow("window5", var5);
	waitKey(0);
	return(0);
}