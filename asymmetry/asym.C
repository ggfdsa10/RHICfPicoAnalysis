#include "./source/Pi0Asymmetry.hh"

// condition name definition
void asym()
{
    gROOT->ProcessLine(".L ./source/Pi0Asymmetry.cc");

    Pi0Asymmetry* pi0Asym = new Pi0Asymmetry();
    pi0Asym -> setFile("/gpfs01/star/pwg/slee5/AnalRHICfPi0_21148.root");
    pi0Asym -> setConditionName("21148");
    pi0Asym -> setConditionName2("DDLE");
    // pi0Asym -> setEevntEndNum(100000);
    pi0Asym -> notCalculBkg();
    pi0Asym -> doAsymmetry();

    pi0Asym -> doDDLE();

    pi0Asym -> doSaveData();
    pi0Asym -> doDrawFigure();

    pi0Asym -> Init();
    pi0Asym -> Make();
    
    pi0Asym -> Finish();

    // full calculations 
    // for(int step=3; step<6; step++){
    //     Pi0Asymmetry* pi0Asym = new Pi0Asymmetry();
    //     pi0Asym -> setFile("/gpfs01/star/pwg/slee5/AnalRHICfPi0.root");
    //     pi0Asym -> setConditionName("21148");

    //     if(step==0){pi0Asym -> doFindGenMassCut();}
    //     if(step==1){pi0Asym -> doBinning();}
    //     if(step==2){pi0Asym -> doBkgEstimation();}
    //     if(step==3){pi0Asym -> doFindBinMean();}
    //     if(step==4){pi0Asym -> doDilutionFactor();}
    //     if(step==5){pi0Asym -> doAsymmtry();}

    //     // pi0Asym -> setEevntEndNum(1000); 
    //     pi0Asym -> doSaveData();
    //     // pi0Asym -> doDrawFigure();

    //     pi0Asym -> Init();
    //     pi0Asym -> Make();
    //     pi0Asym -> Finish();
    //     delete pi0Asym;
    // }


    // delete pi0Asym;
}
