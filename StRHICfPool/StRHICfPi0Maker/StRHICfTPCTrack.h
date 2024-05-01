#ifndef StRHICfTPCTrack_HH
#define StRHICfTPCTrack_HH

#include <TObject.h>
#include "TVector3.h"
#include "TMath.h"

class StRHICfTPCTrack : public TObject
{
    enum pidFlag
    {
        electron = 0,
        positron = 1,
        plusPion = 2,
        minusPion = 3,
        plusKaon = 4,
        minusKaon = 5,
        proton = 6,
        antiProton = 7
    };

    public: 
        StRHICfTPCTrack();
        ~StRHICfTPCTrack();

        virtual void Clear(Option_t *option = "");

        // track information
        void setIsPrimary();
        void setChi2(UShort_t chi2);
        void setStatus(Char_t val);
        void setOriginPos(Float_t x, Float_t y, Float_t z);
        void setMomentum(Float_t px, Float_t py, Float_t pz);
        void setSigmaElectron(Float_t sigma);
        void setSigmaPion(Float_t sigma);
        void setSigmaKaon(Float_t sigma);
        void setSigmaProton(Float_t sigma);
        void setProbElectron(Float_t prob);
        void setProbPion(Float_t prob);
        void setProbKaon(Float_t prob);
        void setProbProton(Float_t prob);
        void setDca3D(Float_t val);

        Bool_t isPrimary();
        UShort_t getChi2();
        Char_t getStatus();
        Float_t getOriginPosX();
        Float_t getOriginPosY();
        Float_t getOriginPosZ();
        TVector3 getOriginPos();
        Float_t getMomX();
        Float_t getMomY();
        Float_t getMomZ();
        TVector3 getMomentum();

        Char_t getPID();
        Float_t getPt();
        Float_t getEta();

        Char_t getCharge();
        Float_t getSigmaElectron();
        Float_t getSigmaPion();
        Float_t getSigmaKaon();
        Float_t getSigmaProton();
        Float_t getProbElectron();
        Float_t getProbPion();
        Float_t getProbKaon();
        Float_t getProbProton();
        Float_t getDca3D();

        // hit information in track
        void setDedx(Float_t val);
        void setDndx(Float_t val);
        void setnHitDedx(Short_t val);
        void setnHitFit(Short_t val);
        void setnHitMax(Short_t val);

        Float_t getDedx();
        Float_t getDndx();
        Short_t getnHitDedx();
        Short_t getnHitFit();
        Short_t getnHitMax();

        // btof traits
        void setIsBtofHit();
        void setBtofMatchFlag(Char_t flag);
        void setBtofTOF(Float_t val);
        void setBtofBeta(Float_t val);
        void setBtofSigmaElectron(Float_t val);
        void setBtofSigmaPion(Float_t val);
        void setBtofSigmaKaon(Float_t val);
        void setBtofSigmaProton(Float_t val);

        Bool_t isBtofHit();
        Char_t getBtofMatchFlag();
        Float_t getBtofTOF();
        Float_t getBtofBeta();
        Float_t getBtofSigmaElectron();
        Float_t getBtofSigmaPion();
        Float_t getBtofSigmaKaon();
        Float_t getBtofSigmaProton();

        // etof traits
        void setIsEtofHit();
        void setEtofMatchFlag(Char_t flag);
        void setEtofTOF(Float_t val);
        void setEtofBeta(Float_t val);

        Bool_t isEtofHit();
        Char_t getEtofMatchFlag();
        Float_t getEtofTOF();
        Float_t getEtofBeta();

        // etof traits
        void setIsMtdHit();
        void setMtdMatchFlag(Char_t flag);
        void setMtdDeltaTOF(Float_t val);
        void setMtdBeta(Float_t val);

        Bool_t isMtdHit();
        Char_t getMtdMatchFlag();
        Float_t getMtdDeltaTOF();
        Float_t getMtdBeta();

    private:
        Bool_t mIsPrimary;
        UShort_t mChi2;  // Chi2 of the track (encoding = chi2*1000)
        Char_t mStatus; // Checks if the track was fitted to any vertex, 0 = not fitted, 1 = fitted
        
        Float_t mOriginPosition[3];
        Float_t mMomentum[3];

        Short_t mNSigmaElectron;
        Short_t mNSigmaPion;
        Short_t mNSigmaKaon;
        Short_t mNSigmaProton;

        Float_t mProbElectron;
        Float_t mProbPion;
        Float_t mProbKaon;
        Float_t mProbProton;

        Float_t mDca3D;
        Float_t mDedx;
        Float_t mDndx;

        Short_t mNHitDedx;
        Short_t mNHitFit;
        Short_t mNHitsMax;

        Bool_t mIsBtofHit;
        Char_t mBTofMatchFlag;  /// 0 - no match, 1 - one-to-one, 2 - one-to-multiple
        Float_t mBtofTOF;
        Float_t mBtofBeta;
        Short_t mBtofNSigmaElectron;
        Short_t mBtofNSigmaPion;
        Short_t mBtofNSigmaKaon;
        Short_t mBtofNSigmaProton;

        Bool_t mIsEtofHit;
        Char_t mETofMatchFlag;  /// 0 - no match, 1 - one-to-one, 2 - one-to-multiple
        Float_t mEtofTOF;
        Float_t mEtofBeta;
 
        Bool_t mIsMtdHit;
        Char_t mMtdMatchFlag;  /// 0 - no match, 1 - one-to-one, 2 - one-to-multiple
        Float_t mMtdDeltaTOF;
        Float_t mMtdBeta;

    ClassDef(StRHICfTPCTrack,1);
};

#endif
