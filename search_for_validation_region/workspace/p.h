//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 16 10:33:26 2022 by ROOT version 6.18/04
// from TTree Data_13TeV_THQLeptonicTag/Data_13TeV_THQLeptonicTag
// found on file: output_Data_600_700_leptonic.root
//////////////////////////////////////////////////////////

#ifndef p_h
#define p_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "toolbox.h"

// Header file for the classes stored in the TTree if any.

class p {
    public :
        TTree          *fChain;   //!pointer to the analyzed TTree or TChain
        Int_t           fCurrent; //!current Tree number in a TChain

        // Fixed size dimensions of array or collections stored in the TTree if any.

        // Declaration of leaf types
        Float_t         MVAscore_TprimeVsNonHiggs;
        Float_t         MVAscore_TprimeVsHiggs;
        Float_t         weight;
        Float_t         dipho_mass;
        Float_t         Tprime_mass;
        Float_t         lepton_leadPt;
        Float_t         T_Mtilde;

        // List of branches
        TBranch        *b_MVAscore_TprimeVsNonHiggs;   //!
        TBranch        *b_MVAscore_TprimeVsHiggs;   //!
        TBranch        *b_weight;   //!
        TBranch        *b_dipho_mass;   //!
        TBranch        *b_Tprime_mass;   //!
        TBranch        *b_lepton_leadPt;   //!
        TBranch        *b_T_Mtilde;   //!

        p(TTree *tree=0, TString input="");
        virtual ~p();
        virtual Int_t    Cut(Long64_t entry, bool unblind);
        virtual Int_t    Cut(const Long64_t &entry, const My_Cut_Values &cut, const vector<double> &bdts, bool set_mgg_window=false);
        virtual My_Cut_Values set_threshold(const vector<double> &a, const vector<double> &b, const vector<double> &c);
        virtual Int_t    GetEntry(Long64_t entry);
        virtual Long64_t LoadTree(Long64_t entry);
        virtual void     Init(TTree *tree, TString input);
        virtual void     Loop();
        virtual Bool_t   Notify();
        virtual void     Show(Long64_t entry = -1);
        virtual void     Report();
        virtual void     Make_plots();
        virtual void     Annotate();

    private:
        TString tag;
        bool is_data;
        bool is_SR1;
        bool is_SR2;
        bool is_SR3;

        Yield_Calculator yc_SR1;
        Yield_Calculator yc_SR2;
        Yield_Calculator yc_SR3;
        Yield_Calculator yc_mp_SR1;

        TCanvas* c1;
        TCanvas* c2;
        TH2D* h_mass_map_SR1;
        TH2D* h_mass_map_SR2;
        TH2D* h_mass_map_SR3;
        TH1D* h_mass_diphoton_SR1;
        TH1D* h_mass_diphoton_SR2;
        TH1D* h_mass_diphoton_SR3;
};

#endif

#ifdef p_cxx
p::p(TTree *tree, TString input) : fChain(0) 
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output_Data_600_700_leptonic.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("output_Data_600_700_leptonic.root");
        }
        f->GetObject("Data_13TeV_THQLeptonicTag",tree);

    }
    Init(tree, input);
}

p::~p()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t p::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t p::LoadTree(Long64_t entry)
{
    // Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void p::Init(TTree *tree, TString input)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    is_data = input.Contains("Data");
    if(is_data) tag = "data";

    if( input.Contains("600_700") )   { is_SR1=true  ; is_SR2=false ; is_SR3=false ; }
    if( input.Contains("800_1000") )  { is_SR1=false ; is_SR2=true  ; is_SR3=false ; }
    if( input.Contains("1100_1200") ) { is_SR1=false ; is_SR2=false ; is_SR3=true  ; }

    c1 = new TCanvas("c1", "", 800, 600);
    c1->SetGrid();
    c1->SetTicks();
    c1->SetRightMargin(0.15);
    c1->SetLeftMargin(0.15);

    c2 = new TCanvas("c2", "", 800, 800);
    c2->SetGrid();
    c2->SetTicks();
    c2->SetRightMargin(0.15);
    c2->SetLeftMargin(0.15);

    h_mass_map_SR1 = new TH2D("h_mass_map_SR1", ";M_{#gamma#gamma} (GeV);M_{T'} (GeV)", 80, 100., 180., 7, 450., 800.);
    h_mass_map_SR2 = new TH2D("h_mass_map_SR2", ";M_{#gamma#gamma} (GeV);M_{T'} (GeV)", 80, 100., 180., 12, 550., 1150.);
    h_mass_map_SR3 = new TH2D("h_mass_map_SR3", ";M_{#gamma#gamma} (GeV);M_{T'} (GeV)", 80, 100., 180., 19, 650., 1600.);
    h_mass_map_SR1->SetStats(0);
    h_mass_map_SR2->SetStats(0);
    h_mass_map_SR3->SetStats(0);

    h_mass_diphoton_SR1 = new TH1D("h_mass_diphoton_SR1", ";M_{#gamma#gamma} (GeV);Entries", 80, 100., 180.);
    h_mass_diphoton_SR2 = new TH1D("h_mass_diphoton_SR2", ";M_{#gamma#gamma} (GeV);Entries", 80, 100., 180.);
    h_mass_diphoton_SR3 = new TH1D("h_mass_diphoton_SR3", ";M_{#gamma#gamma} (GeV);Entries", 80, 100., 180.);
    //h_mass_diphoton_SR1->SetStats(0);
    //h_mass_diphoton_SR2->SetStats(0);
    //h_mass_diphoton_SR3->SetStats(0);
    h_mass_diphoton_SR1->SetMinimum(0);
    h_mass_diphoton_SR2->SetMinimum(0);
    h_mass_diphoton_SR3->SetMinimum(0);
    h_mass_diphoton_SR1->SetMarkerStyle(20);
    h_mass_diphoton_SR2->SetMarkerStyle(20);
    h_mass_diphoton_SR3->SetMarkerStyle(20);
    h_mass_diphoton_SR1->SetLineColor(kBlack);
    h_mass_diphoton_SR2->SetLineColor(kBlack);
    h_mass_diphoton_SR3->SetLineColor(kBlack);

    if(is_data) {
        h_mass_map_SR1->SetMaximum(3);
        h_mass_map_SR2->SetMaximum(3);
        h_mass_map_SR3->SetMaximum(3);
        h_mass_map_SR1->SetMinimum(1);
        h_mass_map_SR2->SetMinimum(1);
        h_mass_map_SR3->SetMinimum(1);
    } else {
        h_mass_map_SR1->SetMinimum(0);
        h_mass_map_SR2->SetMinimum(0);
        h_mass_map_SR3->SetMinimum(0);
    }

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &MVAscore_TprimeVsNonHiggs, &b_MVAscore_TprimeVsNonHiggs);
    fChain->SetBranchAddress("MVAscore_TprimeVsHiggs", &MVAscore_TprimeVsHiggs, &b_MVAscore_TprimeVsHiggs);
    fChain->SetBranchAddress("weight", &weight, &b_weight);
    fChain->SetBranchAddress("dipho_mass", &dipho_mass, &b_dipho_mass);
    fChain->SetBranchAddress("Tprime_mass", &Tprime_mass, &b_Tprime_mass);
    fChain->SetBranchAddress("lepton_leadPt", &lepton_leadPt, &b_lepton_leadPt);
    fChain->SetBranchAddress("T_Mtilde", &T_Mtilde, &b_T_Mtilde);
    Notify();
}

Bool_t p::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void p::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}
Int_t p::Cut(Long64_t entry, bool unblind)
{
    // unblind
    if(unblind) return 1;

    // blind
    bool is_in_mgg_window = dipho_mass > 115. && dipho_mass < 135.;
    //bool pass_mgg_cut = (is_data && !is_in_mgg_window) || (!is_data);
    bool pass_mgg_cut = (is_data && !is_in_mgg_window) || (!is_data && is_in_mgg_window);

    if(pass_mgg_cut)
        return 1;
    else
        return -1;
}

My_Cut_Values p::set_threshold(const vector<double> &a, const vector<double> &b, const vector<double> &c)
{
    My_Cut_Values cut;
    cut.bdt_nrb_lowerBound = a[0];
    cut.bdt_nrb_upperBound = a[1];
    cut.bdt_smh_lowerBound = b[0];
    cut.bdt_smh_upperBound = b[1];
    cut.mass_lowerBound    = c[0];
    cut.mass_upperBound    = c[1];
    return cut;    
}

Int_t p::Cut(const Long64_t &entry, const My_Cut_Values &cut, const vector<double> &bdts, bool set_mgg_window /*=false*/)
{

    double bdt_nrb = bdts[0];
    double bdt_smh = bdts[1];

    bool is_in_mgg_window = dipho_mass > 115. && dipho_mass < 135.;
    bool pass_BDG_NRB     = bdt_nrb > cut.bdt_nrb_lowerBound  && bdt_nrb <= cut.bdt_nrb_upperBound;
    bool pass_BDG_SMH     = bdt_smh > cut.bdt_smh_lowerBound  && bdt_smh <= cut.bdt_smh_upperBound;
    bool pass_Tprime_mass = Tprime_mass > cut.mass_lowerBound && Tprime_mass < cut.mass_upperBound;
    bool accepted;

    if(set_mgg_window)
        accepted = pass_BDG_SMH && pass_BDG_NRB && pass_Tprime_mass && is_in_mgg_window;
    else
        accepted = pass_BDG_SMH && pass_BDG_NRB && pass_Tprime_mass;

    if(accepted) return 1;
    else return -1;
}

void p::Report()
{

    yc_SR1.Report("SR1");
    yc_SR2.Report("SR2");
    yc_SR3.Report("SR3");

    yc_mp_SR1.Report("middle-purity SR1");

    //printf("in SR1: %.2f\n", h_counter_signal_region->GetBinContent(1));
    //printf("in SR2: %.2f\n", h_counter_signal_region->GetBinContent(2));
    //printf("in SR3: %.2f\n", h_counter_signal_region->GetBinContent(3));

    return;
}

void p::Annotate()
{
    TLatex latex;
    latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextAlign(11);
    latex.SetTextSize(26);
    latex.DrawLatex( 0.15, 0.912, "#bf{CMS} #it{Preliminary}" );
    latex.DrawLatex( 0.63, 0.912, "138 fb^{-1} (13 TeV)" );
}

void p::Make_plots()
{
    TString output;

    TString option = "";
    if(is_data) option = "ep";
    else option = "hist";


    if(is_SR1) {
        c2->cd();
        h_mass_map_SR1->Draw("colz");
        output = "eos_lep/h_mass_map_SR1_" + tag;
        Annotate();
        c2->SaveAs(output + ".png");
        c2->SaveAs(output + ".pdf");

        c1->cd();
        h_mass_diphoton_SR1->Draw("ep");
        output = "eos_lep/h_mass_diphoton_SR1_" + tag;
        c1->SaveAs(output + ".png");
        c1->SaveAs(output + ".pdf");
    }

    if(is_SR2) {
        c2->cd();
        h_mass_map_SR2->Draw("colz");
        output = "eos_lep/h_mass_map_SR2_" + tag;
        Annotate();
        c2->SaveAs(output + ".png");
        c2->SaveAs(output + ".pdf");

        c1->cd();
        h_mass_diphoton_SR2->Draw("ep");
        output = "eos_lep/h_mass_diphoton_SR2_" + tag;
        c1->SaveAs(output + ".png");
        c1->SaveAs(output + ".pdf");
    }

    if(is_SR3) {
        c2->cd();
        h_mass_map_SR3->Draw("colz");
        output = "eos_lep/h_mass_map_SR3_" + tag;
        Annotate();
        c2->SaveAs(output + ".png");
        c2->SaveAs(output + ".pdf");

        c1->cd();
        h_mass_diphoton_SR3->Draw("ep");
        output = "eos_lep/h_mass_diphoton_SR3_" + tag;
        c1->SaveAs(output + ".png");
        c1->SaveAs(output + ".pdf");
    }
}
#endif // #ifdef p_cxx
