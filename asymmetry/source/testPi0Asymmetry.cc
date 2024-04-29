#include "testPi0Asymmetry.hh"

testPi0Asymmetry::testPi0Asymmetry()
{
    mIsAllEvent = false;
    mIsSDLEMode = false;
    mIsDDLEMode = false;
    mIsCDLEMode = false;
    mIsNDLEMode = false;
    mIsDMLEMode = false;
    mIsTestMode = false;

    mDoFindGenMassCut = false;
    mDoFindBinMean = false;
    mDoDilution = false;
    mDoAsymmetry = false;
    mNotCalBkg = false;
    mDoSaveData; = false;
    mDoDrawFigure = false;

    mEventPi0Counts = 0;
    mEventSelectedCounts = 0;

    mPath = "/star/u/slee5/forRHICf/asymmetry";
    mSaveDatPath = mPath+"/data";
    mSaveFigPath = mPath+"/figure";
    mFilePath = mSaveDatPath+"/AnalRHICfPi0.root";
    mOutFileName = mSaveDatPath+"/asymPi0.root";

    mConditionName = "All";
    mConditionName2 = "ALL";
    mEventNum = -1;

    mRunName[0] = "TL";
    mRunName[1] = "TS";
    mRunName[2] = "TOP";

    mBBCSSumADCThr[0] = 40.;
    mBBCSSumADCThr[1] = 40.;
    mBBCLSumADCThr[0] = 6.;
    mBBCLSumADCThr[1] = 4.;
    mVPDSumADCThr[0] = 10.;
    mVPDSumADCThr[1] = 10.;


    // test temp code for ADC Threshold by channel

    // BBC Small East 
    mBBCSADCThr[0][0] = 4;
    mBBCSADCThr[0][1] = 8;
    mBBCSADCThr[0][2] = 4;
    mBBCSADCThr[0][3] = 3;
    mBBCSADCThr[0][4] = 14;
    mBBCSADCThr[0][5] = 6;
    mBBCSADCThr[0][6] = 6;
    mBBCSADCThr[0][7] = 3;
    mBBCSADCThr[0][8] = 6;
    mBBCSADCThr[0][9] = 9;
    mBBCSADCThr[0][10] = 5;
    mBBCSADCThr[0][11] = 5;
    mBBCSADCThr[0][12] = 2;
    mBBCSADCThr[0][13] = 4;
    mBBCSADCThr[0][14] = 3;
    mBBCSADCThr[0][15] = 5;

    // BBC Small West 
    mBBCSADCThr[1][0] = 8;
    mBBCSADCThr[1][1] = 6;
    mBBCSADCThr[1][2] = 5;
    mBBCSADCThr[1][3] = 15;
    mBBCSADCThr[1][4] = 9;
    mBBCSADCThr[1][5] = 9;
    mBBCSADCThr[1][6] = 7;
    mBBCSADCThr[1][7] = 16;
    mBBCSADCThr[1][8] = 19;
    mBBCSADCThr[1][9] = 40;
    mBBCSADCThr[1][10] = 4;
    mBBCSADCThr[1][11] = 5;
    mBBCSADCThr[1][12] = 5;
    mBBCSADCThr[1][13] = 8;
    mBBCSADCThr[1][14] = 12;
    mBBCSADCThr[1][15] = 4;

    // BBC Large East 
    mBBCLADCThr[0][0] = 6;
    mBBCLADCThr[0][1] = 6;
    mBBCLADCThr[0][2] = 7;
    mBBCLADCThr[0][3] = 4;
    mBBCLADCThr[0][4] = 4;
    mBBCLADCThr[0][5] = 12;
    mBBCLADCThr[0][6] = 5;
    mBBCLADCThr[0][7] = 12;

    // BBC Large West  
    mBBCLADCThr[1][0] = 0; // dead channel in 21148 fill
    mBBCLADCThr[1][1] = 4; 
    mBBCLADCThr[1][2] = 0; // dead channel in 21148 fill
    mBBCLADCThr[1][3] = 2;
    mBBCLADCThr[1][4] = 7;
    mBBCLADCThr[1][5] = 8;
    mBBCLADCThr[1][6] = 4;
    mBBCLADCThr[1][7] = 4;

    // VPD East
    mVPDADCThr[0][0] = 3;
    mVPDADCThr[0][1] = 4;
    mVPDADCThr[0][2] = 3;
    mVPDADCThr[0][3] = 4;
    mVPDADCThr[0][4] = 3;
    mVPDADCThr[0][5] = 3;
    mVPDADCThr[0][6] = 3;
    mVPDADCThr[0][7] = 4;
    mVPDADCThr[0][8] = 3;
    mVPDADCThr[0][9] = 3;
    mVPDADCThr[0][10] = 3;
    mVPDADCThr[0][11] = 3;
    mVPDADCThr[0][12] = 4;
    mVPDADCThr[0][13] = 3;
    mVPDADCThr[0][14] = 4;
    mVPDADCThr[0][15] = 1;

    // VPD West
    mVPDADCThr[1][0] = 1;
    mVPDADCThr[1][1] = 0; // dead channel in 21148 fill
    mVPDADCThr[1][2] = 1;
    mVPDADCThr[1][3] = 1;
    mVPDADCThr[1][4] = 1;
    mVPDADCThr[1][5] = 1;
    mVPDADCThr[1][6] = 1;
    mVPDADCThr[1][7] = 1;
    mVPDADCThr[1][8] = 0; // dead channel in 21148 fill
    mVPDADCThr[1][9] = 1;
    mVPDADCThr[1][10] = 1;
    mVPDADCThr[1][11] = 1;
    mVPDADCThr[1][12] = 1;
    mVPDADCThr[1][13] = 1;
    mVPDADCThr[1][14] = 1;
    mVPDADCThr[1][15] = 1;
}

testPi0Asymmetry::~testPi0Asymmetry()
{
}

void testPi0Asymmetry::doSDLE(){
    mIsSDLEMode = true;
    mConditionName2 = "SDLE";
}

void testPi0Asymmetry::doDDLE(){
    mIsDDLEMode = true;
    mConditionName2 = "DDLE";
}

void testPi0Asymmetry::doCDLE(){
    mIsCDLEMode = true;
    mConditionName2 = "CDLE";
}

void testPi0Asymmetry::doNDLE(){
    mIsNDLEMode = true;
    mConditionName2 = "NDLE";
}

void testPi0Asymmetry::doDMLE(){
    mIsDMLEMode = true;
    mConditionName2 = "DMLE";
}

void testPi0Asymmetry::doTestCondition(){
    mIsTestMode = true;
}


Int_t testPi0Asymmetry::Init()
{
    cout << "testPi0Asymmetry::Init() --- information" << endl;
    info();


    if(!mIsSDLEMode && !mIsDDLEMode && !mIsCDLEMode && !mIsNDLEMode && !mIsDMLEMode && !mIsTestMode){
       cout << "testPi0Asymmetry::Init() --- Warning!!! event mode is NOT setted, set the all event mode" << endl;
       mIsAllEvent = true;
    }

    mOutFileName = mSaveDatPath + "/asymmetry_" + mConditionName + "_" + mConditionName2 + ".root";


    mAnalPi0File = new TFile(Form("%s", mFilePath.Data()), "read");
    mPi0Tree = (TTree*)mAnalPi0File->Get("pi0");

	mPi0Tree -> SetBranchAddress("tofMult", &mTofMult);
	mPi0Tree -> SetBranchAddress("gloMult", &mGRefMult);
	mPi0Tree -> SetBranchAddress("refMult", &mRefMult);

    mPi0Tree -> SetBranchAddress("bbcSWest", &mBBCSWest);
	mPi0Tree -> SetBranchAddress("bbcSEast", &mBBCSEast);
	mPi0Tree -> SetBranchAddress("bbcLWest", &mBBCLWest);
	mPi0Tree -> SetBranchAddress("bbcLEast", &mBBCLEast);

	mPi0Tree -> SetBranchAddress("bbcSSumWest", &mBBCSSumWest);
	mPi0Tree -> SetBranchAddress("bbcSSumEast", &mBBCSSumEast);
	mPi0Tree -> SetBranchAddress("bbcLSumWest", &mBBCLSumWest);
	mPi0Tree -> SetBranchAddress("bbcLSumEast", &mBBCLSumEast);

	mPi0Tree -> SetBranchAddress("vpdWest", &mVpdWest);
	mPi0Tree -> SetBranchAddress("vpdEast", &mVpdEast);
	mPi0Tree -> SetBranchAddress("vpdHighThrWest", &mVpdWestHighThr);
	mPi0Tree -> SetBranchAddress("vpdHighThrEast", &mVpdEastHighThr);
	mPi0Tree -> SetBranchAddress("vpdEarliestTDC", &mVpdEarliestTDC);
	mPi0Tree -> SetBranchAddress("vpdEarliestTDCHighThr", &mVpdEarliestTDCHighthr);
	mPi0Tree -> SetBranchAddress("vpdTimeDiff", &mVpdTimeDiff);
	
	mPi0Tree -> SetBranchAddress("vpdSumWest", &mVPDSumWest);
	mPi0Tree -> SetBranchAddress("vpdSumEast", &mVPDSumEast);

	mPi0Tree -> SetBranchAddress("zdcADCSumEast", &mZDCADCSumEast);
	mPi0Tree -> SetBranchAddress("zdcADCSumWest", &mZDCADCSumWest);
	mPi0Tree -> SetBranchAddress("zdcADCEast", &mZDCADCEast);
	mPi0Tree -> SetBranchAddress("zdcADCWest", &mZDCADCWest);
	mPi0Tree -> SetBranchAddress("zdcVertexZ", &mZDCVertexZ);

	mPi0Tree -> SetBranchAddress("isShowerTrig", &mIsShowerTrig);
	mPi0Tree -> SetBranchAddress("isPi0Trig", &mIsPi0Trig);
	mPi0Tree -> SetBranchAddress("isHighEMTrig", &mIsHighEMTrig);

	mPi0Tree -> SetBranchAddress("L90", &mL90);

	mPi0Tree -> SetBranchAddress("photonNum", &mPhotonNum);
	mPi0Tree -> SetBranchAddress("photonPid", &mPID);
	mPi0Tree -> SetBranchAddress("photonTowerIdx", &mPhotonTowerIdx);
	mPi0Tree -> SetBranchAddress("photonPos", &mPhotonPos);
	mPi0Tree -> SetBranchAddress("photonE", &mPhotonE);
	mPi0Tree -> SetBranchAddress("towerEnergy", &mTowerEnergy);

    mPi0Tree -> SetBranchAddress("isRHICfPi0", &mIsRHICfPi0);
	mPi0Tree -> SetBranchAddress("bunchNumber", &mPi0BunchNumber);
	mPi0Tree -> SetBranchAddress("fillNumber", &mPi0fillNumber);
	mPi0Tree -> SetBranchAddress("towerIdx", &mPi0TowerIdx);
	mPi0Tree -> SetBranchAddress("type", &mPi0Type);
	mPi0Tree -> SetBranchAddress("blueSpinUp", &mPi0BlueSpinUp);
	mPi0Tree -> SetBranchAddress("x", &mPi0X);
	mPi0Tree -> SetBranchAddress("y", &mPi0Y);
	mPi0Tree -> SetBranchAddress("e", &mPi0E);
	mPi0Tree -> SetBranchAddress("px", &mPi0Px);
	mPi0Tree -> SetBranchAddress("py", &mPi0Py);
	mPi0Tree -> SetBranchAddress("pz", &mPi0Pz);
	mPi0Tree -> SetBranchAddress("pt", &mPi0Pt);
	mPi0Tree -> SetBranchAddress("xf", &mPi0Xf);
	mPi0Tree -> SetBranchAddress("m", &mPi0Mass);

	mPi0Tree -> SetBranchAddress("trackNum", &mTrackNum);
	mPi0Tree -> SetBranchAddress("trackEta", &mTrackEta);
	mPi0Tree -> SetBranchAddress("trackPhi", &mTrackPhi);
	mPi0Tree -> SetBranchAddress("trackPt", &mTrackPt);
	mPi0Tree -> SetBranchAddress("trackPID", &mTrackPID);
	mPi0Tree -> SetBranchAddress("trackDca", &mTrackDca);
	mPi0Tree -> SetBranchAddress("trackPos", &mTrackPos);
	mPi0Tree -> SetBranchAddress("trackMom", &mTrackMom);
	mPi0Tree -> SetBranchAddress("vertex", &mVertex);

	mPi0Tree -> SetBranchAddress("fmsPhotonNum", &mFmsPhotonNum);
	mPi0Tree -> SetBranchAddress("fmsPhotonFlag", &mFmsPhotonFlag);
	mPi0Tree -> SetBranchAddress("fmsPhotonPos", &mFmsPhotonPos);
	mPi0Tree -> SetBranchAddress("fmsPhotonMom", &mFmsPhotonMom);
	mPi0Tree -> SetBranchAddress("fmsPhotonE", &mFmsPhotonE);

    memset(mEventCount, 0, sizeof(mEventCount));
    memset(mGenMassCutRange, 0, sizeof(mGenMassCutRange));
    memset(mPtCutRangeAllXf, 0, sizeof(mPtCutRangeAllXf));
    memset(mBinMean, 0, sizeof(mBinMean));
    memset(mMassFitIntegral, 0, sizeof(mMassFitIntegral));
    memset(mMassCutRange, 0, sizeof(mMassCutRange));
    memset(mDilutionFactor, 0, sizeof(mDilutionFactor));
    memset(polNum, 0, sizeof(polNum));

    mPtCutRangeAllXf[0][0] = 0.;
    mPtCutRangeAllXf[0][1] = 0.1;
    mPtCutRangeAllXf[0][2] = 0.2;
    mPtCutRangeAllXf[0][3] = 1.;
    mPtCutRangeAllXf[0][4] = 1.;

    mPtCutRangeAllXf[1][0] = 0.3;
    mPtCutRangeAllXf[1][1] = 1.;
    mPtCutRangeAllXf[1][2] = 1.;
    mPtCutRangeAllXf[1][3] = 1.;
    mPtCutRangeAllXf[1][4] = 1.;

    mXfCutRangeAllPt[0][0] = 0.;
    mXfCutRangeAllPt[0][1] = 0.2;
    mXfCutRangeAllPt[0][2] = 0.4;
    mXfCutRangeAllPt[0][3] = 0.6;
    mXfCutRangeAllPt[0][4] = 0.8;

    mXfCutRangeAllPt[1][0] = 0.;
    mXfCutRangeAllPt[1][1] = 0.2;
    mXfCutRangeAllPt[1][2] = 0.4;
    mXfCutRangeAllPt[1][3] = 0.6;
    mXfCutRangeAllPt[1][4] = 0.8;

    // read datas
    if(!readData()){return 0;}

    mRunIdx = -1;
    mTypeIdx = -1;

    for(int run = 0; run < kRunTypeNum; run++){
        for(int type=0; type < kPi0TypeNum; type++){
            hMassAll[run][type] = new TH1D(Form("mass_All_type%i_%s", type+1, mRunName[run].Data()), Form("mass_All_type%i_%s", type+1, mRunName[run].Data()), 100, 0, 300);
            hMassAll[run][type] -> SetTitle("; m_{#gamma#gamma} [MeV/c^{2}];");
            hMassAll[run][type] -> SetStats(0);
        
            hEnergy[run][type] = new TH1D(Form("energy_type%i_pi0_%s", type+1, mRunName[run].Data()), Form("energy_type%i_pi0_%s", type+1, mRunName[run].Data()), 300, 0, 300);
            hPt[run][type] = new TH1D(Form("pt_type%i_pi0_%s", type+1, mRunName[run].Data()), Form("pt_type%i_pi0_%s", type+1, mRunName[run].Data()), 20, 0, 1.);
            hXf[run][type] = new TH1D(Form("xf_type%i_pi0_%s", type+1, mRunName[run].Data()), Form("xf_type%i_pi0_%s", type+1, mRunName[run].Data()), 20, 0, 1.);

            hEnergy[run][type] -> SetTitle(Form("type%i #pi^{0} Energy; Energy [GeV];", type+1));
            hPt[run][type] -> SetTitle(Form("type%i #pi^{0} p_{T}; p_{T} [GeV/c];", type+1));
            hXf[run][type] -> SetTitle(Form("type%i #pi^{0} p_{T}; x_{F};", type+1));

            hEnergy[run][type] -> SetStats(0);
            hPt[run][type] -> SetStats(0);
            hXf[run][type] -> SetStats(0);

            for(int pt=0; pt<kFinalBinPt; pt++){
                if(mDoBkgEstimation){
                    hMass[run][type][pt] = new TH1D(Form("hMass_%s_type%i_p%i", mRunName[run].Data(), type+1, pt), Form("hMass_%s_type%i_p%i", mRunName[run].Data(), type+1, pt), 80, 0., 300.);
                    hMass[run][type][pt] -> SetTitle("; m_{#gamma#gamma} [MeV/c^{2}];");
                    hMass[run][type][pt] -> SetStats(0);
                }

                if(mDoFindBinMean){
                    hBinMean[run][type][pt] = new TH1D(Form("hBinMean_%s_type%i_p%i", mRunName[run].Data(), type+1, pt), Form("hBinMean_%s_type%i_p%i", mRunName[run].Data(), type+1, pt), 100, 0., 1.);
                    hBinMean[run][type][pt] -> SetTitle(Form("%s type%i #pi^{0}; p_{T};", mRunName[run].Data(), type+1));
                    hBinMean[run][type][pt] -> SetStats(0);
                }

                if(mDoDilution){
                    hPhi[run][type][pt] = new TH1D(Form("hPhi_%s_type%i_p%i", mRunName[run].Data(), type+1, pt), Form("hPhi_%s_type%i_p%i", mRunName[run].Data(), type+1, pt), 100, 0., 180.);
                    hPhi[run][type][pt] -> SetTitle("; #phi_{#pi^{0}} [#circ];");
                    hPhi[run][type][pt] -> SetStats(0);
                }
            }

            // for Xf
            for(int xf=0; xf<kFinalBinXf; xf++){
                if(mDoBkgEstimation){
                    hMassXf[run][type][xf] = new TH1D(Form("hMass_xf_%s_type%i_p%i", mRunName[run].Data(), type+1, xf), Form("hMass_xf_%s_type%i_p%i", mRunName[run].Data(), type+1, xf), 80, 0., 300.);
                    hMassXf[run][type][xf] -> SetTitle("; m_{#gamma#gamma} [MeV/c^{2}];");
                    hMassXf[run][type][xf] -> SetStats(0);
                }

                if(mDoFindBinMean){
                    hBinMeanXf[run][type][xf] = new TH1D(Form("hBinMean_xf_%s_type%i_p%i", mRunName[run].Data(), type+1, xf), Form("hBinMean_xf_%s_type%i_p%i", mRunName[run].Data(), type+1, xf), 100, 0., 1.);
                    hBinMeanXf[run][type][xf] -> SetTitle(Form("%s type%i #pi^{0}; p_{T};", mRunName[run].Data(), type+1));
                    hBinMeanXf[run][type][xf] -> SetStats(0);
                }

                if(mDoDilution){
                    hPhiXf[run][type][xf] = new TH1D(Form("hPhi_xf_%s_type%i_p%i", mRunName[run].Data(), type+1, xf), Form("hPhi_xf_%s_type%i_p%i", mRunName[run].Data(), type+1, xf), 100, 0., 180.);
                    hPhiXf[run][type][xf] -> SetTitle("; #phi_{#pi^{0}} [#circ];");
                    hPhiXf[run][type][xf] -> SetStats(0);
                }
            }
            
        }


    }
    if(mDoAsymmetry){
        gGeneralAsymPtType[0] = new TGraphErrors();
        gGeneralAsymPtType[0] -> SetName("GeneralAsymPtAllXf");

        gGeneralAsymPtType[1] = new TGraphErrors();
        gGeneralAsymPtType[1] -> SetName("GeneralAsymPtAllXf");

        gGeneralAsymXfType[0] = new TGraphErrors();
        gGeneralAsymXfType[0] -> SetName("GeneralAsymXfAllPt");

        gGeneralAsymXfType[1] = new TGraphErrors();
        gGeneralAsymXfType[1] -> SetName("GeneralAsymXfAllPt");
    }

    fMassFit = new TF1("fit_allMass", &testPi0Asymmetry::polGausFit, 25, 250, 10);
    fMassBkgFit = new TF1("bkgFi_allMass", &testPi0Asymmetry::polFit, 100, 180, 7);
    fMassSignalFit = new TF1("signalFit_allMass", &testPi0Asymmetry::gausFit, 25, 280, 3);
    fMassFit -> SetParameters(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fMassFit -> SetLineColor(kBlue);
    fMassFit -> SetLineWidth(1.2);
    fMassSignalFit -> SetParameters(0, 0, 0);
    fMassSignalFit -> SetLineColor(kRed);
    fMassSignalFit -> SetLineWidth(1.2);
    fMassBkgFit -> SetParameters(0, 0, 0, 0, 0, 0, 0);
    fMassBkgFit -> SetLineColor(kGreen+3);
    fMassBkgFit -> SetLineWidth(1.2);
    return 1;
}

Int_t testPi0Asymmetry::Make()
{
    int eventNum = mPi0Tree->GetEntries();
    if(mEventNum == -1){mEventNum = eventNum;}
    cout << "testPi0Asymmetry::Make() --- running... " << mEventNum << endl;

    for(int event=0; event< mEventNum; event++){
        if(event%10000==0){cout << " event: " << event << " / " << mEventNum << endl;}
        mPi0Tree -> GetEntry(event);
        if(mIsRHICfPi0 == false){continue;}
        mEventPi0Counts++;

        mRunIdx = getRunTypeIdx(mPi0fillNumber);
        mTypeIdx = mPi0Type-1;

        if(mIsAllEvent == false){
            if(!conditionCheck()){continue;}
        }
        mEventSelectedCounts++;


        if(mDoFindGenMassCut){hMassAll[mRunIdx][mTypeIdx] -> Fill(mPi0Mass);}

        if(mDoBinning){
            double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
            double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
            if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                hPt[mRunIdx][mTypeIdx] -> Fill(mPi0Pt);
                hXf[mRunIdx][mTypeIdx] -> Fill(mPi0Xf);
            }
        }

        // main binning ranges
        for(int pt=0; pt<kFinalBinPt; pt++){
            if(mPtCutRangeAllXf[mTypeIdx][pt] <= mPi0Pt && mPi0Pt < mPtCutRangeAllXf[mTypeIdx][pt+1]){
                double phiAngle = (180./TMath::Pi())*TMath::ATan2(mPi0Y, mPi0X); // [degree]

                // for background estimation
                if(mDoBkgEstimation){
                    hMass[mRunIdx][mTypeIdx][pt] -> Fill(mPi0Mass);
                }

                if(mDoFindBinMean){
                    double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                        mBinMean[mRunIdx][mTypeIdx][pt][0] += mPi0Pt;
                        mBinMean[mRunIdx][mTypeIdx][pt][1] += 1.;

                        hBinMean[mRunIdx][mTypeIdx][pt] -> Fill(mPi0Pt);
                    }
                }

                // for dilution factor
                if(mDoDilution){
                    double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                        hPhi[mRunIdx][mTypeIdx][pt] -> Fill(phiAngle);
                        mDilutionFactor[mRunIdx][mTypeIdx][pt] += TMath::Sin(phiAngle*TMath::Pi()/180.);
                    }
                }

                // for asymmetry
                if(mDoAsymmetry){
                    int fillIdx = getFillNumIdx(mPi0fillNumber);

                    // for pi0 asymmetry
                    double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                        if(0. < phiAngle && phiAngle < 180.){
                            if(mPi0BlueSpinUp == true){polNum[fillIdx][mTypeIdx][pt][1] += 1.;} // left 
                            else{polNum[fillIdx][mTypeIdx][pt][0] += 1.;} // right 
                        }
                        else{
                            if(mPi0BlueSpinUp == true){polNum[fillIdx][mTypeIdx][pt][0] += 1.;} // right
                            else{polNum[fillIdx][mTypeIdx][pt][1] += 1.;} // left
                        }
                    }
                }
            }
        }

        // for Xf
        for(int xf=0; xf<kFinalBinXf; xf++){
            if(mXfCutRangeAllPt[mTypeIdx][xf] <= mPi0Xf && mPi0Xf < mXfCutRangeAllPt[mTypeIdx][xf+1]){
                double phiAngle = (180./TMath::Pi())*TMath::ATan2(mPi0Y, mPi0X); // [degree]

                // for background estimation
                if(mDoBkgEstimation){
                    hMassXf[mRunIdx][mTypeIdx][xf] -> Fill(mPi0Mass);
                }

                if(mDoFindBinMean){
                    double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                        mBinMeanXf[mRunIdx][mTypeIdx][xf][0] += mPi0Xf;
                        mBinMeanXf[mRunIdx][mTypeIdx][xf][1] += 1.;

                        hBinMeanXf[mRunIdx][mTypeIdx][xf] -> Fill(mPi0Xf);
                    }
                }

                // for dilution factor
                if(mDoDilution){
                    double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                        hPhiXf[mRunIdx][mTypeIdx][xf] -> Fill(phiAngle);
                        mDilutionFactorXf[mRunIdx][mTypeIdx][xf] += TMath::Sin(phiAngle*TMath::Pi()/180.);
                    }
                }

                // for asymmetry
                if(mDoAsymmetry){
                    int fillIdx = getFillNumIdx(mPi0fillNumber);

                    // for pi0 asymmetry
                    double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
                    if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                        if(0. < phiAngle && phiAngle < 180.){
                            if(mPi0BlueSpinUp == true){polNumXf[fillIdx][mTypeIdx][xf][1] += 1.;} // left 
                            else{polNumXf[fillIdx][mTypeIdx][xf][0] += 1.;} // right 
                        }
                        else{
                            if(mPi0BlueSpinUp == true){polNum[fillIdx][mTypeIdx][pt][0] += 1.;} // right
                            else{polNumXf[fillIdx][mTypeIdx][xf][1] += 1.;} // left
                        }
                    }
                }
            }
        }
        
    }

    for(int run = 0; run < kRunTypeNum; run++){
        for(int type=0; type < kPi0TypeNum; type++){
            mRunIdx = run;
            mTypeIdx = type;

            if(mDoFindGenMassCut){findGenMassCut();}
            if(mDoBkgEstimation){bkgEstimation();}
            if(mDoFindBinMean){findBinMean();}
            if(mDoDilution){dilutionFactor();}
        }
    }

    if(mDoAsymmetry){asymmetry();}

    if(mDoSaveData){saveData();}
    if(mDoDrawFigure){drawFigure();}

    return 1;
}

Int_t testPi0Asymmetry::Finish()
{
    for(int run=0; run<kRunTypeNum; run++){
        for(int type=0; type < kPi0TypeNum; type++){
            delete hMassAll[run][type];
            delete hEnergy[run][type];
            delete hPt[run][type];
            delete hXf[run][type];

            for(int pt=0; pt<kFinalBinPt; pt++){
                delete hMass[run][type][pt];
            }
            for(int xf=0; xf<kFinalBinXf; pt++){
                delete hMassXf[run][type][xf];
            }
            
        }
    }

    delete fMassFit;
    delete fMassBkgFit;
    delete fMassSignalFit;

    mAnalPi0File->Close();
}

Int_t testPi0Asymmetry::clear();

void testPi0Asymmetry::setFile(TString file){mFilePath = file;}
void testPi0Asymmetry::setSaveFigPath(TString path){mSaveDatPath = path;}

int testPi0Asymmetry::getRunTypeIdx(int fillNum)
{
    if(fillNum == 21142 || fillNum == 21145){return 0;}
    if(fillNum == 21148 || fillNum == 21150){return 1;}
    if(fillNum == 21149){return 2;}
    return -1;
}

int testPi0Asymmetry::getFillNumIdx(int fillNum)
{
    if(fillNum == 21142){return 0;}
    if(fillNum == 21145){return 1;}
    if(fillNum == 21148){return 2;}
    if(fillNum == 21149){return 3;}
    if(fillNum == 21150){return 4;}
    return -1;
}
int testPi0Asymmetry::getFillToRunTypeIdx(int fillIdx)
{
    if(fillIdx == 0 || fillIdx == 1){return 0;}
    if(fillIdx == 2 || fillIdx == 4){return 1;}
    if(fillIdx == 3){return 2;}
    return -1;
}

double testPi0Asymmetry::relativeluminosity(int fillIdx)
{
    if(fillIdx == 0){return 0.9581;}
    if(fillIdx == 1){return 0.9623;}
    if(fillIdx == 2){return 0.9924;}
    if(fillIdx == 3){return 0.9949;}
    if(fillIdx == 4){return 0.9774;}
    return 0.;
}

double testPi0Asymmetry::beamPolarization(int fillIdx)
{
    if(fillIdx = 0){return 0.536;}
    if(fillIdx = 1){return 0.554;}
    if(fillIdx = 2){return 0.590;}
    if(fillIdx = 3){return 0.566;}
    if(fillIdx = 4){return 0.592;}
    return 0.;
}


void testPi0Asymmetry::findGenMassCut()
{
    massFitting(hMassAll[mRunIdx][mTypeIdx]);
    double par[10];
    getMassFitPar(par);

    cout << "testPi0Asymmetry::findGenMassCut() --- find a general mass cut condition || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    cout << "===== " << par[0]-3.*par[1] << " < " << par[0] << " < " << par[0]+3.*par[1] << " [MeV/c^2]" << endl;
    mGenMassCutRange[mRunIdx][mTypeIdx][0] = par[0];
    mGenMassCutRange[mRunIdx][mTypeIdx][1] = par[1];
}

void testPi0Asymmetry::findBinMean()
{
    cout << "testPi0Asymmetry::findBinMean() --- find a Mean value each xf, pt bins || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    for(int pt=0; pt<kFinalBinPt; pt++){
        if(mBinMean[mRunIdx][mTypeIdx][pt][0] < 10 || mBinMean[mRunIdx][mTypeIdx][pt][1] < 10){continue;}

        double ptMean = mBinMean[mRunIdx][mTypeIdx][pt][0]/mBinMean[mRunIdx][mTypeIdx][pt][1];
        cout << " <pt>: " << ptMean << " (" << endl;
    }

    for(int xf=0; xf<kFinalBinXf; xf++){
        if(mBinMeanXf[mRunIdx][mTypeIdx][xf][0] < 10 || mBinMeanXf[mRunIdx][mTypeIdx][xf][1] < 1000){continue;}

        double xfMean = mBinMeanXf[mRunIdx][mTypeIdx][xf][0]/mBinMeanXf[mRunIdx][mTypeIdx][xf][1];
        cout << " <xf>: " << xfMean << " (" << endl;
    }
}

void testPi0Asymmetry::bkgEstimation()
{
    cout << "testPi0Asymmetry::bkgEstimation() --- find a general mass cut condition || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    for(int pt=0; pt<kFinalBinPt; pt++){
        double par[10];
        memset(par, 0, sizeof(par));
        int maxBin = hMass[mRunIdx][mTypeIdx][pt] -> GetMaximumBin();
        int entries = hMass[mRunIdx][mTypeIdx][pt] -> GetBinContent(35);

        if(33 <= maxBin && maxBin <= 39 || entries > 80){
            massFitting(hMass[mRunIdx][mTypeIdx][pt]);

            getMassFitPar(par);
            cout << "=== " << par[0]-3.*par[1] << " < " << par[0] << " < " << par[0]+3.*par[1] << " [MeV/c^2] (" << 
            Form("%.2f<pt<%.2f", mPtCutRangeAllXf[mTypeIdx][pt], mPtCutRangeAllXf[mTypeIdx][pt+1]) <<") " << endl;
        }
        mMassCutRange[mRunIdx][mTypeIdx][pt][0] = par[0];
        mMassCutRange[mRunIdx][mTypeIdx][pt][1] = par[1];

        // for signal and background rato
        if(par[0] > 10.){
            double allFitIntegral = fMassFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);
            double SignalFitIntegral = fMassSignalFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);
            double bkgFitIntegral = fMassBkgFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);

            mMassFitIntegral[mRunIdx][mTypeIdx][pt][0] = allFitIntegral;
            mMassFitIntegral[mRunIdx][mTypeIdx][pt][1] = SignalFitIntegral;
            mMassFitIntegral[mRunIdx][mTypeIdx][pt][2] = bkgFitIntegral;
        }
    }


    for(int xf=0; xf<kFinalBinXf; xf++){
        double par[10];
        memset(par, 0, sizeof(par));
        int maxBin = hMassXf[mRunIdx][mTypeIdx][xf] -> GetMaximumBin();
        int entries = hMassXf[mRunIdx][mTypeIdx][xf] -> GetBinContent(35);

        if(33 <= maxBin && maxBin <= 39 || entries > 80){
            massFitting(hMassXf[mRunIdx][mTypeIdx][xf]);

            getMassFitPar(par);
            cout << "=== " << par[0]-3.*par[1] << " < " << par[0] << " < " << par[0]+3.*par[1] << " [MeV/c^2] (" << 
            Form("%.2f<xf<%.2f", mXfCutRangeAllPt[mTypeIdx][xf], mXfCutRangeAllPt[mTypeIdx][xf+1]) <<") " << endl;
        }
        mMassCutRangeXf[mRunIdx][mTypeIdx][xf][0] = par[0];
        mMassCutRangeXf[mRunIdx][mTypeIdx][xf][1] = par[1];

        // for signal and background rato
        if(par[0] > 10.){
            double allFitIntegral = fMassFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);
            double SignalFitIntegral = fMassSignalFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);
            double bkgFitIntegral = fMassBkgFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);

            mMassFitIntegralXf[mRunIdx][mTypeIdx][xf][0] = allFitIntegral;
            mMassFitIntegralXf[mRunIdx][mTypeIdx][xf][1] = SignalFitIntegral;
            mMassFitIntegralXf[mRunIdx][mTypeIdx][xf][2] = bkgFitIntegral;
        }
    }
    
}

void testPi0Asymmetry::dilutionFactor()
{
    cout << "testPi0Asymmetry::dilutionFactor() --- calculate a dilution factor || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    for(int pt=0; pt<kFinalBinPt; pt++){
        double entrise = hPhi[mRunIdx][mTypeIdx][pt] -> GetEntries(); 
        mDilutionFactor[mRunIdx][mTypeIdx][pt] /= entrise;
        if(entrise < 1){mDilutionFactor[mRunIdx][mTypeIdx][pt] = 0.;}

        cout << mRunIdx << " " << mTypeIdx << " " << pt << " " << mDilutionFactor[mRunIdx][mTypeIdx][pt] << endl;
    }

    for(int xf=0; xf<kFinalBinXf; xf++){
        double entrise = hPhiXf[mRunIdx][mTypeIdx][xf] -> GetEntries(); 
        mDilutionFactorXf[mRunIdx][mTypeIdx][xf] /= entrise;
        if(entrise < 1){mDilutionFactorXf[mRunIdx][mTypeIdx][xf] = 0.;}

        cout << mRunIdx << " " << mTypeIdx << " " << xf << " " << mDilutionFactorXf[mRunIdx][mTypeIdx][xf] << endl;
    }
}

void testPi0Asymmetry::asymmetry()
{
    cout << "testPi0Asymmetry::asymmetry() --- calculate Asymmetry " << endl;

    double AN[kFillNum][kPi0TypeNum][kFinalBinPt][3]; // [an, anErr, wieght]
    double ANXf[kFillNum][kPi0TypeNum][kFinalBinXf][3]; // [an, anErr, wieght]
    memset(AN, 0, sizeof(AN));
    memset(ANXf, 0, sizeof(ANXf));

    for(int fill = 0; fill < kFillNum; fill++){
        double relaLumi = relativeluminosity(fill);
        double beamPol = beamPolarization(fill);
        int runIdx = getFillToRunTypeIdx(fill);

        for(int type=0; type < kPi0TypeNum; type++){
            for(int pt=0; pt<kFinalBinPt; pt++){
                double dilution = mDilutionFactor[runIdx][type][pt];
                if(dilution <= 0.01){continue;}

                // signal + background asymmetry
                double rightPolNum = polNum[fill][type][pt][0];
                double leftPolNum = polNum[fill][type][pt][1];
                if(rightPolNum+leftPolNum <= 0.5){continue;}

                double anAll = -1./(dilution * beamPol) * (leftPolNum - relaLumi * rightPolNum) / ((leftPolNum + relaLumi * rightPolNum));
                double anAllErr = 1./TMath::Sqrt(rightPolNum + leftPolNum);

                double an = anAll;
                double anErr = anAllErr;
                double wieght = rightPolNum + leftPolNum;

                AN[fill][type][pt][0] = an;
                AN[fill][type][pt][1] = anErr;
                AN[fill][type][pt][2] = wieght;

                double ptMean = mBinMean[runIdx][type][pt][0]/mBinMean[runIdx][type][pt][1]; 

                int idx = gGeneralAsymPtType[type] -> GetN();
                gGeneralAsymPtType[type] -> SetPoint(idx, ptMean, an);
                gGeneralAsymPtType[type] -> SetPointError(idx, 0., anErr);
            }

            // for Xf
            for(int xf=0; xf<kFinalBinXf; xf++){
                double dilution = mDilutionFactorXf[runIdx][type][xf];
                if(dilution <= 0.01){continue;}

                // signal + background asymmetry
                double rightPolNum = polNumXf[fill][type][xf][0];
                double leftPolNum = polNumXf[fill][type][xf][1];
                if(rightPolNum+leftPolNum <= 0.5){continue;}

                double anAll = -1./(dilution * beamPol) * (leftPolNum - relaLumi * rightPolNum) / ((leftPolNum + relaLumi * rightPolNum));
                double anAllErr = 1./TMath::Sqrt(rightPolNum + leftPolNum);

                double an = anAll;
                double anErr = anAllErr;
                double wieght = rightPolNum + leftPolNum;

                ANXf[fill][type][xf][0] = an;
                ANXf[fill][type][xf][1] = anErr;
                ANXf[fill][type][xf][2] = wieght;

                double ptMean = mBinMeanXf[runIdx][type][xf][0]/mBinMeanXf[runIdx][type][xf][1]; 
                if(mBinMeanXf[runIdx][type][xf][1] < 1000){continue;}

                int idx = gGeneralAsymXfType[type] -> GetN();
                gGeneralAsymXfType[type] -> SetPoint(idx, ptMean, an);
                gGeneralAsymXfType[type] -> SetPointError(idx, 0., anErr);
            }
        }
    }
    cout << "testPi0Asymmetry::asymmetry() --- done !!!" << endl;
}

bool testPi0Asymmetry::conditionCheck()
{
    // test tmp for VPD sum ADC !!!
    mVPDSumEast = 0;
    mVPDSumWest = 0;
    for(int i=0; i<16; i++){
        mVPDSumEast += mVpdEast[i][0];
        mVPDSumWest += mVpdWest[i][0];
    }
    // for Multiplicity!
    // int bbcSEastMult = bbcMultiplicity(0, 0);
    // int bbcSWestMult = bbcMultiplicity(1, 0);
    // int bbcLEastMult = bbcMultiplicity(0, 1);
    // int bbcLWestMult = bbcMultiplicity(1, 1);
    // int vpdEastMult = vpdMultiplicity(0);
    // int vpdWestMult = vpdMultiplicity(1);

    if(mIsSDLEMode == true){
        if(mTofMult == 0){
            // if(mBBCLSumEast == 0){ // SDLE1
            // if(mBBCLSumEast == 0 && mBBCSSumEast == 0){ // SDLE2
            // if(mBBCLSumEast == 0 && mBBCSSumEast == 0 && mVPDSumEast == 0){ // SDLE3
            
            // if(mBBCLSumEast < mBBCLSumADCThr[0]){ // SDLE1Thr
            if(mBBCLSumEast < mBBCLSumADCThr[0] && mBBCSSumEast < mBBCSSumADCThr[0]){ // SDLE2Thr
            // if(mBBCLSumEast < mBBCLSumADCThr[0] && mBBCSSumEast < mBBCSSumADCThr[0] && mVPDSumEast < mVPDSumADCThr[0]){ // SDLE3Thr
                return 1;   
            }
        }
    }

    if(mIsDDLEMode == true){
        if(mTofMult == 0){

            // old version DDLE condition
            // if((mBBCLSumEast > 0 && mBBCLSumWest > 0)){
            // if((mBBCLSumEast > 0 && mBBCLSumWest > 0) || (mBBCSSumEast > 0 && mBBCSSumWest > 0)){
            // if((mBBCLSumEast > 0 && mBBCLSumWest > 0) || (mBBCSSumEast > 0 && mBBCSSumWest > 0) || (mVPDSumEast > 0 && mVPDSumWest > 0)){

            // if((mBBCLSumEast > mBBCLSumADCThr[0] && mBBCLSumWest > mBBCLSumADCThr[1])){
            // if((mBBCLSumEast > mBBCLSumADCThr[0] && mBBCLSumWest > mBBCLSumADCThr[1]) || (mBBCSSumEast > mBBCSSumADCThr[0] && mBBCSSumWest > mBBCSSumADCThr[1])){
            // if((mBBCLSumEast > mBBCLSumADCThr[0] && mBBCLSumWest > mBBCLSumADCThr[1]) || (mBBCSSumEast > mBBCSSumADCThr[0] && mBBCSSumWest > mBBCSSumADCThr[1]) || (mVPDSumEast > mVPDSumADCThr[0] && mVPDSumWest > mVPDSumADCThr[1])){
            //     return 1;
            // }


            // if(mBBCLSumEast > 0){ // DDLE1
            // if(mBBCLSumEast > 0 && mBBCSSumEast > 0){ // DDLE2
            // if(mBBCLSumEast > 0 && mBBCSSumEast > 0 && mVPDSumEast > 0){ // DDLE3

            // if(mBBCLSumEast > mBBCLSumADCThr[0]){ // DDLE1Thr
            if(mBBCLSumEast > mBBCLSumADCThr[0] && mBBCSSumEast > mBBCSSumADCThr[0]){ // DDLE2Thr
            // if(mBBCLSumEast > mBBCLSumADCThr[0] && mBBCSSumEast > mBBCSSumADCThr[0] && mVPDSumEast > mVPDSumADCThr[0]){ // DDLE3Thr
                return 1;   
            }
        }
    }

    if(mIsCDLEMode == true){ 
        if(mTofMult > 0){
            if(mVPDSumWest == 0 && mVPDSumEast == 0){
                return 1;
            }
        }
    }

    if(mIsNDLEMode == true){
        if(mTofMult > 0){
            // if((mBBCSSumWest > 0 || mBBCLSumWest > 0) && (mBBCSSumEast > 0 || mBBCLSumEast > 0)){ // ND1
            // if(mBBCSSumWest > 0 && mBBCLSumWest > 0 && mBBCSSumEast > 0 && mBBCLSumEast > 0){ // ND2
            // if(mBBCSSumWest > 0 && mBBCLSumWest > 0 && mBBCSSumEast > 0 && mBBCLSumEast > 0 && mVPDSumEast > 0 && mVPDSumWest > 0){ // ND3

            // if((mBBCSSumWest > mBBCSSumADCThr[1] || mBBCLSumWest > mBBCLSumADCThr[1]) && (mBBCSSumEast > mBBCSSumADCThr[0] || mBBCLSumEast > mBBCLSumADCThr[0])){ // ND1Thr
            // if(mBBCSSumWest > mBBCSSumADCThr[1] && mBBCLSumWest > mBBCLSumADCThr[1] && mBBCSSumEast > mBBCSSumADCThr[0] && mBBCLSumEast > mBBCLSumADCThr[0]){ // ND2Thr
            if(mBBCSSumWest > mBBCSSumADCThr[1] && mBBCLSumWest > mBBCLSumADCThr[1] && mBBCSSumEast > mBBCSSumADCThr[0] && mBBCLSumEast > mBBCLSumADCThr[0] && mVPDSumEast > mVPDSumADCThr[0] && mVPDSumWest > mVPDSumADCThr[1]){ // ND3Thr

                return 1;
            }
        }
    }

    if(mIsDMLEMode == true){
        if(mTofMult == 0){
            // if(mBBCLSumWest == 0){ // LMLE1
            // if(mBBCLSumWest == 0 && mBBCSSumWest == 0){ // LMLE2
            // if(mBBCLSumWest == 0 && mBBCSSumWest == 0 && mVPDSumWest == 0){ // LMLE3
            // if(mBBCLSumWest < mBBCLSumADCThr[1]){ // LMLE1Thr
            if(mBBCLSumWest < mBBCLSumADCThr[1] && mBBCSSumWest < mBBCSSumADCThr[1]){ // LMLE2Thr
            // if(mBBCLSumWest < mBBCLSumADCThr[1] && mBBCSSumWest < mBBCSSumADCThr[1] && mVPDSumWest < mVPDSumADCThr[1]){ // LMLE3Thr
            //     return 1;
            // }

            // if(mBBCLSumWest > 0){ // HMLE1
            // if(mBBCLSumWest > 0 && mBBCSSumWest > 0){ // HMLE2
            // if(mBBCLSumWest > 0 && mBBCSSumWest > 0 && mVPDSumWest == 0){ // HMLE3
            // if(mBBCLSumWest > mBBCLSumADCThr[1]){ // HMLE1Thr
            // if(mBBCLSumWest > mBBCLSumADCThr[1] && mBBCSSumWest > mBBCSSumADCThr[1]){ // HMLE2Thr
            // if(mBBCLSumWest > mBBCLSumADCThr[1] && mBBCSSumWest > mBBCSSumADCThr[1] && mVPDSumWest > mVPDSumADCThr[1]){ // HMLE3Thr
                return 1;
            }
        }
    }

    if(mIsTestMode == true){
        if(mTofMult == 0){
            // if(mBBCSSumEast > mBBCSSumADCThr[0]){ // BBC small East Threshold cut
            if(mVPDSumEast > mVPDSumADCThr[0]){ // BBC small East Threshold cut
                return 1;
            }
        }
    }

    return 0;
}

int testPi0Asymmetry::bbcMultiplicity(int ew, int det)
{   
    int mult = 0;
    const int chSize = (det ==0)? 16 : 8;
    for(int ch=0; ch<chSize; ch++){
        int adc = -1;
        if(ew == 0){
            if(det == 0){adc = mBBCSEast[ch][0];}
            else{adc = mBBCLEast[ch][0];}
        }
        else{
            if(det == 0){adc = mBBCSWest[ch][0];}
            else{adc = mBBCLWest[ch][0];}
        }

        int Threshold = (det == 0) ? mBBCSADCThr[ew][ch] : mBBCLADCThr[ew][ch];
        if(adc > Threshold){mult++;}
    }
    return mult;
}

int testPi0Asymmetry::vpdMultiplicity(int ew)
{
    int mult = 0;
    const int chSize = 16;
    for(int ch=0; ch<chSize; ch++){
        int adc = -1;
        if(ew == 0){adc = mVpdEast[ch][0];}
        else{adc = mVpdWest[ch][0];}

        int Threshold = mVPDADCThr[ew][ch];
        if(adc > Threshold){mult++;}
    }
    return mult;
}

void testPi0Asymmetry::drawFigure()
{
    cout << "testPi0Asymmetry::drawFigure() --- drawing ... "  << endl;
    
    if(mDoFindGenMassCut){
        TCanvas* cMassAll = new TCanvas("cMassAll","cMassAll", 1300, 600);
        TLatex* allMassLatex = new TLatex();
        TLegend* allMassLeg = new TLegend(0.6,0.7, 0.9, 0.9);

        for(int run=0; run<kRunTypeNum; run++){
            cMassAll -> Clear();
            cMassAll -> Divide(2,1);

            if(hMassAll[run][0]->GetEntries() < 1){continue;}
            for(int type=0; type<kPi0TypeNum; type++){
                const int cMassAllIdx = type+1;
                cMassAll -> cd(cMassAllIdx);
                gPad -> SetGrid(0,0);

                hMassAll[run][type] -> Draw();

                allMassLeg -> Clear();
                allMassLeg -> AddEntry(fMassFit, "All fit","lp");
                allMassLeg -> AddEntry(fMassSignalFit, "Signal fit","lp");
                allMassLeg -> AddEntry(fMassBkgFit, "Bkg fit","lp");
                allMassLeg -> Draw("same");

                double massSignalMean = mGenMassCutRange[run][type][0];
                double massSignalSigma = mGenMassCutRange[run][type][1];

                allMassLatex -> Clear();
                allMassLatex -> SetTextSize(0.05);
                allMassLatex -> DrawLatexNDC(0.15, 0.85, Form("Type%i #pi^{0} Mass", type+1));
                allMassLatex -> DrawLatexNDC(0.15, 0.8, "Run = TS");
                allMassLatex -> DrawLatexNDC(0.57, 0.65, Form("M_{#pi^{0}} = %.2f", massSignalMean));
                allMassLatex -> DrawLatexNDC(0.57, 0.6, Form("#sigma_{#pi^{0}} = %.2f", massSignalSigma));
                allMassLatex -> DrawLatexNDC(0.57, 0.5, Form("entry = %.1f", hMassAll[run][type]->GetEntries()));
                allMassLatex -> Draw("same");
            }

            cMassAll -> Draw();
            cMassAll -> SaveAs(Form("%s/allPi0Mass_%s.pdf", mSaveFigPath.Data(), mRunName[run].Data()));
        }
    }
    
    if(mDoBkgEstimation){
        TCanvas* cMass = new TCanvas("cMass", "cMass", kFinalBinPt*700, kFinalBinPt*1200);
        TLatex* massLatex = new TLatex();
        TLegend* massLeg = new TLegend(0.6,0.7, 0.9, 0.9);

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                int entries = 0;

                for(int pt=0; pt<kFinalBinPt; pt++){
                    entries += hMass[run][type][pt]->GetEntries();
                }
                if(entries < 10){continue;}

                cMass -> Clear();
                cMass -> Divide(2,3);

                int tmpIdx = 0;
                for(int pt=0; pt<kFinalBinPt; pt++){
                    tmpIdx++;
                    const int c1Idx = tmpIdx;
                    cMass -> cd(c1Idx);
                    gPad -> SetGrid(0,0);

                    int maxBin = hMass[run][type][pt] -> GetMaximumBin();
                    double maxBinContent = hMass[run][type][pt] -> GetBinContent(maxBin);
                    hMass[run][type][pt] -> GetYaxis() -> SetRangeUser(0., maxBinContent+maxBinContent/10.);
                    hMass[run][type][pt] -> Draw();
                    
                    massLeg -> Clear();
                    massLeg -> AddEntry(fMassFit, "All fit","lp");
                    massLeg -> AddEntry(fMassSignalFit, "Signal fit","lp");
                    massLeg -> AddEntry(fMassBkgFit, "Bkg fit","lp");
                    massLeg -> Draw("same");

                    massLatex -> Clear();
                    massLatex -> SetTextSize(0.05);
                    massLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                    massLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRangeAllXf[type][pt], mPtCutRangeAllXf[type][pt+1]));
                    massLatex -> DrawLatexNDC(0.57, 0.6, "0 < x_{F} < 1");
                    massLatex -> Draw("same");
                }
            
                cMass -> Draw();
                cMass -> SaveAs(Form("%s/Mass_%s_pi0Type%i.pdf", mSaveFigPath.Data(), mRunName[run].Data(), type+1));
            }
        }
    }

    if(mDoFindBinMean){
        TCanvas* cMeanBin = new TCanvas("cMeanBin", "cMeanBin", 2*750, 3*750);
        TLatex* meanLatex = new TLatex();
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                cMeanBin -> Clear();
                cMeanBin -> Divide(2, 3);

                int entries = 0;
                for(int pt=0; pt<kFinalBinPt; pt++){
                    entries += hBinMean[run][type][pt] -> GetEntries();
                }
                if(entries < 10){continue;}

                int tmpIdx = 0;
                for(int pt=0; pt<kFinalBinPt; pt++){
                    tmpIdx++;
                    const int c1Idx = tmpIdx;
                    cMeanBin -> cd(c1Idx);
                    gPad -> SetGrid(0,0);

                    hBinMean[run][type][pt] -> Draw();

                    meanLatex -> Clear();
                    meanLatex -> SetTextSize(0.05);
                    meanLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                    meanLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRangeAllXf[type][pt], mPtCutRangeAllXf[type][pt+1]));
                    meanLatex -> DrawLatexNDC(0.57, 0.6, "0 < x_{F} < 1");

                    meanLatex -> SetTextSize(0.06);
                    meanLatex -> DrawLatexNDC(0.55, 0.45, Form("mean = %.3f", mBinMean[run][type][pt][0]/mBinMean[run][type][pt][1]));
                }
            
                cMeanBin -> Draw();
                cMeanBin -> SaveAs(Form("%s/MeanEachBin_%s_pi0Type%i.pdf", mSaveFigPath.Data(), mRunName[run].Data(), type+1));
                
            }
        }
    }

    if(mDoDilution){
        TCanvas* cDilution = new TCanvas("cDilution", "cDilution", 2*750, 3*750);
        TLatex* dilutionLatex = new TLatex();
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                cDilution -> Clear();
                cDilution -> Divide(2, 3);

                int entries = 0;
                for(int pt=0; pt<kFinalBinPt; pt++){
                    entries += hPhi[run][type][pt] -> GetEntries();
                }
                if(entries < 10){continue;}

                int tmpIdx = 0;
                for(int pt=0; pt<kFinalBinPt; pt++){
                    tmpIdx++;
                    const int c1Idx = tmpIdx;
                    cDilution -> cd(c1Idx);

                    gPad -> SetGrid(0,0);
                    hPhi[run][type][pt] -> GetXaxis() -> SetRangeUser(0., 200.);
                    hPhi[run][type][pt] -> Draw();

                    dilutionLatex -> Clear();
                    dilutionLatex -> SetTextSize(0.06);
                    dilutionLatex -> DrawLatexNDC(0.6, 0.8, Form("D_{#phi} = %.3f", mDilutionFactor[run][type][pt]));
                    dilutionLatex -> Draw("same");

                    dilutionLatex -> Clear();
                    dilutionLatex -> SetTextSize(0.05);
                    dilutionLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                    dilutionLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRangeAllXf[type][pt], mPtCutRangeAllXf[type][pt+1]));
                    dilutionLatex -> DrawLatexNDC(0.57, 0.6,"0 < x_{F} < 1");
                    dilutionLatex -> Draw("same");
                }
                
                cDilution -> Draw();
                cDilution -> SaveAs(Form("%s/DilutionFactor_%s_pi0Type%i.pdf", mSaveFigPath.Data(), mRunName[run].Data(), type+1));
            }
        }
    }

    if(mDoAsymmetry){
        TLatex* anLatex = new TLatex();
        TLine* dashLine = new TLine(0., 0., 0.99, 0.);
        dashLine -> SetLineStyle(2);

        TLegend* rangeLeg[2];
        TGraph* tmpGraph[2];

        int rangeColor[6] = {99, 93, 209, 60, 52, 1};
        int rangeColor2[3] = {8, 1, 2};
        int MarkerStyle[2] = {20, 26};

        for(int i=0; i<2; i++){
            rangeLeg[i] = new TLegend(0.11, 0.6, 0.5, 0.87);
            tmpGraph[i] = new TGraph();
            tmpGraph[i] -> SetPoint(0, 0., -0.04);
            tmpGraph[i] -> SetPoint(1, 0.9, 0.25);
            tmpGraph[i] -> SetMarkerSize(0);
            tmpGraph[i] -> SetMarkerStyle(MarkerStyle[i]);
            tmpGraph[i] -> SetLineWidth(0);
        }

        TLegend* legAsymPt = new TLegend(0.13, 0.65, 0.5, 0.87);
        TLegend* legAsymXf = new TLegend(0.13, 0.65, 0.5, 0.87);
        TCanvas* cAsym = new TCanvas("cAsym", "cAsym", 1300, 600);
        cAsym -> Divide(2,1);

        cAsym -> cd(1);
        gPad -> SetGrid(0,0);
        tmpGraph[0] -> GetYaxis() -> SetRangeUser(-0.1, 0.3);
        tmpGraph[0] -> SetTitle("; p_{T} [GeV/c]; A_{N}");
        tmpGraph[0] -> Draw("ap");

        gGeneralAsymPtType[0] -> SetMarkerSize(1.2);
        gGeneralAsymPtType[0] -> SetMarkerStyle(MarkerStyle[0]);
        gGeneralAsymPtType[0] -> SetMarkerColor(rangeColor[0]);
        gGeneralAsymPtType[0] -> SetLineColor(rangeColor[0]);
        gGeneralAsymPtType[0] -> Draw("same, p");
        
        anLatex -> Clear();
        anLatex -> SetTextSize(0.04);
        anLatex -> DrawLatexNDC(0.72, 0.85, "Run = TS");
        anLatex -> Draw("same");
        dashLine -> Draw("same");

        cAsym -> cd(2);
        gPad -> SetGrid(0,0);
        tmpGraph[1] -> GetYaxis() -> SetRangeUser(-0.1, 0.3);
        tmpGraph[1] -> SetTitle("; p_{T} [GeV/c]; A_{N}");
        tmpGraph[1] -> Draw("ap");

        gGeneralAsymPtType[1] -> SetMarkerSize(1.2);
        gGeneralAsymPtType[1] -> SetMarkerStyle(MarkerStyle[0]);
        gGeneralAsymPtType[1] -> SetMarkerColor(rangeColor[0]);
        gGeneralAsymPtType[1] -> SetLineColor(rangeColor[0]);
        gGeneralAsymPtType[1] -> Draw("same, p");

        anLatex -> Clear();
        anLatex -> SetTextSize(0.04);
        anLatex -> DrawLatexNDC(0.72, 0.85, "Run = TS");
        anLatex -> Draw("same");
        dashLine -> Draw("same");

        cAsym -> Draw();
        cAsym -> SaveAs(Form("%s/asymmetry.pdf", mSaveFigPath.Data()));

        // test !!!
        // save graph into TFile for comparison asymmetry with other condition, ex) tpc track, fps photon or not
        TFile* fileAsym = new TFile(Form("%s", mOutFileName.Data()), "recreate");
        fileAsym -> cd();
        gGeneralAsymPtType[0] -> Write();
        gGeneralAsymPtType[1] -> Write();
        gGeneralAsymXfType[0] -> Write();
        gGeneralAsymXfType[1] -> Write();

        TTree* treeCounts = new TTree("count", "count");
        Int_t outPi0Count;
        Int_t outSelectCount;
        treeCounts -> Branch("pi0Count", &outPi0Count, "outPi0Count/I");
        treeCounts -> Branch("SelectCount", &outSelectCount, "outSelectCount/I");
        outPi0Count = mEventPi0Counts;
        outSelectCount = mEventSelectedCounts;

        treeCounts -> Fill();
        treeCounts -> Write();

        fileAsym -> Close();

        cout << mOutFileName <<" is saved!!! " << endl;

        // // asymmetry as function of pt in all xf range
        // TCanvas* cAsymPtAllXf = new TCanvas("cAsymPtAllXf", "cAsymPtAllXf", 600, 600);
        // TLegend* legAsymPtAllXf = new TLegend(0.13, 0.65, 0.5, 0.87);
        // gPad -> SetGrid(0,0);
        // tmpGraph[1] -> GetYaxis() -> SetRangeUser(-0.1, 0.3);
        // tmpGraph[1] -> SetTitle("; p_{T} [GeV/c]; A_{N}");
        // tmpGraph[1] -> Draw("ap");

        // gGeneralAsymPt -> SetMarkerSize(1.2);
        // gGeneralAsymPt -> SetMarkerStyle(MarkerStyle[0]);
        // gGeneralAsymPt -> SetMarkerColor(kBlack);
        // gGeneralAsymPt -> SetLineColor(kBlack);
        // gGeneralAsymPt -> Draw("same, p");

        // anLatex -> Clear();
        // anLatex -> SetTextSize(0.04);
        // anLatex -> DrawLatexNDC(0.72, 0.85, "Run = TS");
        // anLatex -> Draw("same");
        // dashLine -> Draw("same");

        // cAsymPtAllXf -> Draw();
        // cAsymPtAllXf -> SaveAs(Form("%s/asymmetry%s.pdf", mSaveFigPath.Data(), mConditionName.Data()));
    }
}

int testPi0Asymmetry::readData()
{
    memset(mOptionChecker, 0, sizeof(mOptionChecker));

    if(mDoFindGenMassCut == false){
        ifstream generalMassFitParFile;
        TString dataPath = mSaveDatPath+"/GeneralMassCut_" + mConditionName + ".dat";
        generalMassFitParFile.open(dataPath.Data());
        if(generalMassFitParFile.is_open()){
            while(!generalMassFitParFile.eof()){
                int run, type;
                double mean, sigma;
                generalMassFitParFile >> run >> type >> mean >> sigma;
                mGenMassCutRange[run][type][0] = mean;
                mGenMassCutRange[run][type][1] = sigma;

                if(mean > 10.){mOptionChecker[0] = true;}
            }
            cout << "testPi0Asymmetry::readData() --- General Mass Cut data is OK" << endl;
        }
        else{
            cout << "testPi0Asymmetry::readData() --- Can't opend general mass fitting parameter data " << dataPath << endl;
            return 0;
        }
        generalMassFitParFile.close();
    }
    if(mDoFindBinMean == false && mDoFindGenMassCut == false){
        ifstream binMeanFile;
        TString dataPath = mSaveDatPath+"/MeanEachBin_" + mConditionName + ".dat";
        binMeanFile.open(dataPath.Data());
        if(binMeanFile.is_open()){
            while(!binMeanFile.eof()){
                int run, type, pt;
                double meanXf, meanPt;
                int ptNum;
                binMeanFile >> run >> type >> pt >> meanPt >> ptNum;
                mBinMean[run][type][pt][0] = meanPt;
                mBinMean[run][type][pt][1] = ptNum;

                if(ptNum > 1){mOptionChecker[3] = true;}
            }
            cout << "testPi0Asymmetry::readData() --- Mean each bins data is OK" << endl;
        }
        else{
            cout << "testPi0Asymmetry::readData() --- Can't opend findBinMean data " << dataPath << endl;
            return 0;
        }
        binMeanFile.close();

        // for Xf
        mOptionChecker[3] = false;
        ifstream binMeanFileXf;
        TString dataPath = mSaveDatPath+"/MeanEachBin_" + mConditionName + "_xf.dat";
        binMeanFileXf.open(dataPath.Data());
        if(binMeanFileXf.is_open()){
            while(!binMeanFileXf.eof()){
                int run, type, xf;
                double meanXf;
                int xfNum;
                binMeanFileXf >> run >> type >> xf >> meanXf >> xfNum;
                mBinMeanXf[run][type][xf][0] = meanXf;
                mBinMeanXf[run][type][xf][1] = xfNum;

                if(xfNum > 1){mOptionChecker[3] = true;}
            }
            cout << "testPi0Asymmetry::readData() --- Mean each bins data for xf is OK" << endl;
        }
        else{
            cout << "testPi0Asymmetry::readData() --- Can't opend findBinMean data for xf" << dataPath << endl;
            return 0;
        }
        binMeanFileXf.close();
    }
    if(mDoDilution == false && mDoFindBinMean == false && mDoFindGenMassCut == false){
        ifstream dilutionFactorFile;
        TString dataPath = mSaveDatPath+"/DilutionFactor_" + mConditionName + ".dat";
        dilutionFactorFile.open(dataPath.Data());
        if(dilutionFactorFile.is_open()){
            while(!dilutionFactorFile.eof()){
                int run, type, xf, pt;
                double factor;
                dilutionFactorFile >> run >> type >> pt >> factor;
                mDilutionFactor[run][type][pt] = factor;

                if(factor > 0.1){mOptionChecker[4] = true;}
            }
            cout << "testPi0Asymmetry::readData() --- Dilution Factor data is OK" << endl;
        }
        else{
            cout << "testPi0Asymmetry::readData() --- Can't opend Dilution data " << dataPath << endl;
            return 0;
        }
        dilutionFactorFile.close();


        // for Xf
        mOptionChecker[4] = false;
        ifstream dilutionFactorFileXf;
        TString dataPath = mSaveDatPath+"/DilutionFactor_" + mConditionName + "_xf.dat";
        dilutionFactorFileXf.open(dataPath.Data());
        if(dilutionFactorFileXf.is_open()){
            while(!dilutionFactorFileXf.eof()){
                int run, type, xf;
                double factor;
                dilutionFactorFileXf >> run >> type >> xf >> factor;
                mDilutionFactorXf[run][type][xf] = factor;

                if(factor > 0.1){mOptionChecker[4] = true;}
            }
            cout << "testPi0Asymmetry::readData() --- Dilution Factor data for xf is OK" << endl;
        }
        else{
            cout << "testPi0Asymmetry::readData() --- Can't opend Dilution data for xf" << dataPath << endl;
            return 0;
        }
        dilutionFactorFileXf.close();
    } 

    if(mDoFindGenMassCut == false && mOptionChecker[0] == false){
        cout << "testPi0Asymmetry::readData() --- General mass cut data is something wrong !! " << endl;
        return 0;
    }
    if(mDoFindBinMean == false && mDoFindGenMassCut == false && mOptionChecker[3] == false){
        cout << "testPi0Asymmetry::readData() ---  Mean each bins data is something wrong !! " << endl;
        return 0;
    }
    if(mDoDilution == false && mDoFindBinMean == false && mDoFindGenMassCut == false && mOptionChecker[4] == false){
        cout << "testPi0Asymmetry::readData() ---  Dilution Factor data is something wrong !! " << endl;
        return 0;
    }
    return 1;
}

void testPi0Asymmetry::saveData()
{
    cout << "testPi0Asymmetry::saveData() --- data saving ..." << endl;
    if(mDoFindGenMassCut){
        ofstream generalMassFitParFile;
        TString dataPath = mSaveDatPath+"/GeneralMassCut_" + mConditionName + ".dat";
        generalMassFitParFile.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                double massSignalMean = mGenMassCutRange[run][type][0];
                double massSignalSigma = mGenMassCutRange[run][type][1];
                if(massSignalMean < 10.){
                    massSignalMean = 0.;
                    massSignalSigma = 0.;
                }
                generalMassFitParFile << run << " " << type << " " << massSignalMean << " " << massSignalSigma << endl;
            }
        }
        generalMassFitParFile.close();
        cout << "General Mass Fitting data is saved !" << endl;
    }
    if(mDoFindBinMean){
        ofstream binMeanFile;
        TString dataPath = mSaveDatPath+"/MeanEachBin_" + mConditionName + ".dat";
        binMeanFile.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    binMeanFile << run << " " << type << " " << pt << " " << 
                    mBinMean[run][type][pt][0] << " " << 
                    mBinMean[run][type][pt][1] << " " << endl;
                }
            }
        }
        binMeanFile.close();
        cout << "mean value each bins data is saved !" << endl;

        // for xf
        ofstream binMeanFileXf;
        TString dataPath = mSaveDatPath+"/MeanEachBin_" + mConditionName + "_xf.dat";
        binMeanFileXf.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int xf=0; xf<kFinalBinXf; xf++){
                    binMeanFileXf << run << " " << type << " " << xf << " " << 
                    mBinMeanXf[run][type][xf][0] << " " << 
                    mBinMeanXf[run][type][xf][1] << " " << endl;
                }
            }
        }
        binMeanFileXf.close();
        cout << "mean value each bins data for xf is saved !" << endl;
    }
    if(mDoDilution){
        ofstream dilutionFactorFile;
        TString dataPath = mSaveDatPath+"/DilutionFactor_" + mConditionName + ".dat";
        dilutionFactorFile.open(dataPath.Data());
        
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    dilutionFactorFile << run << " " << type << " " << pt << " " << mDilutionFactor[run][type][pt] << endl;
                }
            }
        }
        dilutionFactorFile.close();
        cout << "Dilution Factor data is saved !" << endl;


        // for xf
        ofstream dilutionFactorFileXf;
        TString dataPath = mSaveDatPath+"/DilutionFactor_" + mConditionName + "_xf.dat";
        dilutionFactorFileXf.open(dataPath.Data());
        
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int xf=0; xf<kFinalBinXf; xf++){
                    dilutionFactorFileXf << run << " " << type << " " << xf << " " << mDilutionFactorXf[run][type][xf] << endl;
                }
            }
        }
        dilutionFactorFileXf.close();
        cout << "Dilution Factor data is saved !" << endl;
    }
}

void testPi0Asymmetry::info()
{
    cout << "    input data:         " << mFilePath << endl;
    cout << "    output data:        " << mOutFileName << endl;
    cout << "    event end number:   " << mEventNum << endl;
    cout << "    condition version:  " << mConditionName << endl;
    cout << "    condition2 version: " << mConditionName2 << endl;

    cout << "    event mode: ";
    if(mIsSDLEMode){cout << "SDLE" << endl;}
    else if(mIsDDLEMode){cout << "DDLE" << endl;}
    else if(mIsCDLEMode){cout << "CDLE" << endl;}
    else if(mIsNDLEMode){cout << "NDLE" << endl;}
    else if(mIsDMLEMode){cout << "DMLE" << endl;}
    else if(mIsTestMode){cout << "Test conditions" << endl;}
    else{cout << "not setted" << endl;}

    cout << "" << endl;
    cout << "testPi0Asymmetry::info() --- option On-Off" << endl;

    TString optionOn = "";
    optionOn = (mDoFindGenMassCut)? "ON" : "OFF";
    cout << "    DoFindGenMassCut --- " << optionOn << endl;
    optionOn = (mDoFindBinMean)? "ON" : "OFF";
    cout << "    DoFindBinMean --- " << optionOn << endl;
    optionOn = (mDoDilution)? "ON" : "OFF";
    cout << "    DoDilutionFactor --- " << optionOn << endl;
    optionOn = (mDoAsymmetry)? "ON" : "OFF";
    cout << "    DoAsymmetry --- " << optionOn << endl;
    optionOn = (mNotCalBkg)? "ON" : "OFF";
    cout << "    NotCalculBkg --- " << optionOn << endl;
    optionOn = (mDoSaveData)? "ON" : "OFF";
    cout << "    DoSaveData --- " << optionOn << endl;
    optionOn = (mDoDrawFigure)? "ON" : "OFF";
    cout << "    DoDrawFigure --- " << optionOn << endl;

    cout << "" << endl;
}


void testPi0Asymmetry::massFitting(TH1D* histo)
{
    fMassFit -> SetParameters(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fMassSignalFit -> SetParameters(0, 0, 0);
    fMassBkgFit -> SetParameters(0, 0, 0, 0, 0, 0, 0);
    if(histo -> GetEntries() < 1){return;}
    TVirtualFitter::SetMaxIterations(50000);

    fMassFit -> SetParameter(0, 135);
    fMassFit -> SetParameter(1, 10);
    fMassFit -> SetParameter(2, histo->GetMaximum()/2.);
    fMassFit -> SetParameter(3, 5);
    fMassFit -> SetParameter(4, 290);
    fMassFit -> SetParLimits(0, 125, 145);
    fMassFit -> SetParLimits(1, 5, 15);
    histo -> Fit(fMassFit, "Q,R");

    double par[10];
    getMassFitPar(par);

    fMassSignalFit -> SetParameters(par[0], par[1], par[2]);
    fMassSignalFit -> SetParLimits(0, par[0], par[0]);
    fMassSignalFit -> SetParLimits(1, par[1], par[1]);
    fMassSignalFit -> SetParLimits(2, par[2], par[2]);
    histo -> Fit(fMassSignalFit, "Q,R+");

    fMassBkgFit -> SetParameters(par[3], par[4], par[5], par[6], par[7], par[8], par[9]);
    fMassBkgFit -> SetParLimits(0, par[3], par[3]);
    fMassBkgFit -> SetParLimits(1, par[4], par[4]);
    fMassBkgFit -> SetParLimits(2, par[5], par[5]);
    fMassBkgFit -> SetParLimits(3, par[6], par[6]);
    fMassBkgFit -> SetParLimits(4, par[7], par[7]);
    fMassBkgFit -> SetParLimits(5, par[8], par[8]);
    fMassBkgFit -> SetParLimits(6, par[9], par[9]);
    histo -> Fit(fMassBkgFit, "Q,R+");
}

void testPi0Asymmetry::getMassFitPar(double* par){return fMassFit -> GetParameters(par);}
double testPi0Asymmetry::gausFit(double* x, double* par){return par[2]*TMath::Gaus(x[0], par[0], par[1], kTRUE);}
double testPi0Asymmetry::polFit(double* x, double* par){return pow(x[0]-par[0],2)*pow(x[0]-par[1],2)*(par[2]*pow(x[0],3) + par[3]*pow(x[0],2) + par[4]*x[0] + par[5]) + par[6];} // correct one
double testPi0Asymmetry::polGausFit(double* x, double* par){return gausFit(x, par) + polFit(x, &par[3]);}
