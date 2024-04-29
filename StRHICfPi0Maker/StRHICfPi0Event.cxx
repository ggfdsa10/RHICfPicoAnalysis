#include "StRHICfPi0Events.h"

ClassImp(StRHICfPi0Events)

StRHICfPi0Events::StRHICfPi0Events()
{
  Clear();
}

StRHICfPi0Events::~StRHICfPi0Events()
{
    // RHICf data 
  for(UInt_t i=0; i<mRHICfPointColl.size(); i++){
    if(mRHICfPointColl[i]){
        delete mRHICfPointColl[i]; 
        mRHICfPointColl[i] = nullptr;
    }
  }
  mRHICfPointColl.clear();

  if(mRHICfPi0){
    delete mRHICfPi0;
    mRHICfPi0 = nullptr;
  }

  for(UInt_t i=0; i<mTrackColl.size(); i++){
    if(mTrackColl[i]){
        delete mTrackColl[i]; 
        mTrackColl[i] = nullptr;
    }
  }
  mTrackColl.clear();
}

void StRHICfPi0Events::Clear(Option_t *option)
{
  // ======= general data =======
  mRunNum = 0;
  mEventNum = 0;
  mFillNum = 0;
  mBunchNum = 0;
  mSpinBit = 0;
  mBeamEnergy = 0.;
  mPolarization = 0.;
  mRelativeLuminosity = 0.;

  // ======= trigger data =======
  mIsRHICf = 0;
  mIsDiffractive = 0;
  mIsVPD = 0;
  mIsTPC = 0;

  // ======= RHICf data =======
  mRHICfRunNumber = 0;
  mRHICfEventNumber = 0;
  mRHICfTriggerNumber = 0;
  mRHICfRunType = 0;
  memset(mRHICfL90, 0, sizeof(mRHICfL90));
  mIsRHICfPi0 = false;

  for(UInt_t i=0; i<mRHICfPointColl.size(); i++){
    if(mRHICfPointColl[i]){
      delete mRHICfPointColl[i]; 
      mRHICfPointColl[i] = nullptr;
    }
  }
  mRHICfPointColl.clear();

  if(mRHICfPi0){
    delete mRHICfPi0;
    mRHICfPi0 = nullptr;
  }

  // ======= STAR data =======

  // Multiplicity
  mTofMultiplicity = 0;
  mRefMult = 0;
  mGRefMult = 0;

  // BBC
  memset(mBbcEast, 0, sizeof(mBbcEast));
  memset(mBbcLargeEast, 0, sizeof(mBbcLargeEast));
  memset(mBbcWest, 0, sizeof(mBbcWest));
  memset(mBbcLargeWest, 0, sizeof(mBbcLargeWest));

  // VPD
  memset(mVpdEast, 0, sizeof(mVpdEast));
  memset(mVpdWest, 0, sizeof(mVpdWest));
  memset(mVpdEastHighThr, 0, sizeof(mVpdEastHighThr));
  memset(mVpdWestHighThr, 0, sizeof(mVpdWestHighThr));
  memset(mVpdEarliestTDC, 0, sizeof(mVpdEarliestTDC));
  memset(mVpdEarliestTDCHighthr, 0, sizeof(mVpdEarliestTDCHighthr));
  mVpdTimeDiff = 0;

  // ZDC
  memset(mZdcAdcSum, 0, sizeof(mZdcAdcSum));
  memset(mZdcAdc, 0, sizeof(mZdcAdc));
  memset(mZdcTdc, 0, sizeof(mZdcTdc));
  memset(mZdcSmdAdc, 0, sizeof(mZdcSmdAdc));
  mZdcVertexZ = -999.;


  // vertex
  mVertex[0] = -999.;
  mVertex[1] = -999.;
  mVertex[2] = -999.;

  // Tracks
  mPrimaryTrackNum = 0;
  mGlobalTrackNum = 0;
  for(UInt_t i=0; i<mTrackColl.size(); i++){
    if(mTrackColl[i]){
      delete mTrackColl[i]; 
      mTrackColl[i] = nullptr;
    }
  }
  mTrackColl.clear();
  mTrackColl.shrink_to_fit();

  // FMS
  mFmsCategory.clear();
  mFmsPhotonPos.clear();
  mFmsPhoton4Vec.clear();

  // RPS
  mRpsTrackType.clear(); 
  mRpsTrackBranch.clear();
  mRpsMomentum.clear(); 
  for(UInt_t i=0; i<mRpsPos.size(); i++){
    mRpsPos[i].clear();
  }
  mRpsPos.clear();
}

void StRHICfPi0Events::print()
{
}

// ======= General Info =======
void StRHICfPi0Events::setRunNumber(UInt_t num){mRunNum = num;}
void StRHICfPi0Events::setEventNumber(UInt_t num){mEventNum = num;}
void StRHICfPi0Events::setFillNumber(UShort_t num){mFillNum = num;}
void StRHICfPi0Events::setBunchNumber(UShort_t num){mBunchNum = num;}
void StRHICfPi0Events::setSpinBit(UChar_t bit){mSpinBit = bit;}
void StRHICfPi0Events::setBeamEnergy(Float_t val){mBeamEnergy = val;}
void StRHICfPi0Events::setPolarization(Float_t val){mPolarization = val;}
void StRHICfPi0Events::setRelativeLuminosity(Float_t val){mRelativeLuminosity = val;}

UInt_t StRHICfPi0Events::getRunNumber(){return mRunNum;}
UInt_t StRHICfPi0Events::getEventNumber(){return mEventNum;}
UShort_t StRHICfPi0Events::getFillNumber(){return mFillNum;}
UShort_t StRHICfPi0Events::getBunchNumber(){return mBunchNum;}
UChar_t StRHICfPi0Events::getSpinBit(){return mSpinBit;}
Float_t StRHICfPi0Events::getBeamEnergy(){return mBeamEnergy;}
Float_t StRHICfPi0Events::getPolarization(){return mPolarization;}
Float_t StRHICfPi0Events::getRelativeLuminosity(){return mRelativeLuminosity;}

// ======= Trigger Info =======
void StRHICfPi0Events::setIsRHICf(Bool_t val){mIsRHICf = val;}
void StRHICfPi0Events::setIsDiffractive(Bool_t val){mIsDiffractive = val;}
void StRHICfPi0Events::setIsVPD(Bool_t val){mIsVPD = val;}
void StRHICfPi0Events::setIsTPC(Bool_t val){mIsTPC = val;}

Bool_t StRHICfPi0Events::isRHICf(){return mIsRHICf;}
Bool_t StRHICfPi0Events::isDiffractive(){return mIsDiffractive;}
Bool_t StRHICfPi0Events::isVPD(){return mIsVPD;}
Bool_t StRHICfPi0Events::isTPC(){return mIsTPC;}

// ======= RHICf Info =======
void StRHICfPi0Events::setRHICfRunNumber(UInt_t run){mRHICfRunNumber = run;}
void StRHICfPi0Events::setRHICfEventNumber(UInt_t event){mRHICfEventNumber = event;}
void StRHICfPi0Events::setRHICfTriggerNumber(UInt_t trig){mRHICfTriggerNumber = trig;}
void StRHICfPi0Events::setRHICfRunType(UChar_t type){mRHICfRunType = type;}
void StRHICfPi0Events::setRHICfL90(Int_t tower, Float_t val){mRHICfL90[tower] = val;}

UInt_t StRHICfPi0Events::getRHICfRunNumber(){return mRHICfRunNumber;}
UInt_t StRHICfPi0Events::getRHICfEventNumber(){return mRHICfEventNumber;}
UInt_t StRHICfPi0Events::getRHICfTriggerNumber(){return mRHICfTriggerNumber;}
Float_t StRHICfPi0Events::getRHICfL90(Int_t tower){return mRHICfL90[tower];}
UChar_t StRHICfPi0Events::getRHICfRunType(){return mRHICfRunType;}
UChar_t StRHICfPi0Events::getRHICfPointNumber(){return mRHICfPointColl.size();}

Bool_t StRHICfPi0Events::isRHICfShowerTrig(){return (mRHICfTriggerNumber & 0x010)? true : false;}
Bool_t StRHICfPi0Events::isRHICfPi0Trig(){return (mRHICfTriggerNumber & 0x080)? true : false;}
Bool_t StRHICfPi0Events::isRHICfHighEMTrig(){return (mRHICfTriggerNumber & 0x200)? true : false;}

Bool_t StRHICfPi0Events::isRHICfPi0(){return mIsRHICfPi0;}

StRHICfPoint* StRHICfPi0Events::getNewRHICfPoint()
{
  StRHICfPoint* point = new StRHICfPoint();
  mRHICfPointColl.push_back(point);
  return point;
}

std::vector<StRHICfPoint*>& StRHICfPi0Events::getPointCollection(){return mRHICfPointColl;}

StRHICfPoint* StRHICfPi0Events::getRHICfPoint(UInt_t idx)
{
  if(idx < mRHICfPointColl.size()){return mRHICfPointColl[idx];}
  return 0;
}

StRHICfPi0* StRHICfPi0Events::getNewRHICfPi0()
{
  mIsRHICfPi0 = true;
  mRHICfPi0 = new StRHICfPi0();
  return mRHICfPi0;
}

StRHICfPi0* StRHICfPi0Events::getRHICfPi0()
{
  if(mIsRHICfPi0){return mRHICfPi0;}
  cout << "******** StRHICfPi0Events::getRHICfPi0() --- Current events not include Pi0 !! ********" << endl;
  return 0;
}

// ======= STAR sub-detector info =======

// ToF
void StRHICfPi0Events::setTofMultiplicity(UShort_t val){mTofMultiplicity = val;}
void StRHICfPi0Events::setRefMultiplicity(UShort_t val){mRefMult = val;}
void StRHICfPi0Events::setGRefMultiplicity(UShort_t val){mGRefMult = val;}

UShort_t StRHICfPi0Events::getTofMultiplicity(){return mTofMultiplicity;}
UShort_t StRHICfPi0Events::getRefMultiplicity(){return mRefMult;}
UShort_t StRHICfPi0Events::getGRefMultiplicity(){return mGRefMult;}

// BBC
void StRHICfPi0Events::setBbcAdcEast(int pmt, UShort_t adc){mBbcEast[pmt][0] = adc;}
void StRHICfPi0Events::setBbcAdcWest(int pmt, UShort_t adc){mBbcWest[pmt][0] = adc;}
void StRHICfPi0Events::setBbcLargeAdcEast(int pmt, UShort_t adc){mBbcLargeEast[pmt][0] = adc;}
void StRHICfPi0Events::setBbcLargeAdcWest(int pmt, UShort_t adc){mBbcLargeWest[pmt][0] = adc;}

void StRHICfPi0Events::setBbcTdcEast(int pmt, UShort_t tdc){mBbcEast[pmt][1] = tdc;}
void StRHICfPi0Events::setBbcTdcWest(int pmt, UShort_t tdc){mBbcWest[pmt][1] = tdc;}
void StRHICfPi0Events::setBbcLargeTdcEast(int pmt, UShort_t tdc){mBbcLargeEast[pmt][1] = tdc;}
void StRHICfPi0Events::setBbcLargeTdcWest(int pmt, UShort_t tdc){mBbcLargeWest[pmt][1] = tdc;}

void StRHICfPi0Events::setBbcTacEast(int pmt, UShort_t tac){mBbcEast[pmt][2] = tac;}
void StRHICfPi0Events::setBbcTacWest(int pmt, UShort_t tac){mBbcWest[pmt][2] = tac;}
void StRHICfPi0Events::setBbcLargeTacEast(int pmt, UShort_t tac){mBbcLargeEast[pmt][2] = tac;}
void StRHICfPi0Events::setBbcLargeTacWest(int pmt, UShort_t tac){mBbcLargeWest[pmt][2] = tac;}

UShort_t StRHICfPi0Events::getBbcAdcEast(int pmt){return mBbcEast[pmt][0];}
UShort_t StRHICfPi0Events::getBbcAdcWest(int pmt){return mBbcWest[pmt][0];}
UShort_t StRHICfPi0Events::getBbcLargeAdcEast(int pmt){return mBbcLargeEast[pmt][0];}
UShort_t StRHICfPi0Events::getBbcLargeAdcWest(int pmt){return mBbcLargeWest[pmt][0];}

UInt_t StRHICfPi0Events::getBbcAdcSumEast()
{
  UInt_t sumADC = 0;
  for(int pmt=0; pmt<16; pmt++){
    sumADC += mBbcEast[pmt][0];
  }
  return sumADC;
}

UInt_t StRHICfPi0Events::getBbcAdcSumWest()
{
  UInt_t sumADC = 0;
  for(int pmt=0; pmt<16; pmt++){
    sumADC += mBbcWest[pmt][0];
  }
  return sumADC;
}

UInt_t StRHICfPi0Events::getBbcLargeAdcSumEast()
{
  UInt_t sumADC = 0;
  for(int pmt=0; pmt<8; pmt++){
    sumADC += mBbcLargeEast[pmt][0];
  }
  return sumADC;
}

UInt_t StRHICfPi0Events::getBbcLargeAdcSumWest()
{
  UInt_t sumADC = 0;
  for(int pmt=0; pmt<8; pmt++){
    sumADC += mBbcLargeWest[pmt][0];
  }
  return sumADC;
}

UShort_t StRHICfPi0Events::getBbcTdcEast(int pmt){return mBbcEast[pmt][1];}
UShort_t StRHICfPi0Events::getBbcTdcWest(int pmt){return mBbcWest[pmt][1];}
UShort_t StRHICfPi0Events::getBbcLargeTdcEast(int pmt){return mBbcLargeEast[pmt][1];}
UShort_t StRHICfPi0Events::getBbcLargeTdcWest(int pmt){return mBbcLargeWest[pmt][1];}

UShort_t StRHICfPi0Events::getBbcTacEast(int pmt){return mBbcEast[pmt][2];}
UShort_t StRHICfPi0Events::getBbcTacWest(int pmt){return mBbcWest[pmt][2];}
UShort_t StRHICfPi0Events::getBbcLargeTacEast(int pmt){return mBbcLargeEast[pmt][2];}
UShort_t StRHICfPi0Events::getBbcLargeTacWest(int pmt){return mBbcLargeWest[pmt][2];}

// VPD
void StRHICfPi0Events::setVpdAdcEast(int pmt, UShort_t adc){mVpdEast[pmt][0] = adc;}
void StRHICfPi0Events::setVpdAdcWest(int pmt, UShort_t adc){mVpdWest[pmt][0] = adc;}
void StRHICfPi0Events::setVpdAdcHighThrEast(int pmt, UShort_t thr){mVpdEastHighThr[pmt][0] = thr;}
void StRHICfPi0Events::setVpdAdcHighThrWest(int pmt, UShort_t thr){mVpdWestHighThr[pmt][0] = thr;}

void StRHICfPi0Events::setVpdTdcEast(int pmt, UShort_t tdc){mVpdEast[pmt][1] = tdc;}
void StRHICfPi0Events::setVpdTdcWest(int pmt, UShort_t tdc){mVpdWest[pmt][1] = tdc;}
void StRHICfPi0Events::setVpdTdcHighThrEast(int pmt, UShort_t thr){mVpdEastHighThr[pmt][1] = thr;}
void StRHICfPi0Events::setVpdTdcHighThrWest(int pmt, UShort_t thr){mVpdWestHighThr[pmt][1] = thr;}

void StRHICfPi0Events::setVpdEarliestTdcEast(UShort_t eTdc){mVpdEarliestTDC[0] = eTdc;}
void StRHICfPi0Events::setVpdEarliestTdcWest(UShort_t eTdc){mVpdEarliestTDC[1] = eTdc;}
void StRHICfPi0Events::setVpdEarliestTdcHighThrEast(UShort_t thr){mVpdEarliestTDCHighthr[0] = thr;}
void StRHICfPi0Events::setVpdEarliestTdcHighThrWest(UShort_t thr){mVpdEarliestTDCHighthr[1] = thr;}

void StRHICfPi0Events::setVpdTimeDifference(UShort_t time){mVpdTimeDiff = time;}

UShort_t StRHICfPi0Events::getVpdAdcEast(int pmt){return mVpdEast[pmt][0];}
UShort_t StRHICfPi0Events::getVpdAdcWest(int pmt){return mVpdWest[pmt][0];}
UShort_t StRHICfPi0Events::getVpdAdcHighThrEast(int pmt){return mVpdEastHighThr[pmt][0];}
UShort_t StRHICfPi0Events::getVpdAdcHighThrWest(int pmt){return mVpdWestHighThr[pmt][0];}

UInt_t StRHICfPi0Events::getVpdAdcSumEast()
{
  UInt_t sumADC = 0;
  for(int pmt=0; pmt<16; pmt++){
    sumADC += mVpdEast[pmt][0];
  }
  return sumADC;
} 
UInt_t StRHICfPi0Events::getVpdAdcSumWest()
{
  UInt_t sumADC = 0;
  for(int pmt=0; pmt<16; pmt++){
    sumADC += mVpdWest[pmt][0];
  }
  return sumADC;
}

UShort_t StRHICfPi0Events::getVpdTdcEast(int pmt){return mVpdEast[pmt][1];}
UShort_t StRHICfPi0Events::getVpdTdcWest(int pmt){return mVpdWest[pmt][1];}
UShort_t StRHICfPi0Events::getVpdTdcHighThrEast(int pmt){return mVpdEastHighThr[pmt][1];}
UShort_t StRHICfPi0Events::getVpdTdcHighThrWest(int pmt){return mVpdWestHighThr[pmt][1];}

UShort_t StRHICfPi0Events::getVpdEarliestTdcEast(){return mVpdEarliestTDC[0];}
UShort_t StRHICfPi0Events::getVpdEarliestTdcWest(){return mVpdEarliestTDC[1];}
UShort_t StRHICfPi0Events::getVpdEarliestTdcHighThrEast(){return mVpdEarliestTDCHighthr[0];}
UShort_t StRHICfPi0Events::getVpdEarliestTdcHighThrWest(){return mVpdEarliestTDCHighthr[1];}

UShort_t StRHICfPi0Events::getVpdTimeDifference(){return mVpdTimeDiff;}


// ZDC
void StRHICfPi0Events::setZdcAdcSumEast(Float_t adc){mZdcAdcSum[0] = adc;}
void StRHICfPi0Events::setZdcAdcSumWest(Float_t adc){mZdcAdcSum[1] = adc;}
void StRHICfPi0Events::setZdcAdcEast(Int_t idx, Float_t adc){mZdcAdc[0][idx] = adc;}
void StRHICfPi0Events::setZdcAdcWest(Int_t idx, Float_t adc){mZdcAdc[1][idx] = adc;}
void StRHICfPi0Events::setZdcTdcEast(Int_t idx, Float_t tdc){mZdcTdc[0][idx] = tdc;}
void StRHICfPi0Events::setZdcTdcWest(Int_t idx, Float_t tdc){mZdcTdc[1][idx] = tdc;}
void StRHICfPi0Events::setZdcSmdAdcEast(Int_t vertiHori, Int_t idx, Float_t adc){mZdcSmdAdc[0][vertiHori][idx] = adc;}
void StRHICfPi0Events::setZdcSmdAdcWest(Int_t vertiHori, Int_t idx, Float_t adc){mZdcSmdAdc[1][vertiHori][idx] = adc;}
void StRHICfPi0Events::setZdcVertexZ(Float_t val){mZdcVertexZ = val;}

Float_t StRHICfPi0Events::getZdcAdcSumEast(){return mZdcAdcSum[0];}
Float_t StRHICfPi0Events::getZdcAdcSumWest(){return mZdcAdcSum[1];}
Float_t StRHICfPi0Events::getZdcAdcEast(Int_t idx){return mZdcAdc[0][idx];}
Float_t StRHICfPi0Events::getZdcAdcWest(Int_t idx){return mZdcAdc[1][idx];}
Float_t StRHICfPi0Events::getZdcTdcEast(Int_t idx){return mZdcTdc[0][idx];}
Float_t StRHICfPi0Events::getZdcTdcWest(Int_t idx){return mZdcTdc[1][idx];}
Float_t StRHICfPi0Events::getZdcSmdAdcEast(Int_t vertiHori, Int_t idx){return mZdcSmdAdc[0][vertiHori][idx];}
Float_t StRHICfPi0Events::getZdcSmdAdcWest(Int_t vertiHori, Int_t idx){return mZdcSmdAdc[1][vertiHori][idx];}
Float_t StRHICfPi0Events::getZdcVertexZ(){return mZdcVertexZ;}

// Vertex
void StRHICfPi0Events::setVertex(Float_t vx, Float_t vy, Float_t vz)
{
  mVertex[0] = vx;
  mVertex[1] = vy;
  mVertex[2] = vz;
}

Float_t StRHICfPi0Events::getVertexX(){return mVertex[0];}
Float_t StRHICfPi0Events::getVertexY(){return mVertex[1];}
Float_t StRHICfPi0Events::getVertexZ(){return mVertex[2];}
TVector3 StRHICfPi0Events::getVertex()
{
  TVector3 vertex(mVertex[0], mVertex[1], mVertex[2]);
  return vertex;
}

// Tracks
void StRHICfPi0Events::setPrimaryTrackNumber(UShort_t num){mPrimaryTrackNum = num;}
void StRHICfPi0Events::setGlobalTrackNumer(UShort_t num){mGlobalTrackNum = num;}

UShort_t StRHICfPi0Events::getPrimaryTrackNumber(){return mPrimaryTrackNum;}
UShort_t StRHICfPi0Events::getGlobalTrackNumer(){return mGlobalTrackNum;}
UShort_t StRHICfPi0Events::getTrackCollNumber(){return mTrackColl.size();}

StRHICfTPCTrack* StRHICfPi0Events::getNewTPCTrack()
{
  StRHICfTPCTrack* tracks = new StRHICfTPCTrack();
  mTrackColl.push_back(tracks);
  return tracks;
}

StRHICfTPCTrack* StRHICfPi0Events::getTPCTrack(UInt_t idx)
{
  if(idx < mTrackColl.size()){return mTrackColl[idx];}
  return 0;
}

// FMS
void StRHICfPi0Events::setFmsPhoton(UChar_t category, TVector3 pos, TLorentzVector vec4)
{
  mFmsCategory.push_back(category);
  mFmsPhotonPos.push_back(pos);
  mFmsPhoton4Vec.push_back(vec4);
}

UInt_t StRHICfPi0Events::getFmsPhotonNumber(){return int(mFmsCategory.size());}
UChar_t StRHICfPi0Events::getFmsPhotonCategory(Int_t idx){return mFmsCategory[idx];} 
Float_t StRHICfPi0Events::getFmsPhotonX(Int_t idx){return mFmsPhotonPos[idx].X();}
Float_t StRHICfPi0Events::getFmsPhotonY(Int_t idx){return mFmsPhotonPos[idx].Y();}
Float_t StRHICfPi0Events::getFmsPhotonZ(Int_t idx){return mFmsPhotonPos[idx].Z();}
Float_t StRHICfPi0Events::getFmsPhotonPx(Int_t idx){return mFmsPhoton4Vec[idx].Px();}
Float_t StRHICfPi0Events::getFmsPhotonPy(Int_t idx){return mFmsPhoton4Vec[idx].Py();}
Float_t StRHICfPi0Events::getFmsPhotonPz(Int_t idx){return mFmsPhoton4Vec[idx].Pz();}
Float_t StRHICfPi0Events::getFmsPhotonEnergy(Int_t idx){return mFmsPhoton4Vec[idx].E();}
TVector3 StRHICfPi0Events::getFmsPhotonPos(Int_t idx){return mFmsPhotonPos[idx];}
TLorentzVector StRHICfPi0Events::getFmsPhotonFourMomentum(Int_t idx){return mFmsPhoton4Vec[idx];}

// RPS
void StRHICfPi0Events::setRpsInfo(UChar_t type, UChar_t branch, TVector3 trackMom, vector<TVector3> trkPointPos)
{
  if((type==0 && trkPointPos.size()!=1) || (type==1 && trkPointPos.size()!=2)){return;}
  mRpsTrackType.push_back(type);
  mRpsTrackBranch.push_back(branch);
  mRpsMomentum.push_back(trackMom);
  mRpsPos.push_back(trkPointPos);
}

UInt_t StRHICfPi0Events::getRpsTrackNumber(){return mRpsTrackType.size();}
UChar_t StRHICfPi0Events::getRpsTrackType(Int_t idx){return mRpsTrackType[idx];}
UChar_t StRHICfPi0Events::getRpsTrackBranch(Int_t idx){return mRpsTrackBranch[idx];}

Float_t StRHICfPi0Events::getRpsTrackTheta(Int_t idx)
{
  if(getRpsTrackType(idx) == 0){
    return atan(mRpsMomentum[idx].Perp()/abs(mRpsMomentum[idx].Z()));
  }
  if(getRpsTrackType(idx) == 1){
    TVector3 deltaVector = getRpsTrackPosition(idx, 1) - getRpsTrackPosition(idx, 0);
    return atan(deltaVector.Perp()/abs(deltaVector.Z()));
  }
  return 0.;
}

Float_t StRHICfPi0Events::getRpsTrackPhi(Int_t idx)
{
  if(getRpsTrackType(idx) == 0){
    return mRpsMomentum[idx].Phi();
  }
  if(getRpsTrackType(idx) == 1){
    TVector3 deltaVector = getRpsTrackPosition(idx, 1) - getRpsTrackPosition(idx, 0);
    return deltaVector.Phi();
  }
  return 0.;
}

Float_t StRHICfPi0Events::getRpsTrackP(Int_t idx){return mRpsMomentum[idx].Mag();}
Float_t StRHICfPi0Events::getRpsTrackPt(Int_t idx){return mRpsMomentum[idx].Perp();}
Float_t StRHICfPi0Events::getRpsTrackEta(Int_t idx){return mRpsMomentum[idx].PseudoRapidity();}
TVector3 StRHICfPi0Events::getRpsTrackMomentum(Int_t idx){return mRpsMomentum[idx];}

TVector3 StRHICfPi0Events::getRpsTrackPosition(Int_t idx, Int_t pointIdx)
{
  if(getRpsTrackType(idx) == 0){
    return mRpsPos[idx][0];
  }
  if(getRpsTrackType(idx) == 1){
    return mRpsPos[idx][pointIdx];
  }
}
