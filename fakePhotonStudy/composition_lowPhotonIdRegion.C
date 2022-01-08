#include "composition.h"

void composition_lowPhotonIdRegion()
{
    TString input_file = "./rootfiles/myhist_low_photon_sideband.root";
    TString input_tree = "./rootfiles/MVABaby_low_photon_sideband_Data.root";
    // make stack plots {{{
    TString tag = "compositionStudy";
    TFile *fout = TFile::Open("output.root", "recreate");

    TFile *fin = TFile::Open(input_file);
    //std::vector<TString> backgrounds = {"QCD", "GammaJets", "DiPhoton"};
    std::vector<TString> backgrounds = {"QCD", "GammaJets", "DiPhoton", "TTGG", "TTGJets", "TTJets", "VG"};
    std::vector<Int_t> colors = {kOrange+6, kRed+3, kRed+1, kGreen-2, kGreen-7, kSpring+10, kViolet-9};
    std::vector<TH1D*> vH_maxPhotonIDMVA_Bkg;
    std::vector<TH1D*> vH_minPhotonIDMVA_Bkg;

    TH1D *h_maxPhotonIDMVA_Data = (TH1D*) fin->Get("hPhotonMaxIDMVA_fine_Data");
    TH1D *h_minPhotonIDMVA_Data = (TH1D*) fin->Get("hPhotonMinIDMVA_fine_Data");
    cosmetic_histogram(h_maxPhotonIDMVA_Data, "Max Photon ID MVA");
    cosmetic_histogram(h_minPhotonIDMVA_Data, "Min Photon ID MVA");

    double yh_data = 1000;
    double yh_qcd  = 1000;
    double yh_gjet = 1000;
    double yh_dip  = 1000;
    double yh_oth  = 1000;

    // fill vector {{{
    for(int i=0; i<backgrounds.size(); ++i)
    {
        TH1D *h_max = (TH1D*) fin->Get("hPhotonMaxIDMVA_fine_" + backgrounds[i]);
        TH1D *h_min = (TH1D*) fin->Get("hPhotonMinIDMVA_fine_" + backgrounds[i]);
        h_max -> SetFillColor(colors[i]);
        h_min -> SetFillColor(colors[i]);
        vH_maxPhotonIDMVA_Bkg.push_back(h_max);
        vH_minPhotonIDMVA_Bkg.push_back(h_min);

        if(i==0) {
            printf("Data      : ");
            printf("%f, ", h_maxPhotonIDMVA_Data->Integral(0, h_maxPhotonIDMVA_Data->GetSize()-1));
            printf("%f\n", h_minPhotonIDMVA_Data->Integral(0, h_minPhotonIDMVA_Data->GetSize()-1));
            yh_data = h_maxPhotonIDMVA_Data->Integral(0, h_maxPhotonIDMVA_Data->GetSize()-1);
            yh_qcd = h_max->Integral(0, h_max->GetSize()-1);
        } else if(i==1) {
            yh_gjet = h_max->Integral(0, h_max->GetSize()-1);
        } else if(i==2) {
            yh_dip = h_max->Integral(0, h_max->GetSize()-1);
        } else {
            yh_oth += h_max->Integral(0, h_max->GetSize()-1);
        }

        printf("%-10s: ", backgrounds[i].Data());
        printf("%f, ", h_max->Integral(0, h_maxPhotonIDMVA_Data->GetSize()-1));
        printf("%f\n", h_min->Integral(0, h_minPhotonIDMVA_Data->GetSize()-1));
    } //}}}

    // stack hist
    THStack *hs_max = new THStack("hs_max", "");
    THStack *hs_min = new THStack("hs_min", "");
    TH1D *h_maxPhotonIDMVA_others;
    TH1D *h_minPhotonIDMVA_others;
    make_stacks(hs_max, vH_maxPhotonIDMVA_Bkg, h_maxPhotonIDMVA_others);
    make_stacks(hs_min, vH_minPhotonIDMVA_Bkg, h_minPhotonIDMVA_others);

    TCanvas *c1 = new TCanvas("c1", "", 1600, 600);
    c1->SetLogy();

    c1->Divide(2);
    c1->cd(1);
    makeHist(hs_max, h_maxPhotonIDMVA_Data);

    c1->cd(2);
    makeHist(hs_min, h_minPhotonIDMVA_Data);
    c1->SaveAs( Form("eos_test/%s_photonIDMVA_before.png", tag.Data()) );
    //}}}
    // observables, create hist templates{{{
    RooRealVar idmva("idmva","Photon ID MVA",-1.,1.);
    RooCategory channel("channel","channel");
    channel.defineType("maxIDMVA",1);
    channel.defineType("minIDMVA",2);
    
    RooDataHist dh_max_data("dh_max_data", "dh_max_data", idmva, Import(*h_maxPhotonIDMVA_Data));
    RooDataHist dh_min_data("dh_min_data", "dh_min_data", idmva, Import(*h_minPhotonIDMVA_Data));
    RooPlot *frame_max = idmva.frame(Title("Imported data of max photon ID MVA"));
    RooPlot *frame_min = idmva.frame(Title("Imported data of min photon ID MVA"));
    
    c1->cd(1);
	setPad();
	dh_max_data.plotOn(frame_max);
	frame_max->Draw();
    c1->cd(2);
	setPad();
	dh_min_data.plotOn(frame_min);
	frame_min->Draw();
    c1->SaveAs( Form("eos_test/%s_imported_hist_data.png", tag.Data()) );
    //}}}
    // build models{{{
    // models for channel #1
    RooDataHist dh_max_qcd  ("dh_max_qcd"   , "dh_max_qcd"   , idmva , Import(*vH_maxPhotonIDMVA_Bkg[0]));
    RooDataHist dh_max_gjet ("dh_max_gjet"  , "dh_max_gjet"  , idmva , Import(*vH_maxPhotonIDMVA_Bkg[1]));
    RooDataHist dh_max_dip  ("dh_max_dip"   , "dh_max_dip"   , idmva , Import(*vH_maxPhotonIDMVA_Bkg[2]));
    RooDataHist dh_max_oth  ("dh_max_oth"   , "dh_max_oth"   , idmva , Import(*h_maxPhotonIDMVA_others));
    RooHistPdf pdf_max_qcd  ("pdf_max_qcd"  , "pdf_max_qcd"  , idmva , dh_max_qcd  , 0);
    RooHistPdf pdf_max_gjet ("pdf_max_gjet" , "pdf_max_gjet" , idmva , dh_max_gjet , 0);
    RooHistPdf pdf_max_dip  ("pdf_max_dip"  , "pdf_max_dip"  , idmva , dh_max_dip  , 0);
    RooHistPdf pdf_max_oth  ("pdf_max_oth"  , "pdf_max_oth"  , idmva , dh_max_oth  , 0);

    // models for channel #2
    RooDataHist dh_min_qcd  ("dh_min_qcd"   , "dh_min_qcd"   , idmva , Import(*vH_minPhotonIDMVA_Bkg[0]));
    RooDataHist dh_min_gjet ("dh_min_gjet"  , "dh_min_gjet"  , idmva , Import(*vH_minPhotonIDMVA_Bkg[1]));
    RooDataHist dh_min_dip  ("dh_min_dip"   , "dh_min_dip"   , idmva , Import(*vH_minPhotonIDMVA_Bkg[2]));
    RooDataHist dh_min_oth  ("dh_min_oth"   , "dh_min_oth"   , idmva , Import(*h_minPhotonIDMVA_others));
    RooHistPdf pdf_min_qcd  ("pdf_min_qcd"  , "pdf_min_qcd"  , idmva , dh_min_qcd  , 0);
    RooHistPdf pdf_min_gjet ("pdf_min_gjet" , "pdf_min_gjet" , idmva , dh_min_gjet , 0);
    RooHistPdf pdf_min_dip  ("pdf_min_dip"  , "pdf_min_dip"  , idmva , dh_min_dip  , 0);
    RooHistPdf pdf_min_oth  ("pdf_min_oth"  , "pdf_min_oth"  , idmva , dh_min_oth  , 0);

    // key factors to extract
    RooRealVar sf_qcd  ( "sf_qcd"  , "sf_qcd"  , 1.06787 , 0.0 , 100.);
    RooRealVar sf_dip  ( "sf_dip"  , "sf_dip"  , 1.38999 , 0.0 , 100.);
    RooRealVar sf_gjet ( "sf_gjet" , "sf_gjet" , 1.0     , 0.0 , 100.);
    RooRealVar sf_oth  ( "sf_oth"  , "sf_oth"  , 1.0     , 0.0 , 100.);
    sf_oth.setConstant(true);

    // norm = luminosity * acceptance * efficiency
    RooRealVar data_norm  ("data_norm" , "data norm"   , yh_data );
    RooRealVar qcd_norm   ("qcd_norm"  , "qcd norm"    , yh_qcd  );
    RooRealVar dip_norm   ("dip_norm"  , "dip norm"    , yh_dip  );
    RooRealVar gjet_norm  ("gjet_norm" , "gjet norm"   , yh_gjet );
    RooRealVar oth_norm   ("oth_norm"  , "oth norm"    , yh_oth  );

    RooProduct yield_qcd  ("nqcd"      , "qcd yields"  , RooArgList(sf_qcd  , qcd_norm)  );
    RooProduct yield_gjet ("ngjet"     , "gjet yields" , RooArgList(sf_gjet , gjet_norm) );
    RooProduct yield_dip  ("ndip"      , "dip yields"  , RooArgList(sf_dip  , dip_norm)  );
    RooProduct yield_oth  ("noth"      , "oth yields"  , RooArgList(sf_oth  , oth_norm)  );

    RooAddPdf ch1_model("ch1_model","ch1 model",
                        RooArgList(pdf_max_qcd,pdf_max_dip,pdf_max_gjet,pdf_max_oth),RooArgList(yield_qcd,yield_dip,yield_gjet,yield_oth));
    RooAddPdf ch2_model("ch2_model","ch2 model",
                        RooArgList(pdf_min_qcd,pdf_min_dip,pdf_min_gjet,pdf_min_oth),RooArgList(yield_qcd,yield_dip,yield_gjet,yield_oth));
    //}}}
    // import data from TTree{{{
    TFile *ftree = TFile::Open(input_tree);
    TTree *t_max = (TTree*) ftree->Get("t_maxPhotonIDMVA");
    TTree *t_min = (TTree*) ftree->Get("t_minPhotonIDMVA");

    fout->cd(); // to prevent write buffer error
    idmva.setBins(30);

    RooDataSet data_max("data_max", "data_max", t_max, idmva);
    RooDataSet data_min("data_min", "data_min", t_min, idmva);

    RooPlot *frame_data_max = idmva.frame(Title("max Unbinned data shown in default frame binning"));
    RooPlot *frame_data_min = idmva.frame(Title("min Unbinned data shown in default frame binning"));
    
    c1->cd(1); setPad(); data_max.plotOn(frame_data_max); frame_data_max->Draw();
    c1->cd(2); setPad(); data_min.plotOn(frame_data_min); frame_data_min->Draw();
    c1->SaveAs( Form("eos_test/%s_imported_tree_data.png", tag.Data()) );
    //}}}
    
    // now build the simultaneous model by adding two channels
    RooSimultaneous model("model","model",channel);
    model.addPdf(ch1_model,"maxIDMVA");
    model.addPdf(ch2_model,"minIDMVA");
    
    // joint two data sets, fit together
    RooDataSet data("data","joint data",idmva,Index(channel),
                    Import("maxIDMVA",data_max),Import("minIDMVA",data_min));

    model.fitTo(data,Minos(true));

    // print result {{{
    printf("[init] yh_data = %.2f, yh_nrb = %.2f, ", yh_data, yh_qcd + yh_dip + yh_gjet + yh_oth);
    printf("yh_qcd = %.2f, yh_dip = %.2f, yh_gjet = %.2f, yh_oth = %.2f\n", yh_qcd, yh_dip, yh_gjet, yh_oth);

    printf("[result] sf_qcd = %f, sf_gjet = %f, sf_dip = %f\n", sf_qcd.getVal(), sf_gjet.getVal(), sf_dip.getVal());

    yh_qcd *= sf_qcd.getVal(); yh_gjet *= sf_gjet.getVal(); yh_dip *= sf_dip.getVal();
    printf("[result] yh_data = %.2f, yh_nrb = %.2f, ", yh_data, yh_qcd + yh_dip + yh_gjet + yh_oth);
    printf("yh_qcd = %.2f, yh_dip = %.2f, yh_gjet = %.2f, yh_oth = %.2f\n", yh_qcd, yh_dip, yh_gjet, yh_oth);
    //}}}
    // check pdfs on plots {{{
    TCanvas *c2 = new TCanvas("c2","c2",1600,600);
    c2->Divide(2);

    c2->cd(1); // channel1 only
    gPad->SetGrid();
    gPad->SetTicks();
    RooPlot* frame2 = idmva.frame();
    data.plotOn(frame2,Cut("channel==1"));
    model.plotOn(frame2,Slice(channel,"maxIDMVA"),ProjWData(channel,data));
    pdf_max_qcd.plotOn(frame2, LineColor(colors[0]));
    pdf_max_gjet.plotOn(frame2, LineColor(colors[1]));
    pdf_max_dip.plotOn(frame2, LineColor(colors[2]));
    frame2->Draw();

    c2->cd(2); // chaneel2 only
    gPad->SetGrid();
    gPad->SetTicks();
    RooPlot* frame3 = idmva.frame();
    data.plotOn(frame3,Cut("channel==2"));
    model.plotOn(frame3,Slice(channel,"minIDMVA"),ProjWData(channel,data));
    pdf_min_qcd.plotOn(frame3, LineColor(colors[0]));
    pdf_min_gjet.plotOn(frame3, LineColor(colors[1]));
    pdf_min_dip.plotOn(frame3, LineColor(colors[2]));
    frame3->Draw();

    c2->SaveAs("eos_test/test.png");
    //}}}
    // check stack plots {{{
    std::vector<double> v_sfs;
    v_sfs = {sf_qcd.getVal(), sf_gjet.getVal(), sf_dip.getVal()};
    for(int i=0; i<v_sfs.size(); ++i) {
        vH_maxPhotonIDMVA_Bkg[i]->Scale(v_sfs[i]);
        vH_minPhotonIDMVA_Bkg[i]->Scale(v_sfs[i]);
    }

    // after scaling
    THStack *hs_max_updated = new THStack("hs_max_updated", "");
    THStack *hs_min_updated = new THStack("hs_min_updated", "");
    make_stacks(hs_max_updated, vH_maxPhotonIDMVA_Bkg);
    make_stacks(hs_min_updated, vH_minPhotonIDMVA_Bkg);

    c1->cd(1);
    makeHist(hs_max_updated, h_maxPhotonIDMVA_Data);
    c1->cd(2);
    makeHist(hs_min_updated, h_minPhotonIDMVA_Data);
    c1->SaveAs( Form("eos_test/%s_photonIDMVA_after.png", tag.Data()) );

    fout->Close();
   //}}} 
}
