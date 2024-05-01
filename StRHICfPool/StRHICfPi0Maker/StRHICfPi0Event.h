#ifndef StRHICfPi0Events_HH
#define StRHICfPi0Events_HH

#include <iostream>
#include <TObject.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <vector>

#include "StEvent/StRHICfPoint.h"
#include "StRHICfPi0.h"
#include "StRHICfTPCTrack.h"

using namespace std;
using namespace TMath;

class StRHICfPi0Events : public TObject
{
	public: 
		StRHICfPi0Events();
		~StRHICfPi0Events();

    virtual void Clear(Option_t *option = "");
    void print();

    // ======= General Info =======
    void setRunNumber(UInt_t num);
    void setEventNumber(UInt_t num);
    void setFillNumber(UShort_t num);
    void setBunchNumber(UShort_t num);
    void setSpinBit(UChar_t bit);
    void setBeamEnergy(Float_t val);
    void setPolarization(Float_t val);
    void setRelativeLuminosity(Float_t val);

    UInt_t getRunNumber();
    UInt_t getEventNumber();
    UShort_t getFillNumber();
    UShort_t getBunchNumber();
    UChar_t getSpinBit();
    Float_t getBeamEnergy();
    Float_t getPolarization();
    Float_t getRelativeLuminosity();

    // ======= Trigger Info =======
    void setIsRHICf(Bool_t val);
    void setIsDiffractive(Bool_t val);
    void setIsVPD(Bool_t val);
    void setIsTPC(Bool_t val);

    Bool_t isRHICf();
    Bool_t isDiffractive();
    Bool_t isVPD();
    Bool_t isTPC();

    // ======= RHICf Info =======
    void setRHICfRunNumber(UInt_t run);
    void setRHICfEventNumber(UInt_t event);
    void setRHICfTriggerNumber(UInt_t trig);
    void setRHICfRunType(UChar_t type);
    void setRHICfL90(Int_t tower, Float_t val);

    UInt_t getRHICfRunNumber();
    UInt_t getRHICfEventNumber();
    UInt_t getRHICfTriggerNumber();
    UChar_t getRHICfRunType();
    Float_t getRHICfL90(Int_t tower);

    UChar_t getRHICfPointNumber();
    StRHICfPoint* getNewRHICfPoint(); // for write points
    vector<StRHICfPoint*>& getPointCollection();
    StRHICfPoint* getRHICfPoint(UInt_t idx); // for read points

    Bool_t isRHICfShowerTrig();
    Bool_t isRHICfPi0Trig();
    Bool_t isRHICfHighEMTrig();
    
    Bool_t isRHICfPi0();
    StRHICfPi0* getNewRHICfPi0();
    StRHICfPi0* getRHICfPi0();

    // ======= STAR sub-detector info =======

    // Multiplicty
    void setTofMultiplicity(UShort_t val); 
    void setRefMultiplicity(UShort_t val);
    void setGRefMultiplicity(UShort_t val);

    UShort_t getTofMultiplicity(); 
    UShort_t getRefMultiplicity(); 
    UShort_t getGRefMultiplicity(); 


    // BBC
    void setBbcAdcEast(int pmt, UShort_t adc);
    void setBbcAdcWest(int pmt, UShort_t adc);
    void setBbcLargeAdcEast(int pmt, UShort_t adc);
    void setBbcLargeAdcWest(int pmt, UShort_t adc);

    void setBbcTdcEast(int pmt, UShort_t tdc);
    void setBbcTdcWest(int pmt, UShort_t tdc);
    void setBbcLargeTdcEast(int pmt, UShort_t tdc);
    void setBbcLargeTdcWest(int pmt, UShort_t tdc);

    void setBbcTacEast(int pmt, UShort_t tac);
    void setBbcTacWest(int pmt, UShort_t tac);
    void setBbcLargeTacEast(int pmt, UShort_t tac);
    void setBbcLargeTacWest(int pmt, UShort_t tac);

    UShort_t getBbcAdcEast(int pmt);
    UShort_t getBbcAdcWest(int pmt);
    UShort_t getBbcLargeAdcEast(int pmt);
    UShort_t getBbcLargeAdcWest(int pmt);

    UInt_t getBbcAdcSumEast();
    UInt_t getBbcAdcSumWest();
    UInt_t getBbcLargeAdcSumEast();
    UInt_t getBbcLargeAdcSumWest();

    UShort_t getBbcTdcEast(int pmt);
    UShort_t getBbcTdcWest(int pmt);
    UShort_t getBbcLargeTdcEast(int pmt);
    UShort_t getBbcLargeTdcWest(int pmt);

    UShort_t getBbcTacEast(int pmt);
    UShort_t getBbcTacWest(int pmt);
    UShort_t getBbcLargeTacEast(int pmt);
    UShort_t getBbcLargeTacWest(int pmt);


    // VPD
    void setVpdAdcEast(int pmt, UShort_t adc);
    void setVpdAdcWest(int pmt, UShort_t adc);
    void setVpdAdcHighThrEast(int pmt, UShort_t thr);
    void setVpdAdcHighThrWest(int pmt, UShort_t thr);
    
    void setVpdTdcEast(int pmt, UShort_t tdc);
    void setVpdTdcWest(int pmt, UShort_t tdc);
    void setVpdTdcHighThrEast(int pmt, UShort_t thr);
    void setVpdTdcHighThrWest(int pmt, UShort_t thr);

    void setVpdEarliestTdcEast(UShort_t eTdc);
    void setVpdEarliestTdcWest(UShort_t eTdc);
    void setVpdEarliestTdcHighThrEast(UShort_t thr);
    void setVpdEarliestTdcHighThrWest(UShort_t thr);


    void setVpdTimeDifference(UShort_t time);

    UShort_t getVpdAdcEast(int pmt);
    UShort_t getVpdAdcWest(int pmt);
    UShort_t getVpdAdcHighThrEast(int pmt);
    UShort_t getVpdAdcHighThrWest(int pmt);
    UInt_t getVpdAdcSumEast(); 
    UInt_t getVpdAdcSumWest();

    UShort_t getVpdTdcEast(int pmt);
    UShort_t getVpdTdcWest(int pmt);
    UShort_t getVpdTdcHighThrEast(int pmt);
    UShort_t getVpdTdcHighThrWest(int pmt);
    
    UShort_t getVpdEarliestTdcEast();
    UShort_t getVpdEarliestTdcWest();
    UShort_t getVpdEarliestTdcHighThrEast();
    UShort_t getVpdEarliestTdcHighThrWest();

    UShort_t getVpdTimeDifference();


    // ZDC
    void setZdcAdcSumEast(Float_t adc);
    void setZdcAdcSumWest(Float_t adc);
    void setZdcAdcEast(Int_t idx, Float_t adc);
    void setZdcAdcWest(Int_t idx, Float_t adc);
    void setZdcTdcEast(Int_t idx, Float_t tdc);
    void setZdcTdcWest(Int_t idx, Float_t tdc);
    void setZdcSmdAdcEast(Int_t vertiHori, Int_t idx, Float_t adc);
    void setZdcSmdAdcWest(Int_t vertiHori, Int_t idx, Float_t adc);
    void setZdcVertexZ(Float_t val);

    Float_t getZdcAdcSumEast();
    Float_t getZdcAdcSumWest();
    Float_t getZdcAdcEast(Int_t idx);
    Float_t getZdcAdcWest(Int_t idx);
    Float_t getZdcTdcEast(Int_t idx);
    Float_t getZdcTdcWest(Int_t idx);
    Float_t getZdcSmdAdcEast(Int_t vertiHori, Int_t idx);
    Float_t getZdcSmdAdcWest(Int_t vertiHori, Int_t idx);
    Float_t getZdcVertexZ();


    // Vertex
    void setVertex(Float_t vx, Float_t vy, Float_t vz);
    Float_t getVertexX();
    Float_t getVertexY();
    Float_t getVertexZ();
    TVector3 getVertex();

    // Tracks
    void setPrimaryTrackNumber(UShort_t num);
    void setGlobalTrackNumer(UShort_t num);

    UShort_t getPrimaryTrackNumber();
    UShort_t getGlobalTrackNumer();
    UShort_t getTrackCollNumber();
    StRHICfTPCTrack* getNewTPCTrack(); // for write tpc tracks
    StRHICfTPCTrack* getTPCTrack(UInt_t idx); // for read tracks

    // FMS (photons in cluster)
    void setFmsPhoton(UChar_t category, TVector3 pos, TLorentzVector vec4);

    UInt_t getFmsPhotonNumber();
    UChar_t getFmsPhotonCategory(Int_t idx); //[0 = not fitted cluster, 1 = one photon, 2 = two photon in cluster, 3 = invalid]
    Float_t getFmsPhotonX(Int_t idx);
    Float_t getFmsPhotonY(Int_t idx);
    Float_t getFmsPhotonZ(Int_t idx);
    Float_t getFmsPhotonPx(Int_t idx);
    Float_t getFmsPhotonPy(Int_t idx);
    Float_t getFmsPhotonPz(Int_t idx);
    Float_t getFmsPhotonEnergy(Int_t idx);
    TVector3 getFmsPhotonPos(Int_t idx);
    TLorentzVector getFmsPhotonFourMomentum(Int_t idx);

    // RPS
    void setRpsInfo(UChar_t type, UChar_t branch, TVector3 trackMom, vector<TVector3> trkPointPos);

    UInt_t getRpsTrackNumber();
    UChar_t getRpsTrackType(Int_t idx);
    UChar_t getRpsTrackBranch(Int_t idx);
    Float_t getRpsTrackTheta(Int_t idx);
    Float_t getRpsTrackPhi(Int_t idx);
    Float_t getRpsTrackP(Int_t idx);
    Float_t getRpsTrackPt(Int_t idx);
    Float_t getRpsTrackEta(Int_t idx);
    TVector3 getRpsTrackMomentum(Int_t idx);
    TVector3 getRpsTrackPosition(Int_t idx, Int_t pointIdx=0);

	private:
    // ======= General data =======
		UInt_t mRunNum;
		UInt_t mEventNum; 
		UShort_t mFillNum;
		UShort_t mBunchNum;
    UChar_t mSpinBit;
		Float_t mBeamEnergy;
		Float_t mPolarization;
		Float_t mRelativeLuminosity;

    // ======= Trigger data =======
    Bool_t mIsRHICf;
		Bool_t mIsDiffractive;
		Bool_t mIsVPD;
		Bool_t mIsTPC;

    // ======= RHICf data =======
    UInt_t mRHICfRunNumber;
    UInt_t mRHICfEventNumber;
    UInt_t mRHICfTriggerNumber;
    UChar_t mRHICfRunType;
    Float_t mRHICfL90[2]; // [TS, TL]
    Bool_t mIsRHICfPi0;
    vector<StRHICfPoint*> mRHICfPointColl; // IP coor.
    StRHICfPi0* mRHICfPi0 = 0; // IP coor.

    // ======= STAR data ========

    // Multiplicity
    UShort_t mTofMultiplicity;
    UShort_t mRefMult;
    UShort_t mGRefMult;

    // BBC
    UShort_t mBbcEast[16][3]; // [pmt idx][adc, tdc, tac] 
    UShort_t mBbcLargeEast[8][3]; // [pmt idx][adc, tdc, tac] 
    UShort_t mBbcWest[16][3]; // [pmt idx][adc, tdc, tac] 
    UShort_t mBbcLargeWest[8][3]; // [pmt idx][adc, tdc, tac] 

    // VPD
    UShort_t mVpdEast[16][2]; // [pmt idx][adc, tdc] 
    UShort_t mVpdWest[16][2]; // [pmt idx][adc, tdc] 
    UShort_t mVpdEastHighThr[16][2]; // Hight Threshold [pmt idx][adc, tdc] 
    UShort_t mVpdWestHighThr[16][2]; // Hight Threshold [pmt idx][adc, tdc] 
    UShort_t mVpdEarliestTDC[2]; // [East, West]
    UShort_t mVpdEarliestTDCHighthr[2]; // [East, West]
    UShort_t mVpdTimeDiff; // vpdTimeDifference

    // ZDC 
    Float_t mZdcAdcSum[2]; // east west, Attenuated adc summation
    Float_t mZdcAdc[2][4]; // east west [unAttenuated adc sum, pmt=1, 2, 3]
    Float_t mZdcTdc[2][4]; // east west, [tdc sum , pmt= 1, 2, 3]
    Float_t mZdcSmdAdc[2][2][7]; // east west, vertical horizontal, smd= 0 ~ 6
    Float_t mZdcVertexZ;

    // vertex
    Float_t mVertex[3];

    // tracks
    UShort_t mPrimaryTrackNum;
    UShort_t mGlobalTrackNum;
    vector<StRHICfTPCTrack*> mTrackColl;

    // FMS
    vector<unsigned char> mFmsCategory; //[0 = not fitted cluster, 1 = one photon, 2 = two photon in cluster, 3 = invalid]
    vector<TVector3> mFmsPhotonPos;  // IP coor.
    vector<TLorentzVector> mFmsPhoton4Vec; // IP coor.

    // RPS
    vector<unsigned char> mRpsTrackType; // [0 = reco. only one point (local) , 1 = reco. using two point (global) , 2 = undefined]
    vector<unsigned char> mRpsTrackBranch; // Rps branch, [0 = EU, 1 = ED, 2 = WU, 3 = WD]
    vector<TVector3> mRpsMomentum; // MuRpsTrack momentum
    vector<vector<TVector3>> mRpsPos; // correspond to MuRpsTrackPoint->poinstionVec()

	ClassDef(StRHICfPi0Events,1);
};

#endif
