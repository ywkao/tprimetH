#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooHistPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
using namespace RooFit;
 
void rf706_histpdf()
{
    // create pdf for sampling
    RooRealVar x("x", "x", 0, 20);
    RooRealVar par1("par1", "par1", 0.01);
    RooRealVar par2("par2", "par2", -0.01);
    RooRealVar par3("par3", "par3", 0.0004);
    RooPolynomial p("p", "p", x, RooArgList(par1, par2, par3));
    
    // create low stats histogram
    x.setBins(20);
    RooDataSet *data1 = p.generate(x, 500);
    RooDataHist *hist1 = data1->binnedClone();
    RooHistPdf histpdf1("histpdf1", "histpdf1", x, *hist1, 0);
    
    RooPlot *frame1 = x.frame(Title("Low statistics histogram pdf"), Bins(100));
    data1->plotOn(frame1); // unbinned data
    histpdf1.plotOn(frame1); // histogram pdf
    
    // create high stats histogram
    x.setBins(10);
    RooDataSet *data2 = p.generate(x, 100000);
    RooDataHist *hist2 = data2->binnedClone();
    RooHistPdf histpdf2("histpdf2", "histpdf2", x, *hist2, 0);
    
    RooPlot *frame2 = x.frame(Title("High stats histogram pdf with interpolation"), Bins(100));
    data2->plotOn(frame2); // unbinned data
    histpdf2.plotOn(frame2); // histogram pdf
    
    TCanvas *c = new TCanvas("rf706_histpdf", "rf706_histpdf", 800, 400);
    c->Divide(2);
    c->cd(1);
    gPad->SetLeftMargin(0.15);
    frame1->GetYaxis()->SetTitleOffset(1.4);
    frame1->Draw();
    c->cd(2);
    gPad->SetLeftMargin(0.15);
    frame2->GetYaxis()->SetTitleOffset(1.8);
    frame2->Draw();
    c->SaveAs("eos_test/rf706_histpdf.png");
}
