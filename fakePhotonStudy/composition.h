#ifndef __COMPOSITION_H__
#define __COMPOSITION_H__

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "TFile.h"
#include "TString.h"
#include "THStack.h"
#include "TList.h"
#include <vector>
using namespace RooFit;
 
void setPad() //{{{
{
    gPad->SetGrid();
    gPad->SetTicks();
} //}}}
void cosmetic_histogram(TH1D* h, TString xtitle) //{{{
{
    h -> SetStats(0);
    h -> SetMarkerStyle(20);
    h -> GetXaxis() -> SetTitle(xtitle.Data());

    //h -> SetMinimum(0);
    h -> SetMaximum(1e+5);
    h -> SetMinimum(1e-1);
} //}}}
void makeHist(THStack *hs, TH1D* h, std::vector<double> v = {}) //{{{
{
    setPad();
    h->Draw("ep1");

    hs->Draw("hist, same");
    h->Draw("ep1, same");

    gPad->SetLogy(1);

    if(v.size() > 0)
    {
        int counter = 0;
        printf(">>> do the follows\n");

        TList* mylist = hs->GetHists();
        for(const auto&& obj: *mylist)
        {
            TH1D* h_ele = (TH1D*) obj;
            TString name = obj->GetName();

            if(name.Contains("QCD")) {
                h_ele->Scale(v[0]);
                printf("check: %d, %s, %f\n", counter, obj->GetName(), v[0]);
            }

            if(name.Contains("DiPhoton")) {
                h_ele->Scale(v[1]);
                printf("check: %d, %s, %f\n", counter, obj->GetName(), v[1]);
            }
                
            counter += 1;
        }
        
        gPad->Modified();
        gPad->Update();
        hs->Draw("hist, same");
        h->Draw("ep1, same");
    }
} //}}}
void addHistograms(TH1D* h, TH1D* other) //{{{
{
    int bins = h->GetSize();
    for(int i=0; i<bins; ++i)
    {
        double content = h->GetBinContent(i) + other->GetBinContent(i);
        h->SetBinContent(i, content);
    }
}
//}}}
void make_stacks(THStack *hs, vector<TH1D*> v, TH1D *&h) //{{{Data
{
    // add in reverse way
    int counter = 0;
    for(auto iter=v.rbegin(); iter!=v.rend(); ++iter)
    {
        hs -> Add(*iter);
        if(counter==0) {
            h = (TH1D*) (*iter)->Clone();
        } else {
            addHistograms(h, *iter);
        }
        counter += 1;
    }
} //}}}
void make_stacks(THStack *hs, vector<TH1D*> v) //{{{
{
    // add in reverse way
    for(auto iter=v.rbegin(); iter!=v.rend(); ++iter)
        hs -> Add(*iter);
} //}}}
void set_main_pad(TPad* mainPad, bool log) //{{{
{
  //mCanvas->cd();
  mainPad = new TPad("p_main", "p_main", 0.0, 0.3, 1.0, 1.0);
  mainPad->SetBottomMargin(0.02);
  mainPad->SetRightMargin(0.07);
  mainPad->SetTopMargin(0.08);
  mainPad->SetLeftMargin(0.12);
  mainPad->Draw();
  mainPad->cd();
  //if (log) mainPad->SetLogy();
  mainPad->SetGrid();
} //}}}
void set_rat_pad(TPad* ratPad) //{{{
{
  //mCanvas->cd();
  ratPad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 0.3);
  //ratPad->SetBottomMargin(0.36);
  ratPad->SetRightMargin(0.07);
  //ratPad->SetTopMargin(0.07);
  ratPad->SetLeftMargin(0.12);
  //ratPad->Draw();
  //ratPad->cd();
  //ratPad->SetGridy();
} //}}}

#endif
