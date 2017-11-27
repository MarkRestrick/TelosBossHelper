#include "opencv2\opencv.hpp"
#include "opencv2\imgproc.hpp"
#include <Windows.h>
#include <iostream>
#include "opencv2\opencv_modules.hpp"
#include <stdio.h>
#include <opencv2\xfeatures2d.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/features2d.hpp"
#include "opencv/highgui.h"


/*
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

const int fps = 20;

Mat hwnd2mat(HWND hwnd)
{
	HDC hwindowDC, hwindowCompatibleDC;
	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	RECT windowsize;
	GetClientRect(hwnd, &windowsize);

	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom / 1;
	width = windowsize.right / 1;

	src.create(height, width, CV_8UC4);

	//Create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);

	return src;
}





int main()
{
	/*

	//Mat original = imread("Telos.png", CV_LOAD_IMAGE_COLOR);
	//Mat frame;

	//Image to seek, and convert to RGB in memory
	Mat Virus = imread("BlackVirus.png", IMREAD_GRAYSCALE);
	Mat Telos = imread("Telos.png", IMREAD_GRAYSCALE);
	//cvtColor(Virus, Virus, CV_BGR2RGB);



	
	//namedWindow("Output", WINDOW_NORMAL);
	//int key = 0;

	int minHessian = 10;

	Ptr<SURF> detector = SURF::create(minHessian);

	vector<KeyPoint> keypoints_1, keypoints_2;

	detector->detect(Virus, keypoints_1);
	detector->detect(Telos, keypoints_2);

	Ptr<SURF> extractor = SURF::create();

	Mat descriptors_1, descriptors_2;

	extractor->compute(Virus, keypoints_1, descriptors_1);
	extractor->compute(Telos, keypoints_2, descriptors_2);

	//Matching stuff
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	double max_dist = 0; double min_dist = 100;

	//Some weird calculation
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	
	printf("-- Max dist: %f \n", max_dist);
	printf("-- Min dist: %f \n", min_dist);

	// draw only good matches

	vector<DMatch> good_matches;

	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 0.02))
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;

	drawMatches(Virus, keypoints_1, Telos, keypoints_2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//Mat img_keypoints_1;

	//drawKeypoints(Virus, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);



	imshow("Good Matches", img_matches);
	//SurfFeatureDetector detector(minHessian);
	*/

/*


	int key = 0;
	HWND hwndDesktop = GetDesktopWindow();
	Mat3b templ = imread("HoldStill.png");

	while (key != 27)
	{
		Mat src = hwnd2mat(hwndDesktop);
		Mat1b img_gray;
		Mat1b templ_gray;
		cvtColor(src, img_gray, COLOR_BGR2GRAY);
		cvtColor(templ, templ_gray, COLOR_BGR2GRAY);

		//Match Template
		Mat1f result;
		matchTemplate(img_gray, templ_gray, result, TM_CCOEFF_NORMED);
		
	
		//Find highest response
		Point maxLoc;
		minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
		if (result(maxLoc) > 0.8)
		{
			

			//Draw the red rectangle
			rectangle(src, Rect(maxLoc, templ.size()), Scalar(0, 0, 255), 2);
		}

		
		//Rect croppedRectangle = Rect(5, maxLoc.y - 50, 300, 100);
		//Mat CroppedImage = src(croppedRectangle);

		//Show results
		imshow("Result", src);



		
		key = waitKey(10);
	}
	

	//Load Template and image

	//Mat3b img = imread("Telos.png");

	//Convert to grayscale
	/*
	
	Mat1b img_gray;
	Mat1b templ_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	cvtColor(templ, templ_gray, COLOR_BGR2GRAY);

	//Match Template
	Mat1f result;
	matchTemplate(img, templ, result, TM_CCOEFF_NORMED);

	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);

	//Draw the red rectangle
	rectangle(img, Rect(maxLoc, templ.size()), Scalar(255, 255, 255), 2);

	//Show results
	*/

	//imshow("Result", img);
	
		/*

	return 0;

}

*/