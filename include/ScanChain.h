#ifndef _SCAN_CHAIN_H_
#define _SCAN_CHAIN_H_

#include <fstream>
#include <iostream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TString.h"

#include <TCanvas.h>
#include <TH2F.h>
#include <TNtuple.h>

// tprimetHHadronic
#include "ttHLooper.h"
//#include "tprimetHHadronic.cc"
//#include "tprimetHHadronic_v3p2.cc"
//#include "tprimetHHadronic_v3p3.cc" // for the latest samples
#include "tprimetHHadronic_v3p5.cc" // ntuple with chi2 masses from producer
//#include "tprimetHHadronic_v3p3p2.cc" // for testing command

using namespace std;
using namespace tprime;

//vector<TLorentzVector> make_mom_particles(vector<float> &pdgIds, vector<float> &status) {
//  vector<TLorentzVector> vPartons;
//  // note: mom_parton1_pt() and mom_parton2_pt() can be zero
//  if (gen_parton1_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton1_pt(), mom_parton1_eta(), mom_parton1_phi(), mom_parton1_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton1_pdgId());
//    status.push_back(mom_parton1_status());
//  }
//
//  if (gen_parton2_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton2_pt(), mom_parton2_eta(), mom_parton2_phi(), mom_parton2_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton2_pdgId());
//    status.push_back(mom_parton2_status());
//  }
//
//  if (gen_parton3_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton3_pt(), mom_parton3_eta(), mom_parton3_phi(), mom_parton3_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton3_pdgId());
//    status.push_back(mom_parton3_status());
//  }
//
//  if (gen_parton4_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton4_pt(), mom_parton4_eta(), mom_parton4_phi(), mom_parton4_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton4_pdgId());
//    status.push_back(mom_parton4_status());
//  }
//
//  if (gen_parton5_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton5_pt(), mom_parton5_eta(), mom_parton5_phi(), mom_parton5_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton5_pdgId());
//    status.push_back(mom_parton5_status());
//  }
//
//  if (gen_parton6_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton6_pt(), mom_parton6_eta(), mom_parton6_phi(), mom_parton6_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton6_pdgId());
//    status.push_back(mom_parton6_status());
//  }
//
//  if (gen_parton7_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton7_pt(), mom_parton7_eta(), mom_parton7_phi(), mom_parton7_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton7_pdgId());
//    status.push_back(mom_parton7_status());
//  }
//
//  if (gen_parton8_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton8_pt(), mom_parton8_eta(), mom_parton8_phi(), mom_parton8_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton8_pdgId());
//    status.push_back(mom_parton8_status());
//  }
//
//  if (gen_parton9_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton9_pt(), mom_parton9_eta(), mom_parton9_phi(), mom_parton9_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton9_pdgId());
//    status.push_back(mom_parton9_status());
//  }
//
//  if (gen_parton10_pt() > 0) {
//    TLorentzVector mom_parton;
//    mom_parton.SetPtEtaPhiM(mom_parton10_pt(), mom_parton10_eta(), mom_parton10_phi(), mom_parton10_mass());
//    vPartons.push_back(mom_parton);
//    pdgIds.push_back(mom_parton10_pdgId());
//    status.push_back(mom_parton10_status());
//  }
//
//  return vPartons;
//}
//
//vector<TLorentzVector> make_gen_particles(vector<float> &pdgIds, vector<float> &status) {
//  vector<TLorentzVector> vPartons;
//  if (gen_parton1_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton1_pt(), gen_parton1_eta(), gen_parton1_phi(), gen_parton1_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton1_pdgId());
//    status.push_back(gen_parton1_status());
//  }
//
//  if (gen_parton2_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton2_pt(), gen_parton2_eta(), gen_parton2_phi(), gen_parton2_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton2_pdgId());
//    status.push_back(gen_parton2_status());
//  }
//
//  if (gen_parton3_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton3_pt(), gen_parton3_eta(), gen_parton3_phi(), gen_parton3_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton3_pdgId());
//    status.push_back(gen_parton3_status());
//  }
//
//  if (gen_parton4_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton4_pt(), gen_parton4_eta(), gen_parton4_phi(), gen_parton4_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton4_pdgId());
//    status.push_back(gen_parton4_status());
//  }
//
//  if (gen_parton5_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton5_pt(), gen_parton5_eta(), gen_parton5_phi(), gen_parton5_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton5_pdgId());
//    status.push_back(gen_parton5_status());
//  }
//
//  if (gen_parton6_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton6_pt(), gen_parton6_eta(), gen_parton6_phi(), gen_parton6_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton6_pdgId());
//    status.push_back(gen_parton6_status());
//  }
//
//  if (gen_parton7_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton7_pt(), gen_parton7_eta(), gen_parton7_phi(), gen_parton7_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton7_pdgId());
//    status.push_back(gen_parton7_status());
//  }
//
//  if (gen_parton8_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton8_pt(), gen_parton8_eta(), gen_parton8_phi(), gen_parton8_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton8_pdgId());
//    status.push_back(gen_parton8_status());
//  }
//
//  if (gen_parton9_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton9_pt(), gen_parton9_eta(), gen_parton9_phi(), gen_parton9_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton9_pdgId());
//    status.push_back(gen_parton9_status());
//  }
//
//  if (gen_parton10_pt() > 0) {
//    TLorentzVector gen_parton;
//    gen_parton.SetPtEtaPhiM(gen_parton10_pt(), gen_parton10_eta(), gen_parton10_phi(), gen_parton10_mass());
//    vPartons.push_back(gen_parton);
//    pdgIds.push_back(gen_parton10_pdgId());
//    status.push_back(gen_parton10_status());
//  }
//
//  return vPartons;
//}

vector<TLorentzVector> make_jets(vector<double> &btag_scores) {
  vector<TLorentzVector> vJets;
  if (jet1_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet1_pt(), jet1_eta(), jet1_phi(), jet1_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet1_discr());
  }
  if (jet2_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet2_pt(), jet2_eta(), jet2_phi(), jet2_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet2_discr());
  }
  if (jet3_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet3_pt(), jet3_eta(), jet3_phi(), jet3_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet3_discr());
  }
  if (jet4_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet4_pt(), jet4_eta(), jet4_phi(), jet4_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet4_discr());
  }
  if (jet5_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet5_pt(), jet5_eta(), jet5_phi(), jet5_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet5_discr());
  }
  if (jet6_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet6_pt(), jet6_eta(), jet6_phi(), jet6_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet6_discr());
  }
  if (jet7_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet7_pt(), jet7_eta(), jet7_phi(), jet7_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet7_discr());
  }
  if (jet8_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet8_pt(), jet8_eta(), jet8_phi(), jet8_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet8_discr());
  }
  if (jet9_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet9_pt(), jet9_eta(), jet9_phi(), jet9_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet9_discr());
  }
  if (jet10_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet10_pt(), jet10_eta(), jet10_phi(), jet10_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet10_discr());
  }
  if (jet11_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet11_pt(), jet11_eta(), jet11_phi(), jet11_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet11_discr());
  }
  if (jet12_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet12_pt(), jet12_eta(), jet12_phi(), jet12_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet12_discr());
  }
  if (jet13_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet13_pt(), jet13_eta(), jet13_phi(), jet13_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet13_discr());
  }
  if (jet14_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet14_pt(), jet14_eta(), jet14_phi(), jet14_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet14_discr());
  }
  if (jet15_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet15_pt(), jet15_eta(), jet15_phi(), jet15_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet15_discr());
  }
  return vJets;
}

vector<TLorentzVector> make_jets(vector<double> &btag_scores, bool &flag_negative_energy, bool debug = false) {
  vector<TLorentzVector> vJets;
  if (jet1_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet1_pt(), jet1_eta(), jet1_phi(), jet1_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet1_discr());
    if( jet1_e() < 0. ) flag_negative_energy = true;
    if( debug && jet1_e() < 0. ) printf("[WARNING] jet1 pt = %.3f, e = %.3f\n", jet1_pt(), jet1_e());
  }
  if (jet2_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet2_pt(), jet2_eta(), jet2_phi(), jet2_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet2_discr());
    if( jet2_e() < 0. ) flag_negative_energy = true;
    if( debug && jet2_e() < 0. ) printf("[WARNING] jet2 pt = %.3f, e = %.3f\n", jet2_pt(), jet2_e());
  }
  if (jet3_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet3_pt(), jet3_eta(), jet3_phi(), jet3_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet3_discr());
    if( jet3_e() < 0. ) flag_negative_energy = true;
    if( debug && jet3_e() < 0. ) printf("[WARNING] jet3 pt = %.3f, e = %.3f\n", jet3_pt(), jet3_e());
  }
  if (jet4_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet4_pt(), jet4_eta(), jet4_phi(), jet4_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet4_discr());
    if( jet4_e() < 0. ) flag_negative_energy = true;
    if( debug && jet4_e() < 0. ) printf("[WARNING] jet4 pt = %.3f, e = %.3f\n", jet4_pt(), jet4_e());
  }
  if (jet5_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet5_pt(), jet5_eta(), jet5_phi(), jet5_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet5_discr());
    if( jet5_e() < 0. ) flag_negative_energy = true;
    if( debug && jet5_e() < 0. ) printf("[WARNING] jet5 pt = %.3f, e = %.3f\n", jet5_pt(), jet5_e());
  }
  if (jet6_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet6_pt(), jet6_eta(), jet6_phi(), jet6_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet6_discr());
    if( jet6_e() < 0. ) flag_negative_energy = true;
    if( debug && jet6_e() < 0. ) printf("[WARNING] jet6 pt = %.3f, e = %.3f\n", jet6_pt(), jet6_e());
  }
  if (jet7_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet7_pt(), jet7_eta(), jet7_phi(), jet7_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet7_discr());
    if( jet7_e() < 0. ) flag_negative_energy = true;
    if( debug && jet7_e() < 0. ) printf("[WARNING] jet7 pt = %.3f, e = %.3f\n", jet7_pt(), jet7_e());
  }
  if (jet8_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet8_pt(), jet8_eta(), jet8_phi(), jet8_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet8_discr());
    if( jet8_e() < 0. ) flag_negative_energy = true;
    if( debug && jet8_e() < 0. ) printf("[WARNING] jet8 pt = %.3f, e = %.3f\n", jet8_pt(), jet8_e());
  }
  if (jet9_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet9_pt(), jet9_eta(), jet9_phi(), jet9_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet9_discr());
    if( jet9_e() < 0. ) flag_negative_energy = true;
    if( debug && jet9_e() < 0. ) printf("[WARNING] jet9 pt = %.3f, e = %.3f\n", jet9_pt(), jet9_e());
  }
  if (jet10_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet10_pt(), jet10_eta(), jet10_phi(), jet10_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet10_discr());
    if( jet10_e() < 0.0 ) flag_negative_energy = true;
    if( debug && jet10_e() < 0.0 ) printf("[WARNING] jet10 pt = %.3f, e = %.3f\n", jet10_pt(), jet10_e());
  }
  if (jet11_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet11_pt(), jet11_eta(), jet11_phi(), jet11_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet11_discr());
    if( jet11_e() < 0. ) flag_negative_energy = true;
    if( debug && jet11_e() < 0. ) printf("[WARNING] jet11 pt = %.3f, e = %.3f\n", jet11_pt(), jet11_e());
  }
  if (jet12_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet12_pt(), jet12_eta(), jet12_phi(), jet12_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet12_discr());
    if( jet12_e() < 0. ) flag_negative_energy = true;
    if( debug && jet12_e() < 0. ) printf("[WARNING] jet12 pt = %.3f, e = %.3f\n", jet12_pt(), jet12_e());
  }
  if (jet13_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet13_pt(), jet13_eta(), jet13_phi(), jet13_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet13_discr());
    if( jet13_e() < 0. ) flag_negative_energy = true;
    if( debug && jet13_e() < 0. ) printf("[WARNING] jet13 pt = %.3f, e = %.3f\n", jet13_pt(), jet13_e());
  }
  if (jet14_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet14_pt(), jet14_eta(), jet14_phi(), jet14_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet14_discr());
    if( jet14_e() < 0. ) flag_negative_energy = true;
    if( debug && jet14_e() < 0. ) printf("[WARNING] jet14 pt = %.3f, e = %.3f\n", jet14_pt(), jet14_e());
  }
  if (jet15_pt() > 0) {
    TLorentzVector jet;
    jet.SetPtEtaPhiE(jet15_pt(), jet15_eta(), jet15_phi(), jet15_e());
    vJets.push_back(jet);
    btag_scores.push_back(jet15_discr());
    if( jet15_e() < 0. ) flag_negative_energy = true;
    if( debug && jet15_e() < 0. ) printf("[WARNING] jet15 pt = %.3f, e = %.3f\n", jet15_pt(), jet15_e());
  }
  return vJets;
}

double get_ht() {
  double ht = 0;
  if (jet1_pt()  > 0) ht+=jet1_pt();
  if (jet2_pt()  > 0) ht+=jet2_pt();
  if (jet3_pt()  > 0) ht+=jet3_pt();
  if (jet4_pt()  > 0) ht+=jet4_pt();
  if (jet5_pt()  > 0) ht+=jet5_pt();
  if (jet6_pt()  > 0) ht+=jet6_pt();
  if (jet7_pt()  > 0) ht+=jet7_pt();
  if (jet8_pt()  > 0) ht+=jet8_pt();
  if (jet9_pt()  > 0) ht+=jet9_pt();
  if (jet10_pt() > 0) ht+=jet10_pt();
  if (jet11_pt() > 0) ht+=jet11_pt();
  if (jet12_pt() > 0) ht+=jet12_pt();
  if (jet13_pt() > 0) ht+=jet13_pt();
  if (jet14_pt() > 0) ht+=jet14_pt();
  if (jet15_pt() > 0) ht+=jet15_pt();
  return ht;
}

//bool identify_bjet(int &index_bjet, vector<int> &indices, vector<int> &jets_pdgId_genMatched, vector<double> &jets_deltaR_genMatched)
//{
//    bool is_reasonable = true;
//
//    vector<int> vec_bjet_position;
//    vector<int> vec_bjet_index;
//    vector<double> vec_bjet_deltaR;
//    for(unsigned int i = 0; i<indices.size(); ++i)
//    {
//        int index = indices[i];
//        int pdgId = jets_pdgId_genMatched[i];
//        double deltaR = jets_deltaR_genMatched[i];
//        //printf("index: %d, pdgId: %d, deltaR: %.2f\n", index, pdgId, deltaR);
//        if(index >= 0 && abs(pdgId) == 5)
//        {
//            vec_bjet_position.push_back(i);
//            vec_bjet_index.push_back(index);
//            vec_bjet_deltaR.push_back(deltaR);
//        }
//    }
//
//    // determine bjet according to deltaR if there are multiple bjets
//    // caveat: the criterion is for temporary use; momther info is preferred
//    int position_bjet = -1;
//    if(vec_bjet_index.size() == 0)
//    {
//        index_bjet = -1;
//        is_reasonable = false;
//    }
//    else if(vec_bjet_index.size() == 1)
//    {
//        position_bjet = vec_bjet_position[0];
//        index_bjet = vec_bjet_index[0];
//    }
//    else if (vec_bjet_index.size() == 2)
//    {
//        position_bjet = (vec_bjet_deltaR[0] < vec_bjet_deltaR[1]) ? vec_bjet_position[0] : vec_bjet_position[1];
//        index_bjet = (vec_bjet_deltaR[0] < vec_bjet_deltaR[1]) ? vec_bjet_index[0] : vec_bjet_index[1];
//    }
//    else
//    {
//        int minElementIndex = std::min_element(vec_bjet_deltaR.begin(),vec_bjet_deltaR.end()) - vec_bjet_deltaR.begin();
//        position_bjet = vec_bjet_position[minElementIndex];
//        index_bjet = vec_bjet_index[minElementIndex];
//    }
//
//    return is_reasonable;
//
//    //// the rest jets are wjets
//    //for(unsigned int i = 0; i<jets_index_genMatched.size(); ++i)
//    //{
//    //    if(i == position_bjet) continue;
//    //    int index = jets_index_genMatched[i];
//    //    indices_wjets_.push_back(index);
//    //    if(index == -1) is_reasonable = false;
//    //}
//
//    //// no matched b-jet
//    //if(indices_wjets_.size() > 2) is_reasonable = false;
//
//
//    //// w-jet candidates
//    //printf("num wjet candidates = %d\n", indices_wjets_.size());
//    //if( indices_wjets_.size() == 2 )
//    //    indices_wjets = indices_wjets_;
//    //else
//    //{
//    //    vector<int> vec_candidates;
//    //    vector<double> vec_chi2_values;
//    //    for(unsigned int i = 0; i<indices_wjets_.size(); ++i)
//    //    {
//
//    //    }
//    //}
//
//    ////printf("[%d, %d, %d]\n", index_bjet, indices_wjets[0], indices_wjets[1]);
//    //return is_reasonable;
//}
//
//// caveat: omit this function temporarily
//bool get_gen_matched_jets(int &index_bjet, vector<int> &indices_wjets)
//{
//    // have a b-jet && all indices are non-negative
//    bool has_reasonable_match = true;
//    vector<int> jets_index_genMatched;
//    jets_index_genMatched.push_back(genMatched_jet0_index());
//    jets_index_genMatched.push_back(genMatched_jet1_index());
//    jets_index_genMatched.push_back(genMatched_jet2_index());
//    vector<int> jets_pdgId_genMatched;
//    jets_pdgId_genMatched.push_back(genMatched_jet0_pdgId());
//    jets_pdgId_genMatched.push_back(genMatched_jet1_pdgId());
//    jets_pdgId_genMatched.push_back(genMatched_jet2_pdgId());
//    vector<double> jets_deltaR_genMatched;
//    jets_deltaR_genMatched.push_back(genMatched_jet0_deltaR());
//    jets_deltaR_genMatched.push_back(genMatched_jet1_deltaR());
//    jets_deltaR_genMatched.push_back(genMatched_jet2_deltaR());
//
//    //for(int i=0; i<3; ++i)
//    //    printf("[check] get_gen_matched_jets: index = %d, pdgId = %d, deltaR = %.2f\n", jets_index_genMatched[i], jets_pdgId_genMatched[i], jets_deltaR_genMatched[i]);
//
//    has_reasonable_match = identify_bjet_and_wjets(index_bjet, indices_wjets, jets_index_genMatched, jets_pdgId_genMatched, jets_deltaR_genMatched);
//    return has_reasonable_match;
//}
//
//bool gen_matching(vector<TLorentzVector> &partons, vector<TLorentzVector> &jets, vector<int> pdgIds, TLorentzVector &bquark, TLorentzVector &wquark1, TLorentzVector &wquark2)
//{
//    bool has_reasonable_match = true;  
//
//    vector<int> vec_genIndex;
//    vector<int> vec_pdgId_register;
//    vector<int> vec_index_register;
//    vector<double> vec_deltaR_register;
//    for( unsigned int genLoop = 0 ; genLoop < partons.size(); genLoop++ ) {
//        TLorentzVector part = partons[genLoop];
//        vector<double> vec_deltaR;
//        for(unsigned int index = 0 ; index < jets.size(); index++){
//            TLorentzVector jet = jets[index];
//            double deltaR = sqrt( (jet.Eta()-part.Eta())*(jet.Eta()-part.Eta()) + (jet.Phi()-part.Phi())*(jet.Phi()-part.Phi()) );
//            vec_deltaR.push_back(deltaR);
//        }
//        vector<std::pair<int, double> > vec_deltaR_sorted = sortVectorSmaller(vec_deltaR);
//
//        if(vec_deltaR_sorted[0].second > 0.4) continue;
//
//        vec_genIndex.push_back(genLoop);
//        vec_pdgId_register.push_back(pdgIds[genLoop]);
//        vec_index_register.push_back(vec_deltaR_sorted[0].first);
//        vec_deltaR_register.push_back(vec_deltaR_sorted[0].second);
//
//        //printf("genLoop = %d, ", genLoop);
//        //printf("pdgIds[genLoop] = %2d, ", pdgIds[genLoop]);
//        //printf("vec_deltaR_sorted[0].first = %d, ", vec_deltaR_sorted[0].first);
//        //printf("vec_deltaR_sorted[0].second = %.2f\n", vec_deltaR_sorted[0].second);
//    }
//
//    has_reasonable_match = vec_pdgId_register.size() >= 3;
//    if(has_reasonable_match)
//    {
//        // consistent check -> yes consistent
//        //printf("gen indices = [%d, %d, %d]\n", vec_genIndex[0], vec_genIndex[1], vec_genIndex[2] );
//        //printf("pdg codes   = [%d, %d, %d]\n", vec_pdgId_register[0], vec_pdgId_register[1], vec_pdgId_register[2] );
//        //printf("jet indices = [%d, %d, %d]\n", vec_index_register[0], vec_index_register[1], vec_index_register[2] );
//        //printf("jet flashgg = [%.0f, %.0f, %.0f]\n", genMatched_jet0_index(), genMatched_jet1_index(), genMatched_jet2_index() );
//
//        int index_bquark;
//        vector<int> indices_wquarks;
//        // identify b-jet
//        has_reasonable_match = identify_bjet(index_bquark, vec_genIndex, vec_pdgId_register, vec_deltaR_register);
//
//        // identify w-jets
//        for(unsigned int i = 0; i<indices.size(); ++i)
//        {
//            int index = indices[i];
//            int pdgId = jets_pdgId_genMatched[i];
//            double deltaR = jets_deltaR_genMatched[i];
//            //printf("index: %d, pdgId: %d, deltaR: %.2f\n", index, pdgId, deltaR);
//            if(index >= 0) {
//                if(abs(pdgId) == 5) {
//                    vec_bjet_position.push_back(i);
//                    vec_bjet_index.push_back(index);
//                    vec_bjet_deltaR.push_back(deltaR);
//                } else {
//                    vec_wjet_position.push_back(i);
//                    vec_wjet_index.push_back(index);
//                    vec_wjet_deltaR.push_back(deltaR);
//                }
//            }
//        }
//
//        for(unsigned int i = 0; i<vec_wjet_index.size(); ++i)
//        {
//            for(unsigned int j = i+1; j<vec_wjet_index.size(); ++j)
//            {
//                TLorentzVector wquark1 = partons[vec_wjet_index[i]];
//                TLorentzVector wquark2 = partons[vec_wjet_index[j]];
//            }
//        }
//
//        bquark = partons[index_bquark];
//        wquark1 = partons[indices_wquarks[0]];
//        wquark2 = partons[indices_wquarks[1]];
//    }
//
//    return has_reasonable_match;
//}

void makePlot(TCanvas *c1, TH1F *h, TString filename) {
  h->SetLineWidth(2);
  h->Draw("hist");
  c1->SaveAs(filename);
}

void makePlot_twoHists(TCanvas *c1, TH1F *h1, TH1F *h2, TString filename) {
    //h1->SetStats(0);
    //h2->SetStats(0);

    h1->SetLineWidth(2);
    h2->SetLineWidth(2);
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);

    double scale = 1.2;
    double value1 = h1->GetMaximum();
    double value2 = h2->GetMaximum();
    double max_scope = (value1 > value2) ? value1 : value2;
    h1->SetMaximum(max_scope*scale);

    h1->Draw("hist");
    c1->Modified(); c1->Update();
    TPaveStats *stats1 = (TPaveStats*) c1->GetPrimitive("stats");
    stats1->SetName("Minimum chi-2");
    stats1->SetTextColor(kBlue);

    h2->Draw("hist;same");
    c1->Modified(); c1->Update();
    TPaveStats *stats2 = (TPaveStats*) c1->GetPrimitive("stats");
    stats2->SetName("Truth-Matched");
    stats2->SetY1NDC(.4);
    stats2->SetY2NDC(.6);
    stats2->SetTextColor(kRed);

    c1->Modified(); c1->Update();
    c1->SaveAs(filename);
}

void print_counter_percentage(TString title, int counter, int tot){
    double percentage = (double) counter / (double) tot;
    printf("%-80s: counter = %d / %d (%.3f)\n", title.Data(), counter, tot, percentage);
}

const double min_photon_ID_presel_cut = -0.7;

bool passes_selection(TString tag, float minIDMVA_, float maxIDMVA_, float mva_value = -1) {
  if (tag == "ttHHadronic_RunII_MVA_Presel") {
    if (dipho_mass() < 100 || dipho_mass() > 180) 	return false;
    if (n_jets() < 3)					return false;
    if (n_L_bjets() < 1)					return false;
    if (minIDMVA_ < min_photon_ID_presel_cut)		return false;
    return true;
  }
  
  else 
    cout << "Did not recognize tag name" << endl;

  return false;
}

double get_ratio(double a, double b)
{
    double ratio = (a - b) / a;
    return ratio;
}

bool mycheck(TString label, int &counter, double a, double b, double  dipho_pt)
{
    bool is_inconsistent = false;
    double ratio = get_ratio(a, b);
    if(ratio > 1e-7)
    {
      is_inconsistent = true;
      //printf("[check] %s dipho_pt = %7.3f, online: %.7f, offline: %.7f, ratio = %.3f\n", dipho_pt, label.Data(), a, b, ratio);
    } else {
      //printf("Nice job! online = %.7f, offline = %.7f\n", a, b);
      counter += 1;
    }

    return is_inconsistent;
}

// structure my_jets_info{{{
typedef struct{
    float chi2_value_;
    float chi2_bjet_pt_;
    float chi2_bjet_eta_;
    float chi2_bjet_phi_;
    float chi2_bjet_energy_;
    float chi2_wjet1_pt_;
    float chi2_wjet1_eta_;
    float chi2_wjet1_phi_;
    float chi2_wjet1_energy_;
    float chi2_wjet2_pt_;
    float chi2_wjet2_eta_;
    float chi2_wjet2_phi_;
    float chi2_wjet2_energy_;
    float chi2_wboson_pt_;
    float chi2_wboson_eta_;
    float chi2_wboson_phi_;
    float chi2_wboson_energy_;
    float chi2_wboson_mass_;
    float chi2_top_pt_;
    float chi2_top_eta_;
    float chi2_top_phi_;
    float chi2_top_energy_;
    float chi2_top_mass_;
    float chi2_tprime_pt_;
    float chi2_tprime_eta_;
    float chi2_tprime_phi_;
    float chi2_tprime_energy_;
    float chi2_tprime_mass_;
} my_jets_info;
//}}}
void check_ultra_large_tprime_mass(bool condition, my_jets_info instance)
{
    if(condition)
    {
        std::cout << "chi2_value_: "         << instance.chi2_value_         << ", ";
        std::cout << "chi2_bjet_pt_: "       << instance.chi2_bjet_pt_       << ", ";
        std::cout << "chi2_bjet_eta_: "      << instance.chi2_bjet_eta_      << ", ";
        std::cout << "chi2_bjet_phi_: "      << instance.chi2_bjet_phi_      << ", ";
        std::cout << "chi2_bjet_energy_: "   << instance.chi2_bjet_energy_   << ", ";
        std::cout << "chi2_wjet1_pt_: "      << instance.chi2_wjet1_pt_      << ", ";
        std::cout << "chi2_wjet1_eta_: "     << instance.chi2_wjet1_eta_     << ", ";
        std::cout << "chi2_wjet1_phi_: "     << instance.chi2_wjet1_phi_     << ", ";
        std::cout << "chi2_wjet1_energy_: "  << instance.chi2_wjet1_energy_  << ", ";
        std::cout << "chi2_wjet2_pt_: "      << instance.chi2_wjet2_pt_      << ", ";
        std::cout << "chi2_wjet2_eta_: "     << instance.chi2_wjet2_eta_     << ", ";
        std::cout << "chi2_wjet2_phi_: "     << instance.chi2_wjet2_phi_     << ", ";
        std::cout << "chi2_wjet2_energy_: "  << instance.chi2_wjet2_energy_  << ", ";
        std::cout << "chi2_wboson_pt_: "     << instance.chi2_wboson_pt_     << ", ";
        std::cout << "chi2_wboson_eta_: "    << instance.chi2_wboson_eta_    << ", ";
        std::cout << "chi2_wboson_phi_: "    << instance.chi2_wboson_phi_    << ", ";
        std::cout << "chi2_wboson_energy_: " << instance.chi2_wboson_energy_ << ", ";
        std::cout << "chi2_wboson_mass_: "   << instance.chi2_wboson_mass_   << ", ";
        std::cout << "chi2_top_pt_: "        << instance.chi2_top_pt_        << ", ";
        std::cout << "chi2_top_eta_: "       << instance.chi2_top_eta_       << ", ";
        std::cout << "chi2_top_phi_: "       << instance.chi2_top_phi_       << ", ";
        std::cout << "chi2_top_energy_: "    << instance.chi2_top_energy_    << ", ";
        std::cout << "chi2_top_mass_: "      << instance.chi2_top_mass_      << ", ";
        std::cout << "chi2_tprime_pt_: "     << instance.chi2_tprime_pt_     << ", ";
        std::cout << "chi2_tprime_eta_: "    << instance.chi2_tprime_eta_    << ", ";
        std::cout << "chi2_tprime_phi_: "    << instance.chi2_tprime_phi_    << ", ";
        std::cout << "chi2_tprime_energy_: " << instance.chi2_tprime_energy_ << ", ";
        std::cout << "chi2_tprime_mass_: "   << instance.chi2_tprime_mass_   << ", ";
        std::cout << std::endl;
    }
}
#endif
