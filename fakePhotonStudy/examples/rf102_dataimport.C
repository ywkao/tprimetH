#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace RooFit;
 
TH1 *makeTH1();
TTree *makeTTree();

void rf102_dataimport()
{
    //--------------------------------------------------
    // RooDataHist
    //--------------------------------------------------
    TH1 *hh = makeTH1();
    RooRealVar x("x", "x", -10, 10);
    RooDataHist dh("dh", "dh", x, Import(*hh));

    //Make plot of binned dataset showing Poisson error bars (RooFit default)
    RooPlot *frame = x.frame(Title("Imported TH1 with Poisson error bars"));
    dh.plotOn(frame);
    // Fit a Gaussian pdf to the data
    RooRealVar mean("mean", "mean", 0, -10, 10);
    RooRealVar sigma("sigma", "sigma", 3, 0.1, 10);
    RooGaussian gauss("gauss", "gauss", x, mean, sigma);
    gauss.fitTo(dh);
    gauss.plotOn(frame);

    RooPlot *frame2 = x.frame(Title("Imported TH1 with internal errors"));
    dh.plotOn(frame2, DataError(RooAbsData::SumW2));
    gauss.plotOn(frame2);

    //--------------------------------------------------
    // RooDataSet
    //--------------------------------------------------
    TTree *tree = makeTTree();
    RooRealVar y("y", "y", -10, 10);
    RooDataSet ds("ds", "ds", RooArgSet(x, y), Import(*tree));

    TString output = "eos_test/rf102_testData.txt";
    {
        //// Write data to output stream
        //std::ofstream outstream("rf102_testData.txt");
        //// Optionally, adjust the stream here (e.g. std::setprecision)
        //ds.write(outstream);
        //outstream.close();

        ds.write(output.Data());
    }
    // Read data from input stream. The variables of the dataset need to be supplied
    // to the RooDataSet::read() function.
    std::cout << "\n-----------------------\nReading data from ASCII\n";
    RooDataSet *dataReadBack = RooDataSet::read(output.Data(), RooArgList(x, y), "D");
    dataReadBack->Print("V");
    std::cout << "\nOriginal data, line 20:\n";
    ds.get(20)->Print("V");

    std::cout << "\nRead-back data, line 20:\n";
    dataReadBack->get(20)->Print("V");

    // Print number of events in dataset
    ds.Print();
    // Print unbinned dataset with default frame binning (100 bins)
    RooPlot *frame3 = y.frame(Title("Unbinned data shown in default frame binning"));
    ds.plotOn(frame3);
    // Print unbinned dataset with custom binning choice (20 bins)
    RooPlot *frame4 = y.frame(Title("Unbinned data shown with custom binning"));
    ds.plotOn(frame4, Binning(20));
    RooPlot *frame5 = y.frame(Title("Unbinned data read back from ASCII file"));
    ds.plotOn(frame5, Binning(20));
    dataReadBack->plotOn(frame5, Binning(20), MarkerColor(kRed), MarkerStyle(5));
    // Draw all frames on a canvas
    TCanvas *c = new TCanvas("rf102_dataimport", "rf102_dataimport", 1000, 800);
    c->Divide(3, 2);
    c->cd(1);
    gPad->SetLeftMargin(0.15);
    frame->GetYaxis()->SetTitleOffset(1.4);
    frame->Draw();
    c->cd(2);
    gPad->SetLeftMargin(0.15);
    frame2->GetYaxis()->SetTitleOffset(1.4);
    frame2->Draw();
    c->cd(4);
    gPad->SetLeftMargin(0.15);
    frame3->GetYaxis()->SetTitleOffset(1.4);
    frame3->Draw();
    c->cd(5);
    gPad->SetLeftMargin(0.15);
    frame4->GetYaxis()->SetTitleOffset(1.4);
    frame4->Draw();
    c->cd(6);
    gPad->SetLeftMargin(0.15);
    frame4->GetYaxis()->SetTitleOffset(1.4);
    frame5->Draw();

    c->SaveAs("eos_test/rf102_dataimport.png");
}

// Create ROOT TH1 filled with a Gaussian distribution
TH1 *makeTH1()
{
    TH1D *hh = new TH1D("hh", "hh", 25, -10, 10);
    for (int i = 0; i < 100; i++) {
        hh->Fill(gRandom->Gaus(0, 3));
    }
    return hh;
}

// Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
TTree *makeTTree()
{
    TTree *tree = new TTree("tree", "tree");
    Double_t *px = new Double_t;
    Double_t *py = new Double_t;
    tree->Branch("x", px, "x/D");
    tree->Branch("y", py, "y/D");
    for (int i = 0; i < 100; i++) {
        *px = gRandom->Gaus(0, 3);
        *py = gRandom->Uniform() * 30 - 15;
        tree->Fill();
    }
    return tree;
}
