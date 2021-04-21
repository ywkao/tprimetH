#include "MakeMVABabies_ttHHadronic.h"
#include "ScanChain.h"
#include "sorting.h"
#include "chi2_helper.h"
#include <TRandom3.h>

void BabyMaker::ScanChain(TChain* chain, TString name_output_file, TString year, TString ext, TString bkg_options, TString mYear = "", TString idx = "", bool fcnc = false, bool blind = false, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  TRandom3 rndm(1234);
  name_output_file = name_output_file.ReplaceAll("hist_", "MVABaby_");
  printf("Hello World! (Warm greeting from MakeMVABabies_ttHHadronic.C)\n");
  printf("[check] name_output_file = %s\n", name_output_file.Data());

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Make baby ntuple
  MakeBabyNtuple( name_output_file.Data() ); //MakeBabyNtuple( Form("plots/MVABaby_tprimetHHadronic_%s.root", (mYear + idx).Data()));

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

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    TString currentFileTitle = currentFile->GetTitle();
    cout << currentFileTitle << endl;
    TFile file(currentFileTitle);
    TTree *tree;
    tree = (TTree*)file.Get("tagsDumper/trees/tHq_13TeV_THQHadronicTag");

    if (fast) TTreeCache::SetLearnEntries(10);
    if (fast) tree->SetCacheSize(128*1024*1024);
    analyzer.Init(tree);

    // Decide what type of sample this is
    bool isData = false;
    bool isSignal = true;

    bool debug = false;
    int counter = 0; // check nan value
    // Loop over Events in current file
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event)
    {
      // Get Event Content, label type of samples, decide evt weight
      if (nEventsTotal >= nEventsChain) continue;
      if (fast) tree->LoadTree(event);
      analyzer.GetEntry(event);
      ++nEventsTotal;

      // Progress
      tprimetHHadronic::progress( nEventsTotal, nEventsChain );
      InitBabyNtuple();

      // Decide what type of sample this is
      int genPhotonId = 2; //categorize_photons(leadGenMatch(), subleadGenMatch());
      process_id_ = categorize_process(currentFileTitle, genPhotonId);

      double lumi = mYear == "2016" ? lumi_2016 : (mYear == "2017") ? lumi_2017 : lumi_2018;
      evt_weight_ = weight() * branching_fraction_hgg * lumi;
      //printf("[check] evt_weight_ = %.7f = %.7f x %.5f x %.2f\n", evt_weight_, weight(), branching_fraction_hgg, lumi);
      total_yields += evt_weight_;

      // Impute, if applicable
      maxIDMVA_ = dipho_leadIDMVA() >  dipho_subleadIDMVA() ? dipho_leadIDMVA() : dipho_subleadIDMVA();
      minIDMVA_ = dipho_leadIDMVA() <= dipho_subleadIDMVA() ? dipho_leadIDMVA() : dipho_subleadIDMVA();

      //if (has_std_overlaps(currentFileTitle, lead_Prompt(), sublead_Prompt(), genPhotonId)) continue;
      if (minIDMVA_ < -0.7 || maxIDMVA_< -0.7) continue;
      if (isnan(evt_weight_) || isinf(evt_weight_) || evt_weight_ == 0) continue; //some pu weights are nan/inf and this causes problems for histos 

      label_ = 1; // signal
      multi_label_ = 0; // signal
      signal_mass_label_ = categorize_signal_sample(currentFileTitle);
      signal_mass_category_ = categorize_signal_mass_label(currentFileTitle);
      data_sideband_label_ = 0;

      //------------------------------ Variable definitions ------------------------------//
      vector<double> btag_scores;
      vector<TLorentzVector> jets = make_jets(btag_scores);
      vector<TLorentzVector> jets_copy = jets; // debug purpose
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

      ht_            = get_ht(jets);
      dipho_delta_R  = lead_photon.DeltaR(sublead_photon);
      top_tag_score_ = -1;
	  top_tag_mass_  = -1;
      top_tag_pt_    = -1;
      top_tag_eta_   = -1;
      top_tag_phi_   = -1;

      njets_ = n_jets();
      nbjets_ = n_M_bjets();
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
      dipho_pt_ = diphoton.Pt();
      dipho_pt_over_mass_ = diphoton.Pt() / diphoton.M();
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
      bool has_resonable_reco = get_the_best_bjj_candidate(indices_bjj_covMatrix, jets, diphoton, btag_scores, min_chi2_value_2x2, json_file);

      TLorentzVector null;
      TLorentzVector cov_bjet   = has_resonable_reco ? jets[indices_bjj_covMatrix[0]] : null;
      TLorentzVector cov_wjet1  = has_resonable_reco ? jets[indices_bjj_covMatrix[1]] : null;
      TLorentzVector cov_wjet2  = has_resonable_reco ? jets[indices_bjj_covMatrix[2]] : null;
      TLorentzVector cov_wboson = cov_wjet1 + cov_wjet2;
      TLorentzVector cov_top    = cov_bjet + cov_wboson;
      TLorentzVector cov_tprime = cov_top + diphoton;

      bool pass_eta_criteria_on_wjets = ( cov_wjet1.Eta() < 3. && cov_wjet2.Eta() < 3. );
      //if( !passes_btag_rescale_selection ) continue;

      double mass_wboson = has_resonable_reco ? cov_wboson.M()     : -1.;
      double mass_top    = has_resonable_reco ? cov_top.M()        : -1.;
      double mass_tprime = has_resonable_reco ? cov_tprime.M()     : -1.;
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
      chi2_tprime_ptOverM_      = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.Pt()/cov_tprime.M()        : -999;
      chi2_tprime_eta_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.Eta()                      : -999;
      chi2_tprime_deltaR_tbw_   = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.DeltaR(cov_top)            : -999;
      chi2_tprime_deltaR_dipho_ = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_tprime.DeltaR(diphoton)           : -999;
      chi2_bjet_btagScores_     = (has_resonable_reco && pass_eta_criteria_on_wjets) ? btag_scores[indices_bjj_covMatrix[0]] : -999;
      chi2_wjet1_btagScores_    = (has_resonable_reco && pass_eta_criteria_on_wjets) ? btag_scores[indices_bjj_covMatrix[1]] : -999;
      chi2_wjet2_btagScores_    = (has_resonable_reco && pass_eta_criteria_on_wjets) ? btag_scores[indices_bjj_covMatrix[2]] : -999;
      tprime_pt_ratio_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? (cov_top.Pt() + dipho_pt())/ ht_      : -999;

      chi2_bjet_ptOverM_        = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_bjet.Pt() / cov_top.M()           : -999;
      chi2_wjet1_ptOverM_       = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet1.Pt() / cov_wboson.M()       : -999;
      chi2_wjet2_ptOverM_       = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wjet2.Pt() / cov_wboson.M()       : -999;
      chi2_wboson_ptOverM_      = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_wboson.Pt() / cov_wboson.M()      : -999;
      chi2_tbw_ptOverM_         = (has_resonable_reco && pass_eta_criteria_on_wjets) ? cov_top.Pt() / cov_top.M()            : -999;
      helicity_tprime_          = (has_resonable_reco && pass_eta_criteria_on_wjets) ? helicity(cov_top, diphoton)           : -999;

      if(debug && isnan(helicity_tprime_))
      {
          counter += 1;
          printf("[check] indices_bjj_covMatrix[0] = %d\n", indices_bjj_covMatrix[0]);
          printf("[check] indices_bjj_covMatrix[1] = %d\n", indices_bjj_covMatrix[1]);
          printf("[check] indices_bjj_covMatrix[2] = %d\n", indices_bjj_covMatrix[2]);
          printf("\n");

          printf("[check] (Pt, Eta, Phi, M) \n");
          printf("[check] cov_bjet   = (%7.2f, %7.2f, %7.2f, %7.2f) \n", cov_bjet.Pt(), cov_bjet.Eta(), cov_bjet.Phi(), cov_bjet.M() );
          printf("[check] cov_wjet1  = (%7.2f, %7.2f, %7.2f, %7.2f) \n", cov_wjet1.Pt(), cov_wjet1.Eta(), cov_wjet1.Phi(), cov_wjet1.M() );
          printf("[check] cov_wjet2  = (%7.2f, %7.2f, %7.2f, %7.2f) \n", cov_wjet2.Pt(), cov_wjet2.Eta(), cov_wjet2.Phi(), cov_wjet2.M() );
          printf("[check] cov_wboson = (%7.2f, %7.2f, %7.2f, %7.2f) \n", cov_wboson.Pt(), cov_wboson.Eta(), cov_wboson.Phi(), cov_wboson.M() );
          printf("[check] cov_top    = (%7.2f, %7.2f, %7.2f, %7.2f) \n", cov_top.Pt(), cov_top.Eta(), cov_top.Phi(), cov_top.M() );
          printf("\n");

          printf("[check] (Px, Py, Pz, E, M) \n");
          printf("[check] cov_bjet   = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", cov_bjet.Px(), cov_bjet.Py(), cov_bjet.Pz(), cov_bjet.E(), cov_bjet.M() );
          printf("[check] cov_wjet1  = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", cov_wjet1.Px(), cov_wjet1.Py(), cov_wjet1.Pz(), cov_wjet1.E(), cov_wjet1.M() );
          printf("[check] cov_wjet2  = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", cov_wjet2.Px(), cov_wjet2.Py(), cov_wjet2.Pz(), cov_wjet2.E(), cov_wjet2.M() );
          printf("[check] cov_wboson = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", cov_wboson.Px(), cov_wboson.Py(), cov_wboson.Pz(), cov_wboson.E(), cov_wboson.M() );
          printf("[check] cov_top    = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", cov_top.Px(), cov_top.Py(), cov_top.Pz(), cov_top.E(), cov_top.M() );

          int i = indices_bjj_covMatrix[0];
          int j = indices_bjj_covMatrix[1];
          int k = indices_bjj_covMatrix[2];
          printf("[check] jets[%d]    = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", i, jets[i].Px(), jets[i].Py(), jets[i].Pz(), jets[i].E(), jets[i].M() );
          printf("[check] jets[%d]    = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", j, jets[j].Px(), jets[j].Py(), jets[j].Pz(), jets[j].E(), jets[j].M() );
          printf("[check] jets[%d]    = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", k, jets[k].Px(), jets[k].Py(), jets[k].Pz(), jets[k].E(), jets[k].M() );
          printf("[check] j_copy[%d]  = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", i, jets_copy[i].Px(), jets_copy[i].Py(), jets_copy[i].Pz(), jets_copy[i].E(), jets_copy[i].M() );
          printf("[check] j_copy[%d]  = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", j, jets_copy[j].Px(), jets_copy[j].Py(), jets_copy[j].Pz(), jets_copy[j].E(), jets_copy[j].M() );
          printf("[check] j_copy[%d]  = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f) \n", k, jets_copy[k].Px(), jets_copy[k].Py(), jets_copy[k].Pz(), jets_copy[k].E(), jets_copy[k].M() );

          //printf("[check] cov_wjet1.Pt()        = %.2f\n", cov_wjet1.Pt()   );
          //printf("[check] cov_wjet1.Eta()       = %.2f\n", cov_wjet1.Eta()  );
          //printf("[check] cov_wjet1.Phi()       = %.2f\n", cov_wjet1.Phi()  );
          //printf("[check] cov_wjet1.M()         = %.2f\n", cov_wjet1.M()    );

          //printf("[check] cov_wjet2.Pt()        = %.2f\n", cov_wjet2.Pt()   );
          //printf("[check] cov_wjet2.Eta()       = %.2f\n", cov_wjet2.Eta()  );
          //printf("[check] cov_wjet2.Phi()       = %.2f\n", cov_wjet2.Phi()  );
          //printf("[check] cov_wjet2.M()         = %.2f\n", cov_wjet2.M()    );

          //printf("[check] cov_wboson.Pt()       = %.2f\n", cov_wboson.Pt()  );
          //printf("[check] cov_wboson.Eta()      = %.2f\n", cov_wboson.Eta() );
          //printf("[check] cov_wboson.Phi()      = %.2f\n", cov_wboson.Phi() );
          //printf("[check] cov_wboson.M()        = %.2f\n", cov_wboson.M()   );

          //printf("[check] cov_top.Pt()          = %.2f\n", cov_top.Pt()   );
          //printf("[check] cov_top.Eta()         = %.2f\n", cov_top.Eta()  );
          //printf("[check] cov_top.Phi()         = %.2f\n", cov_top.Phi()  );
          //printf("[check] cov_top.M()           = %.2f\n", cov_top.M()    );

          //TLorentzVector test_p1, test_p2, test_m;
          //test_p1.SetPtEtaPhiM( cov_wjet1.Pt(), cov_wjet1.Eta(), cov_wjet1.Phi(), cov_wjet1.M() );
          //test_p2.SetPtEtaPhiM( cov_wjet2.Pt(), cov_wjet2.Eta(), cov_wjet2.Phi(), cov_wjet2.M() );
          //test_m = test_p1 + test_p2;
          //printf("[check] test_p1    = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f  ) \n", test_p1.Px(), test_p1.Py(), test_p1.Pz(), test_p1.E(), test_p1.M() );
          //printf("[check] test_p2    = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f  ) \n", test_p2.Px(), test_p2.Py(), test_p2.Pz(), test_p2.E(), test_p2.M() );
          //printf("[check] test_m     = (%7.2f, %7.2f, %7.2f, %7.2f, %7.2f  ) \n", test_m.Px(), test_m.Py(), test_m.Pz(), test_m.E(), test_m.M() );

          if(has_resonable_reco) printf("has_resonable_reco = true!"); else printf("has_resonable_reco = false!");

          //printf("[check] diphoton.Pt()         = %.2f\n", diphoton.Pt()  );
          //printf("[check] diphoton.Eta()        = %.2f\n", diphoton.Eta() );
          //printf("[check] diphoton.Phi()        = %.2f\n", diphoton.Phi() );
          //printf("[check] diphoton.M()          = %.2f\n", diphoton.M()   );

          printf("[check] btag_scrores = ");
          for(int i=0; i<btag_scores.size(); ++i)
              printf("%.2f ", btag_scores[i]);
          printf("\n\n\n");
      }

      jet1_ptOverM_ = (njets_ >= 1 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[0].Pt() / cov_top.M()  : -999;
      jet2_ptOverM_ = (njets_ >= 2 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[1].Pt() / cov_top.M()  : -999; 
      jet3_ptOverM_ = (njets_ >= 3 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[2].Pt() / cov_top.M()  : -999;
      jet4_ptOverM_ = (njets_ >= 4 && (has_resonable_reco && pass_eta_criteria_on_wjets)) ? jets[3].Pt() / cov_top.M()  : -999;
      //----------------------------------------------------------------------------------------------------//

      
      rand_ = rndm.Rndm(); // index for training and validation
      super_rand_ = -1; //rand_map->retrieve_rand(analyzer.event(), analyzer.run(), analyzer.lumi());
      mass_ = diphoton.M();
      lead_sigmaEtoE_ = dipho_lead_sigmaEoE();
      sublead_sigmaEtoE_ = dipho_sublead_sigmaEoE();

      // ***DNN Business{{{
      top_candidates_ = {0}; //calculate_top_candidates(diphoton, jets, btag_scores, max1_btag_);

      // Do this a dumb hacky way because it is easier to deal with down the line in DNN/BDT prep+training
      top_candidates_1_ = top_candidates_[0] > 0 ? log(top_candidates_[0]) : -9;
      top_candidates_2_ = top_candidates_[1] > 0 ? log(top_candidates_[1]) : -9;
      top_candidates_3_ = top_candidates_[2] > 0 ? log(top_candidates_[2]) : -9;
      top_candidates_4_ = top_candidates_[3] > 0 ? log(top_candidates_[3]) : -9;
      top_candidates_5_ = top_candidates_[4] > 0 ? log(top_candidates_[4]) : -9;
      top_candidates_6_ = top_candidates_[5] > 0 ? log(top_candidates_[5]) : -9;
      top_candidates_7_ = top_candidates_[6] > 0 ? log(top_candidates_[6]) : -9;
      top_candidates_8_ = top_candidates_[7] > 0 ? log(top_candidates_[7]) : -9;
      top_candidates_9_ = top_candidates_[8] > 0 ? log(top_candidates_[8]) : -9;
      top_candidates_10_ = top_candidates_[9] > 0 ? log(top_candidates_[9]) : -9;
      top_candidates_11_ = top_candidates_[10] > 0 ? log(top_candidates_[10]) : -9;
      top_candidates_12_ = top_candidates_[11] > 0 ? log(top_candidates_[11]) : -9;
      //}}}

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
    }// end of event loop

    if(debug) printf("[report] number of helicity nan values = %d\n", counter);

    delete tree;
    file.Close();
  }// end of while loop

  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

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
}
