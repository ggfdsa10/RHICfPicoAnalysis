
#include "TSpectrum.h"
#include <iostream> // time test
#include <time.h> // time test 

using namespace std;

class StMaker;
class StBFChain;
class StMuDstMaker;

void loadLibs();
TString getFileStreamName(TString inputFiles);

void makeAnalRHICfPi0(const Char_t *inputFile = "/star/u/slee5/forRHICf/Files/st_rhicf_18177003_raw_0000006.MuDst.root")
{
	loadLibs();

	StChain* chain = new StChain();
	StMuDstMaker* MuDstMaker = new StMuDstMaker(0, 0, "", inputFile, "MuDst", 100);
	MuDstMaker->SetStatus("*", 1);

	St_db_Maker* dbMk = new St_db_Maker("db", "MySQL:StarDb", "$STAR/StarDb", "StarDb");
	// ================== makers =========================

	TString streamName = getFileStreamName(inputFile);
	if(streamName == "rhicf"){
		StRHICfDbMaker* rhicfDb = new StRHICfDbMaker();
		StRHICfHitMaker* rhicfHit = new StRHICfHitMaker();
		StRHICfPointMaker* rhicfPoint = new StRHICfPointMaker();

		StRHICfPi0Maker* pi0Maker = new StRHICfPi0Maker(1, inputFile, MuDstMaker);
	}
	if(streamName == "rhicf"){}

	// ================ makers end =======================

	chain->Init();
	Int_t totalEvents = MuDstMaker->chain()->GetEntries();
	cout << " Total Events: " << totalEvents << endl;
	// if(totalEvents > 1000){totalEvents = 50;}
	chain->EventLoop(0, totalEvents);


	cout << "****************************************** " << endl;
	cout << "Work done... now its time to close up shop!" << endl;
	cout << "****************************************** " << endl;
	chain->Finish();
	cout << "****************************************** " << endl;
	cout << "total number of events  " << totalEvents << endl;
	cout << "****************************************** " << endl;

	delete chain;
}


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
	gSystem->Load("StPreEclMaker");
	gSystem->Load("StStrangeMuDstMaker");
	gSystem->Load("StMuDSTMaker");
	gSystem->Load("StRHICfDbMaker");
	gSystem->Load("StRHICfRawHitMaker");
	gSystem->Load("StRHICfHitMaker");
	gSystem->Load("StRHICfPointMaker");
    gSystem->Load("StRHICfPi0Maker");
    gSystem->Load("StAnalysisMaker"); // for testing run information

	gSystem->Load("StMuRpsUtil");

	gSystem->Load("libStarAgmlUtil");
	gSystem->Load("StTpcDb");
	gSystem->Load("StMcEvent");
	gSystem->Load("StMcEventMaker");
	gSystem->Load("StDaqLib");
	gSystem->Load("libgen_Tables");
	gSystem->Load("libsim_Tables");
	gSystem->Load("libglobal_Tables");
	gSystem->Load("StEmcTriggerMaker");
	gSystem->Load("StEmcRawMaker");
	gSystem->Load("StEmcADCtoEMaker");
	gSystem->Load("StPreEclMaker");
	gSystem->Load("StEpcMaker");
	gSystem->Load("StEmcSimulatorMaker");
	gSystem->Load("StDbBroker");
	gSystem->Load("StDetectorDbMaker");
	gSystem->Load("StDbUtilities");
	gSystem->Load("StEEmcUtil");
	gSystem->Load("StEEmcDbMaker");
	gSystem->Load("St_db_Maker");
	gSystem->Load("StTriggerUtilities");
	//  MTD libraries
	gSystem->Load("StMagF");
	gSystem->Load("StMtdUtil");
	gSystem->Load("StMtdHitMaker");
	gSystem->Load("StMtdMatchMaker");
	gSystem->Load("StMtdCalibMaker");

	// BTOF libraries
	gSystem->Load("StBTofUtil");
	gSystem->Load("StVpdCalibMaker");
	gSystem->Load("StBTofCalibMaker");

	gSystem->ListLibraries();
}

TString getFileStreamName(TString inputFiles)
{	
	TString streamTypeName = "";

	std::string const dirFile = inputFiles.Data();
	if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos ){
		std::ifstream inputStream( dirFile.c_str() );
		std::string file;
		size_t pos;
		while(getline(inputStream, file)){
			pos = file.find_first_of(" ");
			if (pos != std::string::npos ) file.erase(pos,file.length()-pos);
			if(file.find("MuDst") != std::string::npos) {
				
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
				while(getline(sstreamWord, word, '_'))
				{
					// find a production stream type 
					if(nIdx==1){streamTypeName = word;}
					if(streamTypeName != ""){break;}
					nIdx++;
				}
			} 
		} 
	}
	else if(dirFile.find("MuDst") != std::string::npos) {
		std::stringstream sstreamPath(dirFile);
		std::string wordPath;
		std::vector<string> wordPaths;
		while(getline(sstreamPath, wordPath, '/')){
			wordPaths.push_back(wordPath);
		}
		int wordSize = wordPaths.size();
		std::stringstream sstreamWord(wordPaths[wordSize-1]);
		std::string word;
		int nIdx = 0;
		while(getline(sstreamWord, word, '_'))
		{
			// find a production stream type 
			if(nIdx==1){streamTypeName = word;}
			if(streamTypeName != ""){break;}
			nIdx++;
		}
	}       
	return streamTypeName;
}
