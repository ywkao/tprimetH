#ifndef _TTH_PROCESS_H_
#define _TTH_PROCESS_H_

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

using namespace std;

const int nGenLeptonCats = 6;
const int nRecoLeptonCats = 7;
const int nYearCats = 3; 
const int nGenPhotonCats = 3;
const int nGenPhotonDetailCats = 6;
const int nPhotonLocations = 3;
const int nMVACategories = 2;


class Process
{
  public:
    Process(TFile* f, TString name); 
    ~Process();  

    void add_histogram(TString name, int nBins, double xLow, double xHigh);
    void add_2D_histogram(TString name, int nBinsX, double xLow, double xHigh, int nBinsY, double yLow, double yHigh);
    void fill_histogram(TString name, double value, double weight, int genLeptonId = -1, int genPhotonId = -1, int genPhotonDetailId = -1, int photonLocationId = -1, int mvaCategoryId = -1);
    void fill_histogram(TString name, double value, double weight, vector<int> vId);
    void fill_2D_histogram(TString name, double valueX, double valueY, double weight, vector<int> vId);

  private:
    TFile* mFile;
    TString mName;

    vector<TH1D*> mH;
    vector<TH2D*> mH_2D;

    bool mGenLepton;
    vector<vector<TH1D*>> mHGenLeptonComp;

    bool mRecoLepton;
    vector<vector<TH1D*>> mHRecoLeptonComp;

    bool mYear;
    vector<vector<TH1D*>> mHYearComp;

    bool mGenPhoton;
    vector<vector<TH1D*>> mHGenPhotonComp;

    bool mGenPhotonDetail;
    vector<vector<TH1D*>> mHGenPhotonDetailComp;

    bool mPhotonLocations;
    vector<vector<TH1D*>> mHPhotonLocations;

    bool mMVACategories;
    vector<vector<TH1D*>> mHMVACategories;

    vector<vector<TH2D*>> mHGenLeptonComp_2D;
    vector<vector<TH2D*>> mHRecoLeptonComp_2D;
    vector<vector<TH2D*>> mHYearComp_2D;
    vector<vector<TH2D*>> mHGenPhotonComp_2D;
    vector<vector<TH2D*>> mHGenPhotonDetailComp_2D;
    vector<vector<TH2D*>> mHPhotonLocations_2D;
    vector<vector<TH2D*>> mHMVACategories_2D;
    
    std::map<TString, int> mMap;
    std::map<TString, int> mMap_2D;
};

inline Process::~Process()
{
  for (int i = 0; i < mH.size(); i++)
    delete mH[i];
  for (int i = 0; i < mHGenLeptonComp.size(); i ++ ) {
    for (int j = 0; j < mHGenLeptonComp[i].size(); j++)
      delete mHGenLeptonComp[i][j];
  }
  for (int i = 0; i < mHRecoLeptonComp.size(); i ++ ) {
    for (int j = 0; j < mHRecoLeptonComp[i].size(); j++)
      delete mHRecoLeptonComp[i][j];
  }
  for (int i = 0; i < mHYearComp.size(); i ++ ) {
    for (int j = 0; j < mHYearComp[i].size(); j++)
      delete mHYearComp[i][j];
  }
  for (int i = 0; i < mHGenPhotonComp.size(); i ++ ) {
    for (int j = 0; j < mHGenPhotonComp[i].size(); j++)
      delete mHGenPhotonComp[i][j];
  }
  for (int i = 0; i < mHGenPhotonDetailComp.size(); i ++ ) {
    for (int j = 0; j < mHGenPhotonDetailComp[i].size(); j++)
      delete mHGenPhotonDetailComp[i][j];
  }
  for (int i = 0; i < mHPhotonLocations.size(); i ++ ) {
    for (int j = 0; j < mHPhotonLocations[i].size(); j++) 
    delete mHPhotonLocations[i][j];
  }
  for (int i = 0; i < mHMVACategories.size(); i ++ ) {
    for (int j = 0; j < mHMVACategories[i].size(); j++)
    delete mHMVACategories[i][j];
  }
  for (int i = 0; i < mHGenLeptonComp_2D.size(); i ++ ) {
    for (int j = 0; j < mHGenLeptonComp_2D.size(); j++)
      delete mHGenLeptonComp_2D[i][j];
  }
  for (int i = 0; i < mHRecoLeptonComp_2D.size(); i ++ ) {
    for (int j = 0; j < mHRecoLeptonComp_2D.size(); j++)
      delete mHRecoLeptonComp_2D[i][j];
  }
  for (int i = 0; i < mHYearComp_2D.size(); i ++ ) {
    for (int j = 0; j < mHYearComp_2D.size(); j++)
      delete mHYearComp_2D[i][j];
  }
  for (int i = 0; i < mHGenPhotonComp_2D.size(); i ++ ) {
    for (int j = 0; j < mHGenPhotonComp_2D.size(); j++)
      delete mHGenPhotonComp_2D[i][j];
  }
  for (int i = 0; i < mHGenPhotonDetailComp_2D.size(); i ++ ) {
    for (int j = 0; j < mHGenPhotonDetailComp_2D.size(); j++)
      delete mHGenPhotonDetailComp_2D[i][j];
  }
  for (int i = 0; i < mHPhotonLocations_2D.size(); i ++ ) {
    for (int j = 0; j < mHPhotonLocations_2D.size(); j++)
    delete mHPhotonLocations_2D[i][j];
  }
  for (int i = 0; i < mHMVACategories_2D.size(); i ++ ) {
    for (int j = 0; j < mHMVACategories_2D.size(); j++)
    delete mHMVACategories_2D[i][j];
  }



}

inline Process::Process(TFile* f, TString name) 
{
  mFile = f;
  f->cd();
  mName = name;
  mGenLepton = false;
  mRecoLepton = false;
  mYear = true;
  mGenPhoton = false;
  mGenPhotonDetail = false;
  mPhotonLocations = false; 
  mMVACategories = false;
}

inline void Process::add_histogram(TString name, int nBins, double xLow, double xHigh)
{
  mH.push_back(new TH1D(name + "_" + mName, "", nBins, xLow, xHigh));
  mH[mH.size() - 1]->Sumw2();

  if (mGenLepton) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nGenLeptonCats; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "GenLepton_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }       
    mHGenLeptonComp.push_back(vTemp);
  }

  if (mRecoLepton) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nRecoLeptonCats; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "RecoLepton_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }
    mHRecoLeptonComp.push_back(vTemp);
  }

  if (mYear) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nYearCats; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "Year_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }
    mHYearComp.push_back(vTemp);
  }

  if (mGenPhoton) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nGenPhotonCats; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "GenPhoton_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }       
    mHGenPhotonComp.push_back(vTemp);
  }

  if (mGenPhotonDetail) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nGenPhotonDetailCats; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "GenPhotonDetail_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }
    mHGenPhotonDetailComp.push_back(vTemp);
  }

  if (mPhotonLocations) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nPhotonLocations; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "PhotonLocations_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }
    mHPhotonLocations.push_back(vTemp);
  }

  if (mMVACategories) {
    vector<TH1D*> vTemp;
    for (int i = 0; i < nMVACategories; i++) {
      vTemp.push_back(new TH1D(name + "_" + mName + "MVACategories_" + to_string(i), "", nBins, xLow, xHigh));
      vTemp[i]->Sumw2();
    }
    mHMVACategories.push_back(vTemp);
  }

  mMap[name] = mH.size() - 1;
}

inline void Process::add_2D_histogram(TString name, int nBinsX, double xLow, double xHigh, int nBinsY, double yLow, double yHigh)
{
  mH_2D.push_back(new TH2D(name + "_" + mName, "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
  mH_2D[mH_2D.size() - 1]->Sumw2();

  if (mGenLepton) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nGenLeptonCats; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "GenLepton_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHGenLeptonComp_2D.push_back(vTemp);
  }

  if (mRecoLepton) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nRecoLeptonCats; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "RecoLepton_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHRecoLeptonComp_2D.push_back(vTemp);
  }

  if (mYear) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nYearCats; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "Year_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHYearComp_2D.push_back(vTemp);
  }

  if (mGenPhoton) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nGenPhotonCats; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "GenPhoton_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHGenPhotonComp_2D.push_back(vTemp);
  }

  if (mGenPhotonDetail) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nGenPhotonDetailCats; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "GenPhotonDetail_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHGenPhotonDetailComp_2D.push_back(vTemp);
  }

  if (mPhotonLocations) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nPhotonLocations; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "PhotonLocations_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHPhotonLocations_2D.push_back(vTemp);
  }

  if (mMVACategories) {
    vector<TH2D*> vTemp;
    for (int i = 0; i < nMVACategories; i++) {
      vTemp.push_back(new TH2D(name + "_" + mName + "MVACategories_" + to_string(i), "", nBinsX, xLow, xHigh, nBinsY, yLow, yHigh));
      vTemp[i]->Sumw2();
    }
    mHMVACategories_2D.push_back(vTemp);
  }

  mMap_2D[name] = mH_2D.size() - 1;

}

inline void Process::fill_histogram(TString name, double value, double weight, int genLeptonId, int genPhotonId, int genPhotonDetailId, int photonLocationId, int mvaCategoryId)
{
  std::map<TString, int>::iterator it;
  it = mMap.find(name);
  if (it == mMap.end()) {
    cout << "Did not match this hist: " << name << endl;
    return;
  }
  
  int idx = mMap.find(name)->second;
  mH[idx]->Fill(value, weight);

  if (genLeptonId >= 0 && mGenLepton)
    mHGenLeptonComp[idx][genLeptonId]->Fill(value, weight);
  if (genPhotonId >= 0 && mGenPhoton)
    mHGenPhotonComp[idx][genPhotonId]->Fill(value, weight);
  if (genPhotonDetailId >= 0 && mGenPhotonDetail)
    mHGenPhotonDetailComp[idx][genPhotonDetailId]->Fill(value, weight);
  if (photonLocationId >= 0 && mPhotonLocations)
    mHPhotonLocations[idx][photonLocationId]->Fill(value, weight);
  if (mvaCategoryId >= 0 && mMVACategories)
    mHMVACategories[idx][mvaCategoryId]->Fill(value, weight);  
}

inline void Process::fill_histogram(TString name, double value, double weight, vector<int> vId)
{
  int idx = mMap.find(name)->second;
  mH[idx]->Fill(value, weight);

  int genLeptonId = vId.size() > 0 ? vId[0] : -1;
  int genPhotonId = vId.size() > 1 ? vId[1] : -1;
  int genPhotonDetailId = vId.size() > 2 ? vId[2] : -1;
  int photonLocationId = vId.size() > 3 ? vId[3]: -1;
  int mvaCategoryId = vId.size() > 4 ? vId[4]: -1;
  int recoLeptonId = vId.size() > 5 ? vId[5]: -1;
  int yearId = vId.size() > 6 ? vId[6]: -1;

  if (genLeptonId >= 0  && mGenLepton)
    mHGenLeptonComp[idx][genLeptonId]->Fill(value, weight);
  if (recoLeptonId >= 0 && mRecoLepton)
    mHRecoLeptonComp[idx][recoLeptonId]->Fill(value, weight);
  if (yearId >= 0 && mYear)
    mHYearComp[idx][yearId]->Fill(value, weight);
  if (genPhotonId >= 0 && mGenPhoton)
    mHGenPhotonComp[idx][genPhotonId]->Fill(value, weight);
  if (genPhotonDetailId >= 0 && mGenPhotonDetail)
    mHGenPhotonDetailComp[idx][genPhotonDetailId]->Fill(value, weight);
  if (photonLocationId >= 0 && mPhotonLocations)
    mHPhotonLocations[idx][photonLocationId]->Fill(value, weight);
  if (mvaCategoryId >= 0 && mMVACategories)
    mHMVACategories[idx][mvaCategoryId]->Fill(value, weight);
}

inline void Process::fill_2D_histogram(TString name, double valueX, double valueY, double weight, vector<int> vId)
{
  int idx = mMap_2D.find(name)->second;
  mH_2D[idx]->Fill(valueX, valueY, weight);

  int genLeptonId = vId.size() > 0 ? vId[0] : -1;
  int genPhotonId = vId.size() > 1 ? vId[1] : -1;
  int genPhotonDetailId = vId.size() > 2 ? vId[2] : -1;
  int photonLocationId = vId.size() > 3 ? vId[3]: -1;
  int mvaCategoryId = vId.size() > 4 ? vId[4]: -1;
  int recoLeptonId = vId.size() > 5 ? vId[5]: -1;
  int yearId = vId.size() > 6 ? vId[6]: -1;

  if (genLeptonId >= 0 && mGenLepton)
    mHGenLeptonComp_2D[idx][genLeptonId]->Fill(valueX, valueY, weight);
  if (recoLeptonId >= 0 && mRecoLepton)
    mHRecoLeptonComp_2D[idx][recoLeptonId]->Fill(valueX, valueY, weight);
  if (yearId >= 0 && mYear)
    mHYearComp_2D[idx][yearId]->Fill(valueX, valueY, weight);
  if (genPhotonId >= 0 && mGenPhoton)
    mHGenPhotonComp_2D[idx][genPhotonId]->Fill(valueX, valueY, weight);
  if (genPhotonDetailId >= 0 && mGenPhotonDetail)
    mHGenPhotonDetailComp_2D[idx][genPhotonDetailId]->Fill(valueX, valueY, weight);
  if (photonLocationId >= 0 && mPhotonLocations)
    mHPhotonLocations_2D[idx][photonLocationId]->Fill(valueX, valueY, weight);
  if (mvaCategoryId >= 0 && mMVACategories)
    mHMVACategories_2D[idx][mvaCategoryId]->Fill(valueX, valueY, weight); 
}

#endif // _TTH_PROCESS_H_
