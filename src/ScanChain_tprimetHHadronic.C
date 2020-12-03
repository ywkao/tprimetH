#include "ScanChain.h"
#include "chi2_helper.h"

int ScanChain_tprimetHHadronic(TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  TFile *output_file = new TFile("plots/test.root", "RECREATE");
  //TFile* f1 = new TFile(tag + "_" + ext + "_histograms" + year + idx + ".root", "RECREATE");

  float n_lep;
  float n_jet;
  float mass_diphoton;
  float mass_top;

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  TH1F *h_num_jets         = new TH1F("h_num_jets", ";Jet multiplicity;Entries", 16, 0, 16);
  TH1F *h_mass_diphoton    = new TH1F("h_mass_diphoton", ";Diphoton invariant mass [GeV/c^{2}];Entries", 40, 100, 180);
  TH1F *h_mass_diphoton_v2 = new TH1F("h_mass_diphoton_v2", ";Diphoton_v2 invariant mass [GeV/c^{2}];Entries", 40, 100, 180);
  TH1F *h_mass_wboson      = new TH1F("h_mass_wboson", ";W boson invariant mass [GeV/c^{2}];Entries", 40, 40, 120);
  TH1F *h_mass_top         = new TH1F("h_mass_top", ";Top invariant mass [GeV/c^{2}];Entries", 40, 100, 300);
  TH1F *h_mass_tprime      = new TH1F("h_mass_tprime", ";Tprime invariant mass [GeV/c^{2}];Entries", 40, 200, 1500);

  TH1F *h_mass_tm_wboson      = new TH1F("h_mass_tm_wboson", ";MC-truth-matched W boson invariant mass [GeV/c^{2}];Entries", 40, 40, 120);
  TH1F *h_mass_tm_top         = new TH1F("h_mass_tm_top", ";MC-truth-matched Top invariant mass [GeV/c^{2}];Entries", 40, 100, 300);

  TH1F *h_mass_gen_wboson  = new TH1F("h_mass_gen_wboson", ";gen-leveled W boson invariant mass [GeV/c^{2}];Entries", 40, 40, 120);
  TH1F *h_mass_gen_top     = new TH1F("h_mass_gen_top", ";gen-leveled top invariant mass [GeV/c^{2}];Entries", 40, 100, 300);

  TH1F *h_deltaR_wjets     = new TH1F("h_deltaR_wjets", ";Open angle (wjet1, wjet2);Entries", 40, 0., 6.);
  TH1F *h_deltaR_photons   = new TH1F("h_deltaR_photons", ";Open angle (leading photon, sublading photon);Entries", 40, 0., 6.);
  TH1F *h_deltaR_bW        = new TH1F("h_deltaR_bW", ";Open angle (bjet, W candidate);Entries", 40, 0., 6.);
  TH1F *h_deltaR_tH        = new TH1F("h_deltaR_tH", ";Open angle (top candidate, diphoton);Entries", 40, 0., 6.);

  TH1F *h_helicity_tprime  = new TH1F("h_helicity_tprime", ";helicity (top, diphoton);Entries", 40, 0., 1.);
  TH1F *h_helicity_top     = new TH1F("h_helicity_top", ";helicity (bjet, W candidate);Entries", 40, 0., 1.);
  TH1F *h_helicity_higgs   = new TH1F("h_helicity_higgs", ";helicity (leading photon, sub-leading photon);Entries", 40, 0., 1.);

  TH1F *h_chi2_value       = new TH1F("h_chi2_value", ";Xtt0;Entries", 40, 0, 120);

  TH1F *h_genIndices       = new TH1F("h_genIndices", ";Indices;Entries", 10, -1, 9);
  TH1F *h_genPdgId         = new TH1F("h_genPdgId", ";PdgId;Entries", 14, -7, 7);
  TH1F *h_genDeltaR        = new TH1F("h_genDeltaR", ";DeltaR;Entries", 40, 0, 0.4);

  //h_mass_diphoton->SetDirectory(rootdir);

  //vector<Process*> vProcess = generate_processes(f1);
  //add_variables(vProcess, tag);

  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if (nEvents >= 0) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  int counter_has_reasonable_gen_match = 0;
  int counter_has_reasonable_match = 0;
  int counter_more_than_nine_jets = 0;
  int counter_total_selected_events = 0;
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
    for (unsigned int event = 0; event < nEventsTree; ++event) {

      // Get Event Content
      if (nEventsTotal >= nEventsChain) continue;
      if (fast) tree->LoadTree(event);
      analyzer.GetEntry(event);
      ++nEventsTotal;

      // Progress
      tprimetHHadronic::progress( nEventsTotal, nEventsChain );

      // Analysis Code
      vector<double> btag_scores;
      vector<TLorentzVector> jets = make_jets(btag_scores);
      vector< std::pair<int, double> > btag_scores_sorted = sortVectorGreater(btag_scores);
      if(jets.size() < 3) continue;

      // Di-Photon
      TLorentzVector diphoton;
      diphoton.SetPtEtaPhiE(dipho_pt(), dipho_eta(), dipho_phi(), dipho_e());
      TLorentzVector leading_photon;
      leading_photon.SetPtEtaPhiE(dipho_leadPt(), dipho_leadEta(), dipho_leadPhi(), dipho_leadEt());
      TLorentzVector subleading_photon;
      subleading_photon.SetPtEtaPhiE(dipho_subleadPt(), dipho_subleadEta(), dipho_subleadPhi(), dipho_subleadEt());
      TLorentzVector diphoton_v2 = leading_photon + subleading_photon;
      
      //--------------- MC truth information ---------------//
      vector<int> pdgIds;
      vector<TLorentzVector> partons = make_partons(pdgIds);
      TLorentzVector bquark, wquark1, wquark2;
      printf("gen-indices  : ");
      bool has_reasonable_gen_matching = gen_matching(partons, jets, pdgIds, bquark, wquark1, wquark2);
      if(has_reasonable_gen_matching)
      {
          TLorentzVector gen_wboson = wquark1 + wquark2;
          TLorentzVector gen_top = bquark + gen_wboson;
          h_mass_gen_wboson  -> Fill(gen_wboson.M());
          h_mass_gen_top     -> Fill(gen_top.M());
          counter_has_reasonable_gen_match += 1;
      }

      //--------------- Reco. information ---------------//
      // MC-truth matching
      printf("truth-matched: ");
      int truthMatched_index_bjet;
      vector<int> truthMatched_indices_wjets;
      bool has_reasonable_match = get_gen_matched_jets(truthMatched_index_bjet, truthMatched_indices_wjets);

      if(has_reasonable_match)
      {
          TLorentzVector truthMatched_bjet   = jets[truthMatched_index_bjet];
          TLorentzVector truthMatched_wjet1  = jets[truthMatched_indices_wjets[0]];
          TLorentzVector truthMatched_wjet2  = jets[truthMatched_indices_wjets[1]];
          TLorentzVector truthMatched_wboson = truthMatched_wjet1 + truthMatched_wjet2;
          TLorentzVector truthMatched_top    = truthMatched_bjet + truthMatched_wboson;
          TLorentzVector truthMatched_tprime = truthMatched_top + diphoton;

          h_mass_tm_wboson      -> Fill(truthMatched_wboson.M());
          h_mass_tm_top         -> Fill(truthMatched_top.M());

          counter_has_reasonable_match += 1;
      }

      double min_chi2_value = 99999.;

      // Minimum chi-2 method
      // the bjet is determined according to the DeepCSV algorithm; while the wjets are chosen from the remaining jets 
      int index_bjet = btag_scores_sorted[0].first;
      vector<int> indices_wjets = get_the_best_wjets_candidate(jets, index_bjet, min_chi2_value);

      printf("minimum chi-2: ");
      printf("[%d, %d, %d]\n", index_bjet, indices_wjets[0], indices_wjets[1]);

      TLorentzVector bjet = jets[index_bjet];
      TLorentzVector wjet1 = jets[indices_wjets[0]];
      TLorentzVector wjet2 = jets[indices_wjets[1]];

      TLorentzVector wboson = wjet1 + wjet2;
      TLorentzVector top = bjet + wboson;
      TLorentzVector tprime = top + diphoton;

      h_num_jets         -> Fill(jets.size());
      h_mass_diphoton    -> Fill(CMS_hgg_mass());
      h_mass_diphoton_v2 -> Fill(diphoton_v2.M());
      h_mass_wboson      -> Fill(wboson.M());
      h_mass_top         -> Fill(top.M());
      h_mass_tprime      -> Fill(tprime.M());

      h_deltaR_wjets     -> Fill(wjet1.DeltaR(wjet2));
      h_deltaR_photons   -> Fill(leading_photon.DeltaR(subleading_photon));
      h_deltaR_bW        -> Fill(bjet.DeltaR(wboson));
      h_deltaR_tH        -> Fill(top.DeltaR(diphoton));

      h_helicity_tprime  -> Fill( helicity(top, diphoton) );
      h_helicity_top     -> Fill( helicity(bjet, wboson) );
      h_helicity_higgs   -> Fill( helicity(leading_photon, subleading_photon) );

      h_chi2_value       -> Fill(min_chi2_value);
      h_genIndices       -> Fill(genMatched_jet0_index());
      h_genIndices       -> Fill(genMatched_jet1_index());
      h_genIndices       -> Fill(genMatched_jet2_index());
      h_genPdgId         -> Fill(genMatched_jet0_pdgId());
      h_genPdgId         -> Fill(genMatched_jet1_pdgId());
      h_genPdgId         -> Fill(genMatched_jet2_pdgId());
      h_genDeltaR        -> Fill(genMatched_jet0_deltaR());
      h_genDeltaR        -> Fill(genMatched_jet1_deltaR());
      h_genDeltaR        -> Fill(genMatched_jet2_deltaR());
      //vProcess[processId]->fill_histogram("h" + syst_ext + "Mass", mass(), evt_weight, vId);   


      //--------------- Other info ---------------//
      //for(int i=0; i<jets.size(); ++i)
      //    printf("(%d) idx = %d, btag_scores = %.2f\n", i, btag_scores_sorted[i].first, btag_scores_sorted[i].second);
      printf("\n");

      if(jets.size() > 9) counter_more_than_nine_jets += 1;
      counter_total_selected_events += 1;
    } // end of event loop
  
    // Clean Up
    delete tree;
    file.Close();
  }
  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  print_counter_percentage("Number of jets more than 9", counter_more_than_nine_jets, counter_total_selected_events);
  print_counter_percentage("After the cut of resonable match", counter_has_reasonable_match, counter_total_selected_events);
  print_counter_percentage("Percentage of resonable gen match", counter_has_reasonable_gen_match, counter_total_selected_events);

  // Make plots
  TCanvas *c1 = new TCanvas("c1", "", 800, 600);

  makePlot(c1 , h_num_jets         , "plots/h_num_jets.pdf"         );
  makePlot(c1 , h_mass_diphoton    , "plots/h_mass_diphoton.pdf"    );
  makePlot(c1 , h_mass_diphoton_v2 , "plots/h_mass_diphoton_v2.pdf" );
  makePlot(c1 , h_mass_wboson      , "plots/h_mass_wboson.pdf"      );
  makePlot(c1 , h_mass_top         , "plots/h_mass_top.pdf"         );
  makePlot(c1 , h_mass_gen_wboson  , "plots/h_mass_gen_wboson.pdf"  );
  makePlot(c1 , h_mass_gen_top     , "plots/h_mass_gen_top.pdf"     );
  makePlot(c1 , h_mass_tm_wboson   , "plots/h_mass_tm_wboson.pdf"   );
  makePlot(c1 , h_mass_tm_top      , "plots/h_mass_tm_top.pdf"      );
  makePlot(c1 , h_mass_tprime      , "plots/h_mass_tprime.pdf"      );
  makePlot(c1 , h_deltaR_wjets     , "plots/h_deltaR_wjets.pdf"     );
  makePlot(c1 , h_deltaR_photons   , "plots/h_deltaR_photons.pdf"   );
  makePlot(c1 , h_deltaR_bW        , "plots/h_deltaR_bW.pdf"        );
  makePlot(c1 , h_deltaR_tH        , "plots/h_deltaR_tH.pdf"        );
  makePlot(c1 , h_helicity_tprime  , "plots/h_helicity_tprime.pdf"  );
  makePlot(c1 , h_helicity_top     , "plots/h_helicity_top.pdf"     );
  makePlot(c1 , h_helicity_higgs   , "plots/h_helicity_higgs.pdf"   );
  makePlot(c1 , h_chi2_value       , "plots/h_chi2_value.pdf"       );
  makePlot(c1 , h_genIndices       , "plots/h_genIndices.pdf"       );
  makePlot(c1 , h_genPdgId         , "plots/h_genPdgId.pdf"         );
  makePlot(c1 , h_genDeltaR        , "plots/h_genDeltaR.pdf"        );

  makePlot_twoHists(c1 , h_mass_wboson , h_mass_gen_wboson , "plots/h_genReco_mass_wboson.pdf" );
  makePlot_twoHists(c1 , h_mass_top    , h_mass_gen_top    , "plots/h_genReco_mass_top.pdf"    );
  makePlot_twoHists(c1 , h_mass_wboson , h_mass_tm_wboson  , "plots/h_tmReco_mass_wboson.pdf"  );
  makePlot_twoHists(c1 , h_mass_top    , h_mass_tm_top     , "plots/h_tmReco_mass_top.pdf"     );

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
