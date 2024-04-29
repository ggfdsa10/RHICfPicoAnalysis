#ifndef testNeutronAsymmetry_HH
#define testNeutronAsymmetry_HH

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TString.h>
#include <TVirtualFitter.h>
#include <TLine.h>

class testNeutronAsymmetry
{
    const enum arrayPar
    {
        kFillNum = 5,
        kRunTypeNum = 3,
        kFinalBinPt = 5,
        kFinalBinXf = 5
    };

	public:
		testNeutronAsymmetry();
		~testNeutronAsymmetry();

        Int_t Init();
		Int_t Make();
		Int_t Finish();
		Int_t clear();

		void setFile(TString file);
        void setSaveFigPath(TString path);

        void setConditionName(TString name){mConditionName = name;}
        void setConditionName2(TString name){mConditionName2 = name;}
        void setEevntEndNum(int num = -1){mEventNum = num;}

        void neutronAsym();
        void doSDLE(); // do calculation for Single Diffactive Likely Events
        void doDDLE(); // do calculation for Double Diffactive Likely Events
        void doCDLE(); // do calculation for Central Diffactive Likely Events
        void doNDLE(); // do calculation for Non Diffactive Likely Events
        void doDMLE(); // do calculation for Diffactive Mass Likely Events
        void doTestCondition(); // do calculation for any test conditions 

        void doBinning(){mDoBinning = true;}
        void doFindBinMean(){mDoFindBinMean = true;}
        void doDilutionFactor(){mDoDilution = true;}
        void doAsymmetry(){mDoAsymmetry = true;}

        void doSaveData(){mDoSaveData = true;}
        void doDrawFigure(){mDoDrawFigure = true;}

	private: 
        void findBinMean();
        void dilutionFactor();
        void asymmetry();

        void drawFigure();
        int readData();
        void saveData();
        void info();

        bool conditionCheck();
        int bbcMultiplicity(int ew, int det);
        int vpdMultiplicity(int ew);

        int getRunTypeIdx(int fillNum);
        int getFillNumIdx(int fillNum);
        int getFillToRunTypeIdx(int fillIdx);

        double relativeluminosity(int fillIdx);
        double beamPolarization(int fillIdx);

	private: 
        TString mPath;
        TString mSaveDatPath;
        TString mSaveFigPath;
        TString mFilePath;
        TString mOutFileName;
        TString mRunName[kRunTypeNum];

        TString mConditionName;
        TString mConditionName2;
        int mEventNum;
        int mEventNeutronCounts;
        int mEventSelectedCounts;

        bool mIsAllEvent;
        bool mIsSDLEMode;
        bool mIsDDLEMode;
        bool mIsCDLEMode;
        bool mIsNDLEMode;
        bool mIsDMLEMode;
        bool mIsTestMode;

        bool mDoBinning;
        bool mDoFindBinMean;
        bool mDoDilution;
        bool mDoAsymmetry;

        bool mDoSaveData;
        bool mDoDrawFigure;
        bool mOptionChecker[5];

        // ======== for file and tree ============
		TFile* mAnalPi0File;
        TTree* mPi0Tree;

        Int_t mTofMult; // bTof tray multiplicity
        Int_t mGRefMult; // global track reference multiplicity
        Int_t mRefMult; // ??

        Int_t mBBCSWest[16][3]; // [pmt idx][adc, tdc, tac] 
        Int_t mBBCSEast[16][3]; // [pmt idx][adc, tdc, tac] 
        Int_t mBBCLWest[8][3]; // [pmt idx][adc, tdc, tac] 
        Int_t mBBCLEast[8][3]; // [pmt idx][adc, tdc, tac] 

        Int_t mBBCSSumWest;
        Int_t mBBCSSumEast;
        Int_t mBBCLSumWest;
        Int_t mBBCLSumEast;

        Int_t mVpdEast[16][2]; // [pmt idx][adc, tdc] 
        Int_t mVpdWest[16][2]; // [pmt idx][adc, tdc] 
        Int_t mVpdEastHighThr[16][2]; // Hight Threshold [pmt idx][adc, tdc] 
        Int_t mVpdWestHighThr[16][2]; // Hight Threshold [pmt idx][adc, tdc] 
        Int_t mVpdEarliestTDC[2]; // [East, West]
        Int_t mVpdEarliestTDCHighthr[2]; // [East, West]
        Int_t mVpdTimeDiff; // vpdTimeDifference
        Int_t mVPDSumWest;
        Int_t mVPDSumEast;

        Float_t mZDCADCSumEast;
        Float_t mZDCADCSumWest;
        Float_t mZDCADCEast[4];
        Float_t mZDCADCWest[4]; 
        Float_t mZDCVertexZ;

        Bool_t mIsShowerTrig;
        Bool_t mIsPi0Trig;  
        Bool_t mIsHighEMTrig;

        Float_t mL90[2];

        Int_t mPhotonNum;
        Int_t mPID[4];
        Int_t mPhotonTowerIdx[4];
        Double_t mPhotonPos[4][2];
        Double_t mPhotonE[4][2]; // photon, hadron
        Double_t mTowerEnergy[4][2];

        Bool_t mIsRHICfPi0;
        Int_t mPi0BunchNumber;
        Int_t mPi0fillNumber;
        Int_t mPi0TowerIdx;
        Int_t mPi0Type;
        Bool_t mPi0BlueSpinUp;
        Double_t mPi0X;
        Double_t mPi0Y;
        Double_t mPi0E;
        Double_t mPi0Px;
        Double_t mPi0Py;
        Double_t mPi0Pz;
        Double_t mPi0Pt;
        Double_t mPi0Xf;
        Double_t mPi0Mass;

        Int_t mTrackNum;
        Double_t mTrackEta[100];
        Double_t mTrackPhi[100];
        Double_t mTrackPt[100];
        Int_t mTrackPID[100];
        Double_t mTrackDca[100];
        Double_t mTrackPos[100][3];
        Double_t mTrackMom[100][3];
        Double_t mVertex[3];

        Int_t mFmsPhotonNum;
        Int_t mFmsPhotonFlag[100];
        Double_t mFmsPhotonPos[100][3];
        Double_t mFmsPhotonMom[100][3];
        Double_t mFmsPhotonE[100];
        

        // general data
        int mRunIdx;
        int mEventCount[kRunTypeNum];

        double mPtCutRangeAllXf[6]; // test
        double mXfCutRangeAllPt[6]; // test

        // for Asymmetry array
        double polNum[kFillNum][kFinalBinPt][2]; // [right, left]
        double polNumXf[kFillNum][kFinalBinXf][2]; // [right, left]

        // general histogram
        TH1D* hEnergy[kRunTypeNum];
        TH1D* hPt[kRunTypeNum];
        TH1D* hXf[kRunTypeNum];

        // for bin mean finding
        TH1D* hBinMean[kRunTypeNum][kFinalBinPt]; 
        double mBinMean[kRunTypeNum][kFinalBinPt][2]; // [sum, num]

        TH1D* hBinMeanXf[kRunTypeNum][kFinalBinXf]; 
        double mBinMeanXf[kRunTypeNum][kFinalBinXf][2]; // [sum, num]

        // for dilution factor
        TH1D* hPhi[kRunTypeNum][kFinalBinPt];
        double mDilutionFactor[kRunTypeNum][kFinalBinPt]; // sin(<phi>)

        TH1D* hPhiXf[kRunTypeNum][kFinalBinXf];
        double mDilutionFactorXf[kRunTypeNum][kFinalBinXf]; // sin(<phi>)

        // for asymmetry w/ only statistical uncertainty
        TGraphErrors* gGeneralAsymPt;
        TGraphErrors* gGeneralAsymXf;


        // for ADC Threshold cut array
        double mBBCSSumADCThr[2];
        double mBBCLSumADCThr[2];
        double mVPDSumADCThr[2];
        int mBBCSADCThr[2][16];
        int mBBCLADCThr[2][8];
        int mVPDADCThr[2][16];

};
#endif
