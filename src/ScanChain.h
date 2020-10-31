#ifndef _SCAN_CHAIN_H_
#define _SCAN_CHAIN_H_

#include <iostream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"

// tprimetHHadronic
#include "tprimetHHadronic.cc"

using namespace std;
using namespace tprime;

bool sortByValue(const std::pair<int,double>& pair1, const std::pair<int,double>& pair2 ) {
  return pair1.second > pair2.second;
}

vector< std::pair<int, double> > sortVector(const vector<double> v) {
  vector< std::pair<int, double> > v2;
  for (int i = 0; i < v.size(); i++)
    v2.push_back(std::pair<int, double>(i, v[i]));
  std::sort(v2.begin(), v2.end(), sortByValue);
  return v2;
}

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
  return vJets;
}
#endif
