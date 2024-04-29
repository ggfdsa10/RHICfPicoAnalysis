#ifndef Pi0Asymmetry_HH
#define Pi0Asymmetry_HH

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

class Pi0Asymmetry
{
    const enum arrayPar
    {
        kFillNum = 5,
        kRunTypeNum = 3,
        kPi0TypeNum = 2,
        kGeneralXfRangeNum = 5,
        kGeneralPtRangeNum = 7,
        kGeneralBinXf = 4,
        kGeneralBinPt = 6,
        kBinningNum = 20,
        kBinningRangeNum = 21,
        kFinalBinXf = 4,
        kFinalBinPt = 4,
        kTmpBinXf = 2,
        kTmpBinPt = 2,
    };

	public:
		Pi0Asymmetry();
		~Pi0Asymmetry();

        Int_t Init();
		Int_t Make();
		Int_t Finish();
		Int_t clear();

		void setFile(TString file);
        void setSaveFigPath(TString path);

        void setConditionName(TString name){mConditionName = name;}
        void setConditionName2(TString name){mConditionName2 = name;}
        void setEevntEndNum(int num = -1){mEventNum = num;}

        void doSDLE(){mIsSDLEMode = true;} // do calculation for Single Diffactive Likely Events
        void doDDLE(){mIsDDLEMode = true;} // do calculation for Double Diffactive Likely Events
        void doHDLE(){mIsHDLEMode = true;} // do calculation for High-Mass Pi0 Diffactive Likely Events

        void doFindGenMassCut(){mDoFindGenMassCut = true;}
        void doBinning(){mDoBinning = true;}
        void doBkgEstimation(){mDoBkgEstimation = true;}
        void doFindBinMean(){mDoFindBinMean = true;}
        void doDilutionFactor(){mDoDilution = true;}
        void doAsymmetry(){mDoAsymmetry = true;}
        void notCalculBkg(){mNotCalBkg = true;}

        void doSaveData(){mDoSaveData = true;}
        void doDrawFigure(){mDoDrawFigure = true;}

	private: 
        void findGenMassCut();
        void binningXF();
        void binningPT();
        void bkgEstimation();
        void findBinMean();
        void dilutionFactor();
        void asymmetry();

        void drawFigure();
        int readData();
        void saveData();
        void info();

        int getRunTypeIdx(int fillNum);
        int getFillNumIdx(int fillNum);
        int getFillToRunTypeIdx(int fillIdx);

        double relativeluminosity(int fillIdx);
        double beamPolarization(int fillIdx);

        void massFitting(TH1D* mass);
        void getMassFitPar(double* par);

        double gausFit(double* x, double* par);
        double polFit(double* x, double* par);
        double polGausFit(double* x, double* par);


	private: 
        TString mPath;
        TString mSaveDatPath;
        TString mSaveFigPath;
        TString mFilePath;
        TString mRunName[kRunTypeNum];

        TString mConditionName;
        TString mConditionName2;
        int mEventNum;

        bool mIsSDLEMode;
        bool mIsDDLEMode;
        bool mIsHDLEMode;

        bool mDoFindGenMassCut;
        bool mDoBinning;
        bool mDoBkgEstimation;
        bool mDoFindBinMean;
        bool mDoDilution;
        bool mDoAsymmetry;
        bool mNotCalBkg;
        bool mDoSaveData;
        bool mDoDrawFigure;
        bool mOptionChecker[5];

        // ======== for file and tree ============
		TFile* mAnalPi0File;
        TTree* mPi0Tree;

        Int_t mTofMult; // bTof tray multiplicity
        Int_t mGRefMult; // global track reference multiplicity
        Int_t mRefMult; // ??

        Int_t mBBCWest; // bbc west adc sum
        Int_t mBBCEast; // bbc east adc sum
        Int_t mBBCLargeWest; // bbc large west adc sum
        Int_t mBBCLargeEast; // bbc large east adc sum
        Int_t mVPDWest; // vpd west adc sum
        Int_t mVPDEast; // vpd east adc sum

        Float_t mZDCADCSumEast;
        Float_t mZDCADCSumWest;
        Float_t mZDCADCEast[4];
        Float_t mZDCADCWest[4]; 
        Float_t mZDCVertexZ;

        Bool_t mIsShowerTrig;
        Bool_t mIsPi0Trig;  
        Bool_t mIsHighEMTrig;

        Float_t mL90[2];

        Bool_t mTmpPhotonIdx[4];
        Int_t mPhotonNum;
        Int_t mPID[4];
        Int_t mPhotonTowerIdx[4];
        Double_t mPhotonPos[4][2];
        Double_t mPhotonE[4][2]; // photon, hadron
        Double_t mTowerEnergy[4][2];

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
        int mTypeIdx;
        int mEventCount[kRunTypeNum][kPi0TypeNum];

        // general mass cut range array
        double mGenMassCutRange[kRunTypeNum][kPi0TypeNum][2]; // mean , sigma

        // general range for all runs array
        double mGenRangePT[kGeneralPtRangeNum];
        double mGenRangeXF[kGeneralXfRangeNum];

        // type-dependent range  array 
        double mXfCutRange[kRunTypeNum][kPi0TypeNum][5]; // [run type][pi0 type][boundary]
        double mPtCutRange[kRunTypeNum][kPi0TypeNum][5]; // [run type][pi0 type][boundary]
        double mPtCutRangeAllXf[6];  // test  for type-1 pi0
        double mMassCutRange[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][2]; // [mean, sigma]

        // for Asymmetry array
        double polNum[kFillNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][2]; // [right, left]
        double bkgPolNum[kFillNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][2]; // [right, left]

        // general histogram
        TH1D* hMassAll[kRunTypeNum][kPi0TypeNum];
        TH1D* hEnergy[kRunTypeNum][kPi0TypeNum];
        TH1D* hPt[kRunTypeNum][kPi0TypeNum];
        TH1D* hXf[kRunTypeNum][kPi0TypeNum];
        TH2D* hpt_xf[kRunTypeNum][kPi0TypeNum];

        // for binning each runs 
        double mInitBinRange[kBinningRangeNum];
        TH1D* hPtInXfBin[kRunTypeNum][kPi0TypeNum][kBinningNum];
        TH1D* hXfInPtBin[kRunTypeNum][kPi0TypeNum][kBinningNum];
        

        // for background estimations
        TH1D* hMass[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt];
        double mMassFitIntegral[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][3]; // [totalFitNum, signalFitNum, bkgFitNum] in signal 3 sigma

        // for bin mean finding
        TH1D* hBinMean[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][2]; // [xf, pt]
        double mBinMean[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][2][2]; // [xf, pt][sum, num]

        // for dilution factor
        TH1D* hPhi[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt];
        double mDilutionFactor[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt]; // sin(<phi>)

        // for asymmetry w/ only statistical uncertainty
        TGraphErrors* gAsymByXf[kRunTypeNum][kPi0TypeNum][kFinalBinPt];
        TGraphErrors* gAsymByPt[kRunTypeNum][kPi0TypeNum][kFinalBinXf];
        TGraphErrors* gBkgAsymXf[kRunTypeNum][kPi0TypeNum][kFinalBinPt];
        TGraphErrors* gBkgAsymPt[kRunTypeNum][kPi0TypeNum][kFinalBinXf];
        TGraphErrors* gTypeAsymByXf[kRunTypeNum][kPi0TypeNum][kGeneralBinPt];
        TGraphErrors* gTypeAsymByPt[kRunTypeNum][kPi0TypeNum][kGeneralBinXf];
        TGraphErrors* gRunAsymByXf[kRunTypeNum][kGeneralBinPt];
        TGraphErrors* gRunAsymByPt[kRunTypeNum][kGeneralBinXf];
        TGraphErrors* gGeneralAsymByXf[kGeneralBinPt];
        TGraphErrors* gGeneralAsymByPt[kGeneralBinXf];
        TGraphErrors* gGeneralAsymPt;
        TGraphErrors* gTmpAsymPt;

        // for mass fitting function
        TF1* fMassFit;
        TF1* fMassBkgFit;
        TF1* fMassSignalFit;
        TF1* fbinningLandau;

};
#endif
