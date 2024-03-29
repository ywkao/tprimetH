#include "TTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TLorentzVector.h"

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <TChain.h>
#include "TMath.h"
#include "TGraphErrors.h"


void exe(TString mva, TString type);

void roc_plot(){
    exe("BDT", "SMH");
    exe("BDT", "NRB");
    exe("BDTG", "SMH");
    exe("BDTG", "NRB");
}

void exe(TString mva, TString type){
    TString date = "20210620";
    //TString type = "SMH";
    //TString type = "NRB";
    //TString mva  = "BDTG";

    gStyle->SetOptStat(0);
    
    TFile * file_output = new TFile("output/roc_xcheck.root", "RECREATE");
    TFile * file_16 = TFile::Open(Form("%s/TMVA_Run2_Tprime_%s_varSet8_M600_M700_%s.root"  , date.Data(), type.Data(), date.Data()), "READ");
    TFile * file_17 = TFile::Open(Form("%s/TMVA_Run2_Tprime_%s_varSet8_M800_M1000_%s.root" , date.Data(), type.Data(), date.Data()), "READ");
    TFile * file_18 = TFile::Open(Form("%s/TMVA_Run2_Tprime_%s_varSet8_M1100_M1200_%s.root", date.Data(), type.Data(), date.Data()), "READ");
    
    TString method = Form( "Method_%s/%s/MVA_%s_rejBvsS", mva.Data(), mva.Data(), mva.Data() );
    TH1F * h_roc_16 = (TH1F*) file_16->Get(Form("dataset_Run2_Tprime_%s_varSet8_M600_M700_%s/%s"  , type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_17 = (TH1F*) file_17->Get(Form("dataset_Run2_Tprime_%s_varSet8_M800_M1000_%s/%s" , type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_18 = (TH1F*) file_18->Get(Form("dataset_Run2_Tprime_%s_varSet8_M1100_M1200_%s/%s", type.Data(), date.Data(), method.Data()));
    
    h_roc_16->SetTitle("Background rejection vs Signal selection");
    h_roc_16->GetXaxis()->SetTitleOffset(1.2);
    h_roc_17->GetYaxis()->SetTitle("Background rejection");
    h_roc_18->GetXaxis()->SetTitle("Signal selection");
    
    h_roc_16->SetLineWidth(2);
    h_roc_16->SetLineColor(kRed);
    
    h_roc_17->SetLineWidth(2);
    h_roc_17->SetLineColor(kGreen);
    
    h_roc_18->SetLineWidth(2);
    h_roc_18->SetLineColor(kBlue);
    
    TLegend *leg = new TLegend(0.2, 0.2, 0.6, 0.4, "");
    
    //--------------------------------------------------
    // 20210620
    //--------------------------------------------------
    if(mva == "BDT") {
        if(type == "NRB") {
            leg->AddEntry(h_roc_16, "[600, 700]: AUC=0.992", "l");
            leg->AddEntry(h_roc_17, "[800, 1000]: AUC=0.998", "l");
            leg->AddEntry(h_roc_18, "[1100, 1200]: AUC=0.999", "l");
        }
        if(type == "SMH") {
            leg->AddEntry(h_roc_16, "[600, 700]: AUC=0.962", "l");
            leg->AddEntry(h_roc_17, "[800, 1000]: AUC=0.983", "l");
            leg->AddEntry(h_roc_18, "[1100, 1200]: AUC=0.992", "l");
        }
    }

    if(mva == "BDTG") {
        if(type == "NRB") {
            leg->AddEntry(h_roc_16, "[600, 700]: AUC=0.992", "l");
            leg->AddEntry(h_roc_17, "[800, 1000]: AUC=0.998", "l");
            leg->AddEntry(h_roc_18, "[1100, 1200]: AUC=0.999", "l");
        }
        if(type == "SMH") {
            leg->AddEntry(h_roc_16, "[600, 700]: AUC=0.963", "l");
            leg->AddEntry(h_roc_17, "[800, 1000]: AUC=0.983", "l");
            leg->AddEntry(h_roc_18, "[1100, 1200]: AUC=0.993", "l");
        }
    }
    
    //cout<<h_roc_16->GetEntries()<<endl;
    TCanvas *c1= new TCanvas("c1", "c1",600,600);
    c1->SetLeftMargin(0.15);
    c1->SetGridx();
    c1->SetGridy();
    c1->cd();
    h_roc_16->Draw("l");
    h_roc_17->Draw("l SAME");
    h_roc_18->Draw("l SAME");
    leg->Draw("SAME");
    c1->SaveAs(Form("output/roc_TprimeVs%s_%s.png", type.Data(), mva.Data()));
    c1->SaveAs(Form("output/roc_TprimeVs%s_%s.pdf", type.Data(), mva.Data()));
}
