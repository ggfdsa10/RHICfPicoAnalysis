#include "StRHICfTPCTrack.h"

ClassImp(StRHICfTPCTrack)

StRHICfTPCTrack::StRHICfTPCTrack()
{
    Clear();
}

StRHICfTPCTrack::~StRHICfTPCTrack()
{
}

void StRHICfTPCTrack::Clear(Option_t *option)
{
    mIsPrimary = false;
    mChi2 = 9999;
    mStatus = 0;

    mOriginPosition[0] = -999.;
    mOriginPosition[1] = -999.;
    mOriginPosition[2] = -999.;
    mMomentum[0] = -999.;
    mMomentum[1] = -999.;
    mMomentum[2] = -999.;
    mNSigmaElectron = std::numeric_limits<short>::min();
    mNSigmaPion = std::numeric_limits<short>::min();
    mNSigmaKaon = std::numeric_limits<short>::min();
    mNSigmaProton = std::numeric_limits<short>::min();
    mProbElectron = -999.;
    mProbPion = -999.;
    mProbKaon = -999.;
    mProbProton = -999.;
    mDca3D = -999.;

    mDedx = -999.;
    mDndx = -999.;
    mNHitDedx = 0;
    mNHitFit = 0;
    mNHitsMax = 0;

    mIsBtofHit = false;
    mBTofMatchFlag = -1;  
    mBtofTOF = -999.;
    mBtofBeta = -999.;
    mBtofNSigmaElectron = std::numeric_limits<short>::min();
    mBtofNSigmaPion = std::numeric_limits<short>::min();
    mBtofNSigmaKaon = std::numeric_limits<short>::min();
    mBtofNSigmaProton = std::numeric_limits<short>::min();

    mIsEtofHit = false;
    mETofMatchFlag = -1;  
    mEtofTOF = -999.;
    mEtofBeta = -999.;

    mIsMtdHit = false;
    mMtdMatchFlag = -1;  
    mMtdDeltaTOF = -999.;
    mMtdBeta = -999.;
}

// track information
void StRHICfTPCTrack::setIsPrimary(){mIsPrimary = true;}
void StRHICfTPCTrack::setChi2(UShort_t chi2){mChi2 = chi2;}
void StRHICfTPCTrack::setStatus(Char_t val){mStatus = val;}

void StRHICfTPCTrack::setOriginPos(Float_t x, Float_t y, Float_t z)
{
    mOriginPosition[0]= x;
    mOriginPosition[1]= y;
    mOriginPosition[2]= z;
}

void StRHICfTPCTrack::setMomentum(Float_t px, Float_t py, Float_t pz)
{
    mMomentum[0] = px;  
    mMomentum[1] = py;  
    mMomentum[2] = pz;  
}

void StRHICfTPCTrack::setSigmaElectron(Float_t sigma)
{
    mNSigmaElectron = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ? 
        ( (sigma > 0) ? std::numeric_limits<short>::max() : 
        std::numeric_limits<short>::min() ) : 
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

void StRHICfTPCTrack::setSigmaPion(Float_t sigma)
{
    mNSigmaPion = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}
void StRHICfTPCTrack::setSigmaKaon(Float_t sigma)
{
    mNSigmaKaon = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

void StRHICfTPCTrack::setSigmaProton(Float_t sigma)
{
    mNSigmaProton = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

void StRHICfTPCTrack::setProbElectron(Float_t prob){mProbElectron = prob;}
void StRHICfTPCTrack::setProbPion(Float_t prob){mProbPion = prob;}
void StRHICfTPCTrack::setProbKaon(Float_t prob){mProbKaon = prob;}
void StRHICfTPCTrack::setProbProton(Float_t prob){mProbProton = prob;}
void StRHICfTPCTrack::setDca3D(Float_t val){mDca3D = val;}

Bool_t StRHICfTPCTrack::isPrimary(){return mIsPrimary;}
UShort_t StRHICfTPCTrack::getChi2(){return mChi2;}
Char_t StRHICfTPCTrack::getStatus(){return mStatus;}
Float_t StRHICfTPCTrack::getOriginPosX(){return mOriginPosition[0];}
Float_t StRHICfTPCTrack::getOriginPosY(){return mOriginPosition[1];}
Float_t StRHICfTPCTrack::getOriginPosZ(){return mOriginPosition[2];}
TVector3 StRHICfTPCTrack::getOriginPos()
{
    TVector3 oritinPos(mOriginPosition[0], mOriginPosition[1], mOriginPosition[2]);
    return oritinPos;
}

Float_t StRHICfTPCTrack::getMomX(){return mMomentum[0];}
Float_t StRHICfTPCTrack::getMomY(){return mMomentum[1];}
Float_t StRHICfTPCTrack::getMomZ(){return mMomentum[2];}
TVector3 StRHICfTPCTrack::getMomentum()
{
    TVector3 momentum(mMomentum[0], mMomentum[1], mMomentum[2]);
    return momentum;
}

Char_t StRHICfTPCTrack::getPID()
{
    // test method
    Char_t pid = -1;
    Float_t tmpSigma = (Float_t)std::numeric_limits<short>::max() / 1000.f;
    if(fabs(getSigmaElectron()) < fabs(tmpSigma)){
        tmpSigma = getSigmaElectron();
        if(getCharge() > 0){pid = positron;}
        if(getCharge() < 0){pid = electron;}
    }
    if(fabs(getSigmaPion()) < fabs(tmpSigma)){
        tmpSigma = getSigmaPion();
        if(getCharge() > 0){pid = plusPion;}
        if(getCharge() < 0){pid = minusPion;}
    }
    if(fabs(getSigmaKaon()) < fabs(tmpSigma)){
        tmpSigma = getSigmaKaon();
        if(getCharge() > 0){pid = plusKaon;}
        if(getCharge() < 0){pid = minusKaon;}
    }
    if(fabs(getSigmaProton()) < fabs(tmpSigma)){
        tmpSigma = getSigmaProton();
        if(getCharge() > 0){pid = proton;}
        if(getCharge() < 0){pid = antiProton;}
    }

    return pid;
}

Float_t StRHICfTPCTrack::getPt(){return sqrt(mMomentum[0]*mMomentum[0] + mMomentum[1]*mMomentum[1]);}
Float_t StRHICfTPCTrack::getEta()
{
    double ptot = sqrt(mMomentum[0]*mMomentum[0] + mMomentum[1]*mMomentum[1] + mMomentum[2]*mMomentum[2]);
    double cosTheta = (ptot == 0.0) ? 1.0 : mMomentum[2]/ptot;
    if(cosTheta*cosTheta < 1){return -0.5* TMath::Log( (1.0-cosTheta)/(1.0+cosTheta) );}
    if(mMomentum[2] == 0){return 0;}
    if(mMomentum[2] > 0){return -999.;}
    else{return -999.;}
}

Char_t StRHICfTPCTrack::getCharge(){return (mNHitFit > 0) ? 1 : -1;}
Float_t StRHICfTPCTrack::getSigmaElectron(){return (Float_t)mNSigmaElectron / 1000.f;}
Float_t StRHICfTPCTrack::getSigmaPion(){return (Float_t)mNSigmaPion / 1000.f;}
Float_t StRHICfTPCTrack::getSigmaKaon(){return (Float_t)mNSigmaKaon / 1000.f;}
Float_t StRHICfTPCTrack::getSigmaProton(){return (Float_t)mNSigmaProton / 1000.f;}
Float_t StRHICfTPCTrack::getProbElectron(){return mProbElectron;}
Float_t StRHICfTPCTrack::getProbPion(){return mProbPion;}
Float_t StRHICfTPCTrack::getProbKaon(){return mProbKaon;}
Float_t StRHICfTPCTrack::getProbProton(){return mProbProton;}
Float_t StRHICfTPCTrack::getDca3D(){return mDca3D;}

// hit information in track
void StRHICfTPCTrack::setDedx(Float_t val){mDedx = val;}
void StRHICfTPCTrack::setDndx(Float_t val){mDndx = val;}
void StRHICfTPCTrack::setnHitDedx(Short_t val){mNHitDedx = val;}
void StRHICfTPCTrack::setnHitFit(Short_t val){mNHitFit = val;}
void StRHICfTPCTrack::setnHitMax(Short_t val){mNHitsMax = val;}

Float_t StRHICfTPCTrack::getDedx(){return mDedx;}
Float_t StRHICfTPCTrack::getDndx(){return mDndx;}
Short_t StRHICfTPCTrack::getnHitDedx(){return mNHitDedx;}
Short_t StRHICfTPCTrack::getnHitFit(){return mNHitFit;}
Short_t StRHICfTPCTrack::getnHitMax(){return mNHitsMax;}

void StRHICfTPCTrack::setIsBtofHit(){mIsBtofHit = true;}
void StRHICfTPCTrack::setBtofMatchFlag(Char_t flag){mBTofMatchFlag = flag;}
void StRHICfTPCTrack::setBtofTOF(Float_t val){mBtofTOF = val;}
void StRHICfTPCTrack::setBtofBeta(Float_t val){mBtofBeta = val;}
void StRHICfTPCTrack::setBtofSigmaElectron(Float_t sigma)
{
    mBtofNSigmaElectron = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

void StRHICfTPCTrack::setBtofSigmaPion(Float_t sigma)
{
    mBtofNSigmaPion = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

void StRHICfTPCTrack::setBtofSigmaKaon(Float_t sigma)
{
    mBtofNSigmaKaon = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

void StRHICfTPCTrack::setBtofSigmaProton(Float_t sigma)
{
    mBtofNSigmaProton = ( fabs(sigma * 1000.) > std::numeric_limits<short>::max() ?
        ( (sigma > 0) ? std::numeric_limits<short>::max() :
        std::numeric_limits<short>::min() ) :
        (Short_t)( TMath::Nint( sigma * 1000. ) ) );
}

Bool_t StRHICfTPCTrack::isBtofHit(){return mIsBtofHit;}
Char_t StRHICfTPCTrack::getBtofMatchFlag(){return mBTofMatchFlag;}
Float_t StRHICfTPCTrack::getBtofTOF(){return mBtofTOF;}
Float_t StRHICfTPCTrack::getBtofBeta(){return mBtofBeta;}
Float_t StRHICfTPCTrack::getBtofSigmaElectron(){return (Float_t)mBtofNSigmaElectron / 1000.f;}
Float_t StRHICfTPCTrack::getBtofSigmaPion(){return (Float_t)mBtofNSigmaPion / 1000.f;}
Float_t StRHICfTPCTrack::getBtofSigmaKaon(){return (Float_t)mBtofNSigmaKaon / 1000.f;}
Float_t StRHICfTPCTrack::getBtofSigmaProton(){return (Float_t)mBtofNSigmaProton / 1000.f;}

// etof traits
void StRHICfTPCTrack::setIsEtofHit(){mIsEtofHit = true;}
void StRHICfTPCTrack::setEtofMatchFlag(Char_t flag){mETofMatchFlag =flag;}
void StRHICfTPCTrack::setEtofTOF(Float_t val){mEtofTOF = val;}
void StRHICfTPCTrack::setEtofBeta(Float_t val){mEtofBeta = val;}

Bool_t StRHICfTPCTrack::isEtofHit(){return mIsEtofHit;}
Char_t StRHICfTPCTrack::getEtofMatchFlag(){return mETofMatchFlag;}
Float_t StRHICfTPCTrack::getEtofTOF(){return mEtofTOF;}
Float_t StRHICfTPCTrack::getEtofBeta(){return mEtofBeta;}

// mtd traits
void StRHICfTPCTrack::setIsMtdHit(){mIsMtdHit = true;}
void StRHICfTPCTrack::setMtdMatchFlag(Char_t flag){mMtdMatchFlag = flag;}
void StRHICfTPCTrack::setMtdDeltaTOF(Float_t val){mMtdDeltaTOF = val;}
void StRHICfTPCTrack::setMtdBeta(Float_t val){mMtdBeta = val;}

Bool_t StRHICfTPCTrack::isMtdHit(){return mIsMtdHit;}
Char_t StRHICfTPCTrack::getMtdMatchFlag(){return mMtdMatchFlag;}
Float_t StRHICfTPCTrack::getMtdDeltaTOF(){return mMtdDeltaTOF;}
Float_t StRHICfTPCTrack::getMtdBeta(){return mMtdBeta;}
