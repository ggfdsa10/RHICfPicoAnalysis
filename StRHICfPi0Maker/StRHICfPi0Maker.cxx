// ============================================================ 
// | The StRHICfPi0Maker class                                | 
// | for only RHICf asymmetries of the nuetral Pion analysis. | 
// | To be update for several STAR detector data              | 
// |                                                          | 
// | Author: Seunghwan Lee.                                   | 
// ============================================================ 

#include "StRHICfPi0Maker.h"

// DB headers
#include "StRHICfDbMaker/StRHICfDbMaker.h"

// STAR headers
#include "StChain/StChain.h"
#include "StChain/StChainOpt.h"

// StMuEvents headers
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuTypes.hh"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"

// rhicf
#include "StMuDSTMaker/COMMON/StMuRHICfCollection.h"
#include "StMuDSTMaker/COMMON/StMuRHICfRawHit.h"
#include "StMuDSTMaker/COMMON/StMuRHICfHit.h"
#include "StMuDSTMaker/COMMON/StMuRHICfPoint.h"

// fms
#include "StMuDSTMaker/COMMON/StMuFmsCollection.h"
#include "StMuDSTMaker/COMMON/StMuFmsCluster.h"
#include "StMuDSTMaker/COMMON/StMuFmsPoint.h"

// rps
#include "StMuDSTMaker/COMMON/StMuRpsCollection.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrack.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrackPoint.h"
#include "StMuRpsUtil/StMuRpsUtil.h"
#include "StMuRpsUtil/StMuRpsCollection2.h"

// StEvent headers
#include "StEvent/StEvent.h"
#include "StEvent/StRHICfPoint.h"
#include "StEvent/StTriggerData.h"
#include "StEvent/StTriggerDetectorCollection.h"
#include "StEvent/StTriggerIdCollection.h"
#include "StEvent/StTriggerId.h"
#include "StEvent/StBbcTriggerDetector.h"
#include "StEvent/StVpdTriggerDetector.h"
#include "StEvent/StL0Trigger.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StDcaGeometry.h"

// other
#include <unordered_map>
#include <bitset>
#include <vector>
#include "StMessMgr.h"
#include "Stypes.h"
#include "StEventTypes.h"
#include "StEnumerations.h"

StRHICfPi0Maker::StRHICfPi0Maker(int ioMode, const char* fileName, StMuDstMaker* muDstMaker, const char* name) : 
    StMaker(name), mIoMode(ioMode), mInputFileName(fileName), muDstMaker(muDstMaker), mFileTypeName((char *)"AnalRHICfPi0")
{
}

StRHICfPi0Maker::~StRHICfPi0Maker()
{
}

Int_t StRHICfPi0Maker::Init() 
{  
    // temporary code
    fillNumArray[0] = 21142;
    fillNumArray[1] = 21145;
    fillNumArray[2] = 21148;
    fillNumArray[3] = 21149;
    fillNumArray[4] = 21150;

    mTpcVpdVzDiffCut = 6.; // default picoDst vpd-tpc vertex diff cut
    mNFiles = -1;

    if(mIoMode==ioRead){
        LOG_INFO << "StRHICfPi0Maker::StRHICfPi0Maker() -- begin StRHICfPi0Maker construction for Read mode" << endm;
        openRead();
    }
    else if(mIoMode==ioWrite){
        LOG_INFO << "StRHICfPi0Maker::StRHICfPi0Maker() -- begin StRHICfPi0Maker construction for Write mode" << endm;

        // mMuRpsUtil = new StMuRpsUtil(muDstMaker);
        spinPatternData();
        if(openWrite() == kStErr){return kStErr;}
    }

    iEvent = 0;
    return kStOK;
}

Int_t StRHICfPi0Maker::Make() 
{
    LOG_INFO << "StRHICfPi0Maker::Make()" << endm;

    // =================== DST Set up ======================
    muDst = (StMuDst*) GetInputDS("MuDst"); // from DST
    if(!muDst) {LOG_ERROR << "StRHICfPi0Maker::Make() -- no StMuDst" << endm;  return kStErr;};

    muEvent = muDst->event(); // from muDST
    if(!muEvent) {LOG_ERROR << "StRHICfPi0Maker::Make() -- no StMuEvent" << endm;  return kStErr;};

    muRHICfColl = muDst->muRHICfCollection();
    muRHICfRawHit = muRHICfColl->getRawHit();
    muRHICfHit = muRHICfColl->getHit();

    muFmsColl = muDst->muFmsCollection();

    if(!muRHICfColl) {LOG_ERROR << "StRHICfPi0Maker::Make() -- no MuRHICfCollection"<< endm; return kStErr;}
    if(!muRHICfRawHit){LOG_ERROR << "StRHICfPi0Maker::Make() -- RHICfRawHit not including " << endm; return kStErr;}
    if(!muRHICfHit){LOG_ERROR << "StRHICfPi0Maker::Make() -- RHICfHit not including " << endm; return kStErr;}
    if(!muFmsColl){LOG_ERROR << "StRHICfPi0Maker::Make() -- MuFmsCollection not including " << endm; return kStErr;}

    const StTriggerData* trigData =  muEvent->triggerData();
    if(!trigData){LOG_WARN << "StRHICfPi0Maker::Make() -- no found StTriggerData" << endm; return kStWarn;}

    // Initialize a filled data.
    clear();

    // =================== General information ======================
    StRunInfo runInfo = muEvent->runInfo(); 
    Int_t fillNum = runInfo.beamFillNumber(blue); // star fill number
    Int_t runNum = muEvent->runNumber();
    Int_t eventNum = muEvent->eventId();
    Int_t bunch7Bit = trigData->bunchId7Bit();
    Double_t beamEnergy = runInfo.beamEnergy(StBeamDirection::blue); // [GeV] at COM system
    Int_t spinBit = 0;

    int fillIdx = -1;
    for(int fill=0; fill<5; fill++){
        if(fillNumArray[fill] == fillNum){fillIdx = fill;}
    }
    if(bunch7Bit<31 || (40<=bunch7Bit && bunch7Bit <= 110)){
        int bluePatt = spinPatterns[fillIdx][bunch7Bit][0];
        int yellowPatt = spinPatterns[fillIdx][bunch7Bit][1];
        if(bluePatt == 1 && yellowPatt == 1){spinBit = 5;}
        if(bluePatt == 1 && yellowPatt == -1){spinBit = 6;}
        if(bluePatt == -1 && yellowPatt == 1){spinBit = 9;}
        if(bluePatt == -1 && yellowPatt == -1){spinBit = 10;}
    }

    // =================== Trigger information ======================
    Bool_t isRHICf = muEvent->triggerIdCollection().nominal().isTrigger(590901);
    Bool_t isDiffractive = muEvent->triggerIdCollection().nominal().isTrigger(590902);
    Bool_t isVPD = muEvent->triggerIdCollection().nominal().isTrigger(590903);
    Bool_t isTPC = muEvent->triggerIdCollection().nominal().isTrigger(590904);

    mRHICfPi0Events -> setRunNumber(runNum);
    mRHICfPi0Events -> setEventNumber(eventNum);
    mRHICfPi0Events -> setFillNumber(fillNum);
    mRHICfPi0Events -> setBunchNumber(bunch7Bit);
    mRHICfPi0Events -> setSpinBit(spinBit);
    mRHICfPi0Events -> setBeamEnergy(beamEnergy);
    mRHICfPi0Events -> setPolarization(beamPolarization(fillNum));
    mRHICfPi0Events -> setRelativeLuminosity(relativeluminosity(fillNum));
    mRHICfPi0Events -> setIsRHICf(isRHICf);
    mRHICfPi0Events -> setIsDiffractive(isDiffractive);
    mRHICfPi0Events -> setIsVPD(isVPD);
    mRHICfPi0Events -> setIsTPC(isTPC);

    // =================== RHICf data ======================
    mRHICfPi0Events -> setRHICfRunNumber(muRHICfRawHit -> getRHICfRunNumber());
    mRHICfPi0Events -> setRHICfEventNumber(muRHICfRawHit -> getRHICfEventNumber());
    mRHICfPi0Events -> setRHICfTriggerNumber(muRHICfRawHit->getTriggerNumber());
    mRHICfPi0Events -> setRHICfRunType(muRHICfRawHit -> getRunType());
    mRHICfPi0Events -> setRHICfL90(0, muRHICfHit->getL90(0));
    mRHICfPi0Events -> setRHICfL90(1, muRHICfHit->getL90(1));
    
    // store all photon data in temporary structure
    Int_t rhicfPointNum = muRHICfColl->numberOfPoints();
    for(int classNum = 0; classNum<rhicfPointNum; classNum++){
        StMuRHICfPoint* muRHICfPoint = muRHICfColl->getPoint(classNum);

        // After event cut for analysis
        if(!eventCut(muRHICfPoint)){continue;}

        StRHICfPoint* point = mRHICfPi0Events -> getNewRHICfPoint();
        point -> setTowerIdx(muRHICfPoint -> getTowerIdx());
        point -> setPID(muRHICfPoint -> getPID());
        point -> setPointPos(muRHICfPoint -> getPointPos(0), muRHICfPoint -> getPointPos(1));
        point -> setPointEnergy(muRHICfPoint -> getPointEnergy(0), muRHICfPoint -> getPointEnergy(1));  
        point -> setTowerSumEnergy(muRHICfPoint -> getTowerSumEnergy(0) , muRHICfPoint -> getTowerSumEnergy(1));
    }

    if(mRHICfPi0Events->getPointCollection().size() > 0){
        convertIPSystem(true, false); // Convert the coordinate system from RHICf tower origin to Collision Point
        kinematics();                 // Calculate the Kinematics and various values for Pi0
    }

    // =================== STAR sub-detector data ======================
    vertex();

    // Multiplicty
    mRHICfPi0Events -> setTofMultiplicity(trigData->tofMultiplicity());
    mRHICfPi0Events -> setRefMultiplicity(muEvent->refMult());
    mRHICfPi0Events -> setGRefMultiplicity(muEvent->grefmult());

    triggerDetectorData();
    trackData();
    fmsData();
    rpsData();

    // =================== Fill data ===================
    fillData();

    iEvent++;
    return kStOK;
}

Int_t StRHICfPi0Maker::Finish() 
{
    if(mIoMode==ioWrite){
        LOG_INFO << Form("StRHICfPi0Maker::Finish() -- Writing and closing %s",mOutputFileName.Data()) << endm;
        mTFile -> cd();
        mOutTree -> Write();
        mTFile -> Close();
    }

    return kStOK;
}

Int_t StRHICfPi0Maker::clear()
{
    mVertexVec.SetXYZ(-999., -999., -999.);
    mOutDataArray -> Clear("C");
    mRHICfPi0Events = (StRHICfPi0Events*)mOutDataArray -> ConstructedAt(0);
    return kStOk;
}

StRHICfPi0Events* StRHICfPi0Maker::getRHICfPi0Events(Int_t idx)
{
    if(idx >= mChain->GetEntries()){LOG_ERROR << "StRHICfPi0Maker::getRHICfPi0Events() -- wrong index !! " << endm;}
    mChain -> GetEntry(idx);
    StRHICfPi0Events* rhicfPi0Events = (StRHICfPi0Events*)mReadDataArray -> At(0);
    return rhicfPi0Events;
}

Int_t StRHICfPi0Maker::getAnalEntries(){return mChain->GetEntries();}

Int_t StRHICfPi0Maker::openRead()
{
    mNFiles = 0;
    if(mInputFileName.Length() == 0){
        // No input file
        LOG_ERROR << "Input file is not a existing ... " << endm;
        return kStErr;
    }
    else{
        if(!mChain){mChain = new TChain("AnalRHICfPi0");}

        std::string const dirFile = mInputFileName.Data();
        if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos ){
            std::ifstream inputStream( dirFile.c_str() );
            if(!inputStream) {LOG_ERROR << "ERROR: Cannot open list file " << dirFile << endm;}

            std::string file;
            size_t pos;
            while(getline(inputStream, file)){
                pos = file.find_first_of(" ");
                if (pos != std::string::npos ) file.erase(pos,file.length()-pos);
                if(file.find("AnalRHICfPi0") != std::string::npos) {
                    TFile* ftmp = TFile::Open(file.c_str());
                    if(ftmp && !ftmp->IsZombie() && ftmp->GetNkeys()) {
                        cout << " Read in AnalRHICfPi0 file " << file << endl;
                        mChain->Add(file.c_str());
                        ++mNFiles;
                    } 
                    if (ftmp) {
                        ftmp->Close();
                    } 
                }
            }
            LOG_INFO << " Total " << mNFiles << " files have been read in. " << endm;
        }
        else if(dirFile.find("AnalRHICfPi0") != std::string::npos){
            mChain->Add(dirFile.c_str());
            mNFiles = 1;
            LOG_INFO << " Total " << mNFiles << " files have been read in " << dirFile << endm;
        }

        if(mChain){
            mReadDataArray = new TClonesArray("StRHICfPi0Events");
            mChain -> SetBranchAddress("StRHICfPi0Events", &mReadDataArray);
        }
    }
    return kStOk;
}

Int_t StRHICfPi0Maker::openWrite()
{
    TString streamTypeName;
    TString runNumber;
    TString daqNumber;
    mNFiles = 0;
    TString rootFileName;

    if(mInputFileName.Length() == 0){
        // No input file
        LOG_ERROR << "Input file is not a existing ... " << endm;
        return kStErr;
    }
    else{
        std::string const dirFile = mInputFileName.Data();
        if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos ){
            std::ifstream inputStream( dirFile.c_str() );
            if(!inputStream) {LOG_ERROR << "ERROR: Cannot open list file " << dirFile << endm;}

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
                    rootFileName = wordPaths[wordSize-1];
                    std::string word;
                    int nIdx = 0;
                    while(getline(sstreamWord, word, '_')){
                        // find a production stream type 
                        if(nIdx==1){streamTypeName = word;}
                        if(streamTypeName == "physics"){
                            LOG_ERROR << "Files has not RHICf stream!!! (" << wordPaths[wordSize-1] << ")" << endm;
                            return kStErr;
                        }
                        // find a runnumber 
                        if(nIdx==2){
                            if(word!="adc"){runNumber = word;}
                        }
                        if(nIdx==4){
                            std::stringstream sstreamWord2(word);
                            while(getline(sstreamWord2, word, '.')){
                                daqNumber = word;
                                break;
                            }
                        }
                        nIdx++;
                    }
                    mNFiles++;
                } 

            } 
            LOG_INFO << " Total " << mNFiles << " files have been read in. " << endm;
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
            rootFileName = wordPaths[wordSize-1];
            std::string word;
            int nIdx = 0;
            while(getline(sstreamWord, word, '_')){
                // find a production stream type 
                if(nIdx==1){streamTypeName = word;}
                if(streamTypeName == "physics"){
                    LOG_ERROR << "Files has not RHICf stream!!! (" << wordPaths[wordSize-1] << ")" << endm;
                    return kStErr;
                }
                // find a runnumber 
                if(nIdx==2){
                    if(word!="adc"){runNumber = word;}
                }
                if(nIdx==4){
                    std::stringstream sstreamWord2(word);
                    while(getline(sstreamWord2, word, '.')){
                        daqNumber = word;
                        break;
                    }
                }
                nIdx++;
            }
            mNFiles = 1;
        }
    }

    if(mNFiles == 1){
        mOutputFileName = "st_" + streamTypeName + "_" + runNumber + "_pp500_" + daqNumber + "_AnalRHICfPi0.root";
        LOG_INFO << Form("StRHICfPi0Maker::openWrite() -- Input file name: %s", rootFileName.Data()) << endm;
    }
    else{
        mOutputFileName = "st_" + streamTypeName + "_" + runNumber + "_pp500_AnalRHICfPi0.root";
        LOG_INFO << Form("StRHICfPi0Maker::openWrite() -- number of Files in .list: %i", mNFiles) << endm;
    }
    
    LOG_INFO << Form("StRHICfPi0Maker::openWrite() -- Output file name: %s",mOutputFileName.Data()) << endm;

    mTFile = new TFile(mOutputFileName.Data(), "recreate");
    mOutTree = new TTree("AnalRHICfPi0","AnalRHICfPi0");

    mOutDataArray = new TClonesArray("StRHICfPi0Events");
    mOutTree -> Branch("StRHICfPi0Events",&mOutDataArray);

    return kStOk;
}

Int_t StRHICfPi0Maker::getNFiles(){return mNFiles;}

void StRHICfPi0Maker::spinPatternData()
{
    TString dataPath = "StRoot/StRHICfPool/StRHICfPi0Maker/SpinPatternData/";
    memset(spinPatterns, 0, sizeof(spinPatterns));

    for(int fill=0; fill<5; fill++){
        for(int beam=0; beam<2; beam++){
            TString beamName = (beam==0)? "blue" : "yellow";
            TString spinDataName = dataPath+beamName+Form("_patterns_%i.dat",fillNumArray[fill]);

            std::ifstream spinDataFile;
            spinDataFile.open(spinDataName, ios::in);
            if(!spinDataFile.is_open()){continue;}
            LOG_INFO << "StRHICfPi0Maker::spinPatternData() --- find a " << spinDataName << endm;

            string lines;
            while(getline(spinDataFile, lines)){
                TString line = lines;
                TObjArray *tokens = line.Tokenize(" ");
                TString bunchNum = ((TObjString *) tokens -> At(1)) -> GetString();
                TString pattern = ((TObjString *) tokens -> At(2)) -> GetString();

                spinPatterns[fill][bunchNum.Atoi()-1][beam] = pattern.Atoi();
            }
            spinDataFile.close();
        }
    }
}

void StRHICfPi0Maker::fillData()
{
    mOutTree -> Fill();
}

Bool_t StRHICfPi0Maker::eventCut(StMuRHICfPoint* point)
{
    const Float_t geometryCut = 2.; // [mm]
    const Float_t energyCut = 20.; // [GeV]

    if(point->getPointEnergy(0) < energyCut){return false;} // Energy cut, if energy lower than 20 GeV
    double towerSize = double(checkGSOBarSize(point->getTowerIdx())); 

    Double_t x = point -> getPointPos(0);
    Double_t y = point -> getPointPos(1);
    if(x > towerSize-geometryCut || x < geometryCut){return false;} // Position cut, if x is out of cutting range 
    if(y > towerSize-geometryCut || y < geometryCut){return false;} // Position cut, if y is out of cutting range 

    return true;
}

void StRHICfPi0Maker::convertIPSystem(bool metOpt, bool referOpt)
{
    // for convert Collision Point system, define the system in TS origin
    Int_t TowerIdxByRunType = -999;
    Double_t distOriginToOrigin = distTStoTL - TMath::Sqrt(2.)*geoCenterTL + TMath::Sqrt(2.)*geoCenterTS;
    Double_t beamCenterX = beamCenterPosition(0, metOpt, referOpt);
    Double_t beamCenterY = beamCenterPosition(1, metOpt, referOpt);

    if(mRHICfPi0Events->getRHICfRunType() == kRHICfTL){
        TowerIdxByRunType = 1;
        beamCenterY = beamCenterY + TMath::Sqrt(2.)*geoCenterTL;
    }
    if(mRHICfPi0Events->getRHICfRunType() == kRHICfTS || mRHICfPi0Events->getRHICfRunType() == kRHICfTOP){
        TowerIdxByRunType = 0;
        beamCenterY = beamCenterY + TMath::Sqrt(2.)*geoCenterTS;
    }

    for(UInt_t i=0; i<mRHICfPi0Events->getPointCollection().size(); i++){
        double posX = mRHICfPi0Events->getPointCollection()[i]->getPointPos(0);
        double posY = mRHICfPi0Events->getPointCollection()[i]->getPointPos(1);

        // the Hit Position convert to one tower coordinate
        if(TowerIdxByRunType == 0 && mRHICfPi0Events->getPointCollection()[i]->getTowerIdx() == 1){
            posX += distOriginToOrigin/TMath::Sqrt(2.);
            posY += distOriginToOrigin/TMath::Sqrt(2.);
        }
        if(TowerIdxByRunType == 1 && mRHICfPi0Events->getPointCollection()[i]->getTowerIdx() == 0){
            posX -= distOriginToOrigin/TMath::Sqrt(2.);
            posY -= distOriginToOrigin/TMath::Sqrt(2.);
        }

        // Hit position rotate to -45 degree.
        double tmpPosX = (posX - posY)/TMath::Sqrt(2.);
        double tmpPosY = (posX + posY)/TMath::Sqrt(2.);

        // convert to beam center and IP system [m]
        posX = (tmpPosX - beamCenterX)*0.001;
        posY = (tmpPosY - beamCenterY)*0.001;

        mRHICfPi0Events->getPointCollection()[i] -> setPointPos(posX, posY);
    }
}

void StRHICfPi0Maker::kinematics()
{
    if(mRHICfPi0Events->getPointCollection().size() == 2){
        const Float_t l90CutRange0 = 8.;
        const Float_t l90CutRange1 = 18.;
        int gammaTowerIdx1 = mRHICfPi0Events->getPointCollection()[0]->getTowerIdx();
        int gammaTowerIdx2 = mRHICfPi0Events->getPointCollection()[1]->getTowerIdx();
        if(mRHICfPi0Events->getRHICfL90(gammaTowerIdx1) < l90CutRange0 || l90CutRange1 < mRHICfPi0Events->getRHICfL90(gammaTowerIdx1)){return;} // hadron condidate cut for PID 
        if(mRHICfPi0Events->getRHICfL90(gammaTowerIdx2) < l90CutRange0 || l90CutRange1 < mRHICfPi0Events->getRHICfL90(gammaTowerIdx2)){return;} // hadron condidate cut for PID 
    

        double x1 = mRHICfPi0Events->getPointCollection()[0]->getPointPos(0);
        double y1 = mRHICfPi0Events->getPointCollection()[0]->getPointPos(1);

        double x2 = mRHICfPi0Events->getPointCollection()[1]->getPointPos(0);
        double y2 = mRHICfPi0Events->getPointCollection()[1]->getPointPos(1);

        int pi0Type = -1;
        if(mRHICfPi0Events->getPointCollection()[0]->getTowerIdx() == mRHICfPi0Events->getPointCollection()[1]->getTowerIdx()){
            pi0Type = 2;
            if(x1 == x2 || y1 == y2){return;}
        }
        else{pi0Type = 1;}

        Double_t posZ = distZatIP*0.001;

        double r1 = sqrt(pow(x1,2) + pow(y1,2) + pow(posZ,2));
		double r2 = sqrt(pow(x2,2) + pow(y2,2) + pow(posZ,2));

        double e1 = mRHICfPi0Events->getPointCollection()[0]->getPointEnergy(0);
        double e2 = mRHICfPi0Events->getPointCollection()[1]->getPointEnergy(0);
        double e = e1+e2;

		TVector3 p1 = TVector3((x1/r1)*e1, (y1/r1)*e1, (posZ/r1)*e1);
        TVector3 p2 = TVector3((x2/r2)*e2, (y2/r2)*e2, (posZ/r2)*e2);
        TVector3 p = p1+p2;

        double pT = sqrt(pow(p.X(),2) + pow(p.Y(),2));
        double xf = p.Z()/255.;
        double mass = 1000*sqrt(pow(e,2) - pow(p.X(),2) - pow(p.Y(),2) - pow(p.Z(),2));

        StRHICfPi0* rhicfPi0 = mRHICfPi0Events -> getNewRHICfPi0();
        rhicfPi0->setType(pi0Type);
        if(pi0Type == 2){rhicfPi0->setTowerIdx(mRHICfPi0Events->getPointCollection()[0]->getTowerIdx());}
        rhicfPi0 -> setPosition(x1+x2, y1+y2, posZ);
        rhicfPi0 -> setMomentum(p);
        rhicfPi0 -> setEnergy(e);
        rhicfPi0 -> setMass(mass);
        rhicfPi0 -> setPT(pT);
        rhicfPi0 -> setXF(xf);
    }
}

Double_t StRHICfPi0Maker::beamCenterPosition( int xy, bool metOpt, bool referOpt)
{
    if(mRHICfPi0Events->getRHICfRunType() == kRHICfTL){
        if(mRHICfPi0Events->getFillNumber() == fillNumArray[0]){
            if(metOpt==0){
                if(xy==0){return 0.;}
                else if(xy==1){return 2.21;}
            }
            else if(metOpt==1){
                if(xy==0){return 0.66;}
                else if(xy==1){return 1.37;}
            }
        }
        else if(mRHICfPi0Events->getFillNumber() == fillNumArray[1]){
            if(metOpt==0){
                if(xy==0){return 0.;}
                else if(xy==1){return 2.31;}
            }
            else if(metOpt==1){
                if(xy==0){return 0.22;}
                else if(xy==1){return 1.55;}
            }
        }
    }
    else if(mRHICfPi0Events->getRHICfRunType() == kRHICfTS){
        if(mRHICfPi0Events->getFillNumber() == fillNumArray[2]){
            if(metOpt==0){
                if(xy==0){return 0.;}
                else if(xy==1){return 2.36;}
            }
            else if(metOpt==1){
                if(xy==0){return 0.22;}
                else if(xy==1){return 1.37;}
            }
        }
        else if(mRHICfPi0Events->getFillNumber() == fillNumArray[4]){
            if(metOpt==0){
                if(xy==0){return 0.;}
                else if(xy==1){return 2.33;}
            }
            else if(metOpt==1){
                if(xy==0){return 0.22;}
                else if(xy==1){return 1.55;}
            }
        }
    }
    else if(mRHICfPi0Events->getRHICfRunType() == kRHICfTOP){
        if(referOpt == 0){ // refer to fill 21148
            if(metOpt==0){
                if(xy==0){return 0.;}
                else if(xy==1){return -21.67;}
            }
            else if(metOpt==1){
                if(xy==0){return 0.22;}
                else if(xy==1){return -22.66;}
            }
        }
        if(referOpt == 1){ // refer to fill 21150
            if(metOpt==0){
                if(xy==0){return 0.;}
                else if(xy==1){return -21.71;}
            }
            else if(metOpt==1){
                if(xy==0){return 0.22;}
                else if(xy==1){return -22.48;}
            }
        }
    }
    return 0.;
}

Double_t StRHICfPi0Maker::relativeluminosity(Int_t fillNum)
{
    if(fillNum == fillNumArray[0]){return 0.9581;}
    if(fillNum == fillNumArray[1]){return 0.9623;}
    if(fillNum == fillNumArray[2]){return 0.9924;}
    if(fillNum == fillNumArray[3]){return 0.9949;}
    if(fillNum == fillNumArray[4]){return 0.9774;}
    return 0.;
}

Double_t StRHICfPi0Maker::beamPolarization(Int_t fillNum)
{
    if(fillNum == fillNumArray[0]){return 0.536;}
    if(fillNum == fillNumArray[1]){return 0.554;}
    if(fillNum == fillNumArray[2]){return 0.590;}
    if(fillNum == fillNumArray[3]){return 0.566;}
    if(fillNum == fillNumArray[4]){return 0.592;}
    return 0.;
}

Int_t StRHICfPi0Maker::triggerDetectorData()
{
    const StTriggerData* trigData =  muEvent->triggerData();

    // BBC Small
    for(int pmt=1; pmt<17; pmt++){
        mRHICfPi0Events -> setBbcAdcEast(pmt-1, trigData->bbcADC(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setBbcTdcEast(pmt-1, trigData->bbcTDC5bit(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setBbcTacEast(pmt-1, trigData->bbcTDC(StBeamDirection::east, pmt));

        mRHICfPi0Events -> setBbcAdcWest(pmt-1, trigData->bbcADC(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setBbcTdcWest(pmt-1, trigData->bbcTDC5bit(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setBbcTacWest(pmt-1, trigData->bbcTDC(StBeamDirection::west, pmt));
    }
    // BBC Large
    for(int pmt=17; pmt<25; pmt++){
        mRHICfPi0Events -> setBbcLargeAdcEast(pmt-17, trigData->bbcADC(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setBbcLargeTdcEast(pmt-17, trigData->bbcTDC5bit(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setBbcLargeTacEast(pmt-17, trigData->bbcTDC(StBeamDirection::east, pmt));

        mRHICfPi0Events -> setBbcLargeAdcWest(pmt-17, trigData->bbcADC(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setBbcLargeTdcWest(pmt-17, trigData->bbcTDC5bit(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setBbcLargeTacWest(pmt-17, trigData->bbcTDC(StBeamDirection::west, pmt));
    }
    
    // VPD
    for(int pmt=1; pmt<17; pmt++){
        mRHICfPi0Events -> setVpdAdcEast(pmt-1, trigData->vpdADC(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setVpdTdcEast(pmt-1, trigData->vpdTDC(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setVpdAdcHighThrEast(pmt-1, trigData->vpdADCHighThr(StBeamDirection::east, pmt));
        mRHICfPi0Events -> setVpdTdcHighThrEast(pmt-1, trigData->vpdTDCHighThr(StBeamDirection::east, pmt));

        mRHICfPi0Events -> setVpdAdcWest(pmt-1, trigData->vpdADC(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setVpdTdcWest(pmt-1, trigData->vpdTDC(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setVpdAdcHighThrWest(pmt-1, trigData->vpdADCHighThr(StBeamDirection::west, pmt));
        mRHICfPi0Events -> setVpdTdcHighThrWest(pmt-1, trigData->vpdTDCHighThr(StBeamDirection::west, pmt));
    }
    mRHICfPi0Events -> setVpdEarliestTdcEast(trigData->vpdEarliestTDC(StBeamDirection::east));
    mRHICfPi0Events -> setVpdEarliestTdcHighThrEast(trigData->vpdEarliestTDCHighThr(StBeamDirection::east));

    mRHICfPi0Events -> setVpdEarliestTdcWest(trigData->vpdEarliestTDC(StBeamDirection::west));
    mRHICfPi0Events -> setVpdEarliestTdcHighThrWest(trigData->vpdEarliestTDCHighThr(StBeamDirection::west));
    
    mRHICfPi0Events -> setVpdTimeDifference(trigData->vpdTimeDifference());

    // ZDC
    mRHICfPi0Events -> setZdcAdcSumEast(trigData -> zdcAttenuated(StBeamDirection::east)); // Attenuated adc sum
    mRHICfPi0Events -> setZdcAdcSumWest(trigData -> zdcAttenuated(StBeamDirection::west)); // Attenuated adc sum

    mRHICfPi0Events -> setZdcAdcEast(0, trigData -> zdcUnAttenuated(StBeamDirection::east)); // unAttenuated adc sum
    mRHICfPi0Events -> setZdcAdcEast(1, trigData -> zdcADC(StBeamDirection::east, 1)); // East pmt 1
    mRHICfPi0Events -> setZdcAdcEast(2, trigData -> zdcADC(StBeamDirection::east, 2)); // East pmt 2
    mRHICfPi0Events -> setZdcAdcEast(3, trigData -> zdcADC(StBeamDirection::east, 3)); // East pmt 3

    mRHICfPi0Events -> setZdcAdcWest(0, trigData -> zdcUnAttenuated(StBeamDirection::west)); // unAttenuated adc sum
    mRHICfPi0Events -> setZdcAdcWest(1, trigData -> zdcADC(StBeamDirection::west, 1)); // West pmt 1
    mRHICfPi0Events -> setZdcAdcWest(2, trigData -> zdcADC(StBeamDirection::west, 2)); // West pmt 2
    mRHICfPi0Events -> setZdcAdcWest(3, trigData -> zdcADC(StBeamDirection::west, 3)); // West pmt 3

    mRHICfPi0Events -> setZdcTdcEast(0, trigData -> zdcTDC(StBeamDirection::east));
    mRHICfPi0Events -> setZdcTdcEast(1, trigData -> zdcPmtTDC(StBeamDirection::east, 1));
    mRHICfPi0Events -> setZdcTdcEast(2, trigData -> zdcPmtTDC(StBeamDirection::east, 2));
    mRHICfPi0Events -> setZdcTdcEast(3, trigData -> zdcPmtTDC(StBeamDirection::east, 3));

    mRHICfPi0Events -> setZdcTdcWest(0, trigData -> zdcTDC(StBeamDirection::west));
    mRHICfPi0Events -> setZdcTdcWest(1, trigData -> zdcPmtTDC(StBeamDirection::west, 1));
    mRHICfPi0Events -> setZdcTdcWest(2, trigData -> zdcPmtTDC(StBeamDirection::west, 2));
    mRHICfPi0Events -> setZdcTdcWest(3, trigData -> zdcPmtTDC(StBeamDirection::west, 3));

    for(int i=0; i<7; i++){
        mRHICfPi0Events -> setZdcSmdAdcEast(0, i, trigData -> zdcSMD(StBeamDirection::east, 0, i+1));
        mRHICfPi0Events -> setZdcSmdAdcEast(1, i, trigData -> zdcSMD(StBeamDirection::east, 1, i+1));
        mRHICfPi0Events -> setZdcSmdAdcWest(0, i, trigData -> zdcSMD(StBeamDirection::west, 0, i+1));
        mRHICfPi0Events -> setZdcSmdAdcWest(1, i, trigData -> zdcSMD(StBeamDirection::west, 1, i+1));
    }
    mRHICfPi0Events -> setZdcVertexZ(trigData -> zdcVertexZ());

    return kStOk;
}

Int_t StRHICfPi0Maker::vertex()
{
    // same as PicoVtxMode::VpdOrDefault
    muDst->setVertexIndex(0);
    StMuPrimaryVertex* pVertex = muDst->primaryVertex();
    if(!pVertex){return kStOk;}

    mVertexVec.SetXYZ(pVertex->position().x(), pVertex->position().y(), pVertex->position().z());

    StBTofHeader const* mBTofHeader = muDst->btofHeader();
    if (mBTofHeader && fabs(mBTofHeader->vpdVz()) < 200.){
        float vzVpd = mBTofHeader->vpdVz();
        for (unsigned int iVtx=0; iVtx<muDst->numberOfPrimaryVertices(); ++iVtx){
            StMuPrimaryVertex* vtx = muDst->primaryVertex(iVtx);
            if (!vtx) continue;
            if (fabs(vzVpd - vtx->position().z()) < mTpcVpdVzDiffCut){
                muDst->setVertexIndex(iVtx);
                mVertexVec.SetXYZ(muDst->primaryVertex()->position().x(), muDst->primaryVertex()->position().y(), muDst->primaryVertex()->position().z());
                break;
            }
        }
    }
    mRHICfPi0Events -> setVertex(mVertexVec.X(), mVertexVec.Y(), mVertexVec.Z());

    return kStOk;
}

Int_t StRHICfPi0Maker::trackData()
{
    if(!muDst->primaryVertex()){return kStOk;}

    Double_t mBField = muEvent -> magneticField();

    std::unordered_map<unsigned int, unsigned int> index2Primary;


    // Primary tracks that used vertex fitting
    StMuTrack* pTrk;
    UShort_t nPrimaryTracks = muDst->numberOfPrimaryTracks();
    for(int i=0; i<nPrimaryTracks; i++){
        pTrk = (StMuTrack*)muDst->primaryTracks(i);
        if(!pTrk){continue;}
        index2Primary[pTrk->id()] = i;
    }

    UShort_t primaryTrkNum = 0;
    UShort_t globalTrkNum = 0;

    // Global tracks that all of the tracks in TPC
    StMuTrack* gTrk;
    UShort_t nGlobalTracks = muDst->numberOfGlobalTracks();
    for(int i=0; i<nGlobalTracks; i++){
        gTrk = (StMuTrack*)muDst->globalTracks(i);
        if(!gTrk){continue;}
        if(gTrk->type() != global){continue;}
        StMuTrack const* const pTrk = index2Primary.find(gTrk->id()) != index2Primary.end() ? (StMuTrack*)muDst->primaryTracks(index2Primary[gTrk->id()]) : nullptr;

        Bool_t isPrimary = false;
        if(pTrk){
            if (pTrk->type() != primary) continue;
            if (pTrk->id() != gTrk->id()) continue;
            isPrimary = true;
        }
        if(gTrk->index2Cov() < 0){continue;}

        StDcaGeometry* dcaG = muDst->covGlobTracks(gTrk->index2Cov());
        if(!dcaG){
            LOG_WARN << "No dca Geometry for this track !!! " << i << endm;
            continue;
        }

        if(isPrimary == false){continue;}

        StRHICfTPCTrack* tpcTrack = mRHICfPi0Events -> getNewTPCTrack();

        tpcTrack -> setChi2(gTrk->chi2());
        if(gTrk->primaryTrack()){tpcTrack -> setStatus(1);}
        else{tpcTrack -> setStatus(0);}

        THelixTrack t = dcaG->thelix();
        StThreeVectorD V(muDst->primaryVertex()->position());

        tpcTrack -> setDca3D(t.Dca(V.xyz())); // distance b.t.w global and vertex position in 3D.
        tpcTrack -> setDedx(gTrk->probPidTraits().dEdxFit());
        tpcTrack -> setDndx(gTrk->probPidTraits().dNdxFit());

        // Fill track's hit information
        UShort_t flag = gTrk->flag();
        UShort_t nHitsFit = 0;
        UShort_t nHitsMax = 0;

        if(flag / 100 < 7){ // TPC tracks
            nHitsFit = gTrk->nHitsFit(kTpcId) * gTrk->charge();
            nHitsMax = gTrk->nHitsPoss(kTpcId);
        }
        else { // FTPC tracks
            if(gTrk->helix().momentum(mBField * kilogauss).pseudoRapidity() > 0.){
                //West FTPC
                nHitsFit = gTrk->nHitsFit(kFtpcWestId) * gTrk->charge();
                nHitsMax = gTrk->nHitsPoss(kFtpcWestId);
            }
            else{
                // East FTPC
                nHitsFit = gTrk->nHitsFit(kFtpcEastId) * gTrk->charge();
                nHitsMax = gTrk->nHitsPoss(kFtpcEastId);
            }
        }
        tpcTrack -> setnHitDedx(gTrk->nHitsDedx());
        tpcTrack -> setnHitFit(nHitsFit);
        tpcTrack -> setnHitMax(nHitsMax);

        // position and momentum
        const StThreeVectorF &pvert =  muDst->primaryVertex()->position();
        Double_t vtx[3] = {pvert[0],pvert[1],pvert[2]};
        THelixTrack thelix =  dcaG->thelix();
        thelix.Move(thelix.Path(vtx));
        const Double_t *pos = thelix.Pos();
        const Double_t *mom = thelix.Dir();
        StThreeVectorF momAtDca(mom[0], mom[1], mom[2]);
        momAtDca *= dcaG->momentum().mag();

        tpcTrack -> setOriginPos(pos[0], pos[1], pos[2]);

        if(isPrimary){
            tpcTrack -> setMomentum(pTrk->momentum().x(), pTrk->momentum().y(), pTrk->momentum().z());
            tpcTrack -> setIsPrimary();
            primaryTrkNum++;
        }
        else{
            tpcTrack -> setMomentum(momAtDca[0], momAtDca[1], momAtDca[2]);
            globalTrkNum++;
        }

        // nSigmaPID information
        tpcTrack -> setSigmaElectron(gTrk->nSigmaElectron());
        tpcTrack -> setSigmaPion(gTrk->nSigmaPion());
        tpcTrack -> setSigmaKaon(gTrk->nSigmaKaon());
        tpcTrack -> setSigmaProton(gTrk->nSigmaProton());

        // prob PID information
        tpcTrack -> setProbElectron(gTrk->pidProbElectron());
        tpcTrack -> setProbPion(gTrk->pidProbPion());
        tpcTrack -> setProbKaon(gTrk->pidProbKaon());
        tpcTrack -> setProbProton(gTrk->pidProbProton());

        // pid traits 
        if(gTrk->tofHit()){
            tpcTrack -> setBtofMatchFlag( (UChar_t)(gTrk->btofPidTraits().matchFlag()) );
            tpcTrack -> setBtofTOF( gTrk->btofPidTraits().timeOfFlight() );
            tpcTrack -> setBtofBeta( gTrk->btofPidTraits().beta() );
            tpcTrack -> setBtofSigmaElectron( gTrk->btofPidTraits().sigmaElectron() );
            tpcTrack -> setBtofSigmaPion( gTrk->btofPidTraits().sigmaPion() );
            tpcTrack -> setBtofSigmaKaon( gTrk->btofPidTraits().sigmaKaon() );
            tpcTrack -> setBtofSigmaProton( gTrk->btofPidTraits().sigmaProton() );
        }
        if(gTrk->etofHit()){
            tpcTrack -> setEtofMatchFlag( (UChar_t)(gTrk->etofPidTraits().matchFlag()) );
            tpcTrack -> setEtofTOF(  gTrk->etofPidTraits().timeOfFlight() );
            tpcTrack -> setEtofBeta( gTrk->etofPidTraits().beta() );
        }
        if(gTrk->mtdHit()) {
            tpcTrack -> setMtdMatchFlag( (Char_t)gTrk->mtdPidTraits().matchFlag() );
            tpcTrack -> setMtdDeltaTOF( gTrk->mtdPidTraits().timeOfFlight() - gTrk->mtdPidTraits().expTimeOfFlight() );
            const double c_light = 2.99792458e+8;
            tpcTrack -> setMtdBeta( gTrk->mtdPidTraits().pathLength() / gTrk->mtdPidTraits().expTimeOfFlight() * 1e9 / c_light );
        }
    }
    mRHICfPi0Events -> setPrimaryTrackNumber(primaryTrkNum);
    mRHICfPi0Events -> setGlobalTrackNumer(globalTrkNum);

    return kStOk;
}

Int_t StRHICfPi0Maker::fmsData()
{
    // FMS
    int fmsClusterNum = muFmsColl -> numberOfClusters();
    for(int i=0; i<fmsClusterNum; i++){
        StMuFmsCluster* cluster = muFmsColl->getCluster(i);

        Int_t category = cluster -> category();
        if(category == 0 || category == 3){continue;} // not fitted

        // photon in Cluster
        auto photon = cluster->photons();
        Int_t numerOfPoints = photon->GetEntries();

        Double_t x = 0.;
        Double_t y = 0.;
        Double_t z = 0.;
        for(int i=0; i<numerOfPoints; i++){
            StMuFmsPoint* point = (StMuFmsPoint*)photon -> At(i);
            x += point->xyz().x()*point->energy()/cluster->energy();
            y += point->xyz().y()*point->energy()/cluster->energy();
            z += point->xyz().z()*point->energy()/cluster->energy();
        }

        TVector3 photonPos(x, y, z - 0.); // mVertex
        TLorentzVector fourMomentum(photonPos.Unit()*cluster->energy(), cluster->energy());

        mRHICfPi0Events -> setFmsPhoton(category, photonPos, fourMomentum);
    }
    return kStOk;
}

Int_t StRHICfPi0Maker::rpsData()
{
    // mMuRpsUtil -> updateVertex(0., 0., 0.); // to be updated with mVertexVec
    // StMuRpsCollection2* muRpsColl2 = mMuRpsUtil ->process();
    // int numberTrk = muRpsColl2 -> numberOfTrackPoints(); 
    // int numberTrkPoints = muRpsColl2 -> numberOfTracks(); 

    mMuRpsColl = muDst->RpsCollection();
	int rpsTrackNum = mMuRpsColl->numberOfTracks();
    // int rpsTrackPointNum = mMuRpsColl->numberOfTrackPoints();

    if(rpsTrackNum > 5){
        LOG_INFO << "StRHICfPi0Maker::rpsData() --- Not physical event... continue Roman Pots data" << endl;
        return kStOk;
    }

    int rpsTrackCounter = 0;
    for(int iTrack=0; iTrack<rpsTrackNum; iTrack++){
       StMuRpsTrack* rpsTrack = mMuRpsColl->track(iTrack);
        if(rpsTrack){
            Int_t trackBranch = rpsTrack -> branch();
            Int_t trackType = (Int_t)(rpsTrack -> type()); // 0 == reco. only one point (local) , 1 == reco. using two point (global) , 2 == undefined
            Int_t trackUsedPlane = rpsTrack->planesUsed();
            Float_t trackP = rpsTrack -> p();
            Float_t trackPt = rpsTrack -> pt();
            Float_t trackEta = rpsTrack -> eta();
            Float_t trackT = rpsTrack -> t( muEvent->runInfo().beamEnergy(rpsTrack->branch()<2 ? StBeamDirection::east : StBeamDirection::west) );
            Float_t trackXi = rpsTrack -> xi( muEvent->runInfo().beamEnergy(rpsTrack->branch()<2 ? StBeamDirection::east : StBeamDirection::west) );

            vector<TVector3> trkPointPos;
            for(int iPoint=0; iPoint<2; iPoint++){
                const StMuRpsTrackPoint* trackPoint = rpsTrack->trackPoint(iPoint);
                if(trackPoint){
                    TVector3 pos = trackPoint->positionVec();
                    trkPointPos.push_back(pos);
                }
            }

            Bool_t isTrackBad = false;
            if(trackBranch<0 || trackBranch>3){isTrackBad=true;}
            if(trackType<0 || trackType>1){isTrackBad=true;}
            if(trackUsedPlane<0 || trackUsedPlane>8){isTrackBad=true;}
            if(trackP<0 || trackP>300){isTrackBad=true;}
            if(trackPt<0 || trackPt>300){isTrackBad=true;}
            if(trackEta<-30 || trackEta>30){isTrackBad=true;}
            if(trackXi<-3 || trackXi>3){isTrackBad=true;}
            if(trackT<-1000 || trackT>0){isTrackBad=true;}

            if(isTrackBad == false){
                mRHICfPi0Events->setRpsInfo(trackType, trackBranch, rpsTrack->pVec(), trkPointPos);
                rpsTrackCounter++;
            }
        }
    }
    // mMuRpsUtil -> clear();
    return kStOk;
}
