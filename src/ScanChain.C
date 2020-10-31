#include "ScanChain.h"

int ScanChain(TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  TFile *output_file = new TFile("test.root", "RECREATE");
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
  TH1F *h_num_jets = new TH1F("h_num_jets", ";Jet multiplicity;Entries", 10, 0, 10);
  TH1F *h_mass_diphoton = new TH1F("h_mass_diphoton", ";Diphoton invariant mass [GeV/c^{2}];Entries", 40, 100, 180);
  TH1F *h_mass_wboson = new TH1F("h_mass_wboson", ";W boson invariant mass [GeV/c^{2}];Entries", 40, 40, 120);
  TH1F *h_mass_top = new TH1F("h_mass_top", ";Top invariant mass [GeV/c^{2}];Entries", 40, 100, 300);
  TH1F *h_mass_tprime = new TH1F("h_mass_tprime", ";Tprime invariant mass [GeV/c^{2}];Entries", 40, 200, 1000);

  h_num_jets      -> SetLineWidth(2);
  h_mass_diphoton -> SetLineWidth(2);
  h_mass_wboson   -> SetLineWidth(2);
  h_mass_top      -> SetLineWidth(2);
  h_mass_tprime   -> SetLineWidth(2);
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
      vector<TLorentzVector> jets  = make_jets(btag_scores);
      vector< std::pair<int, double> > btag_scores_sorted = sortVector(btag_scores);

      TLorentzVector bjet = jets[btag_scores_sorted[0].first];
      TLorentzVector wjet1 = jets[btag_scores_sorted[1].first];
      TLorentzVector wjet2 = jets[btag_scores_sorted[2].first];

      for(int i=0; i<3; ++i)
          printf("(%d) idx = %d, btag_scores = %.2f\n", i, btag_scores_sorted[i].first, btag_scores_sorted[i].second);
      printf("\n");

      TLorentzVector wboson = wjet1 + wjet2;
      TLorentzVector top = bjet + wboson;
      TLorentzVector diphoton;
      diphoton.SetPtEtaPhiE(dipho_pt(), dipho_eta(), dipho_phi(), dipho_e());
      
      TLorentzVector tprime = top + diphoton;

      h_num_jets->Fill(n_jets());
      h_mass_diphoton->Fill(CMS_hgg_mass());
      h_mass_wboson->Fill(wboson.M());
      h_mass_top->Fill(top.M());
      h_mass_tprime->Fill(tprime.M());

      //vProcess[processId]->fill_histogram("h" + syst_ext + "Mass", mass(), evt_weight, vId);   
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
