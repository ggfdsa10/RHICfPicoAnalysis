#include "./source/testPi0Asymmetry.hh"

// condition name definition
void testAsym()
{
    gROOT->ProcessLine(".L ./source/testPi0Asymmetry.cc");

    testPi0Asymmetry* pi0Asym = new testPi0Asymmetry();
    pi0Asym -> setFile("/gpfs01/star/pwg/slee5/AnalRHICfPi0_21148.root");
    pi0Asym -> setConditionName("test21148");

    pi0Asym -> doSDLE();
    pi0Asym -> setConditionName2("SDLE2Thr");

    pi0Asym -> doAsymmetry();

    pi0Asym -> doSaveData();
    pi0Asym -> doDrawFigure();

    pi0Asym -> Init();
    pi0Asym -> Make();
    pi0Asym -> Finish();

    // full calculations 
    // for(int step=3; step<4; step++){
    //     testPi0Asymmetry* pi0Asym = new testPi0Asymmetry();
    //     pi0Asym -> setFile("/gpfs01/star/pwg/slee5/AnalRHICfPi0_21148.root");
    //     pi0Asym -> setConditionName("test21148");
    //     // pi0Asym -> setEevntEndNum(50000);
    //     // pi0Asym -> doSDLE();
    //     // pi0Asym -> setConditionName2("woBBCLEtof2");

    //     // if(step==0){pi0Asym -> doFindGenMassCut();}
    //     if(step==1){pi0Asym -> doFindBinMean();}
    //     if(step==2){pi0Asym -> doDilutionFactor();}
    //     if(step==3){pi0Asym -> doAsymmetry();}

    //     pi0Asym -> doSaveData();
    //     pi0Asym -> doDrawFigure();

    //     pi0Asym -> Init();
    //     pi0Asym -> Make();
    //     pi0Asym -> Finish();
    //     delete pi0Asym;
    // }


    // delete pi0Asym;
}
