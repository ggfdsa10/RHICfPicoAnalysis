#include "./source/testNeutronAsymmetry.hh"

// condition name definition
void neuTestAsym()
{
    gROOT->ProcessLine(".L ./source/testNeutronAsymmetry.cc");

    testNeutronAsymmetry* neuAsym = new testNeutronAsymmetry();
    neuAsym -> setFile("/gpfs01/star/pwg/slee5/AnalRHICfPi0_21148.root");
    neuAsym -> setConditionName("test21148");

    neuAsym -> doDMLE();
    neuAsym -> setConditionName2("HMLE2Thr");

    // neuAsym -> doFindBinMean();
    neuAsym -> doAsymmetry();

    neuAsym -> doSaveData();
    neuAsym -> doDrawFigure();

    neuAsym -> Init();
    neuAsym -> Make();
    neuAsym -> Finish();

    // full calculations 
    // for(int step=0; step<3; step++){
    //     testNeutronAsymmetry* neuAsym = new testNeutronAsymmetry();
    //     neuAsym -> setFile("/gpfs01/star/pwg/slee5/AnalRHICfPi0_21148.root");
    //     neuAsym -> setConditionName("test21148");
    //     // neuAsym -> setEevntEndNum(50000);
    //     // neuAsym -> doSDLE();
    //     neuAsym -> setConditionName2("ALL");

    //     if(step==0){neuAsym -> doFindBinMean();}
    //     if(step==1){neuAsym -> doDilutionFactor();}
    //     if(step==2){neuAsym -> doAsymmetry();}

    //     neuAsym -> doSaveData();
    //     neuAsym -> doDrawFigure();

    //     neuAsym -> Init();
    //     neuAsym -> Make();
    //     neuAsym -> Finish();
    //     delete neuAsym;
    // }


    // delete neuAsym;
}
