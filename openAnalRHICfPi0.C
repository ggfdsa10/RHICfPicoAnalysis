#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphErrors.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <TString.h>

using namespace std;

void loadLibs()
{
	gSystem->Load("libTable");
	gSystem->Load("libPhysics");
	gSystem->Load("St_base");
	gSystem->Load("StChain");
	gSystem->Load("St_Tables");
	gSystem->Load("StUtilities");        // new addition 22jul99
	gSystem->Load("StTreeMaker");
	gSystem->Load("StIOMaker");
	gSystem->Load("StarClassLibrary");
	gSystem->Load("StTriggerDataMaker"); // new starting from April 2003
	gSystem->Load("StBichsel");
	gSystem->Load("StEvent");
	gSystem->Load("StEventUtilities");
	gSystem->Load("StDbLib");
	gSystem->Load("StEmcUtil");
	gSystem->Load("StTofUtil");
	gSystem->Load("StPmdUtil");
	gSystem->Load("StRHICfUtil");
    gSystem->Load("StStrangeMuDstMaker");
	gSystem->Load("StMuDSTMaker");
    gSystem->Load("StRHICfPi0Maker");

	gSystem->ListLibraries();
}

TString getFileID(int mode, TString inputFiles);

void openAnalRHICfPi0(const Char_t* inputFile = "")
{
    loadLibs();

    StRHICfPi0Maker* pi0maker = new StRHICfPi0Maker(0, inputFile);
	pi0maker -> Init();

    int eventNum = pi0maker -> getAnalEntries();
	cout << "total events: " << eventNum << endl;

	TString outFileName = "AnalRHICfPi0.root";
	if(pi0maker->getNFiles()==1){
		TString runNum = getFileID(0, inputFile);
		TString daqNum = getFileID(1, inputFile);
		outFileName = Form("AnalRHICfPi0_%s_%s.root", runNum.Data(), daqNum.Data());	
	}

	auto files = new TFile(Form("%s",outFileName.Data()),"recreate");
	auto treePi0 = new TTree("pi0","pi0");

	Int_t OutRunNumber;
	Int_t OutBunchNumber;
	Int_t OutFillNumber;
	Bool_t OutBlueSpinUp;

	Int_t OutTofMult;
	Int_t OutGRefMult;
	Int_t OutRefMult;

	// BBC
	Int_t OutBBCSEast[16][3]; // [pmt idx][adc, tdc, tac] 
    Int_t OutBBCSWest[16][3]; // [pmt idx][adc, tdc, tac] 
	Int_t OutBBCLEast[8][3]; // [pmt idx][adc, tdc, tac] 
    Int_t OutBBCLWest[8][3]; // [pmt idx][adc, tdc, tac] 

	Int_t OutBBCSSumEast;
	Int_t OutBBCSSumWest;
	Int_t OutBBCLSumEast;
	Int_t OutBBCLSumWest;

	// VPD
	Int_t OutVpdEast[16][2]; // [pmt idx][adc, tdc] 
    Int_t OutVpdWest[16][2]; // [pmt idx][adc, tdc] 
    Int_t OutVpdEastHighThr[16][2]; // Hight Threshold [pmt idx][adc, tdc] 
    Int_t OutVpdWestHighThr[16][2]; // Hight Threshold [pmt idx][adc, tdc] 
    Int_t OutVpdEarliestTDC[2]; // [East, West]
    Int_t OutVpdEarliestTDCHighthr[2]; // [East, West]
    Int_t OutVpdTimeDiff; // vpdTimeDifference
	Int_t OutVPDSumEast;
	Int_t OutVPDSumWest;

	// ZDC
	Float_t OutZDCADCSumEast;
	Float_t OutZDCADCSumWest;
	Float_t OutZDCADCEast[4];
	Float_t OutZDCADCWest[4];
	Float_t OutZDCVertexZ;

	// rhicf ============
	Int_t OutTriggerNumber;
	Bool_t OutIsShowerTrig;
	Bool_t OutIsPi0Trig;  
    Bool_t OutIsHighEMTrig;

	Float_t OutL90[2];

	Int_t OutPhotonNum;
	Int_t OutPID[4];
	Int_t OutPhotonTowerIdx[4];
	Double_t OutPhotonPos[4][2];
	Double_t OutPhotonE[4][2]; // photon, hadron
	Double_t OutTowerEnergy[4][2];

	Bool_t OutIsRHICfPi0;
	Int_t OutTowerIdx;
	Int_t OutType;
	Double_t OutX;
	Double_t OutY;
	Double_t OutE;
	Double_t OutPx;
	Double_t OutPy;
	Double_t OutPz;
	Double_t OutPt;
	Double_t OutXf;
	Double_t OutMass;

	// tracks ============
	Int_t OutTrackNum;
	Double_t OutTrackEta[100];
	Double_t OutTrackPhi[100];
	Double_t OutTrackPt[100];
	Int_t OutTrackPID[100];
	
	Double_t OutTrackDca[100];
	Double_t OutTrackPos[100][3];
	Double_t OutTrackMom[100][3];
	Double_t OutVertex[3];

	// fms ================
	Int_t OutFmsPhotonNum;
	Int_t OutFmsPhotonFlag[100];
	Double_t OutFmsPhotonPos[100][3];
	Double_t OutFmsPhotonMom[100][3];
	Double_t OutFmsPhotonE[100];

	// general data =======================
	treePi0 -> Branch("runNumber", &OutRunNumber, "OutRunNumber/I");
	treePi0 -> Branch("bunchNumber", &OutBunchNumber, "OutBunchNumber/I");
	treePi0 -> Branch("fillNumber", &OutFillNumber, "OutFillNumber/I");
	treePi0 -> Branch("blueSpinUp", &OutBlueSpinUp, "OutBlueSpinUp/O");

	treePi0 -> Branch("tofMult", &OutTofMult, "OutTofMult/I");
	treePi0 -> Branch("gloMult", &OutGRefMult, "OutGRefMult/I");
	treePi0 -> Branch("refMult", &OutRefMult, "OutRefMult/I");

	treePi0 -> Branch("bbcSEast", OutBBCSEast, "OutBBCSEast[16][3]/I");
	treePi0 -> Branch("bbcSWest", OutBBCSWest, "OutBBCSWest[16][3]/I");
	treePi0 -> Branch("bbcLEast", OutBBCLEast, "OutBBCLEast[8][3]/I");
	treePi0 -> Branch("bbcLWest", OutBBCLWest, "OutBBCLWest[8][3]/I");

	treePi0 -> Branch("bbcSSumEast", &OutBBCSSumEast, "OutBBCSSumEast/I");
	treePi0 -> Branch("bbcSSumWest", &OutBBCSSumWest, "OutBBCSSumWest/I");
	treePi0 -> Branch("bbcLSumEast", &OutBBCLSumEast, "OutBBCLSumEast/I");
	treePi0 -> Branch("bbcLSumWest", &OutBBCLSumWest, "OutBBCLSumWest/I");

	treePi0 -> Branch("vpdEast", OutVpdEast, "OutVpdEast[16][2]/I");
	treePi0 -> Branch("vpdWest", OutVpdWest, "OutVpdWest[16][2]/I");
	treePi0 -> Branch("vpdHighThrEast", OutVpdEastHighThr, "OutVpdEastHighThr[16][2]/I");
	treePi0 -> Branch("vpdHighThrWest", OutVpdWestHighThr, "OutVpdWestHighThr[16][2]/I");

	treePi0 -> Branch("vpdEarliestTDC", OutVpdEarliestTDC, "OutVpdEarliestTDC[2]/I");
	treePi0 -> Branch("vpdEarliestTDCHighThr", OutVpdEarliestTDCHighthr, "OutVpdEarliestTDCHighthr[2]/I");
	treePi0 -> Branch("vpdTimeDiff", &OutVpdTimeDiff, "OutVpdTimeDiff/I");
	
	treePi0 -> Branch("vpdSumEast", &OutVPDSumEast, "OutVPDSumEast/I");
	treePi0 -> Branch("vpdSumWest", &OutVPDSumWest, "OutVPDSumWest/I");

	treePi0 -> Branch("zdcADCSumEast", &OutZDCADCSumEast, "OutZDCADCSumEast/F");
	treePi0 -> Branch("zdcADCSumWest", &OutZDCADCSumWest, "OutZDCADCSumWest/F");
	treePi0 -> Branch("zdcADCEast", OutZDCADCEast, "OutZDCADCEast[4]/F");
	treePi0 -> Branch("zdcADCWest", OutZDCADCWest, "OutZDCADCWest[4]/F");
	treePi0 -> Branch("zdcVertexZ", OutZDCVertexZ, "OutZDCVertexZ/F");

	// for RHICf ===================
	treePi0 -> Branch("triggerNumber", &OutTriggerNumber, "OutTriggerNumber/I");
	treePi0 -> Branch("isShowerTrig", &OutIsShowerTrig, "OutIsShowerTrig/O");
	treePi0 -> Branch("isPi0Trig", &OutIsPi0Trig, "OutIsPi0Trig/O");
	treePi0 -> Branch("isHighEMTrig", &OutIsHighEMTrig, "OutIsHighEMTrig/O");

	treePi0 -> Branch("L90", &OutL90, "OutL90[2]/F");

	treePi0 -> Branch("photonNum", &OutPhotonNum, "OutPhotonNum/I");
	treePi0 -> Branch("photonPid", &OutPID, "OutPID[4]/I");
	treePi0 -> Branch("photonTowerIdx", &OutPhotonTowerIdx, "OutPhotonTowerIdx[4]/I");
	treePi0 -> Branch("photonPos", &OutPhotonPos, "OutPhotonPos[4][2]/D");
	treePi0 -> Branch("photonE", &OutPhotonE, "OutPhotonE[4][2]/D");
	treePi0 -> Branch("towerEnergy", &OutTowerEnergy, "OutTowerEnergy[4][2]/D");

	treePi0 -> Branch("isRHICfPi0", &OutIsRHICfPi0, "OutIsRHICfPi0/O");
	treePi0 -> Branch("towerIdx", &OutTowerIdx, "OutTowerIdx/I");
	treePi0 -> Branch("type", &OutType, "OutType/I");
	treePi0 -> Branch("x", &OutX, "OutX/D");
	treePi0 -> Branch("y", &OutY, "OutY/D");
	treePi0 -> Branch("e", &OutE, "OutE/D");
	treePi0 -> Branch("px", &OutPx, "OutPx/D");
	treePi0 -> Branch("py", &OutPy, "OutPy/D");
	treePi0 -> Branch("pz", &OutPz, "OutPz/D");
	treePi0 -> Branch("pt", &OutPt, "OutPt/D");
	treePi0 -> Branch("xf", &OutXf, "OutXf/D");
	treePi0 -> Branch("m", &OutMass, "OutMass/D");

	// Track data ================
	treePi0 -> Branch("trackNum", &OutTrackNum, "OutTrackNum/I");
	treePi0 -> Branch("trackEta", OutTrackEta, "OutTrackEta[100]/D");
	treePi0 -> Branch("trackPhi", OutTrackPhi, "OutTrackPhi[100]/D");
	treePi0 -> Branch("trackPt", OutTrackPt, "OutTrackPt[100]/D");
	treePi0 -> Branch("trackPID", OutTrackPID, "OutTrackPID[100]/I");
	treePi0 -> Branch("trackDca", OutTrackDca, "OutTrackDca[100]/D");
	treePi0 -> Branch("trackPos", OutTrackPos, "OutTrackPos[100][3]/D");
	treePi0 -> Branch("trackMom", OutTrackMom, "OutTrackMom[100][3]/D");
	treePi0 -> Branch("vertex", OutVertex, "OutVertex[3]/D");

	// FMS Data ================
	treePi0 -> Branch("fmsPhotonNum", &OutFmsPhotonNum, "OutFmsPhotonNum/I");
	treePi0 -> Branch("fmsPhotonFlag", OutFmsPhotonFlag, "OutFmsPhotonFlag[100]/I");
	treePi0 -> Branch("fmsPhotonPos", OutFmsPhotonPos, "OutFmsPhotonPos[100][3]/D");
	treePi0 -> Branch("fmsPhotonMom", OutFmsPhotonMom, "OutFmsPhotonMom[100][3]/D");
	treePi0 -> Branch("fmsPhotonE", OutFmsPhotonE, "OutFmsPhotonE[100]/D");


    for(int event=0; event<eventNum; event++){
		if(event%1000==0){cout << "event: " << event << " / " << eventNum << endl;}
        StRHICfPi0Events* pi0Events = pi0maker -> getRHICfPi0Events(event);

		// general infomation
		int runNumber = pi0Events -> getRunNumber();
		int bunchNumber = pi0Events -> getBunchNumber();
		int fillNumber = pi0Events -> getFillNumber();


		OutRunNumber = runNumber;
		OutBunchNumber = bunchNumber;
		OutFillNumber = fillNumber;

		OutTriggerNumber = pi0Events->getRHICfTriggerNumber();
		OutIsShowerTrig = pi0Events -> isRHICfShowerTrig();
		OutIsPi0Trig =  pi0Events -> isRHICfPi0Trig();
		OutIsHighEMTrig =  pi0Events -> isRHICfHighEMTrig();

		// spinBit
		int spinBit = pi0Events -> getSpinBit();
		bool blueSpinUp = false;
		if(spinBit == 5 || spinBit == 6){blueSpinUp = true;}
		OutBlueSpinUp = blueSpinUp;

		// Miltiplicity
		OutTofMult = pi0Events -> getTofMultiplicity();
		OutGRefMult = pi0Events -> getGRefMultiplicity();
		OutRefMult = pi0Events -> getRefMultiplicity();

		// BBC
		OutBBCSSumEast = pi0Events -> getBbcAdcSumEast();
		OutBBCSSumWest = pi0Events -> getBbcAdcSumWest();

		OutBBCLSumEast = pi0Events -> getBbcLargeAdcSumEast();
		OutBBCLSumWest = pi0Events -> getBbcLargeAdcSumWest();

        for(int pmt=0; pmt<16; pmt++){
			OutBBCSEast[pmt][0] = pi0Events -> getBbcAdcEast(pmt);
			OutBBCSWest[pmt][0] = pi0Events -> getBbcAdcWest(pmt);

			OutBBCSEast[pmt][1] = pi0Events -> getBbcTdcEast(pmt);
			OutBBCSWest[pmt][1] = pi0Events -> getBbcTdcWest(pmt);

			OutBBCSEast[pmt][2] = pi0Events -> getBbcTacEast(pmt);
			OutBBCSWest[pmt][2] = pi0Events -> getBbcTacWest(pmt);
		}
		for(pmt=0; pmt<8; pmt++){
			OutBBCLEast[pmt][0] = pi0Events -> getBbcLargeAdcEast(pmt);
			OutBBCLWest[pmt][0] = pi0Events -> getBbcLargeAdcWest(pmt);

			OutBBCLEast[pmt][1] = pi0Events -> getBbcLargeTdcEast(pmt);
			OutBBCLWest[pmt][1] = pi0Events -> getBbcLargeTdcWest(pmt);

			OutBBCLEast[pmt][2] = pi0Events -> getBbcLargeTacEast(pmt);
			OutBBCLWest[pmt][2] = pi0Events -> getBbcLargeTacWest(pmt);
		}


		// VPD
		OutVPDSumEast = pi0Events -> getVpdAdcSumEast();
		OutVPDSumWest = pi0Events -> getVpdAdcSumWest();
		OutVpdTimeDiff = pi0Events -> getVpdTimeDifference();

		for(int pmt=0; pmt<16; pmt++){
			OutVpdEast[pmt][0] = pi0Events -> getVpdAdcEast(pmt);
			OutVpdWest[pmt][0] = pi0Events -> getVpdAdcWest(pmt);

			OutVpdEast[pmt][1] = pi0Events -> getVpdTdcEast(pmt);
			OutVpdWest[pmt][1] = pi0Events -> getVpdTdcWest(pmt);

			OutVpdEastHighThr[pmt][0] = pi0Events -> getVpdAdcHighThrEast(pmt);
			OutVpdWestHighThr[pmt][0] = pi0Events -> getVpdAdcHighThrWest(pmt);

			OutVpdEastHighThr[pmt][1] = pi0Events -> getVpdTdcHighThrEast(pmt);
			OutVpdWestHighThr[pmt][1] = pi0Events -> getVpdTdcHighThrWest(pmt);

		}
		OutVpdEarliestTDC[0] = pi0Events -> getVpdEarliestTdcEast(); 
		OutVpdEarliestTDC[1] = pi0Events -> getVpdEarliestTdcWest(); 
		
		OutVpdEarliestTDCHighthr[0] = pi0Events -> getVpdEarliestTdcHighThrEast(); 
		OutVpdEarliestTDCHighthr[1] = pi0Events -> getVpdEarliestTdcHighThrWest(); 


		// ZDC
		OutZDCADCSumEast = pi0Events -> getZdcAdcSumEast();
		OutZDCADCSumWest = pi0Events -> getZdcAdcSumWest();
		for(int i=0; i<4; i++){
			OutZDCADCEast[i] = pi0Events -> getZdcAdcEast(i);
			OutZDCADCWest[i] = pi0Events -> getZdcAdcWest(i);
		}
		OutZDCVertexZ = pi0Events -> getZdcVertexZ();

		// RHICf ============================
		OutL90[0] = pi0Events->getRHICfL90(0);
		OutL90[1] = pi0Events->getRHICfL90(1);

		std::fill(OutPID,OutPID+4,-999);
		std::fill(OutPhotonTowerIdx,OutPhotonTowerIdx+4,-999);
		std::fill(&OutPhotonPos[0][0],&OutPhotonPos[3][2],-999.);
		std::fill(&OutPhotonE[0][0],&OutPhotonE[3][2],-999.);
		std::fill(&OutTowerEnergy[0][0],&OutTowerEnergy[3][2],-999.);

		OutPhotonNum = pi0Events->getRHICfPointNumber();
		for(int i=0; i<OutPhotonNum; i++){
			StRHICfPoint* points = pi0Events->getRHICfPoint(i);
			OutPID[i] = points -> getPID();

			OutPhotonPos[i][0] = points -> getPointPos(0);
			OutPhotonPos[i][1] = points -> getPointPos(1);
			OutPhotonE[i][0] = points -> getPointEnergy(0);
			OutPhotonE[i][1] = points -> getPointEnergy(1);
			int towerIdx = points -> getTowerIdx();
			OutPhotonTowerIdx[i] = towerIdx;
			if(towerIdx <= -1 || towerIdx >=2){continue;}
			OutTowerEnergy[i][towerIdx] = points -> getTowerSumEnergy(0);
		}
		
		OutIsRHICfPi0 = pi0Events->isRHICfPi0();
		OutTowerIdx = -1;
		OutType = -1;
		OutX = -999.;
		OutY = -999.;
		OutE = -999.;
		OutPx = -999.;
		OutPy = -999.;
		OutPz = -999.;
		OutPt = -999.;
		OutXf = -999.;
		OutMass = -999.;

		if(pi0Events->isRHICfPi0()){
			StRHICfPi0* rhicfPi0 = pi0Events->getRHICfPi0();
			OutTowerIdx = rhicfPi0->getTowerIdx();
			OutType = rhicfPi0->getType();
			OutX = rhicfPi0 -> getPosX();
			OutY = rhicfPi0 -> getPosY();
			OutE = rhicfPi0 -> getEnergy();
			OutPx = rhicfPi0 -> getMomX();
			OutPy = rhicfPi0 -> getMomY();
			OutPz = rhicfPi0 -> getMomZ();
			OutPt = rhicfPi0 -> getPT();
			OutXf = rhicfPi0 -> getXF();
			OutMass = rhicfPi0 -> getMass();
		}

		// track =====================
		OutTrackNum = 0;
		std::fill(OutTrackEta, OutTrackEta+100, -999.);
		std::fill(OutTrackPhi, OutTrackPhi+100, -999.);
		std::fill(OutTrackPt, OutTrackPt+100, -999.);
		std::fill(OutTrackPID, OutTrackPID+100, -1);
		std::fill(OutTrackDca, OutTrackDca+100, -999.);
		std::fill(&OutTrackPos[0][0], &OutTrackPos[99][3], -999.);
		std::fill(&OutTrackMom[0][0], &OutTrackMom[99][3], -999.);

		int trackNum = pi0Events -> getTrackCollNumber();
		int tmpTrackNum = 0;
		for(int i=0; i<trackNum; i++){
			StRHICfTPCTrack* track = pi0Events->getTPCTrack(i);

			Bool_t isPrimary = track -> isPrimary();
			if(isPrimary == false){continue;}
			if(tmpTrackNum >= 100){
				cout << "event: " << event << "primary trackNum: " << tmpTrackNum << endl;
				break;
			}
			OutTrackEta[tmpTrackNum] = track -> getEta();
			OutTrackPhi[tmpTrackNum] = track -> getMomentum().Phi();
			OutTrackPt[tmpTrackNum] = track -> getPt();
			OutTrackPID[tmpTrackNum] = track -> getPID();
			OutTrackDca[tmpTrackNum] = track -> getDca3D();
			OutTrackPos[tmpTrackNum][0] = track -> getOriginPosX();
			OutTrackPos[tmpTrackNum][1] = track -> getOriginPosY();
			OutTrackPos[tmpTrackNum][2] = track -> getOriginPosZ();
			OutTrackMom[tmpTrackNum][0] = track -> getMomX();
			OutTrackMom[tmpTrackNum][1] = track -> getMomY();
			OutTrackMom[tmpTrackNum][2] = track -> getMomZ();
			tmpTrackNum++;
		}
		OutTrackNum = tmpTrackNum;


		// vertex ==================
		std::fill(OutVertex, OutVertex+3, -999.);
		OutVertex[0] = pi0Events -> getVertexX();
		OutVertex[1] = pi0Events -> getVertexY();
		OutVertex[2] = pi0Events -> getVertexZ();


		// fms ====================
		std::fill(OutFmsPhotonFlag, OutFmsPhotonFlag+100, -999.);
		std::fill(&OutFmsPhotonPos[0][0], &OutFmsPhotonPos[99][3], -999.);
		std::fill(&OutFmsPhotonMom[0][0], &OutFmsPhotonMom[99][3], -999.);
		std::fill(OutFmsPhotonE, OutFmsPhotonE+100, -999.);

		OutFmsPhotonNum = Int_t(pi0Events -> getFmsPhotonNumber());
		for(int i=0; i<OutFmsPhotonNum; i++){
			OutFmsPhotonFlag[i] = pi0Events -> getFmsPhotonCategory(i);
			OutFmsPhotonPos[i][0] = pi0Events -> getFmsPhotonX(i);
			OutFmsPhotonPos[i][1] = pi0Events -> getFmsPhotonY(i);
			OutFmsPhotonPos[i][2] = pi0Events -> getFmsPhotonZ(i);
			OutFmsPhotonMom[i][0] = pi0Events -> getFmsPhotonPx(i);
			OutFmsPhotonMom[i][1] = pi0Events -> getFmsPhotonPy(i);
			OutFmsPhotonMom[i][2] = pi0Events -> getFmsPhotonPz(i);
			OutFmsPhotonE[i] = pi0Events -> getFmsPhotonEnergy(i);
		}
		treePi0 -> Fill();
    }

	files -> cd();
	treePi0 -> Write();
	files -> Close();

    delete pi0maker;
}


TString getFileID(int mode, TString inputFiles)
{
	TString runNumber = "";
	TString daqNumber = "";

	std::string const dirFile = inputFiles.Data();
	if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos ){
		std::ifstream inputStream( dirFile.c_str() );
		std::string file;
		size_t pos;
		while(getline(inputStream, file)){
			pos = file.find_first_of(" ");
			if (pos != std::string::npos ) file.erase(pos,file.length()-pos);
			if(file.find("AnalRHICfPi0") != std::string::npos) {
				
				std::stringstream sstreamPath(file);
				std::string wordPath;
				std::vector<string> wordPaths;
				while(getline(sstreamPath, wordPath, '/')){
					wordPaths.push_back(wordPath);
				}
				int wordSize = wordPaths.size();

				std::stringstream sstreamWord(wordPaths[wordSize-1]);
				std::string word;
				int nIdx = 0;
				while(getline(sstreamWord, word, '_')){
					// find a runnumber 
					if(nIdx==2){
						if(word!="adc"){runNumber = word;}
					}
					if(nIdx==4){
						daqNumber = word;
					}
					nIdx++;
				}
			}
		}
	}

	if(mode ==0){return runNumber;}
	if(mode ==1){return daqNumber;}
	return "";
}
