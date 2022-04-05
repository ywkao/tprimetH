//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr  3 20:10:51 2022 by ROOT version 6.18/04
// from TTree t/A Baby Ntuple
// found on file: MVABaby_Data_Era2016.root
//////////////////////////////////////////////////////////

#ifndef t_h
#define t_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <vector>

using namespace std;

// Header file for the classes stored in the TTree if any.
struct My_Cut_Values{
    double bdt_nrb_lowerBound;
    double bdt_nrb_upperBound;

    double bdt_smh_lowerBound;
    double bdt_smh_upperBound;

    double mass_lowerBound;
    double mass_upperBound;
};

class t {
    public :
        TTree          *fChain;   //!pointer to the analyzed TTree or TChain
        Int_t           fCurrent; //!current Tree number in a TChain

        // Fixed size dimensions of array or collections stored in the TTree if any.

        // Declaration of leaf types
        Float_t         weight;
        Float_t         dipho_mass;
        Float_t         Tprime_mass;
        Float_t         T_Mtilde;
        Float_t         BDTG_TprimeVsNonHiggs_M600_M700;
        Float_t         BDTG_TprimeVsNonHiggs_M800_M1000;
        Float_t         BDTG_TprimeVsNonHiggs_M1100_M1200;
        Float_t         BDTG_TprimeVsHiggs_M600_M700;
        Float_t         BDTG_TprimeVsHiggs_M800_M1000;
        Float_t         BDTG_TprimeVsHiggs_M1100_M1200;

        // List of branches
        TBranch        *b_weight;   //!
        TBranch        *b_dipho_mass;   //!
        TBranch        *b_Tprime_mass;   //!
        TBranch        *b_T_Mtilde;   //!
        TBranch        *b_BDTG_TprimeVsNonHiggs_M600_M700;   //!
        TBranch        *b_BDTG_TprimeVsNonHiggs_M800_M1000;   //!
        TBranch        *b_BDTG_TprimeVsNonHiggs_M1100_M1200;   //!
        TBranch        *b_BDTG_TprimeVsHiggs_M600_M700;   //!
        TBranch        *b_BDTG_TprimeVsHiggs_M800_M1000;   //!
        TBranch        *b_BDTG_TprimeVsHiggs_M1100_M1200;   //!


        t(TTree *tree=0, TString input="");
        virtual ~t();
        virtual Int_t    Cut(Long64_t entry);
        virtual Int_t    Cut(const Long64_t &entry, const My_Cut_Values &cut, const double &bdt_nrb, const double &bdt_smh);
        virtual My_Cut_Values set_threshold(const vector<double> &a, const vector<double> &b, const vector<double> &c);
        virtual Int_t    GetEntry(Long64_t entry);
        virtual Long64_t LoadTree(Long64_t entry);
        virtual void     Init(TTree *tree, TString input);
        virtual void     Loop();
        virtual Bool_t   Notify();
        virtual void     Show(Long64_t entry = -1);
        virtual void     Report();
        virtual void     Make_plots();
    private:
        TCanvas* c1;
        TH1D* h_counter_signal_region;
        TH1D* h_counter_validation_region;
        TH2D* h_map;

        int n_validation_regions;
        TString tag;
        bool is_data;
        int counter_SR1;
        int counter_SR2;
        int counter_SR3;
        double yields_SR1;
        double yields_SR2;
        double yields_SR3;
};

#endif

#ifdef t_cxx
t::t(TTree *tree, TString input) : fChain(0) 
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MVABaby_Data_Era2016.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("MVABaby_Data_Era2016.root");
        }
        f->GetObject("t",tree);

    }
    Init(tree, input);
}

t::~t()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t t::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t t::LoadTree(Long64_t entry)
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

void t::Init(TTree *tree, TString input)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    is_data = input.Contains("Data");
    if(is_data) tag = "data";
    else if(input.Contains("SMH")) tag = "smh";
    else if(input.Contains("Tprime")) tag = "sig";
    else tag = "others";

    c1 = new TCanvas("c1", "", 800, 600);
    c1->SetGrid();
    c1->SetTicks();
    c1->SetRightMargin(0.15);
    c1->SetLeftMargin(0.15);

    n_validation_regions = 170;
    h_counter_signal_region = new TH1D("h_counter_signal_region", ";Signal regions; Yields", 3, 0, 3);
    h_counter_validation_region = new TH1D("h_counter_validation_region", ";Validation regions; Yields", n_validation_regions, 0, n_validation_regions);
    h_counter_validation_region->SetMinimum(0.);

    h_map = new TH2D("h_map", ";BDT-NRB;BDT-SMH", 50, 0., 1., 50, 0., 1.);
    h_map->SetStats(0);

    counter_SR1 = 0;
    counter_SR2 = 0;
    counter_SR3 = 0;
    yields_SR1 = 0;
    yields_SR2 = 0;
    yields_SR3 = 0;

    fChain->SetBranchAddress("weight", &weight, &b_weight);
    fChain->SetBranchAddress("dipho_mass", &dipho_mass, &b_dipho_mass);
    fChain->SetBranchAddress("Tprime_mass", &Tprime_mass, &b_Tprime_mass);
    fChain->SetBranchAddress("T_Mtilde", &T_Mtilde, &b_T_Mtilde);
    fChain->SetBranchAddress("BDTG_TprimeVsNonHiggs_M600_M700", &BDTG_TprimeVsNonHiggs_M600_M700, &b_BDTG_TprimeVsNonHiggs_M600_M700);
    fChain->SetBranchAddress("BDTG_TprimeVsNonHiggs_M800_M1000", &BDTG_TprimeVsNonHiggs_M800_M1000, &b_BDTG_TprimeVsNonHiggs_M800_M1000);
    fChain->SetBranchAddress("BDTG_TprimeVsNonHiggs_M1100_M1200", &BDTG_TprimeVsNonHiggs_M1100_M1200, &b_BDTG_TprimeVsNonHiggs_M1100_M1200);
    fChain->SetBranchAddress("BDTG_TprimeVsHiggs_M600_M700", &BDTG_TprimeVsHiggs_M600_M700, &b_BDTG_TprimeVsHiggs_M600_M700);
    fChain->SetBranchAddress("BDTG_TprimeVsHiggs_M800_M1000", &BDTG_TprimeVsHiggs_M800_M1000, &b_BDTG_TprimeVsHiggs_M800_M1000);
    fChain->SetBranchAddress("BDTG_TprimeVsHiggs_M1100_M1200", &BDTG_TprimeVsHiggs_M1100_M1200, &b_BDTG_TprimeVsHiggs_M1100_M1200);
    Notify();
}

Bool_t t::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.
    //printf("Hello World!\n");

    return kTRUE;
}

void t::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t t::Cut(Long64_t entry)
{

    bool is_in_mgg_window = dipho_mass > 115. && dipho_mass < 135.;
    bool pass_mgg_cut = (is_data && !is_in_mgg_window) || (!is_data);

    if(pass_mgg_cut)
        return 1;
    else
        return -1;
}

My_Cut_Values t::set_threshold(const vector<double> &a, const vector<double> &b, const vector<double> &c)
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

Int_t t::Cut(const Long64_t &entry, const My_Cut_Values &cut, const double &bdt_nrb, const double &bdt_smh)
{
   bool pass_BDG_NRB     = bdt_nrb > cut.bdt_nrb_lowerBound  && bdt_nrb <= cut.bdt_nrb_upperBound;
   bool pass_BDG_SMH     = bdt_smh > cut.bdt_smh_lowerBound  && bdt_smh <= cut.bdt_smh_upperBound;
   bool pass_Tprime_mass = Tprime_mass > cut.mass_lowerBound && Tprime_mass < cut.mass_upperBound;
   bool accepted         = pass_BDG_SMH && pass_BDG_NRB && pass_Tprime_mass;

   if(accepted) return 1;
   else return -1;
}

void t::Report()
{
    for(int i=0; i<n_validation_regions; ++i) {
        printf("in VR%d: %.2f\n", i+1, h_counter_validation_region->GetBinContent(i+1));
    }

    printf("in SR1: %.2f\n", h_counter_signal_region->GetBinContent(1));
    printf("in SR2: %.2f\n", h_counter_signal_region->GetBinContent(2));
    printf("in SR3: %.2f\n", h_counter_signal_region->GetBinContent(3));
    //printf("counter_SR1 = %d, yields_SR1 = %.2f\n", counter_SR1, yields_SR1);
    //printf("counter_SR2 = %d, yields_SR2 = %.2f\n", counter_SR2, yields_SR2);
    //printf("counter_SR3 = %d, yields_SR3 = %.2f\n", counter_SR3, yields_SR3);
}

void t::Make_plots()
{
    TString output;

    h_counter_signal_region->Draw("hist;text");
    output = "eos/signal_region/h_counter_signal_region_" + tag;
    c1->SaveAs(output + ".png");
    c1->SaveAs(output + ".pdf");

    TString option = "";
    if(is_data) option = "ep";
    else option = "hist";

    h_counter_validation_region->Draw(option);
    output = "eos/h_counter_validation_region_" + tag;
    c1->SaveAs(output + ".png");
    c1->SaveAs(output + ".pdf");

    h_map->Draw("colz");
    output = "eos/h_map_" + tag;
    c1->SaveAs(output + ".png");
    c1->SaveAs(output + ".pdf");
}
#endif // #ifdef t_cxx
