#ifndef MakeMVABabies_ttHHadronic_h 
#define MakeMVABabies_ttHHadronic_h

#include <string>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH2.h"
#include "TString.h"
#include "Math/LorentzVector.h"
#include "Math/GenVector/LorentzVector.h"

using namespace std;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class BabyMaker { //{{{
  public:
    BabyMaker() {};
    ~BabyMaker() {
      if (BabyFile_) delete BabyFile_;
      if (BabyTree_) delete BabyTree_;
      if (BabyTree_maxPhotonIDMVA_) delete BabyTree_maxPhotonIDMVA_;
      if (BabyTree_minPhotonIDMVA_) delete BabyTree_minPhotonIDMVA_;
      if (BabyTree_fakePhotonIDMVA_) delete BabyTree_fakePhotonIDMVA_;
      if (BabyTree_lowPhotonSideband_) delete BabyTree_lowPhotonSideband_;
    }
    void ScanChain(TChain* chain, TString name_output_file, TString treeName, TString year, TString ext, TString bkg_options, TString mYear, TString idx, bool fcnc, bool blind, bool fast, int nEvents, string skimFilePrefix);
    void MakeBabyNtuple(const char *);
    void InitBabyNtuple();
    void FillBabyNtuple();
    void FillBabyNtuple_fakePhoton();
    void FillBabyNtuple_lowPhotonSideband();
    void CloseBabyNtuple();
    
    void Enable_flag_for_Maxime() {produce_ntuples_for_Maxime = true;}
    void Enable_flag_for_fakePhotonStudy() {produce_ntuples_for_fakePhotonStudy = true;}

  private:
    TFile *BabyFile_;
    TTree *BabyTree_;
    TTree *BabyTree_maxPhotonIDMVA_;
    TTree *BabyTree_minPhotonIDMVA_;
    TTree *BabyTree_fakePhotonIDMVA_;
    TTree *BabyTree_lowPhotonSideband_;

    bool debug;
    bool apply_preselection;
    bool produce_ntuples_for_Maxime;
    bool produce_ntuples_for_fakePhotonStudy;
    bool produce_ntuples_for_MVA;

    // Variable names
    vector<string> mva_branches = {"maxIDMVA_", "minIDMVA_", "max2_btag_", "max1_btag_", "dipho_delta_R", "njets_", "ht_", "leadptoM_", "subleadptoM_", "leadIDMVA_", "subleadIDMVA_", "lead_eta_", "sublead_eta_", "jet1_pt_", "jet1_eta_", "jet1_btag_", "jet2_pt_", "jet2_eta_", "jet2_btag_", "jet3_pt_", "jet3_eta_", "jet3_btag_", "jet4_pt_", "jet4_eta_", "jet4_btag_", "jet5_pt_", "jet5_eta_", "jet5_btag_", "jet6_pt_", "jet6_eta_", "jet6_btag_", "leadPSV_", "subleadPSV_", "dipho_cosphi_", "dipho_rapidity_", "met_"};
    //{"maxIDMVA_", "minIDMVA_", "max2_btag_", "max1_btag_", "dipho_delta_R", "njets_", "nbjets_", "ht_", "jet1_pt_", "jet1_eta_", "jet1_btag_", "jet2_pt_", "jet2_eta_", "jet2_btag_", "jet3_pt_", "jet3_eta_", "jet3_btag_", "jet4_pt_", "jet4_eta_", "jet4_btag_", "jet5_pt_", "jet5_eta_", "jet5_btag_", "jet6_pt_", "jet6_eta_", "jet6_btag_", "jet7_pt_", "jet7_eta_", "jet7_btag_", "jet8_pt_", "jet8_eta_", "jet8_btag_", "jet1_phi_", "jet1_energy_", "jet2_phi_", "jet2_energy_", "jet3_phi_", "jet3_energy_", "jet4_phi_", "jet4_energy_", "jet5_phi_", "jet5_energy_", "jet6_phi_", "jet6_energy_", "jet7_phi_", "jet7_energy_", "jet8_phi_", "jet8_energy_", "lead_pT_", "sublead_pT_", "leadptoM_", "subleadptoM_", "leadIDMVA_", "subleadIDMVA_", "lead_eta_", "sublead_eta_", "leadPSV_", "subleadPSV_", "lead_phi_", "sublead_phi_", "dipho_cosphi_", "dipho_rapidity_", "dipho_pt_", "dipho_pt_over_mass_", "met_", "log_met_", "met_phi_", "helicity_angle_", "m_ggj_", "m_jjj_", "chi2_value_", "chi2_bjet_pt_", "chi2_wjet1_pt_", "chi2_wjet2_pt_", "chi2_bjet_eta_", "chi2_wjet1_eta_", "chi2_wjet2_eta_", "chi2_wjets_deltaR_", "chi2_wboson_pt_", "chi2_wboson_eta_", "chi2_wboson_mass_", "chi2_wboson_deltaR_bjet_", "chi2_tbw_mass_", "chi2_tbw_pt_", "chi2_tbw_eta_", "chi2_tbw_deltaR_dipho_", "chi2_tprime_ptOverM_", "chi2_tprime_eta_", "chi2_tprime_deltaR_tbw_", "chi2_tprime_deltaR_dipho_", "chi2_bjet_btagScores_", "chi2_wjet1_btagScores_", "chi2_wjet2_btagScores_", "tprime_pt_ratio_", "chi2_bjet_ptOverM_", "chi2_wjet1_ptOverM_", "chi2_wjet2_ptOverM_", "chi2_wboson_ptOverM_", "chi2_tbw_ptOverM_", "helicity_tprime_", "jet1_ptOverM_", "jet2_ptOverM_", "jet3_ptOverM_", "jet4_ptOverM_"}
    
    //----------------------------------------------------------------------------------------------------
    // For Maxime
    //----------------------------------------------------------------------------------------------------
    float dipho_mass_    ;
    float tprime_mass_   ;
    float tprime_mtilde_ ;
    float bdtg_score_nrb_m600_m700_   ;
    float bdtg_score_nrb_m800_m1000_  ;
    float bdtg_score_nrb_m1100_m1200_ ;
    float bdtg_score_smh_m600_m700_   ;
    float bdtg_score_smh_m800_m1000_  ;
    float bdtg_score_smh_m1100_m1200_ ;
    float bdtg_score_smh_m600_m700_withNRBcut_   ;
    float bdtg_score_smh_m800_m1000_withNRBcut_  ;
    float bdtg_score_smh_m1100_m1200_withNRBcut_ ;

    //----------------------------------------------------------------------------------------------------
    // my full set var
    //----------------------------------------------------------------------------------------------------
    int		                year_;
    unsigned long long		evt_;
    unsigned long long		run_;
    unsigned long long		lumi_;
    int 	                label_;
    int                     multi_label_;
    int		                data_sideband_label_;
    int		                signal_mass_label_;
    int                     signal_mass_category_;
    float	                evt_weight_;
    int 	                process_id_;
    int                     genPhotonId_;
    float 	                rand_;
    float                   super_rand_;
    float                   mass_;
    float                   lead_sigmaEtoE_;
    float                   sublead_sigmaEtoE_;

    // Variable declarations
    float       fake_photon_IDMVA_;
    float       maxIDMVA_;
    float       minIDMVA_;
    float       max2_btag_;
    float       max1_btag_;
    float       dipho_delta_R;
    float   	njets_;
    float	    nbjets_;
    float	    ht_;

    float	    jet1_pt_;
    float       jet1_eta_;
    float 	    jet1_btag_;
    float       jet2_pt_;
    float       jet2_eta_;
    float       jet2_btag_;
    float       jet3_pt_;
    float       jet3_eta_;
    float       jet3_btag_;
    float       jet4_pt_;
    float       jet4_eta_;
    float       jet4_btag_;
    float       jet5_pt_;
    float       jet5_eta_;
    float       jet5_btag_;
    float       jet6_pt_;
    float       jet6_eta_;
    float       jet6_btag_;
    float       jet7_pt_;
    float       jet7_eta_;
    float       jet7_btag_;
    float       jet8_pt_;
    float       jet8_eta_;
    float       jet8_btag_; 

    float       jet1_phi_;
    float       jet1_energy_;
    float       jet2_phi_;
    float       jet2_energy_;
    float       jet3_phi_;
    float       jet3_energy_;
    float       jet4_phi_;
    float       jet4_energy_;
    float       jet5_phi_;
    float       jet5_energy_;
    float       jet6_phi_;
    float       jet6_energy_;
    float       jet7_phi_;
    float       jet7_energy_;
    float       jet8_phi_;
    float       jet8_energy_;

    float       lead_pT_;
    float       sublead_pT_;
    float	    leadptoM_;
    float	    subleadptoM_;
    float	    leadIDMVA_;
    float 	    subleadIDMVA_;
    float       lead_eta_;
    float       sublead_eta_;
    float	    lead_phi_;
    float	    sublead_phi_;
 
    float       leadPSV_;
    float       subleadPSV_;

    float	    dipho_cosphi_;
    float 	    dipho_rapidity_;
    float       dipho_pt_;
    float	    dipho_pt_over_mass_;
    float       met_;
    float	    log_met_;
    float	    met_phi_; 

    float       helicity_angle_;
    float	    m_ggj_;
    float	    m_jjj_;

    //# Meng-Cheng's method
    float       mc_mva_score_tt_v4_;
    float       mc_mva_score_st_v4_;
	float       LeadPho_Pt;
	float       LeadPho_Eta;
	float       LeadPho_Phi;
	float       LeadPho_IDMVA;
	float       SubleadPho_Pt;
	float       SubleadPho_Eta;
	float       SubleadPho_Phi;
	float       SubleadPho_IDMVA;
	float       bJet_Pt;
	float       bJet_Eta;
	float       bJet_Phi;
	float       bJet_btag;
	float       WJet1_Pt;
	float       WJet1_Eta;
	float       WJet1_Phi;
	float       WJet1_btag;
	float       WJet2_Pt;
	float       WJet2_Eta;
	float       WJet2_Phi;
	float       WJet2_btag;
	float       M1Jet_Pt;
	float       M1Jet_Eta;
	float       M1Jet_Phi;
	float       M1Jet_btag;
	float       M1;
	float       M2;
	float       MW;
	float       dR_qH;
	float       dR_bW;
	float       dR_tt;
	float       dR_qq;
	float       dR_tH;
    //# chi-2 related
    float       chi2_value_;
    float       chi2_bjet_pt_;
    float       chi2_wjet1_pt_;
    float       chi2_wjet2_pt_;
    float       chi2_bjet_eta_;
    float       chi2_wjet1_eta_;
    float       chi2_wjet2_eta_;
    float       chi2_wjets_deltaR_;
    float       chi2_wboson_pt_;
    float       chi2_wboson_eta_;
    float       chi2_wboson_mass_;
    float       chi2_wboson_deltaR_bjet_;
    float       chi2_tbw_mass_;
    float       chi2_tbw_pt_;
    float       chi2_tbw_eta_;
    float       chi2_tbw_deltaR_dipho_;
    float       chi2_tprime_ptOverM_;
    float       chi2_tprime_eta_;
    float       chi2_tprime_deltaR_tbw_;
    float       chi2_tprime_deltaR_dipho_;
    float       chi2_bjet_btagScores_;
    float       chi2_wjet1_btagScores_;
    float       chi2_wjet2_btagScores_;
    float       tprime_pt_ratio_;

    float       chi2_bjet_ptOverM_;
    float       chi2_wjet1_ptOverM_;
    float       chi2_wjet2_ptOverM_;
    float       chi2_wboson_ptOverM_;
    float       chi2_tbw_ptOverM_;
    float       helicity_tprime_;

    float       jet1_ptOverM_;
    float       jet2_ptOverM_; 
    float       jet3_ptOverM_;
    float       jet4_ptOverM_;
}; //}}}

inline
void BabyMaker::MakeBabyNtuple(const char *BabyFilename){
  printf("BabyMaker::MakeBabyNtuple: %s\n", BabyFilename);
  BabyFile_ = new TFile(Form("%s", BabyFilename), "RECREATE");
  BabyFile_->cd();
  BabyTree_ = new TTree("t", "A Baby Ntuple");
  BabyTree_maxPhotonIDMVA_ = new TTree("t_maxPhotonIDMVA", "A Baby Ntuple for max photon IDMVA");
  BabyTree_minPhotonIDMVA_ = new TTree("t_minPhotonIDMVA", "A Baby Ntuple for min photon IDMVA");
  BabyTree_fakePhotonIDMVA_ = new TTree("t_fakePhotonIDMVA", "A Baby Ntuple for fake photon IDMVA");
  BabyTree_lowPhotonSideband_ = new TTree("t_lowPhotonSideband", "A Baby Ntuple for low photon ID sideband study");

  produce_ntuples_for_MVA = !(produce_ntuples_for_Maxime || produce_ntuples_for_fakePhotonStudy);
  //----------------------------------------------------------------------------------------------------
  // For Maxime
  //----------------------------------------------------------------------------------------------------
  if(produce_ntuples_for_Maxime){
      printf("[debug] flag1\n");
      BabyTree_->Branch("weight"                            , &evt_weight_    );
      BabyTree_->Branch("dipho_mass"                        , &dipho_mass_    );
      BabyTree_->Branch("Tprime_mass"                       , &tprime_mass_   );
      BabyTree_->Branch("T_Mtilde"                          , &tprime_mtilde_ );

      BabyTree_->Branch("BDTG_TprimeVsNonHiggs_M600_M700"   , &bdtg_score_nrb_m600_m700_   );
      BabyTree_->Branch("BDTG_TprimeVsNonHiggs_M800_M1000"  , &bdtg_score_nrb_m800_m1000_  );
      BabyTree_->Branch("BDTG_TprimeVsNonHiggs_M1100_M1200" , &bdtg_score_nrb_m1100_m1200_ );
      BabyTree_->Branch("BDTG_TprimeVsHiggs_M600_M700"      , &bdtg_score_smh_m600_m700_   );
      BabyTree_->Branch("BDTG_TprimeVsHiggs_M800_M1000"     , &bdtg_score_smh_m800_m1000_  );
      BabyTree_->Branch("BDTG_TprimeVsHiggs_M1100_M1200"    , &bdtg_score_smh_m1100_m1200_ );
  }

  if(produce_ntuples_for_fakePhotonStudy){
      printf("[debug] flag2\n");
      // general event info
      BabyTree_->Branch("weight"            , &evt_weight_        );
      BabyTree_->Branch("process_id"        , &process_id_        );
      BabyTree_->Branch("dipho_mass"        , &dipho_mass_        );

      // for simultaneous fit (pre-selection region)
      BabyTree_maxPhotonIDMVA_->Branch("idmva", &maxIDMVA_);
      BabyTree_minPhotonIDMVA_->Branch("idmva", &minIDMVA_);

      // for fetching fake photon idmva (idmva >= -0.9)
      BabyTree_fakePhotonIDMVA_->Branch("idmva", &fake_photon_IDMVA_);

      // for g-jet fake photon correlation study (low photon id sideband)
      // more {{{
      BabyTree_lowPhotonSideband_->Branch("idmva"                    , &fake_photon_IDMVA_       );
      BabyTree_lowPhotonSideband_->Branch("maxIDMVA_"                , &maxIDMVA_                );
      BabyTree_lowPhotonSideband_->Branch("minIDMVA_"                , &minIDMVA_                );
      BabyTree_lowPhotonSideband_->Branch("max1_btag_"               , &max1_btag_               );
      BabyTree_lowPhotonSideband_->Branch("max2_btag_"               , &max2_btag_               );
      BabyTree_lowPhotonSideband_->Branch("dipho_delta_R"            , &dipho_delta_R            );
      BabyTree_lowPhotonSideband_->Branch("njets_"                   , &njets_                   );
      BabyTree_lowPhotonSideband_->Branch("nbjets_"                  , &nbjets_                  );
      BabyTree_lowPhotonSideband_->Branch("ht_"                      , &ht_                      );
      BabyTree_lowPhotonSideband_->Branch("leadptoM_"                , &leadptoM_                );
      BabyTree_lowPhotonSideband_->Branch("subleadptoM_"             , &subleadptoM_             );
      BabyTree_lowPhotonSideband_->Branch("lead_eta_"                , &lead_eta_                );
      BabyTree_lowPhotonSideband_->Branch("sublead_eta_"             , &sublead_eta_             );
      BabyTree_lowPhotonSideband_->Branch("jet1_ptOverM_"            , &jet1_ptOverM_            );
      BabyTree_lowPhotonSideband_->Branch("jet1_eta_"                , &jet1_eta_                );
      BabyTree_lowPhotonSideband_->Branch("jet1_btag_"               , &jet1_btag_               );
      BabyTree_lowPhotonSideband_->Branch("jet2_ptOverM_"            , &jet2_ptOverM_            );
      BabyTree_lowPhotonSideband_->Branch("jet2_eta_"                , &jet2_eta_                );
      BabyTree_lowPhotonSideband_->Branch("jet2_btag_"               , &jet2_btag_               );
      BabyTree_lowPhotonSideband_->Branch("jet3_ptOverM_"            , &jet3_ptOverM_            );
      BabyTree_lowPhotonSideband_->Branch("jet3_eta_"                , &jet3_eta_                );
      BabyTree_lowPhotonSideband_->Branch("jet3_btag_"               , &jet3_btag_               );
      BabyTree_lowPhotonSideband_->Branch("jet4_ptOverM_"            , &jet4_ptOverM_            );
      BabyTree_lowPhotonSideband_->Branch("jet4_eta_"                , &jet4_eta_                );
      BabyTree_lowPhotonSideband_->Branch("jet4_btag_"               , &jet4_btag_               );
      BabyTree_lowPhotonSideband_->Branch("leadPSV_"                 , &leadPSV_                 );
      BabyTree_lowPhotonSideband_->Branch("subleadPSV_"              , &subleadPSV_              );
      BabyTree_lowPhotonSideband_->Branch("dipho_cosphi_"            , &dipho_cosphi_            );
      BabyTree_lowPhotonSideband_->Branch("dipho_rapidity_"          , &dipho_rapidity_          );
      BabyTree_lowPhotonSideband_->Branch("met_"                     , &met_                     );
      BabyTree_lowPhotonSideband_->Branch("dipho_pt_over_mass_"      , &dipho_pt_over_mass_      );
      BabyTree_lowPhotonSideband_->Branch("helicity_angle_"          , &helicity_angle_          );
      BabyTree_lowPhotonSideband_->Branch("chi2_value_"              , &chi2_value_              );
      BabyTree_lowPhotonSideband_->Branch("chi2_bjet_ptOverM_"       , &chi2_bjet_ptOverM_       );
      BabyTree_lowPhotonSideband_->Branch("chi2_bjet_eta_"           , &chi2_bjet_eta_           );
      BabyTree_lowPhotonSideband_->Branch("chi2_bjet_btagScores_"    , &chi2_bjet_btagScores_    );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjet1_ptOverM_"      , &chi2_wjet1_ptOverM_      );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjet1_eta_"          , &chi2_wjet1_eta_          );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjet1_btagScores_"   , &chi2_wjet1_btagScores_   );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjet2_ptOverM_"      , &chi2_wjet2_ptOverM_      );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjet2_eta_"          , &chi2_wjet2_eta_          );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjet2_btagScores_"   , &chi2_wjet2_btagScores_   );
      BabyTree_lowPhotonSideband_->Branch("chi2_wjets_deltaR_"       , &chi2_wjets_deltaR_       );
      BabyTree_lowPhotonSideband_->Branch("chi2_wboson_ptOverM_"     , &chi2_wboson_ptOverM_     );
      BabyTree_lowPhotonSideband_->Branch("chi2_wboson_eta_"         , &chi2_wboson_eta_         );
      BabyTree_lowPhotonSideband_->Branch("chi2_wboson_mass_"        , &chi2_wboson_mass_        );
      BabyTree_lowPhotonSideband_->Branch("chi2_wboson_deltaR_bjet_" , &chi2_wboson_deltaR_bjet_ );
      BabyTree_lowPhotonSideband_->Branch("chi2_tbw_mass_"           , &chi2_tbw_mass_           );
      BabyTree_lowPhotonSideband_->Branch("chi2_tbw_ptOverM_"        , &chi2_tbw_ptOverM_        );
      BabyTree_lowPhotonSideband_->Branch("chi2_tbw_eta_"            , &chi2_tbw_eta_            );
      BabyTree_lowPhotonSideband_->Branch("chi2_tprime_ptOverM_"     , &chi2_tprime_ptOverM_     );
      BabyTree_lowPhotonSideband_->Branch("chi2_tprime_eta_"         , &chi2_tprime_eta_         );
      BabyTree_lowPhotonSideband_->Branch("tprime_pt_ratio_"         , &tprime_pt_ratio_         );
      BabyTree_lowPhotonSideband_->Branch("helicity_tprime_"         , &helicity_tprime_         );
      //}}}
  }

  //----------------------------------------------------------------------------------------------------
  // my full set var
  //----------------------------------------------------------------------------------------------------
  if(produce_ntuples_for_MVA){
      printf("[debug] flag3\n");
      // more{{{
      //BabyTree_->Branch("BDTG_TprimeVsHiggs_M600_M700_withNRBcut"      , &bdtg_score_smh_m600_m700_withNRBcut_   );
      //BabyTree_->Branch("BDTG_TprimeVsHiggs_M800_M1000_withNRBcut"     , &bdtg_score_smh_m800_m1000_withNRBcut_  );
      //BabyTree_->Branch("BDTG_TprimeVsHiggs_M1100_M1200_withNRBcut"    , &bdtg_score_smh_m1100_m1200_withNRBcut_ );

      // for simultaneous fit (pre-selection region)
      BabyTree_maxPhotonIDMVA_->Branch("idmva", &maxIDMVA_);
      BabyTree_minPhotonIDMVA_->Branch("idmva", &minIDMVA_);

      BabyTree_->Branch("mva_branches"            , &mva_branches            );
      BabyTree_->Branch("year_"                   , &year_                   );
      BabyTree_->Branch("evt_"                    , &evt_                    );
      BabyTree_->Branch("run_"                    , &run_                    );
      BabyTree_->Branch("lumi_"                   , &lumi_                   );
      BabyTree_->Branch("evt_weight_"             , &evt_weight_             );
      BabyTree_->Branch("label_"                  , &label_                  );
      BabyTree_->Branch("multi_label_"            , &multi_label_            );
      BabyTree_->Branch("signal_mass_label_"      , &signal_mass_label_      );
      BabyTree_->Branch("signal_mass_category_"   , &signal_mass_category_   );
      BabyTree_->Branch("data_sideband_label_"    , &data_sideband_label_    );
      BabyTree_->Branch("genPhotonId_"            , &genPhotonId_            );
      BabyTree_->Branch("process_id_"             , &process_id_             );
      BabyTree_->Branch("rand_"                   , &rand_                   );
      BabyTree_->Branch("super_rand_"             , &super_rand_             );
      BabyTree_->Branch("mass_"                   , &mass_                   );

      BabyTree_->Branch("lead_sigmaEtoE_"         , &lead_sigmaEtoE_         );
      BabyTree_->Branch("sublead_sigmaEtoE_"      , &sublead_sigmaEtoE_      );

      // Variable branches
      BabyTree_->Branch("maxIDMVA_"           , &maxIDMVA_           );
      BabyTree_->Branch("minIDMVA_"           , &minIDMVA_           );
      BabyTree_->Branch("max2_btag_"          , &max2_btag_          );
      BabyTree_->Branch("max1_btag_"          , &max1_btag_          );
      BabyTree_->Branch("dipho_delta_R"       , &dipho_delta_R       );
      BabyTree_->Branch("njets_"              , &njets_              );
      BabyTree_->Branch("nbjets_"             , &nbjets_             );
      BabyTree_->Branch("ht_"                 , &ht_                 );

      BabyTree_->Branch("jet1_pt_"            , &jet1_pt_            );
      BabyTree_->Branch("jet1_eta_"           , &jet1_eta_           );
      BabyTree_->Branch("jet1_btag_"          , &jet1_btag_          );
      BabyTree_->Branch("jet2_pt_"            , &jet2_pt_            );
      BabyTree_->Branch("jet2_eta_"           , &jet2_eta_           );
      BabyTree_->Branch("jet2_btag_"          , &jet2_btag_          );
      BabyTree_->Branch("jet3_pt_"            , &jet3_pt_            );
      BabyTree_->Branch("jet3_eta_"           , &jet3_eta_           );
      BabyTree_->Branch("jet3_btag_"          , &jet3_btag_          );
      BabyTree_->Branch("jet4_pt_"            , &jet4_pt_            );
      BabyTree_->Branch("jet4_eta_"           , &jet4_eta_           );
      BabyTree_->Branch("jet4_btag_"          , &jet4_btag_          );
      BabyTree_->Branch("jet5_pt_"            , &jet5_pt_            );
      BabyTree_->Branch("jet5_eta_"           , &jet5_eta_           );
      BabyTree_->Branch("jet5_btag_"          , &jet5_btag_          );
      BabyTree_->Branch("jet6_pt_"            , &jet6_pt_            );
      BabyTree_->Branch("jet6_eta_"           , &jet6_eta_           );
      BabyTree_->Branch("jet6_btag_"          , &jet6_btag_          );
      BabyTree_->Branch("jet7_pt_"            , &jet7_pt_            );
      BabyTree_->Branch("jet7_eta_"           , &jet7_eta_           );
      BabyTree_->Branch("jet7_btag_"          , &jet7_btag_          );
      BabyTree_->Branch("jet8_pt_"            , &jet8_pt_            );
      BabyTree_->Branch("jet8_eta_"           , &jet8_eta_           );
      BabyTree_->Branch("jet8_btag_"          , &jet8_btag_          );

      BabyTree_->Branch("jet1_phi_"           , &jet1_phi_           );
      BabyTree_->Branch("jet1_energy_"        , &jet1_energy_        );
      BabyTree_->Branch("jet2_phi_"           , &jet2_phi_           );
      BabyTree_->Branch("jet2_energy_"        , &jet2_energy_        );
      BabyTree_->Branch("jet3_phi_"           , &jet3_phi_           );
      BabyTree_->Branch("jet3_energy_"        , &jet3_energy_        );
      BabyTree_->Branch("jet4_phi_"           , &jet4_phi_           );
      BabyTree_->Branch("jet4_energy_"        , &jet4_energy_        );
      BabyTree_->Branch("jet5_phi_"           , &jet5_phi_           );
      BabyTree_->Branch("jet5_energy_"        , &jet5_energy_        );
      BabyTree_->Branch("jet6_phi_"           , &jet6_phi_           );
      BabyTree_->Branch("jet6_energy_"        , &jet6_energy_        );
      BabyTree_->Branch("jet7_phi_"           , &jet7_phi_           );
      BabyTree_->Branch("jet7_energy_"        , &jet7_energy_        );
      BabyTree_->Branch("jet8_phi_"           , &jet8_phi_           );
      BabyTree_->Branch("jet8_energy_"        , &jet8_energy_        );

      BabyTree_->Branch("lead_pT_"            , &lead_pT_            );
      BabyTree_->Branch("sublead_pT_"         , &sublead_pT_         );
      BabyTree_->Branch("leadptoM_"           , &leadptoM_           );
      BabyTree_->Branch("subleadptoM_"        , &subleadptoM_        );
      BabyTree_->Branch("leadIDMVA_"          , &leadIDMVA_          );
      BabyTree_->Branch("subleadIDMVA_"       , &subleadIDMVA_       );
      BabyTree_->Branch("lead_eta_"           , &lead_eta_           );
      BabyTree_->Branch("sublead_eta_"        , &sublead_eta_        );
      BabyTree_->Branch("leadPSV_"            , &leadPSV_            );
      BabyTree_->Branch("subleadPSV_"         , &subleadPSV_         );
      BabyTree_->Branch("lead_phi_"           , &lead_phi_           );
      BabyTree_->Branch("sublead_phi_"        , &sublead_phi_        );

      BabyTree_->Branch("dipho_cosphi_"       , &dipho_cosphi_       );
      BabyTree_->Branch("dipho_rapidity_"     , &dipho_rapidity_     );
      BabyTree_->Branch("dipho_pt_"           , &dipho_pt_           );
      BabyTree_->Branch("dipho_pt_over_mass_" , &dipho_pt_over_mass_ );
      BabyTree_->Branch("met_"                , &met_                );
      BabyTree_->Branch("log_met_"            , &log_met_            );
      BabyTree_->Branch("met_phi_"            , &met_phi_            );

      BabyTree_->Branch("helicity_angle_"     , &helicity_angle_     );
      BabyTree_->Branch("m_ggj_"              , &m_ggj_              );
      BabyTree_->Branch("m_jjj_"              , &m_jjj_              );

      //#chi-2 related
      BabyTree_->Branch("chi2_value_"               , &chi2_value_               );
      BabyTree_->Branch("chi2_bjet_pt_"             , &chi2_bjet_pt_             );
      BabyTree_->Branch("chi2_wjet1_pt_"            , &chi2_wjet1_pt_            );
      BabyTree_->Branch("chi2_wjet2_pt_"            , &chi2_wjet2_pt_            );
      BabyTree_->Branch("chi2_bjet_eta_"            , &chi2_bjet_eta_            );
      BabyTree_->Branch("chi2_wjet1_eta_"           , &chi2_wjet1_eta_           );
      BabyTree_->Branch("chi2_wjet2_eta_"           , &chi2_wjet2_eta_           );
      BabyTree_->Branch("chi2_wjets_deltaR_"        , &chi2_wjets_deltaR_        );
      BabyTree_->Branch("chi2_wboson_pt_"           , &chi2_wboson_pt_           );
      BabyTree_->Branch("chi2_wboson_eta_"          , &chi2_wboson_eta_          );
      BabyTree_->Branch("chi2_wboson_mass_"         , &chi2_wboson_mass_         );
      BabyTree_->Branch("chi2_wboson_deltaR_bjet_"  , &chi2_wboson_deltaR_bjet_  );
      BabyTree_->Branch("chi2_tbw_mass_"            , &chi2_tbw_mass_            );
      BabyTree_->Branch("chi2_tbw_pt_"              , &chi2_tbw_pt_              );
      BabyTree_->Branch("chi2_tbw_eta_"             , &chi2_tbw_eta_             );
      BabyTree_->Branch("chi2_tbw_deltaR_dipho_"    , &chi2_tbw_deltaR_dipho_    );
      BabyTree_->Branch("chi2_tprime_ptOverM_"      , &chi2_tprime_ptOverM_      );
      BabyTree_->Branch("chi2_tprime_eta_"          , &chi2_tprime_eta_          );
      BabyTree_->Branch("chi2_tprime_deltaR_tbw_"   , &chi2_tprime_deltaR_tbw_   );
      BabyTree_->Branch("chi2_tprime_deltaR_dipho_" , &chi2_tprime_deltaR_dipho_ );
      BabyTree_->Branch("chi2_bjet_btagScores_"     , &chi2_bjet_btagScores_     );
      BabyTree_->Branch("chi2_wjet1_btagScores_"    , &chi2_wjet1_btagScores_    );
      BabyTree_->Branch("chi2_wjet2_btagScores_"    , &chi2_wjet2_btagScores_    );
      BabyTree_->Branch("tprime_pt_ratio_"          , &tprime_pt_ratio_          );
      BabyTree_->Branch("chi2_bjet_ptOverM_"        , &chi2_bjet_ptOverM_        );
      BabyTree_->Branch("chi2_wjet1_ptOverM_"       , &chi2_wjet1_ptOverM_       );
      BabyTree_->Branch("chi2_wjet2_ptOverM_"       , &chi2_wjet2_ptOverM_       );
      BabyTree_->Branch("chi2_wboson_ptOverM_"      , &chi2_wboson_ptOverM_      );
      BabyTree_->Branch("chi2_tbw_ptOverM_"         , &chi2_tbw_ptOverM_         );
      BabyTree_->Branch("helicity_tprime_"          , &helicity_tprime_          );
      BabyTree_->Branch("jet1_ptOverM_"             , &jet1_ptOverM_             );
      BabyTree_->Branch("jet2_ptOverM_"             , &jet2_ptOverM_             );
      BabyTree_->Branch("jet3_ptOverM_"             , &jet3_ptOverM_             );
      BabyTree_->Branch("jet4_ptOverM_"             , &jet4_ptOverM_             );
      //}}}
  }

  return;
}

inline
void BabyMaker::InitBabyNtuple () {
  debug = false;
  apply_preselection = false;
  produce_ntuples_for_Maxime = false;
  produce_ntuples_for_fakePhotonStudy = false;
  return;
}

inline
void BabyMaker::FillBabyNtuple(){
  BabyTree_->Fill();
  // for simultaneous fit purpose (consider only data in preselection)
  if(process_id_!=18){
    BabyTree_maxPhotonIDMVA_->Fill();
    BabyTree_minPhotonIDMVA_->Fill();
  }
  return;
}

inline
void BabyMaker::FillBabyNtuple_fakePhoton(){
  BabyTree_fakePhotonIDMVA_->Fill();
  return;
}

inline
void BabyMaker::FillBabyNtuple_lowPhotonSideband(){
  BabyTree_lowPhotonSideband_->Fill();
  // simultaneous fit in low photon sideband region
  //BabyTree_maxPhotonIDMVA_->Fill();
  //BabyTree_minPhotonIDMVA_->Fill();
  return;
}

inline
void BabyMaker::CloseBabyNtuple(){
  BabyFile_->cd();
  BabyTree_->Write();
  BabyTree_maxPhotonIDMVA_->Write();
  BabyTree_minPhotonIDMVA_->Write();
  if(produce_ntuples_for_fakePhotonStudy) {
    BabyTree_fakePhotonIDMVA_->Write();
    BabyTree_lowPhotonSideband_->Write();
  }
  BabyFile_->Close();
  return;
}

#endif
