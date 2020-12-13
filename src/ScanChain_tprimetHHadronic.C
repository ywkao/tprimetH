#include "ScanChain.h"
#include "chi2_helper.h"

int ScanChain_tprimetHHadronic(TChain* chain, TString name_output_file, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  TFile *output_file = new TFile(name_output_file, "RECREATE");
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
  TH1F *h_num_bquarks       = new TH1F("h_num_bquarks"       , ";b-quark multiplicity;Entries"                                , 10 , 0   , 10   );
  TH1F *h_num_wquarks       = new TH1F("h_num_wquarks"       , ";w-quark multiplicity;Entries"                                , 10 , 0   , 10   );
  TH1F *h_gen_pdgIds        = new TH1F("h_gen_pdgIds"        , ";gen pdgIds;Entries"                                          , 60 , -30 , 30   );
  TH1F *h_mom_pdgIds        = new TH1F("h_mom_pdgIds"        , ";mom pdgIds;Entries"                                          , 60 , -30 , 30   );

  TH1F *h_num_jets          = new TH1F("h_num_jets"          , ";Jet multiplicity;Entries"                                    , 16 , 0   , 16   );
  TH1F *h_num_gen_particles = new TH1F("h_num_gen_particles" , ";Number of gen-level particles;Entries"                       , 16 , 0   , 16   );
  TH1F *h_mass_diphoton     = new TH1F("h_mass_diphoton"     , ";Diphoton invariant mass [GeV/c^{2}];Entries"                 , 40 , 100 , 180  );
  TH1F *h_mass_diphoton_v2  = new TH1F("h_mass_diphoton_v2"  , ";Diphoton_v2 invariant mass [GeV/c^{2}];Entries"              , 40 , 100 , 180  );

  TH1F *h_mass_tprime       = new TH1F("h_mass_tprime"       , ";Tprime invariant mass [GeV/c^{2}];Entries"                   , 36 , 200 , 2000 );
  TH1F *h_mass_tm_tprime       = new TH1F("h_mass_tm_tprime" , ";MC-truth-matched Tprime invariant mass [GeV/c^{2}];Entries"  , 36 , 200 , 2000 );

  TH1F *h_mass_top          = new TH1F("h_mass_top"          , ";Top invariant mass [GeV/c^{2}];Entries"                      , 40 , 100 , 300  );
  TH1F *h_mass_tm_top       = new TH1F("h_mass_tm_top"       , ";MC-truth-matched Top invariant mass [GeV/c^{2}];Entries"     , 40 , 100 , 300  );
  TH1F *h_mass_gen_top      = new TH1F("h_mass_gen_top"      , ";gen-leveled top invariant mass [GeV/c^{2}];Entries"          , 40 , 100 , 300  );

  TH1F *h_mass_wboson       = new TH1F("h_mass_wboson"       , ";W boson invariant mass [GeV/c^{2}];Entries"                  , 40 , 0   , 200  );
  TH1F *h_mass_tm_wboson    = new TH1F("h_mass_tm_wboson"    , ";MC-truth-matched W boson invariant mass [GeV/c^{2}];Entries" , 40 , 0   , 200  );
  TH1F *h_mass_gen_wboson   = new TH1F("h_mass_gen_wboson"   , ";gen-leveled W boson invariant mass [GeV/c^{2}];Entries"      , 40 , 0   , 200  );

  TH1F *h_deltaR_partons    = new TH1F("h_deltaR_partons"    , "; Open angle (parton, matched jet)"                           , 40 , 0.  , 4.   );
  TH1F *h_ptRatio_partons   = new TH1F("h_ptRatio_partons"   , "; (p_{T}^{reco} - p_{T}^{gen}) / p_{T}^{gen};Entries"         , 40 , 0.  , 4.   );
  TH1F *h_deltaR_wjets      = new TH1F("h_deltaR_wjets"      , ";Open angle (wjet1, wjet2);Entries"                           , 40 , 0.  , 6.   );

  TH1F *h_deltaR_photons    = new TH1F("h_deltaR_photons"    , ";Open angle (leading photon, sublading photon);Entries"       , 40 , 0.  , 6.   );
  TH1F *h_deltaR_bW         = new TH1F("h_deltaR_bW"         , ";Open angle (bjet, W candidate);Entries"                      , 40 , 0.  , 6.   );
  TH1F *h_deltaR_tH         = new TH1F("h_deltaR_tH"         , ";Open angle (top candidate, diphoton);Entries"                , 40 , 0.  , 6.   );
  TH1F *h_helicity_tprime   = new TH1F("h_helicity_tprime"   , ";helicity (top, diphoton);Entries"                            , 40 , 0.  , 1.   );
  TH1F *h_helicity_top      = new TH1F("h_helicity_top"      , ";helicity (bjet, W candidate);Entries"                        , 40 , 0.  , 1.   );
  TH1F *h_helicity_higgs    = new TH1F("h_helicity_higgs"    , ";helicity (leading photon, sub-leading photon);Entries"       , 40 , 0.  , 1.   );
  TH1F *h_genIndices        = new TH1F("h_genIndices"        , ";Indices;Entries"                                             , 10 , -1  , 9    );
  TH1F *h_genPdgId          = new TH1F("h_genPdgId"          , ";PdgId;Entries"                                               , 14 , -7  , 7    );
  TH1F *h_genDeltaR         = new TH1F("h_genDeltaR"         , ";DeltaR;Entries"                                              , 40 , 0   , 0.4  );

  int xtt0_nbins = 50;
  double xtt0_max = 1000.;
  double xtt0_max_2d = 200.;
  TH1F *h_chi2_value        = new TH1F("h_chi2_value"        , ";Xtt0;Entries"                                                , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_chi2_cut_eff      = new TH1F("h_chi2_cut_eff"      , ";Xtt0 cut value;Efficiency"                                   , xtt0_nbins , 0 , xtt0_max  );
  TH2F *h_chi2_mass_wboson  = new TH2F("h_chi2_mass_wboson"  , ";Mass [GeV/c^{2}];Xtt0 cut value"                             , 32 , 0   , 160 , xtt0_nbins , 0 , xtt0_max_2d);
  TH2F *h_chi2_mass_top     = new TH2F("h_chi2_mass_top"     , ";Mass [GeV/c^{2}];Xtt0 cut value"                             , 35 , 0   , 350 , xtt0_nbins , 0 , xtt0_max_2d);

  h_chi2_cut_eff->Sumw2();

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
  int chi2_entries = 0;
  int counter_before_gen_criteria         = 0;
  int counter_after_gen_criteria          = 0;
  int counter_pass_gen_deltaR_criterion   = 0;
  int counter_pass_gen_pt_ratio_criterion = 0;
  int counter_gen_open_angle_selection    = 0;
  int counter_gen_pt_ratio_selection      = 0;
  int counter_has_two_gen_b               = 0;
  int counter_has_reasonable_gen_match    = 0;
  int counter_has_reasonable_match        = 0;
  int counter_more_than_nine_jets         = 0;
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
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event) {
    //for (unsigned int event = 0; event < 100; ++event) {

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
          //printf("w mass = %7.2f, top mass = %7.2f\n", gen_wboson.M(), gen_top.M());
          h_mass_gen_wboson -> Fill(gen_wboson.M());
          h_mass_gen_top    -> Fill(gen_top.M());
          counter_has_reasonable_gen_match += 1;
      }

      //--------------- Reco. information ---------------//
      // MC-truth matching

      vector<int> vec_genIndex_register;
      vector<int> vec_jetIndex_register;
      vector<float> vec_pdgId_register;
      vector<float> vec_mompdgId_register;
      vector<double> vec_deltaR_register;
      vector<double> vec_ptRatio_register;
      int counter_bquark_matching = 0;
      int counter_wquark_matching = 0;
      for( unsigned int genLoop = 0; genLoop < gen_particles.size(); ++genLoop )
      {
          bool is_outgoing_parton = gen_status[genLoop] == 23 && abs(gen_pdgIds[genLoop]) <  6;
          if(!is_outgoing_parton) continue;
          TLorentzVector part = gen_particles[genLoop];

          vector<double> vec_deltaR;
          vector<double> vec_ptRatio;
          for( unsigned int index = 0; index < jets.size(); ++index )
          {
              TLorentzVector jet = jets[index];
              double deltaR = sqrt( (jet.Eta()-part.Eta())*(jet.Eta()-part.Eta()) + (jet.Phi()-part.Phi())*(jet.Phi()-part.Phi()) );
              double ptRatio = part.Pt() > 0. ? (jet.Pt() - part.Pt()) / part.Pt() : 1.;
              vec_deltaR.push_back(deltaR);
              vec_ptRatio.push_back(ptRatio);
          }

          vector<std::pair<int, double> > vec_deltaR_sorted = sortVectorSmaller(vec_deltaR);


          counter_before_gen_criteria += 1;
          h_deltaR_partons->Fill(vec_deltaR_sorted[0].second);
          h_ptRatio_partons->Fill(vec_ptRatio[vec_deltaR_sorted[0].first]);

          bool pass_gen_deltaR_criterion = vec_deltaR_sorted[0].second < 0.4;
          bool pass_gen_pt_ratio_criterion = vec_ptRatio[vec_deltaR_sorted[0].first] < 0.5;
          if(pass_gen_deltaR_criterion) counter_pass_gen_deltaR_criterion += 1;
          if(pass_gen_pt_ratio_criterion) counter_pass_gen_pt_ratio_criterion += 1;
          if( !(pass_gen_deltaR_criterion && pass_gen_pt_ratio_criterion) ) continue;
          counter_after_gen_criteria += 1;

          bool is_bjet = abs(gen_pdgIds[genLoop]) == 5 && abs(mom_pdgIds[genLoop]) == 6;
          bool is_wjet = abs(gen_pdgIds[genLoop]) <  5 && abs(mom_pdgIds[genLoop]) == 24;
          if(is_bjet) counter_bquark_matching += 1;
          if(is_wjet) counter_wquark_matching += 1;

          vec_genIndex_register.push_back(genLoop);
          vec_jetIndex_register.push_back(vec_deltaR_sorted[0].first);
          vec_pdgId_register.push_back(gen_pdgIds[genLoop]);
          vec_mompdgId_register.push_back(mom_pdgIds[genLoop]);
          vec_deltaR_register.push_back(vec_deltaR_sorted[0].second);
          vec_ptRatio_register.push_back(vec_ptRatio[vec_deltaR_sorted[0].first]);

          //printf("genLoop = %d, ", genLoop);
          //printf("gen_pdgIds[genLoop] = %.0f, ", gen_pdgIds[genLoop]);
          //printf("mom_pdgIds[genLoop] = %.0f, ", mom_pdgIds[genLoop]);
          //printf("vec_deltaR_sorted[0].first = %d, ", vec_deltaR_sorted[0].first);
          //printf("vec_deltaR_sorted[0].second = %.2f\n", vec_deltaR_sorted[0].second);
      }

      has_reasonable_gen_matching = counter_bquark_matching >= 1 && counter_wquark_matching >= 2;
      bool MC_truth_matching_is_applicable = vec_pdgId_register.size() >= 3 && has_reasonable_gen_matching;
      if(MC_truth_matching_is_applicable)
      {
          TLorentzVector truthMatched_bjet;
          TLorentzVector truthMatched_wjet1;
          TLorentzVector truthMatched_wjet2;

          int indices_bjj[3] = {-1};
          int counter_wjet = 0;
          for( unsigned int i = 0; i < vec_jetIndex_register.size(); ++i )
          {
              bool is_bjet = abs(vec_pdgId_register[i]) == 5 && abs(vec_mompdgId_register[i]) == 6;
              bool is_wjet = abs(vec_pdgId_register[i]) <  5 && abs(vec_mompdgId_register[i]) == 24;

              if(is_bjet){ truthMatched_bjet = jets[vec_jetIndex_register[i]]; indices_bjj[0] = i; }
              if(is_wjet && counter_wjet == 1){ truthMatched_wjet2 = jets[vec_jetIndex_register[i]]; counter_wjet += 1; indices_bjj[2] = i; }
              if(is_wjet && counter_wjet == 0){ truthMatched_wjet1 = jets[vec_jetIndex_register[i]]; counter_wjet += 1; indices_bjj[1] = i; }

              //printf("(%d) pdgId = %.0f, mompdgId = %.0f\n", i, vec_pdgId_register[i], vec_mompdgId_register[i]);
          }
          //printf("\n");

          bool pass_eta_codition_on_wjets = truthMatched_wjet1.Eta() < 3. && truthMatched_wjet2.Eta() < 3.;
          if(pass_eta_codition_on_wjets)
          {
            TLorentzVector truthMatched_wboson = truthMatched_wjet1 + truthMatched_wjet2;
            TLorentzVector truthMatched_top    = truthMatched_bjet + truthMatched_wboson;
            TLorentzVector truthMatched_tprime = truthMatched_top + diphoton;

            ////printf("w mass = %.2f, ", truthMatched_wboson.M());
            ////printf("top mass = %.2f, ", truthMatched_top.M());
            //if(truthMatched_wboson.M() > 120.)
            //{
            //  for(int i=0; i<3; ++i)
            //    printf("[debug] (%d) pdgId = %.0f, mompdgId = %.0f, deltaR = %.2f\n", i, vec_pdgId_register[indices_bjj[i]], vec_mompdgId_register[indices_bjj[i]], vec_deltaR_register[indices_bjj[i]]);
            //  printf("\n");
            //}

            h_deltaR_wjets   -> Fill(truthMatched_wjet1.DeltaR(truthMatched_wjet2));
            h_mass_tm_wboson -> Fill(truthMatched_wboson.M());
            h_mass_tm_top    -> Fill(truthMatched_top.M());
            h_mass_tm_tprime -> Fill(truthMatched_tprime.M());

            counter_has_reasonable_match += 1;
          }
      }

      double min_chi2_value = 99999.;

      // Minimum chi-2 method
      // the bjet is determined according to the DeepCSV algorithm; while the wjets are chosen from the remaining jets 
      int index_bjet = btag_scores_sorted[0].first;
      vector<int> indices_wjets = get_the_best_wjets_candidate(jets, index_bjet, min_chi2_value);

      //printf("minimum chi-2: ");
      //printf("[%d, %d, %d]\n", index_bjet, indices_wjets[0], indices_wjets[1]);

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

      h_chi2_value       -> Fill(min_chi2_value);
      for(int bin = 1; bin < xtt0_nbins + 1; ++bin )
      {
          double width = xtt0_max / (double) xtt0_nbins;
          double upper_bound = xtt0_max - width  * (double) bin;
          double width_2d = xtt0_max_2d / (double) xtt0_nbins;
          double upper_bound_2d = xtt0_max_2d - width_2d  * (double) bin;
          if(min_chi2_value <  upper_bound)
          {
              h_chi2_mass_wboson -> Fill(wboson.M() , upper_bound_2d);
              h_chi2_mass_top    -> Fill(top.M()    , upper_bound_2d);
              h_chi2_cut_eff -> Fill( upper_bound );
          }
      }

//      h_deltaR_wjets     -> Fill(wjet1.DeltaR(wjet2));
//      h_deltaR_photons   -> Fill(leading_photon.DeltaR(subleading_photon));
//      h_deltaR_bW        -> Fill(bjet.DeltaR(wboson));
//      h_deltaR_tH        -> Fill(top.DeltaR(diphoton));
//
//      h_helicity_tprime  -> Fill( helicity(top, diphoton) );
//      h_helicity_top     -> Fill( helicity(bjet, wboson) );
//      h_helicity_higgs   -> Fill( helicity(leading_photon, subleading_photon) );
//
//      h_genIndices       -> Fill(genMatched_jet0_index());
//      h_genIndices       -> Fill(genMatched_jet1_index());
//      h_genIndices       -> Fill(genMatched_jet2_index());
//      h_genPdgId         -> Fill(genMatched_jet0_pdgId());
//      h_genPdgId         -> Fill(genMatched_jet1_pdgId());
//      h_genPdgId         -> Fill(genMatched_jet2_pdgId());
//      h_genDeltaR        -> Fill(genMatched_jet0_deltaR());
//      h_genDeltaR        -> Fill(genMatched_jet1_deltaR());
//      h_genDeltaR        -> Fill(genMatched_jet2_deltaR());
//      //vProcess[processId]->fill_histogram("h" + syst_ext + "Mass", mass(), evt_weight, vId);   


      //--------------- Other info ---------------//
      //for(int i=0; i<jets.size(); ++i)
      //    printf("(%d) idx = %d, btag_scores = %.2f\n", i, btag_scores_sorted[i].first, btag_scores_sorted[i].second);
      //printf("\n");

      if(jets.size() > 9) counter_more_than_nine_jets += 1;
      counter_total_selected_events += 1;
    } // end of event loop

    double overflow = h_chi2_value -> GetBinContent(xtt0_nbins) + h_chi2_value -> GetBinContent(xtt0_nbins + 1);
    h_chi2_value->SetBinContent(xtt0_nbins, overflow);

    chi2_entries = h_chi2_value -> GetEntries();
    h_chi2_cut_eff -> Scale( 1./(double)chi2_entries );
    for(int bin = 0; bin < xtt0_nbins; ++bin)
    {
        double eff = h_chi2_cut_eff->GetBinContent(bin+1);
        double err = sqrt( ( eff * (1-eff) ) / chi2_entries );
        h_chi2_cut_eff->SetBinError(bin+1, err);
    }
  
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
  print_counter_percentage("pass_gen_deltaR_criterion", counter_pass_gen_deltaR_criterion, counter_before_gen_criteria);
  print_counter_percentage("pass_gen_pt_ratio_criterion", counter_pass_gen_pt_ratio_criterion, counter_before_gen_criteria);
  print_counter_percentage("after_gen_criteria", counter_after_gen_criteria, counter_before_gen_criteria);

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
