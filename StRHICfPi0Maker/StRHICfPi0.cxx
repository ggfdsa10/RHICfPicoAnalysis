#include "StRHICfPi0.h"

ClassImp(StRHICfPi0)

StRHICfPi0::StRHICfPi0()
{
    Clear();
}

StRHICfPi0::~StRHICfPi0()
{
}

void StRHICfPi0::Clear(Option_t *option)
{
    mPi0Types = -1; 
    mTowerIdx = -1;
    mPosition[0] = 0.;
    mPosition[1] = 0.;
    mPosition[2] = 0.;
    mMomentum[0] = 0.;
    mMomentum[1] = 0.;
    mMomentum[2] = 0.;
    mEnergy = 0.; 
    mMass = 0.; 
    mPT = 0.;
    mXF = 0.; 
}

void StRHICfPi0::setPi0(StRHICfPi0* data)
{
    this->setType(data->getType());
    this->setPosition(data->getPosition());
    this->setMomentum(data->getMomentum());
    this->setEnergy(data->getEnergy());
    this->setMass(data->getMass());
    this->setXF(data->getXF());
}

void StRHICfPi0::setType(UChar_t type){mPi0Types = type;}
void StRHICfPi0::setTowerIdx(UChar_t idx){mTowerIdx = idx;}
void StRHICfPi0::setPosition(TVector3 pos)
{
    mPosition[0] = pos.X();
    mPosition[1] = pos.Y();
    mPosition[2] = pos.Z();
}

void StRHICfPi0::setPosition(Float_t x, Float_t y, Float_t z)
{
    mPosition[0] = x;
    mPosition[1] = y;
    mPosition[2] = z;
}

void StRHICfPi0::setMomentum(TVector3 mom)
{
    mMomentum[0] = mom.X();
    mMomentum[1] = mom.Y();
    mMomentum[2] = mom.Z();
}

void StRHICfPi0::setMomentum(Float_t px, Float_t py, Float_t pz)
{
    mMomentum[0] = px;
    mMomentum[1] = py;
    mMomentum[2] = pz;
}

void StRHICfPi0::setEnergy(Float_t e){mEnergy = e;}
void StRHICfPi0::setMass(Float_t m){mMass = m;}
void StRHICfPi0::setPT(Float_t pt){mPT = pt;}
void StRHICfPi0::setXF(Float_t xf){mXF = xf;}

UChar_t StRHICfPi0::getType(){return mPi0Types;}
UChar_t StRHICfPi0::getTowerIdx(){return mTowerIdx;}
TVector3 StRHICfPi0::getPosition()
{
    TVector3 position(mPosition[0], mPosition[1], mPosition[2]);
    return position;
}

Float_t StRHICfPi0::getPosX(){return mPosition[0];}
Float_t StRHICfPi0::getPosY(){return mPosition[1];}
Float_t StRHICfPi0::getPosZ(){return mPosition[2];}
TVector3 StRHICfPi0::getMomentum()
{
    TVector3 momentum(mMomentum[0], mMomentum[1], mMomentum[2]);
    return momentum;
}

Float_t StRHICfPi0::getMomX(){return mMomentum[0];}
Float_t StRHICfPi0::getMomY(){return mMomentum[1];}
Float_t StRHICfPi0::getMomZ(){return mMomentum[2];}
Float_t StRHICfPi0::getEnergy(){return mEnergy;}
Float_t StRHICfPi0::getMass(){return mMass;}
Float_t StRHICfPi0::getPT(){return mPT;}
Float_t StRHICfPi0::getXF(){return mXF;}
Float_t StRHICfPi0::getEta()
{
    double ptot = sqrt(mMomentum[0]*mMomentum[0] + mMomentum[1]*mMomentum[1] + mMomentum[2]*mMomentum[2]);
    double cosTheta = (ptot == 0.0) ? 1.0 : mMomentum[2]/ptot;
    if(cosTheta*cosTheta < 1){return -0.5* TMath::Log( (1.0-cosTheta)/(1.0+cosTheta) );}
    if(mMomentum[2] == 0){return 0;}
    if(mMomentum[2] > 0){return -999.;}
    else{return -999.;}
}

Float_t StRHICfPi0::getTheta(){return TMath::ATan2(sqrt(mMomentum[0]*mMomentum[0] + mMomentum[1]*mMomentum[1]),mMomentum[2]);}
Float_t StRHICfPi0::getPhi(){return TMath::ATan2(mMomentum[1], mMomentum[0]);}

