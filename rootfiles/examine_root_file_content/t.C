#define t_cxx
#include "t.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void t::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L t.C
//      Root > t t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   fChain->SetBranchStatus("*", 0);  // disable all branches
   fChain->SetBranchStatus("evt_"                      , 1);
   fChain->SetBranchStatus("evt_weight_"               , 1);
   fChain->SetBranchStatus("process_id_"               , 1);
   fChain->SetBranchStatus("maxIDMVA_"                 , 1);
   fChain->SetBranchStatus("minIDMVA_"                 , 1);
   fChain->SetBranchStatus("max1_btag_"                , 1);
   fChain->SetBranchStatus("max2_btag_"                , 1);
   fChain->SetBranchStatus("dipho_delta_R"             , 1);
   fChain->SetBranchStatus("njets_"                    , 1);
   fChain->SetBranchStatus("nbjets_"                   , 1);
   fChain->SetBranchStatus("ht_"                       , 1);
   fChain->SetBranchStatus("leadptoM_"                 , 1);
   fChain->SetBranchStatus("subleadptoM_"              , 1);
   fChain->SetBranchStatus("lead_eta_"                 , 1);
   fChain->SetBranchStatus("sublead_eta_"              , 1);
   fChain->SetBranchStatus("jet1_ptOverM_"             , 1);
   fChain->SetBranchStatus("jet1_eta_"                 , 1);
   fChain->SetBranchStatus("jet1_btag_"                , 1);
   fChain->SetBranchStatus("jet2_ptOverM_"             , 1);
   fChain->SetBranchStatus("jet2_eta_"                 , 1);
   fChain->SetBranchStatus("jet2_btag_"                , 1);
   fChain->SetBranchStatus("jet3_ptOverM_"             , 1);
   fChain->SetBranchStatus("jet3_eta_"                 , 1);
   fChain->SetBranchStatus("jet3_btag_"                , 1);
   fChain->SetBranchStatus("jet4_ptOverM_"             , 1);
   fChain->SetBranchStatus("jet4_eta_"                 , 1);
   fChain->SetBranchStatus("jet4_btag_"                , 1);
   fChain->SetBranchStatus("leadPSV_"                  , 1);
   fChain->SetBranchStatus("subleadPSV_"               , 1);
   fChain->SetBranchStatus("dipho_cosphi_"             , 1);
   fChain->SetBranchStatus("dipho_rapidity_"           , 1);
   fChain->SetBranchStatus("met_"                      , 1);
   fChain->SetBranchStatus("dipho_pt_over_mass_"       , 1);
   fChain->SetBranchStatus("helicity_angle_"           , 1);
   fChain->SetBranchStatus("chi2_value_"               , 1);
   fChain->SetBranchStatus("chi2_bjet_ptOverM_"        , 1);
   fChain->SetBranchStatus("chi2_bjet_eta_"            , 1);
   fChain->SetBranchStatus("chi2_bjet_btagScores_"     , 1);
   fChain->SetBranchStatus("chi2_wjet1_ptOverM_"       , 1);
   fChain->SetBranchStatus("chi2_wjet1_eta_"           , 1);
   fChain->SetBranchStatus("chi2_wjet1_btagScores_"    , 1);
   fChain->SetBranchStatus("chi2_wjet2_ptOverM_"       , 1);
   fChain->SetBranchStatus("chi2_wjet2_eta_"           , 1);
   fChain->SetBranchStatus("chi2_wjet2_btagScores_"    , 1);
   fChain->SetBranchStatus("chi2_wjets_deltaR_"        , 1);
   fChain->SetBranchStatus("chi2_wboson_ptOverM_"      , 1);
   fChain->SetBranchStatus("chi2_wboson_eta_"          , 1);
   fChain->SetBranchStatus("chi2_wboson_mass_"         , 1);
   fChain->SetBranchStatus("chi2_wboson_deltaR_bjet_"  , 1);
   fChain->SetBranchStatus("chi2_tbw_mass_"            , 1);
   fChain->SetBranchStatus("chi2_tbw_ptOverM_"         , 1);
   fChain->SetBranchStatus("chi2_tbw_eta_"             , 1);
   fChain->SetBranchStatus("chi2_tbw_deltaR_dipho_"    , 1);
   fChain->SetBranchStatus("chi2_tprime_ptOverM_"      , 1);
   fChain->SetBranchStatus("chi2_tprime_eta_"          , 1);
   fChain->SetBranchStatus("chi2_tprime_deltaR_tbw_"   , 1);
   fChain->SetBranchStatus("chi2_tprime_deltaR_dipho_" , 1);
   fChain->SetBranchStatus("tprime_pt_ratio_"          , 1);
   fChain->SetBranchStatus("helicity_tprime_"          , 1);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      //printf("(%4d) : evt_weight = %5.2f, helicity_tprime_ = %7.2f\n", jentry, evt_weight_, helicity_tprime_);
      examine("evt_"                      , evt_                      );
      examine("evt_weight_"               , evt_weight_               );
      //examine("maxIDMVA_"                 , maxIDMVA_                 );
      //examine("minIDMVA_"                 , minIDMVA_                 );
      //examine("max1_btag_"                , max1_btag_                );
      //examine("max2_btag_"                , max2_btag_                );
      //examine("dipho_delta_R"             , dipho_delta_R             );
      //examine("njets_"                    , njets_                    );
      //examine("nbjets_"                   , nbjets_                   );
      //examine("ht_"                       , ht_                       );
      //examine("leadptoM_"                 , leadptoM_                 );
      //examine("subleadptoM_"              , subleadptoM_              );
      //examine("lead_eta_"                 , lead_eta_                 );
      //examine("sublead_eta_"              , sublead_eta_              );
      //examine("jet1_ptOverM_"             , jet1_ptOverM_             );
      //examine("jet1_eta_"                 , jet1_eta_                 );
      //examine("jet1_btag_"                , jet1_btag_                );
      //examine("jet2_ptOverM_"             , jet2_ptOverM_             );
      //examine("jet2_eta_"                 , jet2_eta_                 );
      //examine("jet2_btag_"                , jet2_btag_                );
      //examine("jet3_ptOverM_"             , jet3_ptOverM_             );
      //examine("jet3_eta_"                 , jet3_eta_                 );
      //examine("jet3_btag_"                , jet3_btag_                );
      //examine("jet4_ptOverM_"             , jet4_ptOverM_             );
      //examine("jet4_eta_"                 , jet4_eta_                 );
      //examine("jet4_btag_"                , jet4_btag_                );
      //examine("leadPSV_"                  , leadPSV_                  );
      //examine("subleadPSV_"               , subleadPSV_               );
      //examine("dipho_cosphi_"             , dipho_cosphi_             );
      //examine("dipho_rapidity_"           , dipho_rapidity_           );
      //examine("met_"                      , met_                      );
      //examine("dipho_pt_over_mass_"       , dipho_pt_over_mass_       );
      //examine("helicity_angle_"           , helicity_angle_           );
      //examine("chi2_value_"               , chi2_value_               );
      //examine("chi2_bjet_ptOverM_"        , chi2_bjet_ptOverM_        );
      //examine("chi2_bjet_eta_"            , chi2_bjet_eta_            );
      //examine("chi2_bjet_btagScores_"     , chi2_bjet_btagScores_     );
      //examine("chi2_wjet1_ptOverM_"       , chi2_wjet1_ptOverM_       );
      //examine("chi2_wjet1_eta_"           , chi2_wjet1_eta_           );
      //examine("chi2_wjet1_btagScores_"    , chi2_wjet1_btagScores_    );
      //examine("chi2_wjet2_ptOverM_"       , chi2_wjet2_ptOverM_       );
      //examine("chi2_wjet2_eta_"           , chi2_wjet2_eta_           );
      //examine("chi2_wjet2_btagScores_"    , chi2_wjet2_btagScores_    );
      //examine("chi2_wjets_deltaR_"        , chi2_wjets_deltaR_        );
      //examine("chi2_wboson_ptOverM_"      , chi2_wboson_ptOverM_      );
      //examine("chi2_wboson_eta_"          , chi2_wboson_eta_          );
      //examine("chi2_wboson_mass_"         , chi2_wboson_mass_         );
      //examine("chi2_wboson_deltaR_bjet_"  , chi2_wboson_deltaR_bjet_  );
      //examine("chi2_tbw_mass_"            , chi2_tbw_mass_            );
      //examine("chi2_tbw_ptOverM_"         , chi2_tbw_ptOverM_         );
      //examine("chi2_tbw_eta_"             , chi2_tbw_eta_             );
      //examine("chi2_tbw_deltaR_dipho_"    , chi2_tbw_deltaR_dipho_    );
      //examine("chi2_tprime_ptOverM_"      , chi2_tprime_ptOverM_      );
      //examine("chi2_tprime_eta_"          , chi2_tprime_eta_          );
      //examine("chi2_tprime_deltaR_tbw_"   , chi2_tprime_deltaR_tbw_   );
      //examine("chi2_tprime_deltaR_dipho_" , chi2_tprime_deltaR_dipho_ );
      //examine("tprime_pt_ratio_"          , tprime_pt_ratio_          );
      //examine("helicity_tprime_"          , helicity_tprime_          );
   }

   // report result
   printf("\n----------------------------------------------------------------------------------------------------\n\n");
   printf(">>> Start to report number of NaN values for each input variable:\n");
   for(t::iter=counter_manager.begin(); t::iter!=counter_manager.end(); t::iter++)
   {
       printf("%30s : ", iter->first.Data());
       cout << iter->second << endl;
   }
}
