//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr  6 11:28:27 2021 by ROOT version 5.34/32
// from TTree t/A Baby Ntuple
// found on file: MVABaby_ttHHadronic_v5.7_tprimetH_impute_hct_BDT_FCNC.root
//////////////////////////////////////////////////////////

#ifndef t_h
#define t_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.
#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxyear = 1;
   const Int_t kMaxevt = 1;
   const Int_t kMaxrun = 1;
   const Int_t kMaxlumi = 1;
   const Int_t kMaxevt_weight = 1;
   const Int_t kMaxlabel = 1;
   const Int_t kMaxmulti_label = 1;
   const Int_t kMaxsignal_mass_label = 1;
   const Int_t kMaxsignal_mass_category = 1;
   const Int_t kMaxdata_sideband_label = 1;
   const Int_t kMaxgenPhotonId = 1;
   const Int_t kMaxprocess_id = 1;
   const Int_t kMaxrand = 1;
   const Int_t kMaxsuper_rand = 1;
   const Int_t kMaxmass = 1;
   const Int_t kMaxlead_sigmaEtoE = 1;
   const Int_t kMaxsublead_sigmaEtoE = 1;
   const Int_t kMaxobjects = 1;
   const Int_t kMaxobjects_boosted = 1;
   const Int_t kMaxtop_candidates = 1;
   const Int_t kMaxmaxIDMVA = 1;
   const Int_t kMaxminIDMVA = 1;
   const Int_t kMaxmax2_btag = 1;
   const Int_t kMaxmax1_btag = 1;
   const Int_t kMaxnjets = 1;
   const Int_t kMaxnbjets = 1;
   const Int_t kMaxht = 1;
   const Int_t kMaxtop_tag_score = 1;
   const Int_t kMaxtop_tag_mass = 1;
   const Int_t kMaxtop_tag_pt = 1;
   const Int_t kMaxtop_tag_eta = 1;
   const Int_t kMaxtop_tag_phi = 1;
   const Int_t kMaxjet1_pt = 1;
   const Int_t kMaxjet1_eta = 1;
   const Int_t kMaxjet1_btag = 1;
   const Int_t kMaxjet2_pt = 1;
   const Int_t kMaxjet2_eta = 1;
   const Int_t kMaxjet2_btag = 1;
   const Int_t kMaxjet3_pt = 1;
   const Int_t kMaxjet3_eta = 1;
   const Int_t kMaxjet3_btag = 1;
   const Int_t kMaxjet4_pt = 1;
   const Int_t kMaxjet4_eta = 1;
   const Int_t kMaxjet4_btag = 1;
   const Int_t kMaxjet5_pt = 1;
   const Int_t kMaxjet5_eta = 1;
   const Int_t kMaxjet5_btag = 1;
   const Int_t kMaxjet6_pt = 1;
   const Int_t kMaxjet6_eta = 1;
   const Int_t kMaxjet6_btag = 1;
   const Int_t kMaxjet7_pt = 1;
   const Int_t kMaxjet7_eta = 1;
   const Int_t kMaxjet7_btag = 1;
   const Int_t kMaxjet8_pt = 1;
   const Int_t kMaxjet8_eta = 1;
   const Int_t kMaxjet8_btag = 1;
   const Int_t kMaxjet1_phi = 1;
   const Int_t kMaxjet1_energy = 1;
   const Int_t kMaxjet2_phi = 1;
   const Int_t kMaxjet2_energy = 1;
   const Int_t kMaxjet3_phi = 1;
   const Int_t kMaxjet3_energy = 1;
   const Int_t kMaxjet4_phi = 1;
   const Int_t kMaxjet4_energy = 1;
   const Int_t kMaxjet5_phi = 1;
   const Int_t kMaxjet5_energy = 1;
   const Int_t kMaxjet6_phi = 1;
   const Int_t kMaxjet6_energy = 1;
   const Int_t kMaxjet7_phi = 1;
   const Int_t kMaxjet7_energy = 1;
   const Int_t kMaxjet8_phi = 1;
   const Int_t kMaxjet8_energy = 1;
   const Int_t kMaxlead_pT = 1;
   const Int_t kMaxsublead_pT = 1;
   const Int_t kMaxleadptoM = 1;
   const Int_t kMaxsubleadptoM = 1;
   const Int_t kMaxleadIDMVA = 1;
   const Int_t kMaxsubleadIDMVA = 1;
   const Int_t kMaxlead_eta = 1;
   const Int_t kMaxsublead_eta = 1;
   const Int_t kMaxleadPSV = 1;
   const Int_t kMaxsubleadPSV = 1;
   const Int_t kMaxlead_phi = 1;
   const Int_t kMaxsublead_phi = 1;
   const Int_t kMaxdipho_cosphi = 1;
   const Int_t kMaxdipho_rapidity = 1;
   const Int_t kMaxdipho_pt = 1;
   const Int_t kMaxdipho_pt_over_mass = 1;
   const Int_t kMaxmet = 1;
   const Int_t kMaxlog_met = 1;
   const Int_t kMaxmet_phi = 1;
   const Int_t kMaxhelicity_angle = 1;
   const Int_t kMaxm_ggj = 1;
   const Int_t kMaxm_jjj = 1;
   const Int_t kMaxtop_candidates_1 = 1;
   const Int_t kMaxtop_candidates_2 = 1;
   const Int_t kMaxtop_candidates_3 = 1;
   const Int_t kMaxtop_candidates_4 = 1;
   const Int_t kMaxtop_candidates_5 = 1;
   const Int_t kMaxtop_candidates_6 = 1;
   const Int_t kMaxtop_candidates_7 = 1;
   const Int_t kMaxtop_candidates_8 = 1;
   const Int_t kMaxtop_candidates_9 = 1;
   const Int_t kMaxtop_candidates_10 = 1;
   const Int_t kMaxtop_candidates_11 = 1;
   const Int_t kMaxtop_candidates_12 = 1;
   const Int_t kMaxchi2_value = 1;
   const Int_t kMaxchi2_bjet_pt = 1;
   const Int_t kMaxchi2_wjet1_pt = 1;
   const Int_t kMaxchi2_wjet2_pt = 1;
   const Int_t kMaxchi2_bjet_eta = 1;
   const Int_t kMaxchi2_wjet1_eta = 1;
   const Int_t kMaxchi2_wjet2_eta = 1;
   const Int_t kMaxchi2_wjets_deltaR = 1;
   const Int_t kMaxchi2_wboson_pt = 1;
   const Int_t kMaxchi2_wboson_eta = 1;
   const Int_t kMaxchi2_wboson_mass = 1;
   const Int_t kMaxchi2_wboson_deltaR_bjet = 1;
   const Int_t kMaxchi2_tbw_mass = 1;
   const Int_t kMaxchi2_tbw_pt = 1;
   const Int_t kMaxchi2_tbw_eta = 1;
   const Int_t kMaxchi2_tbw_deltaR_dipho = 1;
   const Int_t kMaxchi2_tprime_ptOverM = 1;
   const Int_t kMaxchi2_tprime_eta = 1;
   const Int_t kMaxchi2_tprime_deltaR_tbw = 1;
   const Int_t kMaxchi2_tprime_deltaR_dipho = 1;
   const Int_t kMaxchi2_bjet_btagScores = 1;
   const Int_t kMaxchi2_wjet1_btagScores = 1;
   const Int_t kMaxchi2_wjet2_btagScores = 1;
   const Int_t kMaxtprime_pt_ratio = 1;
   const Int_t kMaxchi2_bjet_ptOverM = 1;
   const Int_t kMaxchi2_wjet1_ptOverM = 1;
   const Int_t kMaxchi2_wjet2_ptOverM = 1;
   const Int_t kMaxchi2_wboson_ptOverM = 1;
   const Int_t kMaxchi2_tbw_ptOverM = 1;
   const Int_t kMaxhelicity_tprime = 1;
   const Int_t kMaxjet1_ptOverM = 1;
   const Int_t kMaxjet2_ptOverM = 1;
   const Int_t kMaxjet3_ptOverM = 1;
   const Int_t kMaxjet4_ptOverM = 1;

class t {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<string>  *mva_branches;
   Int_t           year_;
   ULong64_t       evt_;
   ULong64_t       run_;
   ULong64_t       lumi_;
   Float_t         evt_weight_;
   Int_t           label_;
   Int_t           multi_label_;
   Int_t           signal_mass_label_;
   Int_t           signal_mass_category_;
   Int_t           data_sideband_label_;
   Int_t           genPhotonId_;
   Int_t           process_id_;
   Float_t         rand_;
   Float_t         super_rand_;
   Float_t         mass_;
   Float_t         lead_sigmaEtoE_;
   Float_t         sublead_sigmaEtoE_;
   vector<vector<float> > *objects_;
   vector<vector<float> > *objects_boosted_;
   vector<float>   *top_candidates_;
   Float_t         maxIDMVA_;
   Float_t         minIDMVA_;
   Float_t         max2_btag_;
   Float_t         max1_btag_;
   Float_t         dipho_delta_R;
   Float_t         njets_;
   Int_t           nbjets_;
   Float_t         ht_;
   Float_t         top_tag_score_;
   Float_t         top_tag_mass_;
   Float_t         top_tag_pt_;
   Float_t         top_tag_eta_;
   Float_t         top_tag_phi_;
   Float_t         jet1_pt_;
   Float_t         jet1_eta_;
   Float_t         jet1_btag_;
   Float_t         jet2_pt_;
   Float_t         jet2_eta_;
   Float_t         jet2_btag_;
   Float_t         jet3_pt_;
   Float_t         jet3_eta_;
   Float_t         jet3_btag_;
   Float_t         jet4_pt_;
   Float_t         jet4_eta_;
   Float_t         jet4_btag_;
   Float_t         jet5_pt_;
   Float_t         jet5_eta_;
   Float_t         jet5_btag_;
   Float_t         jet6_pt_;
   Float_t         jet6_eta_;
   Float_t         jet6_btag_;
   Float_t         jet7_pt_;
   Float_t         jet7_eta_;
   Float_t         jet7_btag_;
   Float_t         jet8_pt_;
   Float_t         jet8_eta_;
   Float_t         jet8_btag_;
   Float_t         jet1_phi_;
   Float_t         jet1_energy_;
   Float_t         jet2_phi_;
   Float_t         jet2_energy_;
   Float_t         jet3_phi_;
   Float_t         jet3_energy_;
   Float_t         jet4_phi_;
   Float_t         jet4_energy_;
   Float_t         jet5_phi_;
   Float_t         jet5_energy_;
   Float_t         jet6_phi_;
   Float_t         jet6_energy_;
   Float_t         jet7_phi_;
   Float_t         jet7_energy_;
   Float_t         jet8_phi_;
   Float_t         jet8_energy_;
   Float_t         lead_pT_;
   Float_t         sublead_pT_;
   Float_t         leadptoM_;
   Float_t         subleadptoM_;
   Float_t         leadIDMVA_;
   Float_t         subleadIDMVA_;
   Float_t         lead_eta_;
   Float_t         sublead_eta_;
   Float_t         leadPSV_;
   Float_t         subleadPSV_;
   Float_t         lead_phi_;
   Float_t         sublead_phi_;
   Float_t         dipho_cosphi_;
   Float_t         dipho_rapidity_;
   Float_t         dipho_pt_;
   Float_t         dipho_pt_over_mass_;
   Float_t         met_;
   Float_t         log_met_;
   Float_t         met_phi_;
   Float_t         helicity_angle_;
   Float_t         m_ggj_;
   Float_t         m_jjj_;
   Float_t         top_candidates_1_;
   Float_t         top_candidates_2_;
   Float_t         top_candidates_3_;
   Float_t         top_candidates_4_;
   Float_t         top_candidates_5_;
   Float_t         top_candidates_6_;
   Float_t         top_candidates_7_;
   Float_t         top_candidates_8_;
   Float_t         top_candidates_9_;
   Float_t         top_candidates_10_;
   Float_t         top_candidates_11_;
   Float_t         top_candidates_12_;
   Float_t         chi2_value_;
   Float_t         chi2_bjet_pt_;
   Float_t         chi2_wjet1_pt_;
   Float_t         chi2_wjet2_pt_;
   Float_t         chi2_bjet_eta_;
   Float_t         chi2_wjet1_eta_;
   Float_t         chi2_wjet2_eta_;
   Float_t         chi2_wjets_deltaR_;
   Float_t         chi2_wboson_pt_;
   Float_t         chi2_wboson_eta_;
   Float_t         chi2_wboson_mass_;
   Float_t         chi2_wboson_deltaR_bjet_;
   Float_t         chi2_tbw_mass_;
   Float_t         chi2_tbw_pt_;
   Float_t         chi2_tbw_eta_;
   Float_t         chi2_tbw_deltaR_dipho_;
   Float_t         chi2_tprime_ptOverM_;
   Float_t         chi2_tprime_eta_;
   Float_t         chi2_tprime_deltaR_tbw_;
   Float_t         chi2_tprime_deltaR_dipho_;
   Float_t         chi2_bjet_btagScores_;
   Float_t         chi2_wjet1_btagScores_;
   Float_t         chi2_wjet2_btagScores_;
   Float_t         tprime_pt_ratio_;
   Float_t         chi2_bjet_ptOverM_;
   Float_t         chi2_wjet1_ptOverM_;
   Float_t         chi2_wjet2_ptOverM_;
   Float_t         chi2_wboson_ptOverM_;
   Float_t         chi2_tbw_ptOverM_;
   Float_t         helicity_tprime_;
   Float_t         jet1_ptOverM_;
   Float_t         jet2_ptOverM_;
   Float_t         jet3_ptOverM_;
   Float_t         jet4_ptOverM_;

   // List of branches
   TBranch        *b_mva_branches;   //!
   TBranch        *b_year_;   //!
   TBranch        *b_evt_;   //!
   TBranch        *b_run_;   //!
   TBranch        *b_lumi_;   //!
   TBranch        *b_evt_weight_;   //!
   TBranch        *b_label_;   //!
   TBranch        *b_multi_label_;   //!
   TBranch        *b_signal_mass_label_;   //!
   TBranch        *b_signal_mass_category_;   //!
   TBranch        *b_data_sideband_label_;   //!
   TBranch        *b_genPhotonId_;   //!
   TBranch        *b_process_id_;   //!
   TBranch        *b_rand_;   //!
   TBranch        *b_super_rand_;   //!
   TBranch        *b_mass_;   //!
   TBranch        *b_lead_sigmaEtoE_;   //!
   TBranch        *b_sublead_sigmaEtoE_;   //!
   TBranch        *b_objects_;   //!
   TBranch        *b_objects_boosted_;   //!
   TBranch        *b_top_candidates_;   //!
   TBranch        *b_maxIDMVA_;   //!
   TBranch        *b_minIDMVA_;   //!
   TBranch        *b_max2_btag_;   //!
   TBranch        *b_max1_btag_;   //!
   TBranch        *b_dipho_delta_R;   //!
   TBranch        *b_njets_;   //!
   TBranch        *b_nbjets_;   //!
   TBranch        *b_ht_;   //!
   TBranch        *b_top_tag_score_;   //!
   TBranch        *b_top_tag_mass_;   //!
   TBranch        *b_top_tag_pt_;   //!
   TBranch        *b_top_tag_eta_;   //!
   TBranch        *b_top_tag_phi_;   //!
   TBranch        *b_jet1_pt_;   //!
   TBranch        *b_jet1_eta_;   //!
   TBranch        *b_jet1_btag_;   //!
   TBranch        *b_jet2_pt_;   //!
   TBranch        *b_jet2_eta_;   //!
   TBranch        *b_jet2_btag_;   //!
   TBranch        *b_jet3_pt_;   //!
   TBranch        *b_jet3_eta_;   //!
   TBranch        *b_jet3_btag_;   //!
   TBranch        *b_jet4_pt_;   //!
   TBranch        *b_jet4_eta_;   //!
   TBranch        *b_jet4_btag_;   //!
   TBranch        *b_jet5_pt_;   //!
   TBranch        *b_jet5_eta_;   //!
   TBranch        *b_jet5_btag_;   //!
   TBranch        *b_jet6_pt_;   //!
   TBranch        *b_jet6_eta_;   //!
   TBranch        *b_jet6_btag_;   //!
   TBranch        *b_jet7_pt_;   //!
   TBranch        *b_jet7_eta_;   //!
   TBranch        *b_jet7_btag_;   //!
   TBranch        *b_jet8_pt_;   //!
   TBranch        *b_jet8_eta_;   //!
   TBranch        *b_jet8_btag_;   //!
   TBranch        *b_jet1_phi_;   //!
   TBranch        *b_jet1_energy_;   //!
   TBranch        *b_jet2_phi_;   //!
   TBranch        *b_jet2_energy_;   //!
   TBranch        *b_jet3_phi_;   //!
   TBranch        *b_jet3_energy_;   //!
   TBranch        *b_jet4_phi_;   //!
   TBranch        *b_jet4_energy_;   //!
   TBranch        *b_jet5_phi_;   //!
   TBranch        *b_jet5_energy_;   //!
   TBranch        *b_jet6_phi_;   //!
   TBranch        *b_jet6_energy_;   //!
   TBranch        *b_jet7_phi_;   //!
   TBranch        *b_jet7_energy_;   //!
   TBranch        *b_jet8_phi_;   //!
   TBranch        *b_jet8_energy_;   //!
   TBranch        *b_lead_pT_;   //!
   TBranch        *b_sublead_pT_;   //!
   TBranch        *b_leadptoM_;   //!
   TBranch        *b_subleadptoM_;   //!
   TBranch        *b_leadIDMVA_;   //!
   TBranch        *b_subleadIDMVA_;   //!
   TBranch        *b_lead_eta_;   //!
   TBranch        *b_sublead_eta_;   //!
   TBranch        *b_leadPSV_;   //!
   TBranch        *b_subleadPSV_;   //!
   TBranch        *b_lead_phi_;   //!
   TBranch        *b_sublead_phi_;   //!
   TBranch        *b_dipho_cosphi_;   //!
   TBranch        *b_dipho_rapidity_;   //!
   TBranch        *b_dipho_pt_;   //!
   TBranch        *b_dipho_pt_over_mass_;   //!
   TBranch        *b_met_;   //!
   TBranch        *b_log_met_;   //!
   TBranch        *b_met_phi_;   //!
   TBranch        *b_helicity_angle_;   //!
   TBranch        *b_m_ggj_;   //!
   TBranch        *b_m_jjj_;   //!
   TBranch        *b_top_candidates_1_;   //!
   TBranch        *b_top_candidates_2_;   //!
   TBranch        *b_top_candidates_3_;   //!
   TBranch        *b_top_candidates_4_;   //!
   TBranch        *b_top_candidates_5_;   //!
   TBranch        *b_top_candidates_6_;   //!
   TBranch        *b_top_candidates_7_;   //!
   TBranch        *b_top_candidates_8_;   //!
   TBranch        *b_top_candidates_9_;   //!
   TBranch        *b_top_candidates_10_;   //!
   TBranch        *b_top_candidates_11_;   //!
   TBranch        *b_top_candidates_12_;   //!
   TBranch        *b_chi2_value_;   //!
   TBranch        *b_chi2_bjet_pt_;   //!
   TBranch        *b_chi2_wjet1_pt_;   //!
   TBranch        *b_chi2_wjet2_pt_;   //!
   TBranch        *b_chi2_bjet_eta_;   //!
   TBranch        *b_chi2_wjet1_eta_;   //!
   TBranch        *b_chi2_wjet2_eta_;   //!
   TBranch        *b_chi2_wjets_deltaR_;   //!
   TBranch        *b_chi2_wboson_pt_;   //!
   TBranch        *b_chi2_wboson_eta_;   //!
   TBranch        *b_chi2_wboson_mass_;   //!
   TBranch        *b_chi2_wboson_deltaR_bjet_;   //!
   TBranch        *b_chi2_tbw_mass_;   //!
   TBranch        *b_chi2_tbw_pt_;   //!
   TBranch        *b_chi2_tbw_eta_;   //!
   TBranch        *b_chi2_tbw_deltaR_dipho_;   //!
   TBranch        *b_chi2_tprime_ptOverM_;   //!
   TBranch        *b_chi2_tprime_eta_;   //!
   TBranch        *b_chi2_tprime_deltaR_tbw_;   //!
   TBranch        *b_chi2_tprime_deltaR_dipho_;   //!
   TBranch        *b_chi2_bjet_btagScores_;   //!
   TBranch        *b_chi2_wjet1_btagScores_;   //!
   TBranch        *b_chi2_wjet2_btagScores_;   //!
   TBranch        *b_tprime_pt_ratio_;   //!
   TBranch        *b_chi2_bjet_ptOverM_;   //!
   TBranch        *b_chi2_wjet1_ptOverM_;   //!
   TBranch        *b_chi2_wjet2_ptOverM_;   //!
   TBranch        *b_chi2_wboson_ptOverM_;   //!
   TBranch        *b_chi2_tbw_ptOverM_;   //!
   TBranch        *b_helicity_tprime_;   //!
   TBranch        *b_jet1_ptOverM_;   //!
   TBranch        *b_jet2_ptOverM_;   //!
   TBranch        *b_jet3_ptOverM_;   //!
   TBranch        *b_jet4_ptOverM_;   //!

   t(TTree *tree=0);
   virtual ~t();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     examine(TString name, Float_t var);

   map<TString, Int_t> counter_manager;
   map<TString, Int_t>::iterator iter;
};

#endif

#ifdef t_cxx
t::t(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../MVABaby_ttHHadronic_v5.7_tprimetH_impute_hct_BDT_FCNC.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../MVABaby_ttHHadronic_v5.7_tprimetH_impute_hct_BDT_FCNC.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
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

void t::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mva_branches = 0;
   objects_ = 0;
   objects_boosted_ = 0;
   top_candidates_ = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mva_branches", &mva_branches, &b_mva_branches);
   fChain->SetBranchAddress("year_", &year_, &b_year_);
   fChain->SetBranchAddress("evt_", &evt_, &b_evt_);
   fChain->SetBranchAddress("run_", &run_, &b_run_);
   fChain->SetBranchAddress("lumi_", &lumi_, &b_lumi_);
   fChain->SetBranchAddress("evt_weight_", &evt_weight_, &b_evt_weight_);
   fChain->SetBranchAddress("label_", &label_, &b_label_);
   fChain->SetBranchAddress("multi_label_", &multi_label_, &b_multi_label_);
   fChain->SetBranchAddress("signal_mass_label_", &signal_mass_label_, &b_signal_mass_label_);
   fChain->SetBranchAddress("signal_mass_category_", &signal_mass_category_, &b_signal_mass_category_);
   fChain->SetBranchAddress("data_sideband_label_", &data_sideband_label_, &b_data_sideband_label_);
   fChain->SetBranchAddress("genPhotonId_", &genPhotonId_, &b_genPhotonId_);
   fChain->SetBranchAddress("process_id_", &process_id_, &b_process_id_);
   fChain->SetBranchAddress("rand_", &rand_, &b_rand_);
   fChain->SetBranchAddress("super_rand_", &super_rand_, &b_super_rand_);
   fChain->SetBranchAddress("mass_", &mass_, &b_mass_);
   fChain->SetBranchAddress("lead_sigmaEtoE_", &lead_sigmaEtoE_, &b_lead_sigmaEtoE_);
   fChain->SetBranchAddress("sublead_sigmaEtoE_", &sublead_sigmaEtoE_, &b_sublead_sigmaEtoE_);
   fChain->SetBranchAddress("objects_", &objects_, &b_objects_);
   fChain->SetBranchAddress("objects_boosted_", &objects_boosted_, &b_objects_boosted_);
   fChain->SetBranchAddress("top_candidates_", &top_candidates_, &b_top_candidates_);
   fChain->SetBranchAddress("maxIDMVA_", &maxIDMVA_, &b_maxIDMVA_);
   fChain->SetBranchAddress("minIDMVA_", &minIDMVA_, &b_minIDMVA_);
   fChain->SetBranchAddress("max2_btag_", &max2_btag_, &b_max2_btag_);
   fChain->SetBranchAddress("max1_btag_", &max1_btag_, &b_max1_btag_);
   fChain->SetBranchAddress("dipho_delta_R", &dipho_delta_R, &b_dipho_delta_R);
   fChain->SetBranchAddress("njets_", &njets_, &b_njets_);
   fChain->SetBranchAddress("nbjets_", &nbjets_, &b_nbjets_);
   fChain->SetBranchAddress("ht_", &ht_, &b_ht_);
   fChain->SetBranchAddress("top_tag_score_", &top_tag_score_, &b_top_tag_score_);
   fChain->SetBranchAddress("top_tag_mass_", &top_tag_mass_, &b_top_tag_mass_);
   fChain->SetBranchAddress("top_tag_pt_", &top_tag_pt_, &b_top_tag_pt_);
   fChain->SetBranchAddress("top_tag_eta_", &top_tag_eta_, &b_top_tag_eta_);
   fChain->SetBranchAddress("top_tag_phi_", &top_tag_phi_, &b_top_tag_phi_);
   fChain->SetBranchAddress("jet1_pt_", &jet1_pt_, &b_jet1_pt_);
   fChain->SetBranchAddress("jet1_eta_", &jet1_eta_, &b_jet1_eta_);
   fChain->SetBranchAddress("jet1_btag_", &jet1_btag_, &b_jet1_btag_);
   fChain->SetBranchAddress("jet2_pt_", &jet2_pt_, &b_jet2_pt_);
   fChain->SetBranchAddress("jet2_eta_", &jet2_eta_, &b_jet2_eta_);
   fChain->SetBranchAddress("jet2_btag_", &jet2_btag_, &b_jet2_btag_);
   fChain->SetBranchAddress("jet3_pt_", &jet3_pt_, &b_jet3_pt_);
   fChain->SetBranchAddress("jet3_eta_", &jet3_eta_, &b_jet3_eta_);
   fChain->SetBranchAddress("jet3_btag_", &jet3_btag_, &b_jet3_btag_);
   fChain->SetBranchAddress("jet4_pt_", &jet4_pt_, &b_jet4_pt_);
   fChain->SetBranchAddress("jet4_eta_", &jet4_eta_, &b_jet4_eta_);
   fChain->SetBranchAddress("jet4_btag_", &jet4_btag_, &b_jet4_btag_);
   fChain->SetBranchAddress("jet5_pt_", &jet5_pt_, &b_jet5_pt_);
   fChain->SetBranchAddress("jet5_eta_", &jet5_eta_, &b_jet5_eta_);
   fChain->SetBranchAddress("jet5_btag_", &jet5_btag_, &b_jet5_btag_);
   fChain->SetBranchAddress("jet6_pt_", &jet6_pt_, &b_jet6_pt_);
   fChain->SetBranchAddress("jet6_eta_", &jet6_eta_, &b_jet6_eta_);
   fChain->SetBranchAddress("jet6_btag_", &jet6_btag_, &b_jet6_btag_);
   fChain->SetBranchAddress("jet7_pt_", &jet7_pt_, &b_jet7_pt_);
   fChain->SetBranchAddress("jet7_eta_", &jet7_eta_, &b_jet7_eta_);
   fChain->SetBranchAddress("jet7_btag_", &jet7_btag_, &b_jet7_btag_);
   fChain->SetBranchAddress("jet8_pt_", &jet8_pt_, &b_jet8_pt_);
   fChain->SetBranchAddress("jet8_eta_", &jet8_eta_, &b_jet8_eta_);
   fChain->SetBranchAddress("jet8_btag_", &jet8_btag_, &b_jet8_btag_);
   fChain->SetBranchAddress("jet1_phi_", &jet1_phi_, &b_jet1_phi_);
   fChain->SetBranchAddress("jet1_energy_", &jet1_energy_, &b_jet1_energy_);
   fChain->SetBranchAddress("jet2_phi_", &jet2_phi_, &b_jet2_phi_);
   fChain->SetBranchAddress("jet2_energy_", &jet2_energy_, &b_jet2_energy_);
   fChain->SetBranchAddress("jet3_phi_", &jet3_phi_, &b_jet3_phi_);
   fChain->SetBranchAddress("jet3_energy_", &jet3_energy_, &b_jet3_energy_);
   fChain->SetBranchAddress("jet4_phi_", &jet4_phi_, &b_jet4_phi_);
   fChain->SetBranchAddress("jet4_energy_", &jet4_energy_, &b_jet4_energy_);
   fChain->SetBranchAddress("jet5_phi_", &jet5_phi_, &b_jet5_phi_);
   fChain->SetBranchAddress("jet5_energy_", &jet5_energy_, &b_jet5_energy_);
   fChain->SetBranchAddress("jet6_phi_", &jet6_phi_, &b_jet6_phi_);
   fChain->SetBranchAddress("jet6_energy_", &jet6_energy_, &b_jet6_energy_);
   fChain->SetBranchAddress("jet7_phi_", &jet7_phi_, &b_jet7_phi_);
   fChain->SetBranchAddress("jet7_energy_", &jet7_energy_, &b_jet7_energy_);
   fChain->SetBranchAddress("jet8_phi_", &jet8_phi_, &b_jet8_phi_);
   fChain->SetBranchAddress("jet8_energy_", &jet8_energy_, &b_jet8_energy_);
   fChain->SetBranchAddress("lead_pT_", &lead_pT_, &b_lead_pT_);
   fChain->SetBranchAddress("sublead_pT_", &sublead_pT_, &b_sublead_pT_);
   fChain->SetBranchAddress("leadptoM_", &leadptoM_, &b_leadptoM_);
   fChain->SetBranchAddress("subleadptoM_", &subleadptoM_, &b_subleadptoM_);
   fChain->SetBranchAddress("leadIDMVA_", &leadIDMVA_, &b_leadIDMVA_);
   fChain->SetBranchAddress("subleadIDMVA_", &subleadIDMVA_, &b_subleadIDMVA_);
   fChain->SetBranchAddress("lead_eta_", &lead_eta_, &b_lead_eta_);
   fChain->SetBranchAddress("sublead_eta_", &sublead_eta_, &b_sublead_eta_);
   fChain->SetBranchAddress("leadPSV_", &leadPSV_, &b_leadPSV_);
   fChain->SetBranchAddress("subleadPSV_", &subleadPSV_, &b_subleadPSV_);
   fChain->SetBranchAddress("lead_phi_", &lead_phi_, &b_lead_phi_);
   fChain->SetBranchAddress("sublead_phi_", &sublead_phi_, &b_sublead_phi_);
   fChain->SetBranchAddress("dipho_cosphi_", &dipho_cosphi_, &b_dipho_cosphi_);
   fChain->SetBranchAddress("dipho_rapidity_", &dipho_rapidity_, &b_dipho_rapidity_);
   fChain->SetBranchAddress("dipho_pt_", &dipho_pt_, &b_dipho_pt_);
   fChain->SetBranchAddress("dipho_pt_over_mass_", &dipho_pt_over_mass_, &b_dipho_pt_over_mass_);
   fChain->SetBranchAddress("met_", &met_, &b_met_);
   fChain->SetBranchAddress("log_met_", &log_met_, &b_log_met_);
   fChain->SetBranchAddress("met_phi_", &met_phi_, &b_met_phi_);
   fChain->SetBranchAddress("helicity_angle_", &helicity_angle_, &b_helicity_angle_);
   fChain->SetBranchAddress("m_ggj_", &m_ggj_, &b_m_ggj_);
   fChain->SetBranchAddress("m_jjj_", &m_jjj_, &b_m_jjj_);
   fChain->SetBranchAddress("top_candidates_1_", &top_candidates_1_, &b_top_candidates_1_);
   fChain->SetBranchAddress("top_candidates_2_", &top_candidates_2_, &b_top_candidates_2_);
   fChain->SetBranchAddress("top_candidates_3_", &top_candidates_3_, &b_top_candidates_3_);
   fChain->SetBranchAddress("top_candidates_4_", &top_candidates_4_, &b_top_candidates_4_);
   fChain->SetBranchAddress("top_candidates_5_", &top_candidates_5_, &b_top_candidates_5_);
   fChain->SetBranchAddress("top_candidates_6_", &top_candidates_6_, &b_top_candidates_6_);
   fChain->SetBranchAddress("top_candidates_7_", &top_candidates_7_, &b_top_candidates_7_);
   fChain->SetBranchAddress("top_candidates_8_", &top_candidates_8_, &b_top_candidates_8_);
   fChain->SetBranchAddress("top_candidates_9_", &top_candidates_9_, &b_top_candidates_9_);
   fChain->SetBranchAddress("top_candidates_10_", &top_candidates_10_, &b_top_candidates_10_);
   fChain->SetBranchAddress("top_candidates_11_", &top_candidates_11_, &b_top_candidates_11_);
   fChain->SetBranchAddress("top_candidates_12_", &top_candidates_12_, &b_top_candidates_12_);
   fChain->SetBranchAddress("chi2_value_", &chi2_value_, &b_chi2_value_);
   fChain->SetBranchAddress("chi2_bjet_pt_", &chi2_bjet_pt_, &b_chi2_bjet_pt_);
   fChain->SetBranchAddress("chi2_wjet1_pt_", &chi2_wjet1_pt_, &b_chi2_wjet1_pt_);
   fChain->SetBranchAddress("chi2_wjet2_pt_", &chi2_wjet2_pt_, &b_chi2_wjet2_pt_);
   fChain->SetBranchAddress("chi2_bjet_eta_", &chi2_bjet_eta_, &b_chi2_bjet_eta_);
   fChain->SetBranchAddress("chi2_wjet1_eta_", &chi2_wjet1_eta_, &b_chi2_wjet1_eta_);
   fChain->SetBranchAddress("chi2_wjet2_eta_", &chi2_wjet2_eta_, &b_chi2_wjet2_eta_);
   fChain->SetBranchAddress("chi2_wjets_deltaR_", &chi2_wjets_deltaR_, &b_chi2_wjets_deltaR_);
   fChain->SetBranchAddress("chi2_wboson_pt_", &chi2_wboson_pt_, &b_chi2_wboson_pt_);
   fChain->SetBranchAddress("chi2_wboson_eta_", &chi2_wboson_eta_, &b_chi2_wboson_eta_);
   fChain->SetBranchAddress("chi2_wboson_mass_", &chi2_wboson_mass_, &b_chi2_wboson_mass_);
   fChain->SetBranchAddress("chi2_wboson_deltaR_bjet_", &chi2_wboson_deltaR_bjet_, &b_chi2_wboson_deltaR_bjet_);
   fChain->SetBranchAddress("chi2_tbw_mass_", &chi2_tbw_mass_, &b_chi2_tbw_mass_);
   fChain->SetBranchAddress("chi2_tbw_pt_", &chi2_tbw_pt_, &b_chi2_tbw_pt_);
   fChain->SetBranchAddress("chi2_tbw_eta_", &chi2_tbw_eta_, &b_chi2_tbw_eta_);
   fChain->SetBranchAddress("chi2_tbw_deltaR_dipho_", &chi2_tbw_deltaR_dipho_, &b_chi2_tbw_deltaR_dipho_);
   fChain->SetBranchAddress("chi2_tprime_ptOverM_", &chi2_tprime_ptOverM_, &b_chi2_tprime_ptOverM_);
   fChain->SetBranchAddress("chi2_tprime_eta_", &chi2_tprime_eta_, &b_chi2_tprime_eta_);
   fChain->SetBranchAddress("chi2_tprime_deltaR_tbw_", &chi2_tprime_deltaR_tbw_, &b_chi2_tprime_deltaR_tbw_);
   fChain->SetBranchAddress("chi2_tprime_deltaR_dipho_", &chi2_tprime_deltaR_dipho_, &b_chi2_tprime_deltaR_dipho_);
   fChain->SetBranchAddress("chi2_bjet_btagScores_", &chi2_bjet_btagScores_, &b_chi2_bjet_btagScores_);
   fChain->SetBranchAddress("chi2_wjet1_btagScores_", &chi2_wjet1_btagScores_, &b_chi2_wjet1_btagScores_);
   fChain->SetBranchAddress("chi2_wjet2_btagScores_", &chi2_wjet2_btagScores_, &b_chi2_wjet2_btagScores_);
   fChain->SetBranchAddress("tprime_pt_ratio_", &tprime_pt_ratio_, &b_tprime_pt_ratio_);
   fChain->SetBranchAddress("chi2_bjet_ptOverM_", &chi2_bjet_ptOverM_, &b_chi2_bjet_ptOverM_);
   fChain->SetBranchAddress("chi2_wjet1_ptOverM_", &chi2_wjet1_ptOverM_, &b_chi2_wjet1_ptOverM_);
   fChain->SetBranchAddress("chi2_wjet2_ptOverM_", &chi2_wjet2_ptOverM_, &b_chi2_wjet2_ptOverM_);
   fChain->SetBranchAddress("chi2_wboson_ptOverM_", &chi2_wboson_ptOverM_, &b_chi2_wboson_ptOverM_);
   fChain->SetBranchAddress("chi2_tbw_ptOverM_", &chi2_tbw_ptOverM_, &b_chi2_tbw_ptOverM_);
   fChain->SetBranchAddress("helicity_tprime_", &helicity_tprime_, &b_helicity_tprime_);
   fChain->SetBranchAddress("jet1_ptOverM_", &jet1_ptOverM_, &b_jet1_ptOverM_);
   fChain->SetBranchAddress("jet2_ptOverM_", &jet2_ptOverM_, &b_jet2_ptOverM_);
   fChain->SetBranchAddress("jet3_ptOverM_", &jet3_ptOverM_, &b_jet3_ptOverM_);
   fChain->SetBranchAddress("jet4_ptOverM_", &jet4_ptOverM_, &b_jet4_ptOverM_);
   Notify();

   counter_manager["evt_"]                      = 0;
   counter_manager["evt_weight_"]               = 0;
   counter_manager["maxIDMVA_"]                 = 0;
   counter_manager["minIDMVA_"]                 = 0;
   counter_manager["max1_btag_"]                = 0;
   counter_manager["max2_btag_"]                = 0;
   counter_manager["dipho_delta_R"]             = 0;
   counter_manager["njets_"]                    = 0;
   counter_manager["nbjets_"]                   = 0;
   counter_manager["ht_"]                       = 0;
   counter_manager["leadptoM_"]                 = 0;
   counter_manager["subleadptoM_"]              = 0;
   counter_manager["lead_eta_"]                 = 0;
   counter_manager["sublead_eta_"]              = 0;
   counter_manager["jet1_ptOverM_"]             = 0;
   counter_manager["jet1_eta_"]                 = 0;
   counter_manager["jet1_btag_"]                = 0;
   counter_manager["jet2_ptOverM_"]             = 0;
   counter_manager["jet2_eta_"]                 = 0;
   counter_manager["jet2_btag_"]                = 0;
   counter_manager["jet3_ptOverM_"]             = 0;
   counter_manager["jet3_eta_"]                 = 0;
   counter_manager["jet3_btag_"]                = 0;
   counter_manager["jet4_ptOverM_"]             = 0;
   counter_manager["jet4_eta_"]                 = 0;
   counter_manager["jet4_btag_"]                = 0;
   counter_manager["leadPSV_"]                  = 0;
   counter_manager["subleadPSV_"]               = 0;
   counter_manager["dipho_cosphi_"]             = 0;
   counter_manager["dipho_rapidity_"]           = 0;
   counter_manager["met_"]                      = 0;
   counter_manager["dipho_pt_over_mass_"]       = 0;
   counter_manager["helicity_angle_"]           = 0;
   counter_manager["chi2_value_"]               = 0;
   counter_manager["chi2_bjet_ptOverM_"]        = 0;
   counter_manager["chi2_bjet_eta_"]            = 0;
   counter_manager["chi2_bjet_btagScores_"]     = 0;
   counter_manager["chi2_wjet1_ptOverM_"]       = 0;
   counter_manager["chi2_wjet1_eta_"]           = 0;
   counter_manager["chi2_wjet1_btagScores_"]    = 0;
   counter_manager["chi2_wjet2_ptOverM_"]       = 0;
   counter_manager["chi2_wjet2_eta_"]           = 0;
   counter_manager["chi2_wjet2_btagScores_"]    = 0;
   counter_manager["chi2_wjets_deltaR_"]        = 0;
   counter_manager["chi2_wboson_ptOverM_"]      = 0;
   counter_manager["chi2_wboson_eta_"]          = 0;
   counter_manager["chi2_wboson_mass_"]         = 0;
   counter_manager["chi2_wboson_deltaR_bjet_"]  = 0;
   counter_manager["chi2_tbw_mass_"]            = 0;
   counter_manager["chi2_tbw_ptOverM_"]         = 0;
   counter_manager["chi2_tbw_eta_"]             = 0;
   counter_manager["chi2_tbw_deltaR_dipho_"]    = 0;
   counter_manager["chi2_tprime_ptOverM_"]      = 0;
   counter_manager["chi2_tprime_eta_"]          = 0;
   counter_manager["chi2_tprime_deltaR_tbw_"]   = 0;
   counter_manager["chi2_tprime_deltaR_dipho_"] = 0;
   counter_manager["tprime_pt_ratio_"]          = 0;
   counter_manager["helicity_tprime_"]          = 0;
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
Int_t t::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void t::examine(TString name, Float_t var)
{
    if(name == "evt_" && var < 0)
    {
        printf("%s is a negative value! process_id_ = %d, ", name.Data(), process_id_);
        iter = counter_manager.find(name.Data());
        iter->second += 1;
        cout << iter->first << ": " << iter->second << endl;
    }

    if( isnan(var) )
    {
        printf("%s is a NaN value! process_id_ = %d, ", name.Data(), process_id_);
        iter = counter_manager.find(name.Data());
        iter->second += 1;
        cout << iter->first << ": " << iter->second << endl;
    }

    if( isinf(var) ) printf("%s is inf value\n", name.Data());
}
#endif // #ifdef t_cxx
