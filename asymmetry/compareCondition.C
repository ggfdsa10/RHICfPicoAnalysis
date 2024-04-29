#include "TGraphErrors.h"

void forPi0();
void forNeutron();

void compareCondition()
{
    // forPi0();
    forNeutron();
}

void forPi0(){
    TString fileCondName = "test21148";
    bool isLittleShift = true;
    bool isCheckEventCount = false;

    int colorIdx[8] = {1, 2, 8, 4, 95, 51, 67, 91};
    int markerStyleIdx[4] = {20, 21, 22, 23};
    double anDrawRange[2] = {-0.075, 0.245};

    const int numberOfConditions = 5;
    TString DiffModeType = "All"; // NDLE, SDLE, DDLE, DMLE
    TString subCondiType = "";    // See the diffractive event log 

    TString condiNameArr[numberOfConditions] = {
        "NDLE3Thr",
        "SDLE2Thr",
        "DDLE2Thr",
        "LMLE2Thr",
        "HMLE2Thr"
    };

    TString condiLegendArr[numberOfConditions] = {
        "NDLE",
        "SDLE",
        "DDLE",
        "LMLE",
        "HMLE"
    };

    TFile* file_All = new TFile(Form("./data/asymmetry_%s_ALL.root", fileCondName.Data()),"read");
    TGraphErrors* asymAll = (TGraphErrors*)file_All -> Get("GeneralAsymPtAllXf;1");
    TGraphErrors* asymAllType2 = (TGraphErrors*)file_All -> Get("GeneralAsymPtAllXf;2");

    TGraphErrors* asymAllXf = (TGraphErrors*)file_All -> Get("GeneralAsymXfAllPt;1");
    TGraphErrors* asymAllXfType2 = (TGraphErrors*)file_All -> Get("GeneralAsymXfAllPt;2");

    TFile* file_condi[numberOfConditions];
    TGraphErrors* asymType1Condi[numberOfConditions];
    TGraphErrors* asymType2Condi[numberOfConditions];

    TGraphErrors* asymXfType1Condi[numberOfConditions];
    TGraphErrors* asymXfType2Condi[numberOfConditions];

    bool isXfAsym = true;

    for(int i=0; i<numberOfConditions; i++){
        file_condi[i] = new TFile(Form("./data/asymmetry_%s_%s.root", fileCondName.Data(), condiNameArr[i].Data()),"read");
        asymType1Condi[i] = (TGraphErrors*)file_condi[i] -> Get("GeneralAsymPtAllXf;1");
        asymType2Condi[i] = (TGraphErrors*)file_condi[i] -> Get("GeneralAsymPtAllXf;2");
        
        asymXfType1Condi[i] = (TGraphErrors*)file_condi[i] -> Get("GeneralAsymXfAllPt;1");
        asymXfType2Condi[i] = (TGraphErrors*)file_condi[i] -> Get("GeneralAsymXfAllPt;2");
        if(!asymXfType1Condi[i]){isXfAsym = false;}
    }

    Double_t EventRatio[numberOfConditions];
    TTree* treeForCounts[numberOfConditions];

    for(int i=0; i < numberOfConditions; i++){
        EventRatio[i] = 0.;

        Int_t pi0Count;
        Int_t selectedCount;

        treeForCounts[i] = (TTree*)file_condi[i] -> Get("count");
        treeForCounts[i] -> SetBranchAddress("pi0Count", &pi0Count);
        treeForCounts[i] -> SetBranchAddress("SelectCount", &selectedCount);
        treeForCounts[i] -> GetEntry(0);

        EventRatio[i] = double(selectedCount)/double(pi0Count)*100.;

        cout << i << " " << condiNameArr[i].Data() << " pi0Event: " << pi0Count << " selectedEvent: " << selectedCount << " ratio: " << double(selectedCount)/double(pi0Count)*100. << endl;
    }





    auto c1 = new TCanvas("","",1250,600);
    c1 ->Divide(2,1);

    c1 -> cd(1);
    gPad -> SetGrid(0,0);
    TString DrawOpt = "p";

    TGraph* tmpGraph = new TGraph();
    tmpGraph -> SetPoint(0, 0., -0.04);
    tmpGraph -> SetPoint(1, 0.7, 0.25);
    tmpGraph -> SetMarkerSize(0);
    tmpGraph -> SetMarkerStyle(20);
    tmpGraph -> SetLineWidth(0);
    tmpGraph -> GetYaxis() -> SetRangeUser(anDrawRange[0], anDrawRange[1]); 
    tmpGraph -> GetXaxis() -> SetRangeUser(0., 0.55);
    tmpGraph -> SetTitle("; p_{T} [GeV/c]; A_{N}");
    tmpGraph -> Draw("ap");

    if(!asymAll){cout <<"no " << endl;}
    asymAll -> SetMarkerSize(1.3);
    asymAll -> SetMarkerStyle(markerStyleIdx[0]);
    asymAll -> SetMarkerColor(colorIdx[0]);
    asymAll -> SetLineColor(colorIdx[0]);
    asymAll -> SetLineWidth(2);
    asymAll -> Draw(Form("same, %s",DrawOpt.Data()));

    asymAllType2 -> SetMarkerSize(1.3);
    asymAllType2 -> SetMarkerStyle(markerStyleIdx[0]);
    asymAllType2 -> SetMarkerColor(colorIdx[0]);
    asymAllType2 -> SetLineColor(colorIdx[0]);
    asymAllType2 -> SetLineWidth(2);
    asymAllType2 -> Draw(Form("same, %s",DrawOpt.Data()));

    for(int i=0; i<numberOfConditions; i++){

        if(isLittleShift == true){
            double shiftPoint = 0.002*double(i+1);
            for(int p=0; p<asymType1Condi[i] -> GetN(); p++){
                double pt, an;
                asymType1Condi[i] -> GetPoint(p, pt, an);
                asymType1Condi[i] -> SetPoint(p, pt+shiftPoint, an);
            }
            double ptT2, anT2;
            asymType2Condi[i] -> GetPoint(0, ptT2, anT2);
            asymType2Condi[i] -> SetPoint(0, ptT2+shiftPoint, anT2); 
        }

        int markerStyleNum = 0;
        int markerColorNum = 0;
        double markerSize = 1.3;
        if(condiLegendArr[i].Index("ND") != -1){
            markerStyleNum = markerStyleIdx[1]; 
            markerColorNum = colorIdx[1];
        }
        if(condiLegendArr[i].Index("SD") != -1 || condiLegendArr[i].Index("DD") != -1){
            markerStyleNum = markerStyleIdx[2];
            markerSize = 1.5;
            if(condiLegendArr[i].Index("SD") != -1){markerColorNum = colorIdx[2];}
            else{markerColorNum = colorIdx[3];}   
        }

        if(condiLegendArr[i].Index("LM") != -1 || condiLegendArr[i].Index("HM") != -1){
            markerStyleNum = markerStyleIdx[3]; 
            markerSize = 1.5;

            if(condiLegendArr[i].Index("LM") != -1){markerColorNum = colorIdx[4];}
            else{markerColorNum = colorIdx[5];}   
        }
        

        asymType1Condi[i] -> SetMarkerSize(markerSize);
        asymType1Condi[i] -> SetMarkerStyle(markerStyleNum);
        asymType1Condi[i] -> SetMarkerColor(markerColorNum);
        asymType1Condi[i] -> SetLineColor(markerColorNum);
        asymType1Condi[i] -> SetLineWidth(2);
        asymType1Condi[i] -> Draw(Form("same, %s",DrawOpt.Data()));

        asymType2Condi[i] -> SetMarkerSize(markerSize);
        asymType2Condi[i] -> SetMarkerStyle(markerStyleNum);
        asymType2Condi[i] -> SetMarkerColor(markerColorNum);
        asymType2Condi[i] -> SetLineColor(markerColorNum);
        asymType2Condi[i] -> SetLineWidth(2);
        asymType2Condi[i] -> Draw(Form("same, %s",DrawOpt.Data()));
    }

    TLatex* anLatex = new TLatex();
    anLatex -> SetTextSize(0.04);
    anLatex -> DrawLatexNDC(0.4, 0.15, "p^{#uparrow}+p #rightarrow #pi^{0} + X, #sqrt{s} = 510 GeV");
    anLatex -> DrawLatexNDC(0.67, 0.85, "TS Run");
    anLatex -> DrawLatexNDC(0.67, 0.8, "Fill 21148");
    anLatex -> DrawLatexNDC(0.67, 0.75, "6 < #eta");
    anLatex -> DrawLatexNDC(0.67, 0.7, "0 < x_{F} < 1");

    if(isCheckEventCount){
        for(int i=0; i<numberOfConditions; i++){
            anLatex -> SetTextSize(0.025);
            anLatex -> DrawLatexNDC(0.67, 0.4-double(i)*0.035, Form("cond%i ratio = %.2f %", i+1, EventRatio[i]));
        }
    }

    anLatex -> SetTextSize(0.03);
    anLatex -> Draw("same");

    TLine* dashLine = new TLine(0., 0., 0.548, 0.);
    dashLine -> SetLineStyle(2);
    dashLine -> Draw("same");

    TLegend* leg = new TLegend(0.13, 0.7, 0.45, 0.88);
    leg -> SetBorderSize(0);
    leg -> SetTextSize(0.025);

    leg -> AddEntry(asymAll, "All events", "p");
    for(int i=0; i<numberOfConditions; i++){
        leg -> AddEntry(asymType1Condi[i], Form("%s", condiLegendArr[i].Data()), "p");
    }
    leg -> Draw("same");


    // =============== for Xf ====================
    c1 -> cd(2);
    gPad -> SetGrid(0,0);
    TString DrawOpt = "p";

    TGraph* tmpGraphXf = new TGraph();
    tmpGraphXf -> SetPoint(0, 0., -0.04);
    tmpGraphXf -> SetPoint(1, 1., 0.25);
    tmpGraphXf -> SetMarkerSize(0);
    tmpGraphXf -> SetMarkerStyle(20);
    tmpGraphXf -> SetLineWidth(0);
    tmpGraphXf -> GetYaxis() -> SetRangeUser(anDrawRange[0], anDrawRange[1]); 
    tmpGraphXf -> GetXaxis() -> SetRangeUser(0.15, 1.);
    tmpGraphXf -> SetTitle("; x_{F}; A_{N}");
    tmpGraphXf -> Draw("ap");

    if(!asymAllXf){cout <<" no " << endl;}
    asymAllXf -> SetMarkerSize(1.3);
    asymAllXf -> SetMarkerStyle(markerStyleIdx[0]);
    asymAllXf -> SetMarkerColor(colorIdx[0]);
    asymAllXf -> SetLineColor(colorIdx[0]);
    asymAllXf -> SetLineWidth(2);
    asymAllXf -> Draw(Form("same, %s",DrawOpt.Data()));

    asymAllXfType2 -> SetMarkerSize(1.3);
    asymAllXfType2 -> SetMarkerStyle(markerStyleIdx[0]);
    asymAllXfType2 -> SetMarkerColor(colorIdx[0]);
    asymAllXfType2 -> SetLineColor(colorIdx[0]);
    asymAllXfType2 -> SetLineWidth(2);
    asymAllXfType2 -> Draw(Form("same, %s",DrawOpt.Data()));

    if(isXfAsym == true){
        for(int i=0; i<numberOfConditions; i++){

            if(isLittleShift == true){
                double shiftPoint = 0.002*double(i+1);
                for(int p=0; p<asymXfType1Condi[i] -> GetN(); p++){
                    double pt, an;
                    asymXfType1Condi[i] -> GetPoint(p, pt, an);
                    asymXfType1Condi[i] -> SetPoint(p, pt+shiftPoint, an);
                }

                for(int p=0; p<asymXfType2Condi[i] -> GetN(); p++){
                    double ptT2, anT2;
                    asymXfType2Condi[i] -> GetPoint(p, ptT2, anT2);
                    asymXfType2Condi[i] -> SetPoint(p, ptT2+shiftPoint, anT2); 
                }
            }

            int markerStyleNum = 0;
            int markerColorNum = 0;
            double markerSize = 1.3;
            if(condiLegendArr[i].Index("ND") != -1){
                markerStyleNum = markerStyleIdx[1]; 
                markerColorNum = colorIdx[1];
            }
            if(condiLegendArr[i].Index("SD") != -1 || condiLegendArr[i].Index("DD") != -1){
                markerStyleNum = markerStyleIdx[2];
                markerSize = 1.5;
                if(condiLegendArr[i].Index("SD") != -1){markerColorNum = colorIdx[2];}
                else{markerColorNum = colorIdx[3];}   
            }

            if(condiLegendArr[i].Index("LM") != -1 || condiLegendArr[i].Index("HM") != -1){
                markerStyleNum = markerStyleIdx[3]; 
                markerSize = 1.5;

                if(condiLegendArr[i].Index("LM") != -1){markerColorNum = colorIdx[4];}
                else{markerColorNum = colorIdx[5];}   
            }
        
            asymXfType1Condi[i] -> SetMarkerSize(markerSize);
            asymXfType1Condi[i] -> SetMarkerStyle(markerStyleNum);
            asymXfType1Condi[i] -> SetMarkerColor(markerColorNum);
            asymXfType1Condi[i] -> SetLineColor(markerColorNum);
            asymXfType1Condi[i] -> SetLineWidth(2);
            asymXfType1Condi[i] -> Draw(Form("same, %s",DrawOpt.Data()));

            asymXfType2Condi[i] -> SetMarkerSize(markerSize);
            asymXfType2Condi[i] -> SetMarkerStyle(markerStyleNum);
            asymXfType2Condi[i] -> SetMarkerColor(markerColorNum);
            asymXfType2Condi[i] -> SetLineColor(markerColorNum);
            asymXfType2Condi[i] -> SetLineWidth(2);
            asymXfType2Condi[i] -> Draw(Form("same, %s",DrawOpt.Data()));
        }
    }

    TLatex* anLatex = new TLatex();
    anLatex -> SetTextSize(0.04);
    anLatex -> DrawLatexNDC(0.4, 0.15, "p^{#uparrow}+p #rightarrow #pi^{0} + X, #sqrt{s} = 510 GeV");
    anLatex -> DrawLatexNDC(0.67, 0.85, "TS Run");
    anLatex -> DrawLatexNDC(0.67, 0.8, "Fill 21148");
    anLatex -> DrawLatexNDC(0.67, 0.75, "6 < #eta");
    anLatex -> DrawLatexNDC(0.67, 0.7, "0 < p_{T} < 1");

    if(isCheckEventCount){
        for(int i=0; i<numberOfConditions; i++){
            anLatex -> SetTextSize(0.025);
            anLatex -> DrawLatexNDC(0.67, 0.4-double(i)*0.035, Form("cond%i ratio = %.2f %", i+1, EventRatio[i]));
        }
    }

    anLatex -> SetTextSize(0.03);
    anLatex -> Draw("same");

    TLine* dashLine = new TLine(0.15, 0., 1., 0.);
    dashLine -> SetLineStyle(2);
    dashLine -> Draw("same");

    TLegend* leg = new TLegend(0.13, 0.7, 0.45, 0.88);
    leg -> SetBorderSize(0);
    leg -> SetTextSize(0.025);

    leg -> AddEntry(asymAll, "All events", "p");
    if(isXfAsym == true){
        for(int i=0; i<numberOfConditions; i++){
            leg -> AddEntry(asymXfType1Condi[i], Form("%s", condiLegendArr[i].Data()), "p");
        }
    }
    leg -> Draw("same");


    c1 -> Draw();
    TString saveName = "./Asym_pi0"+DiffModeType+subCondiType+".pdf";
    c1 -> SaveAs(Form("%s", saveName.Data()));

}



// ====================================== for Neutron Asymmetry ===============================================
// ====================================== for Neutron Asymmetry ===============================================
// ====================================== for Neutron Asymmetry ===============================================

void forNeutron(){
    TString fileCondName = "test21148";
    bool isLittleShift = true;
    bool isCheckEventCount = false;

    int colorIdx[8] = {1, 2, 8, 4, 95, 51, 67, 91};
    int markerStyleIdx[4] = {20, 21, 22, 23};
    double anDrawRange[2] = {-0.18, 0.12};

    const int numberOfConditions = 5;
    TString DiffModeType = "All"; // NDLE, SDLE, DDLE, DMLE
    TString subCondiType = "";    // See the diffractive event log 

    TString condiNameArr[numberOfConditions] = {
        "NDLE3Thr",
        "SDLE2Thr",
        "DDLE2Thr",
        "LMLE2Thr",
        "HMLE2Thr"
    };

    TString condiLegendArr[numberOfConditions] = {
        "NDLE",
        "SDLE",
        "DDLE",
        "LMLE",
        "HMLE"
    };

    TFile* file_All = new TFile(Form("./data/asymmetry_Neu_%s_ALL.root", fileCondName.Data()),"read");
    TGraphErrors* asymAll = (TGraphErrors*)file_All -> Get("GeneralAsymPtAllXf;1");
    TGraphErrors* asymAllXf = (TGraphErrors*)file_All -> Get("GeneralAsymXfAllPt;1");

    TFile* file_condi[numberOfConditions];
    TGraphErrors* asymType1Condi[numberOfConditions];
    TGraphErrors* asymXfType1Condi[numberOfConditions];

    bool isXfAsym = true;

    for(int i=0; i<numberOfConditions; i++){
        file_condi[i] = new TFile(Form("./data/asymmetry_Neu_%s_%s.root", fileCondName.Data(), condiNameArr[i].Data()),"read");
        asymType1Condi[i] = (TGraphErrors*)file_condi[i] -> Get("GeneralAsymPtAllXf;1");
        
        asymXfType1Condi[i] = (TGraphErrors*)file_condi[i] -> Get("GeneralAsymXfAllPt;1");
        if(!asymXfType1Condi[i]){isXfAsym = false;}
    }

    Double_t EventRatio[numberOfConditions];
    TTree* treeForCounts[numberOfConditions];

    for(int i=0; i < numberOfConditions; i++){
        EventRatio[i] = 0.;

        Int_t neuCount;
        Int_t selectedCount;

        treeForCounts[i] = (TTree*)file_condi[i] -> Get("count");
        treeForCounts[i] -> SetBranchAddress("NeuCount", &neuCount);
        treeForCounts[i] -> SetBranchAddress("SelectCount", &selectedCount);
        treeForCounts[i] -> GetEntry(0);

        EventRatio[i] = double(selectedCount)/double(neuCount)*100.;

        cout << i << " " << condiNameArr[i].Data() << " NeutronEvent: " << neuCount << " selectedEvent: " << selectedCount << " ratio: " << double(selectedCount)/double(neuCount)*100. << endl;
    }
    




    auto c1 = new TCanvas("","",1250,600);
    c1 ->Divide(2,1);

    c1 -> cd(1);
    gPad -> SetGrid(0,0);
    TString DrawOpt = "p";

    TGraph* tmpGraph = new TGraph();
    tmpGraph -> SetPoint(0, 0., -0.04);
    tmpGraph -> SetPoint(1, 0.7, 0.25);
    tmpGraph -> SetMarkerSize(0);
    tmpGraph -> SetMarkerStyle(20);
    tmpGraph -> SetLineWidth(0);
    tmpGraph -> GetYaxis() -> SetRangeUser(anDrawRange[0], anDrawRange[1]); 
    tmpGraph -> GetXaxis() -> SetRangeUser(0., 0.55);
    tmpGraph -> SetTitle("; p_{T} [GeV/c]; A_{N}");
    tmpGraph -> Draw("ap");

    if(!asymAll){cout <<"no " << endl;}
    asymAll -> SetMarkerSize(1.3);
    asymAll -> SetMarkerStyle(markerStyleIdx[0]);
    asymAll -> SetMarkerColor(colorIdx[0]);
    asymAll -> SetLineColor(colorIdx[0]);
    asymAll -> SetLineWidth(2);
    asymAll -> Draw(Form("same, %s",DrawOpt.Data()));

    for(int i=0; i<numberOfConditions; i++){

        if(isLittleShift == true){
            double shiftPoint = 0.002*double(i+1);
            for(int p=0; p<asymType1Condi[i] -> GetN(); p++){
                double pt, an;
                asymType1Condi[i] -> GetPoint(p, pt, an);
                asymType1Condi[i] -> SetPoint(p, pt+shiftPoint, an);
            }
        }

        int markerStyleNum = 0;
        int markerColorNum = 0;
        double markerSize = 1.3;
        if(condiLegendArr[i].Index("ND") != -1){
            markerStyleNum = markerStyleIdx[1]; 
            markerColorNum = colorIdx[1];
        }
        if(condiLegendArr[i].Index("SD") != -1 || condiLegendArr[i].Index("DD") != -1){
            markerStyleNum = markerStyleIdx[2];
            markerSize = 1.5;
            if(condiLegendArr[i].Index("SD") != -1){markerColorNum = colorIdx[2];}
            else{markerColorNum = colorIdx[3];}   
        }

        if(condiLegendArr[i].Index("LM") != -1 || condiLegendArr[i].Index("HM") != -1){
            markerStyleNum = markerStyleIdx[3]; 
            markerSize = 1.5;

            if(condiLegendArr[i].Index("LM") != -1){markerColorNum = colorIdx[4];}
            else{markerColorNum = colorIdx[5];}   
        }
        

        asymType1Condi[i] -> SetMarkerSize(markerSize);
        asymType1Condi[i] -> SetMarkerStyle(markerStyleNum);
        asymType1Condi[i] -> SetMarkerColor(markerColorNum);
        asymType1Condi[i] -> SetLineColor(markerColorNum);
        asymType1Condi[i] -> SetLineWidth(2);
        asymType1Condi[i] -> Draw(Form("same, %s",DrawOpt.Data()));
    }

    TLatex* anLatex = new TLatex();
    anLatex -> SetTextSize(0.04);
    anLatex -> DrawLatexNDC(0.4, 0.15, "p^{#uparrow}+p #rightarrow n + X, #sqrt{s} = 510 GeV");
    anLatex -> DrawLatexNDC(0.67, 0.85, "TS Run");
    anLatex -> DrawLatexNDC(0.67, 0.8, "Fill 21148");
    anLatex -> DrawLatexNDC(0.67, 0.75, "6 < #eta");
    anLatex -> DrawLatexNDC(0.67, 0.7, "0 < x_{F} < 1");

    if(isCheckEventCount){
        for(int i=0; i<numberOfConditions; i++){
            anLatex -> SetTextSize(0.025);
            anLatex -> DrawLatexNDC(0.67, 0.4-double(i)*0.035, Form("cond%i ratio = %.2f %", i+1, EventRatio[i]));
        }
    }

    anLatex -> SetTextSize(0.03);
    anLatex -> Draw("same");

    TLine* dashLine = new TLine(0., 0., 0.548, 0.);
    dashLine -> SetLineStyle(2);
    dashLine -> Draw("same");

    TLegend* leg = new TLegend(0.13, 0.7, 0.45, 0.88);
    leg -> SetBorderSize(0);
    leg -> SetTextSize(0.025);

    leg -> AddEntry(asymAll, "All events", "p");
    for(int i=0; i<numberOfConditions; i++){
        leg -> AddEntry(asymType1Condi[i], Form("%s", condiLegendArr[i].Data()), "p");
    }
    leg -> Draw("same");


    // =============== for Xf ====================
    c1 -> cd(2);
    gPad -> SetGrid(0,0);
    TString DrawOpt = "p";

    TGraph* tmpGraphXf = new TGraph();
    tmpGraphXf -> SetPoint(0, 0., -0.04);
    tmpGraphXf -> SetPoint(1, 1., 0.25);
    tmpGraphXf -> SetMarkerSize(0);
    tmpGraphXf -> SetMarkerStyle(20);
    tmpGraphXf -> SetLineWidth(0);
    tmpGraphXf -> GetYaxis() -> SetRangeUser(anDrawRange[0], anDrawRange[1]); 
    tmpGraphXf -> GetXaxis() -> SetRangeUser(0., 1.);
    tmpGraphXf -> SetTitle("; x_{F}; A_{N}");
    tmpGraphXf -> Draw("ap");

    if(!asymAllXf){cout <<" no " << endl;}
    asymAllXf -> SetMarkerSize(1.3);
    asymAllXf -> SetMarkerStyle(markerStyleIdx[0]);
    asymAllXf -> SetMarkerColor(colorIdx[0]);
    asymAllXf -> SetLineColor(colorIdx[0]);
    asymAllXf -> SetLineWidth(2);
    asymAllXf -> Draw(Form("same, %s",DrawOpt.Data()));

    if(isXfAsym == true){
        for(int i=0; i<numberOfConditions; i++){

            if(isLittleShift == true){
                double shiftPoint = 0.002*double(i+1);
                for(int p=0; p<asymXfType1Condi[i] -> GetN(); p++){
                    double pt, an;
                    asymXfType1Condi[i] -> GetPoint(p, pt, an);
                    asymXfType1Condi[i] -> SetPoint(p, pt+shiftPoint, an);
                }
            }

            int markerStyleNum = 0;
            int markerColorNum = 0;
            double markerSize = 1.3;
            if(condiLegendArr[i].Index("ND") != -1){
                markerStyleNum = markerStyleIdx[1]; 
                markerColorNum = colorIdx[1];
            }
            if(condiLegendArr[i].Index("SD") != -1 || condiLegendArr[i].Index("DD") != -1){
                markerStyleNum = markerStyleIdx[2];
                markerSize = 1.5;
                if(condiLegendArr[i].Index("SD") != -1){markerColorNum = colorIdx[2];}
                else{markerColorNum = colorIdx[3];}   
            }

            if(condiLegendArr[i].Index("LM") != -1 || condiLegendArr[i].Index("HM") != -1){
                markerStyleNum = markerStyleIdx[3]; 
                markerSize = 1.5;

                if(condiLegendArr[i].Index("LM") != -1){markerColorNum = colorIdx[4];}
                else{markerColorNum = colorIdx[5];}   
            }
            

            asymXfType1Condi[i] -> SetMarkerSize(markerSize);
            asymXfType1Condi[i] -> SetMarkerStyle(markerStyleNum);
            asymXfType1Condi[i] -> SetMarkerColor(markerColorNum);
            asymXfType1Condi[i] -> SetLineColor(markerColorNum);
            asymXfType1Condi[i] -> SetLineWidth(2);
            asymXfType1Condi[i] -> Draw(Form("same, %s",DrawOpt.Data()));
        }
    }

    TLatex* anLatex = new TLatex();
    anLatex -> SetTextSize(0.04);
    anLatex -> DrawLatexNDC(0.4, 0.15, "p^{#uparrow}+p #rightarrow n + X, #sqrt{s} = 510 GeV");
    anLatex -> DrawLatexNDC(0.67, 0.85, "TS Run");
    anLatex -> DrawLatexNDC(0.67, 0.8, "Fill 21148");
    anLatex -> DrawLatexNDC(0.67, 0.75, "6 < #eta");
    anLatex -> DrawLatexNDC(0.67, 0.7, "0 < p_{T} < 1");

    if(isCheckEventCount){
        for(int i=0; i<numberOfConditions; i++){
            anLatex -> SetTextSize(0.025);
            anLatex -> DrawLatexNDC(0.67, 0.4-double(i)*0.035, Form("cond%i ratio = %.2f %", i+1, EventRatio[i]));
        }
    }

    anLatex -> SetTextSize(0.03);
    anLatex -> Draw("same");

    TLine* dashLine = new TLine(0., 0., 1., 0.);
    dashLine -> SetLineStyle(2);
    dashLine -> Draw("same");

    TLegend* leg = new TLegend(0.13, 0.7, 0.45, 0.88);
    leg -> SetBorderSize(0);
    leg -> SetTextSize(0.025);

    leg -> AddEntry(asymAll, "All events", "p");
    if(isXfAsym == true){
        for(int i=0; i<numberOfConditions; i++){
            leg -> AddEntry(asymXfType1Condi[i], Form("%s", condiLegendArr[i].Data()), "p");
        }
    }
    leg -> Draw("same");


    c1 -> Draw();
    TString saveName = "./Asym_Neu"+DiffModeType+subCondiType+".pdf";
    c1 -> SaveAs(Form("%s", saveName.Data()));

}
