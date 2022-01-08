#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
using namespace RooFit;
 
void rf201_composite()
{
    RooRealVar x("x", "x", 0, 10);
    
    // Create two gaussian PDFs
    RooRealVar mean("mean", "mean of gaussians", 5);
    RooRealVar sigma1("sigma1", "width of gaussians", 0.5);
    RooRealVar sigma2("sigma2", "width of gaussians", 1);
    
    RooGaussian sig1("sig1", "Signal component 1", x, mean, sigma1);
    RooGaussian sig2("sig2", "Signal component 2", x, mean, sigma2);
    
    // Build Chebychev polynomial pdf
    RooRealVar a0("a0", "a0", 0.5, 0., 1.);
    RooRealVar a1("a1", "a1", 0.2, 0., 1.);
    RooChebychev bkg("bkg", "Background", x, RooArgSet(a0, a1));

    //--------------------------------------------------
    // Method 1
    //--------------------------------------------------
    // Add signal components
    RooRealVar sig1frac("sig1frac", "fraction of component 1 in signal", 0.8, 0., 1.);
    RooAddPdf sig("sig", "Signal", RooArgList(sig1, sig2), sig1frac);
    
    // Add signal & bkg
    RooRealVar bkgfrac("bkgfrac", "fraction of background", 0.5, 0., 1.);
    RooAddPdf model("model", "g1+g2+a", RooArgList(bkg, sig), bkgfrac);
    
    // samples, fit, and plot
    RooDataSet *data = model.generate(x, 1000);
    
    model.fitTo(*data);
    
    RooPlot *xframe = x.frame(Title("Example of composite pdf=(sig1+sig2)+bkg"));
    data->plotOn(xframe);
    model.plotOn(xframe);
    model.plotOn(xframe, Components(bkg), LineStyle(kDashed));
    model.plotOn(xframe, Components(RooArgSet(bkg, sig2)), LineStyle(kDotted));
    
    model.Print("t"); // print structure of composite pdf
    
    //--------------------------------------------------
    // Method 2
    //--------------------------------------------------
    RooAddPdf model2("model", "g1+g2+a", RooArgList(bkg, sig1, sig2), RooArgList(bkgfrac, sig1frac), kTRUE);
    
    model2.plotOn(xframe, LineColor(kRed), LineStyle(kDashed));
    model2.plotOn(xframe, Components(RooArgSet(bkg, sig2)), LineColor(kRed), LineStyle(kDashed));
    model2.Print("t");
    
    
    TCanvas *c = new TCanvas("rf201_composite", "rf201_composite", 600, 600);
    gPad->SetLeftMargin(0.15);
    xframe->GetYaxis()->SetTitleOffset(1.4);
    xframe->Draw();
    c->SaveAs("eos_test/rf201_composite.png");
}
