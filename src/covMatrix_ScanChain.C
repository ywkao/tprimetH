#include "ScanChain.h"
#include "truth_matching.h"
#include "sorting.h"
#include <fstream>

int covMatrix_ScanChain(TChain* chain, TString name_output_file, TString year, TString mass_tag,  bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  // Output File
  TFile *output_file = new TFile(name_output_file, "RECREATE");

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  TH1F *h_num_bquarks       = new TH1F("h_num_bquarks"       , ";b-quark multiplicity;Entries"                                , 10 , 0   , 10   );
  TH1F *h_num_wquarks       = new TH1F("h_num_wquarks"       , ";w-quark multiplicity;Entries"                                , 10 , 0   , 10   );
  TH1F *h_gen_pdgIds        = new TH1F("h_gen_pdgIds"        , ";gen pdgIds;Entries"                                          , 60 , -30 , 30   );
  TH1F *h_mom_pdgIds        = new TH1F("h_mom_pdgIds"        , ";mom pdgIds;Entries"                                          , 60 , -30 , 30   );

  TH1F *h_num_jets          = new TH1F("h_num_jets"          , ";Jet multiplicity;Entries"                                    , 16 , 0   , 16   );
  TH1F *h_num_gen_particles = new TH1F("h_num_gen_particles" , ";Number of gen-level particles;Entries"                       , 16 , 0   , 16   );
  TH1F *h_mass_diphoton     = new TH1F("h_mass_diphoton"     , ";Diphoton invariant mass [GeV/c^{2}];Entries"                 , 40 , 100 , 180  );

  TH1F *h_mass_tm_wboson    = new TH1F("h_mass_tm_wboson"    , ";MC-truth-matched W boson invariant mass [GeV/c^{2}];Entries" , 40 , 0   , 200  );
  TH1F *h_mass_tm_top       = new TH1F("h_mass_tm_top"       , ";MC-truth-matched Top invariant mass [GeV/c^{2}];Entries"     , 40 , 100 , 300  );
  TH1F *h_mass_tm_tprime    = new TH1F("h_mass_tm_tprime"    , ";MC-truth-matched Tprime invariant mass [GeV/c^{2}];Entries"  , 36 , 200 , 2000 );
  TH1F *h_mass_gen_wboson   = new TH1F("h_mass_gen_wboson"   , ";gen-leveled W boson invariant mass [GeV/c^{2}];Entries"      , 40 , 0   , 200  );
  TH1F *h_mass_gen_top      = new TH1F("h_mass_gen_top"      , ";gen-leveled top invariant mass [GeV/c^{2}];Entries"          , 40 , 100 , 300  );

  TH1F *h_deltaR_partons    = new TH1F("h_deltaR_partons"    , "; Open angle (parton, matched jet)"                           , 40 , 0.  , 4.   );
  TH1F *h_ptRatio_partons   = new TH1F("h_ptRatio_partons"   , "; abs(p_{T}^{reco} - p_{T}^{gen}) / p_{T}^{gen};Entries"      , 40 , 0.  , 4.   );
  TH1F *h_deltaR_wjets      = new TH1F("h_deltaR_wjets"      , ";Open angle (wjet1, wjet2);Entries"                           , 40 , 0.  , 6.   );

  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if (nEvents >= 0) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  double Nevents_pass_selection           = 0;
  int counter_has_reasonable_gen_match    = 0;
  int counter_has_reasonable_match        = 0;
  int counter_before_gen_criteria         = 0;
  int counter_after_gen_criteria          = 0;
  int counter_pass_gen_deltaR_criterion   = 0;
  int counter_pass_gen_pt_ratio_criterion = 0;
  int counter_total_selected_events       = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile file(currentFile->GetTitle());
    TTree *tree = (TTree*)file.Get("tagsDumper/trees/tHq_13TeV_THQHadronicTag");

    if (fast) TTreeCache::SetLearnEntries(10);
    if (fast) tree->SetCacheSize(128*1024*1024);
    analyzer.Init(tree);

    // Loop over Events in current file
    if (nEventsTotal >= nEventsChain) continue;
    double mean[3] = {0};
    double covarianceMatrix[3][3] = {0};
    unsigned int nEventsTree = tree->GetEntriesFast();

    //================================================= Evaluate MeanValues ===================================================//
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
      
      //--------------- MC truth information ---------------//
      vector<float> gen_pdgIds, gen_status;
      vector<float> mom_pdgIds, mom_status;
      vector<TLorentzVector> gen_particles = make_gen_particles(gen_pdgIds, gen_status);
      vector<TLorentzVector> moms = make_mom_particles(mom_pdgIds, mom_status);

      TLorentzVector bquark, wquark1, wquark2;
      
      int counter_bquark = 0;
      int counter_wquark = 0;
      int counter_gen_particles = 0;
      for( unsigned int i = 0; i < gen_particles.size(); ++i )
      {
          bool is_bquark = gen_status[i] == 23 && abs(gen_pdgIds[i]) == 5 && abs(mom_pdgIds[i]) == 6;
          bool is_wquark = gen_status[i] == 23 && abs(gen_pdgIds[i]) <  6 && abs(mom_pdgIds[i]) == 24;

          if(is_bquark) bquark = gen_particles[i];
          if(is_wquark && counter_wquark == 1){ wquark2 = gen_particles[i]; counter_wquark += 1; }
          if(is_wquark && counter_wquark == 0){ wquark1 = gen_particles[i]; counter_wquark += 1; }

          //printf("gen status = %.0f, gen pdgId = %8.0f, mom pdgId = %.0f\n", gen_status[i], gen_pdgIds[i], mom_pdgIds[i]);
          //printf("gen status = %.0f, pdgId = %8.0f, pt = %.2f\n", gen_status[i], gen_pdgIds[i], gen_particles[i].Pt());

          if( abs(gen_pdgIds[i]) == 5 ) counter_bquark += 1;
          counter_gen_particles += 1;
          
          h_gen_pdgIds->Fill(gen_pdgIds[i]);
          h_mom_pdgIds->Fill(mom_pdgIds[i]);
      }
      //printf("\n");
      h_num_bquarks->Fill(counter_bquark);
      h_num_wquarks->Fill(counter_wquark);
      h_num_gen_particles->Fill(counter_gen_particles);

      bool has_reasonable_gen_matching = counter_bquark >= 1 && counter_wquark >= 2;
      if(has_reasonable_gen_matching)
      {
          TLorentzVector gen_wboson = wquark1 + wquark2;
          TLorentzVector gen_top = bquark + gen_wboson;
          h_mass_gen_wboson -> Fill(gen_wboson.M());
          h_mass_gen_top    -> Fill(gen_top.M());
          counter_has_reasonable_gen_match += 1;
      }

      //--------------- Reco. information ---------------//

      // MC-truth matching
      truth_matching_helper tr(gen_particles, jets, gen_pdgIds, gen_status, mom_pdgIds, h_deltaR_partons, h_ptRatio_partons);
      bool MC_truth_matching_is_applicable = tr.perform_mc_truth_matching(); // counter_bquark_matching >= 1 && counter_wquark_matching >= 2;
      if(MC_truth_matching_is_applicable)
      {
          TLorentzVector truthMatched_bjet;
          TLorentzVector truthMatched_wjet1;
          TLorentzVector truthMatched_wjet2;

          int indices_bjj[3] = {-1};
          int counter_wjet = 0;
          for( unsigned int i = 0; i < tr.get_register_jetIndex().size(); ++i )
          {
              bool is_bjet = abs(tr.get_register_pdgId()[i]) == 5 && abs(tr.get_register_mompdgId()[i]) == 6;
              bool is_wjet = abs(tr.get_register_pdgId()[i]) <  5 && abs(tr.get_register_mompdgId()[i]) == 24;

              if(is_bjet){ truthMatched_bjet = jets[tr.get_register_jetIndex()[i]]; indices_bjj[0] = i; }
              if(is_wjet && counter_wjet == 1){ truthMatched_wjet2 = jets[tr.get_register_jetIndex()[i]]; counter_wjet += 1; indices_bjj[2] = i; }
              if(is_wjet && counter_wjet == 0){ truthMatched_wjet1 = jets[tr.get_register_jetIndex()[i]]; counter_wjet += 1; indices_bjj[1] = i; }

              //printf("(%d) pdgId = %.0f, mompdgId = %.0f\n", i, tr.get_register_pdgId()[i], tr.get_register_mompdgId()[i]);
          }
          //printf("\n");

          bool pass_eta_codition_on_wjets = truthMatched_wjet1.Eta() < 3. && truthMatched_wjet2.Eta() < 3.;
          if(pass_eta_codition_on_wjets)
          {
              TLorentzVector truthMatched_wboson = truthMatched_wjet1 + truthMatched_wjet2;
              TLorentzVector truthMatched_top    = truthMatched_bjet + truthMatched_wboson;
              TLorentzVector truthMatched_tprime = truthMatched_top + diphoton;

              h_deltaR_wjets   -> Fill(truthMatched_wjet1.DeltaR(truthMatched_wjet2));
              h_mass_tm_wboson -> Fill(truthMatched_wboson.M());
              h_mass_tm_top    -> Fill(truthMatched_top.M());
              h_mass_tm_tprime -> Fill(truthMatched_tprime.M());

              counter_has_reasonable_match += 1;

              //==================================================//
              //-------------   Covariant Matrix   ---------------//
              //==================================================//
              mean[0] += truthMatched_wboson.M();
              mean[1] += truthMatched_top.M();
              mean[2] += truthMatched_tprime.M();

              Nevents_pass_selection += 1.;
          }
      }

      //--------------- Other info ---------------//
      h_num_jets         -> Fill(jets.size());
      h_mass_diphoton    -> Fill(CMS_hgg_mass());
      counter_total_selected_events += 1;
    } // end of event loop

    mean[0] /= Nevents_pass_selection;
    mean[1] /= Nevents_pass_selection;
    mean[2] /= Nevents_pass_selection;

    //================================================= Evaluate CovMatrix ===================================================//
    nEventsTotal = 0; //NOTE: temporarily
    Nevents_pass_selection = 0.;
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
      
      //--------------- MC truth information ---------------//
      vector<float> gen_pdgIds, gen_status;
      vector<float> mom_pdgIds, mom_status;
      vector<TLorentzVector> gen_particles = make_gen_particles(gen_pdgIds, gen_status);
      vector<TLorentzVector> moms = make_mom_particles(mom_pdgIds, mom_status);

      //--------------- Reco. information ---------------//

      // MC-truth matching
      truth_matching_helper tr(gen_particles, jets, gen_pdgIds, gen_status, mom_pdgIds);
      bool MC_truth_matching_is_applicable = tr.perform_mc_truth_matching(); // counter_bquark_matching >= 1 && counter_wquark_matching >= 2;
      if(MC_truth_matching_is_applicable)
      {
          TLorentzVector truthMatched_bjet;
          TLorentzVector truthMatched_wjet1;
          TLorentzVector truthMatched_wjet2;

          int indices_bjj[3] = {-1};
          int counter_wjet = 0;
          for( unsigned int i = 0; i < tr.get_register_jetIndex().size(); ++i )
          {
              bool is_bjet = abs(tr.get_register_pdgId()[i]) == 5 && abs(tr.get_register_mompdgId()[i]) == 6;
              bool is_wjet = abs(tr.get_register_pdgId()[i]) <  5 && abs(tr.get_register_mompdgId()[i]) == 24;

              if(is_bjet){ truthMatched_bjet = jets[tr.get_register_jetIndex()[i]]; indices_bjj[0] = i; }
              if(is_wjet && counter_wjet == 1){ truthMatched_wjet2 = jets[tr.get_register_jetIndex()[i]]; counter_wjet += 1; indices_bjj[2] = i; }
              if(is_wjet && counter_wjet == 0){ truthMatched_wjet1 = jets[tr.get_register_jetIndex()[i]]; counter_wjet += 1; indices_bjj[1] = i; }
          }

          bool pass_eta_codition_on_wjets = truthMatched_wjet1.Eta() < 3. && truthMatched_wjet2.Eta() < 3.;
          if(pass_eta_codition_on_wjets)
          {
              TLorentzVector truthMatched_wboson = truthMatched_wjet1 + truthMatched_wjet2;
              TLorentzVector truthMatched_top    = truthMatched_bjet + truthMatched_wboson;
              TLorentzVector truthMatched_tprime = truthMatched_top + diphoton;

              //==================================================//
              //-------------   Covariant Matrix   ---------------//
              //==================================================//
              double element_0 = truthMatched_wboson.M() - mean[0];
              double element_1 = truthMatched_top.M()    - mean[1];
              double element_2 = truthMatched_tprime.M() - mean[2];
              covarianceMatrix[0][0] += element_0 * element_0;
              covarianceMatrix[0][1] += element_0 * element_1;
              covarianceMatrix[0][2] += element_0 * element_2;
              covarianceMatrix[1][0] += element_1 * element_0;
              covarianceMatrix[1][1] += element_1 * element_1;
              covarianceMatrix[1][2] += element_1 * element_2;
              covarianceMatrix[2][0] += element_2 * element_0;
              covarianceMatrix[2][1] += element_2 * element_1;
              covarianceMatrix[2][2] += element_2 * element_2;

              Nevents_pass_selection += 1.;
          }
      }
    } // end of event loop

    covarianceMatrix[0][0] /= Nevents_pass_selection;
    covarianceMatrix[0][1] /= Nevents_pass_selection;
    covarianceMatrix[0][2] /= Nevents_pass_selection;
    covarianceMatrix[1][0] /= Nevents_pass_selection;
    covarianceMatrix[1][1] /= Nevents_pass_selection;
    covarianceMatrix[1][2] /= Nevents_pass_selection;
    covarianceMatrix[2][0] /= Nevents_pass_selection;
    covarianceMatrix[2][1] /= Nevents_pass_selection;
    covarianceMatrix[2][2] /= Nevents_pass_selection;

    //================================================= Evaluate CovMatrix ===================================================//
    printf("h_mass_tm_wboson : %.2f, %.2f\n", h_mass_tm_wboson -> GetMean(), h_mass_tm_wboson -> GetStdDev());
    printf("h_mass_tm_top    : %.2f, %.2f\n", h_mass_tm_top    -> GetMean(), h_mass_tm_top    -> GetStdDev());
    printf("h_mass_tm_tprime : %.2f, %.2f\n", h_mass_tm_tprime -> GetMean(), h_mass_tm_tprime -> GetStdDev());

    printf("mean = %6.2f, sigma_prime_jj  = %6.2f\n", mean[0], sqrt(covarianceMatrix[0][0]));
    printf("mean = %6.2f, sigma_prime_bjj = %6.2f\n", mean[1], sqrt(covarianceMatrix[1][1]));
    printf("mean = %6.2f, sigma_prime_qgg = %6.2f\n", mean[2], sqrt(covarianceMatrix[2][2]));
    printf("---------------\n");
    printf("matrix(0,0) = %6.2f; matrix(0,1) = %6.2f;\n", covarianceMatrix[0][0], 0.);
    printf("matrix(1,0) = %6.2f; matrix(1,1) = %6.2f;\n", 0., covarianceMatrix[1][1]);
    printf("---------------\n");
    printf("matrix(0,0) = %6.2f; matrix(0,1) = %6.2f;\n", covarianceMatrix[0][0], covarianceMatrix[0][1]);
    printf("matrix(1,0) = %6.2f; matrix(1,1) = %6.2f;\n", covarianceMatrix[1][0], covarianceMatrix[1][1]);
    printf("---------------\n");
    printf("matrix(0,0) = %6.2f; matrix(0,1) = %6.2f; matrix(0,2) = %6.2f;\n", covarianceMatrix[0][0], covarianceMatrix[0][1], covarianceMatrix[0][2]);
    printf("matrix(1,0) = %6.2f; matrix(1,1) = %6.2f; matrix(1,2) = %6.2f;\n", covarianceMatrix[1][0], covarianceMatrix[1][1], covarianceMatrix[1][2]);
    printf("matrix(2,0) = %6.2f; matrix(2,1) = %6.2f; matrix(2,2) = %6.2f;\n", covarianceMatrix[2][0], covarianceMatrix[2][1], covarianceMatrix[2][2]);
    printf("\n");

    char* message = new char[1024];
    ofstream myfile;

    // output as a json file
    printf("%s", Form("json/covMatrix_Era%s_M%s.json", year.Data(), mass_tag.Data()) );
    myfile.open(Form("json/covMatrix_Era%s_M%s.json", year.Data(), mass_tag.Data()));
    myfile << "{\n";
    sprintf( message, Form("    \"mass_reco_w\" : %.2f,\n"     , mean[0]) ); myfile << message;
    sprintf( message, Form("    \"mass_reco_top\" : %.2f,\n"   , mean[1]) ); myfile << message;
    sprintf( message, Form("    \"mass_reco_tprime\" : %.2f,\n", mean[2]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_00\" : %.2f,\n", covarianceMatrix[0][0]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_01\" : %.2f,\n", covarianceMatrix[0][1]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_02\" : %.2f,\n", covarianceMatrix[0][2]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_10\" : %.2f,\n", covarianceMatrix[1][0]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_11\" : %.2f,\n", covarianceMatrix[1][1]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_12\" : %.2f,\n", covarianceMatrix[1][2]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_20\" : %.2f,\n", covarianceMatrix[2][0]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_21\" : %.2f,\n", covarianceMatrix[2][1]) ); myfile << message;
    sprintf( message, Form("    \"covMatrix_22\" : %.2f\n" , covarianceMatrix[2][2]) ); myfile << message;
    myfile << "}\n";
    myfile.close();

    // output as a txt file
    myfile.open(Form("dir_log/covMatrix_Era%s_M%s.txt", year.Data(), mass_tag.Data()));
    myfile << "//### Automatically generated by src/covMatrix_ScanChain.C ###//\n";
    sprintf( message, Form("//### Dataset: %s\n", name_output_file.Data()) ); myfile << message;
    sprintf( message, Form("    \"mass_reco_w\" : %.2f,\n"     , mean[0]) ); myfile << message;
    sprintf( message, Form("    \"mass_reco_top\" : %.2f,\n"   , mean[1]) ); myfile << message;
    sprintf( message, Form("    \"mass_reco_tprime\" : %.2f,\n", mean[2]) ); myfile << message;
    sprintf( message, Form("%6.2f, %6.2f, %6.2f\n", covarianceMatrix[0][0], covarianceMatrix[0][1], covarianceMatrix[0][2]) ); myfile << message;
    sprintf( message, Form("%6.2f, %6.2f, %6.2f\n", covarianceMatrix[1][0], covarianceMatrix[1][1], covarianceMatrix[1][2]) ); myfile << message;
    sprintf( message, Form("%6.2f, %6.2f, %6.2f\n", covarianceMatrix[2][0], covarianceMatrix[2][1], covarianceMatrix[2][2]) ); myfile << message;
    myfile.close();

    // Clean Up
    delete message;
    delete tree;
    file.Close();
  }
  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  print_counter_percentage("After the cut of resonable match"  , counter_has_reasonable_match        , counter_total_selected_events );
  print_counter_percentage("Percentage of resonable gen match" , counter_has_reasonable_gen_match    , counter_total_selected_events );
  print_counter_percentage("pass_gen_deltaR_criterion"         , counter_pass_gen_deltaR_criterion   , counter_before_gen_criteria   );
  print_counter_percentage("pass_gen_pt_ratio_criterion"       , counter_pass_gen_pt_ratio_criterion , counter_before_gen_criteria   );
  print_counter_percentage("after_gen_criteria"                , counter_after_gen_criteria          , counter_before_gen_criteria   );

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
