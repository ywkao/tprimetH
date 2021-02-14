void print_values(TString name, double mean, double error);
void estimate_mean_and_error(TH1D* h_sig, double &mean_signal, double &width_signal);

void fitdata_one_gaussian( TString object, TString year_str, TString mass_str, double init_mean, double lower_bound, double upper_bound, double init_sigma){
    TString filename = "plots/hist_TprimeBToTH_M-" + mass_str + "_Era" + year_str + "_v2p4.root";
    TString png_name = "plots/fit_mass_" + object + "_M-" + mass_str + "_Era" + year_str + "_v2p4.png";
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

    gaus.fitTo(data, Minos(true));

    // make plot
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    RooPlot *frame_mass=mass.frame();
    data.plotOn(frame_mass);
    gaus.plotOn(frame_mass, LineColor(kBlue), Name("gaus"));
    frame_mass->Draw();

    TLegend *legend = new TLegend(0.6, 0.7, 0.90, 0.90);
    legend->AddEntry("data", "Signal MC samples", "ep");
    legend->AddEntry("gaus", "Gaussian fit", "l");
    legend->Draw("same");

    // estimate values
    double std_mean = hist->GetMean();
    double std_dev = hist->GetStdDev();
    double mode, mode_sigma;
    estimate_mean_and_error(hist, mode, mode_sigma);

    TLatex latex;
    latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextAlign(11);
    latex.SetTextSize(24);
    latex.DrawLatex( 0.50, 0.50, "std hist" );
    latex.DrawLatex( 0.50, 0.40, "fit result" );
    latex.DrawLatex( 0.50, 0.30, "mode" );
    latex.DrawLatex( 0.62, 0.50, Form(": %.2f #pm %.2f", std_mean, std_dev) );
    latex.DrawLatex( 0.62, 0.40, Form(": %.2f #pm %.2f", mu.getVal(), sigma.getVal()) );
    latex.DrawLatex( 0.62, 0.30, Form(": %.2f #pm %.2f", mode, mode_sigma) );

    gPad->SetTicky();
    c1->SaveAs(png_name);
}

void print_values(TString name, double mean, double error)
{
    printf("%s: mass = %.2f \\pm %.2f \n", name.Data(), mean, error);
}

void estimate_mean_and_error(TH1D* h_sig, double &mean_signal, double &width_signal)
{
    //--- Do the mean and width calculation ---//
    int bin_max = h_sig->GetMaximumBin();
    mean_signal = h_sig->GetBinCenter(bin_max);
    width_signal = 0.;
    double binW = h_sig->GetBinWidth(1);

    double all_integral = 0.;
    for(int i=1;i<(int)h_sig->GetNbinsX();++i)
        all_integral += h_sig->GetBinContent(i)*binW;

    double acc_integral = h_sig->GetBinContent(bin_max)*binW;
    for(int i=1;i<(int)h_sig->GetNbinsX();++i)
    {
        acc_integral += h_sig->GetBinContent(bin_max+i)*binW;
        acc_integral += h_sig->GetBinContent(bin_max-i)*binW;
        if( acc_integral/all_integral >= 0.682 ) {
            width_signal = h_sig->GetBinCenter(bin_max+i) - mean_signal;
            break;
        }
    }

    printf("[self] ratio = %.2f (%.2f/%.2f)\n", acc_integral/all_integral, acc_integral, all_integral );
    printf("[self] mass = %.2f \\pm %.2f\n", mean_signal, width_signal);
}
