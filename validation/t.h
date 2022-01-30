//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep  8 13:58:26 2021 by ROOT version 6.14/09
// from TTree t/A Baby Ntuple
// found on file: /eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime/output_Data_v3p8_21Jul21.root
//////////////////////////////////////////////////////////

#ifndef t_h
#define t_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>

// Header file for the classes stored in the TTree if any.

struct My_Cut_Values{ double bdt_nrb; double bdt_smh; double mass_low; double mass_high; };

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

   TString input_file_name;

   My_Cut_Values set_threshold(double a, double b, double c, double d);

   t(TTree *tree=0, TString name="");
   virtual ~t();
   virtual Int_t    Cut(Long64_t entry, My_Cut_Values cut, double bdt_nrb, double bdt_smh);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree, TString name);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

private:
   bool is_in_sideband;
   bool pass_BDG_SMH;
   bool pass_BDG_NRB;
   bool pass_Tprime_mass;
   bool accepted;
};

#endif

#ifdef t_cxx
t::t(TTree *tree, TString name) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime/output_Data_v3p8_21Jul21.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime/output_Data_v3p8_21Jul21.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree, name);
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

void t::Init(TTree *tree, TString name)
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

   input_file_name = name;
}

Bool_t t::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void t::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

My_Cut_Values t::set_threshold(double a, double b, double c, double d)
{
    My_Cut_Values cut;
    cut.bdt_nrb   = a;
    cut.bdt_smh   = b;
    cut.mass_low  = c;
    cut.mass_high = d;
    return cut;    
}

Int_t t::Cut(Long64_t entry, My_Cut_Values cut, double bdt_nrb, double bdt_smh)
{
   bool is_data = input_file_name.Contains("Data");

   is_in_sideband   = is_data ? dipho_mass<115. || dipho_mass>135. : true;
   pass_BDG_NRB     = bdt_nrb > cut.bdt_nrb;
   pass_BDG_SMH     = bdt_smh > cut.bdt_smh;
   pass_Tprime_mass = Tprime_mass > cut.mass_low && Tprime_mass < cut.mass_high;
   accepted         = is_in_sideband && pass_BDG_SMH && pass_BDG_NRB && pass_Tprime_mass;

   if(accepted) return 1;
   else return -1;
}

#endif // #ifdef t_cxx
