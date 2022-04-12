#include "MakeMVABabies_ttHHadronic.h"
#include "ScanChain.h"
#include "sorting.h"
#include "chi2_helper.h"
#include <TRandom3.h>
#include "TMVA/Reader.h"  // to produce ntuples for Maxime

#include "THQ_BDT_Helper.h"

void BabyMaker::ScanChain(TChain* chain, TString name_output_file, TString treeName, TString year, TString ext, TString bkg_options, TString mYear = "", TString idx = "", bool fcnc = false, bool blind = true, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  //----------------------------------------------------------------------------------------------------
  // init {{{
  //----------------------------------------------------------------------------------------------------
  TRandom3 rndm(1234);
  name_output_file = name_output_file.ReplaceAll("hist_", "MVABaby_");
  printf("Hello World! (Warm greeting from MakeMVABabies_ttHHadronic.C)\n");
  printf("[check] name_output_file = %s\n", name_output_file.Data());

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

  cout << "mYear: " << mYear << endl;
  //set_json(mYear); opening good run list

  double lumi_2016 = 35.9;
  double lumi_2017 = 41.5;
  double lumi_2018 = 59.76;
  double branching_fraction_hgg = 0.00227;
  double total_yields = 0.;

  TF1* photon_fakeID_shape_runII;
  if(mYear=="2016")
      photon_fakeID_shape_runII = get_photon_ID_shape("fake_runII");
  else
      photon_fakeID_shape_runII = get_photon_ID_shape("fake_tprime_ultraLegacy");

  //----------------------------------------------------------------------------------------------------}}}
  // options for producing ntuples {{{
  //----------------------------------------------------------------------------------------------------
  InitBabyNtuple(); // set all boolean false

  debug = false;
  Enable_flag_for_Maxime(); // produce_ntuples_for_Maxime
  //Enable_flag_for_fakePhotonStudy(); // produce_ntuples_for_fakePhotonStudy
  apply_preselection = true; // reflect stack plots
  //apply_preselection = false; // study "Low photon ID sideband"

  // Make baby ntuple
  MakeBabyNtuple( name_output_file.Data() );

  //----------------------------------------------------------------------------------------------------}}}
  // Init MVA Helpers {{{
  //----------------------------------------------------------------------------------------------------
  
  // MVA reference (consistency check)
  TString BDT_nrb_xml_file_;
  TString BDT_smh_xml_file_;
  bool use_v3p8;
  use_v3p8 = false;
  use_v3p8 = true;
  if ( use_v3p8 && (name_output_file.Contains("Data") || name_output_file.Contains("EGamma") || name_output_file.Contains("GJet_Pt") || name_output_file.Contains("QCD"))) { //v3p8
      BDT_nrb_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/20210620/dataset_Run2_Tprime_NRB_varSet8_M600_M700_20210620/weights/TMVAClassification_BDTG.weights.xml";
      BDT_smh_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/20210620/dataset_Run2_Tprime_SMH_varSet8_M600_M700_20210620/weights/TMVAClassification_BDTG.weights.xml";
  } else { //v3p6
      BDT_nrb_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/20210525/dataset_Run2_Tprime_NRB_varSet8_M600_M700_20210525/weights/TMVAClassification_BDTG.weights.xml";
      BDT_smh_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/20210520/dataset_Run2_Tprime_SMH_varSet8_M600_M700_20210520/weights/TMVAClassification_BDTG.weights.xml";
  }

  //bool ref_ultraLegacySample = (mYear!="2016");
  bool ref_ultraLegacySample = true;
  if (ref_ultraLegacySample) {
      BDT_nrb_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/20210820/dataset_Run2_Tprime_NRB_varSet8_M600_M700_20210820/weights/TMVAClassification_BDTG.weights.xml";
      BDT_smh_xml_file_ = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/20210818/dataset_Run2_Tprime_SMH_varSet8_M600_M700_20210818/weights/TMVAClassification_BDTG.weights.xml";
  }

  flashgg::THQ_BDT_Helper *tprimeTagger_nrb = new flashgg::THQ_BDT_Helper("BDTG", BDT_nrb_xml_file_);
  flashgg::THQ_BDT_Helper *tprimeTagger_smh = new flashgg::THQ_BDT_Helper("BDTG", BDT_smh_xml_file_);

  // MVAs
  TString path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ttH/MVAs/results/";

  TString mass_tag03 = "M600_M700_";
  TString mass_tag04 = "M800_M1000_";
  TString mass_tag05 = "M1100_M1200_";

  TString date = "20220118";
  date = "20220125";
  TString mvaTag = "BDTG";
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed03_tmva_bdtg = new flashgg::THQ_BDT_Helper(mvaTag.Data() , path+date+"/dataset_Run2_Tprime_SMH_varSet8_"+mass_tag03+date+"/weights/TMVAClassification_"+mvaTag+".weights.xml" );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed04_tmva_bdtg = new flashgg::THQ_BDT_Helper(mvaTag.Data() , path+date+"/dataset_Run2_Tprime_SMH_varSet8_"+mass_tag04+date+"/weights/TMVAClassification_"+mvaTag+".weights.xml" );
  flashgg::THQ_BDT_Helper *mva_smh_varset8_mixed05_tmva_bdtg = new flashgg::THQ_BDT_Helper(mvaTag.Data() , path+date+"/dataset_Run2_Tprime_SMH_varSet8_"+mass_tag05+date+"/weights/TMVAClassification_"+mvaTag+".weights.xml" );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed03_tmva_bdtg = new flashgg::THQ_BDT_Helper(mvaTag.Data() , path+date+"/dataset_Run2_Tprime_NRB_varSet8_"+mass_tag03+date+"/weights/TMVAClassification_"+mvaTag+".weights.xml" );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed04_tmva_bdtg = new flashgg::THQ_BDT_Helper(mvaTag.Data() , path+date+"/dataset_Run2_Tprime_NRB_varSet8_"+mass_tag04+date+"/weights/TMVAClassification_"+mvaTag+".weights.xml" );
  flashgg::THQ_BDT_Helper *mva_nrb_varset8_mixed05_tmva_bdtg = new flashgg::THQ_BDT_Helper(mvaTag.Data() , path+date+"/dataset_Run2_Tprime_NRB_varSet8_"+mass_tag05+date+"/weights/TMVAClassification_"+mvaTag+".weights.xml" );
  flashgg::InputVariables MVAvarList;

  //----------------------------------------------------------------------------------------------------}}}
  // counters{{{
  //----------------------------------------------------------------------------------------------------
  int counter = 0; // count events passing selection criteria
  int counter_negative_reco_mass = 0;
  int counter_jet_negative_energy = 0;
  int counter_nrb_same = 0;
  int counter_smh_same = 0;
  int counter_one_fake_photon = 0; // check "purity" for gammam + jet
  int counter_two_fake_photons = 0; // check "purity" for QCD
  //----------------------------------------------------------------------------------------------------}}}
  
  std::map<TString, double> map_pfDeepCSV_btag_loose_wp = { {"2016", 0.2217}, {"2017", 0.1355}, {"2018", 0.1208} };
  double pfDeepCSV_btag_loose_wp = map_pfDeepCSV_btag_loose_wp[mYear];

  int counter_check = 0;
  int counter_check_preselection = 0;
  int counter_check_lowPhotonSideBand = 0;
  int counter_check_rest = 0;
  int counter_check_myFunction = 0;
  int counter_inject_from_CR = 0;
  int counter_SR_mixed03 = 0;
  int counter_SR_mixed04 = 0;
  int counter_SR_mixed05 = 0;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    // Get file content {{{
    TString currentFileTitle = currentFile->GetTitle();
    cout << currentFileTitle << endl;
    TFile file(currentFileTitle);
    TTree *tree = (TTree*)file.Get(treeName); // "tagsDumper/trees/tHq_13TeV_THQHadronicTag"

    if (fast) TTreeCache::SetLearnEntries(10);
    if (fast) tree->SetCacheSize(128*1024*1024);
    analyzer.Init(tree);
    //}}}
    // Loop over Events in current file
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event)
    {
      //----------------------------------------------------------------------------------------------------
      // Get Event Content {{{
      //----------------------------------------------------------------------------------------------------
      if (nEventsTotal >= nEventsChain) continue;
      if (fast) tree->LoadTree(event);
      analyzer.GetEntry(event);
      ++nEventsTotal;

      // Progress
      tprimetHHadronic::progress( nEventsTotal, nEventsChain );

      //----------------------------------------------------------------------------------------------------}}}
      // Block signal region {{{
      //----------------------------------------------------------------------------------------------------
      bool isData = currentFileTitle.Contains("Data") || currentFileTitle.Contains("DoubleEG") || currentFileTitle.Contains("EGamma"); 
      //if (isData) if (!pass_json(mYear, analyzer.run(), analyzer.lumi())) continue; // to be checked further!!

      //int genPhotonId = -1; //categorize_photons(leadGenMatch(), subleadGenMatch());
      int genPhotonId = categorize_photons(leadGenMatch(), subleadGenMatch());
      process_id_ = categorize_process(currentFileTitle, genPhotonId);
      bool is_signal = (process_id_ >= 27 && process_id_ <= 36);
      bool is_ttH    = (process_id_ == 0);
      bool is_data = (process_id_ == 10);

      double lumi = mYear == "2016" ? lumi_2016 : (mYear == "2017") ? lumi_2017 : lumi_2018;

      // Decide evt wight
      evt_weight_ = is_data ? 1. : weight() * lumi;
      total_yields += evt_weight_;

      // Impute, if applicable
      maxIDMVA_ = dipho_leadIDMVA() >  dipho_subleadIDMVA() ? dipho_leadIDMVA() : dipho_subleadIDMVA();
      minIDMVA_ = dipho_leadIDMVA() <= dipho_subleadIDMVA() ? dipho_leadIDMVA() : dipho_subleadIDMVA();

      if (bkg_options.Contains("impute")) {
        if (isData && !produce_ntuples_for_fakePhotonStudy)
          impute_photon_id(min_photon_ID_presel_cut, maxIDMVA_, photon_fakeID_shape_runII, minIDMVA_, evt_weight_, process_id_);
        // reminder: in fake photon study, we need original min photon idmva for categorize events
      }

      if(!produce_ntuples_for_Maxime) {
        if (is_data && process_id_ != 18 && blind && CMS_hgg_mass() > 115. && CMS_hgg_mass() < 135.)  continue;
        if (is_data && process_id_ != 18 && blind && CMS_hgg_mass() > 115. && CMS_hgg_mass() < 135.)
            printf("[WARNING] Data events in signal region is used! mass = %.2f, process_id_ = %d\n", CMS_hgg_mass(), process_id_);
      }

      bool pass_photon_pt_criteria = dipho_leadPt()>30. && dipho_subleadPt()>18.;
      if(!pass_photon_pt_criteria) continue;

      if(apply_preselection){
          if (!passes_selection("ttHHadronic_RunII_MVA_Presel", minIDMVA_, maxIDMVA_)) continue;
          if (minIDMVA_ < -0.7 || maxIDMVA_< -0.7) continue;
      }
      
      if (isnan(evt_weight_) || isinf(evt_weight_) || evt_weight_ == 0) continue; //some pu weights are nan/inf and this causes problems for histos 
      if (has_std_overlaps(currentFileTitle, lead_Prompt(), sublead_Prompt(), genPhotonId)) continue;

      //for consistency test 
      //bool perform_consistency_check = false;
      //bool perform_consistency_check = true;
      //if(perform_consistency_check && process_id_ == 18) continue;

      //----------------------------------------------------------------------------------------------------}}}
      // Assign variables values {{{
      //----------------------------------------------------------------------------------------------------
      // assign values {{{
	  label_ = (is_data && process_id_ != 18) ? 2 : is_signal ? 1 : 0; // 0 = bkg, 1 = tprime, 2 = data
      multi_label_ = is_signal ? 0 : is_ttH ? 1 : 2; // signal vs tth vs bkg
      signal_mass_label_ = categorize_signal_sample(currentFileTitle);
      signal_mass_category_ = categorize_signal_mass_label(currentFileTitle);
      data_sideband_label_ = 0;

      //------------------------------ Variable definitions ------------------------------//
      vector<double> btag_scores;
      bool flag_negative_energy = false;
      vector<TLorentzVector> jets = make_jets(btag_scores, flag_negative_energy, false); //consistency check
      //vector<TLorentzVector> jets = make_jets(btag_scores);
      vector< std::pair<int, double> > btag_scores_sorted = sortVectorGreater(btag_scores);
      if(jets.size() < 3) continue;

      TLorentzVector diphoton, lead_photon, sublead_photon;
      lead_photon.SetPtEtaPhiM(dipho_leadPt(), dipho_leadEta(), dipho_leadPhi(), 0.);
      sublead_photon.SetPtEtaPhiM(dipho_subleadPt(), dipho_subleadEta(), dipho_subleadPhi(), 0.);
      diphoton.SetPtEtaPhiE(dipho_pt(), dipho_eta(), dipho_phi(), dipho_e());

      year_ = mYear == "2016" ? 2016 : (mYear == "2017" ? 2017 : (mYear == "2018" ? 2018 : -1)); 
      evt_  = analyzer.event();
      run_  = analyzer.run();
      lumi_ = analyzer.lumi();

      if(debug && flag_negative_energy)
          printf("[Info] Run:Lumi:Event = %d:%d:%d\n", run_, lumi_, evt_);

      ht_            = HT();
      scaled_ht_     = (ht_ / 2500.) - 1.;
      dipho_delta_R  = lead_photon.DeltaR(sublead_photon);

      // check nbjets
      float my_n_bjets = 0;
      bool to_get_nbjets = true;
      if(to_get_nbjets) {
          std::size_t num_jets = jets.size();
          for(std::size_t i = 0; i < num_jets; ++i ){ // b-jet
              if (btag_scores[i] < pfDeepCSV_btag_loose_wp) continue;
              if ( !(fabs(jets[i].Eta())<2.5) ) continue;
              my_n_bjets += 1;
          }
      }

      //njets_ = n_jets();
      njets_ = jets.size();
      //nbjets_ = n_L_bjets();
      nbjets_ = my_n_bjets;
      max1_btag_ = btag_scores_sorted[0].second;
      max2_btag_ = btag_scores_sorted[1].second;
      jet1_pt_   = njets_ >= 1 ? jets[0].Pt()   : -999;
      jet1_eta_  = njets_ >= 1 ? jets[0].Eta()  : -999;
      jet1_btag_ = njets_ >= 1 ? btag_scores[0] : -999;
      jet2_pt_   = njets_ >= 2 ? jets[1].Pt()   : -999; 
      jet2_eta_  = njets_ >= 2 ? jets[1].Eta()  : -999;
      jet2_btag_ = njets_ >= 2 ? btag_scores[1] : -999;
      jet3_pt_   = njets_ >= 3 ? jets[2].Pt()   : -999;
      jet3_eta_  = njets_ >= 3 ? jets[2].Eta()  : -999;
      jet3_btag_ = njets_ >= 3 ? btag_scores[2] : -999;
      jet4_pt_   = njets_ >= 4 ? jets[3].Pt()   : -999;
      jet4_eta_  = njets_ >= 4 ? jets[3].Eta()  : -999;
      jet4_btag_ = njets_ >= 4 ? btag_scores[3] : -999;
      jet5_pt_   = njets_ >= 5 ? jets[4].Pt()   : -999;
      jet5_eta_  = njets_ >= 5 ? jets[4].Eta()  : -999;
      jet5_btag_ = njets_ >= 5 ? btag_scores[4] : -999;
      jet6_pt_   = njets_ >= 6 ? jets[5].Pt()   : -999;
      jet6_eta_  = njets_ >= 6 ? jets[5].Eta()  : -999;
      jet6_btag_ = njets_ >= 6 ? btag_scores[5] : -999;
      jet7_pt_   = njets_ >= 7 ? jets[6].Pt()   : -999;
      jet7_eta_  = njets_ >= 7 ? jets[6].Eta()  : -999;
      jet7_btag_ = njets_ >= 7 ? btag_scores[6] : -999;
      jet8_pt_   = njets_ >= 8 ? jets[7].Pt()   : -999;
      jet8_eta_  = njets_ >= 8 ? jets[7].Eta()  : -999;
      jet8_btag_ = njets_ >= 8 ? btag_scores[7] : -999; 

      jet1_phi_     = njets_ >= 1 ? jets[0].Phi() : -999;
      jet1_energy_  = njets_ >= 1 ? jets[0].E()   : -999;
      jet2_phi_     = njets_ >= 2 ? jets[1].Phi() : -999;
      jet2_energy_  = njets_ >= 2 ? jets[1].E()   : -999;
      jet3_phi_     = njets_ >= 3 ? jets[2].Phi() : -999;
      jet3_energy_  = njets_ >= 3 ? jets[2].E()   : -999;
      jet4_phi_     = njets_ >= 4 ? jets[3].Phi() : -999;
      jet4_energy_  = njets_ >= 4 ? jets[3].E()   : -999;
      jet5_phi_     = njets_ >= 5 ? jets[4].Phi() : -999;
      jet5_energy_  = njets_ >= 5 ? jets[4].E()   : -999;
      jet6_phi_     = njets_ >= 6 ? jets[5].Phi() : -999;
      jet6_energy_  = njets_ >= 6 ? jets[5].E()   : -999;
      jet7_phi_     = njets_ >= 7 ? jets[6].Phi() : -999;
      jet7_energy_  = njets_ >= 7 ? jets[6].E()   : -999;
      jet8_phi_     = njets_ >= 8 ? jets[7].Phi() : -999;
      jet8_energy_  = njets_ >= 8 ? jets[7].E()   : -999;

      // photons, diphoton, helicity angle, top masses
      lead_pT_      = dipho_leadPt();
      sublead_pT_   = dipho_subleadPt();
      leadptoM_     = dipho_lead_ptoM();
      subleadptoM_  = dipho_sublead_ptoM();
      leadIDMVA_    = dipho_leadIDMVA();
      subleadIDMVA_ = dipho_subleadIDMVA();
      lead_eta_     = dipho_leadEta();
      sublead_eta_  = dipho_subleadEta();
      lead_phi_     = dipho_leadPhi();
      sublead_phi_  = dipho_subleadPhi();

      leadPSV_ = dipho_lead_haspixelseed();
      subleadPSV_ = dipho_sublead_haspixelseed();

      dipho_cosphi_ = dipho_cosphi();
      dipho_pt_ = dipho_pt();
      dipho_pt_over_mass_ = dipho_pt() / CMS_hgg_mass();
      met_ = recoMET_pt();
      log_met_ = log(recoMET_pt());
      met_phi_ = recoMET_phi();

      dipho_rapidity_ = diphoton.Rapidity(); //dipho_rapidity();
      helicity_angle_ = helicity(lead_photon, sublead_photon);

      //calculate_masses(diphoton, jets, m_ggj_, m_jjj_);
      m_ggj_ = -1; //m_ggj_ > 0 ? log(m_ggj_) : -9;
      m_jjj_ = -1; //m_jjj_ > 0 ? log(m_jjj_) : -9;

      //------------------------------ Minimum chi-2 method (cov.) ------------------------------//
      TString json_file = "json/covMatrix_Era2017_M1000.json";
      double min_chi2_value_2x2 = 99999.;
      vector<int> indices_bjj_covMatrix(3, -1);
      bool has_resonable_reco = get_the_best_bjj_candidate(mYear, indices_bjj_covMatrix, jets, diphoton, btag_scores, min_chi2_value_2x2, json_file);

      TLorentzVector null;
      TLorentzVector cov_bjet   = has_resonable_reco ? jets[indices_bjj_covMatrix[0]] : null;
      TLorentzVector cov_wjet1  = has_resonable_reco ? jets[indices_bjj_covMatrix[1]] : null;
      TLorentzVector cov_wjet2  = has_resonable_reco ? jets[indices_bjj_covMatrix[2]] : null;
      TLorentzVector cov_wboson = cov_wjet1 + cov_wjet2;
      TLorentzVector cov_top    = cov_bjet + cov_wboson;
      TLorentzVector cov_tprime = cov_top + diphoton;

      //bool pass_eta_criteria_on_wjets = ( cov_wjet1.Eta() < 3. && cov_wjet2.Eta() < 3. );
      bool pass_eta_criteria_on_wjets = ( abs(cov_wjet1.Eta()) < 3. && abs(cov_wjet2.Eta()) < 3. );

      if( !pass_eta_criteria_on_wjets ) continue;
      if( !has_resonable_reco ) continue;
      //if( !passes_btag_rescale_selection ) continue;

      min_chi2_value_2x2 = has_resonable_reco ? min_chi2_value_2x2 : -1.;

      chi2_value_               = min_chi2_value_2x2;
      chi2_bjet_pt_             = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.Pt()                         : -999;
      chi2_wjet1_pt_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.Pt()                        : -999;
      chi2_wjet2_pt_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.Pt()                        : -999;
      chi2_bjet_eta_            = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.Eta()                        : -999;
      chi2_wjet1_eta_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.Eta()                       : -999;
      chi2_wjet2_eta_           = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.Eta()                       : -999;
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

      helicity_tprime_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? helicity(cov_top, diphoton)           : -999;

      // use mass reconstructed at producer level for better consistency in significant digit; v3p5 onward
      chi2_wboson_mass_         = chi2_recoMass_wboson();
      chi2_tbw_mass_            = chi2_recoMass_top();
      chi2_value_               = chi2_calculator_2x2(chi2_wboson_mass_, chi2_tbw_mass_);

      chi2_bjet_ptOverM_        = (has_resonable_reco && pass_eta_criteria_on_wjets ) ? cov_bjet.Pt()   / chi2_tbw_mass_         : -999;
      chi2_wjet1_ptOverM_       = (has_resonable_reco && pass_eta_criteria_on_wjets ) ? cov_wjet1.Pt()  / chi2_wboson_mass_      : -999;
      chi2_wjet2_ptOverM_       = (has_resonable_reco && pass_eta_criteria_on_wjets ) ? cov_wjet2.Pt()  / chi2_wboson_mass_      : -999;
      chi2_wboson_ptOverM_      = (has_resonable_reco && pass_eta_criteria_on_wjets ) ? cov_wboson.Pt() / chi2_wboson_mass_      : -999;
      chi2_tbw_ptOverM_         = (has_resonable_reco && pass_eta_criteria_on_wjets ) ? cov_top.Pt()    / chi2_tbw_mass_         : -999;
      chi2_tprime_ptOverM_      = (has_resonable_reco && pass_eta_criteria_on_wjets ) ? cov_tprime.Pt() / chi2_recoMass_tprime() : -999;

      jet1_ptOverM_ = (njets_ >= 1 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[0].Pt() / chi2_tbw_mass_  : -999;
      jet2_ptOverM_ = (njets_ >= 2 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[1].Pt() / chi2_tbw_mass_  : -999; 
      jet3_ptOverM_ = (njets_ >= 3 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[2].Pt() / chi2_tbw_mass_  : -999;
      jet4_ptOverM_ = (njets_ >= 4 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[3].Pt() / chi2_tbw_mass_  : -999;

      //----------------------------------------------------------------------------------------------------//
      
      rand_ = rndm.Rndm(); // index for training and validation
      super_rand_ = -1; //rand_map->retrieve_rand(analyzer.event(), analyzer.run(), analyzer.lumi());
      mass_ = CMS_hgg_mass();
      lead_sigmaEtoE_ = dipho_lead_sigmaEoE();
      sublead_sigmaEtoE_ = dipho_sublead_sigmaEoE();

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
        //}}}

      //----------------------------------------------------------------------------------------------------}}}
      // Apply normalization factors from template fit
      //----------------------------------------------------------------------------------------------------
      //double weight_from_template_fit = 1.;
      double weight_from_template_fit = get_weight_from_template_fit(mYear, process_id_);
      evt_weight_ *= weight_from_template_fit;

      // For Maxime {{{
      //----------------------------------------------------------------------------------------------------
      // Note: 
      // 1. evt_weight_ for ggh and tth have oversample correction
      // 2. mva scores are transformed scores from BDT
      // 3. 3 kinds of mva scores according to T' mass
      
      if(produce_ntuples_for_Maxime){
        dipho_mass_    = diphoton.M();
        tprime_mass_   = cov_tprime.M();
        tprime_mtilde_ = cov_tprime.M() - cov_top.M() - diphoton.M() + 173. + 125.;
      }

      bdtg_score_nrb_m600_m700_   = mva_nrb_varset8_mixed03_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      bdtg_score_nrb_m800_m1000_  = mva_nrb_varset8_mixed04_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      bdtg_score_nrb_m1100_m1200_ = mva_nrb_varset8_mixed05_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      bdtg_score_smh_m600_m700_   = mva_smh_varset8_mixed03_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      bdtg_score_smh_m800_m1000_  = mva_smh_varset8_mixed04_tmva_bdtg->evaluate("BDTG" , MVAvarList);
      bdtg_score_smh_m1100_m1200_ = mva_smh_varset8_mixed05_tmva_bdtg->evaluate("BDTG" , MVAvarList);

      double mva_value_nrb = tprimeTagger_nrb->evaluate("BDTG" , MVAvarList);
      double mva_value_smh = tprimeTagger_smh->evaluate("BDTG" , MVAvarList);

      //----------------------------------------------------------------------------------------------------//}}}
      // MVA cut values {{{
      //----------------------------------------------------------------------------------------------------
      bool pass_mva_cut_bdtg_nrb_mixed03 = bdtg_score_nrb_m600_m700_   > 0.530;
      bool pass_mva_cut_bdtg_nrb_mixed04 = bdtg_score_nrb_m800_m1000_  > 0.363;
      bool pass_mva_cut_bdtg_nrb_mixed05 = bdtg_score_nrb_m1100_m1200_ > 0.228;
      bool pass_mva_cut_bdtg_smh_mixed03 = bdtg_score_smh_m600_m700_   > 0.828;
      bool pass_mva_cut_bdtg_smh_mixed04 = bdtg_score_smh_m800_m1000_  > 0.826;
      bool pass_mva_cut_bdtg_smh_mixed05 = bdtg_score_smh_m1100_m1200_ > 0.816;

      bool is_within_SR_mixed03 = pass_mva_cut_bdtg_nrb_mixed03 && pass_mva_cut_bdtg_smh_mixed03;
      bool is_within_SR_mixed04 = pass_mva_cut_bdtg_nrb_mixed04 && pass_mva_cut_bdtg_smh_mixed04;
      bool is_within_SR_mixed05 = pass_mva_cut_bdtg_nrb_mixed05 && pass_mva_cut_bdtg_smh_mixed05;
      bool is_within_CR_mixed03 = pass_mva_cut_bdtg_nrb_mixed03 && !pass_mva_cut_bdtg_smh_mixed03;
      bool is_within_CR_mixed04 = pass_mva_cut_bdtg_nrb_mixed04 && !pass_mva_cut_bdtg_smh_mixed04;
      bool is_within_CR_mixed05 = pass_mva_cut_bdtg_nrb_mixed05 && !pass_mva_cut_bdtg_smh_mixed05;

      //----------------------------------------------------------------------------------------------------}}}
      bool performExcessStudy = false; //{{{
      if(performExcessStudy) {
          bool vip_permission;
          bool in_signal_window = CMS_hgg_mass() > 115. && CMS_hgg_mass() < 135.;
          bool within_limits = counter_inject_from_CR < 320; // # of injected CR events
          vip_permission = is_within_CR_mixed03 && in_signal_window && within_limits;
          //vip_permission = assign_permission(run_, lumi_, evt_);
          
          bool blind_signal_window = is_data && process_id_ != 18 && blind && in_signal_window;
          if( blind_signal_window && !vip_permission) continue;
          if( !(process_id_!=18 && (is_within_SR_mixed03 || vip_permission)) ) continue;
          if( vip_permission ) counter_inject_from_CR += 1;
      } //}}}
      // check signal efficiency
      if(process_id_ != 18 && is_within_SR_mixed03) counter_SR_mixed03 += 1;
      if(process_id_ != 18 && is_within_SR_mixed04) counter_SR_mixed04 += 1;
      if(process_id_ != 18 && is_within_SR_mixed05) counter_SR_mixed05 += 1;

      // Debug: entries in low photon sideband
      counter_check += 1; // after pre-selection
      if ( passes_selection("ttHHadronic_RunII_MVA_Presel", minIDMVA_, maxIDMVA_, -999.) )
          counter_check_preselection += 1;
      else if ( process_id_==18 || (minIDMVA_ < -0.7 && maxIDMVA_ > -0.7) )
          counter_check_lowPhotonSideBand += 1;
      else
          counter_check_rest += 1;

      if ( process_id_==18 || passes_selection("fake_photon_study", minIDMVA_, maxIDMVA_, -999.) )
          counter_check_myFunction += 1;

      // consistency check {{{
      //----------------------------------------------------------------------------------------------------//
      if(process_id_ != 18) { //exclude data-driven from consistency check
          counter += 1;
          if(flag_negative_energy) counter_jet_negative_energy += 1;
          // # turn off sanity check for BDT (b-jet criteria change)
          //bool found_discrepancy_nrb = mycheck("BDT (NRB)", counter_nrb_same, MVAscore_BDT_nrb(), mva_value_nrb, dipho_pt());
          //bool found_discrepancy_smh = mycheck("BDT (SMH)", counter_smh_same, MVAscore_BDT_smh(), mva_value_smh, dipho_pt());

          // check inf values
          bool flag = false;
          if(chi2_recoMass_wboson()<=0.) { flag = true; printf("chi2_recoMass_wboson() = %f, %f\n", chi2_recoMass_wboson(), cov_wboson.M()); }
          if(chi2_recoMass_top()<=0.)    { flag = true; printf("chi2_recoMass_top() = %f, %f\n", chi2_recoMass_top(), cov_top.M());          }
          if(chi2_recoMass_tprime()<=0.) { flag = true; printf("chi2_recoMass_tprime() = %f, %f\n", chi2_recoMass_tprime(), cov_tprime.M()); }
          if(flag)
          {
              counter_negative_reco_mass += 1;
              tprimeTagger_nrb->print_details(MVAvarList);
              printf("\n----------------------------------------------------------------------------------------------------\n\n");
          }
          tprimeTagger_nrb->examine_values(MVAvarList); // print out when found Nan or Inf values
      }

      //----------------------------------------------------------------------------------------------------//}}}
      // Fake photon study / oversampling {{{
      //----------------------------------------------------------------------------------------------------//
      if(produce_ntuples_for_fakePhotonStudy) {

          // fake photon IDMVA: t_fakePhotonIDMVA
          if(genPhotonId == 0) { // fake-fake
              fake_photon_IDMVA_ = dipho_leadIDMVA();
              FillBabyNtuple_fakePhoton();
              fake_photon_IDMVA_ = dipho_subleadIDMVA();
              FillBabyNtuple_fakePhoton();
              if(minIDMVA_<-0.7 && maxIDMVA_<-0.7)
                counter_two_fake_photons += 1;
          } else if (genPhotonId == 1) { // one fake photon
              if(leadGenMatch() != 1)    { fake_photon_IDMVA_ = dipho_leadIDMVA()   ; }
              if(subleadGenMatch() != 1) { fake_photon_IDMVA_ = dipho_subleadIDMVA(); }
              FillBabyNtuple_fakePhoton();
              if(minIDMVA_<-0.7)
                counter_one_fake_photon += 1;
          } else if (genPhotonId == 2) { // prompt-prompt
          } else {
              printf("[fake photon study] Case not applicable..\n");
          }

          // correlation study: t_lowPhotonSideband (GJet/QCD only)
          FillBabyNtuple_lowPhotonSideband();

          // composition study: Data (MC) in low photon sideband
          if ( process_id_==18 || passes_selection("fake_photon_study", minIDMVA_, maxIDMVA_, -999.) )
          {
              // general info: t, t_maxPhotonIDMVA, t_minPhotonIDMVA
              FillBabyNtuple();
          }

      } else if(produce_ntuples_for_Maxime) {
          if(process_id_!=18) FillBabyNtuple();
      } else {
          const float oversample_ggh = 81.;
          const float oversample_tth = 1.;
          float oversample;
          if (fcnc) {
            if (process_id_ == 14)
              oversample = oversample_ggh;
            else if (process_id_ == 0)
              oversample = oversample_tth;
            else
              oversample = 1.;
            evt_weight_ *= 1./oversample;
            for (int i = 0; i < int(oversample); i++)
              FillBabyNtuple();
          }
          else
            FillBabyNtuple();
      }
      //}}}
    }// end of event loop

    delete tree;
    file.Close();
  }// end of while loop
  // print info & clean up{{{
  printf("[check] reco mass < 0 GeV: %d/%d (%.2f)\n", counter_negative_reco_mass, counter, (double) counter_negative_reco_mass / (double) counter);
  printf("[check] jet energy < -100 GeV: %d/%d (%.2f)\n", counter_jet_negative_energy, counter, (double) counter_jet_negative_energy / (double) counter);
  printf("[check] BDT(NRB) same: %d/%d (%.2f)\n", counter_nrb_same, counter, (double) counter_nrb_same / (double) counter);
  printf("[check] BDT(SMH) same: %d/%d (%.2f)\n", counter_smh_same, counter, (double) counter_smh_same / (double) counter);
  printf("[check] one fake photon : %d/%d (%.2f)\n", counter_one_fake_photon, counter, (double) counter_one_fake_photon / (double) counter);
  printf("[check] two fake photons: %d/%d (%.2f)\n", counter_two_fake_photons, counter, (double) counter_two_fake_photons / (double) counter);

  print_counter("counter_check_preselection", counter_check_preselection, counter_check);
  print_counter("counter_check_lowPhotonSideBand", counter_check_lowPhotonSideBand, counter_check);
  print_counter("counter_check_rest", counter_check_rest, counter_check);
  print_counter("counter_check_myFunction", counter_check_myFunction, counter_check);

  // percentage in SRs after pre-selection (exclude data-driven samples)
  print_counter("is_within_SR_mixed03", counter_SR_mixed03, counter);
  print_counter("is_within_SR_mixed04", counter_SR_mixed04, counter);
  print_counter("is_within_SR_mixed05", counter_SR_mixed05, counter);

  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  //}}}
  // release memory & write & end {{{
  delete tprimeTagger_nrb;
  delete tprimeTagger_smh;
  delete mva_nrb_varset8_mixed03_tmva_bdtg;
  delete mva_nrb_varset8_mixed04_tmva_bdtg;
  delete mva_nrb_varset8_mixed05_tmva_bdtg;
  delete mva_smh_varset8_mixed03_tmva_bdtg;
  delete mva_smh_varset8_mixed04_tmva_bdtg;
  delete mva_smh_varset8_mixed05_tmva_bdtg;

  CloseBabyNtuple();
 
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "Expected Yields: " << total_yields << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time: " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time: " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return;
  //}}}
}
