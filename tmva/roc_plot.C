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

void compare(TString mva, TString type, vector<double> v_auc, vector<int> v_mass, vector<TString> date, vector<TString> prefix);
void exe(TString mva, TString type, vector<double> v_auc, TString date, TString prefix);
void exe_bdt_vs_bdtg(TString type);

TString path = "/eos/user/y/ykao/tPrimeExcessHgg/xmlfiles";

std::map<TString, TString> mLabels = {
    {"20210620", "Pure MC"},
    {"20210820", "Data-driven QCD"}
};


void roc_plot(){
    //exe_bdt_vs_bdtg("SMH");
    //exe_bdt_vs_bdtg("NRB");

    // display  three mass category
    //exe("BDT", "NRB", { 0.992, 0.998, 0.999 }, "20210620", "");
    //exe("BDT", "SMH", { 0.962, 0.983, 0.992 }, "20210620", "");
    //exe("BDTG", "NRB", { 0.992, 0.998, 0.999 }, "20210620", "");
    //exe("BDTG", "SMH", { 0.963, 0.983, 0.993 }, "20210620", "");
    //exe("BDTG", "NRB", { 0.995, 0.998, 0.999 }, "20210820", "results/20210820/");

    // compare two
    compare("BDTG", "NRB", { 0.992, 0.995 }, {600, 700}, {"20210620", "20210820"}, {"", "results/20210820/"});
    compare("BDTG", "NRB", { 0.998, 0.998 }, {800, 1000}, {"20210620", "20210820"}, {"", "results/20210820/"});
    compare("BDTG", "NRB", { 0.999, 0.999 }, {1100, 1200}, {"20210620", "20210820"}, {"", "results/20210820/"});
}

void exe_bdt_vs_bdtg(TString type) //{{{
{
    TString date = "20210620";

    gStyle->SetOptStat(0);
    
    //TFile * file_output = new TFile("output/roc_xcheck.root", "RECREATE");
    TFile * file_16 = TFile::Open(Form("%s/TMVA_Run2_Tprime_%s_varSet8_M600_M700_%s.root"  , date.Data(), type.Data(), date.Data()), "READ");
    TFile * file_17 = TFile::Open(Form("%s/TMVA_Run2_Tprime_%s_varSet8_M800_M1000_%s.root" , date.Data(), type.Data(), date.Data()), "READ");
    TFile * file_18 = TFile::Open(Form("%s/TMVA_Run2_Tprime_%s_varSet8_M1100_M1200_%s.root", date.Data(), type.Data(), date.Data()), "READ");
    
    TString mva, method;

    mva = "BDT";
    method = Form( "Method_%s/%s/MVA_%s_rejBvsS", mva.Data(), mva.Data(), mva.Data() );
    TH1F * h_roc_16_bdt = (TH1F*) file_16->Get(Form("dataset_Run2_Tprime_%s_varSet8_M600_M700_%s/%s"  , type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_17_bdt = (TH1F*) file_17->Get(Form("dataset_Run2_Tprime_%s_varSet8_M800_M1000_%s/%s" , type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_18_bdt = (TH1F*) file_18->Get(Form("dataset_Run2_Tprime_%s_varSet8_M1100_M1200_%s/%s", type.Data(), date.Data(), method.Data()));
    
    mva = "BDTG";
    method = Form( "Method_%s/%s/MVA_%s_rejBvsS", mva.Data(), mva.Data(), mva.Data() );
    TH1F * h_roc_16_bdtg = (TH1F*) file_16->Get(Form("dataset_Run2_Tprime_%s_varSet8_M600_M700_%s/%s"  , type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_17_bdtg = (TH1F*) file_17->Get(Form("dataset_Run2_Tprime_%s_varSet8_M800_M1000_%s/%s" , type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_18_bdtg = (TH1F*) file_18->Get(Form("dataset_Run2_Tprime_%s_varSet8_M1100_M1200_%s/%s", type.Data(), date.Data(), method.Data()));
    
    h_roc_16_bdt->SetTitle("");
    h_roc_16_bdt->GetXaxis()->SetTitleOffset(1.2);
    h_roc_16_bdt->SetLineWidth(2); h_roc_16_bdt->SetLineStyle(2); h_roc_16_bdt->SetLineColor(kRed);
    h_roc_17_bdt->SetLineWidth(2); h_roc_17_bdt->SetLineStyle(2); h_roc_17_bdt->SetLineColor(kGreen);
    h_roc_18_bdt->SetLineWidth(2); h_roc_18_bdt->SetLineStyle(2); h_roc_18_bdt->SetLineColor(kBlue);
    
    h_roc_16_bdtg->SetTitle("");
    h_roc_16_bdtg->GetXaxis()->SetTitleOffset(1.2);
    h_roc_16_bdtg->SetLineWidth(2); h_roc_16_bdtg->SetLineColor(kRed);
    h_roc_17_bdtg->SetLineWidth(2); h_roc_17_bdtg->SetLineColor(kGreen);
    h_roc_18_bdtg->SetLineWidth(2); h_roc_18_bdtg->SetLineColor(kBlue);
    
    //--------------------------------------------------
    // 20210620
    //--------------------------------------------------
    TLegend *leg = new TLegend(0.2, 0.2, 0.6, 0.5, "");
    
    if(type == "NRB") {
        leg->AddEntry(h_roc_16_bdt, "BDT [600, 700]: AUC=0.992", "l");
        leg->AddEntry(h_roc_17_bdt, "BDT [800, 1000]: AUC=0.998", "l");
        leg->AddEntry(h_roc_18_bdt, "BDT [1100, 1200]: AUC=0.999", "l");
        leg->AddEntry(h_roc_16_bdtg, "BDTG [600, 700]: AUC=0.992", "l");
        leg->AddEntry(h_roc_17_bdtg, "BDTG [800, 1000]: AUC=0.998", "l");
        leg->AddEntry(h_roc_18_bdtg, "BDTG [1100, 1200]: AUC=0.999", "l");
    }
    if(type == "SMH") {
        leg->AddEntry(h_roc_16_bdt, "BDT [600, 700]: AUC=0.962", "l");
        leg->AddEntry(h_roc_17_bdt, "BDT [800, 1000]: AUC=0.983", "l");
        leg->AddEntry(h_roc_18_bdt, "BDT [1100, 1200]: AUC=0.992", "l");
        leg->AddEntry(h_roc_16_bdtg, "BDTG [600, 700]: AUC=0.963", "l");
        leg->AddEntry(h_roc_17_bdtg, "BDTG [800, 1000]: AUC=0.983", "l");
        leg->AddEntry(h_roc_18_bdtg, "BDTG [1100, 1200]: AUC=0.993", "l");
    }
    
    TCanvas *c1= new TCanvas("c1", "c1",600,600);
    c1->SetLeftMargin(0.15);
    c1->SetGridx();
    c1->SetGridy();
    c1->cd();
    h_roc_16_bdt->Draw("l");
    h_roc_16_bdtg->Draw("l");
    h_roc_17_bdt->Draw("l SAME");
    h_roc_17_bdtg->Draw("l SAME");
    h_roc_18_bdt->Draw("l SAME");
    h_roc_18_bdtg->Draw("l SAME");
    leg->Draw("SAME");
    c1->SaveAs(Form("output/roc_TprimeVs%s.png", type.Data()));
    c1->SaveAs(Form("output/roc_TprimeVs%s.pdf", type.Data()));
} //}}}
void exe(TString mva, TString type, vector<double> v_auc, TString date, TString prefix) //{{{
{

    gStyle->SetOptStat(0);
    
    //TFile * file_output = new TFile("output/roc_xcheck.root", "RECREATE");
    TFile * file_16 = TFile::Open(Form("%s/%s/TMVA_Run2_Tprime_%s_varSet8_M600_M700_%s.root"  , path.Data(), date.Data(), type.Data(), date.Data()), "READ");
    TFile * file_17 = TFile::Open(Form("%s/%s/TMVA_Run2_Tprime_%s_varSet8_M800_M1000_%s.root" , path.Data(), date.Data(), type.Data(), date.Data()), "READ");
    TFile * file_18 = TFile::Open(Form("%s/%s/TMVA_Run2_Tprime_%s_varSet8_M1100_M1200_%s.root", path.Data(), date.Data(), type.Data(), date.Data()), "READ");
    
    TString method = Form( "Method_%s/%s/MVA_%s_rejBvsS", mva.Data(), mva.Data(), mva.Data() );
    TH1F * h_roc_16 = (TH1F*) file_16->Get(Form("%sdataset_Run2_Tprime_%s_varSet8_M600_M700_%s/%s"  , prefix.Data(), type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_17 = (TH1F*) file_17->Get(Form("%sdataset_Run2_Tprime_%s_varSet8_M800_M1000_%s/%s" , prefix.Data(), type.Data(), date.Data(), method.Data()));
    TH1F * h_roc_18 = (TH1F*) file_18->Get(Form("%sdataset_Run2_Tprime_%s_varSet8_M1100_M1200_%s/%s", prefix.Data(), type.Data(), date.Data(), method.Data()));
    
    h_roc_16->SetTitle("Background rejection vs Signal selection");
    h_roc_16->SetTitle("");
    h_roc_16->GetXaxis()->SetTitle("Signal selection efficiency");
    h_roc_16->GetYaxis()->SetTitle("Background rejection");
    h_roc_16->GetXaxis()->SetTitleOffset(1.2);
    
    h_roc_16->SetLineWidth(2);
    h_roc_16->SetLineColor(kRed);
    
    h_roc_17->SetLineWidth(2);
    h_roc_17->SetLineColor(kGreen);
    
    h_roc_18->SetLineWidth(2);
    h_roc_18->SetLineColor(kBlue);
    
    TLegend *leg = new TLegend(0.2, 0.2, 0.6, 0.4, "");
    leg->AddEntry(h_roc_16, Form("[600, 700]: AUC=%.3f", v_auc[0]), "l");
    leg->AddEntry(h_roc_17, Form("[800, 1000]: AUC=%.3f", v_auc[1]), "l");
    leg->AddEntry(h_roc_18, Form("[1100, 1200]: AUC=%.3f", v_auc[2]), "l");

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
    c1->SaveAs(Form("output/roc_TprimeVs%s_%s_%s.png", type.Data(), mva.Data(), date.Data()));
    c1->SaveAs(Form("output/roc_TprimeVs%s_%s_%s.pdf", type.Data(), mva.Data(), date.Data()));
} //}}}
void compare(TString mva, TString type, vector<double> v_auc, vector<int> v_mass, vector<TString> date, vector<TString> prefix) //{{{
{

    TString mass_tag = Form("M%d_M%d", v_mass[0], v_mass[1]);
    TString mass_region = Form("[%d, %d]", v_mass[0], v_mass[1]);
    gStyle->SetOptStat(0);
    
    //TFile * file_output = new TFile("output/roc_xcheck.root", "RECREATE");
    TFile * file_01 = TFile::Open(Form("%s/%s/TMVA_Run2_Tprime_%s_varSet8_%s_%s.root", path.Data(), date[0].Data(), type.Data(), mass_tag.Data(), date[0].Data()), "READ");
    TFile * file_02 = TFile::Open(Form("%s/%s/TMVA_Run2_Tprime_%s_varSet8_%s_%s.root", path.Data(), date[1].Data(), type.Data(), mass_tag.Data(), date[1].Data()), "READ");
    
    TString method = Form( "Method_%s/%s/MVA_%s_rejBvsS", mva.Data(), mva.Data(), mva.Data() );
    TH1F * h_roc_01 = (TH1F*) file_01->Get(Form("%sdataset_Run2_Tprime_%s_varSet8_%s_%s/%s", prefix[0].Data(), type.Data(), mass_tag.Data(), date[0].Data(), method.Data()));
    TH1F * h_roc_02 = (TH1F*) file_02->Get(Form("%sdataset_Run2_Tprime_%s_varSet8_%s_%s/%s", prefix[1].Data(), type.Data(), mass_tag.Data(), date[1].Data(), method.Data()));
    
    h_roc_01->SetTitle("");
    h_roc_01->GetXaxis()->SetTitle("Signal selection efficiency");
    h_roc_01->GetYaxis()->SetTitle("Background rejection");
    h_roc_01->GetXaxis()->SetTitleOffset(1.2);
    
    h_roc_01->SetLineWidth(2);
    h_roc_01->SetLineColor(kBlue);
    
    h_roc_02->SetLineWidth(2);
    h_roc_02->SetLineColor(kRed);

    TLegend *leg = new TLegend(0.2, 0.2, 0.8, 0.36, "");
    leg->SetLineColor(0);
    leg->SetTextSize(0.04);
    leg->AddEntry(h_roc_01, Form("%s: AUC=%.3f", mLabels[date[0]].Data(), v_auc[0]), "l");
    leg->AddEntry(h_roc_02, Form("%s: AUC=%.3f", mLabels[date[1]].Data(), v_auc[1]), "l");

    TCanvas *c1= new TCanvas("c1", "c1",600,600);
    c1->SetLeftMargin(0.15);
    c1->SetGridx();
    c1->SetGridy();
    c1->cd();
    h_roc_01->Draw("l");
    h_roc_02->Draw("l SAME");
    leg->Draw("SAME");
    c1->SaveAs(Form("output/comparison_roc_TprimeVs%s_%s_%s.png", type.Data(), mva.Data(), mass_tag.Data()));
    c1->SaveAs(Form("output/comparison_roc_TprimeVs%s_%s_%s.pdf", type.Data(), mva.Data(), mass_tag.Data()));
} //}}}

