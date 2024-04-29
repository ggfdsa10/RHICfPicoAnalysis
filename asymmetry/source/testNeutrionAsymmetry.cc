#include "testNeutronAsymmetry.hh"

testNeutronAsymmetry::testNeutronAsymmetry()
{
    mIsAllEvent = false;
    mIsSDLEMode = false;
    mIsDDLEMode = false;
    mIsCDLEMode = false;
    mIsNDLEMode = false;
    mIsDMLEMode = false;
    mIsTestMode = false;

    mDoFindBinMean = false;
    mDoDilution = false;
    mDoAsymmetry = false;
    mDoSaveData; = false;
    mDoDrawFigure = false;

    mEventNeutronCounts = 0;
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

testNeutronAsymmetry::~testNeutronAsymmetry()
{
}

void testNeutronAsymmetry::doSDLE(){
    mIsSDLEMode = true;
    mConditionName2 = "SDLE";
}

void testNeutronAsymmetry::doDDLE(){
    mIsDDLEMode = true;
    mConditionName2 = "DDLE";
}

void testNeutronAsymmetry::doCDLE(){
    mIsCDLEMode = true;
    mConditionName2 = "CDLE";
}

void testNeutronAsymmetry::doNDLE(){
    mIsNDLEMode = true;
    mConditionName2 = "NDLE";
}

void testNeutronAsymmetry::doDMLE(){
    mIsDMLEMode = true;
    mConditionName2 = "DMLE";
}

void testNeutronAsymmetry::doTestCondition(){
    mIsTestMode = true;
}


Int_t testNeutronAsymmetry::Init()
{
    cout << "testNeutronAsymmetry::Init() --- information" << endl;
    info();


    if(!mIsSDLEMode && !mIsDDLEMode && !mIsCDLEMode && !mIsNDLEMode && !mIsDMLEMode && !mIsTestMode){
       cout << "testNeutronAsymmetry::Init() --- Warning!!! event mode is NOT setted, set the all event mode" << endl;
       mIsAllEvent = true;
    }

    mOutFileName = mSaveDatPath + "/asymmetry_Neu_" + mConditionName + "_" + mConditionName2 + ".root";


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
    memset(mPtCutRangeAllXf, 0, sizeof(mPtCutRangeAllXf));
    memset(mXfCutRangeAllPt, 0, sizeof(mXfCutRangeAllPt));
    memset(mBinMean, 0, sizeof(mBinMean));
    memset(mDilutionFactor, 0, sizeof(mDilutionFactor));
    memset(polNum, 0, sizeof(polNum));

    mPtCutRangeAllXf[0] = 0.;
    mPtCutRangeAllXf[1] = 0.05;
    mPtCutRangeAllXf[2] = 0.1;
    mPtCutRangeAllXf[3] = 0.2;
    mPtCutRangeAllXf[4] = 0.3;
    mPtCutRangeAllXf[5] = 1.;

    mXfCutRangeAllPt[0] = 0.15;
    mXfCutRangeAllPt[1] = 0.3;
    mXfCutRangeAllPt[2] = 0.4;
    mXfCutRangeAllPt[3] = 0.5;
    mXfCutRangeAllPt[4] = 0.6;
    mXfCutRangeAllPt[5] = 1.;


    // read datas
    if(!readData()){return 0;}

    mRunIdx = -1;

    for(int run = 0; run < kRunTypeNum; run++){
        hEnergy[run] = new TH1D(Form("energy_pi0_%s", mRunName[run].Data()), Form("energy_pi0_%s", mRunName[run].Data()), 300, 0, 300);
        hPt[run] = new TH1D(Form("pt_pi0_%s", mRunName[run].Data()), Form("pt_pi0_%s", mRunName[run].Data()), 20, 0, 1.);
        hXf[run] = new TH1D(Form("xf_pi0_%s", mRunName[run].Data()), Form("xf_pi0_%s", mRunName[run].Data()), 20, 0, 1.);

        hEnergy[run] -> SetTitle(Form("#pi^{0} Energy; Energy [GeV];"));
        hPt[run] -> SetTitle(Form("#pi^{0} p_{T}; p_{T} [GeV/c];"));
        hXf[run] -> SetTitle(Form("#pi^{0} p_{T}; x_{F};"));

        hEnergy[run] -> SetStats(0);
        hPt[run]-> SetStats(0);
        hXf[run]-> SetStats(0);

        for(int pt=0; pt<kFinalBinPt; pt++){
            if(mDoFindBinMean){
                hBinMean[run][pt] = new TH1D(Form("hBinMean_%s_p%i", mRunName[run].Data(), pt), Form("hBinMean_%s_p%i", mRunName[run].Data(), pt), 100, 0., 1.);
                hBinMean[run][pt] -> SetTitle(Form("%s #pi^{0}; p_{T};", mRunName[run].Data()));
                hBinMean[run][pt] -> SetStats(0);
            }

            if(mDoDilution){
                hPhi[run][pt] = new TH1D(Form("hPhi_%s_p%i", mRunName[run].Data(), pt), Form("hPhi_%s_p%i", mRunName[run].Data(), pt), 100, 0., 180.);
                hPhi[run][pt] -> SetTitle("; #phi_{#pi^{0}} [#circ];");
                hPhi[run][pt] -> SetStats(0);
            }
        }

        // for Xf
        for(int xf=0; xf<kFinalBinXf; xf++){
            if(mDoFindBinMean){
                hBinMeanXf[run][xf] = new TH1D(Form("hBinMean_xf_%s_p%i", mRunName[run].Data(), xf), Form("hBinMean_xf_%s_type%i_p%i", mRunName[run].Data(), xf), 100, 0., 1.);
                hBinMeanXf[run][xf] -> SetTitle(Form("%s #pi^{0}; p_{T};", mRunName[run].Data()));
                hBinMeanXf[run][xf] -> SetStats(0);
            }

            if(mDoDilution){
                hPhiXf[run][xf] = new TH1D(Form("hPhi_xf_%s_p%i", mRunName[run].Data(), xf), Form("hPhi_xf_%s_p%i", mRunName[run].Data(), xf), 100, 0., 180.);
                hPhiXf[run][xf] -> SetTitle("; #phi_{#pi^{0}} [#circ];");
                hPhiXf[run][xf] -> SetStats(0);
            }
        }

    }
    if(mDoAsymmetry){
        gGeneralAsymPt = new TGraphErrors();
        gGeneralAsymPt -> SetName("GeneralAsymPtAllXf");
        gGeneralAsymXf = new TGraphErrors();
        gGeneralAsymXf -> SetName("GeneralAsymXfAllPt");
    }

    return 1;
}

Int_t testNeutronAsymmetry::Make()
{
    int eventNum = mPi0Tree->GetEntries();
    if(mEventNum == -1){mEventNum = eventNum;}
    cout << "testNeutronAsymmetry::Make() --- running... " << mEventNum << endl;

    for(int event=0; event< mEventNum; event++){
        if(event%10000==0){cout << " event: " << event << " / " << mEventNum << endl;}
        mPi0Tree -> GetEntry(event);

        for(int photon=0; photon<mPhotonNum; photon++){
            
            int photonTowerIdx = mPhotonTowerIdx[photon];
            double photonEnergy = mPhotonE[photon][1];

            if(mL90[photonTowerIdx] <= 20){continue;}
            if(photonEnergy < 20.){continue;}

            mEventNeutronCounts++;

            mRunIdx = getRunTypeIdx(mPi0fillNumber);

            if(mIsAllEvent == false){
                if(!conditionCheck()){continue;}
            }
            mEventSelectedCounts++;

            // Neutron informations 
            const double distZatIP = 18000.0; // [mm]
            const double neutronMass = 939.565; // [MeV/c^2]

            double neuPosX = mPhotonPos[photon][0]; // [m]
            double neuPosY = mPhotonPos[photon][1]; // [m]
            double neuPosZ = distZatIP*0.001; // [m]
            double neuR = TMath::Sqrt(neuPosX*neuPosX + neuPosY*neuPosY + neuPosZ*neuPosZ);

            double neuMass = neutronMass*0.001; // [GeV/c]
            double neuP = TMath::Sqrt(photonEnergy*photonEnergy - neuMass*neuMass);
            double neuPx = (neuPosX/neuR)*neuP;
            double neuPy = (neuPosY/neuR)*neuP;
            double neuPz = (neuPosZ/neuR)*neuP;

            double neuPt = TMath::Sqrt(neuPx*neuPx + neuPy*neuPy);
            double neuXf = neuPz/255.;

            // main binning ranges
            for(int pt=0; pt<kFinalBinPt; pt++){
                if(mPtCutRangeAllXf[pt] <= neuPt && neuPt < mPtCutRangeAllXf[pt+1]){
                    double neuAngle = (180./TMath::Pi())*TMath::ATan2(neuPosY, neuPosX); // [degree]

                    if(mDoFindBinMean){
                        mBinMean[mRunIdx][pt][0] += neuPt;
                        mBinMean[mRunIdx][pt][1] += 1.;

                        hBinMean[mRunIdx][pt] -> Fill(neuPt);
                    }

                    // for dilution factor
                    if(mDoDilution){
                        hPhi[mRunIdx][pt] -> Fill(neuAngle);
                        mDilutionFactor[mRunIdx][pt] += TMath::Sin(neuAngle*TMath::Pi()/180.);
                    }

                    // for asymmetry
                    if(mDoAsymmetry){
                        int fillIdx = getFillNumIdx(mPi0fillNumber);

                        // for pi0 asymmetry
                        if(0. < neuAngle && neuAngle < 180.){
                            if(mPi0BlueSpinUp == true){polNum[fillIdx][pt][1] += 1.;} // left 
                            else{polNum[fillIdx][pt][0] += 1.;} // right 
                        }
                        else{
                            if(mPi0BlueSpinUp == true){polNum[fillIdx][pt][0] += 1.;} // right
                            else{polNum[fillIdx][pt][1] += 1.;} // left
                        }
                    }
                    
                }
            }

            // for Xf
            for(int xf=0; xf<kFinalBinXf; xf++){
                if(mXfCutRangeAllPt[xf] <= neuXf && neuXf < mXfCutRangeAllPt[xf+1]){
                    double neuAngle = (180./TMath::Pi())*TMath::ATan2(neuPosY, neuPosX); // [degree]

                    if(mDoFindBinMean){
                        mBinMeanXf[mRunIdx][xf][0] += neuXf;
                        mBinMeanXf[mRunIdx][xf][1] += 1.;

                        hBinMeanXf[mRunIdx][xf] -> Fill(neuXf);
                    }

                    // for dilution factor
                    if(mDoDilution){
                        hPhiXf[mRunIdx][xf] -> Fill(neuAngle);
                        mDilutionFactorXf[mRunIdx][xf] += TMath::Sin(neuAngle*TMath::Pi()/180.);
                    }

                    // for asymmetry
                    if(mDoAsymmetry){
                        int fillIdx = getFillNumIdx(mPi0fillNumber);

                        // for pi0 asymmetry
                        if(0. < neuAngle && neuAngle < 180.){
                            if(mPi0BlueSpinUp == true){polNumXf[fillIdx][xf][1] += 1.;} // left 
                            else{polNumXf[fillIdx][xf][0] += 1.;} // right 
                        }
                        else{
                            if(mPi0BlueSpinUp == true){polNumXf[fillIdx][xf][0] += 1.;} // right
                            else{polNumXf[fillIdx][xf][1] += 1.;} // left
                        }
                    }
                }
            }
        }
    }

    for(int run = 0; run < kRunTypeNum; run++){
        mRunIdx = run;
        if(mDoFindBinMean){findBinMean();}
        if(mDoDilution){dilutionFactor();}
    
    }

    if(mDoAsymmetry){asymmetry();}

    if(mDoSaveData){saveData();}
    if(mDoDrawFigure){drawFigure();}

    return 1;
}

Int_t testNeutronAsymmetry::Finish()
{
    for(int run=0; run<kRunTypeNum; run++){
        delete hEnergy[run];
        delete hPt[run];
        delete hXf[run];
    }

    mAnalPi0File->Close();
}

Int_t testNeutronAsymmetry::clear();

void testNeutronAsymmetry::setFile(TString file){mFilePath = file;}
void testNeutronAsymmetry::setSaveFigPath(TString path){mSaveDatPath = path;}

int testNeutronAsymmetry::getRunTypeIdx(int fillNum)
{
    if(fillNum == 21142 || fillNum == 21145){return 0;}
    if(fillNum == 21148 || fillNum == 21150){return 1;}
    if(fillNum == 21149){return 2;}
    return -1;
}

int testNeutronAsymmetry::getFillNumIdx(int fillNum)
{
    if(fillNum == 21142){return 0;}
    if(fillNum == 21145){return 1;}
    if(fillNum == 21148){return 2;}
    if(fillNum == 21149){return 3;}
    if(fillNum == 21150){return 4;}
    return -1;
}
int testNeutronAsymmetry::getFillToRunTypeIdx(int fillIdx)
{
    if(fillIdx == 0 || fillIdx == 1){return 0;}
    if(fillIdx == 2 || fillIdx == 4){return 1;}
    if(fillIdx == 3){return 2;}
    return -1;
}

double testNeutronAsymmetry::relativeluminosity(int fillIdx)
{
    if(fillIdx == 0){return 0.9581;}
    if(fillIdx == 1){return 0.9623;}
    if(fillIdx == 2){return 0.9924;}
    if(fillIdx == 3){return 0.9949;}
    if(fillIdx == 4){return 0.9774;}
    return 0.;
}

double testNeutronAsymmetry::beamPolarization(int fillIdx)
{
    if(fillIdx = 0){return 0.536;}
    if(fillIdx = 1){return 0.554;}
    if(fillIdx = 2){return 0.590;}
    if(fillIdx = 3){return 0.566;}
    if(fillIdx = 4){return 0.592;}
    return 0.;
}

void testNeutronAsymmetry::findBinMean()
{
    cout << "testNeutronAsymmetry::findBinMean() --- find a Mean value each xf, pt bins || run: " << mRunName[mRunIdx] << endl;
    for(int pt=0; pt<kFinalBinPt; pt++){
        if(mBinMean[mRunIdx][pt][0] < 10 || mBinMean[mRunIdx][pt][1] < 10){continue;}

        double ptMean = mBinMean[mRunIdx][pt][0]/mBinMean[mRunIdx][pt][1];
        cout << " <pt>: " << ptMean << " (" << endl;
    }

    for(int xf=0; xf<kFinalBinXf; xf++){
        if(mBinMeanXf[mRunIdx][xf][0] < 10 || mBinMeanXf[mRunIdx][xf][1] < 10){continue;}

        double xfMean = mBinMeanXf[mRunIdx][xf][0]/mBinMeanXf[mRunIdx][xf][1];
        cout << " <xf>: " << xfMean << " (" << endl;
    }
}

void testNeutronAsymmetry::dilutionFactor()
{
    cout << "testNeutronAsymmetry::dilutionFactor() --- calculate a dilution factor || run: " << mRunName[mRunIdx] << endl;
    for(int pt=0; pt<kFinalBinPt; pt++){
        double entrise = hPhi[mRunIdx][pt] -> GetEntries(); 
        mDilutionFactor[mRunIdx][pt] /= entrise;
        if(entrise < 1){mDilutionFactor[mRunIdx][pt] = 0.;}

        cout << mRunIdx << " " << pt << " " << mDilutionFactor[mRunIdx][pt] << endl;
    }

    for(int xf=0; xf<kFinalBinXf; xf++){
        double entrise = hPhiXf[mRunIdx][xf] -> GetEntries(); 
        mDilutionFactorXf[mRunIdx][xf] /= entrise;
        if(entrise < 1){mDilutionFactorXf[mRunIdx][xf] = 0.;}

        cout << mRunIdx << " " << xf << " " << mDilutionFactorXf[mRunIdx][xf] << endl;
    }
}

void testNeutronAsymmetry::asymmetry()
{
    cout << "testNeutronAsymmetry::asymmetry() --- calculate Asymmetry " << endl;

    double AN[kFillNum][kFinalBinPt][3]; // [an, anErr, wieght]
    double ANXf[kFillNum][kFinalBinXf][3]; // [an, anErr, wieght]
    memset(AN, 0, sizeof(AN));
    memset(ANXf, 0, sizeof(ANXf));

    for(int fill = 0; fill < kFillNum; fill++){
        double relaLumi = relativeluminosity(fill);
        double beamPol = beamPolarization(fill);
        int runIdx = getFillToRunTypeIdx(fill);

        for(int pt=0; pt<kFinalBinPt; pt++){
            double dilution = mDilutionFactor[runIdx][pt];
            if(dilution <= 0.01){continue;}

            // signal + background asymmetry
            double rightPolNum = polNum[fill][pt][0];
            double leftPolNum = polNum[fill][pt][1];
            if(rightPolNum+leftPolNum <= 0.5){continue;}

            double anAll = -1./(dilution * beamPol) * (leftPolNum - relaLumi * rightPolNum) / ((leftPolNum + relaLumi * rightPolNum));
            double anAllErr = 1./TMath::Sqrt(rightPolNum + leftPolNum);

            double an = anAll;
            double anErr = anAllErr;
            double wieght = rightPolNum + leftPolNum;

            AN[fill][pt][0] = an;
            AN[fill][pt][1] = anErr;
            AN[fill][pt][2] = wieght;

            double ptMean = mBinMean[runIdx][pt][0]/mBinMean[runIdx][pt][1]; 

            int idx = gGeneralAsymPt -> GetN();
            gGeneralAsymPt -> SetPoint(idx, ptMean, an);
            gGeneralAsymPt -> SetPointError(idx, 0., anErr);
        }

        // for Xf
        for(int xf=0; xf<kFinalBinXf; xf++){
            double dilution = mDilutionFactorXf[runIdx][xf];
            if(dilution <= 0.01){continue;}

            // signal + background asymmetry
            double rightPolNum = polNumXf[fill][xf][0];
            double leftPolNum = polNumXf[fill][xf][1];
            if(rightPolNum+leftPolNum <= 0.5){continue;}

            double anAll = -1./(dilution * beamPol) * (leftPolNum - relaLumi * rightPolNum) / ((leftPolNum + relaLumi * rightPolNum));
            double anAllErr = 1./TMath::Sqrt(rightPolNum + leftPolNum);

            double an = anAll;
            double anErr = anAllErr;
            double wieght = rightPolNum + leftPolNum;

            ANXf[fill][xf][0] = an;
            ANXf[fill][xf][1] = anErr;
            ANXf[fill][xf][2] = wieght;

            double ptMean = mBinMeanXf[runIdx][xf][0]/mBinMeanXf[runIdx][xf][1]; 

            int idx = gGeneralAsymXf -> GetN();
            gGeneralAsymXf -> SetPoint(idx, ptMean, an);
            gGeneralAsymXf -> SetPointError(idx, 0., anErr);
        }
    }
    cout << "testNeutronAsymmetry::asymmetry() --- done !!!" << endl;
}

bool testNeutronAsymmetry::conditionCheck()
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
            // if(mBBCLSumWest < mBBCLSumADCThr[1] && mBBCSSumWest < mBBCSSumADCThr[1]){ // LMLE2Thr
            // if(mBBCLSumWest < mBBCLSumADCThr[1] && mBBCSSumWest < mBBCSSumADCThr[1] && mVPDSumWest < mVPDSumADCThr[1]){ // LMLE3Thr
            //     return 1;
            // }

            // if(mBBCLSumWest > 0){ // HMLE1
            // if(mBBCLSumWest > 0 && mBBCSSumWest > 0){ // HMLE2
            // if(mBBCLSumWest > 0 && mBBCSSumWest > 0 && mVPDSumWest == 0){ // HMLE3
            // if(mBBCLSumWest > mBBCLSumADCThr[1]){ // HMLE1Thr
            if(mBBCLSumWest > mBBCLSumADCThr[1] && mBBCSSumWest > mBBCSSumADCThr[1]){ // HMLE2Thr
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

int testNeutronAsymmetry::bbcMultiplicity(int ew, int det)
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

int testNeutronAsymmetry::vpdMultiplicity(int ew)
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

void testNeutronAsymmetry::drawFigure()
{
    cout << "testNeutronAsymmetry::drawFigure() --- drawing ... "  << endl;

    if(mDoFindBinMean){
        TCanvas* cMeanBin = new TCanvas("cMeanBin", "cMeanBin", 3*750, 3*750);
        TLatex* meanLatex = new TLatex();
        for(int run=0; run<kRunTypeNum; run++){

            cMeanBin -> Clear();
            cMeanBin -> Divide(2, 3);

            int entries = 0;
            for(int pt=0; pt<kFinalBinPt; pt++){
                entries += hBinMean[run][pt] -> GetEntries();
            }
            if(entries < 10){continue;}

            int tmpIdx = 0;
            for(int pt=0; pt<kFinalBinPt; pt++){
                tmpIdx++;
                const int c1Idx = tmpIdx;
                cMeanBin -> cd(c1Idx);
                gPad -> SetGrid(0,0);

                hBinMean[run][pt] -> Draw();

                meanLatex -> Clear();
                meanLatex -> SetTextSize(0.05);
                meanLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                meanLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRangeAllXf[pt], mPtCutRangeAllXf[pt+1]));
                meanLatex -> DrawLatexNDC(0.57, 0.6, "0 < x_{F} < 1");

                meanLatex -> SetTextSize(0.06);
                meanLatex -> DrawLatexNDC(0.55, 0.45, Form("mean = %.3f", mBinMean[run][pt][0]/mBinMean[run][pt][1]));
            }
        
            cMeanBin -> Draw();
            cMeanBin -> SaveAs(Form("%s/MeanEachBin_%s_Neu.pdf", mSaveFigPath.Data(), mRunName[run].Data()));
            
        }
    }

    if(mDoDilution){
        TCanvas* cDilution = new TCanvas("cDilution", "cDilution", 3*750, 3*750);
        TLatex* dilutionLatex = new TLatex();
        for(int run=0; run<kRunTypeNum; run++){
            cDilution -> Clear();
            cDilution -> Divide(2, 3);

            int entries = 0;
            for(int pt=0; pt<kFinalBinPt; pt++){
                entries += hPhi[run][pt] -> GetEntries();
            }
            if(entries < 10){continue;}

            int tmpIdx = 0;
            for(int pt=0; pt<kFinalBinPt; pt++){
                tmpIdx++;
                const int c1Idx = tmpIdx;
                cDilution -> cd(c1Idx);

                gPad -> SetGrid(0,0);
                hPhi[run][pt] -> GetXaxis() -> SetRangeUser(0., 200.);
                hPhi[run][pt] -> Draw();

                dilutionLatex -> Clear();
                dilutionLatex -> SetTextSize(0.06);
                dilutionLatex -> DrawLatexNDC(0.6, 0.8, Form("D_{#phi} = %.3f", mDilutionFactor[run][pt]));
                dilutionLatex -> Draw("same");

                dilutionLatex -> Clear();
                dilutionLatex -> SetTextSize(0.05);
                dilutionLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                dilutionLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRangeAllXf[pt], mPtCutRangeAllXf[pt+1]));
                dilutionLatex -> DrawLatexNDC(0.57, 0.6,"0 < x_{F} < 1");
                dilutionLatex -> Draw("same");
            }
            
            cDilution -> Draw();
            cDilution -> SaveAs(Form("%s/DilutionFactor_%s_Neu.pdf", mSaveFigPath.Data(), mRunName[run].Data()));
        }
    }

    if(mDoAsymmetry){
        // test !!!
        // save graph into TFile for comparison asymmetry with other condition, ex) tpc track, fps photon or not
        TFile* fileAsym = new TFile(Form("%s", mOutFileName.Data()), "recreate");
        fileAsym -> cd();
        gGeneralAsymPt -> Write();
        gGeneralAsymXf -> Write();

        TTree* treeCounts = new TTree("count", "count");
        Int_t outNeutronCount;
        Int_t outSelectCount;
        treeCounts -> Branch("NeuCount", &outNeutronCount, "outNeutronCount/I");
        treeCounts -> Branch("SelectCount", &outSelectCount, "outSelectCount/I");
        outNeutronCount = mEventNeutronCounts;
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

int testNeutronAsymmetry::readData()
{
    memset(mOptionChecker, 0, sizeof(mOptionChecker));

    if(mDoFindBinMean == false){
        ifstream binMeanFile;
        TString dataPath = mSaveDatPath+"/MeanEachBin_Neu_" + mConditionName + ".dat";
        binMeanFile.open(dataPath.Data());
        if(binMeanFile.is_open()){
            while(!binMeanFile.eof()){
                int run, pt;
                double meanXf, meanPt;
                int ptNum;
                binMeanFile >> run >> pt >> meanPt >> ptNum;
                mBinMean[run][pt][0] = meanPt;
                mBinMean[run][pt][1] = ptNum;

                if(ptNum > 1){mOptionChecker[3] = true;}
            }
            cout << "testNeutronAsymmetry::readData() --- Mean each bins data is OK" << endl;
        }
        else{
            cout << "testNeutronAsymmetry::readData() --- Can't opend findBinMean data " << dataPath << endl;
            return 0;
        }
        binMeanFile.close();

        // for Xf
        mOptionChecker[3] = false;
        ifstream binMeanFileXf;
        TString dataPath = mSaveDatPath+"/MeanEachBin_Neu_" + mConditionName + "_xf.dat";
        binMeanFileXf.open(dataPath.Data());
        if(binMeanFileXf.is_open()){
            while(!binMeanFileXf.eof()){
                int run, xf;
                double meanXf;
                int xfNum;
                binMeanFileXf >> run >> xf >> meanXf >> xfNum;
                mBinMeanXf[run][xf][0] = meanXf;
                mBinMeanXf[run][xf][1] = xfNum;

                if(xfNum > 1){mOptionChecker[3] = true;}
            }
            cout << "testNeutronAsymmetry::readData() --- Mean each bins data for xf is OK" << endl;
        }
        else{
            cout << "testNeutronAsymmetry::readData() --- Can't opend findBinMean data for xf" << dataPath << endl;
            return 0;
        }
        binMeanFileXf.close();
    }
    if(mDoDilution == false && mDoFindBinMean == false){
        ifstream dilutionFactorFile;
        TString dataPath = mSaveDatPath+"/DilutionFactor_Neu_" + mConditionName + ".dat";
        dilutionFactorFile.open(dataPath.Data());
        if(dilutionFactorFile.is_open()){
            while(!dilutionFactorFile.eof()){
                int run, xf, pt;
                double factor;
                dilutionFactorFile >> run >> pt >> factor;
                mDilutionFactor[run][pt] = factor;

                if(factor > 0.1){mOptionChecker[4] = true;}
            }
            cout << "testNeutronAsymmetry::readData() --- Dilution Factor data is OK" << endl;
        }
        else{
            cout << "testNeutronAsymmetry::readData() --- Can't opend Dilution data " << dataPath << endl;
            return 0;
        }
        dilutionFactorFile.close();


        // for Xf
        mOptionChecker[4] = false;
        ifstream dilutionFactorFileXf;
        TString dataPath = mSaveDatPath+"/DilutionFactor_Neu_" + mConditionName + "_xf.dat";
        dilutionFactorFileXf.open(dataPath.Data());
        if(dilutionFactorFileXf.is_open()){
            while(!dilutionFactorFileXf.eof()){
                int run, xf;
                double factor;
                dilutionFactorFileXf >> run >> xf >> factor;
                mDilutionFactorXf[run][xf] = factor;

                if(factor > 0.1){mOptionChecker[4] = true;}
            }
            cout << "testNeutronAsymmetry::readData() --- Dilution Factor data for xf is OK" << endl;
        }
        else{
            cout << "testNeutronAsymmetry::readData() --- Can't opend Dilution data for xf" << dataPath << endl;
            return 0;
        }
        dilutionFactorFileXf.close();
    } 

    if(mDoFindBinMean == false && mOptionChecker[3] == false){
        cout << "testNeutronAsymmetry::readData() ---  Mean each bins data is something wrong !! " << endl;
        return 0;
    }
    if(mDoDilution == false && mDoFindBinMean == false && mOptionChecker[4] == false){
        cout << "testNeutronAsymmetry::readData() ---  Dilution Factor data is something wrong !! " << endl;
        return 0;
    }
    return 1;
}

void testNeutronAsymmetry::saveData()
{
    cout << "testNeutronAsymmetry::saveData() --- data saving ..." << endl;

    if(mDoFindBinMean){
        ofstream binMeanFile;
        TString dataPath = mSaveDatPath+"/MeanEachBin_Neu_" + mConditionName + ".dat";
        binMeanFile.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int pt=0; pt<kFinalBinPt; pt++){
                binMeanFile << run << " " << pt << " " << 
                mBinMean[run][pt][0] << " " << 
                mBinMean[run][pt][1] << " " << endl;
            }
            
        }
        binMeanFile.close();
        cout << "mean value each bins data is saved !" << endl;

        // for xf
        ofstream binMeanFileXf;
        TString dataPath = mSaveDatPath+"/MeanEachBin_Neu_" + mConditionName + "_xf.dat";
        binMeanFileXf.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int xf=0; xf<kFinalBinXf; xf++){
                binMeanFileXf << run << " " << xf << " " << 
                mBinMeanXf[run][xf][0] << " " << 
                mBinMeanXf[run][xf][1] << " " << endl;
            }
            
        }
        binMeanFileXf.close();
        cout << "mean value each bins data for xf is saved !" << endl;
    }
    if(mDoDilution){
        ofstream dilutionFactorFile;
        TString dataPath = mSaveDatPath+"/DilutionFactor_Neu_" + mConditionName + ".dat";
        dilutionFactorFile.open(dataPath.Data());
        
        for(int run=0; run<kRunTypeNum; run++){
            for(int pt=0; pt<kFinalBinPt; pt++){
                dilutionFactorFile << run << " " << pt << " " << mDilutionFactor[run][pt] << endl;
            }   
        }
        dilutionFactorFile.close();
        cout << "Dilution Factor data is saved !" << endl;


        // for xf
        ofstream dilutionFactorFileXf;
        TString dataPath = mSaveDatPath+"/DilutionFactor_Neu_" + mConditionName + "_xf.dat";
        dilutionFactorFileXf.open(dataPath.Data());
        
        for(int run=0; run<kRunTypeNum; run++){
            for(int xf=0; xf<kFinalBinXf; xf++){
                dilutionFactorFileXf << run << " " << xf << " " << mDilutionFactorXf[run][xf] << endl;
            }   
        }
        dilutionFactorFileXf.close();
        cout << "Dilution Factor data is saved !" << endl;
    }
}

void testNeutronAsymmetry::info()
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
    cout << "testNeutronAsymmetry::info() --- option On-Off" << endl;

    TString optionOn = "";
    optionOn = (mDoFindBinMean)? "ON" : "OFF";
    cout << "    DoFindBinMean --- " << optionOn << endl;
    optionOn = (mDoDilution)? "ON" : "OFF";
    cout << "    DoDilutionFactor --- " << optionOn << endl;
    optionOn = (mDoAsymmetry)? "ON" : "OFF";
    cout << "    DoAsymmetry --- " << optionOn << endl;
    optionOn = (mDoSaveData)? "ON" : "OFF";
    cout << "    DoSaveData --- " << optionOn << endl;
    optionOn = (mDoDrawFigure)? "ON" : "OFF";
    cout << "    DoDrawFigure --- " << optionOn << endl;

    cout << "" << endl;
}
