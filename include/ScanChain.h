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
#include "TVector3.h"
#include "TString.h"

#include <TCanvas.h>

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

void makePlot(TCanvas *c1, TH1F *h, TString filename) {
  h->SetLineWidth(2);
  h->Draw("hist");
  c1->SaveAs(filename);
}

void print_counter_percentage(TString title, int counter, int tot){
    double percentage = (double) counter / (double) tot;
    printf("%s: counter = %d / %d (%.2f)\n", title.Data(), counter, tot, percentage);
}

#endif
