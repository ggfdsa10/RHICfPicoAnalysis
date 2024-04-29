#include "Pi0Asymmetry.hh"

Pi0Asymmetry::Pi0Asymmetry()
{
    mIsSDLEMode = false;
    mIsDDLEMode = false;
    mIsHDLEMode = false;

    mDoFindGenMassCut = false;
    mDoBinning = false;
    mDoBkgEstimation = false;
    mDoFindBinMean = false;
    mDoDilution = false;
    mDoAsymmetry = false;
    mNotCalBkg = false;
    mDoSaveData; = false;
    mDoDrawFigure = false;

    mPath = "/star/u/slee5/forRHICf/asymmetry";
    mSaveDatPath = mPath+"/data";
    mSaveFigPath = mPath+"/figure";
    mFilePath = mSaveDatPath+"/AnalRHICfPi0.root";

    mConditionName = "All";
    mConditionName2 = "";
    mEventNum = -1;

    mRunName[0] = "TL";
    mRunName[1] = "TS";
    mRunName[2] = "TOP";

    mGenRangeXF[0] = 0.25;
    mGenRangeXF[1] = 0.34;
    mGenRangeXF[2] = 0.44;
    mGenRangeXF[3] = 0.58;
    mGenRangeXF[4] = 1.;

    mGenRangePT[0] = 0.;
    mGenRangePT[1] = 0.07;
    mGenRangePT[2] = 0.19;
    mGenRangePT[3] = 0.3;
    mGenRangePT[4] = 0.5;
    mGenRangePT[5] = 0.69;
    mGenRangePT[6] = 1.;

    mPtCutRangeAllXf[0] = 0.;
    mPtCutRangeAllXf[1] = 0.1;
    mPtCutRangeAllXf[2] = 0.2;
    mPtCutRangeAllXf[3] = 0.3;
    mPtCutRangeAllXf[4] = 0.4;
    mPtCutRangeAllXf[5] = 1.;

}

Pi0Asymmetry::~Pi0Asymmetry()
{
}

Int_t Pi0Asymmetry::Init()
{
    cout << "Pi0Asymmetry::Init() --- information" << endl;
    info();

    mAnalPi0File = new TFile(Form("%s", mFilePath.Data()), "read");
    mPi0Tree = (TTree*)mAnalPi0File->Get("pi0");

	mPi0Tree -> SetBranchAddress("tofMult", &mTofMult);
	mPi0Tree -> SetBranchAddress("gloMult", &mGRefMult);
	mPi0Tree -> SetBranchAddress("refMult", &mRefMult);

	mPi0Tree -> SetBranchAddress("bbcWest", &mBBCWest);
	mPi0Tree -> SetBranchAddress("bbcEast", &mBBCEast);
	mPi0Tree -> SetBranchAddress("bbcLargeWest", &mBBCLargeWest);
	mPi0Tree -> SetBranchAddress("bbcLargeEast", &mBBCLargeEast);

	mPi0Tree -> SetBranchAddress("vpdWest", &mVPDWest);
	mPi0Tree -> SetBranchAddress("vpdEast", &mVPDEast);

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
    memset(mXfCutRange, 0, sizeof(mXfCutRange));
    memset(mPtCutRange, 0, sizeof(mPtCutRange));
    memset(mInitBinRange, 0, sizeof(mInitBinRange));
    memset(mMassCutRange, 0, sizeof(mMassCutRange));
    memset(mMassFitIntegral, 0, sizeof(mMassFitIntegral));
    memset(mBinMean, 0, sizeof(mBinMean));
    memset(mDilutionFactor, 0, sizeof(mDilutionFactor));
    memset(polNum, 0, sizeof(polNum));
    memset(bkgPolNum, 0, sizeof(bkgPolNum));

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
            hpt_xf[run][type] = new TH2D(Form("ptxf_type%i_pi0_%s", type+1, mRunName[run].Data()), Form("ptxf_type%i_pi0_%s", type+1, mRunName[run].Data()), 100, 0, 1., 100, 0, 1.);

            hEnergy[run][type] -> SetTitle(Form("type%i #pi^{0} Energy; Energy [GeV];", type+1));
            hPt[run][type] -> SetTitle(Form("type%i #pi^{0} p_{T}; p_{T} [GeV/c];", type+1));
            hXf[run][type] -> SetTitle(Form("type%i #pi^{0} x_{F}; x_{F} ;", type+1));
            hpt_xf[run][type] -> SetTitle(Form("type%i #pi^{0} kinematics; x_{F} ; p_{T} [GeV/c]", type+1));

            hEnergy[run][type] -> SetStats(0);
            hPt[run][type] -> SetStats(0);
            hXf[run][type] -> SetStats(0);
            hpt_xf[run][type] -> SetStats(0);

            // for binning
            if(mDoBinning){
                for(int i=0; i<kBinningRangeNum; i++){
                    if(i<20){
                        hPtInXfBin[run][type][i] = new TH1D(Form("ptInXfBin_%i_type%i_%s", i, type+1, mRunName[run].Data()), Form("ptInXfBin_%i_type%i_%s", i, type+1, mRunName[run].Data()), 100, 0., 1.);
                        hXfInPtBin[run][type][i] = new TH1D(Form("xfInPtBin_%i_type%i_%s", i, type+1, mRunName[run].Data()), Form("xfInPtBin_%i_type%i_%s", i, type+1, mRunName[run].Data()), 100, 0., 1.);
                    }
                    mInitBinRange[i] = 0.05*double(i);
                }
            }

            for(int xf=0; xf<kFinalBinXf; xf++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    if(mDoBkgEstimation){
                        hMass[run][type][xf][pt] = new TH1D(Form("hMass_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), Form("hMass_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), 80, 0., 300.);
                        hMass[run][type][xf][pt] -> SetTitle("; m_{#gamma#gamma} [MeV/c^{2}];");
                        hMass[run][type][xf][pt] -> SetStats(0);
                    }

                    if(mDoFindBinMean){
                        hBinMean[run][type][xf][pt][0] = new TH1D(Form("hBinMeanXf_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), Form("hBinMeanXf_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), 100, 0., 1.);
                        hBinMean[run][type][xf][pt][1] = new TH1D(Form("hBinMeanPt_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), Form("hBinMeanPt_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), 100, 0., 1.);
                        hBinMean[run][type][xf][pt][0] -> SetTitle(Form("%s type%i #pi^{0} x_{F}; x_{F};", mRunName[run].Data(), type+1));
                        hBinMean[run][type][xf][pt][0] -> SetStats(0);
                        hBinMean[run][type][xf][pt][1] -> SetTitle(Form("%s type%i #pi^{0} p_{T}; p_{T} [GeV/c];", mRunName[run].Data(), type+1));
                        hBinMean[run][type][xf][pt][1] -> SetStats(0);
                    }

                    if(mDoDilution){
                        hPhi[run][type][xf][pt] = new TH1D(Form("hPhi_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), Form("hPhi_%s_type%i_x%i_p%i", mRunName[run].Data(), type+1, xf, pt), 100, 0., 180.);
                        hPhi[run][type][xf][pt] -> SetTitle("; #phi_{#pi^{0}} [#circ];");
                        hPhi[run][type][xf][pt] -> SetStats(0);
                    }
                }
            }
        }

        if(mDoAsymmetry){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    gAsymByXf[run][type][pt] = new TGraphErrors();
                    gAsymByXf[run][type][pt] -> SetName(Form("%s_type%i_p%i_AsymByXf", mRunName[run].Data(), type+1, pt));
                }
                for(int xf=0; xf<kFinalBinXf; xf++){
                    gAsymByPt[run][type][xf] = new TGraphErrors();
                    gAsymByPt[run][type][xf] -> SetName(Form("%s_type%i_x%i_AsymByPt", mRunName[run].Data(), type+1, xf));
                }

                for(int pt=0; pt<kGeneralBinPt; pt++){
                    gTypeAsymByXf[run][type][pt] = new TGraphErrors();
                    gTypeAsymByXf[run][type][pt] -> SetName(Form("%s_p%i_type%i_GeneralAsymByXf", mRunName[run].Data(), pt, type+1));

                    if(type==0){
                        gRunAsymByXf[run][pt] = new TGraphErrors();
                        gRunAsymByXf[run][pt] -> SetName(Form("%s_p%i_GeneralAsymByXf", mRunName[run].Data(), pt));
                    }
                }
                for(int xf=0; xf<kGeneralBinXf; xf++){
                    gTypeAsymByPt[run][type][xf] = new TGraphErrors();
                    gTypeAsymByPt[run][type][xf] -> SetName(Form("%s_x%i_type%i_GeneralAsymByPt", mRunName[run].Data(), xf, type+1));

                    if(type==0){
                        gRunAsymByPt[run][xf] = new TGraphErrors();
                        gRunAsymByPt[run][xf] -> SetName(Form("%s_p%i_GeneralAsymByPt", mRunName[run].Data(), pt));
                    }
                }
            }
            gGeneralAsymPt = new TGraphErrors();
            gGeneralAsymPt -> SetName("GeneralAsymPtAllXf");

            gTmpAsymPt = new TGraphErrors();
            gTmpAsymPt -> SetName("AsymPt");

        }
    }
    if(mDoAsymmetry){
        for(int pt=0; pt<kGeneralBinPt; pt++){
            gGeneralAsymByXf[pt] = new TGraphErrors();
            gGeneralAsymByXf[pt] -> SetName(Form("AsymmetryByXf_p%i", pt));
        }
        for(int xf=0; xf<kGeneralBinXf; xf++){
            gGeneralAsymByPt[xf] = new TGraphErrors();
            gGeneralAsymByPt[xf] -> SetName(Form("AsymmetryByPt_x%i", xf));
        }
    }

    fMassFit = new TF1("fit_allMass", &Pi0Asymmetry::polGausFit, 25, 250, 10);
    fMassBkgFit = new TF1("bkgFi_allMass", &Pi0Asymmetry::polFit, 100, 180, 7);
    fMassSignalFit = new TF1("signalFit_allMass", &Pi0Asymmetry::gausFit, 25, 280, 3);
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

Int_t Pi0Asymmetry::Make()
{
    int eventNum = mPi0Tree->GetEntries();
    if(mEventNum == -1){mEventNum = eventNum;}
    cout << "Pi0Asymmetry::Make() --- running... " << mEventNum << endl;

    for(int event=0; event< mEventNum; event++){
        if(event%10000==0){cout << " event: " << event << " / " << mEventNum << endl;}
        mPi0Tree -> GetEntry(event);

        mRunIdx = getRunTypeIdx(mPi0fillNumber);
        mTypeIdx = mPi0Type-1;

        if(mIsSDLEMode == true){
            if(mTofMult > 0){continue;} 
            if(mBBCWest > 0){continue;} 
            if(mBBCLargeWest > 0){continue;} 
            if(mVPDWest > 0){continue;} 
            if(mZDCADCSumWest > 0){continue;} 
        }
        if(mIsDDLEMode == true){
            if(mTofMult > 0){continue;} 
            if(mBBCWest > 0){continue;} 
            if(mBBCLargeWest > 0){continue;} 
            if(mBBCEast > 0){continue;} 
            if(mBBCLargeEast > 0){continue;} 
        }
        if(mIsHDLEMode == true){ // test, to be study for this mode, and I will apply New condition
            if(mTofMult > 0){continue;} 
            if(mBBCWest > 0){continue;} 
            if(mBBCLargeWest > 0){continue;} 
            if(mBBCEast > 0){continue;} 
            if(mBBCLargeEast > 0){continue;} 
        }



        if(mDoFindGenMassCut){hMassAll[mRunIdx][mTypeIdx] -> Fill(mPi0Mass);}

        if(mDoBinning){
            double massCutBelow = mGenMassCutRange[mRunIdx][mTypeIdx][0] - 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
            double massCutAbove = mGenMassCutRange[mRunIdx][mTypeIdx][0] + 3.*mGenMassCutRange[mRunIdx][mTypeIdx][1];
            if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){
                hXf[mRunIdx][mTypeIdx] -> Fill(mPi0Xf);
                hPt[mRunIdx][mTypeIdx] -> Fill(mPi0Pt);
                hpt_xf[mRunIdx][mTypeIdx] -> Fill(mPi0Xf, mPi0Pt);
                for(int i=0; i<20; i++){
                    if(mInitBinRange[i] <= mPi0Xf && mPi0Xf < mInitBinRange[i+1]){hPtInXfBin[mRunIdx][mTypeIdx][i] -> Fill(mPi0Pt);}
                    if(mInitBinRange[i] <= mPi0Pt && mPi0Pt < mInitBinRange[i+1]){hXfInPtBin[mRunIdx][mTypeIdx][i] -> Fill(mPi0Xf);}
                }
            }
        }

        // main binning ranges
        for(int xf=0; xf<kFinalBinXf; xf++){
            if(mXfCutRange[mRunIdx][mTypeIdx][xf] <= mPi0Xf && mPi0Xf < mXfCutRange[mRunIdx][mTypeIdx][xf+1]){

                for(int pt=0; pt<kFinalBinPt; pt++){
                    if(mPtCutRange[mRunIdx][mTypeIdx][pt] <= mPi0Pt && mPi0Pt < mPtCutRange[mRunIdx][mTypeIdx][pt+1]){
                        double phiAngle = (180./TMath::Pi())*TMath::ATan2(mPi0Y, mPi0X); // [degree]

                        // for background estimation
                        if(mDoBkgEstimation){
                            hMass[mRunIdx][mTypeIdx][xf][pt] -> Fill(mPi0Mass);
                        }

                        if(mDoFindBinMean){
                            double massCutBelow = mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] - 3.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            double massCutAbove = mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] + 3.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){ // |mass| <= 3 sigma
                                mBinMean[mRunIdx][mTypeIdx][xf][pt][0][0] += mPi0Xf;
                                mBinMean[mRunIdx][mTypeIdx][xf][pt][1][0] += mPi0Pt;
                                mBinMean[mRunIdx][mTypeIdx][xf][pt][0][1] += 1.;
                                mBinMean[mRunIdx][mTypeIdx][xf][pt][1][1] += 1.;

                                hBinMean[mRunIdx][mTypeIdx][xf][pt][0] -> Fill(mPi0Xf);
                                hBinMean[mRunIdx][mTypeIdx][xf][pt][1] -> Fill(mPi0Pt);
                            }
                        }

                        // for dilution factor
                        if(mDoDilution){
                            double massCutBelow = mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] - 3.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            double massCutAbove = mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] + 3.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){ // |mass| <= 3 sigma
                                hPhi[mRunIdx][mTypeIdx][xf][pt] -> Fill(phiAngle);
                                mDilutionFactor[mRunIdx][mTypeIdx][xf][pt] += TMath::Sin(phiAngle*TMath::Pi()/180.);
                            }
                        }

                        // for asymmetry
                        if(mDoAsymmetry){
                            int fillIdx = getFillNumIdx(mPi0fillNumber);

                            // for pi0 asymmetry
                            double massCutBelow = mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] - 3.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            double massCutAbove = mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] + 3.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            if(massCutBelow <= mPi0Mass && mPi0Mass <= massCutAbove){ // |mass| <= 3 sigma
                                if(0. < phiAngle && phiAngle < 180.){
                                    if(mPi0BlueSpinUp == true){polNum[fillIdx][mTypeIdx][xf][pt][1] += 1.;} // left 
                                    else{polNum[fillIdx][mTypeIdx][xf][pt][0] += 1.;} // right 
                                }
                                else{
                                    if(mPi0BlueSpinUp == true){polNum[fillIdx][mTypeIdx][xf][pt][0] += 1.;} // right
                                    else{polNum[fillIdx][mTypeIdx][xf][pt][1] += 1.;} // left
                                }
                            }

                            // for Background asymmetry
                            if(mNotCalBkg == true){continue;}
                            double massCutBelowForBkg = massCutBelow - 2.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            double massCutAboveForBkg = massCutAbove + 2.*mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1];
                            if((massCutBelowForBkg <= mPi0Mass && mPi0Mass < massCutBelow) || (massCutAbove < mPi0Mass && mPi0Mass <= massCutAboveForBkg)){ // 3 sigma < mass <= 5 sigma
                                if(0. < phiAngle && phiAngle < 180.){
                                    if(mPi0BlueSpinUp == true){bkgPolNum[fillIdx][mTypeIdx][xf][pt][1] += 1.;} // left 
                                    else{bkgPolNum[fillIdx][mTypeIdx][xf][pt][0] += 1.;} // right 
                                }
                                else{
                                    if(mPi0BlueSpinUp == true){bkgPolNum[fillIdx][mTypeIdx][xf][pt][0] += 1.;} // right
                                    else{bkgPolNum[fillIdx][mTypeIdx][xf][pt][1] += 1.;} // left
                                }
                            }
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
            if(mDoBinning){
                binningXF();
                binningPT();
            }
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

Int_t Pi0Asymmetry::Finish()
{
    for(int run=0; run<kRunTypeNum; run++){
        for(int type=0; type < kPi0TypeNum; type++){
            delete hMassAll[run][type];
            delete hEnergy[run][type];
            delete hPt[run][type];
            delete hXf[run][type];
            delete hpt_xf[run][type];

            for(int i=0; i<kBinningNum; i++){
                delete hPtInXfBin[run][type][i];
                delete hXfInPtBin[run][type][i];
            }

            for(int xf=0; xf<kFinalBinXf; xf++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    delete hMass[run][type][xf][pt];
                }
            }
        }
    }

    delete fMassFit;
    delete fMassBkgFit;
    delete fMassSignalFit;
    delete fbinningLandau;

    mAnalPi0File->Close();
}

Int_t Pi0Asymmetry::clear();

void Pi0Asymmetry::setFile(TString file){mFilePath = file;}
void Pi0Asymmetry::setSaveFigPath(TString path){mSaveDatPath = path;}

int Pi0Asymmetry::getRunTypeIdx(int fillNum)
{
    if(fillNum == 21142 || fillNum == 21145){return 0;}
    if(fillNum == 21148 || fillNum == 21150){return 1;}
    if(fillNum == 21149){return 2;}
    return -1;
}

int Pi0Asymmetry::getFillNumIdx(int fillNum)
{
    if(fillNum == 21142){return 0;}
    if(fillNum == 21145){return 1;}
    if(fillNum == 21148){return 2;}
    if(fillNum == 21149){return 3;}
    if(fillNum == 21150){return 4;}
    return -1;
}
int Pi0Asymmetry::getFillToRunTypeIdx(int fillIdx)
{
    if(fillIdx == 0 || fillIdx == 1){return 0;}
    if(fillIdx == 2 || fillIdx == 4){return 1;}
    if(fillIdx == 3){return 2;}
    return -1;
}

double Pi0Asymmetry::relativeluminosity(int fillIdx)
{
    if(fillIdx == 0){return 0.9581;}
    if(fillIdx == 1){return 0.9623;}
    if(fillIdx == 2){return 0.9924;}
    if(fillIdx == 3){return 0.9949;}
    if(fillIdx == 4){return 0.9774;}
    return 0.;
}

double Pi0Asymmetry::beamPolarization(int fillIdx)
{
    if(fillIdx = 0){return 0.536;}
    if(fillIdx = 1){return 0.554;}
    if(fillIdx = 2){return 0.590;}
    if(fillIdx = 3){return 0.566;}
    if(fillIdx = 4){return 0.592;}
    return 0.;
}


void Pi0Asymmetry::findGenMassCut()
{
    massFitting(hMassAll[mRunIdx][mTypeIdx]);
    double par[10];
    getMassFitPar(par);

    cout << "Pi0Asymmetry::findGenMassCut() --- find a general mass cut condition || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    cout << "===== " << par[0]-3.*par[1] << " < " << par[0] << " < " << par[0]+3.*par[1] << " [MeV/c^2]" << endl;
    mGenMassCutRange[mRunIdx][mTypeIdx][0] = par[0];
    mGenMassCutRange[mRunIdx][mTypeIdx][1] = par[1];
}

void Pi0Asymmetry::binningXF()
{
    if(hXf[mRunIdx][mTypeIdx]->GetEntries() < 1){return;}
    cout << "Pi0Asymmetry::binningXF() --- " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;

    double typeBound0 = (mTypeIdx==0)? 0.3 : 0.5;
    double typeBound1 = (mTypeIdx==0)? 0.7 : 0.8;

    fbinningLandau = new TF1(Form("%s_binFitLandau_type%i",mRunName[mRunIdx].Data(), mTypeIdx+1), "landau", typeBound1, typeBound0);
    fbinningLandau -> SetParameters(0., 0., 0.);

    for(int i=0; i<20; i++){
        double meanPtinXf = hPtInXfBin[mRunIdx][mTypeIdx][i] -> GetMean();
        double statics = hXf[mRunIdx][mTypeIdx] -> GetBinContent(i+1);
        statics /= meanPtinXf;
        if(statics <= 1 || meanPtinXf <= 1.e-4){statics = 0;}
        hXf[mRunIdx][mTypeIdx] -> SetBinContent(i+1, statics);
    }

    hXf[mRunIdx][mTypeIdx] -> Fit(fbinningLandau, "Q,R");

    double par[3];
    fbinningLandau -> GetParameters(par);

    fbinningLandau = new TF1(Form("%i_%itmp_landauFit",mRunIdx, mTypeIdx+1), "landau", 0., 1.);
    fbinningLandau -> SetParameters(par[0], par[1], par[2]);

    double xfIntegral = fbinningLandau -> Integral(0., 1.);
    xfIntegral /= double(kFinalBinXf);

    int tmpIdx = 0;
    double tmpBoundary = 0.;
    cout << "==== run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx << Form(" --- boundary_%i: ", tmpIdx) << tmpBoundary << endl;
    mXfCutRange[mRunIdx][mTypeIdx][tmpIdx] = tmpBoundary;

    for(int i=1; i<5000; i++){
        double endValue = double(i)/5000.;
        double inte = fbinningLandau -> Integral(tmpBoundary, endValue);
        if(xfIntegral < inte){
            tmpBoundary = endValue - 1./5000.;
            tmpIdx++;

            cout << "==== run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx << Form(" --- boundary_%i: ", tmpIdx) << tmpBoundary << endl;
            mXfCutRange[mRunIdx][mTypeIdx][tmpIdx] = tmpBoundary;
        }
    }
    mXfCutRange[mRunIdx][mTypeIdx][tmpIdx] = 1.;
}

void Pi0Asymmetry::binningPT()
{
    if(hPt[mRunIdx][mTypeIdx]->GetEntries() < 1){return;}
    cout << "Pi0Asymmetry::binningPT() --- " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;

    double typeBound0 = (mTypeIdx==0)? 0.05 : 0.3;
    double typeBound1 = (mTypeIdx==0)? 0.2 : 0.5;

    fbinningLandau = new TF1(Form("%s_binFitLandau_type%i",mRunName[mRunIdx].Data(), mTypeIdx+1), "landau", typeBound1, typeBound0);
    fbinningLandau -> SetParameters(0., 0., 0.);

    for(int i=0; i<20; i++){
        double meanXfinPt = hXfInPtBin[mRunIdx][mTypeIdx][i] -> GetMean();
        double statics = hPt[mRunIdx][mTypeIdx] -> GetBinContent(i+1);
        statics /= meanXfinPt;
        if(statics <= 1 || meanXfinPt <= 1.e-4){statics = 0;}
        hPt[mRunIdx][mTypeIdx] -> SetBinContent(i+1, statics);
    }

    hPt[mRunIdx][mTypeIdx] -> Fit(fbinningLandau, "Q,R");

    double par[3];
    fbinningLandau -> GetParameters(par);

    fbinningLandau = new TF1(Form("%i_%itmp_landauFit",mRunIdx, mTypeIdx+1), "landau", 0., 1.);
    fbinningLandau -> SetParameters(par[0], par[1], par[2]);

    double PtIntegral = fbinningLandau -> Integral(0., 1.);
    PtIntegral /= double(kFinalBinPt);

    int tmpIdx = 0;
    double tmpBoundary = 0.;
    cout << "==== run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx << Form(" --- boundary_%i: ", tmpIdx) << tmpBoundary << endl;
    mPtCutRange[mRunIdx][mTypeIdx][tmpIdx] = tmpBoundary;

    for(int i=1; i<5000; i++){
        double endValue = double(i)/5000.;
        double inte = fbinningLandau -> Integral(tmpBoundary, endValue);
        if(PtIntegral < inte){
            tmpBoundary = endValue - 1./5000.;
            tmpIdx++;

            cout << "==== run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx << Form(" --- boundary_%i: ", tmpIdx) << tmpBoundary << endl;
            mPtCutRange[mRunIdx][mTypeIdx][tmpIdx] = tmpBoundary;
        }
    }
    mPtCutRange[mRunIdx][mTypeIdx][tmpIdx] = 1.;
}

void Pi0Asymmetry::bkgEstimation()
{
    cout << "Pi0Asymmetry::bkgEstimation() --- find a general mass cut condition || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    for(int xf=0; xf<kFinalBinXf; xf++){
        for(int pt=0; pt<kFinalBinPt; pt++){
            double par[10];
            memset(par, 0, sizeof(par));
            int maxBin = hMass[mRunIdx][mTypeIdx][xf][pt] -> GetMaximumBin();
            int entries = hMass[mRunIdx][mTypeIdx][xf][pt] -> GetBinContent(35);

            if(33 <= maxBin && maxBin <= 39 || entries > 80){
                massFitting(hMass[mRunIdx][mTypeIdx][xf][pt]);

                getMassFitPar(par);
                cout << "=== " << par[0]-3.*par[1] << " < " << par[0] << " < " << par[0]+3.*par[1] << " [MeV/c^2] (" << 
                Form("%.2f<xf<%.2f", mXfCutRange[mRunIdx][mTypeIdx][xf], mXfCutRange[mRunIdx][mTypeIdx][xf+1]) << " && " << 
                Form("%.2f<pt<%.2f", mPtCutRange[mRunIdx][mTypeIdx][pt], mPtCutRange[mRunIdx][mTypeIdx][pt+1]) <<") " << endl;
            }
            mMassCutRange[mRunIdx][mTypeIdx][xf][pt][0] = par[0];
            mMassCutRange[mRunIdx][mTypeIdx][xf][pt][1] = par[1];

            // for signal and background rato
            if(par[0] > 10.){
                double allFitIntegral = fMassFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);
                double SignalFitIntegral = fMassSignalFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);
                double bkgFitIntegral = fMassBkgFit -> Integral(par[0] - 3.*par[1] , par[0] + 3.*par[1]);

                mMassFitIntegral[mRunIdx][mTypeIdx][xf][pt][0] = allFitIntegral;
                mMassFitIntegral[mRunIdx][mTypeIdx][xf][pt][1] = SignalFitIntegral;
                mMassFitIntegral[mRunIdx][mTypeIdx][xf][pt][2] = bkgFitIntegral;
            }
        }
    }
}

void Pi0Asymmetry::findBinMean()
{
    cout << "Pi0Asymmetry::findBinMean() --- find a Mean value each xf, pt bins || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    for(int xf=0; xf<kFinalBinXf; xf++){
        for(int pt=0; pt<kFinalBinPt; pt++){
            if(mBinMean[mRunIdx][mTypeIdx][xf][pt][0][1] < 10 || mBinMean[mRunIdx][mTypeIdx][xf][pt][1][1] < 10){continue;}

            double xfMean = mBinMean[mRunIdx][mTypeIdx][xf][pt][0][0]/mBinMean[mRunIdx][mTypeIdx][xf][pt][0][1];
            double ptMean = mBinMean[mRunIdx][mTypeIdx][xf][pt][1][0]/mBinMean[mRunIdx][mTypeIdx][xf][pt][1][1];
            cout << "<xf>: " << xfMean << " <pt>: " << ptMean << " (" <<            
            Form("%.2f<xf<%.2f", mXfCutRange[mRunIdx][mTypeIdx][xf], mXfCutRange[mRunIdx][mTypeIdx][xf+1]) << " && " << 
            Form("%.2f<pt<%.2f", mPtCutRange[mRunIdx][mTypeIdx][pt], mPtCutRange[mRunIdx][mTypeIdx][pt+1]) <<") " << endl;
        }
    }
}

void Pi0Asymmetry::dilutionFactor()
{
    cout << "Pi0Asymmetry::dilutionFactor() --- calculate a dilution factor || run: " << mRunName[mRunIdx] << " pi0Type: " << mTypeIdx+1 << endl;
    for(int xf=0; xf<kFinalBinXf; xf++){
        for(int pt=0; pt<kFinalBinPt; pt++){
            double entrise = hPhi[mRunIdx][mTypeIdx][xf][pt] -> GetEntries(); 
            mDilutionFactor[mRunIdx][mTypeIdx][xf][pt] /= entrise;
            if(entrise < 1){mDilutionFactor[mRunIdx][mTypeIdx][xf][pt] = 0.;}

            cout << mRunIdx << " " << mTypeIdx << " " << xf << " " << pt << " " << mDilutionFactor[mRunIdx][mTypeIdx][xf][pt] << endl;
        }
    }
}

void Pi0Asymmetry::asymmetry()
{
    cout << "Pi0Asymmetry::asymmetry() --- calculate Asymmetry " << endl;

    double estimatedWieght[kFillNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt];
    double tmpAN[kFillNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][2]; // [an, anErr]
    memset(estimatedWieght, 0, sizeof(estimatedWieght));
    memset(tmpAN, 0, sizeof(tmpAN));

    for(int fill = 0; fill < kFillNum; fill++){
        double relaLumi = relativeluminosity(fill);
        double beamPol = beamPolarization(fill);
        int runIdx = getFillToRunTypeIdx(fill);

        for(int type=0; type < kPi0TypeNum; type++){
            for(int xf=0; xf<kFinalBinXf; xf++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    double dilution = mDilutionFactor[runIdx][type][xf][pt];
                    if(dilution <= 0.01){continue;}

                    // signal + background asymmetry
                    double rightPolNum = polNum[fill][type][xf][pt][0];
                    double leftPolNum = polNum[fill][type][xf][pt][1];
                    if(rightPolNum+leftPolNum <= 0.5){continue;}

                    double anAll = -1./(dilution * beamPol) * (leftPolNum - relaLumi * rightPolNum) / ((leftPolNum + relaLumi * rightPolNum));
                    double anAllErr = 1./TMath::Sqrt(rightPolNum + leftPolNum);

                    double an = 0.;
                    double anErr = 0.;
                    double wieght = 0.;

                    if(mNotCalBkg == false){
                        // background asymmetry
                        double rightBkgPolNum = bkgPolNum[fill][type][xf][pt][0];
                        double leftBkgPolNum = bkgPolNum[fill][type][xf][pt][1];

                        double anBkg = -1./(dilution * beamPol) * (leftBkgPolNum - relaLumi * rightBkgPolNum) / ((leftBkgPolNum + relaLumi * rightBkgPolNum));
                        double anBkgErr = 1./TMath::Sqrt(rightBkgPolNum + leftBkgPolNum);

                        double allSignalRatio = mMassFitIntegral[runIdx][type][xf][pt][0] / mMassFitIntegral[runIdx][type][xf][pt][1]; // allNum / signalNum
                        double bkgSignalRatio = mMassFitIntegral[runIdx][type][xf][pt][2] / mMassFitIntegral[runIdx][type][xf][pt][1]; // bkgNum / signalNum
                    
                        // signal asymmetry
                        if(rightBkgPolNum+leftBkgPolNum <= 0.5){
                            an = anAll;
                            anErr = anAllErr;
                            wieght = rightPolNum + leftPolNum;
                        }
                        if(rightBkgPolNum+leftBkgPolNum >= 1.){
                            an = allSignalRatio * anAll - bkgSignalRatio * anBkg;
                            anErr = TMath::Sqrt(pow(allSignalRatio, 2) * pow(anAllErr, 2) + pow(bkgSignalRatio, 2) * pow(anBkgErr,2));
                            wieght= (rightPolNum + leftPolNum)/allSignalRatio;
                        }
                    }
                    if(mNotCalBkg == true){
                        an = anAll;
                        anErr = anAllErr;
                        wieght = rightPolNum + leftPolNum;
                    }

                    tmpAN[fill][type][xf][pt][0] = an;
                    tmpAN[fill][type][xf][pt][1] = anErr;
                    estimatedWieght[fill][type][xf][pt] = wieght;
                }
            }
        }
    }

    double AN[kRunTypeNum][kPi0TypeNum][kFinalBinXf][kFinalBinPt][3]; // [an, anErr, w]
    memset(AN, 0, sizeof(AN));

    double runTypeAn[kRunTypeNum][kPi0TypeNum][kGeneralBinXf][kGeneralBinPt][6]; // [xf mean, pt mean, an , anErr, w, num]
    memset(runTypeAn, 0, sizeof(runTypeAn));

    int pi0Num[kRunTypeNum][kPi0TypeNum][kGeneralBinXf][kGeneralBinPt];
    memset(pi0Num, 0, sizeof(pi0Num));
    
    // for summation of weighted AN and uncertainty into asymmetry graph
    for(int run = 0; run < kRunTypeNum; run++){
        for(int type=0; type < kPi0TypeNum; type++){
            for(int xf=0; xf<kFinalBinXf; xf++){
                for(int pt=0; pt<kFinalBinPt; pt++){
                    double dilution = mDilutionFactor[run][type][xf][pt];
                    double xfMean = mBinMean[run][type][xf][pt][0][0]/mBinMean[run][type][xf][pt][0][1];
                    double ptMean = mBinMean[run][type][xf][pt][1][0]/mBinMean[run][type][xf][pt][1][1]; 
                    if(dilution <= 0.01 || xfMean <= 1.e-6 || ptMean <= 1.e-6){continue;} 

                    double an, anErr, w;
                    int num;

                    if(run == 0){ // TL
                        an = ((tmpAN[0][type][xf][pt][0] * estimatedWieght[0][type][xf][pt]) + (tmpAN[1][type][xf][pt][0] * estimatedWieght[1][type][xf][pt])) / (estimatedWieght[0][type][xf][pt] + estimatedWieght[1][type][xf][pt]);
                        anErr = ((tmpAN[0][type][xf][pt][1] * estimatedWieght[0][type][xf][pt]) + (tmpAN[1][type][xf][pt][1] * estimatedWieght[1][type][xf][pt])) / (estimatedWieght[0][type][xf][pt] + estimatedWieght[1][type][xf][pt]);
                        w = estimatedWieght[0][type][xf][pt] + estimatedWieght[1][type][xf][pt];
                        num = polNum[0][type][xf][pt][0] + polNum[0][type][xf][pt][1] + polNum[1][type][xf][pt][0] + polNum[1][type][xf][pt][1];
                    }
                    if(run == 1){ // TS
                        an = ((tmpAN[2][type][xf][pt][0] * estimatedWieght[2][type][xf][pt]) + (tmpAN[4][type][xf][pt][0] * estimatedWieght[4][type][xf][pt])) / (estimatedWieght[2][type][xf][pt] + estimatedWieght[4][type][xf][pt]);
                        anErr = ((tmpAN[2][type][xf][pt][1] * estimatedWieght[2][type][xf][pt]) + (tmpAN[4][type][xf][pt][1] * estimatedWieght[4][type][xf][pt])) / (estimatedWieght[2][type][xf][pt] + estimatedWieght[4][type][xf][pt]);
                        w = estimatedWieght[2][type][xf][pt] + estimatedWieght[4][type][xf][pt];
                        num = polNum[2][type][xf][pt][0] + polNum[2][type][xf][pt][1] + polNum[4][type][xf][pt][0] + polNum[4][type][xf][pt][1];
                    }
                    if(run == 3){ // TOP
                        an = tmpAN[3][type][xf][pt][0];
                        anErr = tmpAN[3][type][xf][pt][1];
                        w = estimatedWieght[3][type][xf][pt];
                        num = polNum[3][type][xf][pt][0] + polNum[3][type][xf][pt][1];
                    }
                    
                    gAsymByXf[run][type][pt] -> SetPoint(xf, xfMean, an);
                    gAsymByXf[run][type][pt] -> SetPointError(xf, 0., anErr);

                    gAsymByPt[run][type][xf] -> SetPoint(pt, ptMean, an);
                    gAsymByPt[run][type][xf] -> SetPointError(pt, 0., anErr);

                    AN[run][type][xf][pt][0] = an;
                    AN[run][type][xf][pt][1] = anErr;
                    AN[run][type][xf][pt][2] = w;

                    pi0Num[run][type][xf][pt] = num;
                }
            }
        }

        for(int type=0; type<kPi0TypeNum; type++){
            for(int pt=0; pt<kGeneralBinPt; pt++){
                for(int xf=0; xf<kGeneralBinXf; xf++){
                    double xfPoint = 0.;
                    double ptPoint = 0.;
                    double GeneralWieght = 0.;
                    double GeneralAN = 0.;
                    double GeneralAnErr = 0.;
                    double GeneralPi0Num = 0.;

                    for(int i=0; i<kFinalBinXf; i++){
                        for(int j=0; j<kFinalBinPt; j++){

                            double xfMean = mBinMean[run][type][i][j][0][0]/mBinMean[run][type][i][j][0][1];
                            double ptMean = mBinMean[run][type][i][j][1][0]/mBinMean[run][type][i][j][1][1]; 

                            double an = AN[run][type][i][j][0];
                            double anErr = AN[run][type][i][j][1];
                            double weight = AN[run][type][i][j][2];

                            int num = pi0Num[run][type][i][j];
                            
                            if(weight < 10.){continue;}
                            if(mGenRangePT[pt] <= ptMean && ptMean < mGenRangePT[pt+1]   &&   mGenRangeXF[xf] <= xfMean && xfMean < mGenRangeXF[xf+1]){
                                xfPoint += (xfMean * weight);
                                ptPoint += (ptMean * weight);
                                GeneralAN += (an * weight);
                                GeneralAnErr += (anErr * weight);
                                GeneralWieght += weight;
                                GeneralPi0Num += num;
                            }
                        }
                    }

                    xfPoint = xfPoint/GeneralWieght;     
                    ptPoint = ptPoint/GeneralWieght;     
                    GeneralAN = GeneralAN/GeneralWieght;
                    GeneralAnErr = GeneralAnErr/GeneralWieght;

                    runTypeAn[run][type][xf][pt][0] = xfPoint;
                    runTypeAn[run][type][xf][pt][1] = ptPoint;
                    runTypeAn[run][type][xf][pt][2] = GeneralAN;
                    runTypeAn[run][type][xf][pt][3] = GeneralAnErr;
                    runTypeAn[run][type][xf][pt][4] = GeneralWieght;
                    runTypeAn[run][type][xf][pt][5] = GeneralPi0Num;

                    if(GeneralWieght > 10.){
                        int idxXf = gTypeAsymByXf[run][type][pt]->GetN();
                        gTypeAsymByXf[run][type][pt] -> SetPoint(idxXf, xfPoint, GeneralAN);
                        gTypeAsymByXf[run][type][pt] -> SetPointError(idxXf, 0., GeneralAnErr);

                        int idxPt = gTypeAsymByPt[run][type][xf] -> GetN();
                        gTypeAsymByPt[run][type][xf] -> SetPoint(idxPt, ptPoint, GeneralAN);
                        gTypeAsymByPt[run][type][xf] -> SetPointError(idxPt, 0., GeneralAnErr);
                    }
                }
            }
        }
    }   

    for(int pt=0; pt<kGeneralBinPt; pt++){
        for(int xf=0; xf<kGeneralBinXf; xf++){
            double xfPoint = 0.;
            double ptPoint = 0.;
            double GeneralWieght = 0.;
            double GeneralAN = 0.;
            double GeneralAnErr = 0.;
            double GeneralPi0Num = 0.;

            // for final asymmetry graph
            for(int run=0; run<kRunTypeNum; run++){
                for(int type=0; type<kPi0TypeNum; type++){
                    if(runTypeAn[run][type][xf][pt][4] < 10.){continue;}
                    xfPoint += (runTypeAn[run][type][xf][pt][0] * runTypeAn[run][type][xf][pt][4]);
                    ptPoint += (runTypeAn[run][type][xf][pt][1] * runTypeAn[run][type][xf][pt][4]);
                    GeneralAN += (runTypeAn[run][type][xf][pt][2] * runTypeAn[run][type][xf][pt][4]);
                    GeneralAnErr += (runTypeAn[run][type][xf][pt][3] * runTypeAn[run][type][xf][pt][4]);
                    GeneralWieght += runTypeAn[run][type][xf][pt][4];
                    GeneralPi0Num += runTypeAn[run][type][xf][pt][5];
                }
            }

            xfPoint = xfPoint/GeneralWieght;     
            ptPoint = ptPoint/GeneralWieght;     
            GeneralAN = GeneralAN/GeneralWieght;
            GeneralAnErr = GeneralAnErr/GeneralWieght;

            if(GeneralWieght > 10.){
                int idxXf = gGeneralAsymByXf[pt]->GetN();
                gGeneralAsymByXf[pt] -> SetPoint(idxXf, xfPoint, GeneralAN);
                gGeneralAsymByXf[pt] -> SetPointError(idxXf, 0., GeneralAnErr);

                int idxPt = gGeneralAsymByPt[xf] -> GetN();
                gGeneralAsymByPt[xf] -> SetPoint(idxPt, ptPoint, GeneralAN);
                gGeneralAsymByPt[xf] -> SetPointError(idxPt, 0., GeneralAnErr);
            }
        }
    }

    for(int pt=0; pt<kGeneralBinPt; pt++){
        double ptPoint = 0.;
        double GeneralWieght = 0.;
        double GeneralAN = 0.;
        double GeneralAnErr = 0.;
        double GeneralPi0Num = 0.;
        for(int xf=0; xf<kGeneralBinXf; xf++){
            for(int run=0; run<kRunTypeNum; run++){
                for(int type=0; type<kPi0TypeNum; type++){
                    if(runTypeAn[run][type][xf][pt][4] < 10.){continue;}
                    ptPoint += (runTypeAn[run][type][xf][pt][1] * runTypeAn[run][type][xf][pt][4]);
                    GeneralAN += (runTypeAn[run][type][xf][pt][2] * runTypeAn[run][type][xf][pt][4]);
                    GeneralAnErr += (runTypeAn[run][type][xf][pt][3] * runTypeAn[run][type][xf][pt][4]);
                    GeneralWieght += runTypeAn[run][type][xf][pt][4];
                    GeneralPi0Num += runTypeAn[run][type][xf][pt][5];
                }
            }
        }  
        ptPoint = ptPoint/GeneralWieght;     
        GeneralAN = GeneralAN/GeneralWieght;
        GeneralAnErr = GeneralAnErr/GeneralWieght;

        if(GeneralWieght > 10.){
            int idx = gGeneralAsymPt -> GetN();
            gGeneralAsymPt -> SetPoint(idx, ptPoint, GeneralAN);
            gGeneralAsymPt -> SetPointError(idx, 0., GeneralAnErr);
            
            // test number of pi0 in general binnings
            cout << " ptPoint: " << ptPoint << " num: " << GeneralPi0Num << " an: " << GeneralAN << " anErr: " << GeneralAnErr << endl;
        }
    }

    const double bin = 0.2;

    double sumPoint[2]; 
    double sumWieght[2];
    double sumAN[2];
    double sumAnErr[2];

    memset(sumPoint, 0, sizeof(sumPoint));
    memset(sumWieght, 0, sizeof(sumWieght));
    memset(sumAN, 0, sizeof(sumAN));
    memset(sumAnErr, 0, sizeof(sumAnErr));

    for(int pt=0; pt<kGeneralBinPt; pt++){
        double ptPoint = 0.;
        double GeneralWieght = 0.;
        double GeneralAN = 0.;
        double GeneralAnErr = 0.;
        for(int xf=0; xf<kGeneralBinXf; xf++){
            for(int run=0; run<kRunTypeNum; run++){
                for(int type=0; type<kPi0TypeNum; type++){
                    if(runTypeAn[run][type][xf][pt][4] < 10.){continue;}
                    ptPoint += (runTypeAn[run][type][xf][pt][1] * runTypeAn[run][type][xf][pt][4]);
                    GeneralAN += (runTypeAn[run][type][xf][pt][2] * runTypeAn[run][type][xf][pt][4]);
                    GeneralAnErr += (runTypeAn[run][type][xf][pt][3] * runTypeAn[run][type][xf][pt][4]);
                    GeneralWieght += runTypeAn[run][type][xf][pt][4];
                }
            }
        }  

        if(GeneralWieght < 10.){continue;}

        // test 
        // cout << ptPoint << " " << GeneralAN << " " << GeneralAnErr << " " << GeneralWieght << endl;

        double tmpPoint = ptPoint/GeneralWieght;
        if(tmpPoint < bin){
            sumPoint[0] += ptPoint;     
            sumAN[0] += GeneralAN;
            sumAnErr[0] += GeneralAnErr;
            sumWieght[0] += GeneralWieght;
        }
        if(tmpPoint >= bin){
            sumPoint[1] += ptPoint;     
            sumAN[1] += GeneralAN;
            sumAnErr[1] += GeneralAnErr;
            sumWieght[1] += GeneralWieght;
        }
    }  

    if(sumWieght[0] > 10.){
        sumPoint[0] = sumPoint[0]/sumWieght[0];     
        sumAN[0] = sumAN[0]/sumWieght[0];
        sumAnErr[0] = sumAnErr[0]/sumWieght[0];
        gTmpAsymPt -> SetPoint(0, sumPoint[0], sumAN[0]);
        gTmpAsymPt -> SetPointError(0, 0., sumAnErr[0]);
    }

    if(sumWieght[1] > 10.){
        sumPoint[1] = sumPoint[1]/sumWieght[1];     
        sumAN[1] = sumAN[1]/sumWieght[1];
        sumAnErr[1] = sumAnErr[1]/sumWieght[1];
        gTmpAsymPt -> SetPoint(1, sumPoint[1], sumAN[1]);
        gTmpAsymPt -> SetPointError(1, 0., sumAnErr[1]);
    }

    cout << "Pi0Asymmetry::asymmetry() --- done !!!" << endl;
}

void Pi0Asymmetry::drawFigure()
{
    cout << "Pi0Asymmetry::drawFigure() --- drawing ... "  << endl;
    
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
                allMassLatex -> Draw("same");
            }

            cMassAll -> Draw();
            cMassAll -> SaveAs(Form("%s/allPi0Mass_%s.pdf", mSaveFigPath.Data(), mRunName[run].Data()));
        }
    }
    
    if(mDoBinning){
        TCanvas* cXfBinning = new TCanvas("XFbinning","XFbinning", 1400, 600);
        TCanvas* cPtBinning = new TCanvas("Ptbinning","Ptbinning", 1400, 600);

        const int canvasSize = kBinningNum/4;
        TCanvas* cPtInXf = new TCanvas("PtinXfBinning", "PtinXfBinning", 600*4, 600*canvasSize);
        TCanvas* cXfInPt = new TCanvas("XfInPtBinning", "XfInPtBinning", 600*4, 600*canvasSize);
        TCanvas* cKinematics = new TCanvas("cKinematics", "cKinematics", 1300, 600);
        for(int run=0; run<kRunTypeNum; run++){
            cXfBinning -> Clear();
            cXfBinning -> Divide(2,1);

            if(hXf[run][0]->GetEntries() < 1){continue;}

            for(int type=0; type<kPi0TypeNum; type++){
                const int cBinIdx = type+1;
                cXfBinning -> cd(cBinIdx);
                gPad -> SetGrid(0,0);
                hXf[run][type] -> SetTitle(Form("type%i #pi^{0} x_{F} w/ binning; x_{F}; Stat./p_{T}", type+1));
                hXf[run][type] -> GetYaxis()->SetRangeUser(0., hXf[run][type]->GetBinContent(hXf[run][type]->GetMaximumBin()) + hXf[run][type]->GetBinContent(hXf[run][type]->GetMaximumBin())/4.);
                hXf[run][type] -> Draw();
            }
            cXfBinning -> Draw();
            cXfBinning -> SaveAs(Form("%s/binning_%s_Xf.pdf", mSaveFigPath.Data(), mRunName[run].Data()));


            cPtBinning -> Clear();
            cPtBinning -> Divide(2,1);
            for(int type=0; type<kPi0TypeNum; type++){
                const int cBinIdx = type+1;
                cPtBinning -> cd(cBinIdx);
                gPad -> SetGrid(0,0);
                hPt[run][type] -> SetTitle(Form("type%i #pi^{0} p_{T} w/ binning; P_{T}; Stat./x_{F}", type+1));
                hPt[run][type] -> GetYaxis()->SetRangeUser(0., hPt[run][type]->GetBinContent(hPt[run][type]->GetMaximumBin()) + hPt[run][type]->GetBinContent(hPt[run][type]->GetMaximumBin())/4.);
                hPt[run][type] -> Draw();
            }
            cPtBinning -> Draw();
            cPtBinning -> SaveAs(Form("%s/binning_%s_Pt.pdf", mSaveFigPath.Data(), mRunName[run].Data()));

            for(int type=0; type<kPi0TypeNum; type++){
                cPtInXf -> Clear();
                cPtInXf -> Divide(4,canvasSize);

                for(int i=0; i<kBinningNum; i++){
                    const int cBinIdx = i+1;
                    cPtInXf -> cd(cBinIdx);

                    hPtInXfBin[run][type][i] -> SetTitle( Form("%s pi0 p_{T} in %.2f<x_{F}<%.2f; p_{T} [GeV/c];",mRunName[run].Data(), mInitBinRange[i], mInitBinRange[i+1]));
                    hPtInXfBin[run][type][i] -> Draw();
                }
                cPtInXf -> Draw();
                cPtInXf -> SaveAs(Form("%s/binning_PtInXf_%s_type%i.pdf", mSaveFigPath.Data(), mRunName[run].Data(), type+1));

                cXfInPt -> Clear();
                cXfInPt -> Divide(4,canvasSize);

                for(int i=0; i<kBinningNum; i++){
                    const int cBinIdx = i+1;
                    cXfInPt -> cd(cBinIdx);

                    hXfInPtBin[run][type][i] -> SetTitle( Form("%s pi0 x_{F} in %.2f<p_{T}<%.2f; x_{F} [GeV/c];",mRunName[run].Data(), mInitBinRange[i], mInitBinRange[i+1]));
                    hXfInPtBin[run][type][i] -> Draw();
                }
                cXfInPt -> Draw();
                cXfInPt -> SaveAs(Form("%s/binning_XfInPt_%s_type%i.pdf", mSaveFigPath.Data(), mRunName[run].Data(), type+1));
            }

            cKinematics -> Clear();
            cKinematics ->  Divide(2,1);
            TLatex* kinematicLatex = new TLatex();
            TLine* kinematicBoundary = new TLine();

            for(int type=0; type<kPi0TypeNum; type++){
                kinematicBoundary -> Clear();
                kinematicBoundary -> SetLineWidth(1.3);
                kinematicBoundary -> SetLineStyle(2);
                const int cIdx = type+1;
                cKinematics->cd(cIdx);
                gPad -> SetGrid(0,0);
                hpt_xf[run][type] -> Draw("colz");
                kinematicLatex -> Clear();
                kinematicLatex -> SetTextSize(0.05);
                kinematicLatex -> DrawLatexNDC(0.13, 0.85, Form("Type-%i #pi^{0}, Run = %s", type+1, mRunName[run].Data()));
                kinematicLatex -> Draw("same");

                for(int xf=0; xf<kFinalBinXf; xf++){
                    kinematicBoundary -> DrawLine(mXfCutRange[run][type][xf], 0., mXfCutRange[run][type][xf], 1.);
                }
                for(int pt=0; pt<kFinalBinPt; pt++){
                    kinematicBoundary -> DrawLine(0., mPtCutRange[run][type][pt], 1., mPtCutRange[run][type][pt]);
                }

                kinematicBoundary -> Draw("same");
            }

            cKinematics -> Draw();
            cKinematics -> SaveAs(Form("%s/kinematics_%s.pdf", mSaveFigPath.Data(), mRunName[run].Data()));
        }
    }

    if(mDoBkgEstimation){
        TCanvas* cMass = new TCanvas("cMass", "cMass", kFinalBinXf*750, kFinalBinPt*750);
        TLatex* massLatex = new TLatex();
        TLegend* massLeg = new TLegend(0.6,0.7, 0.9, 0.9);

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                int entries = 0;
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        entries += hMass[run][type][xf][pt]->GetEntries();
                    }
                }
                if(entries < 10){continue;}

                cMass -> Clear();
                cMass -> Divide(kFinalBinXf, kFinalBinPt);

                int tmpIdx = 0;
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        tmpIdx++;
                        const int c1Idx = tmpIdx;
                        cMass -> cd(c1Idx);
                        gPad -> SetGrid(0,0);

                        int maxBin = hMass[run][type][xf][pt] -> GetMaximumBin();
                        double maxBinContent = hMass[run][type][xf][pt] -> GetBinContent(maxBin);
                        hMass[run][type][xf][pt] -> GetYaxis() -> SetRangeUser(0., maxBinContent+maxBinContent/10.);
                        hMass[run][type][xf][pt] -> Draw();
                        
                        massLeg -> Clear();
                        massLeg -> AddEntry(fMassFit, "All fit","lp");
                        massLeg -> AddEntry(fMassSignalFit, "Signal fit","lp");
                        massLeg -> AddEntry(fMassBkgFit, "Bkg fit","lp");
                        massLeg -> Draw("same");

                        massLatex -> Clear();
                        massLatex -> SetTextSize(0.05);
                        massLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                        massLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRange[run][type][pt], mPtCutRange[run][type][pt+1]));
                        massLatex -> DrawLatexNDC(0.57, 0.6, Form("%.2f < x_{F} < %.2f", mXfCutRange[run][type][xf], mXfCutRange[run][type][xf+1]));

                        if(mMassCutRange[run][type][xf][pt][0] > 10.){
                            massLatex -> DrawLatexNDC(0.57, 0.5, Form("M_{#pi^{0}} = %.2f", mMassCutRange[run][type][xf][pt][0]));
                            massLatex -> DrawLatexNDC(0.57, 0.45, Form("#sigma_{#pi^{0}} = %.2f", mMassCutRange[run][type][xf][pt][1]));
                            massLatex -> DrawLatexNDC(0.52, 0.3, Form("Bkg ratio = %.3f", mMassFitIntegral[run][type][xf][pt][2]/mMassFitIntegral[run][type][xf][pt][0]));
                        }
                        massLatex -> Draw("same");
                    }
                }
                cMass -> Draw();
                cMass -> SaveAs(Form("%s/Mass_%s_pi0Type%i.pdf", mSaveFigPath.Data(), mRunName[run].Data(), type+1));
            }
        }
    }

    if(mDoFindBinMean){
        TCanvas* cMeanBin = new TCanvas("cMeanBin", "cMeanBin", kFinalBinXf*750, kFinalBinPt*750);
        TLatex* meanLatex = new TLatex();
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int xfOrPt = 0; xfOrPt<2; xfOrPt++){
                    cMeanBin -> Clear();
                    cMeanBin -> Divide(kFinalBinXf, kFinalBinPt);

                    int entries = 0;
                    for(int xf=0; xf<kFinalBinXf; xf++){
                        for(int pt=0; pt<kFinalBinPt; pt++){
                            entries += hBinMean[run][type][xf][pt][xfOrPt] -> GetEntries();
                        }
                    }
                    if(entries < 10){continue;}

                    int tmpIdx = 0;
                    for(int xf=0; xf<kFinalBinXf; xf++){
                        for(int pt=0; pt<kFinalBinPt; pt++){
                            tmpIdx++;
                            const int c1Idx = tmpIdx;
                            cMeanBin -> cd(c1Idx);
                            gPad -> SetGrid(0,0);

                            hBinMean[run][type][xf][pt][xfOrPt] -> Draw();

                            meanLatex -> Clear();
                            meanLatex -> SetTextSize(0.05);
                            meanLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                            meanLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRange[run][type][pt], mPtCutRange[run][type][pt+1]));
                            meanLatex -> DrawLatexNDC(0.57, 0.6, Form("%.2f < x_{F} < %.2f", mXfCutRange[run][type][xf], mXfCutRange[run][type][xf+1]));

                            meanLatex -> SetTextSize(0.06);
                            meanLatex -> DrawLatexNDC(0.55, 0.45, Form("mean = %.3f", mBinMean[run][type][xf][pt][xfOrPt][0]/mBinMean[run][type][xf][pt][xfOrPt][1]));
                        }
                    }
                    cMeanBin -> Draw();
                    TString text = (xfOrPt == 0)? "Xf" : "Pt";
                    cMeanBin -> SaveAs(Form("%s/MeanEachBin%s_%s_pi0Type%i.pdf", mSaveFigPath.Data(), text.Data(), mRunName[run].Data(), type+1));
                }
            }
        }
    }

    if(mDoDilution){
        TCanvas* cDilution = new TCanvas("cDilution", "cDilution", kFinalBinXf*750, kFinalBinPt*750);
        TLatex* dilutionLatex = new TLatex();
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                cDilution -> Clear();
                cDilution -> Divide(kFinalBinXf, kFinalBinPt);

                int entries = 0;
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        entries += hPhi[run][type][xf][pt] -> GetEntries();
                    }
                }
                if(entries < 10){continue;}

                int tmpIdx = 0;
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        tmpIdx++;
                        const int c1Idx = tmpIdx;
                        cDilution -> cd(c1Idx);

                        gPad -> SetGrid(0,0);
                        hPhi[run][type][xf][pt] -> GetXaxis() -> SetRangeUser(0., 200.);
                        hPhi[run][type][xf][pt] -> Draw();

                        dilutionLatex -> Clear();
                        dilutionLatex -> SetTextSize(0.06);
                        dilutionLatex -> DrawLatexNDC(0.6, 0.8, Form("D_{#phi} = %.3f", mDilutionFactor[run][type][xf][pt]));
                        dilutionLatex -> Draw("same");

                        dilutionLatex -> Clear();
                        dilutionLatex -> SetTextSize(0.05);
                        dilutionLatex -> DrawLatexNDC(0.15, 0.8, Form("Run = %s", mRunName[run].Data()));
                        dilutionLatex -> DrawLatexNDC(0.57, 0.65, Form("%.2f < p_{T} < %.2f", mPtCutRange[run][type][pt], mPtCutRange[run][type][pt+1]));
                        dilutionLatex -> DrawLatexNDC(0.57, 0.6, Form("%.2f < x_{F} < %.2f", mXfCutRange[run][type][xf], mXfCutRange[run][type][xf+1]));
                        dilutionLatex -> Draw("same");
                    }
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

        TCanvas* cAsymByPt = new TCanvas("cAsymByPt", "cAsymByPt", 1300, 1200);
        TLegend* rangeLegBy = new TLegend(0.65, 0.13, 0.87, 0.38);

        cAsymByPt -> Divide(2, 2);
        for(int xf=0; xf<kGeneralBinXf; xf++){
            const int cIdx = xf+1;
            cAsymByPt -> cd(cIdx);
            tmpGraph[0] -> GetYaxis() -> SetRangeUser(-0.3, 0.3);
            tmpGraph[0] -> SetTitle("; p_{T} [GeV/c]; A_{N}");
            tmpGraph[0] -> Draw("ap");

            rangeLegBy -> Clear();
            // rangeLegBy -> SetBorderSize(0);
            rangeLegBy -> SetTextSize(0.03);

            for(int run=0; run<kRunTypeNum; run++){
                for(int type=0; type<2; type++){
                    gTypeAsymByPt[run][type][xf] -> SetMarkerSize(1.2);
                    gTypeAsymByPt[run][type][xf] -> SetMarkerStyle(MarkerStyle[type]);
                    gTypeAsymByPt[run][type][xf] -> SetMarkerColor(rangeColor2[run]);
                    gTypeAsymByPt[run][type][xf] -> SetLineColor(rangeColor2[run]);
                    gTypeAsymByPt[run][type][xf] -> Draw("same, p");
                    rangeLegBy -> AddEntry(gTypeAsymByPt[run][type][xf], Form("Type%i (%s)", type+1, mRunName[run].Data()), "p");
                }
            }
            rangeLegBy -> Draw("same");

            anLatex -> Clear();
            anLatex -> SetTextSize(0.05);
            anLatex -> DrawLatexNDC(0.15, 0.83, Form("%.2f < x_{F} < %.2f", mGenRangeXF[xf], mGenRangeXF[xf+1]));
            anLatex -> Draw("same");
            dashLine -> Draw("same");
        }
        cAsymByPt -> Draw();
        cAsymByPt -> SaveAs(Form("%s/asymPi0_byPt.pdf", mSaveFigPath.Data()));


        TCanvas* cAsymByXf = new TCanvas("cAsymByXf", "cAsymByXf", 1300, 1800);
        cAsymByXf -> Divide(2, 3);
        for(int pt=0; pt<kGeneralBinPt; pt++){
            const int cIdx = pt+1;
            cAsymByXf -> cd(cIdx);
            tmpGraph[1] -> GetYaxis() -> SetRangeUser(-0.3, 0.3);
            tmpGraph[1] -> SetTitle("; x_{F}; A_{N}");
            tmpGraph[1] -> Draw("ap");

            rangeLegBy -> Clear();
            // rangeLegBy -> SetBorderSize(0);
            rangeLegBy -> SetTextSize(0.03);

            for(int run=0; run<kRunTypeNum; run++){
                for(int type=0; type<2; type++){
                    gTypeAsymByXf[run][type][pt] -> SetMarkerSize(1.2);
                    gTypeAsymByXf[run][type][pt] -> SetMarkerStyle(MarkerStyle[type]);
                    gTypeAsymByXf[run][type][pt] -> SetMarkerColor(rangeColor2[run]);
                    gTypeAsymByXf[run][type][pt] -> SetLineColor(rangeColor2[run]);
                    gTypeAsymByXf[run][type][pt] -> Draw("same, p");
                    rangeLegBy -> AddEntry(gTypeAsymByXf[run][type][pt], Form("Type%i (%s)", type+1, mRunName[run].Data()), "p");
                }
            }
            rangeLegBy -> Draw("same");

            anLatex -> Clear();
            anLatex -> SetTextSize(0.05);
            anLatex -> DrawLatexNDC(0.15, 0.83, Form("%.2f < p_{T} < %.2f", mGenRangePT[pt], mGenRangePT[pt+1]));
            anLatex -> Draw("same");
            dashLine -> Draw("same");
        }
        cAsymByXf -> Draw();
        cAsymByXf -> SaveAs(Form("%s/asymPi0_byXf.pdf", mSaveFigPath.Data()));        

        TLegend* legAsymPt = new TLegend(0.13, 0.65, 0.5, 0.87);
        TLegend* legAsymXf = new TLegend(0.13, 0.65, 0.5, 0.87);
        TCanvas* cAsym = new TCanvas("cAsym", "cAsym", 1300, 600);
        cAsym -> Divide(2,1);
        cAsym -> cd(1);
        gPad -> SetGrid(0,0);
        tmpGraph[0] -> GetYaxis() -> SetRangeUser(-0.1, 0.3);
        tmpGraph[0] -> SetTitle("; x_{F}; A_{N}");
        tmpGraph[0] -> Draw("ap");
        for(int pt=0; pt<kGeneralBinPt; pt++){
            gGeneralAsymByXf[pt] -> SetMarkerSize(1.2);
            gGeneralAsymByXf[pt] -> SetMarkerStyle(MarkerStyle[0]);
            gGeneralAsymByXf[pt] -> SetMarkerColor(rangeColor[pt]);
            gGeneralAsymByXf[pt] -> SetLineColor(rangeColor[pt]);
            gGeneralAsymByXf[pt] -> Draw("same, p");
            legAsymPt -> AddEntry(gGeneralAsymByXf[pt], Form("%.2f < p_{T} < %.2f GeV/c", mGenRangePT[pt], mGenRangePT[pt+1]), "p");
        }
        legAsymPt -> SetBorderSize(0);
        legAsymPt -> SetTextSize(0.03);
        legAsymPt -> Draw("same");

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
        for(int xf=0; xf<kGeneralBinXf; xf++){
            gGeneralAsymByPt[xf] -> SetMarkerSize(1.2);
            gGeneralAsymByPt[xf] -> SetMarkerStyle(MarkerStyle[0]);
            gGeneralAsymByPt[xf] -> SetMarkerColor(rangeColor[xf]);
            gGeneralAsymByPt[xf] -> SetLineColor(rangeColor[xf]);
            gGeneralAsymByPt[xf] -> Draw("same, p");
            legAsymXf -> AddEntry(gGeneralAsymByPt[xf], Form("%.2f < x_{F} < %.2f", mGenRangeXF[xf], mGenRangeXF[xf+1]), "p");
        }
        legAsymXf -> SetBorderSize(0);
        legAsymXf -> SetTextSize(0.03);
        legAsymXf -> Draw("same");

        anLatex -> Clear();
        anLatex -> SetTextSize(0.04);
        anLatex -> DrawLatexNDC(0.72, 0.85, "Run = TS");
        anLatex -> Draw("same");
        dashLine -> Draw("same");

        cAsym -> Draw();
        cAsym -> SaveAs(Form("%s/asymmetry.pdf", mSaveFigPath.Data()));


        // test !!!
        // save graph into TFile for comparison asymmetry with other condition, ex) tpc track, fps photon or not
        TFile* fileAsym = new TFile(Form("%s/asymmetry_%s_%s.root", mSaveDatPath.Data(), mConditionName.Data(), mConditionName2.Data()), "recreate");
        fileAsym -> cd();
        gGeneralAsymPt -> Write();
        gTmpAsymPt -> Write();
        for(int pt=0; pt<kGeneralBinPt; pt++){
            gGeneralAsymByXf[pt] -> Write();
        }
        for(int xf=0; xf<kGeneralBinXf; xf++){
            gGeneralAsymByPt[xf] -> Write();
        }
        fileAsym -> Close();
        cout << Form("%s/asymmetry_%s_%s.root", mSaveDatPath.Data(), mConditionName.Data(), mConditionName2.Data()) <<" is saved!!! " << endl;


        // asymmetry as function of pt in all xf range
        TCanvas* cAsymPtAllXf = new TCanvas("cAsymPtAllXf", "cAsymPtAllXf", 600, 600);
        TLegend* legAsymPtAllXf = new TLegend(0.13, 0.65, 0.5, 0.87);
        gPad -> SetGrid(0,0);
        tmpGraph[1] -> GetYaxis() -> SetRangeUser(-0.1, 0.3);
        tmpGraph[1] -> SetTitle("; p_{T} [GeV/c]; A_{N}");
        tmpGraph[1] -> Draw("ap");

        gGeneralAsymPt -> SetMarkerSize(1.2);
        gGeneralAsymPt -> SetMarkerStyle(MarkerStyle[0]);
        gGeneralAsymPt -> SetMarkerColor(kBlack);
        gGeneralAsymPt -> SetLineColor(kBlack);
        gGeneralAsymPt -> Draw("same, p");
        legAsymPtAllXf -> AddEntry(gGeneralAsymByPt[xf], "0 < x_{F} < 1", "p");

        legAsymPtAllXf -> SetBorderSize(0);
        legAsymPtAllXf -> SetTextSize(0.03);
        legAsymPtAllXf -> Draw("same");

        anLatex -> Clear();
        anLatex -> SetTextSize(0.04);
        anLatex -> DrawLatexNDC(0.72, 0.85, "Run = TS");
        anLatex -> Draw("same");
        dashLine -> Draw("same");

        cAsymPtAllXf -> Draw();
        cAsymPtAllXf -> SaveAs(Form("%s/asymmetry%s.pdf", mSaveFigPath.Data(), mConditionName.Data()));


    }
}

int Pi0Asymmetry::readData()
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
            cout << "Pi0Asymmetry::readData() --- General Mass Cut data is OK" << endl;
        }
        else{
            cout << "Pi0Asymmetry::readData() --- Can't opend general mass fitting parameter data " << dataPath << endl;
            return 0;
        }
        generalMassFitParFile.close();
    }
    if(mDoBinning == false && mDoFindGenMassCut == false){
        ifstream binningXfFile;
        TString dataPath = mSaveDatPath+"/binning_" + mConditionName + ".dat";
        binningXfFile.open(dataPath.Data());
        if(binningXfFile.is_open()){
            while(!binningXfFile.eof()){
                int isXF;
                int run, type, index;
                double boundary;
                binningXfFile >> isXF >> run >> type >> index >> boundary;

                if(isXF == 1){mXfCutRange[run][type][index] = boundary;}
                if(isXF == 0){mPtCutRange[run][type][index] = boundary;}

                if(boundary >= 0.1){mOptionChecker[1] = true;}
            }
            cout << "Pi0Asymmetry::readData() --- Binning data is OK" << endl;
        }
        else{
            cout << "Pi0Asymmetry::readData() --- Can't opend binning data " << dataPath << endl;
            return 0;
        }
        binningXfFile.close();
    }
    if(mDoBkgEstimation == false && mDoBinning == false && mDoFindGenMassCut == false){

        ifstream massFitParFile;
        TString dataPath = mSaveDatPath+"/MassFitParEachBin_" + mConditionName + ".dat";
        massFitParFile.open(dataPath.Data());
        if(massFitParFile.is_open()){
            while(!massFitParFile.eof()){
                int run, type, xf, pt;
                double mean, sigma;
                double allInte, signalInte, bkgInte;
                massFitParFile >> run >> type >> xf >> pt >> mean >> sigma >> allInte >> signalInte >> bkgInte;
                mMassCutRange[run][type][xf][pt][0] = mean;
                mMassCutRange[run][type][xf][pt][1] = sigma;

                mMassFitIntegral[run][type][xf][pt][0] = allInte;
                mMassFitIntegral[run][type][xf][pt][1] = signalInte;
                mMassFitIntegral[run][type][xf][pt][2] = bkgInte;
            
                if(mean > 10.){mOptionChecker[2] = true;}
            }
            cout << "Pi0Asymmetry::readData() --- Mass fitting parameter data is OK" << endl;
        }
        else{
            cout << "Pi0Asymmetry::readData() --- Can't opend binning data " << dataPath << endl;
            return 0;
        }
        massFitParFile.close();
        
    }
    if(mDoFindBinMean == false && mDoBkgEstimation == false && mDoBinning == false && mDoFindGenMassCut == false){
        ifstream binMeanFile;
        TString dataPath = mSaveDatPath+"/MeanEachBin_" + mConditionName + ".dat";
        binMeanFile.open(dataPath.Data());
        if(binMeanFile.is_open()){
            while(!binMeanFile.eof()){
                int run, type, xf, pt;
                double meanXf, meanPt;
                int xfNum, ptNum;
                binMeanFile >> run >> type >> xf >> pt >> meanXf >> xfNum >> meanPt >> ptNum;
                mBinMean[run][type][xf][pt][0][0] = meanXf;
                mBinMean[run][type][xf][pt][0][1] = xfNum;
                mBinMean[run][type][xf][pt][1][0] = meanPt;
                mBinMean[run][type][xf][pt][1][1] = ptNum;

                if(xfNum > 1){mOptionChecker[3] = true;}
            }
            cout << "Pi0Asymmetry::readData() --- Mean each bins data is OK" << endl;
        }
        else{
            cout << "Pi0Asymmetry::readData() --- Can't opend binning data " << dataPath << endl;
            return 0;
        }
        binMeanFile.close();
    }
    if(mDoDilution == false && mDoFindBinMean == false && mDoBkgEstimation == false && mDoBinning == false && mDoFindGenMassCut == false){
        ifstream dilutionFactorFile;
        TString dataPath = mSaveDatPath+"/DilutionFactor_" + mConditionName + ".dat";
        dilutionFactorFile.open(dataPath.Data());
        if(dilutionFactorFile.is_open()){
            while(!dilutionFactorFile.eof()){
                int run, type, xf, pt;
                double factor;
                dilutionFactorFile >> run >> type >> xf >> pt >> factor;
                mDilutionFactor[run][type][xf][pt] = factor;

                if(factor > 0.1){mOptionChecker[4] = true;}
            }
            cout << "Pi0Asymmetry::readData() --- Dilution Factor data is OK" << endl;
        }
        else{
            cout << "Pi0Asymmetry::readData() --- Can't opend binning data " << dataPath << endl;
            return 0;
        }
        dilutionFactorFile.close();
    } 

    if(mDoFindGenMassCut == false && mOptionChecker[0] == false){
        cout << "Pi0Asymmetry::readData() --- General mass cut data is something wrong !! " << endl;
        return 0;
    }
    if(mDoBinning == false && mDoFindGenMassCut == false && mOptionChecker[1] == false){
        cout << "Pi0Asymmetry::readData() --- Binning data is something wrong !! " << endl;
        return 0;
    }
    if(mDoBkgEstimation == false && mDoBinning == false && mDoFindGenMassCut == false && mOptionChecker[2] == false){
        cout << "Pi0Asymmetry::readData() ---  Mass fitting par. data is something wrong !! " << endl;
        return 0;
    }
    if(mDoFindBinMean == false && mDoBkgEstimation == false && mDoBinning == false && mDoFindGenMassCut == false && mOptionChecker[3] == false){
        cout << "Pi0Asymmetry::readData() ---  Mean each bins data is something wrong !! " << endl;
        return 0;
    }
    if(mDoDilution == false && mDoFindBinMean == false && mDoBkgEstimation == false && mDoBinning == false && mDoFindGenMassCut == false && mOptionChecker[4] == false){
        cout << "Pi0Asymmetry::readData() ---  Dilution Factor data is something wrong !! " << endl;
        return 0;
    }
    return 1;
}

void Pi0Asymmetry::saveData()
{
    cout << "Pi0Asymmetry::saveData() --- data saving ..." << endl;
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
    if(mDoBinning){
        ofstream binningFile;
        TString dataPath = mSaveDatPath+"/binning_" + mConditionName + ".dat";
        binningFile.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){

                for(int xfbin = 0; xfbin<kFinalBinXf+1; xfbin++){
                    binningFile << 1 << " " << run << " " << type << " " << xfbin << " "  << mXfCutRange[run][type][xfbin] << endl;
                }
                for(int ptbin = 0; ptbin<kFinalBinPt+1; ptbin++){
                    binningFile << 0 << " " << run << " " << type << " " << ptbin << " " << mPtCutRange[run][type][ptbin] << endl;
                }
            }
        }
        binningFile.close();
        cout << "Binning data is saved !" << endl;
    }
    if(mDoBkgEstimation){
        ofstream massFitParFile;
        TString dataPath = mSaveDatPath+"/MassFitParEachBin_" + mConditionName + ".dat";
        massFitParFile.open(dataPath.Data());
        
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        massFitParFile << run << " " << type << " " << xf << " " << pt << " " << 
                        mMassCutRange[run][type][xf][pt][0] << " " << mMassCutRange[run][type][xf][pt][1] << " " <<  // signal fit mean and sigma 
                        mMassFitIntegral[run][type][xf][pt][0] << " " << mMassFitIntegral[run][type][xf][pt][1] << " " << mMassFitIntegral[run][type][xf][pt][2] << endl; // all, signal, bkg fit integral value
                    }
                }
            }
        }
        massFitParFile.close();
        cout << "Mass each bin fitting par data is saved !" << endl;
    }
    if(mDoFindBinMean){
        ofstream binMeanFile;
        TString dataPath = mSaveDatPath+"/MeanEachBin_" + mConditionName + ".dat";
        binMeanFile.open(dataPath.Data());

        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        binMeanFile << run << " " << type << " " << xf << " " << pt << " " << 
                        mBinMean[run][type][xf][pt][0][0] << " " << 
                        mBinMean[run][type][xf][pt][0][1] << " " << 
                        mBinMean[run][type][xf][pt][1][0] << " " << 
                        mBinMean[run][type][xf][pt][1][1] << " " << endl;
                    }
                }
            }
        }
        binMeanFile.close();
        cout << "mean value each bins data is saved !" << endl;
    }
    if(mDoDilution){
        ofstream dilutionFactorFile;
        TString dataPath = mSaveDatPath+"/DilutionFactor_" + mConditionName + ".dat";
        dilutionFactorFile.open(dataPath.Data());
        
        for(int run=0; run<kRunTypeNum; run++){
            for(int type=0; type<kPi0TypeNum; type++){
                for(int xf=0; xf<kFinalBinXf; xf++){
                    for(int pt=0; pt<kFinalBinPt; pt++){
                        dilutionFactorFile << run << " " << type << " " << xf << " " << pt << " " << mDilutionFactor[run][type][xf][pt] << endl;
                    }
                }
            }
        }
        dilutionFactorFile.close();
        cout << "Dilution Factor data is saved !" << endl;
    }
}

void Pi0Asymmetry::info()
{
    cout << "=== input data: " << mFilePath << endl;
    cout << "=== event end number: " << mEventNum << endl;
    cout << "=== condition version: " << mConditionName << endl;
    cout << "=== option On-Off === " << endl;

    TString optionOn = "";
    optionOn = (mDoFindGenMassCut)? "ON" : "OFF";
    cout << "    DoFindGenMassCut --- " << optionOn << endl;
    optionOn = (mDoBinning)? "ON" : "OFF";
    cout << "    DoBinning --- " << optionOn << endl;
    optionOn = (mDoBkgEstimation)? "ON" : "OFF";
    cout << "    DoBkgEstimation --- " << optionOn << endl;
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
}


void Pi0Asymmetry::massFitting(TH1D* histo)
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

void Pi0Asymmetry::getMassFitPar(double* par){return fMassFit -> GetParameters(par);}
double Pi0Asymmetry::gausFit(double* x, double* par){return par[2]*TMath::Gaus(x[0], par[0], par[1], kTRUE);}
double Pi0Asymmetry::polFit(double* x, double* par){return pow(x[0]-par[0],2)*pow(x[0]-par[1],2)*(par[2]*pow(x[0],3) + par[3]*pow(x[0],2) + par[4]*x[0] + par[5]) + par[6];} // correct one
double Pi0Asymmetry::polGausFit(double* x, double* par){return gausFit(x, par) + polFit(x, &par[3]);}


