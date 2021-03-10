#include "ScanChain.h"
#include "chi2_helper.h"
#include "truth_matching.h"
#include "sorting.h"

int ScanChain_tprimetHHadronic_signal(TChain* chain, TString name_output_file, TString mYear, TString mass_str, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  printf("Hello World!\n");
  name_output_file = name_output_file.ReplaceAll("hist_", "myhist_");
  //name_output_file = name_output_file.ReplaceAll("hist_", "testOnly_");
  TFile *output_file = new TFile(name_output_file, "RECREATE");
  TString currentFileTitle = name_output_file;
  TString json_file = "json/covMatrix_Era2017_M1000.json";

  TString tag = "Hadronic";
  vector<Process*> vProcess = generate_processes(output_file);
  add_variables(vProcess, tag);

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

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    // Get File Content
    TFile file(currentFile->GetTitle());
    TTree *tree = (TTree*)file.Get("tagsDumper/trees/tHq_13TeV_THQHadronicTag");

    if (fast) TTreeCache::SetLearnEntries(10);
    if (fast) tree->SetCacheSize(128*1024*1024);
    analyzer.Init(tree);

    // Loop over Events in current file
    if (nEventsTotal >= nEventsChain) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event)
    {
      //if( (event+1) % 100 == 0) printf("ievent = %d / %d\n", event, nEventsTree);
      bool debug = false;
      bool debug_deeper = false;
      
      // Get Event Content
      if (nEventsTotal >= nEventsChain) continue;
      if (fast) tree->LoadTree(event);
      analyzer.GetEntry(event);
      ++nEventsTotal;

      // Progress
      tprimetHHadronic::progress( nEventsTotal, nEventsChain );

      float evt_weight = weight();
      int genLeptonId = 0; // isData ? -1 : categorize_leptons(nGoodEls(), nGoodMus()); // none of reco lepton exists
      int genPhotonId = 2; // isData ? -1 : categorize_photons(leadGenMatch(), subleadGenMatch()); // no effect for signal samples
      int genPhotonDetailId = 5; // isData ? -1 : categorize_photons_detail(lead_photon_type(), sublead_photon_type()); // assume prompt-prompt
      int photonLocationId = categorize_photon_locations(dipho_leadEta(), dipho_subleadEta());
      int mvaCategoryId = 1; // mva_value < -0.8 ? 0 : 1; // assume signal is 1
      int yearId = mYear == "2016" ? 0 : (mYear == "2017" ? 1 : (mYear == "2018" ? 2 : -1));
      int processId = categorize_process(currentFileTitle, genPhotonId);
      vector<int> vId = {genLeptonId, genPhotonId, genPhotonDetailId, photonLocationId, mvaCategoryId, -1, yearId};

      // Jets
      vector<double> btag_scores;
      vector<TLorentzVector> jets = make_jets(btag_scores);
      vector< std::pair<int, double> > btag_scores_sorted = sortVectorGreater(btag_scores);
      if(jets.size() < 3) continue;

      // Di-Photon
      TLorentzVector diphoton;
      diphoton.SetPtEtaPhiE(dipho_pt(), dipho_eta(), dipho_phi(), dipho_e());
      TLorentzVector lead_photon;
      lead_photon.SetPtEtaPhiE(dipho_leadPt(), dipho_leadEta(), dipho_leadPhi(), dipho_leadEt());
      TLorentzVector sublead_photon;
      sublead_photon.SetPtEtaPhiE(dipho_subleadPt(), dipho_subleadEta(), dipho_subleadPhi(), dipho_subleadEt());
      TLorentzVector diphoton_v2 = lead_photon + sublead_photon;
      
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

  
      //------------------------------ Fill histograms ------------------------------//
      TString syst_ext = "";
      vProcess[processId]->fill_histogram("h" + syst_ext + "Mass", diphoton.M(), evt_weight, vId);   
      vProcess[processId]->fill_histogram("h" + syst_ext + "PtHiggs", diphoton.Pt(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "DiphotonPtOverMass", diphoton.Pt() / diphoton.M(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonDeltaR", lead_photon.DeltaR(sublead_photon), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "Rapidity", diphoton.Rapidity(), evt_weight, vId);

      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_wboson_cov"   , mass_wboson        , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_top_cov"      , mass_top           , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_tprime_cov"   , mass_tprime        , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "mass_tprime_tilde" , mass_tprime_tilde  , evt_weight , vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "cov_chi2_value"    , min_chi2_value_2x2 , evt_weight , vId);

      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPt", dipho_leadPt(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadEta", dipho_leadEta(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPhi", dipho_leadPhi(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadIDMVA", dipho_leadIDMVA(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonLeadPToM", dipho_lead_ptoM(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPt", dipho_subleadPt(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadEta", dipho_subleadEta(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPhi", dipho_subleadPhi(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadIDMVA", dipho_subleadIDMVA(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "PhotonSubleadPToM", dipho_sublead_ptoM(), evt_weight, vId);

      vProcess[processId]->fill_histogram("h" + syst_ext + "NJets", n_jets(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "NbLoose", n_L_bjets(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "NbMedium", n_M_bjets(), evt_weight, vId);
      vProcess[processId]->fill_histogram("h" + syst_ext + "NbTight", n_T_bjets(), evt_weight, vId); 

      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet1pT", jet1_pt(), evt_weight, vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet2pT", jet2_pt(), evt_weight, vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet3pT", jet3_pt(), evt_weight, vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet4pT", jet4_pt(), evt_weight, vId);
      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet1Eta", jet1_eta(), evt_weight, vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet2Eta", jet2_eta(), evt_weight, vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet3Eta", jet3_eta(), evt_weight, vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet4Eta", jet4_eta(), evt_weight, vId);
      if (jet1_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet1BTag", jet1_discr(), evt_weight, vId);
      if (jet2_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet2BTag", jet2_discr(), evt_weight, vId);
      if (jet3_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet3BTag", jet3_discr(), evt_weight, vId);
      if (jet4_pt() >= 0) vProcess[processId]->fill_histogram("h" + syst_ext + "Jet4BTag", jet4_discr(), evt_weight, vId);

    } // end of event loop

    // Clean Up
    delete tree;
    file.Close();
  }
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
  cout << "------------------------------" << endl;
  cout << "CPU  Time: " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time: " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}
