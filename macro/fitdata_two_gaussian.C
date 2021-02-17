#include "toolbox.C"

void fitdata_two_gaussian( TString object, TString year_str, TString mass_str, double init_mean, double lower_bound, double upper_bound, double init_sigma, double init_mean_2nd, double lower_bound_2nd, double upper_bound_2nd, double init_sigma_2nd){
    TString filename = "plots/hist_TprimeBToTH_M-" + mass_str + "_Era" + year_str + "_v2p4.root";
    TString png_name = "plots/fit_two_gaussian_mass_" + object + "_M-" + mass_str + "_Era" + year_str + "_v2p4.png";
    TFile *fin = TFile::Open(filename);

    TString nt_name = "nt_mass_" + object;
    TNtupleD *nt = (TNtupleD*) fin->Get(nt_name);

    int nbins_hist = (int) ((upper_bound - lower_bound) * 100);
    TH1D *hist = new TH1D("hist", "", nbins_hist, lower_bound, upper_bound);
    nt->Project("hist", "mass");

    using namespace RooFit;
    RooRealVar  mass("mass", "mass", lower_bound, upper_bound); //mass.setBins(160);
    RooDataSet  data("data", "data", nt, RooArgSet(mass));

    //==============================//
    //==========   Model  ==========//
    //==============================//
    RooRealVar  mu("mu", "mu", init_mean, lower_bound, upper_bound);
    RooRealVar  sigma("sigma", "sigma", init_sigma, 0.1, 50.);
    RooGaussian gaus("gaus", "gaus", mass, mu, sigma);

    RooRealVar  mu_2nd("mu_2nd", "mu_2nd", init_mean_2nd, lower_bound_2nd, upper_bound_2nd);
    RooRealVar  sigma_2nd("sigma_2nd", "sigma_2nd", init_sigma_2nd, 0.1, 50.0);
    RooGaussian gaus_2nd("gaus_2nd", "gaus_2nd", mass, mu_2nd, sigma_2nd);

    RooRealVar  frac("frac", "frac", 0.2, 0.0, 1.0);
    RooAddPdf   model("model", "model", RooArgList(gaus, gaus_2nd), RooArgList(frac));
    
    model.fitTo(data, Minos(true));

    // result
    print_values("1st", mu.getVal(), sigma.getVal());
    print_values("2nd", mu_2nd.getVal(), sigma_2nd.getVal());

    // make plot
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    RooPlot *frame_mass=mass.frame();
    data.plotOn(frame_mass);
    model.plotOn(frame_mass);
    model.plotOn(frame_mass , Components(gaus)     , LineStyle(1) , LineColor(kRed)     , FillStyle(3144) , FillColor(kRed-9)   , DrawOption("F") , Name("1st_gaussian"));
    model.plotOn(frame_mass , Components(gaus_2nd) , LineStyle(1) , LineColor(kGreen+2) , FillStyle(3144) , FillColor(kGreen-9) , DrawOption("F") , Name("2nd_gaussian"));
    frame_mass->Draw();

    TLegend *legend = new TLegend(0.1, 0.6, 0.40, 0.90);
    legend->AddEntry("data", "Signal MC samples", "ep");
    legend->AddEntry("1st_gaussian", "1st gaussian", "f");
    legend->AddEntry("2nd_gaussian", "2nd gaussian", "f");
    legend->Draw("same");


    RooDataSet *pseudo_data = model.generate(mass, nbins_hist * 100);
    TH1 *model_hist = pseudo_data->createHistogram("mass", nbins_hist * 10);
    double std_mean = hist->GetMean();
    double std_dev = hist->GetStdDev();
    double mode, mode_sigma; estimate_mean_and_error(model_hist, mode, mode_sigma);

    TLatex latex;
    latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextAlign(11);
    latex.SetTextSize(20);
    latex.DrawLatex( 0.65, 0.80, "std hist" );
    latex.DrawLatex( 0.65, 0.70, "fit mode" );
    latex.DrawLatex( 0.73, 0.80, Form(": %.2f #pm %.2f", std_mean, std_dev) );
    latex.DrawLatex( 0.73, 0.70, Form(": %.2f #pm %.2f", mode, mode_sigma) );

    //model_hist->Draw("same");

//    fstream fout;
//    fout.open("json/fit_result.txt", "ios::app");
//    fout << filename.Data() << "\n";
//    fout << "std hist: " << std_mean << "+/-" << std_dev << "\n";
//    fout << "fit mode: " << mode << "+/-" << mode_sigma << "\n";
//    fout.close();

    gPad->SetTicky();
    c1->SaveAs(png_name);
}
