// ============================================================ 
// | The StRHICfPi0Maker class                                | 
// | for only RHICf asymmetries of the nuetral Pion analysis. | 
// |                                                          | 
// | Author: Seunghwan Lee.                                   | 
// ============================================================ 

#ifndef StRHICfPi0Maker_HH
#define StRHICfPi0Maker_HH

#include <iostream>
#include <TROOT.h>
#include <TString.h>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "TVector3.h"
#include "TRandom3.h"
#include "TH1D.h"

#include "StMaker.h"
#include "StRHICfPool/StRHICfPi0Maker/StRHICfPi0Events.h"
#include "StRHICfPool/StRHICfPi0Maker/StRHICfPi0.h"

#include "StRHICfUtil/StRHICfFunction.h"

class StEvent;
class StMuEvent;
class StMuDst;
class StMuDstMaker;

class StMuRHICfCollection;
class StMuRHICfRawHit;
class StMuRHICfHit;
class StMuRHICfPoint;

class StMuFmsCollection;
class StMuRpsUtil;
class StMuRpsCollection;
class StMuRpsCollection2;

using namespace std;
using namespace TMath;

class StRHICfPi0Maker : public StMaker, StRHICfFunction
{
	public: 
		StRHICfPi0Maker(int ioMode, const char* fileName, StMuDstMaker* muDstMaker = 0, const char* name="RHICfPi0");
		~StRHICfPi0Maker();

		Int_t Init();
		Int_t Make();
		Int_t Finish();
		Int_t clear();

		// for read a AnalRHICfPi0 files
		Int_t getAnalEntries();
		Int_t getNFiles();
		StRHICfPi0Events* getRHICfPi0Events(Int_t idx);

	private:
		// general 
		Int_t openRead();
		Int_t openWrite();

		void spinPatternData();
		void fillData();

		// for RHICf Pi0
		Bool_t eventCut(StMuRHICfPoint* point);
		void convertIPSystem(bool metOpt, bool referOpt=0);
		void kinematics();
		Double_t beamCenterPosition(int xy, bool metOpt, bool referOpt=0); // metOpt: scan & hit mode, referOpt: refer to fill number(21148, 21150) in only TOP type.
																		   // metOpt false = scan, true = hit mode , referOpt false = 21148, true = 21450 using mode.
		Double_t relativeluminosity(Int_t fillNum); // temporary functions.
		Double_t beamPolarization(Int_t fillNum); // temporary functions.
		
		// for STAR sub-detectors
		Int_t triggerDetectorData();
		Int_t vertex();
		Int_t trackData();
		Int_t fmsData();
		Int_t rpsData();

		// Out data structrue
		int mIoMode;
		Int_t mNFiles;
		TString mInputFileName;
		TString mOutputFileName;
		TString mFileTypeName;

		TFile* mTFile = 0;
		TTree* mOutTree = 0;
		TClonesArray* mOutDataArray = 0;
		StRHICfPi0Events* mRHICfPi0Events = 0;

		// AnalRHICfPi0 Reader
		TChain* mChain = 0;
		TClonesArray* mReadDataArray = 0;

		// Spin table
		int spinPatterns[5][120][2]; // [Fill number][bunch number][blue, yellow] for Fill no. 21142, 21145, 21148, 21149, 21150

		// Event Coll.
		StMuDstMaker* muDstMaker;
		StMuDst* muDst;
		StMuEvent* muEvent;
		StEvent* dsEvent;
		Long64_t iEvent;

		// RHICf Coll.
		StMuRHICfCollection* muRHICfColl;
		StMuRHICfRawHit* muRHICfRawHit;
		StMuRHICfHit* muRHICfHit;

		// Track Coll.
		TObjArray* mMuGTrks; // global tracks
		TObjArray* mMuTrks; // primary tracks
		TVector3 mVertexVec;
		Float_t mTpcVpdVzDiffCut;
		
		// FMS Coll.
		StMuFmsCollection* muFmsColl;
		// Roman Pots Coll.
		StMuRpsCollection* mMuRpsColl;
		StMuRpsUtil* mMuRpsUtil;

		// const double distZatIP = 17812.0; // [mm] Distance of the beam from interaction point to RHICf detector.
		const double distZatIP = 18000.0; // [mm] Distance of the beam from interaction point to RHICf detector.
		const double geoCenterTL = 20.0; // [mm] geometrical large tower center
		const double geoCenterTS = 10.0; // [mm] geometrical small tower center
		const double distTStoTL = 47.4; // [mm] Distance between center of TL and cernter of TS

		int fillNumArray[5];

	protected:
		enum ioMode {ioRead, ioWrite};


	ClassDef(StRHICfPi0Maker,0);
};

#endif
