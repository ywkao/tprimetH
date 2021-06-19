#include "ScanChain.h"
#include "chi2_helper.h"
#include "truth_matching.h"
#include "sorting.h"
#include "TMVA/Reader.h" 

#include "THQ_BDT_Helper.h"

int ScanChain_tprimetHHadronic_signal(TChain* chain, TString name_output_file, TString treeName, TString xml_file, TString mYear, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  // init{{{
  printf("Hello World!\n");
  name_output_file = name_output_file.ReplaceAll("hist_", "myhist_");
  //name_output_file = name_output_file.ReplaceAll("hist_", "testOnly_");
  TFile *output_file = new TFile(name_output_file, "RECREATE");
  TString currentFileTitle = name_output_file;
  TString json_file = "json/covMatrix_Era2017_M1000.json";

  TString tag = "Hadronic";
  vector<Process*> vProcess = generate_processes(output_file);
  add_variables(vProcess, tag);

  bool evaluate_mva = xml_file != "none";
  bool evaluate_all_mva = false;

  float n_lep;
  float n_jet;
  float mass_diphoton;
  float mass_top;

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if (nEvents >= 0) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  //}}}
  // Declare BDT vars {{{
  float maxIDMVA_                 = 0.;
  float minIDMVA_                 = 0.;
  float max2_btag_                = 0.;
  float max1_btag_                = 0.;
  float dipho_delta_R             = 0.;
  float njets_                    = 0.;
  float nbjets_                   = 0.;
  float ht_                       = 0.;
  float leadptoM_                 = 0.;
  float subleadptoM_              = 0.;
  float lead_eta_                 = 0.;
  float sublead_eta_              = 0.;
  float jet1_pt_                  = 0.;
  float jet1_eta_                 = 0.;
  float jet1_btag_                = 0.;
  float jet2_pt_                  = 0.;
  float jet2_eta_                 = 0.;
  float jet2_btag_                = 0.;
  float jet3_pt_                  = 0.;
  float jet3_eta_                 = 0.;
  float jet3_btag_                = 0.;
  float jet4_pt_                  = 0.;
  float jet4_eta_                 = 0.;
  float jet4_btag_                = 0.;
  float jet1_phi_                 = 0.;
  float jet2_phi_                 = 0.; 
  float jet3_phi_                 = 0.;
  float jet4_phi_                 = 0.;
  float jet1_mass_                = 0.;
  float jet2_mass_                = 0.; 
  float jet3_mass_                = 0.;
  float jet4_mass_                = 0.;
  float jet1_energy_              = 0.;
  float jet2_energy_              = 0.; 
  float jet3_energy_              = 0.;
  float jet4_energy_              = 0.;
  float leadPSV_                  = 0.;
  float subleadPSV_               = 0.;
  float dipho_cosphi_             = 0.;
  float dipho_rapidity_           = 0.;
  float met_                      = 0.;
  float dipho_pt_over_mass_       = 0.;
  float helicity_angle_           = 0.;
  float chi2_value_               = 0.;
  float chi2_bjet_pt_             = 0.;
  float chi2_wjet1_pt_            = 0.;
  float chi2_wjet2_pt_            = 0.;
  float chi2_bjet_eta_            = 0.;
  float chi2_wjet1_eta_           = 0.;
  float chi2_wjet2_eta_           = 0.;
  float chi2_bjet_phi_            = 0.;
  float chi2_wjet1_phi_           = 0.;
  float chi2_wjet2_phi_           = 0.;
  float chi2_bjet_mass_           = 0.;
  float chi2_wjet1_mass_          = 0.;
  float chi2_wjet2_mass_          = 0.;
  float chi2_bjet_energy_         = 0.;
  float chi2_wjet1_energy_        = 0.;
  float chi2_wjet2_energy_        = 0.;
  float chi2_wjets_deltaR_        = 0.;
  float chi2_wboson_pt_           = 0.;
  float chi2_wboson_eta_          = 0.;
  float chi2_wboson_mass_         = 0.;
  float chi2_wboson_deltaR_bjet_  = 0.;
  float chi2_tbw_mass_            = 0.;
  float chi2_tbw_pt_              = 0.;
  float chi2_tbw_eta_             = 0.;
  float chi2_tbw_deltaR_dipho_    = 0.;
  float chi2_tprime_ptOverM_      = 0.;
  float chi2_tprime_eta_          = 0.;
  float chi2_tprime_deltaR_tbw_   = 0.;
  float chi2_tprime_deltaR_dipho_ = 0.;
  float chi2_bjet_btagScores_     = 0.;
  float chi2_wjet1_btagScores_    = 0.;
  float chi2_wjet2_btagScores_    = 0.;
  float tprime_pt_ratio_          = 0.;
  float chi2_bjet_ptOverM_        = 0.;
  float chi2_wjet1_ptOverM_       = 0.;
  float chi2_wjet2_ptOverM_       = 0.;
  float chi2_wboson_ptOverM_      = 0.;
  float chi2_tbw_ptOverM_         = 0.;
  float helicity_tprime_          = 0.;
  float jet1_ptOverM_             = 0.;
  float jet2_ptOverM_             = 0.;
  float jet3_ptOverM_             = 0.;
  float jet4_ptOverM_             = 0.;

  //}}}
  // BDT business{{{
  //----------------------------------------------------------------------------------------------------
  // MVA reference (consistency check)
  //----------------------------------------------------------------------------------------------------
  TString BDT_nrb_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/20210525/dataset_Run2_Tprime_NRB_varSet8_M600_M700_20210525/weights/TMVAClassification_BDTG.weights.xml";
  TString BDT_smh_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/20210520/dataset_Run2_Tprime_SMH_varSet8_M600_M700_20210520/weights/TMVAClassification_BDTG.weights.xml";
  flashgg::THQ_BDT_Helper *tprimeTagger_nrb = new flashgg::THQ_BDT_Helper("BDTG", BDT_nrb_xml_file_);
  flashgg::THQ_BDT_Helper *tprimeTagger_smh = new flashgg::THQ_BDT_Helper("BDTG", BDT_smh_xml_file_);

  flashgg::InputVariables MVAvarList;

  //----------------------------------------------------------------------------------------------------
  // Init MVA Helpers
  //----------------------------------------------------------------------------------------------------
  TString path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs";

  TString mass_tag03 = "M600_M700";
  TString mass_tag04 = "M800_M1000";
  TString mass_tag05 = "M1100_M1200";

//dataset_Run2_Tprime_NRB_varSet8_M1100_M1200_20210618/weights/TMVAClassification_BDT.weights.xml
//dataset_Run2_Tprime_NRB_varSet8_M1100_M1200_20210618/weights/TMVAClassification_BDTG.weights.xml
//dataset_Run2_Tprime_NRB_varSet8_M600_M700_20210618/weights/TMVAClassification_BDT.weights.xml
//dataset_Run2_Tprime_NRB_varSet8_M600_M700_20210618/weights/TMVAClassification_BDTG.weights.xml
//dataset_Run2_Tprime_NRB_varSet8_M800_M1000_20210618/weights/TMVAClassification_BDT.weights.xml
//dataset_Run2_Tprime_NRB_varSet8_M800_M1000_20210618/weights/TMVAClassification_BDTG.weights.xml
//dataset_Run2_Tprime_SMH_varSet8_M1100_M1200_20210618/weights/TMVAClassification_BDT.weights.xml
//dataset_Run2_Tprime_SMH_varSet8_M1100_M1200_20210618/weights/TMVAClassification_BDTG.weights.xml
//dataset_Run2_Tprime_SMH_varSet8_M600_M700_20210618/weights/TMVAClassification_BDT.weights.xml
//dataset_Run2_Tprime_SMH_varSet8_M600_M700_20210618/weights/TMVAClassification_BDTG.weights.xml
//dataset_Run2_Tprime_SMH_varSet8_M800_M1000_20210618/weights/TMVAClassification_BDT.weights.xml
//dataset_Run2_Tprime_SMH_varSet8_M800_M1000_20210618/weights/TMVAClassification_BDTG.weights.xml

  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed03_tmva      = new flashgg::THQ_BDT_Helper("BDT"  , path + "/20210426/dataset_Run2_Tprime_ttH_varSet8_" + mass_tag03 + "/weights/TMVAClassification_BDT.weights.xml"           );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed04_tmva      = new flashgg::THQ_BDT_Helper("BDT"  , path + "/20210528/dataset_Run2_Tprime_SMH_varSet8_" + mass_tag04 + "_20210528/weights/TMVAClassification_BDT.weights.xml"  );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed05_tmva      = new flashgg::THQ_BDT_Helper("BDT"  , path + "/20210528/dataset_Run2_Tprime_SMH_varSet8_" + mass_tag05 + "_20210528/weights/TMVAClassification_BDT.weights.xml"  );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed03_tmva      = new flashgg::THQ_BDT_Helper("BDT"  , path + "/20210430/dataset_Run2_Tprime_NRB_varSet8_" + mass_tag03 + "/weights/TMVAClassification_BDT.weights.xml"           );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed04_tmva      = new flashgg::THQ_BDT_Helper("BDT"  , path + "/20210527/dataset_Run2_Tprime_NRB_varSet8_" + mass_tag04 + "_20210527/weights/TMVAClassification_BDT.weights.xml"  );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed05_tmva      = new flashgg::THQ_BDT_Helper("BDT"  , path + "/20210527/dataset_Run2_Tprime_NRB_varSet8_" + mass_tag05 + "_20210527/weights/TMVAClassification_BDT.weights.xml"  );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed03_tmva_bdtg = new flashgg::THQ_BDT_Helper("BDTG" , path + "/20210520/dataset_Run2_Tprime_SMH_varSet8_" + mass_tag03 + "_20210520/weights/TMVAClassification_BDTG.weights.xml" );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed04_tmva_bdtg = new flashgg::THQ_BDT_Helper("BDTG" , path + "/20210520/dataset_Run2_Tprime_SMH_varSet8_" + mass_tag04 + "_20210520/weights/TMVAClassification_BDTG.weights.xml" );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed05_tmva_bdtg = new flashgg::THQ_BDT_Helper("BDTG" , path + "/20210520/dataset_Run2_Tprime_SMH_varSet8_" + mass_tag05 + "_20210520/weights/TMVAClassification_BDTG.weights.xml" );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed03_tmva_bdtg = new flashgg::THQ_BDT_Helper("BDTG" , path + "/20210525/dataset_Run2_Tprime_NRB_varSet8_" + mass_tag03 + "_20210525/weights/TMVAClassification_BDTG.weights.xml" );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed04_tmva_bdtg = new flashgg::THQ_BDT_Helper("BDTG" , path + "/20210525/dataset_Run2_Tprime_NRB_varSet8_" + mass_tag04 + "_20210525/weights/TMVAClassification_BDTG.weights.xml" );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed05_tmva_bdtg = new flashgg::THQ_BDT_Helper("BDTG" , path + "/20210525/dataset_Run2_Tprime_NRB_varSet8_" + mass_tag05 + "_20210525/weights/TMVAClassification_BDTG.weights.xml" );
  //}}}
  bool perform_consistency_check = false;
  // bool, lumi, pdf, counters{{{
  //----------------------------------------------------------------------------------------------------
  // Other inits
  //----------------------------------------------------------------------------------------------------
  bool debug = false;
  bool debug_deeper = false;

  cout << "mYear: " << mYear << endl;
  double lumi_2016 = 35.9;
  double lumi_2017 = 41.5;
  double lumi_2018 = 59.76;
  double branching_fraction_hgg = 0.00227;
  double total_yields = 0.;

  TF1* photon_fakeID_shape_runII = get_photon_ID_shape("fake_runII");

  int counter = 0;
  int counter_nrb_same = 0;
  int counter_smh_same = 0;
  int counter_jet_negative_energy = 0;
  int counter_tprime_ultraHeavy_mass = 0;
  int counter_tprime_ultraHeavy_mass_3TeV = 0;
  int counter_tprime_ultraHeavy_mass_5TeV = 0;
  int counter_tprime_ultraHeavy_mass_7TeV = 0;
  int counter_tprime_ultraHeavy_mass_10TeV = 0;
  int counter_tprime_ultraHeavy_mass_13TeV = 0;
  //}}}
  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    // Get File Content{{{
    TFile file(currentFile->GetTitle());
    TTree *tree = (TTree*)file.Get(treeName); // "tagsDumper/trees/tHq_13TeV_THQHadronicTag"

    if (fast) TTreeCache::SetLearnEntries(10);
    if (fast) tree->SetCacheSize(128*1024*1024);
    analyzer.Init(tree);
    //}}}
    // Loop over Events in current file
    if (nEventsTotal >= nEventsChain) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event)
    {
      //----------------------------------------------------------------------------------------------------
      // Get Event Content
      //----------------------------------------------------------------------------------------------------
      if (nEventsTotal >= nEventsChain) continue;
      if (fast) tree->LoadTree(event);
      analyzer.GetEntry(event);
      ++nEventsTotal;
      tprimetHHadronic::progress( nEventsTotal, nEventsChain );

      //----------------------------------------------------------------------------------------------------
      // Jets
      //----------------------------------------------------------------------------------------------------
      bool flag_negative_energy = false;
      vector<double> btag_scores;
      vector<TLorentzVector> jets = make_jets(btag_scores, flag_negative_energy);
      vector< std::pair<int, double> > btag_scores_sorted = sortVectorGreater(btag_scores);
      if(jets.size() < 3) continue;

      //----------------------------------------------------------------------------------------------------
      // Blinded region
      //----------------------------------------------------------------------------------------------------
      // processId, evt_weight, photon IDMVA, data-driven description, ttX overlap removal, blind Mgg signal region{{{
      bool isData = currentFileTitle.Contains("DoubleEG") || currentFileTitle.Contains("EGamma"); 
      bool blind = true;
      int genPhotonId = isData ? -1 : categorize_photons(leadGenMatch(), subleadGenMatch()); // overlap removal for ttX
      int processId = categorize_process(currentFileTitle, genPhotonId);
      bool is_signal = (processId >= 27 && processId <= 36); // signal id in [27, 36]
      bool is_data = (processId == 10);

      double lumi = mYear == "2016" ? lumi_2016 : (mYear == "2017") ? lumi_2017 : lumi_2018;
      float evt_weight = is_data ? 1. : weight() * lumi;

      // Impute, if applicable
      maxIDMVA_ = dipho_leadIDMVA() >  dipho_subleadIDMVA() ? dipho_leadIDMVA() : dipho_subleadIDMVA();
      minIDMVA_ = dipho_leadIDMVA() <= dipho_subleadIDMVA() ? dipho_leadIDMVA() : dipho_subleadIDMVA();
      if (is_data) impute_photon_id(min_photon_ID_presel_cut, maxIDMVA_, photon_fakeID_shape_runII, minIDMVA_, evt_weight, processId);

      // Micmic HLT; ensure MC and Data have the same selection
      bool pass_photon_pt_criteria = dipho_leadPt()>30. && dipho_subleadPt()>18.;
      if(!pass_photon_pt_criteria) continue;

      if (is_data && processId != 18 && blind && CMS_hgg_mass() > 115. && CMS_hgg_mass() < 135.)  continue;
      if (is_data && processId != 18 && blind && CMS_hgg_mass() > 115. && CMS_hgg_mass() < 135.)
          printf("[WARNING] Data events in signal region is used! mass = %.2f, processId = %d\n", CMS_hgg_mass(), processId);

      if (isnan(evt_weight) || isinf(evt_weight) || evt_weight == 0) continue; //some pu weights are nan/inf and this causes problems for histos 
      if (has_std_overlaps(currentFileTitle, lead_Prompt(), sublead_Prompt(), genPhotonId)) continue;

      double leadID_ = dipho_leadIDMVA() == maxIDMVA_ ? maxIDMVA_ : minIDMVA_;
      double subleadID_ = dipho_leadIDMVA() == maxIDMVA_ ? minIDMVA_ : maxIDMVA_; 
      //}}}

      //----------------------------------------------------------------------------------------------------
      // Assign variables values
      //----------------------------------------------------------------------------------------------------
      my_jets_info my_jets_info_instance;
      // assign values {{{
      //----------------------------------------------------------------------------------------------------
      // Di-Photon
      //----------------------------------------------------------------------------------------------------
      TLorentzVector diphoton, lead_photon, sublead_photon;
      diphoton.SetPtEtaPhiE(dipho_pt(), dipho_eta(), dipho_phi(), dipho_e());
      lead_photon.SetPtEtaPhiM(dipho_leadPt(), dipho_leadEta(), dipho_leadPhi(), 0.);
      sublead_photon.SetPtEtaPhiM(dipho_subleadPt(), dipho_subleadEta(), dipho_subleadPhi(), 0.);
      TLorentzVector diphoton_v2 = lead_photon + sublead_photon;
      
      //------------------------------ Variable definitions ------------------------------//
//    ht_         = get_ht(jets); // function defined in include/ttHLooper.h
//    ht_         = get_ht(); // function defined in include/ScanChain.h
      ht_         = HT();
      njets_      = n_jets();
      nbjets_     = n_L_bjets();
      max1_btag_  = btag_scores_sorted[0].second;
      max2_btag_  = btag_scores_sorted[1].second;
      jet1_pt_    = njets_ >= 1 ? jets[0].Pt()   : -999;
      jet1_eta_   = njets_ >= 1 ? jets[0].Eta()  : -999;
      jet1_btag_  = njets_ >= 1 ? btag_scores[0] : -999;
      jet2_pt_    = njets_ >= 2 ? jets[1].Pt()   : -999;
      jet2_eta_   = njets_ >= 2 ? jets[1].Eta()  : -999;
      jet2_btag_  = njets_ >= 2 ? btag_scores[1] : -999;
      jet3_pt_    = njets_ >= 3 ? jets[2].Pt()   : -999;
      jet3_eta_   = njets_ >= 3 ? jets[2].Eta()  : -999;
      jet3_btag_  = njets_ >= 3 ? btag_scores[2] : -999;
      jet4_pt_    = njets_ >= 4 ? jets[3].Pt()   : -999;
      jet4_eta_   = njets_ >= 4 ? jets[3].Eta()  : -999;
      jet4_btag_  = njets_ >= 4 ? btag_scores[3] : -999;

      jet1_phi_   = njets_ >= 1 ? jets[0].Phi()  : -999;
      jet2_phi_   = njets_ >= 2 ? jets[1].Phi()  : -999;
      jet3_phi_   = njets_ >= 3 ? jets[2].Phi()  : -999;
      jet4_phi_   = njets_ >= 4 ? jets[3].Phi()  : -999;
      jet1_mass_  = njets_ >= 1 ? jets[0].M()    : -999;
      jet2_mass_  = njets_ >= 2 ? jets[1].M()    : -999;
      jet3_mass_  = njets_ >= 3 ? jets[2].M()    : -999;
      jet4_mass_  = njets_ >= 4 ? jets[3].M()    : -999;
      jet1_energy_  = njets_ >= 1 ? jets[0].E()    : -999;
      jet2_energy_  = njets_ >= 2 ? jets[1].E()    : -999;
      jet3_energy_  = njets_ >= 3 ? jets[2].E()    : -999;
      jet4_energy_  = njets_ >= 4 ? jets[3].E()    : -999;

      // photons, diphoton, helicity angle, top masses
      dipho_delta_R       = lead_photon.DeltaR(sublead_photon);
      leadptoM_           = dipho_lead_ptoM();
      subleadptoM_        = dipho_sublead_ptoM();
      lead_eta_           = dipho_leadEta();
      sublead_eta_        = dipho_subleadEta();

      leadPSV_            = dipho_lead_haspixelseed();
      subleadPSV_         = dipho_sublead_haspixelseed();

      dipho_cosphi_       = dipho_cosphi();
      dipho_pt_over_mass_ = dipho_pt() / CMS_hgg_mass();
      met_                = recoMET_pt();

      dipho_rapidity_     = diphoton.Rapidity(); //dipho_rapidity();
      helicity_angle_     = helicity(lead_photon, sublead_photon);

      //------------------------------ Minimum chi-2 method (cov.) ------------------------------//
      double min_chi2_value_2x2 = 99999.;
      vector<int> indices_bjj_covMatrix(3, -1);
      bool has_resonable_reco = get_the_best_bjj_candidate(indices_bjj_covMatrix, jets, diphoton, btag_scores, min_chi2_value_2x2, json_file);

      TLorentzVector null;
      TLorentzVector cov_bjet  = has_resonable_reco ? jets[indices_bjj_covMatrix[0]] : null;
      TLorentzVector cov_wjet1 = has_resonable_reco ? jets[indices_bjj_covMatrix[1]] : null;
      TLorentzVector cov_wjet2 = has_resonable_reco ? jets[indices_bjj_covMatrix[2]] : null;
      TLorentzVector cov_wboson = cov_wjet1 + cov_wjet2;
      TLorentzVector cov_top = cov_bjet + cov_wboson;
      TLorentzVector cov_tprime = cov_top + diphoton;

      bool pass_eta_criteria_on_wjets = ( cov_wjet1.Eta() < 3. && cov_wjet2.Eta() < 3. );
      if( !pass_eta_criteria_on_wjets ) continue;

      double mass_wboson = has_resonable_reco ? cov_wboson.M()     : -1.;
      double mass_top    = has_resonable_reco ? cov_top.M()        : -1.;
      double mass_tprime = has_resonable_reco ? cov_tprime.M()     : -1.;
      double mass_tprime_tilde = has_resonable_reco ? ( cov_tprime.M() - cov_top.M() - diphoton.M() + 175.5 + 125.0 ) : -1.;
      min_chi2_value_2x2 = has_resonable_reco ? min_chi2_value_2x2 : -1.;

      chi2_value_               = min_chi2_value_2x2;
      chi2_bjet_pt_             = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.Pt()                         : -999;
      chi2_wjet1_pt_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.Pt()                        : -999;
      chi2_wjet2_pt_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.Pt()                        : -999;
      chi2_bjet_eta_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.Eta()                        : -999;
      chi2_wjet1_eta_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.Eta()                       : -999;
      chi2_wjet2_eta_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.Eta()                       : -999;
      chi2_bjet_phi_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.Phi()                        : -999;
      chi2_wjet1_phi_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.Phi()                       : -999;
      chi2_wjet2_phi_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.Phi()                       : -999;
      chi2_bjet_mass_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.M()                          : -999;
      chi2_wjet1_mass_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.M()                         : -999;
      chi2_wjet2_mass_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.M()                         : -999;
      chi2_bjet_energy_         = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.E()                          : -999;
      chi2_wjet1_energy_        = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.E()                         : -999;
      chi2_wjet2_energy_        = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.E()                         : -999;
      chi2_wjets_deltaR_        = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.DeltaR(cov_wjet2)           : -999;
      chi2_wboson_pt_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wboson.Pt()                       : -999;
      chi2_wboson_eta_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wboson.Eta()                      : -999;
      chi2_wboson_mass_         = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wboson.M()                        : -999;
      chi2_wboson_deltaR_bjet_  = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wboson.DeltaR(cov_bjet)           : -999;
      chi2_tbw_mass_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_top.M()                           : -999;
      chi2_tbw_pt_              = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_top.Pt()                          : -999;
      chi2_tbw_eta_             = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_top.Eta()                         : -999;
      chi2_tbw_deltaR_dipho_    = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_top.DeltaR(diphoton)              : -999;
      chi2_tprime_eta_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.Eta()                      : -999;
      chi2_tprime_deltaR_tbw_   = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.DeltaR(cov_top)            : -999;
      chi2_tprime_deltaR_dipho_ = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.DeltaR(diphoton)           : -999;
      chi2_bjet_btagScores_     = (has_resonable_reco && pass_eta_criteria_on_wjets) ? btag_scores[indices_bjj_covMatrix[0]] : -999;
      chi2_wjet1_btagScores_    = (has_resonable_reco && pass_eta_criteria_on_wjets) ? btag_scores[indices_bjj_covMatrix[1]] : -999;
      chi2_wjet2_btagScores_    = (has_resonable_reco && pass_eta_criteria_on_wjets) ? btag_scores[indices_bjj_covMatrix[2]] : -999;
      tprime_pt_ratio_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? (cov_top.Pt() + dipho_pt())/ ht_      : -999;

      // use mass reconstructed at producer level for better consistency in significant digit; v3p5 onward
      chi2_wboson_mass_         = chi2_recoMass_wboson();
      chi2_tbw_mass_            = chi2_recoMass_top();
      chi2_value_               = chi2_calculator_2x2(chi2_wboson_mass_, chi2_tbw_mass_, json_file);
  
      chi2_bjet_ptOverM_        = (has_resonable_reco && pass_eta_criteria_on_wjets)  ? cov_bjet.Pt() / chi2_tbw_mass_          : -999;
      chi2_wjet1_ptOverM_       = (has_resonable_reco && pass_eta_criteria_on_wjets)  ? cov_wjet1.Pt() / chi2_wboson_mass_      : -999;
      chi2_wjet2_ptOverM_       = (has_resonable_reco && pass_eta_criteria_on_wjets)  ? cov_wjet2.Pt() / chi2_wboson_mass_      : -999;
      chi2_wboson_ptOverM_      = (has_resonable_reco && pass_eta_criteria_on_wjets)  ? cov_wboson.Pt() / chi2_wboson_mass_     : -999;
      chi2_tbw_ptOverM_         = (has_resonable_reco && pass_eta_criteria_on_wjets)  ? cov_top.Pt() / chi2_tbw_mass_           : -999;
      chi2_tprime_ptOverM_      = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.Pt() / chi2_recoMass_tprime() : -999;
      helicity_tprime_          = (has_resonable_reco && pass_eta_criteria_on_wjets)  ? helicity(cov_top, diphoton)             : -999;
 
      jet1_ptOverM_ = (njets_ >= 1 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[0].Pt() / chi2_tbw_mass_  : -999;
      jet2_ptOverM_ = (njets_ >= 2 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[1].Pt() / chi2_tbw_mass_  : -999; 
      jet3_ptOverM_ = (njets_ >= 3 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[2].Pt() / chi2_tbw_mass_  : -999;
      jet4_ptOverM_ = (njets_ >= 4 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[3].Pt() / chi2_tbw_mass_  : -999;
      //}}}
      // my_jets_info{{{
      my_jets_info_instance.chi2_value_         = chi2_value_;
      my_jets_info_instance.chi2_bjet_pt_       = cov_bjet.Pt();
      my_jets_info_instance.chi2_bjet_eta_      = cov_bjet.Eta();
      my_jets_info_instance.chi2_bjet_phi_      = cov_bjet.Phi();
      my_jets_info_instance.chi2_bjet_energy_   = cov_bjet.E();
      my_jets_info_instance.chi2_wjet1_pt_      = cov_wjet1.Pt();
      my_jets_info_instance.chi2_wjet1_eta_     = cov_wjet1.Eta();
      my_jets_info_instance.chi2_wjet1_phi_     = cov_wjet1.Phi();
      my_jets_info_instance.chi2_wjet1_energy_  = cov_wjet1.E();
      my_jets_info_instance.chi2_wjet2_pt_      = cov_wjet2.Pt();
      my_jets_info_instance.chi2_wjet2_eta_     = cov_wjet2.Eta();
      my_jets_info_instance.chi2_wjet2_phi_     = cov_wjet2.Phi();
      my_jets_info_instance.chi2_wjet2_energy_  = cov_wjet2.E();
      my_jets_info_instance.chi2_wboson_pt_     = cov_wboson.Pt();
      my_jets_info_instance.chi2_wboson_eta_    = cov_wboson.Eta();
      my_jets_info_instance.chi2_wboson_phi_    = cov_wboson.Phi();
      my_jets_info_instance.chi2_wboson_energy_ = cov_wboson.E();
      my_jets_info_instance.chi2_wboson_mass_   = cov_wboson.M();
      my_jets_info_instance.chi2_top_pt_        = cov_top.Pt();
      my_jets_info_instance.chi2_top_eta_       = cov_top.Eta();
      my_jets_info_instance.chi2_top_phi_       = cov_top.Phi();
      my_jets_info_instance.chi2_top_energy_    = cov_top.E();
      my_jets_info_instance.chi2_top_mass_      = cov_top.M();
      my_jets_info_instance.chi2_tprime_pt_     = cov_tprime.Pt();
      my_jets_info_instance.chi2_tprime_eta_    = cov_tprime.Eta();
      my_jets_info_instance.chi2_tprime_phi_    = cov_tprime.Phi();
      my_jets_info_instance.chi2_tprime_energy_ = cov_tprime.E();
      my_jets_info_instance.chi2_tprime_mass_   = cov_tprime.M();
      //}}}
        // MVA input variables {{{
        MVAvarList.maxIDMVA_                = maxIDMVA_;
        MVAvarList.minIDMVA_                = minIDMVA_;
        MVAvarList.max1_btag_               = max1_btag_;
        MVAvarList.max2_btag_               = max2_btag_;
        MVAvarList.dipho_delta_R            = dipho_delta_R;
        MVAvarList.njets_                   = njets_;
        MVAvarList.nbjets_                  = nbjets_;
        MVAvarList.ht_                      = ht_;
        MVAvarList.leadptoM_                = leadptoM_;
        MVAvarList.subleadptoM_             = subleadptoM_;
        MVAvarList.lead_eta_                = lead_eta_;
        MVAvarList.sublead_eta_             = sublead_eta_;
        MVAvarList.leadPSV_                 = leadPSV_;
        MVAvarList.subleadPSV_              = subleadPSV_;
        MVAvarList.dipho_cosphi_            = dipho_cosphi_;
        MVAvarList.dipho_rapidity_          = dipho_rapidity_;
        MVAvarList.met_                     = met_;
        MVAvarList.dipho_pt_over_mass_      = dipho_pt_over_mass_;
        MVAvarList.helicity_angle_          = helicity_angle_;
        MVAvarList.chi2_value_              = chi2_value_;
        MVAvarList.chi2_bjet_ptOverM_       = chi2_bjet_ptOverM_;
        MVAvarList.chi2_bjet_eta_           = chi2_bjet_eta_;
        MVAvarList.chi2_bjet_btagScores_    = chi2_bjet_btagScores_;
        MVAvarList.chi2_wjet1_ptOverM_      = chi2_wjet1_ptOverM_;
        MVAvarList.chi2_wjet1_eta_          = chi2_wjet1_eta_;
        MVAvarList.chi2_wjet1_btagScores_   = chi2_wjet1_btagScores_;
        MVAvarList.chi2_wjet2_ptOverM_      = chi2_wjet2_ptOverM_;
        MVAvarList.chi2_wjet2_eta_          = chi2_wjet2_eta_;
        MVAvarList.chi2_wjet2_btagScores_   = chi2_wjet2_btagScores_;
        MVAvarList.chi2_wjets_deltaR_       = chi2_wjets_deltaR_;
        MVAvarList.chi2_wboson_ptOverM_     = chi2_wboson_ptOverM_;
        MVAvarList.chi2_wboson_eta_         = chi2_wboson_eta_;
        MVAvarList.chi2_wboson_mass_        = chi2_wboson_mass_;
        MVAvarList.chi2_wboson_deltaR_bjet_ = chi2_wboson_deltaR_bjet_;
        MVAvarList.chi2_tbw_mass_           = chi2_tbw_mass_;
        MVAvarList.chi2_tbw_ptOverM_        = chi2_tbw_ptOverM_;
        MVAvarList.chi2_tbw_eta_            = chi2_tbw_eta_;
        MVAvarList.chi2_tprime_ptOverM_     = chi2_tprime_ptOverM_;
        MVAvarList.chi2_tprime_eta_         = chi2_tprime_eta_;
        MVAvarList.tprime_pt_ratio_         = tprime_pt_ratio_;
        MVAvarList.helicity_tprime_         = helicity_tprime_;
        MVAvarList.jet1_ptOverM_            = jet1_ptOverM_;
        MVAvarList.jet2_ptOverM_            = jet2_ptOverM_;
        MVAvarList.jet3_ptOverM_            = jet3_ptOverM_;
        MVAvarList.jet4_ptOverM_            = jet4_ptOverM_;
        MVAvarList.jet1_eta_                = jet1_eta_;
        MVAvarList.jet1_btag_               = jet1_btag_;
        MVAvarList.jet2_eta_                = jet2_eta_;
        MVAvarList.jet2_btag_               = jet2_btag_;
        MVAvarList.jet3_eta_                = jet3_eta_;
        MVAvarList.jet3_btag_               = jet3_btag_;
        MVAvarList.jet4_eta_                = jet4_eta_;
        MVAvarList.jet4_btag_               = jet4_btag_;

        // tprime mass is not used for training
        float chi2_tprime_mass_             = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.M()                   : -999;
        //}}}

      //----------------------------------------------------------------------------------------------------
      // Evaluate MVA values
      //----------------------------------------------------------------------------------------------------
      // more{{{
      double mva_value_nrb = tprimeTagger_nrb->evaluate("BDTG", MVAvarList);
      double mva_value_smh = tprimeTagger_smh->evaluate("BDTG", MVAvarList);

      double mva_value_smh_varset8_mixed03_tmva = mva_smh_varset8_mixed03_tmva->evaluate("BDT"  , MVAvarList);
      double mva_value_smh_varset8_mixed04_tmva = mva_smh_varset8_mixed04_tmva->evaluate("BDT"  , MVAvarList);
      double mva_value_smh_varset8_mixed05_tmva = mva_smh_varset8_mixed05_tmva->evaluate("BDT"  , MVAvarList);
      double mva_value_nrb_varset8_mixed03_tmva = mva_nrb_varset8_mixed03_tmva->evaluate("BDT"  , MVAvarList);
      double mva_value_nrb_varset8_mixed04_tmva = mva_nrb_varset8_mixed04_tmva->evaluate("BDT"  , MVAvarList);
      double mva_value_nrb_varset8_mixed05_tmva = mva_nrb_varset8_mixed05_tmva->evaluate("BDT"  , MVAvarList);
      double mva_value_smh_varset8_mixed03_tmva_bdtg = mva_smh_varset8_mixed03_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      double mva_value_smh_varset8_mixed04_tmva_bdtg = mva_smh_varset8_mixed04_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      double mva_value_smh_varset8_mixed05_tmva_bdtg = mva_smh_varset8_mixed05_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      double mva_value_nrb_varset8_mixed03_tmva_bdtg = mva_nrb_varset8_mixed03_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      double mva_value_nrb_varset8_mixed04_tmva_bdtg = mva_nrb_varset8_mixed04_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      double mva_value_nrb_varset8_mixed05_tmva_bdtg = mva_nrb_varset8_mixed05_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      //}}}

      //----------------------------------------------------------------------------------------------------
      // For the moment the genPhotonId is assumed -1 (TTGG, TTG, TTJets might have overlap)
      //----------------------------------------------------------------------------------------------------
      int mvaCategoryId = mva_value_nrb < -0.8 ? 0 : 1;
      if (!passes_selection("ttHHadronic_RunII_MVA_Presel", minIDMVA_, maxIDMVA_, -999.))	continue; // -999 represents no cut on mva values

      int genLeptonId = 0; // isData ? -1 : categorize_leptons(nGoodEls(), nGoodMus()); // none of reco lepton exists
      int genPhotonDetailId = 5; // isData ? -1 : categorize_photons_detail(lead_photon_type(), sublead_photon_type()); // assume prompt-prompt
      int photonLocationId = categorize_photon_locations(dipho_leadEta(), dipho_subleadEta());
      int yearId = mYear == "2016" ? 0 : (mYear == "2017" ? 1 : (mYear == "2018" ? 2 : -1));
      vector<int> vId = {genLeptonId, genPhotonId, genPhotonDetailId, photonLocationId, mvaCategoryId, -1, yearId};

      total_yields += evt_weight;

      //----------------------------------------------------------------------------------------------------
      // Consistency check
      //----------------------------------------------------------------------------------------------------
      if(perform_consistency_check && processId == 18) continue; //exclude data-driven from consistency check
      // more{{{
      counter += 1;
      if(flag_negative_energy) counter_jet_negative_energy += 1;
      if(mass_tprime > 3000.) counter_tprime_ultraHeavy_mass_3TeV += 1;
      if(mass_tprime > 5000.) counter_tprime_ultraHeavy_mass_5TeV += 1;
      if(mass_tprime > 7000.) counter_tprime_ultraHeavy_mass_7TeV += 1;
      if(mass_tprime > 10000.) counter_tprime_ultraHeavy_mass_10TeV += 1;
      if(mass_tprime > 13000.) counter_tprime_ultraHeavy_mass_13TeV += 1;
      check_ultra_large_tprime_mass(mass_tprime > 5000., my_jets_info_instance);

      bool found_discrepancy_nrb = mycheck("BDT (NRB)", counter_nrb_same, MVAscore_BDT_nrb(), mva_value_nrb_varset8_mixed03_tmva_bdtg, dipho_pt());
      bool found_discrepancy_smh = mycheck("BDT (SMH)", counter_smh_same, MVAscore_BDT_smh(), mva_value_smh_varset8_mixed03_tmva_bdtg, dipho_pt());
      
      bool check_var = found_discrepancy_nrb || found_discrepancy_smh;
      if(debug && check_var)
      {
          int evt_  = analyzer.event();
          int run_  = analyzer.run();
          int lumi_ = analyzer.lumi();
          printf("[Info] Run:Lumi:Event = %d:%d:%d\n", run_, lumi_, evt_);
          printf("[check] processId = %d, minIDMVA = %.2f, maxIDMVA = %.2f\n", processId, minIDMVA_, maxIDMVA_);

          // printf format
          printf("%s: %.10f , " , "diphoton_mass_"           , CMS_hgg_mass                );
          printf("%s: %.10f , " , "diphoton_pt_"             , dipho_pt()                 );
          tprimeTagger_nrb->print_details( MVAvarList );
          printf("%s: %.10f , " , "score_nrb_"               , mva_value_nrb                );
          printf("%s: %.10f , " , "score_smh_"               , mva_value_smh                );
          printf("\n\n");
      }
      //}}}

      //----------------------------------------------------------------------------------------------------
      // MVA cut values
      //----------------------------------------------------------------------------------------------------
      bool pass_mva_cut_bdt_nrb_mixed03 = mva_value_nrb_varset8_mixed03_tmva > 0.560;//0.560; //0.510;
      bool pass_mva_cut_bdt_nrb_mixed04 = mva_value_nrb_varset8_mixed04_tmva > 0.500;//0.551; //0.500;
      bool pass_mva_cut_bdt_nrb_mixed05 = mva_value_nrb_varset8_mixed05_tmva > 0.490;//0.542; //0.490;
      bool pass_mva_cut_bdt_smh_mixed03 = mva_value_smh_varset8_mixed03_tmva > 0.520;
      bool pass_mva_cut_bdt_smh_mixed04 = mva_value_smh_varset8_mixed04_tmva > 0.522;
      bool pass_mva_cut_bdt_smh_mixed05 = mva_value_smh_varset8_mixed05_tmva > 0.534;
      bool pass_mva_cut_bdtg_nrb_mixed03 = mva_value_nrb_varset8_mixed03_tmva_bdtg > 0.560; //0.580; //0.500; //0.785;
      bool pass_mva_cut_bdtg_nrb_mixed04 = mva_value_nrb_varset8_mixed04_tmva_bdtg > 0.337; //0.706;
      bool pass_mva_cut_bdtg_nrb_mixed05 = mva_value_nrb_varset8_mixed05_tmva_bdtg > 0.206; //0.580;
      bool pass_mva_cut_bdtg_smh_mixed03 = mva_value_smh_varset8_mixed03_tmva_bdtg > 0.814;
      bool pass_mva_cut_bdtg_smh_mixed04 = mva_value_smh_varset8_mixed04_tmva_bdtg > 0.820;
      bool pass_mva_cut_bdtg_smh_mixed05 = mva_value_smh_varset8_mixed05_tmva_bdtg > 0.800;

      bool pass_mva_cut_bdtg_nrb_mixed03_Maxime = mva_value_nrb_varset8_mixed03_tmva_bdtg > 0.940;
      bool pass_mva_cut_bdtg_smh_mixed03_Maxime = mva_value_smh_varset8_mixed03_tmva_bdtg > 0.300;

      //bool pass_tprime_low_mass_criterion = mass_tprime > 300.;
      bool pass_tprime_low_mass_criterion = mass_tprime > 0.;

      bool criteria_mva_Maxime = mva_value_nrb_varset8_mixed03_tmva_bdtg > 0.94 && mva_value_smh_varset8_mixed03_tmva_bdtg > 0.30;
      bool criteria_TprimeMass_Maxime = mass_tprime > 450. && mass_tprime < 900.;
      bool pass_selection_from_Maxime_optimization = criteria_mva_Maxime && criteria_TprimeMass_Maxime;

      //****************************************************************************************************
      // Fill histograms
      //****************************************************************************************************
      TString syst_ext = "";
      
      if(leadGenMatch() != 1)    { vProcess[processId]->fill_histogram("h" + syst_ext + "fake_photon_IDMVA" , dipho_leadIDMVA()   , evt_weight, vId); }
      if(subleadGenMatch() != 1) { vProcess[processId]->fill_histogram("h" + syst_ext + "fake_photon_IDMVA" , dipho_subleadIDMVA(), evt_weight, vId); }

      if(pass_tprime_low_mass_criterion){

      //----------------------------------------------------------------------------------------------------
      // diphoton mass after cutting MVA scores
      //----------------------------------------------------------------------------------------------------
      // more{{{
      if(pass_mva_cut_bdt_nrb_mixed03)                                   { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDT_nrb_cut_mixed03"            , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdt_nrb_mixed04)                                   { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDT_nrb_cut_mixed04"            , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdt_nrb_mixed05)                                   { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDT_nrb_cut_mixed05"            , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed03)                                  { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDTG_nrb_cut_mixed03"           , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed04)                                  { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDTG_nrb_cut_mixed04"           , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed05)                                  { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDTG_nrb_cut_mixed05"           , diphoton.M() , evt_weight , vId); }

      // diphoton mass in signal regions defined by BDTs
      if(pass_mva_cut_bdt_nrb_mixed03 && pass_mva_cut_bdt_smh_mixed03)   { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDT_smh_cut_mixed03"            , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdt_nrb_mixed04 && pass_mva_cut_bdt_smh_mixed04)   { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDT_smh_cut_mixed04"            , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdt_nrb_mixed05 && pass_mva_cut_bdt_smh_mixed05)   { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDT_smh_cut_mixed05"            , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed03 && pass_mva_cut_bdtg_smh_mixed03) { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDTG_smh_cut_mixed03"           , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed04 && pass_mva_cut_bdtg_smh_mixed04) { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDTG_smh_cut_mixed04"           , diphoton.M() , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed05 && pass_mva_cut_bdtg_smh_mixed05) { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_BDTG_smh_cut_mixed05"           , diphoton.M() , evt_weight , vId); }
      if(pass_selection_from_Maxime_optimization)                        { vProcess[processId]->fill_histogram("h" + syst_ext + "Mass_pass_Maxime_criteria_mixed03"        , diphoton.M() , evt_weight , vId); }

      // Tprime mass in signal regions defined by BDTs
      if(pass_mva_cut_bdt_nrb_mixed03 && pass_mva_cut_bdt_smh_mixed03)   { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_BDT_smh_cut_mixed03"     , mass_tprime  , evt_weight , vId); }
      if(pass_mva_cut_bdt_nrb_mixed04 && pass_mva_cut_bdt_smh_mixed04)   { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_BDT_smh_cut_mixed04"     , mass_tprime  , evt_weight , vId); }
      if(pass_mva_cut_bdt_nrb_mixed05 && pass_mva_cut_bdt_smh_mixed05)   { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_BDT_smh_cut_mixed05"     , mass_tprime  , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed03 && pass_mva_cut_bdtg_smh_mixed03) { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_BDTG_smh_cut_mixed03"    , mass_tprime  , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed04 && pass_mva_cut_bdtg_smh_mixed04) { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_BDTG_smh_cut_mixed04"    , mass_tprime  , evt_weight , vId); }
      if(pass_mva_cut_bdtg_nrb_mixed05 && pass_mva_cut_bdtg_smh_mixed05) { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_BDTG_smh_cut_mixed05"    , mass_tprime  , evt_weight , vId); }
      if(pass_selection_from_Maxime_optimization)                        { vProcess[processId]->fill_histogram("h" + syst_ext + "Tprime_Mass_pass_Maxime_criteria_mixed03" , mass_tprime  , evt_weight , vId); }
      //}}}

      //----------------------------------------------------------------------------------------------------
      // MVA Scores
      //----------------------------------------------------------------------------------------------------
      // more{{{
      // BDT
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed03_tmva_n100"  , mva_value_nrb_varset8_mixed03_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed03_tmva_n2000" , mva_value_nrb_varset8_mixed03_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed04_tmva_n100"  , mva_value_nrb_varset8_mixed04_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed04_tmva_n2000" , mva_value_nrb_varset8_mixed04_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed05_tmva_n100"  , mva_value_nrb_varset8_mixed05_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed05_tmva_n2000" , mva_value_nrb_varset8_mixed05_tmva , evt_weight , vId);

      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_n100"  , mva_value_smh_varset8_mixed03_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_n2000" , mva_value_smh_varset8_mixed03_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_n100"  , mva_value_smh_varset8_mixed04_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_n2000" , mva_value_smh_varset8_mixed04_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_n100"  , mva_value_smh_varset8_mixed05_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_n2000" , mva_value_smh_varset8_mixed05_tmva , evt_weight , vId);

      if(pass_mva_cut_bdt_nrb_mixed03){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_withNRBcut_n100"  , mva_value_smh_varset8_mixed03_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_withNRBcut_n2000" , mva_value_smh_varset8_mixed03_tmva , evt_weight , vId);
      }
      if(pass_mva_cut_bdt_nrb_mixed04){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_withNRBcut_n100"  , mva_value_smh_varset8_mixed04_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_withNRBcut_n2000" , mva_value_smh_varset8_mixed04_tmva , evt_weight , vId);
      }
      if(pass_mva_cut_bdt_nrb_mixed05){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_withNRBcut_n100"  , mva_value_smh_varset8_mixed05_tmva , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_withNRBcut_n2000" , mva_value_smh_varset8_mixed05_tmva , evt_weight , vId);
      }

      vProcess[processId]->fill_2D_histogram("h" + syst_ext + "MVAScore_nrb_smh_varset8_mixed03_tmva" , mva_value_nrb_varset8_mixed03_tmva , mva_value_smh_varset8_mixed03_tmva , evt_weight , vId);
      vProcess[processId]->fill_2D_histogram("h" + syst_ext + "MVAScore_nrb_smh_varset8_mixed04_tmva" , mva_value_nrb_varset8_mixed04_tmva , mva_value_smh_varset8_mixed04_tmva , evt_weight , vId);
      vProcess[processId]->fill_2D_histogram("h" + syst_ext + "MVAScore_nrb_smh_varset8_mixed05_tmva" , mva_value_nrb_varset8_mixed05_tmva , mva_value_smh_varset8_mixed05_tmva , evt_weight , vId);

      // BDTG
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed03_tmva_bdtg_n30"   , mva_value_nrb_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed03_tmva_bdtg_n100"  , mva_value_nrb_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed03_tmva_bdtg_n2000" , mva_value_nrb_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed04_tmva_bdtg_n30"   , mva_value_nrb_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed04_tmva_bdtg_n100"  , mva_value_nrb_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed04_tmva_bdtg_n2000" , mva_value_nrb_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed05_tmva_bdtg_n30"   , mva_value_nrb_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed05_tmva_bdtg_n100"  , mva_value_nrb_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_nrb_varset8_mixed05_tmva_bdtg_n2000" , mva_value_nrb_varset8_mixed05_tmva_bdtg , evt_weight , vId);

      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_n30"   , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_n100"  , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_n2000" , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_bdtg_n30"   , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_bdtg_n100"  , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_bdtg_n2000" , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_bdtg_n30"   , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_bdtg_n100"  , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_bdtg_n2000" , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);

      if(pass_mva_cut_bdtg_nrb_mixed03){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_withNRBcut_n30"   , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_withNRBcut_n100"  , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_withNRBcut_n2000" , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      }
      if(pass_mva_cut_bdtg_nrb_mixed04){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_bdtg_withNRBcut_n30"   , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_bdtg_withNRBcut_n100"  , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed04_tmva_bdtg_withNRBcut_n2000" , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      }
      if(pass_mva_cut_bdtg_nrb_mixed05){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_bdtg_withNRBcut_n30"   , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_bdtg_withNRBcut_n100"  , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed05_tmva_bdtg_withNRBcut_n2000" , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      }
      if(pass_mva_cut_bdtg_nrb_mixed03_Maxime){
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_withMaximeNRBcut_n30"   , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_withMaximeNRBcut_n100"  , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MVA_value_smh_varset8_mixed03_tmva_bdtg_withMaximeNRBcut_n2000" , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      }

      vProcess[processId]->fill_2D_histogram("h" + syst_ext + "MVAScore_nrb_smh_varset8_mixed03_tmva_bdtg" , mva_value_nrb_varset8_mixed03_tmva_bdtg , mva_value_smh_varset8_mixed03_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_2D_histogram("h" + syst_ext + "MVAScore_nrb_smh_varset8_mixed04_tmva_bdtg" , mva_value_nrb_varset8_mixed04_tmva_bdtg , mva_value_smh_varset8_mixed04_tmva_bdtg , evt_weight , vId);
      vProcess[processId]->fill_2D_histogram("h" + syst_ext + "MVAScore_nrb_smh_varset8_mixed05_tmva_bdtg" , mva_value_nrb_varset8_mixed05_tmva_bdtg , mva_value_smh_varset8_mixed05_tmva_bdtg , evt_weight , vId);
      //}}}

      //----------------------------------------------------------------------------------------------------
      // Kinematics
      //----------------------------------------------------------------------------------------------------
      // more{{{
      vProcess[processId]->fill_histogram("h" + syst_ext + "NVtx"               , nvtx()                             , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "Mass"               , diphoton.M()                       , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PtHiggs"            , diphoton.Pt()                      , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "DiphotonPtOverMass" , diphoton.Pt() / diphoton.M()       , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonDeltaR"       , lead_photon.DeltaR(sublead_photon) , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "Rapidity"           , diphoton.Rapidity()                , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "AbsCosHelicity"     , helicity_angle_                    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "DiphotonCosPhi"     , dipho_cosphi()                     , evt_weight , vId);

      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_wboson_cov"          , mass_wboson               , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_top_cov"             , mass_top                  , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_tprime_cov"          , mass_tprime               , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_tprime_tilde"        , mass_tprime_tilde         , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "cov_chi2_value"           , min_chi2_value_2x2        , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_bjet_pt"             , chi2_bjet_pt_             , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet1_pt"            , chi2_wjet1_pt_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet2_pt"            , chi2_wjet2_pt_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_bjet_eta"            , chi2_bjet_eta_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet1_eta"           , chi2_wjet1_eta_           , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet2_eta"           , chi2_wjet2_eta_           , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjets_deltaR"        , chi2_wjets_deltaR_        , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wboson_pt"           , chi2_wboson_pt_           , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wboson_eta"          , chi2_wboson_eta_          , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wboson_mass"         , chi2_wboson_mass_         , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wboson_deltaR_bjet"  , chi2_wboson_deltaR_bjet_  , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tbw_mass"            , chi2_tbw_mass_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tbw_pt"              , chi2_tbw_pt_              , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tbw_eta"             , chi2_tbw_eta_             , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tbw_deltaR_dipho"    , chi2_tbw_deltaR_dipho_    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tprime_ptOverM"      , chi2_tprime_ptOverM_      , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tprime_eta"          , chi2_tprime_eta_          , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tprime_deltaR_tbw"   , chi2_tprime_deltaR_tbw_   , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tprime_deltaR_dipho" , chi2_tprime_deltaR_dipho_ , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_bjet_btagScores"     , chi2_bjet_btagScores_     , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet1_btagScores"    , chi2_wjet1_btagScores_    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet2_btagScores"    , chi2_wjet2_btagScores_    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "tprime_pt_ratio"          , tprime_pt_ratio_          , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_bjet_ptOverM"        , chi2_bjet_ptOverM_        , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet1_ptOverM"       , chi2_wjet1_ptOverM_       , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wjet2_ptOverM"       , chi2_wjet2_ptOverM_       , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_wboson_ptOverM"      , chi2_wboson_ptOverM_      , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "chi2_tbw_ptOverM"         , chi2_tbw_ptOverM_         , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "helicity_tprime"          , helicity_tprime_          , evt_weight , vId);

      // Leading photon
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPt"        , dipho_leadPt()       , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadEta"       , dipho_leadEta()      , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPhi"       , dipho_leadPhi()      , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadIDMVA"     , leadID_              , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPToM"      , dipho_lead_ptoM()    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPixelSeed"    , dipho_lead_haspixelseed()    , evt_weight , vId);

      // Subleading photon
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPt"     , dipho_subleadPt()    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadEta"    , dipho_subleadEta()   , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPhi"    , dipho_subleadPhi()   , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadIDMVA"  , subleadID_           , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPToM"   , dipho_sublead_ptoM() , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPixelSeed" , dipho_sublead_haspixelseed() , evt_weight , vId);

      // Min/Max ID photon
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonMaxIDMVA"      , maxIDMVA_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonMinIDMVA"      , minIDMVA_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonMaxIDMVA_fine" , maxIDMVA_            , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonMinIDMVA_fine" , minIDMVA_            , evt_weight , vId);

      // Jets
      vProcess[processId]->fill_histogram("h" + syst_ext + "NJets"    , n_jets()    , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "NbLoose"  , n_L_bjets() , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "NbMedium" , n_M_bjets() , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "NbTight"  , n_T_bjets() , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "HT"                     , ht_                          , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MetPt"                  , met_                         , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "MaxBTag"                , max1_btag_                   , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "SecondMaxBTag"          , max2_btag_                   , evt_weight , vId);
      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet1pT"       , jet1_pt()     , evt_weight , vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet2pT"       , jet2_pt()     , evt_weight , vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet3pT"       , jet3_pt()     , evt_weight , vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet4pT"       , jet4_pt()     , evt_weight , vId);
      if (jet5_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet5pT"       , jet5_pt()     , evt_weight , vId);
      if (jet6_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet6pT"       , jet6_pt()     , evt_weight , vId);
      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet1Eta"      , jet1_eta()    , evt_weight , vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet2Eta"      , jet2_eta()    , evt_weight , vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet3Eta"      , jet3_eta()    , evt_weight , vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet4Eta"      , jet4_eta()    , evt_weight , vId);
      if (jet5_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet5Eta"      , jet5_eta()    , evt_weight , vId);
      if (jet6_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet6Eta"      , jet6_eta()    , evt_weight , vId);
      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet1BTag"     , jet1_discr()  , evt_weight , vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet2BTag"     , jet2_discr()  , evt_weight , vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet3BTag"     , jet3_discr()  , evt_weight , vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet4BTag"     , jet4_discr()  , evt_weight , vId);
      if (jet5_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet5BTag"     , jet5_discr()  , evt_weight , vId);
      if (jet6_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet6BTag"     , jet6_discr()  , evt_weight , vId);
      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "jet1_ptOverM" , jet1_ptOverM_ , evt_weight , vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "jet2_ptOverM" , jet2_ptOverM_ , evt_weight , vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "jet3_ptOverM" , jet3_ptOverM_ , evt_weight , vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "jet4_ptOverM" , jet4_ptOverM_ , evt_weight , vId);
      //}}}

      } // end of tprime mass criterion

      //----------------------------------------------------------------------------------------------------
      // skipped session
      //----------------------------------------------------------------------------------------------------
    } // end of event loop

    printf("[check] BDT(NRB) same: %d/%d (%.2f)\n", counter_nrb_same, counter, (double) counter_nrb_same / (double) counter);
    printf("[check] BDT(SMH) same: %d/%d (%.2f)\n", counter_smh_same, counter, (double) counter_smh_same / (double) counter);
    //printf("[check] jet energy < -100 GeV: %d/%d (%.2f)\n", counter_jet_negative_energy, counter, (double) counter_jet_negative_energy / (double) counter);
    printf("[check] jet energy < 0 GeV: %d/%d (%.2f)\n", counter_jet_negative_energy, counter, (double) counter_jet_negative_energy / (double) counter);
    printf("[check] T' mass > 3TeV : %d/%d (%.2f)\n" , counter_tprime_ultraHeavy_mass_3TeV  , counter , (double) counter_tprime_ultraHeavy_mass_3TeV / (double) counter);
    printf("[check] T' mass > 5TeV : %d/%d (%.2f)\n" , counter_tprime_ultraHeavy_mass_5TeV  , counter , (double) counter_tprime_ultraHeavy_mass_5TeV / (double) counter);
    printf("[check] T' mass > 7TeV : %d/%d (%.2f)\n" , counter_tprime_ultraHeavy_mass_7TeV  , counter , (double) counter_tprime_ultraHeavy_mass_7TeV / (double) counter);
    printf("[check] T' mass > 10TeV: %d/%d (%.2f)\n" , counter_tprime_ultraHeavy_mass_10TeV , counter , (double) counter_tprime_ultraHeavy_mass_10TeV / (double) counter);
    printf("[check] T' mass > 13TeV: %d/%d (%.2f)\n" , counter_tprime_ultraHeavy_mass_13TeV , counter , (double) counter_tprime_ultraHeavy_mass_13TeV / (double) counter);

    // Clean Up
    delete tree;
    file.Close();
  }
  delete tprimeTagger_nrb;
  delete tprimeTagger_smh;
  delete mva_smh_varset8_mixed03_tmva;
  delete mva_smh_varset8_mixed04_tmva;
  delete mva_smh_varset8_mixed05_tmva;
  delete mva_nrb_varset8_mixed03_tmva;
  delete mva_nrb_varset8_mixed04_tmva;
  delete mva_nrb_varset8_mixed05_tmva;
  delete mva_smh_varset8_mixed03_tmva_bdtg;
  delete mva_smh_varset8_mixed04_tmva_bdtg;
  delete mva_smh_varset8_mixed05_tmva_bdtg;
  delete mva_nrb_varset8_mixed03_tmva_bdtg;
  delete mva_nrb_varset8_mixed04_tmva_bdtg;
  delete mva_nrb_varset8_mixed05_tmva_bdtg;

  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  // Example Histograms
  output_file->cd();
  output_file->Write();
  output_file->Close();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "Expected Yields: " << total_yields << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time: " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time: " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}

