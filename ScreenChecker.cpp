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
#include "ScreenChecker.h"

ScreenChecker::ScreenChecker()
{
	//ChatArea = Rect(0, 0, 0, 0);
	//DebuffArea = Rect(0, 0, 0, 0);
	ImageSetup();


	/*
	m_currentPhase = 1;

	int key = 0;
	HWND hwndDesktop = GetDesktopWindow();
	RECT desktopSize;
	GetWindowRect(hwndDesktop, &desktopSize);

	PhaseArea = Rect(1, 1, (desktopSize.right / 2), 100);

	while (key != 27)
	{
		src = hwnd2mat(hwndDesktop);
		
		Mat1b img_gray;
		Mat1b templ_gray;
		cvtColor(src, img_gray, COLOR_BGR2GRAY);

		//DebuffCheck(img_gray, m_Phase1Gray);

		//Rect croppedRectangle = Rect(5, maxLoc.y - 50, 300, 100);
		//Mat CroppedImage = src(croppedRectangle);

		
		Mat1b PhaseCropped = img_gray(PhaseArea);

		Mat1b DebuffCropped = (!DebuffArea.empty()) ? img_gray(DebuffArea) : img_gray;

		Mat1b ChatCropped; 
		
		if(!ChatArea.empty())
		{
			ChatCropped = img_gray(ChatArea);
		}
		else
		{
			ChatCropped = img_gray;
		}

		Rect Something;

		m_currentPhase = PhaseCheck(PhaseCropped);

		if (m_currentPhase == 1)
		{
			
			m_greenAnima = DebuffCheck(DebuffCropped, m_GreenAnimaGray, 0.98f);
			m_tendrils = AttackCheck(ChatCropped, m_TendrilsGray, 0.85f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_greenAnima)
			{
				if (!m_GAnimaFlag)
				{
					m_GAnimaFlag = true;
					cout << "GREEN ANIMA ACTIVE PEW PEW \n";
				}
				
			}
			else
			{
				m_GAnimaFlag = false;
			}


			if (m_tendrils)
			{
				if (!m_TendrilsFlag)
				{
					m_TendrilsFlag = true;
					cout << "TENDRILS HAPPENED, NEXT IS GIELINOR \n";
				}
			}
			else
			{
				m_TendrilsFlag = false;
			}


			if (m_uppercut)
			{
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, HOLD STILL NEXT \n";
				}	
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, TENDRILS NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}
			
			
		}


		if (m_currentPhase == 2)
		{

			m_blackAnima = DebuffCheck(DebuffCropped, m_BlackAnimaGray, 0.97f);
			m_blackVirus = DebuffCheck(DebuffCropped, m_BlackVirusGray, 0.82f);
			m_tendrils = AttackCheck(ChatCropped, m_TendrilsGray, 0.85f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_blackAnima)
			{

				if (!m_BAnimaFlag)
				{
					cout << "BLACK ANIMA ACTIVE GET OUT IF NOT INTENTIONAL \n";
					m_BAnimaFlag = true;
				}

			}
			else
			{
				m_BAnimaFlag = false;
			}


			if (m_blackVirus)
			{
				if (!m_BVirFlag)
				{
					m_BVirFlag = true;
					cout << "BLACK VIRUS ACTIVE GET TO BLACK STREAM, PREPARE FOR GIELINOR \n";
				}

			}
			else
			{
				m_BVirFlag = false;
			}


			if (m_tendrils)
			{
				if (!m_TendrilsFlag)
				{
					m_TendrilsFlag = true;
					cout << "TENDRILS HAPPENED, NEXT IS ONSLAUGHT, FOLLOWED BY HOLD STILL \n";
				}
			}
			else
			{
				m_TendrilsFlag = false;
			}


			if (m_uppercut)
			{
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, TENDRILS ARE NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, BLACK VIRUS IS NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}

		if (m_currentPhase == 3)
		{

			m_redVirus = DebuffCheck(DebuffCropped, m_RedVirusGray, 0.82f);
			m_redAnima = DebuffCheck(DebuffCropped, m_RedAnimaGray, 0.98f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_redVirus)
			{
				if (!m_RVirFlag)
				{
					m_RVirFlag = true;
					cout << "RED VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_RVirFlag = false;
			}

			if (m_redAnima)
			{
				if (!m_RAnimaFlag)
				{
					m_RAnimaFlag = true;
					cout << "RED ANIMA ACTIVE PEWPEW \n";
				}

			}
			else
			{
				m_RAnimaFlag = false;
			}



			if (m_uppercut)
			{
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, HOLD STILL NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, RED VIRUS NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}

		if (m_currentPhase == 4)
		{

			m_animaBomb = AttackCheck(ChatCropped, m_AnimaBombGray, 0.85f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_animaBomb)
			{
				if (!m_RVirFlag)
				{
					m_RVirFlag = true;
					cout << "ANIMA BOMB HAPPENED, NEXT IS HOLD STILL \n";
				}

			}
			else
			{
				m_RVirFlag = false;
			}



			if (m_uppercut)
			{
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, ANIMA BOMB NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, GIELINOR NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}


		if (m_currentPhase == 5)
		{

			m_redVirus = DebuffCheck(DebuffCropped, m_RedVirusGray, 0.85f);
			m_blackVirus = DebuffCheck(DebuffCropped, m_BlackVirusGray, 0.85f);
			m_greenVirus = DebuffCheck(DebuffCropped, m_GreenVirusGray, 0.85f);
			m_redAnima = DebuffCheck(DebuffCropped, m_RedAnimaGray, 0.98f);
			m_greenAnima = DebuffCheck(DebuffCropped, m_GreenAnimaGray, 0.98f);
			m_blackAnima = DebuffCheck(DebuffCropped, m_BlackAnimaGray, 0.98f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_redVirus)
			{
				if (!m_RVirFlag)
				{
					m_RVirFlag = true;
					cout << "RED VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_RVirFlag = false;
			}

			if (m_redAnima)
			{
				if (!m_RAnimaFlag)
				{
					m_RAnimaFlag = true;
					cout << "RED ANIMA ACTIVE PEWPEW \n";
				}

			}
			else
			{
				m_RAnimaFlag = false;
			}


			if (m_blackVirus)
			{
				if (!m_BVirFlag)
				{
					m_BVirFlag = true;
					cout << "BLACK VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_BVirFlag = false;
			}

			if (m_blackAnima)
			{
				if (!m_BAnimaFlag)
				{
					m_BAnimaFlag = true;
					cout << "BLACK ANIMA ACTIVE GET OUT IF NOT INTENTIONAL \n";
				}

			}
			else
			{
				m_BAnimaFlag = false;
			}

			if (m_greenVirus)
			{
				if (!m_GVirFlag)
				{
					m_GVirFlag = true;
					cout << "GREEN VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_GVirFlag = false;
			}

			if (m_greenAnima)
			{
				if (!m_GAnimaFlag)
				{
					m_GAnimaFlag = true;
					cout << "GREEN ANIMA ACTIVE PEWPEW \n";
				}

			}
			else
			{
				m_GAnimaFlag = false;
			}



		}
		
		//Match Template
		//Mat1f result;
		//matchTemplate(img_gray, templ_gray, result, TM_CCOEFF_NORMED);
		//matchTemplate(src, templ, result, TM_SQDIFF);


		//Find highest response
		//Point maxLoc;
		//minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
		//if (result(maxLoc) > 0.82)
		//{


			//Draw the red rectangle
			//rectangle(src, Rect(maxLoc, templ.size()), Scalar(0, 0, 255), 2);
		//}

		/*
		if (m_currentPhase == 1)
		{
			GreenVirusCheck(img_gray);
		}
		*/

		//Rect croppedRectangle = Rect(5, maxLoc.y - 50, 300, 100);
		//Mat CroppedImage = src(croppedRectangle);




		//Show results
		//imshow("Result", src);




		//key = waitKey(10);
	//}


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



	
}

ScreenChecker::~ScreenChecker()
{

}

void ScreenChecker::SetCurrentPhase(int phase)
{
	m_currentPhase = phase;
}

Mat ScreenChecker::hwnd2mat(HWND hwnd)
{
	HDC hwindowDC, hwindowCompatibleDC;
	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
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
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); 
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);

	return src;
}

void ScreenChecker::ImageSetup()
{
	m_GreenVirus = imread("Images/GreenVirus.png");
	m_BlackVirus = imread("Images/BlackVirus.png"); 
	m_RedVirus = imread("Images/RedVirus.png");

	m_GreenAnima = imread("Images/GreenAnima.png");
	m_BlackAnima = imread("Images/BlackAnima.png");
	m_RedAnima = imread("Images/RedAnima.png");

	m_Tendrils = imread("Images/Tendril.png");
	m_HoldStill = imread("Images/HoldStill.png");
	m_Gielinor = imread("Images/Uppercut2.png");
	m_AnimaCleanse = imread("Images/AnimaCleanse.png");
	m_AnimaBomb = imread("Images/AnimaBomb.png");
	m_GolemSpawn = imread("Images/AnimaGolems.png");
	m_OHKO = imread("Images/OHKO.png");
	m_Phase1 = imread("Images/Phase1.png");
	m_Phase2 = imread("Images/Phase2.png");
	m_Phase3 = imread("Images/Phase3.png");
	m_Phase4 = imread("Images/Phase4.png");
	m_Phase5 = imread("Images/Phase5.png");

	

	cvtColor(m_GreenVirus, m_GreenVirusGray, COLOR_BGR2GRAY);
	cvtColor(m_BlackVirus, m_BlackVirusGray, COLOR_BGR2GRAY);
	cvtColor(m_RedVirus, m_RedVirusGray, COLOR_BGR2GRAY);
	
	cvtColor(m_GreenAnima, m_GreenAnimaGray, COLOR_BGR2GRAY);
	cvtColor(m_BlackAnima, m_BlackAnimaGray, COLOR_BGR2GRAY);
	cvtColor(m_RedAnima, m_RedAnimaGray, COLOR_BGR2GRAY);
	
	cvtColor(m_Tendrils, m_TendrilsGray, COLOR_BGR2GRAY);
	cvtColor(m_HoldStill, m_HoldStillGray, COLOR_BGR2GRAY);
	cvtColor(m_Gielinor, m_GielinorGray, COLOR_BGR2GRAY);
	cvtColor(m_AnimaCleanse, m_AnimaCleanseGray, COLOR_BGR2GRAY);
	cvtColor(m_AnimaBomb, m_AnimaBombGray, COLOR_BGR2GRAY);
	cvtColor(m_GolemSpawn, m_GolemSpawnGray, COLOR_BGR2GRAY);
	cvtColor(m_OHKO, m_OHKOGray, COLOR_BGR2GRAY);
	cvtColor(m_Phase1, m_Phase1Gray, COLOR_BGR2GRAY);
	cvtColor(m_Phase2, m_Phase2Gray, COLOR_BGR2GRAY);
	cvtColor(m_Phase3, m_Phase3Gray, COLOR_BGR2GRAY);
	cvtColor(m_Phase4, m_Phase4Gray, COLOR_BGR2GRAY);
	cvtColor(m_Phase5, m_Phase5Gray, COLOR_BGR2GRAY);
	

}

bool ScreenChecker::GreenVirusCheck(Mat &Source)
{

	Mat3b greenVirTemp = imread("GreenVirus.png");

	Mat1b greenVirTemp_gray;
	cvtColor(greenVirTemp, greenVirTemp_gray, COLOR_BGR2GRAY);

	//Match Template
	Mat1f result;
	matchTemplate(Source, greenVirTemp_gray, result, TM_CCOEFF_NORMED);
	//matchTemplate(src, templ, result, TM_SQDIFF);


	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.82)
	{

		
		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, greenVirTemp_gray.size()), Scalar(0, 0, 255), 2);
		return true;
	}
	return false;
}

bool ScreenChecker::DebuffCheck(Mat &Source, Mat1b &Debuff, float thresh)
{

	//Match Template
	Mat1f result;
	matchTemplate(Source, Debuff, result, TM_CCOEFF_NORMED);
	//matchTemplate(src, templ, result, TM_SQDIFF);


	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > thresh)
	{


		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, Debuff.size()), Scalar(0, 0, 255), 2);
		
		if (DebuffArea.empty())
		{
			m_debuffLoc = maxLoc;
			DebuffArea = Rect(maxLoc.x - 120, maxLoc.y -80, 350, 200);
		}
		

		return true;
	}
	return false;
}

bool ScreenChecker::AttackCheck(Mat &Source, Mat1b &Debuff, float thresh)
{

	//Match Template
	Mat1f result;
	matchTemplate(Source, Debuff, result, TM_CCOEFF_NORMED);
	//matchTemplate(src, templ, result, TM_SQDIFF);


	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > thresh)
	{


		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, Debuff.size()), Scalar(0, 0, 255), 2);
		
		if (ChatArea.empty())
		{
			cout << "Fixed Chat";
			m_chatLoc = maxLoc;
			ChatArea = Rect( maxLoc.x, maxLoc.y - 20, 300, 50);
		}
		

		return true;
	}
	return false;
}

int ScreenChecker::PhaseCheck(Mat & Source)
{
	//Match Template
	Mat1f result;
	matchTemplate(Source, m_Phase1Gray, result, TM_CCOEFF_NORMED);
	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.95)
	{
		if (m_phaseLastFrame == 5 || m_phaseLastFrame == 4 || m_phaseLastFrame == 3 || m_phaseLastFrame == 2)
		{
			ResetAll();
		}
		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, m_Phase1Gray.size()), Scalar(0, 0, 255), 2);
		m_phaseLastFrame = 1;
		return 1;
	}

	matchTemplate(Source, m_Phase2Gray, result, TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.95)
	{
		if (m_phaseLastFrame = 1)
		{
			ResetAll();
		}
		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, m_Phase2Gray.size()), Scalar(0, 0, 255), 2);
		m_phaseLastFrame = 2;
		return 2;
	}

	matchTemplate(Source, m_Phase3Gray, result, TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.95)
	{
		if (m_phaseLastFrame = 2)
		{
			ResetAll();
		}
		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, m_Phase3Gray.size()), Scalar(0, 0, 255), 2);
		m_phaseLastFrame = 3;
		return 3;
	}

	matchTemplate(Source, m_Phase4Gray, result, TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.95)
	{
		if (m_phaseLastFrame = 3)
		{
			ResetAll();
		}
		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, m_Phase4Gray.size()), Scalar(0, 0, 255), 2);
		m_phaseLastFrame = 4;
		return 4;
	}

	matchTemplate(Source, m_Phase5Gray, result, TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.95)
	{
		if (m_phaseLastFrame = 4)
		{
			ResetAll();
		}
		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, m_Phase5Gray.size()), Scalar(0, 0, 255), 2);
		m_phaseLastFrame = 5;
		return 5;
	}

	if (m_phaseLastFrame != 0)
	{
		return m_phaseLastFrame;
	}
	else
	{
		return 0;
	}
	
	return 0;
}

bool ScreenChecker::BlackVirusCheck(Mat &Source)
{

	Mat3b blackVirTemp = imread("BlackVirus.png");

	Mat1b blackVirTemp_gray;
	cvtColor(blackVirTemp, blackVirTemp_gray, COLOR_BGR2GRAY);

	//Match Template
	Mat1f result;
	matchTemplate(Source, blackVirTemp_gray, result, TM_CCOEFF_NORMED);
	//matchTemplate(src, templ, result, TM_SQDIFF);


	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.82)
	{


		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, blackVirTemp_gray.size()), Scalar(0, 0, 255), 2);
		return true;
	}
	return false;
}

bool ScreenChecker::RedVirusCheck(Mat &Source)
{

	Mat3b redVirTemp = imread("RedVirus.png");

	Mat1b redVirTemp_gray;
	cvtColor(redVirTemp, redVirTemp_gray, COLOR_BGR2GRAY);

	//Match Template
	Mat1f result;
	matchTemplate(Source, redVirTemp_gray, result, TM_CCOEFF_NORMED);
	//matchTemplate(src, templ, result, TM_SQDIFF);


	//Find highest response
	Point maxLoc;
	minMaxLoc(result, NULL, NULL, NULL, &maxLoc);
	if (result(maxLoc) > 0.82)
	{


		//Draw the red rectangle
		rectangle(src, Rect(maxLoc, redVirTemp_gray.size()), Scalar(0, 0, 255), 2);
		return true;
	}
	return false;
}

bool ScreenChecker::GreenAnimaCheck(Mat & Source)
{
	return false;
}

void ScreenChecker::Update()
{
	HWND hwndDesktop = GetDesktopWindow();
	RECT desktopSize;
	GetWindowRect(hwndDesktop, &desktopSize);

	PhaseArea = Rect(1, 1, (desktopSize.right / 2), 100);


		src = hwnd2mat(hwndDesktop);

		Mat1b img_gray;
		Mat1b templ_gray;
		cvtColor(src, img_gray, COLOR_BGR2GRAY);

		//DebuffCheck(img_gray, m_Phase1Gray);

		//Rect croppedRectangle = Rect(5, maxLoc.y - 50, 300, 100);
		//Mat CroppedImage = src(croppedRectangle);


		Mat1b PhaseCropped = img_gray(PhaseArea);

		Mat1b DebuffCropped = (!DebuffArea.empty()) ? img_gray(DebuffArea) : img_gray;

		Mat1b ChatCropped;

		if (!ChatArea.empty())
		{
			ChatCropped = img_gray(ChatArea);
		}
		else
		{
			ChatCropped = img_gray;
		}

		Rect Something;

		m_currentPhase = PhaseCheck(PhaseCropped);

		if (m_currentPhase == 1)
		{

			m_greenAnima = DebuffCheck(DebuffCropped, m_GreenAnimaGray, 0.98f);
			m_tendrils = AttackCheck(ChatCropped, m_TendrilsGray, 0.85f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_greenAnima)
			{
				if (!m_GAnimaFlag)
				{
					m_GAnimaFlag = true;
					cout << "GREEN ANIMA ACTIVE PEW PEW \n";
				}

			}
			else
			{
				m_GAnimaFlag = false;
			}


			if (m_tendrils)
			{
				lastFrameAbility = 0;
				if (!m_TendrilsFlag)
				{
					m_TendrilsFlag = true;
					m_Phase1Start = false;
					cout << "TENDRILS HAPPENED, NEXT IS GIELINOR \n";
				}
			}
			else
			{
				m_TendrilsFlag = false;
			}


			if (m_uppercut)
			{
				lastFrameAbility = 1;
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, HOLD STILL NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				lastFrameAbility = 2;
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, TENDRILS NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}


		if (m_currentPhase == 2)
		{

			m_blackAnima = DebuffCheck(DebuffCropped, m_BlackAnimaGray, 0.97f);
			m_blackVirus = DebuffCheck(DebuffCropped, m_BlackVirusGray, 0.82f);
			m_tendrils = AttackCheck(ChatCropped, m_TendrilsGray, 0.85f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_blackAnima)
			{

				if (!m_BAnimaFlag)
				{
					cout << "BLACK ANIMA ACTIVE GET OUT IF NOT INTENTIONAL \n";
					m_BAnimaFlag = true;
				}

			}
			else
			{
				m_BAnimaFlag = false;
			}


			if (m_blackVirus)
			{
				lastFrameAbility = 3;
				if (!m_BVirFlag)
				{
					m_BVirFlag = true;
					cout << "BLACK VIRUS ACTIVE GET TO BLACK STREAM, PREPARE FOR GIELINOR \n";
				}

			}
			else
			{
				m_BVirFlag = false;
			}


			if (m_tendrils)
			{
				lastFrameAbility = 0;
				if (!m_TendrilsFlag)
				{
					m_TendrilsFlag = true;
					cout << "TENDRILS HAPPENED, NEXT IS ONSLAUGHT, FOLLOWED BY HOLD STILL \n";
				}
			}
			else
			{
				m_TendrilsFlag = false;
			}


			if (m_uppercut)
			{
				lastFrameAbility = 1;
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, TENDRILS ARE NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				lastFrameAbility = 2;
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, BLACK VIRUS IS NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}

		if (m_currentPhase == 3)
		{

			m_redVirus = DebuffCheck(DebuffCropped, m_RedVirusGray, 0.82f);
			m_redAnima = DebuffCheck(DebuffCropped, m_RedAnimaGray, 0.98f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);
			m_animaCleanse = AttackCheck(ChatCropped, m_AnimaCleanseGray, 0.85f);

			if (m_redVirus)
			{
				lastFrameAbility = 4;
				if (!m_RVirFlag)
				{
					m_RVirFlag = true;
					cout << "RED VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_RVirFlag = false;
			}

			if (m_redAnima)
			{
				if (!m_RAnimaFlag)
				{
					m_RAnimaFlag = true;
					cout << "RED ANIMA ACTIVE PEWPEW \n";
				}

			}
			else
			{
				m_RAnimaFlag = false;
			}



			if (m_uppercut)
			{
				lastFrameAbility = 1;
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, HOLD STILL NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				lastFrameAbility = 2;
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, RED VIRUS NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}

		if (m_currentPhase == 4)
		{

			m_animaBomb = AttackCheck(ChatCropped, m_AnimaBombGray, 0.85f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_animaBomb)
			{
				lastFrameAbility = 5;
				if (!m_RVirFlag)
				{
					m_RVirFlag = true;
					cout << "ANIMA BOMB HAPPENED, NEXT IS HOLD STILL \n";
				}

			}
			else
			{
				m_RVirFlag = false;
			}



			if (m_uppercut)
			{
				lastFrameAbility = 1;
				if (!m_GielinorFlag)
				{
					m_GielinorFlag = true;
					cout << "UPPERCUT HAPPENED, ANIMA BOMB NEXT \n";
				}
			}
			else
			{
				m_GielinorFlag = false;
			}

			if (m_holdStill)
			{
				lastFrameAbility = 2;
				if (!m_HoldFlag)
				{
					m_HoldFlag = true;
					cout << "HOLD STILL HAPPENED, GIELINOR NEXT \n";
				}
			}
			else
			{
				m_HoldFlag = false;
			}


		}


		if (m_currentPhase == 5)
		{

			m_redVirus = DebuffCheck(DebuffCropped, m_RedVirusGray, 0.85f);
			m_blackVirus = DebuffCheck(DebuffCropped, m_BlackVirusGray, 0.85f);
			m_greenVirus = DebuffCheck(DebuffCropped, m_GreenVirusGray, 0.85f);
			m_redAnima = DebuffCheck(DebuffCropped, m_RedAnimaGray, 0.98f);
			m_greenAnima = DebuffCheck(DebuffCropped, m_GreenAnimaGray, 0.98f);
			m_blackAnima = DebuffCheck(DebuffCropped, m_BlackAnimaGray, 0.98f);
			m_uppercut = AttackCheck(ChatCropped, m_GielinorGray, 0.85f);
			m_holdStill = AttackCheck(ChatCropped, m_HoldStillGray, 0.85f);

			if (m_redVirus)
			{
				if (!m_RVirFlag)
				{
					m_RVirFlag = true;
					cout << "RED VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_RVirFlag = false;
			}

			if (m_redAnima)
			{
				if (!m_RAnimaFlag)
				{
					m_RAnimaFlag = true;
					cout << "RED ANIMA ACTIVE PEWPEW \n";
				}

			}
			else
			{
				m_RAnimaFlag = false;
			}


			if (m_blackVirus)
			{
				if (!m_BVirFlag)
				{
					m_BVirFlag = true;
					cout << "BLACK VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_BVirFlag = false;
			}

			if (m_blackAnima)
			{
				if (!m_BAnimaFlag)
				{
					m_BAnimaFlag = true;
					cout << "BLACK ANIMA ACTIVE GET OUT IF NOT INTENTIONAL \n";
				}

			}
			else
			{
				m_BAnimaFlag = false;
			}

			if (m_greenVirus)
			{
				if (!m_GVirFlag)
				{
					m_GVirFlag = true;
					cout << "GREEN VIRUS ACTIVE CLEANSE ASAP \n";
				}

			}
			else
			{
				m_GVirFlag = false;
			}

			if (m_greenAnima)
			{
				if (!m_GAnimaFlag)
				{
					m_GAnimaFlag = true;
					cout << "GREEN ANIMA ACTIVE PEWPEW \n";
				}

			}
			else
			{
				m_GAnimaFlag = false;
			}



		}

		//imshow("Result", ChatCropped);

		//Switch safeguards against messages being pushed off of chat location
		if (m_blackVirus == m_redVirus == m_holdStill == m_uppercut == m_tendrils == m_animaBomb == m_animaCleanse == false)
		{
			switch (lastFrameAbility)
			{
			case 0:
				m_tendrils = true;
				break;
			case 1:
				m_uppercut = true;
				break;
			case 2:
				m_holdStill = true;
				break;
			case 3:
				m_blackVirus = true;
				break;
			case 4:
				m_redVirus = true;
				break;
			case 5:
				m_animaBomb = true;
				default:
				break;
			}
		}
}

void ScreenChecker::ResetAll()
{
	m_GVirFlag = false;
	m_BVirFlag = false;
	m_RVirFlag = false;
	m_GAnimaFlag = false;
	m_BAnimaFlag = false;
	m_RAnimaFlag = false;
	m_HoldFlag = false;
	m_GielinorFlag = false;
	m_TendrilsFlag = false;
	m_AnimaBombFlag = false;

	m_greenVirus = false;
	m_blackVirus = false;
	m_redVirus = false;
	m_greenAnima = false;
	m_blackAnima = false;
	m_redAnima = false;
	m_holdStill = false;
	m_uppercut = false;
	m_tendrils = false;
	m_animaBomb = false;
}