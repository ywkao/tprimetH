#include "toolbox.C"

void fit_chi2_value( TString title, TString object, TString year_str, TString mass_str, double init_rate, double lower_bound, double fit_bound, double upper_bound){
    TString filename = "plots/hist_TprimeBToTH_M-" + mass_str + "_Era" + year_str + "_v2p4.root";
    TString png_name = "plots/fit_" + object + "_M-" + mass_str + "_Era" + year_str + "_v2p4.png";
    TFile *fin = TFile::Open(filename);

    TNtupleD *nt = (TNtupleD*) fin->Get(object);

    int nbins_hist = (int) (upper_bound - lower_bound);
    TH1D *hist = new TH1D("hist", "", nbins_hist, lower_bound, upper_bound);
    nt->Project("hist", "chi2_value");
    double y_scope_max = get_y_scope_max(hist, true);
    double entries_in_the_first_bin = hist->GetBinContent(1);

    using namespace RooFit;
    RooRealVar  chi2_value("chi2_value", "chi2_value", lower_bound, upper_bound);
    RooDataSet  data("data", "data", nt, RooArgSet(chi2_value));

    chi2_value.setRange("fit_region", lower_bound, fit_bound );
    chi2_value.setRange("dual_region", fit_bound, upper_bound );

    //==============================//
    //==========   Model  ==========//
    //==============================//
    RooRealVar  rate("rate", "rate", init_rate, -50, 0.);
    RooExponential model("exp", "exp", chi2_value, rate);
    RooFitResult *result = model.fitTo(data, Minos(true), Range("fit_region"), Save(kTRUE));
    printf("rooFit result:\n");
    result->Print();

    double intersection_chi2_value = log(entries_in_the_first_bin) / (-1. * rate.getVal());

    // make plot
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    RooPlot *frame = chi2_value.frame(Title(title));
    data.plotOn(frame);
    model.plotOn(frame, Range("dual_region"), LineStyle(kDashed), LineColor(kGreen+3), Name("extrapolation"));
    model.plotOn(frame, LineColor(kBlue), Name("exp"));
    frame->SetAxisRange(1.e-1, y_scope_max, "Y");
    frame->Draw();

    c1->Update();
    TLine *line = new TLine(c1->GetUxmin(), 1., c1->GetUxmax(), 1.);
    line->SetLineWidth(2);
    line->SetLineStyle(2);
    line->SetLineColor(kBlack);
    line->Draw("same");

    TLegend *legend = new TLegend(0.6, 0.7, 0.90, 0.90);
    legend->AddEntry("data", "Signal MC samples", "ep");
    legend->AddEntry("exp", "Exponential", "l");
    legend->AddEntry("extrapolation", "Extrapolation", "l");
    legend->Draw("same");

    TLatex latex;
    //latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextAlign(11);
    latex.SetTextSize(24);
    latex.SetTextColor(kRed);
    latex.DrawLatex( intersection_chi2_value + 3., 3., Form("#chi^{2} value @ intersection: %.2f", intersection_chi2_value) );

    auto gr = new TGraph();
    gr->SetPoint(0, intersection_chi2_value, 1.);
    gr->SetMarkerColor(kRed);
    gr->SetMarkerStyle(kFullCircle);
    gr->Draw("p;same");

//    fstream fout;
//    fout.open("json/fit_result.txt", "ios::app");
//    fout << filename.Data() << "\n";
//    fout << "std hist: " << std_mean << "+/-" << std_dev << "\n";
//    fout << "fit mode: " << mode << "+/-" << mode_sigma << "\n";
//    fout.close();

    gPad->SetLogy();
    gPad->SetTicks();

    c1->SaveAs(png_name);
}
