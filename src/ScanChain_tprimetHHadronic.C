#include "ScanChain.h"
#include "chi2_helper.h"
#include "truth_matching.h"
#include "sorting.h"
//#include "my_hists.h"

int ScanChain_tprimetHHadronic(TChain* chain, TString name_output_file, TString year_str, TString mass_str, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {
  //TFile* f1 = new TFile(tag + "_" + ext + "_histograms" + year + idx + ".root", "RECREATE");
  TFile *output_file = new TFile(name_output_file, "RECREATE");
  TString json_file = "json/covMatrix_Era" + year_str + "_M" + mass_str + ".json";


  float n_lep;
  float n_jet;
  float mass_diphoton;
  float mass_top;

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Histograms{{{
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
  TH1F *h_mass_tprime_tm    = new TH1F("h_mass_tprime_tm"    , ";MC-truth-matched Tprime invariant mass [GeV/c^{2}];Entries"  , 36 , 200 , 2000 );
  TH1F *h_mass_tprime_cov   = new TH1F("h_mass_tprime_cov"   , ";(cov. matrix) Tprime invariant mass [GeV/c^{2}];Entries"     , 36 , 200 , 2000 );

  TH1F *h_mass_top          = new TH1F("h_mass_top"          , ";Top invariant mass [GeV/c^{2}];Entries"                      , 40 , 100 , 300  );
  TH1F *h_mass_top_tm       = new TH1F("h_mass_top_tm"       , ";MC-truth-matched Top invariant mass [GeV/c^{2}];Entries"     , 40 , 100 , 300  );
  TH1F *h_mass_top_cov      = new TH1F("h_mass_top_cov"      , ";(cov. matrix) Top invariant mass [GeV/c^{2}];Entries"        , 40 , 100 , 300  );
  TH1F *h_mass_top_gen      = new TH1F("h_mass_top_gen"      , ";gen-leveled top invariant mass [GeV/c^{2}];Entries"          , 40 , 100 , 300  );
  TH1F *h_pt_top_tm         = new TH1F("h_pt_top_tm"         , ";MC-truth-matched Top pt [GeV/c];Entries"                     , 40 , 0   , 1000 );

  TH1F *h_mass_wboson       = new TH1F("h_mass_wboson"       , ";W boson invariant mass [GeV/c^{2}];Entries"                  , 40 , 0   , 200  );
  TH1F *h_mass_wboson_tm    = new TH1F("h_mass_wboson_tm"    , ";MC-truth-matched W boson invariant mass [GeV/c^{2}];Entries" , 40 , 0   , 200  );
  TH1F *h_mass_wboson_cov   = new TH1F("h_mass_wboson_cov"   , ";(cov. matrix) W boson invariant mass [GeV/c^{2}];Entries"    , 40 , 0   , 200  );
  TH1F *h_mass_wboson_gen   = new TH1F("h_mass_wboson_gen"   , ";gen-leveled W boson invariant mass [GeV/c^{2}];Entries"      , 40 , 0   , 200  );
  TH1F *h_pt_wboson_tm      = new TH1F("h_pt_wboson_tm"      , ";MC-truth-matched W boson pt [GeV/c];Entries"                 , 40 , 0   , 1000 );

  TH1F *h_mass_tprime_subspace       = new TH1F("h_mass_tprime_subspace"        , ";Tprime invariant mass [GeV/c^{2}];Entries"                    , 36  , 200  , 2000 );
  TH1F *h_mass_tprime_cov_subspace   = new TH1F("h_mass_tprime_cov_subspace"    , ";(cov. matrix) Tprime invariant mass [GeV/c^{2}];Entries"      , 36  , 200  , 2000 );
  TH1F *h_mass_top_subspace          = new TH1F("h_mass_top_subspace"           , ";Top invariant mass [GeV/c^{2}];Entries"                       , 40  , 100  , 300  );
  TH1F *h_mass_top_cov_subspace      = new TH1F("h_mass_top_cov_subspace"       , ";(cov. matrix) Top invariant mass [GeV/c^{2}];Entries"         , 40  , 100  , 300  );
  TH1F *h_mass_wboson_subspace       = new TH1F("h_mass_wboson_subspace"        , ";W boson invariant mass [GeV/c^{2}];Entries"                   , 40  , 0    , 200  );
  TH1F *h_mass_wboson_cov_subspace   = new TH1F("h_mass_wboson_cov_subspace"    , ";(cov. matrix) W boson invariant mass [GeV/c^{2}];Entries"     , 40  , 0    , 200  );

  TH1F *h_deltaR_partons    = new TH1F("h_deltaR_partons"     , "; Open angle (parton, matched jet)"                            , 40  , 0.   , 4.   );
  TH1F *h_ptRatio_partons   = new TH1F("h_ptRatio_partons"    , "; abs(p_{T}^{reco} - p_{T}^{gen}) / p_{T}^{gen};Entries"       , 40  , 0.   , 4.   );
  TH1F *h_deltaR_wjets      = new TH1F("h_deltaR_wjets"       , ";Open angle (wjet1, wjet2);Entries"                            , 40  , 0.   , 6.   );

  TH1F *h_deltaR_photons    = new TH1F("h_deltaR_photons"     , ";Open angle (leading photon, sublading photon);Entries"        , 40  , 0.   , 6.   );
  TH1F *h_deltaR_bW         = new TH1F("h_deltaR_bW"          , ";Open angle (bjet, W candidate);Entries"                       , 40  , 0.   , 6.   );
  TH1F *h_deltaR_tH         = new TH1F("h_deltaR_tH"          , ";Open angle (top candidate, diphoton);Entries"                 , 40  , 0.   , 6.   );
  TH1F *h_helicity_tprime   = new TH1F("h_helicity_tprime"    , ";helicity (top, diphoton);Entries"                             , 40  , 0.   , 1.   );
  TH1F *h_helicity_top      = new TH1F("h_helicity_top"       , ";helicity (bjet, W candidate);Entries"                         , 40  , 0.   , 1.   );
  TH1F *h_helicity_higgs    = new TH1F("h_helicity_higgs"     , ";helicity (leading photon, sub-leading photon);Entries"        , 40  , 0.   , 1.   );
  TH1F *h_genIndices        = new TH1F("h_genIndices"         , ";Indices;Entries"                                              , 10  , -1   , 9    );
  TH1F *h_genPdgId          = new TH1F("h_genPdgId"           , ";PdgId;Entries"                                                , 14  , -7   , 7    );
  TH1F *h_genDeltaR         = new TH1F("h_genDeltaR"          , ";DeltaR;Entries"                                               , 40  , 0    , 0.4  );

  int xtt0_nbins = 40;
  double xtt0_max = 100.;
  double xtt0_max_2d = 200.;
  // subspace := consider events that the MC truth matching is applicable (~37%)
  TH1F *h_chi2_value                         = new TH1F("h_chi2_value"                         , ";Xtt0;Entries"                                     , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_chi2_value_subspace                = new TH1F("h_chi2_value_subspace"                , ";Xtt0;Entries"                                     , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_chi2_cut_eff                       = new TH1F("h_chi2_cut_eff"                       , ";Xtt0 cut value;Efficiency"                        , xtt0_nbins , 0 , xtt0_max  );
  TH2F *h_chi2_mass_wboson                   = new TH2F("h_chi2_mass_wboson"                   , ";Mass [GeV/c^{2}];Xtt0 cut value"                  , 32         , 0 , 160          , xtt0_nbins , 0 , xtt0_max_2d);
  TH2F *h_chi2_mass_top                      = new TH2F("h_chi2_mass_top"                      , ";Mass [GeV/c^{2}];Xtt0 cut value"                  , 35         , 0 , 350          , xtt0_nbins , 0 , xtt0_max_2d);
  TH1F *h_cov_chi2_value                     = new TH1F("h_cov_chi2_value"                     , ";(cov. matrix) Xtt0;Entries"                       , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_chi2_value_subspace            = new TH1F("h_cov_chi2_value_subspace"            , ";(cov. matrix) Xtt0;Entries"                       , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_chi2_cut_eff                   = new TH1F("h_cov_chi2_cut_eff"                   , ";(cov. matrix) Xtt0 cut value;Efficiency"          , xtt0_nbins , 0 , xtt0_max  );
  TH2F *h_cov_chi2_mass_wboson               = new TH2F("h_cov_chi2_mass_wboson"               , ";(cov. matrix) Mass [GeV/c^{2}];Xtt0 cut value"    , 32         , 0 , 160          , xtt0_nbins , 0 , xtt0_max_2d);
  TH2F *h_cov_chi2_mass_top                  = new TH2F("h_cov_chi2_mass_top"                  , ";(cov. matrix) Mass [GeV/c^{2}];Xtt0 cut value"    , 35         , 0 , 350          , xtt0_nbins , 0 , xtt0_max_2d);

  TH1F *h_numerator_vs_chi2Cut               = new TH1F("h_numerator_vs_chi2Cut"               , ";Xtt0 cut value;Denominator"                       , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_denominator_vs_chi2Cut             = new TH1F("h_denominator_vs_chi2Cut"             , ";Xtt0 cut value;Denominator"                       , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_matchingEff_vs_chi2Cut             = new TH1F("h_matchingEff_vs_chi2Cut"             , ";Xtt0 cut value;Matching efficiency"               , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_numerator_vs_chi2Cut           = new TH1F("h_cov_numerator_vs_chi2Cut"           , ";(cov. matrix) Xtt0 cut value;Denominator"         , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_denominator_vs_chi2Cut         = new TH1F("h_cov_denominator_vs_chi2Cut"         , ";(cov. matrix) Xtt0 cut value;Denominator"         , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_matchingEff_vs_chi2Cut         = new TH1F("h_cov_matchingEff_vs_chi2Cut"         , ";(cov. matrix) Xtt0 cut value;Matching efficiency" , xtt0_nbins , 0 , xtt0_max  );

  TH1F *h_numerator_vs_chi2Bins              = new TH1F("h_numerator_vs_chi2Bins"              , ";Xtt0 value;Denominator"                           , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_denominator_vs_chi2Bins            = new TH1F("h_denominator_vs_chi2Bins"            , ";Xtt0 value;Denominator"                           , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_matchingEff_vs_chi2Bins            = new TH1F("h_matchingEff_vs_chi2Bins"            , ";Xtt0 value;Matching efficiency"                   , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_numerator_vs_chi2Bins          = new TH1F("h_cov_numerator_vs_chi2Bins"          , ";(cov. matrix) Xtt0 value;Denominator"             , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_denominator_vs_chi2Bins        = new TH1F("h_cov_denominator_vs_chi2Bins"        , ";(cov. matrix) Xtt0 value;Denominator"             , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_matchingEff_vs_chi2Bins        = new TH1F("h_cov_matchingEff_vs_chi2Bins"        , ";(cov. matrix) Xtt0 value;Matching efficiency"     , xtt0_nbins , 0 , xtt0_max  );

  TH1F *h_matchingEff_vs_chi2Cut_rebase      = new TH1F("h_matchingEff_vs_chi2Cut_rebase"      , ";Xtt0 cut value;Matching efficiency"               , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_matchingEff_vs_chi2Cut_rebase  = new TH1F("h_cov_matchingEff_vs_chi2Cut_rebase"  , ";(cov. matrix) Xtt0 cut value;Matching efficiency" , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_matchingEff_vs_chi2Bins_rebase     = new TH1F("h_matchingEff_vs_chi2Bins_rebase"     , ";Xtt0 value;Matching efficiency"                   , xtt0_nbins , 0 , xtt0_max  );
  TH1F *h_cov_matchingEff_vs_chi2Bins_rebase = new TH1F("h_cov_matchingEff_vs_chi2Bins_rebase" , ";(cov. matrix) Xtt0 value;Matching efficiency"     , xtt0_nbins , 0 , xtt0_max  );

  h_chi2_cut_eff->Sumw2();
  h_cov_chi2_cut_eff->Sumw2();

  //h_mass_diphoton->SetDirectory(rootdir);
  //vector<Process*> vProcess = generate_processes(f1);
  //add_variables(vProcess, tag);
  //}}}
  TNtuple *nt_top            = new TNtuple("nt_top", "nt_top", "mass:pt");
  TNtuple *nt_wboson         = new TNtuple("nt_wboson", "nt_wboson", "mass:pt");
  TNtuple *nt_mass_top       = new TNtuple("nt_mass_top", "nt_mass_top", "mass");
  TNtuple *nt_mass_wboson    = new TNtuple("nt_mass_wboson", "nt_mass_wboson", "mass");
  TNtuple *nt_mass_diphoton  = new TNtuple("nt_mass_diphoton", "nt_mass_diphoton", "mass");
  TNtuple *nt_chi2_value     = new TNtuple("nt_chi2_value", "nt_chi2_value", "chi2_value");
  TNtuple *nt_chi2_value_cov = new TNtuple("nt_chi2_value_cov", "nt_chi2_value_cov", "chi2_value");

  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if (nEvents >= 0) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  int chi2_entries = 0;
  int counter_MC_applicable               = 0;
  int counter_matching_chi2Method         = 0;
  int counter_matching_covMatrix          = 0;
  int counter_before_gen_criteria         = 0;
  int counter_after_gen_criteria          = 0;
  int counter_pass_gen_deltaR_criterion   = 0;
  int counter_pass_gen_pt_ratio_criterion = 0;
  int counter_gen_open_angle_selection    = 0;
  int counter_gen_pt_ratio_selection      = 0;
  int counter_has_two_gen_b               = 0;
  int counter_has_bquark_and_wquarks      = 0;
  int counter_has_reasonable_MC_match     = 0;
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
      
      //----------------------------- MC truth information -----------------------------//
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
          h_mass_wboson_gen -> Fill(gen_wboson.M());
          h_mass_top_gen    -> Fill(gen_top.M());
          counter_has_bquark_and_wquarks += 1;
      }

      //----------------------------- Reco. information -----------------------------//
      bool debug = false;
      bool debug_deeper = false;
      
      // MC-truth matching
      vector<int> indices_bjj_truthMatching(3, -1);
      truth_matching_helper tr(gen_particles, jets, gen_pdgIds, gen_status, mom_pdgIds, h_deltaR_partons, h_ptRatio_partons);
      bool MC_truth_matching_is_applicable = tr.perform_mc_truth_matching(); // counter_bquark_matching >= 1 && counter_wquark_matching >= 2;
      if(MC_truth_matching_is_applicable)
      {
          TLorentzVector truthMatched_bjet;
          TLorentzVector truthMatched_wjet1;
          TLorentzVector truthMatched_wjet2;

          int counter_wjet = 0;
          for( unsigned int i = 0; i < tr.get_register_jetIndex().size(); ++i )
          {
              bool is_bjet = abs(tr.get_register_pdgId()[i]) == 5 && abs(tr.get_register_mompdgId()[i]) == 6;
              bool is_wjet = abs(tr.get_register_pdgId()[i]) <  5 && abs(tr.get_register_mompdgId()[i]) == 24;

              if(is_bjet){ truthMatched_bjet = jets[tr.get_register_jetIndex()[i]]; indices_bjj_truthMatching[0] = tr.get_register_jetIndex()[i]; }
              if(is_wjet && counter_wjet == 1){ truthMatched_wjet2 = jets[tr.get_register_jetIndex()[i]]; counter_wjet += 1; indices_bjj_truthMatching[2] = tr.get_register_jetIndex()[i]; }
              if(is_wjet && counter_wjet == 0){ truthMatched_wjet1 = jets[tr.get_register_jetIndex()[i]]; counter_wjet += 1; indices_bjj_truthMatching[1] = tr.get_register_jetIndex()[i]; }

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
            h_mass_tprime_tm -> Fill(truthMatched_tprime.M());

            h_pt_wboson_tm   -> Fill(truthMatched_wboson.Pt());
            h_mass_wboson_tm -> Fill(truthMatched_wboson.M());

            h_pt_top_tm      -> Fill(truthMatched_top.Pt());
            h_mass_top_tm    -> Fill(truthMatched_top.M());

            nt_top -> Fill(truthMatched_top.M(), truthMatched_top.Pt());
            nt_wboson -> Fill(truthMatched_wboson.M(), truthMatched_wboson.Pt());
            nt_mass_top -> Fill(truthMatched_top.M());
            nt_mass_wboson -> Fill(truthMatched_wboson.M());

            counter_has_reasonable_MC_match += 1;
          }

          counter_after_gen_criteria += 1;
      }
      if(tr.get_pass_gen_deltaR_criterion()) counter_pass_gen_deltaR_criterion += 1;
      if(tr.get_pass_gen_pt_ratio_criterion()) counter_pass_gen_pt_ratio_criterion += 1;

      h_num_jets         -> Fill(jets.size());
      h_mass_diphoton    -> Fill(CMS_hgg_mass());
      h_mass_diphoton_v2 -> Fill(diphoton_v2.M());
      nt_mass_diphoton   -> Fill(CMS_hgg_mass());

      // Minimum chi-2 method
      // the bjet is determined according to the DeepCSV algorithm; while the wjets are chosen from the remaining jets 
      double min_chi2_value = 99999.;
      int index_bjet = btag_scores_sorted[0].first;
      vector<int> indices_wjets(2, -999);
      bool has_resonable_reco_chi2 = get_the_best_wjets_candidate(indices_wjets, jets, index_bjet, min_chi2_value);
      vector<int> indices_bjj_chi2Method = {index_bjet, indices_wjets[0], indices_wjets[1]};

      TLorentzVector bjet = jets[index_bjet];
      TLorentzVector wjet1 = jets[indices_wjets[0]];
      TLorentzVector wjet2 = jets[indices_wjets[1]];

      bool pass_eta_codition_on_wjets = wjet1.Eta() < 3. && wjet2.Eta() < 3.;
      if(pass_eta_codition_on_wjets)
      {
          TLorentzVector wboson = wjet1 + wjet2;
          TLorentzVector top = bjet + wboson;
          TLorentzVector tprime = top + diphoton;

          h_mass_wboson -> Fill(wboson.M());
          h_mass_top    -> Fill(top.M());
          h_mass_tprime -> Fill(tprime.M());
          h_chi2_value  -> Fill(min_chi2_value);
          nt_chi2_value -> Fill(min_chi2_value);

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
                  h_chi2_cut_eff     -> Fill( upper_bound );
              }
          }

          if(MC_truth_matching_is_applicable){
              h_mass_tprime_subspace -> Fill(tprime.M());
              h_mass_top_subspace    -> Fill(top.M());
              h_mass_wboson_subspace -> Fill(wboson.M());
          }

          if(min_chi2_value < 5.) debug = true;
      } // end of eta selection for the chi-2 method

      //Minimum chi-2 with covaraince matrix
      double min_chi2_value_2x2 = 99999.;
      vector<int> indices_bjj_covMatrix(3, -1);
      bool has_resonable_reco = get_the_best_bjj_candidate(indices_bjj_covMatrix, jets, diphoton, btag_scores, min_chi2_value_2x2, json_file);

      if(has_resonable_reco)
      {
        TLorentzVector cov_bjet  = jets[indices_bjj_covMatrix[0]];
        TLorentzVector cov_wjet1 = jets[indices_bjj_covMatrix[1]];
        TLorentzVector cov_wjet2 = jets[indices_bjj_covMatrix[2]];

        if( cov_wjet1.Eta() < 3. && cov_wjet2.Eta() < 3. )
        {
            TLorentzVector cov_wboson = cov_wjet1 + cov_wjet2;
            TLorentzVector cov_top = cov_bjet + cov_wboson;
            TLorentzVector cov_tprime = cov_top + diphoton;

            h_mass_wboson_cov -> Fill(cov_wboson.M());
            h_mass_top_cov    -> Fill(cov_top.M());
            h_mass_tprime_cov -> Fill(cov_tprime.M());
            h_cov_chi2_value  -> Fill(min_chi2_value_2x2);
            nt_chi2_value_cov -> Fill(min_chi2_value_2x2);

            for(int bin = 1; bin < xtt0_nbins + 1; ++bin )
            {
                double width = xtt0_max / (double) xtt0_nbins;
                double upper_bound = xtt0_max - width  * (double) bin;
                double width_2d = xtt0_max_2d / (double) xtt0_nbins;
                double upper_bound_2d = xtt0_max_2d - width_2d  * (double) bin;
                if(min_chi2_value_2x2 <  upper_bound)
                {
                    h_cov_chi2_mass_wboson -> Fill(cov_wboson.M() , upper_bound_2d);
                    h_cov_chi2_mass_top    -> Fill(cov_top.M()    , upper_bound_2d);
                    h_cov_chi2_cut_eff     -> Fill( upper_bound );
                }
            }
            if(MC_truth_matching_is_applicable){
                h_mass_tprime_cov_subspace -> Fill(cov_tprime.M());
                h_mass_top_cov_subspace    -> Fill(cov_top.M());
                h_mass_wboson_cov_subspace -> Fill(cov_wboson.M());
            }
        } // end of eta selection for the chi-2 method
      }

      //--------------- Other info ---------------//
      //h_deltaR_wjets     -> Fill(wjet1.DeltaR(wjet2));
      //h_deltaR_photons   -> Fill(leading_photon.DeltaR(subleading_photon));
      //h_deltaR_bW        -> Fill(bjet.DeltaR(wboson));
      //h_deltaR_tH        -> Fill(top.DeltaR(diphoton));
      //
      //h_helicity_tprime  -> Fill( helicity(top, diphoton) );
      //h_helicity_top     -> Fill( helicity(bjet, wboson) );
      //h_helicity_higgs   -> Fill( helicity(leading_photon, subleading_photon) );
      //
      //h_genIndices       -> Fill(genMatched_jet0_index());
      //h_genIndices       -> Fill(genMatched_jet1_index());
      //h_genIndices       -> Fill(genMatched_jet2_index());
      //h_genPdgId         -> Fill(genMatched_jet0_pdgId());
      //h_genPdgId         -> Fill(genMatched_jet1_pdgId());
      //h_genPdgId         -> Fill(genMatched_jet2_pdgId());
      //h_genDeltaR        -> Fill(genMatched_jet0_deltaR());
      //h_genDeltaR        -> Fill(genMatched_jet1_deltaR());
      //h_genDeltaR        -> Fill(genMatched_jet2_deltaR());
      ////vProcess[processId]->fill_histogram("h" + syst_ext + "Mass", mass(), evt_weight, vId);   
      if(MC_truth_matching_is_applicable)
      {
          bool chi2Method_is_matched = matching_teller(indices_bjj_truthMatching, indices_bjj_chi2Method);
          bool covMatrix_is_matched  = matching_teller(indices_bjj_truthMatching, indices_bjj_covMatrix);

          if(debug){
              if(chi2Method_is_matched) counter_matching_chi2Method += 1;
              if(covMatrix_is_matched)  counter_matching_covMatrix  += 1;
              counter_MC_applicable += 1;

              if(debug_deeper){
                  TString text;
                  text = chi2Method_is_matched ? "matched!" : "Nah";
                  printf("chi-2 sim: %.2f, %s\n", min_chi2_value, text.Data());
                  text = covMatrix_is_matched ? "matched!" : "Nah";
                  printf("chi-2 cov: %.2f, %s\n", min_chi2_value_2x2, text.Data());
              }
          }

          // various chi-2 cut values
          for(int bin = 1; bin < xtt0_nbins + 1; ++bin )
          {
              double width = xtt0_max / (double) xtt0_nbins;
              double upper_bound = xtt0_max - width  * (double) bin;
              double lower_bound = xtt0_max - width  * (double) (bin + 1);
              // every event has an chi-2 value; if cut on the value, the denominator should change accordingly
              if(min_chi2_value < upper_bound)
              {
                  h_denominator_vs_chi2Cut -> Fill( upper_bound );
                  if(chi2Method_is_matched) h_numerator_vs_chi2Cut -> Fill( upper_bound );

                  if(min_chi2_value > lower_bound)
                  {
                      h_denominator_vs_chi2Bins -> Fill( lower_bound );
                      if(chi2Method_is_matched) h_numerator_vs_chi2Bins -> Fill( lower_bound );
                  }
              }

              if(min_chi2_value_2x2 < upper_bound)
              {
                  h_cov_denominator_vs_chi2Cut -> Fill( upper_bound );
                  if(covMatrix_is_matched) h_cov_numerator_vs_chi2Cut -> Fill( upper_bound );

                  if(min_chi2_value_2x2 > lower_bound)
                  {
                      h_cov_denominator_vs_chi2Bins -> Fill( lower_bound );
                      if(chi2Method_is_matched) h_cov_numerator_vs_chi2Bins -> Fill( lower_bound );
                  }
              }
          }

          // record chi-2 value distribution in the subspace
          h_chi2_value_subspace->Fill(min_chi2_value);
          h_cov_chi2_value_subspace->Fill(min_chi2_value_2x2);

          //print_indices(debug, "truth matching", indices_bjj_truthMatching);
          //print_indices(debug, "simple chi2 method", indices_bjj_chi2Method);
          //print_indices(debug, "cov-matrix chi2 method", indices_bjj_covMatrix);
      }

      if(jets.size() > 9) counter_more_than_nine_jets += 1;
      counter_total_selected_events += 1;
    } // end of event loop

    // evaluate matching efficiency
    chi2_entries = h_chi2_value -> GetEntries();
    h_chi2_cut_eff -> Scale( 1./(double)chi2_entries );
    for(int bin = 0; bin < xtt0_nbins; ++bin)
    {
        double eff = h_chi2_cut_eff->GetBinContent(bin+1);
        double err = sqrt( ( eff * (1-eff) ) / chi2_entries );
        h_chi2_cut_eff->SetBinError(bin+1, err);
    }

    convert_to_matching_efficiency( h_matchingEff_vs_chi2Cut, h_numerator_vs_chi2Cut, h_denominator_vs_chi2Cut, xtt0_nbins, chi2_entries, true );
    convert_to_matching_efficiency( h_cov_matchingEff_vs_chi2Cut, h_cov_numerator_vs_chi2Cut, h_cov_denominator_vs_chi2Cut, xtt0_nbins, chi2_entries, true );
    convert_to_matching_efficiency( h_matchingEff_vs_chi2Bins, h_numerator_vs_chi2Bins, h_denominator_vs_chi2Bins, xtt0_nbins, chi2_entries, true );
    convert_to_matching_efficiency( h_cov_matchingEff_vs_chi2Bins, h_cov_numerator_vs_chi2Bins, h_cov_denominator_vs_chi2Bins, xtt0_nbins, chi2_entries, true );

    convert_to_matching_efficiency( h_matchingEff_vs_chi2Cut_rebase, h_numerator_vs_chi2Cut, h_denominator_vs_chi2Cut, xtt0_nbins, chi2_entries, false );
    convert_to_matching_efficiency( h_cov_matchingEff_vs_chi2Cut_rebase, h_cov_numerator_vs_chi2Cut, h_cov_denominator_vs_chi2Cut, xtt0_nbins, chi2_entries, false );
    convert_to_matching_efficiency( h_matchingEff_vs_chi2Bins_rebase, h_numerator_vs_chi2Bins, h_denominator_vs_chi2Bins, xtt0_nbins, chi2_entries, false );
    convert_to_matching_efficiency( h_cov_matchingEff_vs_chi2Bins_rebase, h_cov_numerator_vs_chi2Bins, h_cov_denominator_vs_chi2Bins, xtt0_nbins, chi2_entries, false );

  
    // Clean Up
    delete tree;
    file.Close();
  }
  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  print_counter_percentage("Number of jets more than 9"              , counter_more_than_nine_jets         , counter_total_selected_events );
  print_counter_percentage("Percentage of having bquark and wquarks" , counter_has_bquark_and_wquarks      , counter_total_selected_events );
  print_counter_percentage("After the cut of resonable MC match"     , counter_has_reasonable_MC_match     , counter_total_selected_events );
  print_counter_percentage("SelectionEff: wjets eta criteria"        , h_mass_wboson->GetEntries()         , counter_total_selected_events );
  print_counter_percentage("Matching efficiency chi2Method"          , counter_matching_chi2Method         , counter_MC_applicable         );
  print_counter_percentage("Matching efficiency covMatrix"           , counter_matching_covMatrix          , counter_MC_applicable         );
  // MC truth matching info (not fiexed yet; may abandom)
  //print_counter_percentage("pass_gen_deltaR_criterion"               , counter_pass_gen_deltaR_criterion   , counter_before_gen_criteria   );
  //print_counter_percentage("pass_gen_pt_ratio_criterion"             , counter_pass_gen_pt_ratio_criterion , counter_before_gen_criteria   );
  //print_counter_percentage("after_gen_criteria"                      , counter_after_gen_criteria          , counter_before_gen_criteria   );

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
