/***************************************************************************
 * Author: Akio Ogawa, Seunghwan Lee
 ***************************************************************************
 *
 * Description: This is the Hit maker for the RHICf data. 
 *
 ***************************************************************************
 * $Id: StRHICfHitMaker.cxx,v 1.4 2017/01/30 18:10:16 akio Exp $
 * $Log: StRHICfHitMaker.cxx,v $
 ***************************************************************************/

#ifndef StRHICfHitMaker_H
#define StRHICfHitMaker_H

#include "TMatrixD.h"
#include "TVectorD.h"
#include "TArrayD.h"

#include "StMaker.h"
#include "StRoot/StRHICfUtil/StRHICfFunction.h"

//test 
// #include <fstream>
// #include <iostream>
// #include <string>

class StRHICfDbMaker;
class StRHICfCollection;
class StRHICfRawHit;
class StRHICfHit;
class StMuRHICfUtil;

class StRHICfHitMaker : public StMaker, StRHICfFunction
{
	public: 
		StRHICfHitMaker(const Char_t* name="RHICfHit");
		~StRHICfHitMaker();

		int InitRun(int runNumber);
		int Make();
		int Finish();

	private:
		int caliPlate();
		int caliGSOBar();
		int genCrossTalkMatrix();
		int caliCrossTalk(); 

		TMatrixD* mCrossTalkMatrix;

		StRHICfDbMaker* mRHICfDbMaker = 0; 
		StRHICfCollection* mRHICfCollection = 0; 
		StRHICfRawHit* mRHICfRawHitColl = 0;
		StRHICfHit* mRHICfHitColl = 0;
		StMuRHICfUtil* mMuRHICfUtil = 0;

		const int mADCThreshold = 3600;

		// // test
		// ofstream writeTxt;
		// ofstream writeTxtNumber;

	ClassDef(StRHICfHitMaker,0);
};

#endif
