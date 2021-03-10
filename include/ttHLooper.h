#include "TF1.h"
#include "TF2.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "ttH_process.h"
#include "GoldenJSON/goodrun.cc"

vector<Process*> generate_processes(TFile* f) {
  vector<Process*> v;
  v.push_back(new Process(f, "ttH"));
  v.push_back(new Process(f, "DY"));
  v.push_back(new Process(f, "DiPhoton"));
  v.push_back(new Process(f, "GammaJets"));
  v.push_back(new Process(f, "QCD"));
  v.push_back(new Process(f, "TTGG"));
  v.push_back(new Process(f, "TTGJets"));
  v.push_back(new Process(f, "VG"));
  v.push_back(new Process(f, "WJets"));
  v.push_back(new Process(f, "TTJets"));
  v.push_back(new Process(f, "Data"));
  v.push_back(new Process(f, "THQ"));
  v.push_back(new Process(f, "THW"));
  v.push_back(new Process(f, "TGamma"));
  v.push_back(new Process(f, "ggH"));
  v.push_back(new Process(f, "VBF"));
  v.push_back(new Process(f, "VH"));
  v.push_back(new Process(f, "GammaJets_Madgraph"));
  v.push_back(new Process(f, "QCD_GammaJets_imputed"));
  v.push_back(new Process(f, "TTZ"));
  v.push_back(new Process(f, "VV"));
  v.push_back(new Process(f, "tV"));
  v.push_back(new Process(f, "TT_FCNC_hut"));
  v.push_back(new Process(f, "TT_FCNC_hct"));
  v.push_back(new Process(f, "ST_FCNC_hut"));
  v.push_back(new Process(f, "ST_FCNC_hct"));
  v.push_back(new Process(f, "TTW"));
  v.push_back(new Process(f, "TprimeBToTH_M-600"));
  v.push_back(new Process(f, "TprimeBToTH_M-625"));
  v.push_back(new Process(f, "TprimeBToTH_M-650"));
  v.push_back(new Process(f, "TprimeBToTH_M-675"));
  v.push_back(new Process(f, "TprimeBToTH_M-700"));
  v.push_back(new Process(f, "TprimeBToTH_M-800"));
  v.push_back(new Process(f, "TprimeBToTH_M-900"));
  v.push_back(new Process(f, "TprimeBToTH_M-1000"));
  v.push_back(new Process(f, "TprimeBToTH_M-1100"));
  v.push_back(new Process(f, "TprimeBToTH_M-1200"));
 //v.push_back(new Process

  return v;
}

void add_variables(vector<Process*> v, TString tag, vector<TString> syst_labels = {""}) {
  bool hadronic = tag.Contains("Hadronic");
  bool leptonic = tag.Contains("Leptonic");
  if (!hadronic && !leptonic)
    cout << "Tag name not matched to either hadronic/leptonic" << endl;

  for (unsigned int j = 0; j < syst_labels.size(); j++) {
      for (int i = 0; i < v.size(); i++) {
        //v[i]->add_histogram("h" + syst_labels[j] + "mc_mva_score_tt_v2", 50, -1.0, 1.0);
        //v[i]->add_histogram("h" + syst_labels[j] + "mc_mva_score_st_v2", 50, -1.0, 1.0);
        //v[i]->add_histogram("h" + syst_labels[j] + "mc_mva_score_tt_v4", 50, -1.0, 1.0);
        //v[i]->add_histogram("h" + syst_labels[j] + "mc_mva_score_st_v4", 50, -1.0, 1.0);
        v[i]->add_histogram("h" + syst_labels[j] + "Mass", 100, 0, 250);
        v[i]->add_histogram("h" + syst_labels[j] + "Mass_v2", 50, 0, 250);
        v[i]->add_histogram("h" + syst_labels[j] + "mass_wboson_cov" , 40, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "mass_top_cov"    , 36, 0, 360);
        v[i]->add_histogram("h" + syst_labels[j] + "mass_tprime_cov" , 50, 0, 1500);
        v[i]->add_histogram("h" + syst_labels[j] + "mass_tprime_tilde" , 50, 0, 1500);
        v[i]->add_histogram("h" + syst_labels[j] + "cov_chi2_value"  , 50, 0, 100);
        //v[i]->add_histogram("h" + syst_labels[j] + "Mass_PassPtToM", 40, 100, 180);
        //v[i]->add_histogram("h" + syst_labels[j] + "Mass_FailPtToM", 40, 100, 180);
        //v[i]->add_histogram("h" + syst_labels[j] + "Mass_PassPtToM_AfterBDTCut", 40, 100, 180);
        //v[i]->add_histogram("h" + syst_labels[j] + "Mass_FailPtToM_AfterBDTCut", 40, 100, 180);
        //v[i]->add_histogram("h" + syst_labels[j] + "MassAN", 80, 100, 180);
        v[i]->add_histogram("h" + syst_labels[j] + "Rapidity", 25, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "DiphotonSumPt", 25, 0, 1000);
        v[i]->add_histogram("h" + syst_labels[j] + "DiphotonCosPhi", 25, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "NVtx", 25, 0, 75);
        v[i]->add_histogram("h" + syst_labels[j] + "MetPt", 25, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "HT", 50, 0, 5000);
        v[i]->add_histogram("h" + syst_labels[j] + "MT", 50, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "DiphotonMassResolution", 250, 0, 0.1);
        //v[i]->add_histogram("h" + syst_labels[j] + "DiphotonMassResolutionLowMVA", 25, 0, 0.1);
        //v[i]->add_histogram("h" + syst_labels[j] + "DiphotonMassResolutionMedMVA", 25, 0, 0.1);
        //v[i]->add_histogram("h" + syst_labels[j] + "DiphotonMassResolutionHighMVA", 25, 0, 0.1);
        //v[i]->add_histogram("h" + syst_labels[j] + "MassTop1", 100, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "MassTop2", 100, 0, 500);

        //v[i]->add_histogram("h" + syst_labels[j] + "MassTop_Hq_1", 100, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "MassTop_Hq_2", 100, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "MassTop_qqq_1", 100, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "MassTop_qqq_2", 100, 0, 500);

        //v[i]->add_histogram("h" + syst_labels[j] + "GJet_BDT", 100, 0, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "NJets", 16, -0.5, 15.5);
        v[i]->add_histogram("h" + syst_labels[j] + "NbLoose", 16, -0.5, 15.5);
        v[i]->add_histogram("h" + syst_labels[j] + "NbMedium", 16, -0.5, 15.5);
        v[i]->add_histogram("h" + syst_labels[j] + "NbTight", 16, -0.5, 15.5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet1pT", 25, 0, 500);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet1Eta", 25, -5, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet2pT", 25, 0, 500);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet2Eta", 25, -5, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet3pT", 25, 0, 500);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet3Eta", 25, -5, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet4pT", 25, 0, 500);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet4Eta", 25, -5, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet5pT", 25, 0, 500);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet5Eta", 25, -5, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet6pT", 25, 0, 500);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet6Eta", 25, -5, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet1BTag", 25, 0, 1);   
        v[i]->add_histogram("h" + syst_labels[j] + "Jet2BTag", 25, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet3BTag", 25, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "Jet4BTag", 25, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "Jet5BTag", 25, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "Jet6BTag", 25, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "Jet1CTag", 25, 0, 1);   
        v[i]->add_histogram("h" + syst_labels[j] + "Jet2CTag", 25, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "Jet3CTag", 25, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "Jet4CTag", 25, 0, 1);  

        //v[i]->add_histogram("h" + syst_labels[j] + "bJet1pT", 25, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "bJet1Eta", 25, -3, 3);
        //v[i]->add_histogram("h" + syst_labels[j] + "bJet2pT", 25, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "bJet2Eta", 50, -3, 3);    

        v[i]->add_histogram("h" + syst_labels[j] + "PtHiggs", 25, 0, 400);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonDeltaR", 25, 0, 6); 
        v[i]->add_histogram("h" + syst_labels[j] + "DiphotonPtOverMass", 30, 0, 3);

        //v[i]->add_histogram("h" + syst_labels[j] + "MinDrDiphoJet", 25, 0, 6);
        //v[i]->add_histogram("h" + syst_labels[j] + "DijetClosestWMass", 25, 0, 50);
        //v[i]->add_histogram("h" + syst_labels[j] + "DijetMass", 50, 0, 500);
        //v[i]->add_histogram("h" + syst_labels[j] + "DeltaRDiphoW", 25, 0, 6);
        //v[i]->add_histogram("h" + syst_labels[j] + "DeltaRDiphoLep", 25, 0, 6);
        //v[i]->add_histogram("h" + syst_labels[j] + "DeltaRDiphoTop", 25, 0, 6);
        //v[i]->add_histogram("h" + syst_labels[j] + "TopPt", 25, 0, 400);
        //v[i]->add_histogram("h" + syst_labels[j] + "TopMass", 25, 0, 400);
        //v[i]->add_histogram("h" + syst_labels[j] + "TopEta", 25, -3, 3);

        //v[i]->add_histogram("h" + syst_labels[j] + "LeadMinDr", 25, 0, 6);
        //v[i]->add_histogram("h" + syst_labels[j] + "SubleadMinDr", 25, 0, 6);
        
        v[i]->add_histogram("h" + syst_labels[j] + "AbsCosHelicity", 10, 0, 1);

        // Leading photon
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadPt", 25, 0, 350);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadEt", 25, 0, 350);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadEta", 25, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadPhi", 25, -3.142, 3.142);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadSigmaIEtaIEta", 50, 0, 0.05);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadHOverE", 25, 0, 0.1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadR9", 25, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadIDMVA", 20, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadPToM", 50, 0, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadSigmaEOverE", 100, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadPtGen", 25, 0, 350);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonLeadPixelSeed", 2, -0.5, 1.5);

        // Subleading photon
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadPt", 25, 0, 350);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadEt", 25, 0, 350);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadEta", 25, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadPhi", 25, -3.142, 3.142);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadSigmaIEtaIEta", 50, 0, 0.05);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadHOverE", 25, 0, 0.1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadR9", 25, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadIDMVA", 20, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadPToM", 50, 0, 5);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadSigmaEOverE", 100, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadPtGen", 25, 0, 350);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonSubleadPixelSeed", 2, -0.5, 1.5);


        // Min/Max ID photon
        //v[i]->add_histogram("h" + syst_labels[j] + "MinIDPhotonPt", 25, 0, 350);
        //v[i]->add_histogram("h" + syst_labels[j] + "MinIDPhotonEta", 25, -3, 3);
        //v[i]->add_histogram("h" + syst_labels[j] + "MaxIDPhotonPt", 25, 0, 350);
        //v[i]->add_histogram("h" + syst_labels[j] + "MaxIDPhotonEta", 25, -3, 3);

        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonPtRatio", 50, 0.0, 2.0);
        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonDeltaRGen", 50, 0, 0.15);

        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA", 50, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf", 25, 0, 8);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_ttZ", 25, 0, 12);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_ttZ_v2", 18, 0, 10);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_ttZ_v3", 12, 0, 10);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_ttZ_v4", 10, 0, 10);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_ttZ_v5", 15, 0, 10);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_bounded", 25, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "tthMVA_RunII_transf_bounded_v2", 12, 0, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "MVA_transf", 15, 0, 10);        

        v[i]->add_histogram("h" + syst_labels[j] + "MaxBTagSum", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "SecondMaxBTagSum", 50, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "MaxBTag", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "SecondMaxBTag", 50, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "MaxCTag", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "SecondMaxCTag", 50, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "MaxCvsL", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "SecondMaxCvsL", 50, 0, 1);  
        v[i]->add_histogram("h" + syst_labels[j] + "MaxCvsB", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "SecondMaxCvsB", 50, 0, 1);  

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA", 10, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA", 10, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_fine", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_fine", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_entries", 10, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_entries", 10, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_fine_entries", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_fine_entries", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_coarse", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_coarse", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_coarse_entries", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_coarse_entries", 5, -1, 1);

        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets5+", 10, -1, 1);
        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets5+", 10, -1, 1);
        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets7+", 10, -1, 1);
        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets7+", 10, -1, 1);

        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_coarse_0b", 5, -1, 1);
        //v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_coarse_0b", 5, -1, 1);
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets", 30, -1, 1, 16, -0.5, 15.5); 
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets", 30, -1, 1, 16, -0.5, 15.5);
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets_entries", 30, -1, 1, 16, -0.5, 15.5);
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets_entries", 30, -1, 1, 16, -0.5, 15.5); 
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NTightLeps", 30, -1, 1, 3, -0.5, 2.5);
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NTightLeps", 30, -1, 1, 3, -0.5, 2.5);
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NTightLeps_entries", 30, -1, 1, 3, -0.5, 2.5);
        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NTightLeps_entries", 30, -1, 1, 3, -0.5, 2.5);

        //v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_MinIDMVA", 20, -1, 1, 20, -1, 1);

        /*
        // Correlation with IDMVA
        v[i]->add_histogram("h" + syst_labels[j] + "FakePhotonIDMVA", 40, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA", 40, -1, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_Barrel_LowPt", 40, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_Barrel_HighPt", 40, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_Endcap_LowPt", 40, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_Endcap_HighPt", 40, -1, 1);

        v[i]->add_2D_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_NJets", 20, -1, 1, 10, -0.5, 9.5);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_MaxBTag", 20, -1, 1, 20, 0, 1);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_2ndMaxBTag", 20, -1, 1, 20, 0, 1);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA_NJets", 20, -1, 1, 10, -0.5, 9.5);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA_MaxBTag", 20, -1, 1, 20, 0, 1);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA_2ndMaxBTag", 20, -1, 1, 20, 0, 1);

        v[i]->add_2D_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_Pt", 20, -1, 1, 20, 0, 300);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA_Pt", 20, -1, 1, 20, 0, 300);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_Eta", 20, -1, 1, 20, 0, 2.4);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA_Eta", 20, -1, 1, 20, 0, 2.4);

        v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonLeadIDMVA_LeadPt", 20, -1, 1, 20, 0, 300);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonSubleadIDMVA_SubleadPt", 20, -1, 1, 20, 0, 300);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonLeadIDMVA_LeadEta", 20, -1, 1, 20, 0, 2.4);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PhotonSubleadIDMVA_SubleadEta", 20, -1, 1, 20, 0, 2.4);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "FakePhotonIDMVA_DiPhotonPt", 20, -1, 1, 20, 0, 300);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "PromptPhotonIDMVA_DiPhotonPt", 20, -1, 1, 20, 0, 300);

        v[i]->add_2D_histogram("h" + syst_labels[j] + "BDT_LeadPtoM", 20, 0, 1, 20, 0, 2);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "BDT_SubleadPtoM", 20, 0, 1, 20, 0, 2);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "Mass_LeadPtoM", 20, 100, 180, 20, 0, 2);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "Mass_SubleadPtoM", 20, 100, 180, 20, 0, 2);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "Mass_LeadPtoM_afterBDTCut", 20, 100, 180, 20, 0, 2);
        v[i]->add_2D_histogram("h" + syst_labels[j] + "Mass_SubleadPtoM_afterBDTCut", 20, 100, 180, 20, 0, 2);

        v[i]->add_2D_histogram("h" + syst_labels[j] + "Mass_MVAScore", 20, 100, 180, 20, 0, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets2", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets2", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets3", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets3", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMaxIDMVA_NJets4+", 30, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_NJets4+", 30, -1, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "DiphoMVA", 25, -1, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_prompt", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_elec", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_fake", 5, -1, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_prompt", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_elec", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_fake", 8, 0, 200);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_prompt", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_elec", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_fake", 10, -3, 3);

        v[i]->add_histogram("h" + syst_labels[j] + "HadronicMVA", 20, 0, 1.0);
        v[i]->add_histogram("h" + syst_labels[j] + "LeptonicMVA", 20, 0, 1.0);

        v[i]->add_histogram("h" + syst_labels[j] + "HadronicMVA_coarse", 10, 0.0, 1.0);
        v[i]->add_histogram("h" + syst_labels[j] + "LeptonicMVA_coarse", 10, 0.0, 1.0);

        v[i]->add_histogram("h" + syst_labels[j] + "HadronicMVA_fine", 50, 0.0, 1.0);
        v[i]->add_histogram("h" + syst_labels[j] + "LeptonicMVA_fine", 50, 0.0, 1.0);

        v[i]->add_histogram("h" + syst_labels[j] + "LeptonPt", 25, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "LeptonEta", 25, -3, 3);

        v[i]->add_histogram("h" + syst_labels[j] + "MuonMiniIsolation", 10, 0, 0.25);

        v[i]->add_histogram("h" + syst_labels[j] + "PixelSeed", 2, -0.5, 1.5);
        v[i]->add_histogram("h" + syst_labels[j] + "PixelSeedEB", 2, -0.5, 1.5);
        v[i]->add_histogram("h" + syst_labels[j] + "PixelSeedEE", 2, -0.5, 1.5);


        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_passPSV", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_failPSV", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_passEVeto", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_failEVeto", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_passBothVeto", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonMinIDMVA_failBothVeto", 5, -1, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_passPSV", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_failPSV", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_passEVeto", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_failEVeto", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_passBothVeto", 5, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonIDMVA_failBothVeto", 5, -1, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_passPSV", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_failPSV", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_passEVeto", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_failEVeto", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_passBothVeto", 8, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonPt_failBothVeto", 8, 0, 200);

        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_passPSV", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_failPSV", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_passEVeto", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_failEVeto", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_passBothVeto", 10, -3, 3);
        v[i]->add_histogram("h" + syst_labels[j] + "PhotonEta_failBothVeto", 10, -3, 3); 
        */

        v[i]->add_histogram("h" + syst_labels[j] + "LeptonPt", 25, 0, 200);
        v[i]->add_histogram("h" + syst_labels[j] + "LeptonEta", 25, -3, 3);

        v[i]->add_histogram("h" + syst_labels[j] + "MuonMiniIsolation", 10, 0, 0.25);

        v[i]->add_histogram("h" + syst_labels[j] + "TopTagger_score", 20, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "DNNScore_fcnc_tt", 20, -1, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "DNNScore_fcnc_st", 20, -1, 1);
        //v[i]->add_histogram("h" + syst_labels[j] + "TopTagger_topMass", 40, 0, 400);
        //v[i]->add_histogram("h" + syst_labels[j] + "TopTagger_WMass", 20, 0, 200);

        v[i]->add_histogram("h" + syst_labels[j] + "NLepLoose", 3, -0.5, 2.5);
        v[i]->add_histogram("h" + syst_labels[j] + "NLepMedium", 3, -0.5, 2.5);
        v[i]->add_histogram("h" + syst_labels[j] + "NLepTight", 3, -0.5, 2.5);

        v[i]->add_histogram("h" + syst_labels[j] + "DNNScore_ttH_vs_dipho", 50, 0, 1);
        v[i]->add_histogram("h" + syst_labels[j] + "DNNScore_ttH_vs_ttGG", 50, 0, 1);

        v[i]->add_histogram("h" + syst_labels[j] + "Rho", 50, 0, 100);

        //---------------//
        v[i]->add_histogram("h" + syst_labels[j] + "Rho", 50, 0, 100);

      }
  }
}

vector<TH1D*> generate_1Dhist_vector(TString name, int length, int nBins, float xLow, float xHigh) {
  vector<TH1D*> hVec(length);
  for (unsigned int i = 0; i < hVec.size(); i++) {
    hVec[i] = new TH1D(name + "_" + to_string(i), "", nBins, xLow, xHigh);
    hVec[i]->Sumw2();
  }
  return hVec;
}

int categorize_process(TString currentFileTitle, int genPhotonId = -1) {
  if (currentFileTitle.Contains("ttHJet") || currentFileTitle.Contains("ttHToGG")) // && currentFileTitle.Contains("M125"))
    return 0;
  else if (currentFileTitle.Contains("DY"))
    return 1;
  else if (currentFileTitle.Contains("DiPhoton"))
    return 2;
  else if (currentFileTitle.Contains("GJet_Pt"))
    return 3;
  //else if (currentFileTitle.Contains("GGJet") && !currentFileTitle.Contains("TTG"))
  //  return 4;
  else if (currentFileTitle.Contains("QCD"))
    return 4;

  else if (currentFileTitle.Contains("TTGG") || currentFileTitle.Contains("TTGJets") || (currentFileTitle.Contains("TTJets")) || currentFileTitle.Contains("TTTo2L2Nu") || currentFileTitle.Contains("TTToSemiLeptonic")) {
    if (genPhotonId != -1) {
      if (genPhotonId == 2) // pp
        return 5;
      else if (genPhotonId == 1) // pf
        return 6;
      else if (genPhotonId == 0) // ff
        return 9;
    }
    else {
      if (currentFileTitle.Contains("TTGG"))
      return 5;
      else if (currentFileTitle.Contains("TTGJets"))
	return 6;
      else if ((currentFileTitle.Contains("TTJets")) || currentFileTitle.Contains("TTTo2L2Nu") || currentFileTitle.Contains("TTToSemiLeptonic"))
      return 9;
    }
  }

  else if (currentFileTitle.Contains("WG") || currentFileTitle.Contains("ZG"))
    return 7;
  else if (currentFileTitle.Contains("WJets") && !currentFileTitle.Contains("TTW"))
    return 8;
  else if (currentFileTitle.Contains("DoubleEG") || currentFileTitle.Contains("EGamma"))
    return 10;
  else if (currentFileTitle.Contains("THQ"))
    return 11;
  else if (currentFileTitle.Contains("THW"))
    return 12;
  else if (currentFileTitle.Contains("TGJets"))
    return 13;
  else if (currentFileTitle.Contains("GluGluHToGG"))
    return 14;
  else if (currentFileTitle.Contains("VBF"))
    return 15;
  else if (currentFileTitle.Contains("VHToGG"))
    return 16;
  else if (currentFileTitle.Contains("GJets_HT"))
    return 17;
  // 18 is imputed QCD/GJets
  else if (currentFileTitle.Contains("TTZ"))
    return 19;
  else if (currentFileTitle.Contains("WW") || currentFileTitle.Contains("WZ") || currentFileTitle.Contains("ZZ"))
    return 20;
  else if (currentFileTitle.Contains("ST_tW") || currentFileTitle.Contains("tZq"))
    return 21;
  else if ((currentFileTitle.Contains("TT_FCNC") && currentFileTitle.Contains("hut") ) || (currentFileTitle.Contains("FCNC_private_TT") && currentFileTitle.Contains("HUT") ))
    return 22;
  else if ((currentFileTitle.Contains("TT_FCNC") && currentFileTitle.Contains("hct") ) || (currentFileTitle.Contains("FCNC_private_TT") && currentFileTitle.Contains("HCT") ))
    return 23;
  else if ((currentFileTitle.Contains("ST_FCNC") && currentFileTitle.Contains("hut") ) || (currentFileTitle.Contains("FCNC_private_ST") && currentFileTitle.Contains("HUT") ))
    return 24;
  else if ((currentFileTitle.Contains("ST_FCNC") && currentFileTitle.Contains("hct") ) || (currentFileTitle.Contains("FCNC_private_ST") && currentFileTitle.Contains("HCT") ))
    return 25;
  else if (currentFileTitle.Contains("TTW"))
    return 26;
  else if (currentFileTitle.Contains("TprimeBToTH_M-600"))
    return 27;
  else if (currentFileTitle.Contains("TprimeBToTH_M-625"))
    return 28;
  else if (currentFileTitle.Contains("TprimeBToTH_M-650"))
    return 29;
  else if (currentFileTitle.Contains("TprimeBToTH_M-675"))
    return 30;
  else if (currentFileTitle.Contains("TprimeBToTH_M-700"))
    return 31;
  else if (currentFileTitle.Contains("TprimeBToTH_M-800"))
    return 32;
  else if (currentFileTitle.Contains("TprimeBToTH_M-900"))
    return 33;
  else if (currentFileTitle.Contains("TprimeBToTH_M-1000"))
    return 34;
  else if (currentFileTitle.Contains("TprimeBToTH_M-1100"))
    return 35;
  else if (currentFileTitle.Contains("TprimeBToTH_M-1200"))
    return 36;
  else {
    //cout << "File does not fit into one of the background categories." << endl;
    cout << "File does not fit into one of the background categories: " << currentFileTitle << endl;

    return -1;
  }
}

const std::vector<TString> independent_systematic_collections =
{
    "",
    /*
    "MvaShiftDown01sigma",
    "SigmaEOverEShiftDown01sigma",
    "MaterialCentralBarrelDown01sigma",
    "MaterialOuterBarrelDown01sigma",
    "MaterialForwardDown01sigma",
    "FNUFEBDown01sigma",
    "FNUFEEDown01sigma",
    "MCScaleGain6EBDown01sigma",
    "MCScaleGain1EBDown01sigma",
    "ShowerShapeHighR9EBDown01sigma",
    "MCScaleHighR9EBDown01sigma",
    "MCSmearHighR9EBRhoDown01sigma",
    "MCSmearHighR9EBPhiDown01sigma",
    "ShowerShapeHighR9EEDown01sigma",
    "MCScaleHighR9EEDown01sigma",
    "MCSmearHighR9EERhoDown01sigma",
    "MCSmearHighR9EEPhiDown01sigma",
    "ShowerShapeLowR9EBDown01sigma",
    "MCScaleLowR9EBDown01sigma",
    "MCSmearLowR9EBRhoDown01sigma",
    "MCSmearLowR9EBPhiDown01sigma",
    "ShowerShapeLowR9EEDown01sigma",
    "MCScaleLowR9EEDown01sigma",
    "MCSmearLowR9EERhoDown01sigma",
    "MCSmearLowR9EEPhiDown01sigma",
    "JECDown01sigma",
    "JERDown01sigma",
    "PUJIDShiftDown01sigma",
    "metJecUncertaintyDown01sigma",
    "metJerUncertaintyDown01sigma",
    "metPhoUncertaintyDown01sigma",
    "metUncUncertaintyDown01sigma",
    "MvaShiftUp01sigma",
    "SigmaEOverEShiftUp01sigma",
    "MaterialCentralBarrelUp01sigma",
    "MaterialOuterBarrelUp01sigma",
    "MaterialForwardUp01sigma",
    "FNUFEBUp01sigma",
    "FNUFEEUp01sigma",
    "MCScaleGain6EBUp01sigma",
    "MCScaleGain1EBUp01sigma",
    "ShowerShapeHighR9EBUp01sigma",
    "MCScaleHighR9EBUp01sigma",
    "MCSmearHighR9EBRhoUp01sigma",
    "MCSmearHighR9EBPhiUp01sigma",
    "ShowerShapeHighR9EEUp01sigma",
    "MCScaleHighR9EEUp01sigma",
    "MCSmearHighR9EERhoUp01sigma",
    "MCSmearHighR9EEPhiUp01sigma",
    "ShowerShapeLowR9EBUp01sigma",
    "MCScaleLowR9EBUp01sigma",
    "MCSmearLowR9EBRhoUp01sigma",
    "MCSmearLowR9EBPhiUp01sigma",
    "ShowerShapeLowR9EEUp01sigma",
    "MCScaleLowR9EEUp01sigma",
    "MCSmearLowR9EERhoUp01sigma",
    "MCSmearLowR9EEPhiUp01sigma",
    "JECUp01sigma",
    "JERUp01sigma",
    "PUJIDShiftUp01sigma",
    "metJecUncertaintyUp01sigma",
    "metJerUncertaintyUp01sigma",
    "metPhoUncertaintyUp01sigma",
    "metUncUncertaintyUp01sigma", 
    */
    "JECDown01sigma",
    "JECUp01sigma",
    "MvaShiftDown01sigma",
    "MvaShiftUp01sigma",
    "MCSmearHighR9EBPhiDown01sigma",
    "MCSmearHighR9EBPhiUp01sigma",
    "MCSmearLowR9EBPhiDown01sigma",
    "MCSmearLowR9EBPhiUp01sigma",
    "JERDown01sigma",
    "JERUp01sigma",
};

const std::vector<TString> weight_systematics = 
{
    /*
    "UnmatchedPUWeightDown01sigma",
    "MvaLinearSystDown01sigma",
    "LooseMvaSFDown01sigma",
    "PreselSFDown01sigma",
    "electronVetoSFDown01sigma",
    "TriggerWeightDown01sigma",
    "FracRVWeightDown01sigma",
    "ElectronWeightDown01sigma",
    "JetBTagCutWeightDown01sigma",
    "JetBTagReshapeWeightDown01sigma",
    "UnmatchedPUWeightUp01sigma",
    "MvaLinearSystUp01sigma",
    "LooseMvaSFUp01sigma",
    "PreselSFUp01sigma",
    "electronVetoSFUp01sigma",
    "TriggerWeightUp01sigma",
    "FracRVWeightUp01sigma",
    "ElectronWeightUp01sigma",
    "JetBTagCutWeightUp01sigma",
    "JetBTagReshapeWeightUp01sigma",
    */
    "JetBTagReshapeWeightDown01sigma",
    "JetBTagReshapeWeightUp01sigma",
    "PreselSFDown01sigma",
    "PreselSFUp01sigma",
    "electronVetoSFDown01sigma",
    "electronVetoSFUp01sigma",
};

int multiclassifier_label(TString currentFileTitle, int genPhotonId, bool fcnc = false) {
  if (fcnc) {
    if (currentFileTitle.Contains("FCNC")) return 0; // signal
    else if (currentFileTitle.Contains("ttHJetToGG") || currentFileTitle.Contains("ttHToGG") || currentFileTitle.Contains("THQ") || currentFileTitle.Contains("THW") || currentFileTitle.Contains("VBF") || currentFileTitle.Contains("GluGluHToGG") || currentFileTitle.Contains("VHToGG")) return 1; // resonant bkg
    else return 2; // non-resonant bkg
  }

  if (currentFileTitle.Contains("ttHJet"))
    return 0;
  else if (currentFileTitle.Contains("TTGG") || currentFileTitle.Contains("TTGJets") || currentFileTitle.Contains("TTJets") || currentFileTitle.Contains("TTTo2L2Nu") || currentFileTitle.Contains("TTToSemiLeptonic")) {
    if (genPhotonId == 2) // pp
      return 1;
    else if (genPhotonId == 1) // pf
      return 2;
    else if (genPhotonId == 0) // ff
      return 3;
  }
  else if (currentFileTitle.Contains("DoubleEG") || currentFileTitle.Contains("EGamma")) {
    return -1;
  }
  else
    return 4;
}

const double barrel_eta = 1.479;
int categorize_photon_locations(double eta_lead, double eta_sublead) {
  if (abs(eta_lead) < barrel_eta && abs(eta_sublead) < barrel_eta)
    return 0;
  else if (abs(eta_lead) < barrel_eta || abs(eta_sublead) < barrel_eta)
    return 1;
  else if (abs(eta_lead) > barrel_eta && abs(eta_sublead) > barrel_eta)
    return 2;
  else {
    cout << "Shouldn't be here" << endl;
    return -999;
  }
}

bool has_ttX_overlap(TString currentFileTitle, int lead_prompt, int sublead_prompt) {
  if (!(currentFileTitle.Contains("TTJets") || currentFileTitle.Contains("TTGJets"))) {
    return false;
  }
  else if (lead_prompt != 0 && sublead_prompt != 0)
    return false;
  return true;
}

bool has_simple_vgamma_overlap(TString currentFileTitle, int genPhotonId) {
  if (!(currentFileTitle.Contains("DYJetsToLL_M-50")))
    return false;
  else if (genPhotonId == 2 || genPhotonId == 1) // don't take PP,PF events from DY sample now that we have Z+gamma for all 3 years
    return true;
}

bool has_simple_qcd_overlap(TString currentFileTitle, int genPhotonId) {
  if (!(currentFileTitle.Contains("QCD") || currentFileTitle.Contains("GJet_Pt") || currentFileTitle.Contains("GJets_HT"))) {
    return false;
  }
  else if (currentFileTitle.Contains("GJet_Pt") || currentFileTitle.Contains("GJets_HT")) {
    if (genPhotonId == 2) // PP
      return true;
  }
  else if (currentFileTitle.Contains("QCD")) {
    if (genPhotonId == 1 || genPhotonId == 2) // FP, PP
      return true;
  }
  return false;
}

bool has_std_overlaps(TString currentFileTitle, int lead_prompt, int sublead_prompt, int genPhotonId) {
  if (has_ttX_overlap(currentFileTitle, lead_prompt, sublead_prompt))
    return true;
  if (has_simple_vgamma_overlap(currentFileTitle, genPhotonId))
    return true;
  if (has_simple_qcd_overlap(currentFileTitle, genPhotonId))
    return true;
  return false;
}

const TString gjet_bdt_file = "../MVAs/GJetReweight_1617_GJetReweight_CombineSamples_bdt.xml";
const double gjet_normalization = 188341.868812 / 345058.328323; // scale factor to make reweighted (Pythia + MadGraph) yield match MadGraph yield. First number taken from hMass_GammaJets_Madgraph->IntegralAndError(1,80,err) in ttHHadronic_GJet_Reweight_Preselection__histogramsAll.root and second number taken from hMass_GammaJets->IntegralAndError(1,80,err) in ttHHadronic_GJet_Reweight_Preselection_wWeights__histogramsAll.root

// 2017-only results
//const double qcd_factor_2017 = 2.6302765969200204; 
//const double gjets_factor_2017 = 1.9817470714424696; 
//const double diphoton_factor_2017 = 1.1645911726186993; 
const double qcd_factor_2017 = 2.34;
const double gjets_factor_2017 = 1.76;
const double diphoton_factor_2017 = 1.26;

const vector<double> qcd_factor_Njets_2017 = {2.2940045704500824, 1.7784105604582408, 1.7659539814519811}; 
const vector<double> gjets_factor_Njets_2017 = {1.945909958008661, 2.865798441193098, 3.6723528776911034}; 
const vector<double> diphoton_factor_Njets_2017 = {1.195047195435529, 0.9420013195895437, 0.8631697452232668}; 

// 2016+2017 results
const double qcd_factor = 2.399144178915237;
const double gjets_factor = 1.7532994814392295;
const double diphoton_factor = 1.1389466592137074;
const vector<double> qcd_factor_Njets = {2.357160350951758, 2.0445853297833256, 1.3099669292651388};
const vector<double> gjets_factor_Njets = {1.660622209083969, 2.234460138056228, 3.227084762144053};
const vector<double> diphoton_factor_Njets = {1.2072907358168674, 1.0503124421392787, 0.7338075364880837};

double qcdX_njets_bin(int n_jets) {
  if (n_jets == 2)
    return 0;
  else if (n_jets == 3)
    return 1;
  else if (n_jets >= 4) 
    return 2;
  else
    return 0;
}

double qcdX_factor(TString currentFileTitle, TString qcd_scale, int n_jets) {
  if (qcd_scale == "inclusive_NJets") {
    if (currentFileTitle.Contains("GJet_Pt") || currentFileTitle.Contains("GJets_HT")) 
      return gjets_factor_2017; 
    else if (currentFileTitle.Contains("QCD"))
      return qcd_factor_2017; 
    else if (currentFileTitle.Contains("DiPhotonJetsBox"))
      return diphoton_factor_2017; 
    else
      return 1.0;
  }
  else if (qcd_scale == "binned_NJets") {
    int jet_idx = qcdX_njets_bin(n_jets);
    if (currentFileTitle.Contains("GJet_Pt") || currentFileTitle.Contains("GJets_HT"))
      return gjets_factor_Njets[jet_idx];
    else if (currentFileTitle.Contains("QCD"))
      return qcd_factor_Njets[jet_idx];
    else if (currentFileTitle.Contains("DiPhotonJetsBox"))
      return diphoton_factor_Njets[jet_idx];  
    else
      return 1.0; 
  }
}

/* These are for p_T/m_gg > 0.2 
const double diphoton_factor_hadronic_runII = 1.147982488785183;
const double gjets_factor_hadronic_runII    = 1.7587831077271554;
const double qcd_factor_hadronic_runII      = 2.290911314017982;

const double qcd_gjets_impute_factor_hadronic_runII = 0.9383634106686037;
const double diphoton_impute_factor_hadronic_runII  = 1.1823424964786557;
*/
// No cut on p_T/m_gg
// v1.6
//const double diphoton_factor_hadronic_runII = 1.233076855887245;
//const double gjets_factor_hadronic_runII    = 2.081601597627392;
//const double qcd_factor_hadronic_runII      = 2.5892320260734283;

//v3.10
const double diphoton_factor_hadronic_runII = 1.3362705187667576;//2.2971182909603067;
const double gjets_factor_hadronic_runII    = 2.0113788480528183;
const double qcd_factor_hadronic_runII      = 2.2971182909603067; 

//v1.5
//const double qcd_gjets_impute_factor_hadronic_runII = 0.9433630221924071; 
//const double diphoton_impute_factor_hadronic_runII  = 1.24575175003913; 
//v1.6
//const double qcd_gjets_impute_factor_hadronic_runII = 0.9537308742404281;
//const double diphoton_impute_factor_hadronic_runII  = 1.289449696556433;

//v3.10
const double qcd_gjets_impute_factor_hadronic_runII = 1.0462238864596276;
const double diphoton_impute_factor_hadronic_runII  = 1.3852459996672792;

const double diphoton_factor_leptonic_runII = 1.919798;
const double gjets_factor_leptonic_runII    = 1.919798;
const double qcd_factor_leptonic_runII      = 1.00;

const double qcd_gjets_impute_factor_leptonic_runII = 0.02350297991807451;
const double diphoton_impute_factor_leptonic_runII  = 1.0;

const double diphoton_nTightLep0_prob = 0.4865;
const double diphoton_nTightLep1_prob = 0.4791;
const double diphoton_nTightLep2_prob = 0.0344;

const double br_tToHq_assumed = 0.1441; // width(t->Hq|kappa_{Hqt}=1) / width^{SM}_{total} (values taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopFCNCxsection)
const double br_tToHc_limit = 0.0011; // from p34 of https://arxiv.org/pdf/1812.11568.pdf
const double br_tToHu_limit = 0.0012; // ""

double scale_fcnc(TString currentFileTitle) {
  double weight = 1.;
  if (currentFileTitle.Contains("leptonic") && currentFileTitle.Contains("FCNC"))
    weight = weight * 1.0/1.527;

  if (currentFileTitle.Contains("eta_hut"))
    weight = weight * br_tToHu_limit / br_tToHq_assumed;
  else if (currentFileTitle.Contains("eta_hct"))
    weight = weight * br_tToHc_limit / br_tToHq_assumed;

  return weight; 
}

double scale_fcnc_to_atlas_limit(TString currentFileTitle) {
  if (currentFileTitle.Contains("eta_hut"))
    return br_tToHu_limit / br_tToHq_assumed;
  else if (currentFileTitle.Contains("eta_hct"))
    return br_tToHc_limit / br_tToHq_assumed;
  return 1.0;
}

double scale_bkg(TString currentFileTitle, TString bkg_options, int processId, TString channel, bool fcnc = false) {
  // Better to scale mass points in prep.py
  //if (fcnc && currentFileTitle.Contains("ttHJet"))
  //  return (1.0/7.0); // we use 6 ttH mass points in training, so scale by a factor of 1/6
  
  if (bkg_options == "none")
    return 1.0;

  if (channel == "Hadronic") {
    if (bkg_options == "scale_diphoton") {
      if (currentFileTitle.Contains("GJets_HT"))
	return gjets_factor_hadronic_runII;
      else if (currentFileTitle.Contains("QCD"))
	return qcd_factor_hadronic_runII;
      else if (currentFileTitle.Contains("DiPhotonJetsBox"))
	return diphoton_factor_hadronic_runII;
      else
	return 1.0;
    }

    else if (bkg_options == "impute") {
      if ((currentFileTitle.Contains("EGamma") || currentFileTitle.Contains("DoubleEG")) && processId == 18)
	return qcd_gjets_impute_factor_hadronic_runII;
      else if (currentFileTitle.Contains("DiPhotonJetsBox"))
	return diphoton_impute_factor_hadronic_runII;
      else
	return 1.0;
    }

    else if (bkg_options == "impute_no_scale") 
      return 1.0;
  }

  else if (channel == "Leptonic") {
    if (bkg_options == "old_vgamma")
      return 1.0;
    else if (bkg_options == "scale_mc") {
      if (currentFileTitle.Contains("GJets_HT"))
        return gjets_factor_leptonic_runII;
      else if (currentFileTitle.Contains("QCD"))
        return qcd_factor_leptonic_runII;
      else if (currentFileTitle.Contains("DiPhotonJetsBox"))
        return diphoton_factor_leptonic_runII;
      else
	return 1.0;
    }
    else if (bkg_options == "impute_no_scale")
      return 1.0;
    else if (bkg_options == "impute") {
      if ((currentFileTitle.Contains("EGamma") || currentFileTitle.Contains("DoubleEG")) && processId == 18)
        return qcd_gjets_impute_factor_leptonic_runII;
      else if (currentFileTitle.Contains("DiPhotonJetsBox"))
        return diphoton_impute_factor_leptonic_runII;
      else
        return 1.0;
    }

  }

  else
    cout << "Did not recognize background scaling option" << endl;
  return 0.0;

}

void impute_photon_id(double minID_cut, float maxIDMVA, TF1* photon_fakeID_shape, float &minIDMVA, float &evt_weight, int &process_id) {
  if (!(maxIDMVA > minID_cut && minIDMVA < minID_cut))
    return;
  else {
    minIDMVA = photon_fakeID_shape->GetRandom(minID_cut, maxIDMVA);
    evt_weight *= photon_fakeID_shape->Integral(minID_cut, maxIDMVA) / photon_fakeID_shape->Integral(-0.9, minID_cut);
    process_id = 18;
    return;
  }
}

TRandom* myRand = new TRandom(0);
void impute_photon_and_lepton_id(double minID_cut, float maxIDMVA, TF1* photon_fakeID_shape, float &minIDMVA, float &n_lep_medium, float &n_lep_tight, float &evt_weight, int &process_id) {
  if (!(maxIDMVA > minID_cut && minIDMVA < minID_cut && n_lep_medium == 0))
    return;
  else {
    //cout << "Imputing this event: maxIDMVA = " << maxIDMVA << ", minIDMVA = " << minIDMVA << ", n_lep_medium = " << n_lep_medium <<endl;
    minIDMVA = photon_fakeID_shape->GetRandom(minID_cut, maxIDMVA);
    double rand = myRand->Rndm();
    n_lep_tight = rand <= diphoton_nTightLep0_prob ? 0 : (rand <= diphoton_nTightLep0_prob + diphoton_nTightLep1_prob ? 1 : 2);
    n_lep_medium = n_lep_tight == 2 ? 2 : 1;
    evt_weight *= photon_fakeID_shape->Integral(minID_cut, maxIDMVA) / photon_fakeID_shape->Integral(-0.9, minID_cut);
    process_id = 18;
    //cout << "Same event, after imputing: maxIDMVA = " << maxIDMVA << ", minIDMVA = " << minIDMVA << ", n_lep_medium = " << n_lep_medium << ", evt_weight = " << evt_weight << endl;
    return;
  }
}

const double impute_transfer_factor = 1.191; // N_data passing minIDVMA cut / N_data failing minIDMVA cut (obtained from `python impute_transfer_factor.py --input_fail "../ttHHadronicLoose_impute_sideband__histogramsAll.root" --input_pass "../ttHHadronicLoose_impute_presel__histogramsAll.root"`)

// Function derived from PhotonID_Sideband/derive_shape.py
// "min" : python derive_shape.py --input "../ttHHadronicLoose_NoQCDScale_histogramsAll.root" --data_driven
// "max" : python derive_shape.py --input "../ttHHadronicLoose_NoQCDScale_histogramsAll.root" --data_driven --hist_name "hPhotonMaxIDMVA_fine"

TF1* get_photon_ID_shape(TString type) {
  TF1* f_IDMVA = new TF1("f_IDMVA", "[0] + [1]*x + [2]*x^2 + [3]*x^3 + [4]*x^4 + [5]*x^5 + [6]*x^6 + [7]*x^7", -1.0, 1.0);

  if (type == "min") {
    f_IDMVA->SetParameter(0, 1546.58);
    f_IDMVA->SetParameter(1, -2339.5);
    f_IDMVA->SetParameter(2, 4520.45);
    f_IDMVA->SetParameter(3, -5953.99);
    f_IDMVA->SetParameter(4, -3007.99);
    f_IDMVA->SetParameter(5, 8550.25);
    f_IDMVA->SetParameter(6, 18200.1);
    f_IDMVA->SetParameter(7, -21973.2);
  }
  else if (type == "max") {
    f_IDMVA->SetParameter(0, 2074.26);
    f_IDMVA->SetParameter(1, -1503.06);
    f_IDMVA->SetParameter(2, 2046.56);
    f_IDMVA->SetParameter(3, 12631.6);
    f_IDMVA->SetParameter(4, 3714.54);
    f_IDMVA->SetParameter(5, -47364.6);
    f_IDMVA->SetParameter(6, -4399.99);
    f_IDMVA->SetParameter(7, 59619.5);
  }
  else if (type == "lead") {
    f_IDMVA->SetParameter(0, 2456.69); 
    f_IDMVA->SetParameter(1, -2760.28); 
    f_IDMVA->SetParameter(2, 1409.34); 
    f_IDMVA->SetParameter(3, 14775.1); 
    f_IDMVA->SetParameter(4, 23726.9); 
    f_IDMVA->SetParameter(5, -73229.7); 
    f_IDMVA->SetParameter(6, -26851); 
    f_IDMVA->SetParameter(7, 89832); 
  }
  else if (type == "sublead") {
    f_IDMVA->SetParameter(0, 3014.79); 
    f_IDMVA->SetParameter(1, -2977.22); 
    f_IDMVA->SetParameter(2, 6433.38); 
    f_IDMVA->SetParameter(3, -3873.4); 
    f_IDMVA->SetParameter(4, -7026.29); 
    f_IDMVA->SetParameter(5, 2512.59); 
    f_IDMVA->SetParameter(6, 20228.5); 
    f_IDMVA->SetParameter(7, -6647.97); 
  }
  else if (type == "fake") {
    f_IDMVA->SetParameter(0, 4142.68); 
    f_IDMVA->SetParameter(1, -6005.08); 
    f_IDMVA->SetParameter(2, 12297.7); 
    f_IDMVA->SetParameter(3, -12373); 
    f_IDMVA->SetParameter(4, -25571.6); 
    f_IDMVA->SetParameter(5, 28165.2); 
    f_IDMVA->SetParameter(6, 58033.1); 
    f_IDMVA->SetParameter(7, -55772.5); 
  }
  else if (type == "fake_runII_pTMggCutAtPoint2") {
    f_IDMVA->SetParameter(0, 6244.78);
    f_IDMVA->SetParameter(1, -8740.43);
    f_IDMVA->SetParameter(2, 10637.2);
    f_IDMVA->SetParameter(3, -4925.31);
    f_IDMVA->SetParameter(4, -6361.07);
    f_IDMVA->SetParameter(5, 969.525);
    f_IDMVA->SetParameter(6, 26352);
    f_IDMVA->SetParameter(7, -18116.8);
  }

  else if (type == "fake_runII") {
    f_IDMVA->SetParameter(0, 8818.17);
    f_IDMVA->SetParameter(1, -12755.5);
    f_IDMVA->SetParameter(2, 26130);
    f_IDMVA->SetParameter(3, -26664.9);
    f_IDMVA->SetParameter(4, -54741.1);
    f_IDMVA->SetParameter(5, 76558);
    f_IDMVA->SetParameter(6, 112245);
    f_IDMVA->SetParameter(7, -123913);
  }

  else if (type == "fake_barrel_lowPt") {
    f_IDMVA->SetParameter(0, 744.04); 
    f_IDMVA->SetParameter(1, -1118.68); 
    f_IDMVA->SetParameter(2, 1944.08); 
    f_IDMVA->SetParameter(3, -1859.54); 
    f_IDMVA->SetParameter(4, -4195.24); 
    f_IDMVA->SetParameter(5, 4209.09); 
    f_IDMVA->SetParameter(6, 8162.02); 
    f_IDMVA->SetParameter(7, -7385.49); 
  }
  else if (type == "fake_barrel_highPt") {
    f_IDMVA->SetParameter(0, 989.714); 
    f_IDMVA->SetParameter(1, -1731.67); 
    f_IDMVA->SetParameter(2, 3120.35); 
    f_IDMVA->SetParameter(3, -2744.14); 
    f_IDMVA->SetParameter(4, -4944.81); 
    f_IDMVA->SetParameter(5, 5135.66); 
    f_IDMVA->SetParameter(6, 14870.4); 
    f_IDMVA->SetParameter(7, -13887.5); 
  }
  else if (type == "fake_endcap_lowPt") {
    f_IDMVA->SetParameter(0, 93.664); 
    f_IDMVA->SetParameter(1, -194.721); 
    f_IDMVA->SetParameter(2, 10.2034); 
    f_IDMVA->SetParameter(3, 536.54); 
    f_IDMVA->SetParameter(4, 407.474); 
    f_IDMVA->SetParameter(5, -1653.73); 
    f_IDMVA->SetParameter(6, 638.739); 
    f_IDMVA->SetParameter(7, 229.782); 
  }
  else if (type == "fake_endcap_highPt") {
    f_IDMVA->SetParameter(0, 177.77); 
    f_IDMVA->SetParameter(1, -215.428); 
    f_IDMVA->SetParameter(2, 700.557); 
    f_IDMVA->SetParameter(3, 338.359); 
    f_IDMVA->SetParameter(4, -1518.96); 
    f_IDMVA->SetParameter(5, -1392.57); 
    f_IDMVA->SetParameter(6, 3457.53); 
    f_IDMVA->SetParameter(7, -1272.35); 
  }


  return f_IDMVA;
}

TF2* get_photon_ID_shape() {
  TF2* f_IDMVA = new TF2("f_IDMVA", "[0] + [1]*x + [2]*y + [3]*(x**2) + [4]*(x*y) + [5]*(y**2) + [6]*(x**3) + [7]*((x**2)*y) + [8]*((x) * (y**2)) + [9]*(y**3) + [10]*(x**4) + [11]*(y**4) + [12]*(x**5) + [13]*(y**5) + [14]*(x**6) + [15]*(y**6) + [16]*(x**7) + [17]*(y**7)",  -0.7, 1.0, -0.7, 1.0); 
  f_IDMVA->SetParameter(0, 5.50626e+01); 
  f_IDMVA->SetParameter(2, 6.13402e+02); 
  f_IDMVA->SetParameter(3, -7.36922e+02); 
  f_IDMVA->SetParameter(4, -1.58195e+03); 
  f_IDMVA->SetParameter(5, 2.93274e+03); 
  f_IDMVA->SetParameter(6, -9.08034e+02); 
  f_IDMVA->SetParameter(7, 1.19128e+03); 
  f_IDMVA->SetParameter(8, -2.94121e+03); 
  f_IDMVA->SetParameter(9, 1.96396e+03); 
  f_IDMVA->SetParameter(10, -1.00375e+03); 
  f_IDMVA->SetParameter(11, 2.02756e+03); 
  f_IDMVA->SetParameter(12, -2.36958e+02); 
  f_IDMVA->SetParameter(13, -2.54148e+03); 
  f_IDMVA->SetParameter(14, 1.65733e+03); 
  f_IDMVA->SetParameter(15, -3.98055e+03); 
  f_IDMVA->SetParameter(16, 1.40529e+03);
  f_IDMVA->SetParameter(17, 5.57964e+03); 
  f_IDMVA->SetParameter(18, -2.16032e+03); 
  
  return f_IDMVA;
}

//const TF1* gjet_ID_shape = get_photon_ID_shape();

void swap(double &a, double &b) {
  double temp_a = a;
  double temp_b = b;
  a = temp_b;
  b = temp_a;
  return;
}

const std::map<double, int> lepton_probs = {
	{0.4841, 0},
	{0.9669, 1},
	{1.0, 2}
};

//TRandom* myRand = new TRandom(0);
float impute_leps_from_fakePDF() { // values from `python derive_shape_fake_lepton.py --input "../ttHLeptonicLoose_impute2_8Apr2019_scaled_histograms2017.root"`
  double rand = myRand->Rndm();
  if ( rand <= 0.4841 )
    return 0;
  else if ( rand <= 0.9669 )
    return 1;
  else
    return 2;
}

double impute_from_fakePDF_withKinematics(double minID_cut, float maxIDMVA, int event, vector<TF1*> photon_fakeID_shapes, float pt, float eta, float &evt_weight) {
  evt_weight *= impute_transfer_factor;

  int idx = -1;
  if (pt > 40 && eta < barrel_eta)
    idx = 0;
  else if (pt < 40 && eta < barrel_eta)
    idx = 1;
  else if (pt > 40 && eta > barrel_eta)
    idx = 2;
  else if (pt < 40 && eta > barrel_eta)
    idx = 3;

  if (photon_fakeID_shapes.size() != 4) {
    cout << "Incorrect number of fake PDFs (should be 4)" << endl;
    return -999;
  } 
  else {
    double minIDMVA = photon_fakeID_shapes[idx]->GetRandom(minID_cut, maxIDMVA);
    double weight = photon_fakeID_shapes[idx]->Integral(minID_cut, maxIDMVA) / photon_fakeID_shapes[idx]->Integral(-0.9, minID_cut);
    evt_weight *= weight;
    return minIDMVA;
  }

}

double impute_from_fakePDF(double minID_cut, float maxIDMVA, int event, TF1* photon_fakeID_shape, float &evt_weight) {
  //evt_weight *= impute_transfer_factor;
  
  double minIDMVA = photon_fakeID_shape->GetRandom(minID_cut, maxIDMVA);
  
  double weight = photon_fakeID_shape->Integral(minID_cut, maxIDMVA) / photon_fakeID_shape->Integral(-0.9, minID_cut);
  evt_weight *= weight;

  //cout << "Max IDMVA: " << maxIDMVA << " , Min IDMVA: " << minIDMVA << endl;
  //cout << "Applying additional weight factor of: " << weight << endl;

  return minIDMVA;
  
}

double impute_photon_id(double minID_cut, float &maxIDMVA, int event, TF1* photon_minID_shape, TF1* photon_maxID_shape, float &evt_weight, TF2* photon_ID_shape = nullptr) {
  evt_weight *= impute_transfer_factor;

  if (photon_ID_shape == nullptr) {
    double minIDMVA = photon_minID_shape->GetRandom(minID_cut, 1.0);
    maxIDMVA = photon_maxID_shape->GetRandom(minID_cut, 1.0);
    return minIDMVA;
  }

  else {
    Double_t minIDMVA_(-999), maxIDMVA_(-999);
    while (minIDMVA_ >= maxIDMVA_)
      photon_ID_shape->GetRandom2(maxIDMVA_, minIDMVA_);
    double minIDMVA = minIDMVA_;
    maxIDMVA = maxIDMVA_;
    cout << "Max IDMVA: " << maxIDMVA << " , Min IDMVA: " << minIDMVA << endl;
    return minIDMVA;
  }
  
}

void impute_lead_sublead_photon_id(double minID_cut, float &leadIDMVA, float &subleadIDMVA, int event, TF1* photon_leadID_shape, TF1* photon_subleadID_shape, float &evt_weight) {
  evt_weight *= impute_transfer_factor;
  leadIDMVA = photon_leadID_shape->GetRandom(minID_cut, 1.0);
  subleadIDMVA = photon_subleadID_shape->GetRandom(minID_cut, 1.0);
  cout << "Lead IDMVA: " << leadIDMVA << " , Sublead IDMVA: " << subleadIDMVA << endl;
  return;
} 

bool is_wrong_tt_jets_sample(TString currentFileTitle, TString channel) {
  if (!(currentFileTitle.Contains("TTTo") || currentFileTitle.Contains("TTJets")))
    return false;
  if (currentFileTitle.Contains("TTJets_Tune")) { // use these for Hadronic
    if (channel == "Hadronic") {
      cout << "Hadronic channel, so using inclusive sample: " << currentFileTitle << endl;
      return false;
    }
    else if (channel == "Leptonic") {
      cout << "Leptonic channel, so skipping inclusive sample: " << currentFileTitle << endl;
      return true;
    }
  }
  else if (currentFileTitle.Contains("SingleLept") || currentFileTitle.Contains("DiLept") || currentFileTitle.Contains("TTTo2L2Nu") || currentFileTitle.Contains("TTToSemiLeptonic")) { // use these for Leptonic
    if (channel == "Hadronic") {
      cout << "Hadronic channel, so skipping lepton decays sample: " << currentFileTitle << endl;
      return true;
    }
    else if (channel == "Leptonic") {
      cout << "Leptonic channel, so using lepton decays sample: " << currentFileTitle << endl;
      return false;  
    }
  }
} 

bool is_low_stats_process(TString currentFileTitle) {
  //if (currentFileTitle.Contains("QCD") || currentFileTitle.Contains("DY") || currentFileTitle.Contains("TTJets") || currentFileTitle.Contains("TTTo2L2Nu") || currentFileTitle.Contains("TTToSemiLeptonic"))
  if (currentFileTitle.Contains("QCD"))
    return true;
  return false;
}

int categorize_signal_sample(TString currentFileTitle) {
  if (currentFileTitle.Contains("HToGG") || currentFileTitle.Contains("ttHJetToGG")) {
    if ((currentFileTitle.Contains("M125") || currentFileTitle.Contains("M120") || currentFileTitle.Contains("M130")) && !currentFileTitle.Contains("powheg")) { // save for fgg final fit purposes
      return 0; 
    }
    else if (currentFileTitle.Contains("M127")) {
      return 1; // save for bdt optimization purposes 
    }
    else
      return 2; // don't need to save for anything, do with it what you please
  }
  else
    return -1;
}

int categorize_signal_mass_label(TString currentFileTitle) {
    if (currentFileTitle.Contains("M120"))
        return 120;
    else if (currentFileTitle.Contains("M123"))
        return 123;
    else if (currentFileTitle.Contains("M124"))
        return 124;
    else if (currentFileTitle.Contains("M125"))
        return 125;
    else if (currentFileTitle.Contains("M126"))
        return 126;
    else if (currentFileTitle.Contains("M127"))
        return 127;
    else if (currentFileTitle.Contains("M130"))
        return 130;
    else
        return -1;
}

int categorize_photons(int leadGenMatch, int subleadGenMatch) {
  if (leadGenMatch != 1 && subleadGenMatch != 1)
    return 0; // fake-fake
  else if (!(leadGenMatch == 1 && subleadGenMatch == 1) && (leadGenMatch == 1 || subleadGenMatch == 1))
    return 1; // prompt-fake
  else if (leadGenMatch == 1 && subleadGenMatch == 1)
    return 2; // prompt-prompt
  else {
    cout << "Shouldn't be here" << endl;
    return -999;
  }
}

int categorize_photons_detail(int leadPhotonType, int subleadPhotonType) {
  if (leadPhotonType == 3 && subleadPhotonType == 3)
    return 0; //fake-fake
  else if ((leadPhotonType == 2 && subleadPhotonType == 3) || (leadPhotonType == 3 && subleadPhotonType == 2))
    return 1; //fake-elec
  else if (leadPhotonType == 2 && subleadPhotonType == 2)
    return 2; //elec-elec
  else if ((leadPhotonType == 3 && subleadPhotonType == 1) || (leadPhotonType == 1 && subleadPhotonType == 3))
    return 3; //fake-prompt
  else if ((leadPhotonType == 2 && subleadPhotonType == 1) || (leadPhotonType == 1 && subleadPhotonType == 2))
    return 4; //elec-prompt
  else if (leadPhotonType == 1 && subleadPhotonType == 1)
    return 5; //prompt-prompt
}

int categorize_leptons(int nGoodEls, int nGoodMus) {
  int nLeps = nGoodEls + nGoodMus;
  if (nLeps == 0)
    return 0;
  if (nLeps == 1) {
    if (nGoodEls == 1)
      return 1;
    if (nGoodMus == 1)
      return 2;
  }
  if (nLeps >= 2) {
    if (nGoodEls >= 1 && nGoodMus >= 1)
      return 3;
    if (nGoodEls >= 2)
      return 4;
    if (nGoodMus >= 2)
      return 5;
  }
  
}

int categorize_reco_leptons(int nGoodEls, int nGoodMus) {
  int nLeps = nGoodEls + nGoodMus;
  if (nLeps == 0)
    return 0;
  if (nLeps == 1) {
    if (nGoodEls == 1)
      return 1;
    if (nGoodMus == 1)
      return 2;
  }
  if (nLeps == 2) {
    if (nGoodEls == 1 || nGoodMus == 1)
      return 3;
    if (nGoodEls >= 2)
      return 4;
    if (nGoodMus >= 2)
      return 5;
  }
  if (nLeps >= 3) {
    return 6;
  }
}

double sgn(double x) {
  if (x < 0)
    return -1;
  else if (x > 0)
    return 1;
  else 
    return 0;
}

bool sortByValue(const std::pair<int,double>& pair1, const std::pair<int,double>& pair2 ) {
  return pair1.second > pair2.second;
}

vector<std::pair<int, double>> sortVector(const vector<double> v) {
  vector<std::pair<int, double>> v2;
  for (int i = 0; i < v.size(); i++)
    v2.push_back(std::pair<int, double>(i, v[i]));
  std::sort(v2.begin(), v2.end(), sortByValue);
  return v2;
}

const double m_Z = 91.12;
const double m_top = 172.44;
TLorentzVector get_hadronic_top(const vector<TLorentzVector> jets, const vector<std::pair<int, double>> btag_scores_sorted) {
  int idx_btag_1 = btag_scores_sorted[0].first;
  int idx_btag_2 = btag_scores_sorted[1].first;
  TLorentzVector b_candidate_1 = jets[idx_btag_1];
  TLorentzVector b_candidate_2 = jets[idx_btag_2];
  TLorentzVector top_candidate;
  double min_diff = 9999;
  for (int i = 0; i < jets.size(); i++) {
    if (i == idx_btag_1 || i == idx_btag_2)
      continue;
    for (int j = i + 1; j < jets.size(); j++) {
      if (j == idx_btag_1 || j == idx_btag_2)
	continue;
      TLorentzVector top_candidate_1 = b_candidate_1 + jets[i] + jets[j];
      TLorentzVector top_candidate_2 = b_candidate_2 + jets[i] + jets[j];
      if (abs(top_candidate_1.M() - m_top) < min_diff) {
	top_candidate = top_candidate_1;
	min_diff = abs(top_candidate_1.M() - m_top);
      }
      if (abs(top_candidate_2.M() - m_top) < min_diff) {
        top_candidate = top_candidate_2;
        min_diff = abs(top_candidate_2.M() - m_top);
      }
    }
  }
  return top_candidate;
}

const double mW = 80;
double closest_mW(const vector<TLorentzVector> jets, const TLorentzVector diphoton, double &deltaR) {
  double min_diff = 999;
  int jet1_idx(-1), jet2_idx(-1);
  for (int i = 0; i < jets.size(); i++) {
    for (int j = i + 1; j < jets.size(); j++) {
      TLorentzVector dijet = jets[i] + jets[j];
      double diff = abs(dijet.M() - mW);
      if (diff < min_diff) {
	min_diff = diff;
	jet1_idx = i;
	jet2_idx = j;
      }
    }
  }
  deltaR = jets[jet1_idx].DeltaR(jets[jet2_idx]);
  return min_diff;
}

double deltaR_Higgs_W(const vector<TLorentzVector> jets, const TLorentzVector diphoton) {
  double min_diff = 999;
  int jet1_idx(-1), jet2_idx(-1);
  for (int i = 0; i < jets.size(); i++) {
    for (int j = i + 1; j < jets.size(); j++) {
      TLorentzVector dijet = jets[i] + jets[j];
      double diff = abs(dijet.M() - mW);
      if (diff < min_diff) {
        min_diff = diff;
        jet1_idx = i;
        jet2_idx = j;
      }
    }
  }
  return jets[jet1_idx].DeltaR(jets[jet2_idx]);
}

double get_ht(vector<TLorentzVector> jets) {
  double ht = 0;
  for (int i = 0; i < jets.size(); i++) {
    ht += jets[i].Pt();
  }
  return ht;
}

double min_dr(const TLorentzVector target, const vector<TLorentzVector> objects) {
  double min = 999;
  for (int i = 0; i < objects.size(); i++) {
    double dr = target.DeltaR(objects[i]);
    min = dr < min ? dr : min;
  }
  return min;
}

const float pad_value = -9.;
void calculate_masses(TLorentzVector diphoton, vector<TLorentzVector> jets, float &m1, float &m2) {
  if (jets.size() < 4) {
    m1 = pad_value;
    m2 = pad_value;
    return;
  }
  float min_mass_diff = 999999;
  for (int i = 0; i < 4; i++) {
    TLorentzVector t1 = diphoton + jets[i];
    TLorentzVector t2;
    for (int j = 0; j < 4; j++) {
      if (j == i) continue;
      t2 += jets[j];
    }
    float mass_diff = abs(t1.M() - m_top) + abs(t2.M() - m_top);
    if (mass_diff < min_mass_diff) {
      min_mass_diff = mass_diff;
      m1 = t1.M();
      m2 = t2.M();
    }
  }
  return;
}

bool sortByTopMass(const std::pair<int,double>& pair1, const std::pair<int,double>& pair2 ) {
  return abs(pair1.second - m_top) < abs(pair2.second - m_top);
}

vector<float> sort_by_top_mass_difference(vector<float> masses, std::vector<std::pair<int, double>> &ordering) {
    vector<float> v;
    
    for (unsigned int i = 0; i < masses.size(); i++)
        ordering.push_back(std::pair<int,double>(i, masses[i]));

    // sort
    std::sort(ordering.begin(), ordering.end(), sortByTopMass);
    for (unsigned int i = 0; i < masses.size(); i++)
        v.push_back(masses.at(ordering[i].first));
    return v;    
}

unsigned int factorial(unsigned int a) {
    unsigned int b = 1;
    for (int i = 1; i <= a; i++)
        b *= i;
    return b;
}

unsigned int N_choose_K(unsigned int N, unsigned int K) {
    return factorial(N) / ( factorial(N - K) * factorial(K));
}

const unsigned int max_jets = 6;
vector<float> calculate_top_candidates(TLorentzVector diphoton, vector<TLorentzVector> jets, vector<double> btag_scores, float max_btag) {
    vector<float> top_candidates;
    vector<float> t_Hq_candidates;
    vector<float> t_qqq_candidates;
    unsigned int n_jets = jets.size();
    // First calculate t->Hc candidates
    for (unsigned int i = 0; i < min(max_jets, n_jets); i++) { // gives up to max_jets-1 candidates
        vector<float> t_qqq_candidates_mini;
        if (btag_scores[i] >= max_btag)
            continue;
        TLorentzVector top_cand = diphoton + jets[i];
        t_Hq_candidates.push_back(top_cand.M());
        //cout << "ggj jet: " << i << endl;
        // Now reconstruct other top quark
        for (unsigned int j = 0; j < min(max_jets, n_jets); j++) { // for each m_ggj candidate, gives up to Binomial(max_jets-2,2) candidates
            if (j == i)
                continue;
            if (btag_scores[j] < max_btag)
                continue;
            for (unsigned int k = 0; k < min(max_jets, n_jets); k++) {
                if (k == i || k == j)
                    continue;
                for (unsigned int m = k + 1; m < min(max_jets, n_jets); m++) {
                    if (m == i || m == j)
                        continue;
                    TLorentzVector bjet = jets[j];
                    TLorentzVector qjet1 = jets[k];
                    TLorentzVector qjet2 = jets[m];
                    TLorentzVector top_cand = bjet + qjet1 + qjet2;
                    t_qqq_candidates_mini.push_back(top_cand.M());
                    //cout << "bjj jet: " << j << ", " << k << ", " << m << endl;
                }
            }
        }
        std::vector<std::pair<int, double>> ordering_;
        t_qqq_candidates_mini = sort_by_top_mass_difference(t_qqq_candidates_mini, ordering_);
        t_qqq_candidates.insert(t_qqq_candidates.end(), t_qqq_candidates_mini.begin(), t_qqq_candidates_mini.end());
        while (t_qqq_candidates.size() < (t_Hq_candidates.size())*N_choose_K(max_jets-2, 2))
            t_qqq_candidates.push_back(pad_value);
        //for (unsigned int l = 0; l < t_qqq_candidates.size(); l++)
        //    cout << t_qqq_candidates[l] << endl;

        //cout << endl << endl;
    }
    std::vector<std::pair<int, double>> ordering;
    t_Hq_candidates = sort_by_top_mass_difference(t_Hq_candidates, ordering);

    unsigned int n_t_Hq = t_Hq_candidates.size();
    unsigned int max_Hqs = 2;
    for (unsigned int i = 0; i < min(max_Hqs, n_t_Hq); i++) {
        top_candidates.push_back(t_Hq_candidates[i]);
        unsigned int idx = ordering[i].first;
        for (unsigned int j = idx*N_choose_K(max_jets-2, 2); j < (idx+1)*N_choose_K(max_jets-2, 2); j++) {
            top_candidates.push_back(t_qqq_candidates[j]);
        }
    } 
    
    //cout << "Sorted t_Hq_candidates:" << endl;
    //for (unsigned int i = 0; i < t_Hq_candidates.size(); i++)
    //    cout << t_Hq_candidates[i] <<endl;
    //while (t_Hq_candidates.size() < (max_jets - 1)) {
    //    t_Hq_candidates.push_back(0);
    //}

    /*
    // Now calculate t->qqq candidates
    vector<float> t_qqq_candidates;
    for (unsigned int i = 0; i < min(max_jets, n_jets); i++) { // gives up to Binomial(max_jets-1,2) candidates
        if (btag_scores[i] < max_btag) // demand that the b-jet be in the top candidate
            continue;
        for (unsigned int j = 0; j < min(max_jets, n_jets); j++) {
            if (i == j)
                continue;
            for (unsigned int k = j+1; k < min(max_jets, n_jets); k++) {
                if (i == k)
                   continue;
                TLorentzVector bjet = jets[i];
                TLorentzVector qjet1 = jets[j];
                TLorentzVector qjet2 = jets[k];
                TLorentzVector top_cand = bjet + qjet1 + qjet2;
                t_qqq_candidates.push_back(top_cand.M());
            }
        }
    }
    t_qqq_candidates = sort_by_top_mass_difference(t_qqq_candidates);
    //cout << "Sorted t_qqq_candidates:" << endl;
    //for (unsigned int i = 0; i < t_qqq_candidates.size(); i++) 
    //    cout << t_qqq_candidates[i] << endl;
    while (t_qqq_candidates.size() < N_choose_K(max_jets-1, 2))
        t_qqq_candidates.push_back(0);
    */

    // concatenate two vectors
    //top_candidates = t_Hq_candidates;
    //top_candidates.insert(top_candidates.end(), t_qqq_candidates.begin(), t_qqq_candidates.end());

    //cout << "N_jets: " << jets.size() << endl;
    while (top_candidates.size() < 2 * (1 + N_choose_K(max_jets-2, 2)))
        top_candidates.push_back(0);
    //cout << "Top candidates size: " << top_candidates.size() << endl;
    //for (unsigned int i = 0; i < top_candidates.size(); i++)
    //    cout << top_candidates[i] << endl;
    //cout << "End event" << endl << endl;
    //cout << top_candidates.size() << endl;
    return top_candidates;
}

double helicity(const TLorentzVector particle_1, const TLorentzVector particle_2) {
  TLorentzVector p1 = particle_1;
  TLorentzVector parent = particle_1 + particle_2;
  
  TVector3 boost_to_parent = -(parent.BoostVector());
  p1.Boost(boost_to_parent);

  TVector3 v1 = p1.Vect();
  TVector3 vParent = parent.Vect();

  double cos_theta_1 = (v1.Dot(vParent)) / (v1.Mag() * vParent.Mag());

  return abs(cos_theta_1);  
}

double convert_tmva_to_prob(double score) {
  // Undo TMVA transformation
  double raw_score = -0.5 * log( (2 / (score + 1)) - 1);

  // Apply logistic (sigmoid) transformation
  double prob = 1 / (1 + exp(-raw_score));
  return prob;
}

/*
const vector<TString> vSamples_2016 = {"DoubleEG", 
			"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v2", 
			"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", 
			"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa", 
			"GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8", 
			"GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8", 
			"GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8", 
			"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8", 
			"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8", 
			"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8", 
			"TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8",
			"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8",		
			"WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
			"TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"				
}; */


const vector<TString> vSamples_2016 = {
			// Data
			"DoubleEG_Run2016B-03Feb2017_ver1-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016B-03Feb2017_ver2-v2_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016C-03Feb2017-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016D-03Feb2017-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016E-03Feb2017-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016F-03Feb2017-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016G-03Feb2017-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016H-03Feb2017_ver2-v1_MINIAOD_2016_topTag_overlapRemoval",
			"DoubleEG_Run2016H-03Feb2017_ver3-v1_MINIAOD_2016_topTag_overlapRemoval",
			// gamma + jets
                        "GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        // gamma + jets madgraph sample
                        "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
                        "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// ttH
			"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v2_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ttHJetToGG_M120_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ttHJetToGG_M123_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ttHJetToGG_M124_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ttHJetToGG_M126_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ttHJetToGG_M127_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ttHJetToGG_M130_13TeV_amcatnloFXFX_madspin_pythia8_v2_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			//"ttHJetToGG_M110_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			//"ttHJetToGG_M105_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			//"ttHJetToGG_M100_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// DY
			"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// gamma gamma + jets
			"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"DiPhotonJetsBox_M40_80-Sherpa_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// jets
			"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// tt + X
			"TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",	
			// V + gamma
			"ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// t + gamma
			"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// ttV
			"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// tV
			"tZq_ll_4f_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			// VV
			"WW_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"WZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",

			// other signal modes
			//"THQ_HToGG_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			//"THW_HToGG_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"VBFHToGG_M125_13TeV_amcatnlo_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_2016_topTag_overlapRemoval",
			"VBFHToGG_M125_13TeV_amcatnlo_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_2016_topTag_overlapRemoval",
};

const vector<TString> vSamples_2017 = {
			/*	
			"DoubleEG",
			"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa",
			"GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8",
			"GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8",
			"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8",
			"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8",
			"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8"
			*/


			// Data
			"DoubleEG_Run2017B-31Mar2018-v1_MINIAOD_forHualin_2017",
			"DoubleEG_Run2017C-31Mar2018-v1_MINIAOD_forHualin_2017",
			"DoubleEG_Run2017D-31Mar2018-v1_MINIAOD_forHualin_2017",
			"DoubleEG_Run2017E-31Mar2018-v1_MINIAOD_forHualin_2017",
			"DoubleEG_Run2017F-31Mar2018-v1_MINIAOD_forHualin_2017",
			// DY
			"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1_MINIAODSIM_forHualin_2017",
			"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_forHualin_2017",
			// gamma gamma + jets
			"DiPhotonJetsBox_M40_80-Sherpa_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			// gamma + jets
			"GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			// gamma + jets MadGraph samples
			"GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			// jets
			"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			// TT + X
			"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_forHualin_2017",
			"TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			// V + gamma
			"WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			// t + gamma
			"TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			// ttV
			"TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			// tV
			"ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			// VV
			"ZZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2_MINIAODSIM_forHualin_2017",
			"WZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"WW_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",

			// ttH
			"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M120_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M123_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M124_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M126_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M127_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			
			"ttHJetToGG_M130_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M115_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			/*
			"ttHJetToGG_M110_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"ttHJetToGG_M105_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			*/
			//"ttHJetToGG_M100_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			// other signal modes
			//"THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_TuneCP5_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			//"THW_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_TuneCP5_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
			"VBFHToGG_M125_13TeV_amcatnlo_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_forHualin_2017",
};

/*
const vector<TString> vSamples_2017 = {"DoubleEG",
			"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8",
			"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa",
			"GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8",
			"GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8",
			"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
			"TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8",
			"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			
			// No V + gamma samples for 2017 :(
};
*/

const vector<TString> vSamples_2018 = {"EGamma",
                        "ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8",
                        "DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8",
                        "DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa",
                        "GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
                        "GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8",
                        "GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
                        "QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
                        "QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8",
                        "QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8",
                        "TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8",
                        "TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
                        "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8"
                        // No V + gamma samples for 2017 :(
};


const vector<TString> vSamples_2016_RunII = {
		// Data
		"DoubleEG_Run2016B-17Jul2018_ver1-v1_MINIAOD_RunII",
		"DoubleEG_Run2016B-17Jul2018_ver2-v1_MINIAOD_RunII",
		"DoubleEG_Run2016C-17Jul2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2016D-17Jul2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2016E-17Jul2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2016F-17Jul2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2016G-17Jul2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2016H-17Jul2018-v1_MINIAOD_RunII",

		// ttH signal
		//"ttHJetToGG_M110_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M120_13TeV_amcatnloFXFX_madspin_pythia8_v2_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M123_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M124_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v2_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M126_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M127_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M130_13TeV_amcatnloFXFX_madspin_pythia8_v2_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",

		// other signal modes
		"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_RunIISummer16MiniAODv3-BS2016_BSandPUSummer16_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		//"THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_TuneCUETP8M1_v2_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		// missing VH, THQ, THW
		
		// QCD backgrounds
		"DiPhotonJetsBox_M40_80-Sherpa_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII", 
		"GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII", 
		"GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII", 
		"GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII", 
		"GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII", 
		"GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII", 
		"GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII", 
		"GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII", 
		"GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII", 
		"GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",

		// tt + X bkgs
		"TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",

		// V + (gamma) bkgs
		"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1_MINIAODSIM_RunII",
		"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1_MINIAODSIM_RunII",
		"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1_MINIAODSIM_RunII",
		"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1_MINIAODSIM_RunII",
		"ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1_MINIAODSIM_RunII",

		// VV
		"WW_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"WW_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"WZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"WZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",

		// t + V
		"tZq_ll_4f_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1_MINIAODSIM_RunII",
		"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1_MINIAODSIM_RunII",
		"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1_MINIAODSIM_RunII",
		"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",

		// tt + V
		"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1_MINIAODSIM_RunII",
		"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_RunII",
		"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1_MINIAODSIM_RunII",
		"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1_MINIAODSIM_RunII",
			
		// t + gamma
		"TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		
		// FCNC 
		/*
		"ST_FCNC-TH_Tleptonic_HToaa_eta_hut-MadGraph5-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"ST_FCNC-TH_Tleptonic_HToaa_eta_hct-MadGraph5-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII",
		"TT_FCNC-aTtoHJ_Tleptonic_HToaa_eta_hut-MadGraph5-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_RunII",
		"TT_FCNC-aTtoHJ_Tleptonic_HToaa_eta_hct-MadGraph5-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_RunII" */

};

const vector<TString> vSamples_2017_RunII = {
		"DoubleEG_Run2017B-31Mar2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2017C-31Mar2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2017D-31Mar2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2017E-31Mar2018-v1_MINIAOD_RunII",
		"DoubleEG_Run2017F-31Mar2018-v1_MINIAOD_RunII",

		// FCNC
		/*
                "ST_FCNC-TH_Tleptonic_HToaa_eta_hct-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
                "ST_FCNC-TH_Tleptonic_HToaa_eta_hut-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
                "TT_FCNC-aTtoHJ_Thadronic_HToaa_eta_hct-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM_RunII",
                "TT_FCNC-aTtoHJ_Thadronic_HToaa_eta_hut-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
                "TT_FCNC-aTtoHJ_Tleptonic_HToaa_eta_hct-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
                "TT_FCNC-aTtoHJ_Tleptonic_HToaa_eta_hut-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		*/
                "TT_FCNC-aTtoHJ_Thadronic_HToaa_eta_hct-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM_RunII",
                "TT_FCNC-aTtoHJ_Thadronic_HToaa_eta_hut-MadGraph5-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",

		// ttH Signal
		//"ttHJetToGG_M105_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		//"ttHJetToGG_M110_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		//"ttHJetToGG_M115_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M120_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M123_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M124_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M126_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M127_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M130_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",

		// other signal modes
		"VBFHToGG_M125_13TeV_amcatnlo_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",

		// QCD backgrounds
		"DiPhotonJetsBox_M40_80-Sherpa_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		
		// tt + X bkgs
		"TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_RunII",
		"TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",

		// V + (gamma)
		"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_RunII",
		"WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM_RunII",
		"ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM_RunII",

		// VV
		"WW_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"WZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ZZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",

		// t + V
		"ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",

		// tt + V
		"TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
		"TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",

		// t + gamma
		"TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
};

const vector<TString> vSamples_2018_RunII = {
		"EGamma_Run2018A-17Sep2018-v2_MINIAOD_RunII",
		"EGamma_Run2018B-17Sep2018-v1_MINIAOD_RunII",
		"EGamma_Run2018C-17Sep2018-v1_MINIAOD_RunII",
		"EGamma_Run2018D-22Jan2019-v2_MINIAOD_RunII",

		// ttH Signal
		//"ttHJetToGG_M110_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M120_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M123_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M127_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"ttHJetToGG_M130_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII", 

                // other signal modes
		"VBFHToGG_M126_13TeV_amcatnlo_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"GluGluHToGG_M-125_13TeV_powheg_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",

                // QCD backgrounds
		"DiPhotonJetsBox_M40_80-Sherpa_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
                "DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_RunII",
		"GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-4cores5k_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_RunII",
		"QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
                "QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
                "QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",


                // tt + X bkgs
		"TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2_MINIAODSIM_RunII",
		"TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_RunII",
		"TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18MiniAOD-NZSFlatPU28to62_102X_upgrade2018_realistic_v15_ext1-v1_MINIAODSIM_RunII",
		"TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",

                // V + (gamma)
		//"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1_MINIAODSIM_RunII",
		"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1_MINIAODSIM_RunII",
                "DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_RunII", // copy these from 2017 because 2018 sample has SUCH bad stats
		"WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1_MINIAODSIM_RunII",
		"ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_RunII",
		
                // VV
 		"WW_TuneCP5_13TeV-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2_MINIAODSIM_RunII",
		"WZ_TuneCP5_13TeV-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3_MINIAODSIM_RunII",
		"ZZ_TuneCP5_13TeV-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2_MINIAODSIM_RunII",

                // t + V
		"ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1_MINIAODSIM_RunII",
		"ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1_MINIAODSIM_RunII",
		"tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_RunII",

                // tt + V
		"TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_RunII",
		"TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_RunII",

                // t + gamma
		"TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2_MINIAODSIM_RunII"

};

//const char* json_2018 = "GoldenJSON/Cert_314472-322633_13TeV_PromptReco_Collisions18_JSON_snt.txt";
const char* json_2018 = "GoldenJSON/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON_snt.txt";
const char* json_2017 = "GoldenJSON/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_snt.txt";
const char* json_2016 = "GoldenJSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_snt.txt";

void set_json(TString year) {
  const char* json_file;
  json_file = year == "2018" ? json_2018 : ( year == "2017" ? json_2017 : ( year == "2016" ? json_2016 : ""));
  set_goodrun_file(json_file);
}

bool pass_json(TString year, unsigned int run, unsigned int lumi_block) {
  if (year == "2018" || year == "2017" || year == "2016") { 
    return goodrun(run, lumi_block);
  }
}

/*const vector<TString> vSamples_2018 = {
			"GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIISummer18MiniAOD-101X_upgrade2018_realistic_v7-v1_MINIAODSIM_test",
			"GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8_RunIISummer18MiniAOD-101X_upgrade2018_realistic_v7-v1_MINIAODSIM_test",
			"GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_RunIISummer18MiniAOD-101X_upgrade2018_realistic_v7-v1_MINIAODSIM_test"
};*/

void add_samples(TChain* ch, TString year) {
  bool runII = year.Contains("RunII");

  TString tag;
  TString location;
  vector<TString> vSamples;

  if (runII) {
    tag = "v1.6";
    location = "/home/users/sjmay/ttH/Loopers/merged_babies";
    if (year.Contains("2016"))
      vSamples = vSamples_2016_RunII;
    else if (year.Contains("2017"))
      vSamples = vSamples_2017_RunII;
    else if (year.Contains("2018"))
      vSamples = vSamples_2018_RunII; 

    for (int i = 0; i < vSamples.size(); i++) {
      ch->Add(location + "/" + vSamples[i] + "_ttH_Babies_RunII" + tag + "/merged_ntuple.root");
    }


  }

  else {

    tag = year == "2016" ? "v80.3" : "v94.8";
    //tag = year == "2016" ? "v80.3" : "RunIIv1.0";

    location = "/home/users/sjmay/ttH/Loopers/merged_babies";

    vSamples = year == "2018" ? vSamples_2018 : (year == "2017" ? vSamples_2017 : vSamples_2016);

    for (int i = 0; i < vSamples.size(); i++) {
      TString tag_temp = vSamples[i].Contains("EGamma") ? "v102.1" : tag;
      TString year_temp = year == "2018" ? (vSamples[i].Contains("EGamma") ? "2018" : "2017") : year;
      ch->Add(location + "/" + vSamples[i] + "__ttH_Babies_" + tag_temp + "_" + year_temp + "/merged_ntuple.root"); // delete me
      //ch->Add(location + "/" + vSamples[i] + "_ttH_Babies_" + tag_temp + "/merged_ntuple.root"); 
    }
  }
}
