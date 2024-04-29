#ifndef StRHICfPi0_HH
#define StRHICfPi0_HH

#include <TObject.h>
#include "TVector3.h"
#include "TMath.h"

class StRHICfPi0 : public TObject
{
    public: 
        StRHICfPi0();
        ~StRHICfPi0();

        virtual void Clear(Option_t *option = "");

        void setPi0(StRHICfPi0* data);
        void setType(UChar_t type);
        void setTowerIdx(UChar_t idx);
        void setPosition(TVector3 pos);
        void setPosition(Float_t x, Float_t y, Float_t z);
        void setMomentum(TVector3 mom);
        void setMomentum(Float_t px, Float_t py, Float_t pz);
        void setEnergy(Float_t e);
        void setMass(Float_t m);
        void setPT(Float_t pt);
        void setXF(Float_t xf);

        UChar_t getType(); 
        UChar_t getTowerIdx();
        TVector3 getPosition();
        Float_t getPosX();
        Float_t getPosY();
        Float_t getPosZ();
        TVector3 getMomentum();
        Float_t getMomX();
        Float_t getMomY();
        Float_t getMomZ();
        Float_t getEnergy();
        Float_t getMass();
        Float_t getPT();
        Float_t getXF();
        Float_t getEta();
        Float_t getTheta();
        Float_t getPhi();

    private:
        UChar_t mPi0Types; // 1: Pi0 type1, 2: Pi0 type2
        UChar_t mTowerIdx; // only type2 pi0.
        Float_t mPosition[3]; // at the RHICf detector surface
        Float_t mMomentum[3]; // at IP coor.
        Float_t mEnergy; // at IP coor.
        Float_t mMass; // invariant mass [MeV/c^2]
        Float_t mPT; // Transverse momentum at IP coor.
        Float_t mXF; // momentum fraction at IP coor.
        Bool_t mBkgFlag;

    ClassDef(StRHICfPi0,1);
};

#endif
