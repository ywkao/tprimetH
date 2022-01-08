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
 
void setPad();
void cosmetic_histogram(TH1D* h, TString xtitle);
void makeHist(THStack *hs, TH1D* h, TH1D* other, std::vector<double> v = {});
void addHistograms(TH1D* h, TH1D* other);
TH1D* convert_ht_range(TH1D* h);

void template_fit()
{
    TString input_file = "./rootfiles/myhist_combine_RunII.root";
    TString input_tree = "./rootfiles/MVABaby_Data_simultaneousFit.root";
    //TString input_file = "./rootfiles/myhist_low_photon_sideband.root";
    //TString input_tree = "./rootfiles/MVABaby_low_photon_sideband_Data.root";
    
    // make stack plots {{{
    //TString path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH";
    //TString input_file = path + "/shortcut_plots/plots_20210725/myhist_combine_RunII.root";
    TFile *fout = TFile::Open("output.root", "recreate");

    TFile *fin = TFile::Open(input_file);
    std::vector<TString> backgrounds = {"QCD_GammaJets_imputed", "DiPhoton", "TTGG", "TTGJets", "TTJets", "VG"};
    std::vector<Int_t> colors = {kOrange+6, kRed+1, kGreen-2, kGreen-7, kSpring+10, kViolet-9};
    std::vector<TH1D*> vH_maxPhotonIDMVA_Bkg;
    std::vector<TH1D*> vH_minPhotonIDMVA_Bkg;
    std::vector<TH1D*> vH_ht_Bkg;

    TH1D *h_maxPhotonIDMVA_others;
    TH1D *h_minPhotonIDMVA_others;
    TH1D *h_ht_others;

    TH1D *h_maxPhotonIDMVA_Data = (TH1D*) fin->Get("hPhotonMaxIDMVA_fine_Data");
    TH1D *h_minPhotonIDMVA_Data = (TH1D*) fin->Get("hPhotonMinIDMVA_fine_Data");
    TH1D *h_ht_Data = convert_ht_range( (TH1D*) fin->Get("hHT_coarse_Data") );
    cosmetic_histogram(h_maxPhotonIDMVA_Data, "Max Photon ID MVA");
    cosmetic_histogram(h_minPhotonIDMVA_Data, "Min Photon ID MVA");
    cosmetic_histogram(h_ht_Data, "HT");

    TH1D *h_maxPhotonIDMVA_subtracted = new TH1D(*h_maxPhotonIDMVA_Data);
    TH1D *h_minPhotonIDMVA_subtracted = new TH1D(*h_minPhotonIDMVA_Data);
    TH1D *h_ht_subtracted = new TH1D(*h_ht_Data);

    double yh_data = 1000;
    double yh_qcd = 1000;
    double yh_dip = 1000;
    double yh_oth = 1000;

    THStack *hs_max = new THStack("hs_max", "");
    THStack *hs_min = new THStack("hs_min", "");
    THStack *hs_ht = new THStack("hs_ht", "");
    for(int i=backgrounds.size()-1; i>=0; --i)
    {
        TH1D *h_max = (TH1D*) fin->Get("hPhotonMaxIDMVA_fine_" + backgrounds[i]);
        TH1D *h_min = (TH1D*) fin->Get("hPhotonMinIDMVA_fine_" + backgrounds[i]);
        TH1D *h_ht = convert_ht_range( (TH1D*) fin->Get("hHT_coarse_" + backgrounds[i]) );
        h_max -> SetFillColor(colors[i]);
        h_min -> SetFillColor(colors[i]);
        h_ht -> SetFillColor(colors[i]);
        vH_maxPhotonIDMVA_Bkg.push_back(h_max);
        vH_minPhotonIDMVA_Bkg.push_back(h_min);
        vH_ht_Bkg.push_back(h_ht);
        hs_max -> Add(h_max);
        hs_min -> Add(h_min);
        hs_ht -> Add(h_ht);

        if(i>1) {
            // exclude QCD and gamma gamma + jets
            h_maxPhotonIDMVA_subtracted -> Add(h_max, -1.0);
            h_minPhotonIDMVA_subtracted -> Add(h_min, -1.0);
            h_ht_subtracted -> Add(h_ht, -1.0);

            if(i==backgrounds.size()-1) {
                h_maxPhotonIDMVA_others = (TH1D*) h_max->Clone();
                h_minPhotonIDMVA_others = (TH1D*) h_min->Clone();
                h_ht_others = (TH1D*) h_ht->Clone();
            } else {
                addHistograms(h_maxPhotonIDMVA_others, h_max);
                addHistograms(h_minPhotonIDMVA_others, h_min);
                addHistograms(h_ht_others, h_ht);
            }

        } else {
            printf("%s: %f\n", backgrounds[i].Data(), h_max->Integral(0, h_max->GetSize()-1));
            printf("%s: %f\n", backgrounds[i].Data(), h_min->Integral(0, h_min->GetSize()-1));

            if(i==1)
                yh_dip = h_max->Integral(0, h_max->GetSize()-1);

            if(i==0) {
                yh_qcd = h_max->Integral(0, h_max->GetSize()-1);
                yh_oth = h_maxPhotonIDMVA_others->Integral(0, h_maxPhotonIDMVA_others->GetSize()-1);
                yh_data = h_maxPhotonIDMVA_Data->Integral(0, h_maxPhotonIDMVA_Data->GetSize()-1);

                printf("Others: %f\n", h_maxPhotonIDMVA_others->Integral(0, h_maxPhotonIDMVA_others->GetSize()-1));
                printf("Others: %f\n", h_minPhotonIDMVA_others->Integral(0, h_minPhotonIDMVA_others->GetSize()-1));
                printf("Others: %f\n", h_ht_others->Integral(0, h_ht_others->GetSize()-1));
                printf("Data: %f\n", h_maxPhotonIDMVA_Data->Integral(0, h_maxPhotonIDMVA_Data->GetSize()-1));
                printf("Data: %f\n", h_minPhotonIDMVA_Data->Integral(0, h_minPhotonIDMVA_Data->GetSize()-1));
                printf("Data: %f\n", h_ht_Data->Integral(0, h_ht_Data->GetSize()-1));
            }
        }
    }

    TH1D *h_PhotonIDMVA_combine = new TH1D(*h_maxPhotonIDMVA_subtracted);
    h_PhotonIDMVA_combine -> Add(h_minPhotonIDMVA_subtracted, 1.0);

    TCanvas *c1 = new TCanvas("c1", "", 2400, 600);
    c1->Divide(3);
    c1->cd(1);
    makeHist(hs_max, h_maxPhotonIDMVA_Data, h_maxPhotonIDMVA_others);
    c1->cd(2);
    makeHist(hs_min, h_minPhotonIDMVA_Data, h_minPhotonIDMVA_others);
    c1->cd(3);
    makeHist(hs_ht, h_ht_Data, h_ht_others);
    c1->SaveAs("eos_test/photonIDMVA_before.png");
    c1->SaveAs("eos_test/photonIDMVA_before.pdf");
    //}}}
    
    // observables, create hist templates{{{
    RooRealVar idmva("idmva","Photon ID MVA",-1.,1.);
    RooCategory channel("channel","channel");
    channel.defineType("maxIDMVA",1);
    channel.defineType("minIDMVA",2);
    channel.defineType("scaledHT",3);
    
    RooDataHist dh_max_data("dh_max_data", "dh_max_data", idmva, Import(*h_maxPhotonIDMVA_Data));
    RooDataHist dh_min_data("dh_min_data", "dh_min_data", idmva, Import(*h_minPhotonIDMVA_Data));
    RooDataHist dh_ht_data("dh_ht_data", "dh_ht_data", idmva, Import(*h_ht_Data));
    RooDataHist dh_max_subtracted("dh_max_subtracted", "dh_max_subtracted", idmva, Import(*h_maxPhotonIDMVA_subtracted));
    RooDataHist dh_min_subtracted("dh_min_subtracted", "dh_min_subtracted", idmva, Import(*h_minPhotonIDMVA_subtracted));
    RooDataHist dh_ht_subtracted("dh_ht_subtracted", "dh_ht_subtracted", idmva, Import(*h_ht_subtracted));
    RooPlot *frame_max = idmva.frame(Title("Imported data of max photon ID MVA"));
    RooPlot *frame_min = idmva.frame(Title("Imported data of min photon ID MVA"));
    RooPlot *frame_ht = idmva.frame(Title("Imported data of HT"));
    
    c1->cd(1);
	setPad();
	dh_max_data.plotOn(frame_max);
	dh_max_subtracted.plotOn(frame_max, MarkerColor(kBlue));
	frame_max->Draw();
    c1->cd(2);
	setPad();
	dh_min_data.plotOn(frame_min);
	dh_min_subtracted.plotOn(frame_min, MarkerColor(kBlue));
	frame_min->Draw();
    c1->cd(3);
	setPad();
	dh_ht_data.plotOn(frame_ht);
	dh_ht_subtracted.plotOn(frame_ht, MarkerColor(kBlue));
	frame_ht->Draw();
    c1->SaveAs("eos_test/imported_hist_data.png");
    c1->SaveAs("eos_test/imported_hist_data.pdf");
    //}}}
    // build models{{{
    // models for channel #1
    RooDataHist dh_max_qcd("dh_max_qcd", "dh_max_qcd", idmva, Import(*vH_maxPhotonIDMVA_Bkg[5]));
    RooDataHist dh_max_dip("dh_max_dip", "dh_max_dip", idmva, Import(*vH_maxPhotonIDMVA_Bkg[4]));
    RooDataHist dh_max_oth("dh_max_oth", "dh_max_oth", idmva, Import(*h_maxPhotonIDMVA_others));
    RooHistPdf pdf_max_qcd("pdf_max_qcd", "pdf_max_qcd", idmva, dh_max_qcd, 0);
    RooHistPdf pdf_max_dip("pdf_max_dip", "pdf_max_dip", idmva, dh_max_dip, 0);
    RooHistPdf pdf_max_oth("pdf_max_oth", "pdf_max_oth", idmva, dh_max_oth, 0);

    // models for channel #2
    RooDataHist dh_min_qcd("dh_min_qcd", "dh_min_qcd", idmva, Import(*vH_minPhotonIDMVA_Bkg[5]));
    RooDataHist dh_min_dip("dh_min_dip", "dh_min_dip", idmva, Import(*vH_minPhotonIDMVA_Bkg[4]));
    RooDataHist dh_min_oth("dh_min_oth", "dh_min_oth", idmva, Import(*h_minPhotonIDMVA_others));
    RooHistPdf pdf_min_qcd("pdf_min_qcd", "pdf_min_qcd", idmva, dh_min_qcd, 0);
    RooHistPdf pdf_min_dip("pdf_min_dip", "pdf_min_dip", idmva, dh_min_dip, 0);
    RooHistPdf pdf_min_oth("pdf_min_oth", "pdf_min_oth", idmva, dh_min_oth, 0);

    // models for channel #3
    RooDataHist dh_ht_qcd("dh_ht_qcd", "dh_ht_qcd", idmva, Import(*vH_ht_Bkg[5]));
    RooDataHist dh_ht_dip("dh_ht_dip", "dh_ht_dip", idmva, Import(*vH_ht_Bkg[4]));
    RooDataHist dh_ht_oth("dh_ht_oth", "dh_ht_oth", idmva, Import(*h_ht_others));
    RooHistPdf pdf_ht_qcd("pdf_ht_qcd", "pdf_ht_qcd", idmva, dh_ht_qcd, 0);
    RooHistPdf pdf_ht_dip("pdf_ht_dip", "pdf_ht_dip", idmva, dh_ht_dip, 0);
    RooHistPdf pdf_ht_oth("pdf_ht_oth", "pdf_ht_oth", idmva, dh_ht_oth, 0);

    //RooPlot *frame = idmva.frame(Title("Check pdf of min photon IDMVA"));
    //c1->cd(1);
	//setPad();
    //vH_minPhotonIDMVA_Bkg[5]->Draw("hist");
    //vH_minPhotonIDMVA_Bkg[4]->Draw("hist,same");
    //h_minPhotonIDMVA_others->Draw("hist,same");
    //c1->cd(2);
	//setPad();
	//dh_min_qcd.plotOn(frame);
	//dh_min_dip.plotOn(frame);
	//dh_min_oth.plotOn(frame);
	//frame->Draw();
    //c1->SaveAs("eos_test/test.png");

    // key factors to extract
    RooRealVar sf_qcd("sf_qcd","sf_qcd",1.06787,0.0,5.0);
    RooRealVar sf_dip("sf_dip","sf_dip",1.38999,0.0,5.0);
    RooRealVar sf_oth("sf_oth","sf_oth",1.0,0.0,5.00);

    //sf_dip.setConstant(true);
    sf_oth.setConstant(true);

    // norm = luminosity * acceptance * efficiency
    //RooRealVar data_norm("data_norm", "data norm", 188240);
    //RooRealVar qcd_norm("qcd_norm","qcd norm",118526.56);
    //RooRealVar dip_norm("dip_norm","dip norm",41626.71);
    //RooRealVar oth_norm("oth_norm","oth norm",3806.89);
    RooRealVar data_norm("data_norm", "data norm", yh_data);
    RooRealVar qcd_norm("qcd_norm","qcd norm", yh_qcd);
    RooRealVar dip_norm("dip_norm","dip norm", yh_dip);
    RooRealVar oth_norm("oth_norm","oth norm", yh_oth);

    RooProduct yield_qcd("nqcd","qcd yields", RooArgList(sf_qcd,qcd_norm));
    RooProduct yield_dip("ndip","dip yields", RooArgList(sf_dip,dip_norm));
    RooProduct yield_oth("noth","oth yields", RooArgList(sf_oth,oth_norm));

    RooAddPdf ch1_model("ch1_model","ch1 model",
                        RooArgList(pdf_max_qcd,pdf_max_dip,pdf_max_oth),RooArgList(yield_qcd,yield_dip,yield_oth));
    RooAddPdf ch2_model("ch2_model","ch2 model",
                        RooArgList(pdf_min_qcd,pdf_min_dip,pdf_min_oth),RooArgList(yield_qcd,yield_dip,yield_oth));
    RooAddPdf ch3_model("ch3_model","ch3 model",
                        RooArgList(pdf_ht_qcd,pdf_ht_dip,pdf_ht_oth),RooArgList(yield_qcd,yield_dip,yield_oth));
    //}}}
    // import data from TTree{{{
    TFile *ftree = TFile::Open(input_tree);
    TTree *t_max = (TTree*) ftree->Get("t_maxPhotonIDMVA");
    TTree *t_min = (TTree*) ftree->Get("t_minPhotonIDMVA");
    TTree *t_ht = (TTree*) ftree->Get("t_HT"); //scaled HT

    fout->cd(); // to prevent write buffer error
    idmva.setBins(30);

    RooDataSet data_max("data_max", "data_max", t_max, idmva);
    RooDataSet data_min("data_min", "data_min", t_min, idmva);
    RooDataSet data_ht("data_ht", "data_ht", t_ht, idmva);

    RooPlot *frame_data_max = idmva.frame(Title("max Unbinned data shown in default frame binning"));
    RooPlot *frame_data_min = idmva.frame(Title("min Unbinned data shown in default frame binning"));
    RooPlot *frame_data_ht = idmva.frame(Title("HT Unbinned data shown in default frame binning"));
    
    c1->cd(1); setPad(); data_max.plotOn(frame_data_max); frame_data_max->Draw();
    c1->cd(2); setPad(); data_min.plotOn(frame_data_min); frame_data_min->Draw();
    c1->cd(3); setPad(); data_ht.plotOn(frame_data_ht); frame_data_ht->Draw();
    c1->SaveAs("eos_test/imported_tree_data.png");
    c1->SaveAs("eos_test/imported_tree_data.pdf");
    //}}}
    // now build the simultaneous model by adding two channels
    RooSimultaneous model("model","model",channel);
    model.addPdf(ch1_model,"maxIDMVA");
    model.addPdf(ch2_model,"minIDMVA");
    model.addPdf(ch3_model,"ht");
    
    // joint two data sets, fit together
    RooDataSet data("data","joint data",idmva,Index(channel),
                    Import("maxIDMVA",data_max),Import("minIDMVA",data_min),Import("ht",data_ht));

    model.fitTo(data,Minos(true));

    printf("[init] yh_data = %.2f, yh_nrb = %.2f, ", yh_data, yh_qcd + yh_dip + yh_oth);
    printf("yh_qcd = %.2f, yh_dip = %.2f, yh_oth = %.2f\n", yh_qcd, yh_dip, yh_oth);

    printf("[result] sf_qcd = %f, sf_dip = %f\n", sf_qcd.getVal(), sf_dip.getVal());

    yh_qcd *= sf_qcd.getVal(); yh_dip *= sf_dip.getVal();
    printf("[result] yh_data = %.2f, yh_nrb = %.2f, ", yh_data, yh_qcd + yh_dip + yh_oth);
    printf("yh_qcd = %.2f, yh_dip = %.2f, yh_oth = %.2f\n", yh_qcd, yh_dip, yh_oth);
    
    // check pdfs on plots {{{
    TCanvas *c2 = new TCanvas("c2","c2",2400,600);
    c2->Divide(3);

    c2->cd(1); // channel1 only
    gPad->SetGrid();
    gPad->SetTicks();
    RooPlot* frame2 = idmva.frame();
    data.plotOn(frame2,Cut("channel==1"));
    model.plotOn(frame2,Slice(channel,"maxIDMVA"),ProjWData(channel,data));
    pdf_max_qcd.plotOn(frame2, LineColor(colors[0]));
    pdf_max_dip.plotOn(frame2, LineColor(colors[1]));
    pdf_max_oth.plotOn(frame2, LineColor(colors[2]));
    frame2->Draw();

    c2->cd(2); // channel2 only
    gPad->SetGrid();
    gPad->SetTicks();
    RooPlot* frame3 = idmva.frame();
    data.plotOn(frame3,Cut("channel==2"));
    model.plotOn(frame3,Slice(channel,"minIDMVA"),ProjWData(channel,data));
    pdf_min_qcd.plotOn(frame3, LineColor(colors[0]));
    pdf_min_dip.plotOn(frame3, LineColor(colors[1]));
    pdf_min_oth.plotOn(frame3, LineColor(colors[2]));
    frame3->Draw();

    c2->cd(3); // channel3 only
    gPad->SetGrid();
    gPad->SetTicks();
    RooPlot* frame4 = idmva.frame();
    data.plotOn(frame4,Cut("channel==3"));
    model.plotOn(frame4,Slice(channel,"ht"),ProjWData(channel,data));
    pdf_ht_qcd.plotOn(frame4, LineColor(colors[0]));
    pdf_ht_dip.plotOn(frame4, LineColor(colors[1]));
    pdf_ht_oth.plotOn(frame4, LineColor(colors[2]));
    frame4->Draw();

    c2->SaveAs("eos_test/test.png");
    c2->SaveAs("eos_test/test.pdf");
    //}}}
    // check stack plots {{{
    std::vector<double> v_sfs;
    v_sfs = {sf_qcd.getVal(), sf_dip.getVal()};

    THStack *hs_max_updated = new THStack("hs_max_updated", "");
    THStack *hs_min_updated = new THStack("hs_min_updated", "");
    THStack *hs_ht_updated = new THStack("hs_ht_updated", "");
    for(int i=0; i<backgrounds.size(); ++i)
    {
        if(i+2==backgrounds.size()) {
            vH_maxPhotonIDMVA_Bkg[i]->Scale(v_sfs[1]);
            vH_minPhotonIDMVA_Bkg[i]->Scale(v_sfs[1]);
            vH_ht_Bkg[i]->Scale(v_sfs[1]);
        }
        if(i+1==backgrounds.size()) {
            vH_maxPhotonIDMVA_Bkg[i]->Scale(v_sfs[0]);
            vH_minPhotonIDMVA_Bkg[i]->Scale(v_sfs[0]);
            vH_ht_Bkg[i]->Scale(v_sfs[0]);
        }
        hs_max_updated -> Add(vH_maxPhotonIDMVA_Bkg[i]);
        hs_min_updated -> Add(vH_minPhotonIDMVA_Bkg[i]);
        hs_ht_updated -> Add(vH_ht_Bkg[i]);
    }

    c1->cd(1);
    makeHist(hs_max_updated, h_maxPhotonIDMVA_Data, h_maxPhotonIDMVA_others);
    c1->cd(2);
    makeHist(hs_min_updated, h_minPhotonIDMVA_Data, h_minPhotonIDMVA_others);
    c1->cd(3);
    makeHist(hs_ht_updated, h_ht_Data, h_ht_others);
    c1->SaveAs("eos_test/photonIDMVA_after.png");
    c1->SaveAs("eos_test/photonIDMVA_after.pdf");

    fout->Close();
    //}}}
}

void setPad() //{{{
{
    gPad->SetGrid();
    gPad->SetTicks();
} //}}}
void cosmetic_histogram(TH1D* h, TString xtitle) //{{{
{
    h -> SetStats(0);
    h -> SetMarkerStyle(20);
    h -> SetMinimum(0);
    h -> GetXaxis() -> SetTitle(xtitle.Data());
    //h -> SetMaximum(1e+5);
    //h -> SetMinimum(1e-1);
} //}}}
void makeHist(THStack *hs, TH1D* h, TH1D* other, std::vector<double> v = {}) //{{{
{
    //gPad->SetLogy(1);
    setPad();
    h->Draw("ep1");

    hs->Draw("hist, same");
    h->Draw("ep1, same");

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

    //other->SetFillColor(kBlue);
    //other->Draw("hist, same");
} //}}}
void addHistograms(TH1D* h, TH1D* other) //{{{
{
    int bins = h->GetSize();
    for(int i=0; i<bins; ++i)
    {
        double content = h->GetBinContent(i) + other->GetBinContent(i);
        h->SetBinContent(i, content);
    }
}//}}}
TH1D* convert_ht_range(TH1D* h) //{{{
{
    int nbins = h->GetSize()-2;
    TString histName = h->GetName();
    TH1D* output = new TH1D(histName, ";HT;", nbins, -1., 1.);
    for(int i=0; i<nbins; ++i)
    {
        double content = h->GetBinContent(i+1);
        output->SetBinContent(i+1, content);
    }

    return output;
} //}}}
