#ifndef SCREENCHECKER_H
#define SCREENCHECKER_H

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

using namespace cv;
using namespace std;

class ScreenChecker
{
public:
	ScreenChecker();
	~ScreenChecker();

	void Update();

	void SetCurrentPhase(int phase);

	inline bool GetGAnima() { return m_greenAnima; };
	inline bool GetBAnima() { return m_blackAnima; };
	inline bool GetRAnima() { return m_redAnima; };

	inline bool GetBVirus() { return m_blackVirus; };
	inline bool getGVirus() { return m_greenVirus; };
	inline bool getRVirus() { return m_redVirus; };

	inline bool GetGielinor() { return m_uppercut; };
	inline bool GetHoldStill() { return m_holdStill; };
	inline bool GetTendrils() { return m_tendrils; };
	inline bool GetABomb() { return m_animaBomb; };
	inline bool GetPhase1Start() { return m_Phase1Start; };
	inline bool GetAnimaCleanse() { return m_animaCleanse; };
	inline int GetPhase() { return m_currentPhase; };


private:
	Mat hwnd2mat(HWND hwnd);

	Mat src;

	Mat3b m_GreenVirus, m_BlackVirus, m_RedVirus, m_GreenAnima, m_BlackAnima, m_RedAnima, m_Tendrils, m_HoldStill, m_Gielinor, m_AnimaCleanse, m_AnimaBomb, m_GolemSpawn, m_OHKO;
	Mat3b m_Phase1, m_Phase2, m_Phase3, m_Phase4, m_Phase5;

	Mat1b m_GreenVirusGray, m_BlackVirusGray, m_RedVirusGray, m_GreenAnimaGray, m_BlackAnimaGray, m_RedAnimaGray, m_TendrilsGray, m_HoldStillGray, m_GielinorGray, m_AnimaCleanseGray;
	Mat1b m_AnimaBombGray, m_GolemSpawnGray, m_OHKOGray, m_Phase1Gray, m_Phase2Gray, m_Phase3Gray, m_Phase4Gray, m_Phase5Gray;

	void ImageSetup();
	void ResetAll();

	bool GreenVirusCheck(Mat &Source);
	bool BlackVirusCheck(Mat &Source);
	bool RedVirusCheck(Mat &Source);

	bool DebuffCheck(Mat &Source, Mat1b &Debuff, float thresh);
	bool AttackCheck(Mat &Source, Mat1b &Debuff, float thresh);
	int PhaseCheck(Mat &Source);

	bool GreenAnimaCheck(Mat &Source);
	bool BlackAnimaCheck(Mat &Source);
	bool RedAnimaCheck(Mat &Source);

	bool HoldStillCheck(Mat &Source);
	bool UppercutCheck(Mat &Source);
	bool TendrilsCheck(Mat &Source);
	bool AnimaBombCheck(Mat &Source);
	
	Point m_debuffLoc;
	Point m_chatLoc;

	Rect PhaseArea;
	Rect DebuffArea;
	Rect ChatArea;

	int m_currentPhase;
	int m_phaseLastFrame;

	bool m_greenVirus;
	bool m_blackVirus;
	bool m_redVirus;
	
	bool m_greenAnima;
	bool m_blackAnima;
	bool m_redAnima;

	bool m_holdStill;
	bool m_uppercut;
	bool m_tendrils;
	bool m_animaBomb;
	bool m_animaCleanse;

	int lastFrameAbility;

	bool m_Phase1Start = true;

	//These are flags so that a trigger is only sent off once per true activation
	bool m_GVirFlag, m_BVirFlag, m_RVirFlag, m_GAnimaFlag, m_BAnimaFlag, m_RAnimaFlag, m_HoldFlag, m_GielinorFlag, m_TendrilsFlag, m_AnimaBombFlag;


};

#endif