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

class BabyMaker {
  public:
    BabyMaker() {};
    ~BabyMaker() {
      if (BabyFile_) delete BabyFile_;
      if (BabyTree_) delete BabyTree_;
    }
    void ScanChain(TChain* chain, TString name_output_file, TString year, TString ext, TString bkg_options, TString mYear, TString idx, bool fcnc, bool blind, bool fast, int nEvents, string skimFilePrefix);
    void MakeBabyNtuple(const char *);
    void InitBabyNtuple();
    void FillBabyNtuple();
    void CloseBabyNtuple();
    

  private:
    TFile *BabyFile_;
    TTree *BabyTree_;

    // Variable names
    vector<string> mva_branches = {"maxIDMVA_", "minIDMVA_", "max2_btag_", "max1_btag_", "dipho_delta_R", "njets_", "ht_", "leadptoM_", "subleadptoM_", "leadIDMVA_", "subleadIDMVA_", "lead_eta_", "sublead_eta_", "jet1_pt_", "jet1_eta_", "jet1_btag_", "jet2_pt_", "jet2_eta_", "jet2_btag_", "jet3_pt_", "jet3_eta_", "jet3_btag_", "jet4_pt_", "jet4_eta_", "jet4_btag_", "jet5_pt_", "jet5_eta_", "jet5_btag_", "jet6_pt_", "jet6_eta_", "jet6_btag_", "leadPSV_", "subleadPSV_", "dipho_cosphi_", "dipho_rapidity_", "met_"};
    

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

    // DNN Business
    vector<vector<float>>  objects_;
    vector<vector<float>>  objects_boosted_;

    vector<float> top_candidates_;

    // Variable declarations
    float       maxIDMVA_;
    float       minIDMVA_;
    float       max2_btag_;
    float       max1_btag_;
    float       dipho_delta_R;
    float   	njets_;
    int		    nbjets_;
    float	    ht_;

    float       top_tag_score_;
    float       top_tag_mass_;
    float       top_tag_pt_;
    float       top_tag_eta_;
    float       top_tag_phi_;

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

    float       top_candidates_1_;
    float       top_candidates_2_;
    float       top_candidates_3_;
    float       top_candidates_4_;
    float       top_candidates_5_;
    float       top_candidates_6_;
    float       top_candidates_7_;
    float       top_candidates_8_;
    float       top_candidates_9_;
    float       top_candidates_10_;
    float       top_candidates_11_;
    float       top_candidates_12_;
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
};

inline
void BabyMaker::MakeBabyNtuple(const char *BabyFilename){
  printf("BabyMaker::MakeBabyNtuple: %s\n", BabyFilename);
  BabyFile_ = new TFile(Form("%s", BabyFilename), "RECREATE");
  BabyFile_->cd();
  BabyTree_ = new TTree("t", "A Baby Ntuple");

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

  BabyTree_->Branch("objects_"                , &objects_                );
  BabyTree_->Branch("objects_boosted_"        , &objects_boosted_        );
  BabyTree_->Branch("top_candidates_"         , &top_candidates_         );

  // Variable branches
  BabyTree_->Branch("maxIDMVA_"           , &maxIDMVA_           );
  BabyTree_->Branch("minIDMVA_"           , &minIDMVA_           );
  BabyTree_->Branch("max2_btag_"          , &max2_btag_          );
  BabyTree_->Branch("max1_btag_"          , &max1_btag_          );
  BabyTree_->Branch("dipho_delta_R"       , &dipho_delta_R       );
  BabyTree_->Branch("njets_"              , &njets_              );
  BabyTree_->Branch("nbjets_"             , &nbjets_             );
  BabyTree_->Branch("ht_"                 , &ht_                 );

  BabyTree_->Branch("top_tag_score_"      , &top_tag_score_      );
  BabyTree_->Branch("top_tag_mass_"       , &top_tag_mass_       );
  BabyTree_->Branch("top_tag_pt_"         , &top_tag_pt_         );
  BabyTree_->Branch("top_tag_eta_"        , &top_tag_eta_        );
  BabyTree_->Branch("top_tag_phi_"        , &top_tag_phi_        );

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

  BabyTree_->Branch("top_candidates_1_"   , &top_candidates_1_   );
  BabyTree_->Branch("top_candidates_2_"   , &top_candidates_2_   );
  BabyTree_->Branch("top_candidates_3_"   , &top_candidates_3_   );
  BabyTree_->Branch("top_candidates_4_"   , &top_candidates_4_   );
  BabyTree_->Branch("top_candidates_5_"   , &top_candidates_5_   );
  BabyTree_->Branch("top_candidates_6_"   , &top_candidates_6_   );
  BabyTree_->Branch("top_candidates_7_"   , &top_candidates_7_   );
  BabyTree_->Branch("top_candidates_8_"   , &top_candidates_8_   );
  BabyTree_->Branch("top_candidates_9_"   , &top_candidates_9_   );
  BabyTree_->Branch("top_candidates_10_"  , &top_candidates_10_  );
  BabyTree_->Branch("top_candidates_11_"  , &top_candidates_11_  );
  BabyTree_->Branch("top_candidates_12_"  , &top_candidates_12_  );
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

  return;
}

inline
void BabyMaker::InitBabyNtuple () {
  return;
}

inline
void BabyMaker::FillBabyNtuple(){
  BabyTree_->Fill();
  return;
}

inline
void BabyMaker::CloseBabyNtuple(){
  BabyFile_->cd();
  BabyTree_->Write();
  BabyFile_->Close();
  return;
}

#endif
