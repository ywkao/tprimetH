void finetuning(TH2F* h);
void print_values(TH2F *h);

void get_correlation_matrix(TString filename, TString dataset, TString output)
{
    TFile *fin = TFile::Open(filename);

    TCanvas *c1 = new TCanvas("c1", "", 800, 600);
    gStyle->SetPalette(1);
    gPad->SetBottomMargin(0.20);
    gPad->SetLeftMargin(0.16);
    gPad->SetRightMargin(0.12);

    TH2F *hs = (TH2F*) fin->Get( dataset + "/CorrelationMatrixS" );
    TH2F *hb = (TH2F*) fin->Get( dataset + "/CorrelationMatrixB" );

    finetuning(hs);
    finetuning(hb);

    hs->Draw("colz");
    c1->SaveAs(output.ReplaceAll(".pdf", "signal.pdf"));

    hb->Draw("colz");
    c1->SaveAs(output.ReplaceAll(".pdf", "bkg.pdf"));
}

void finetuning(TH2F* h)
{
    h->GetXaxis()->SetLabelSize(0.022);
    h->GetYaxis()->SetLabelSize(0.022);
    h->LabelsOption("v");

    print_values(h);
}

void print_values(TH2F *h)
{
    int nbins = h->GetNbinsX();

    for(int i=0; i<nbins; ++i)
        printf("%s, %f\n", h->GetXaxis()->GetBinLabel(i+1), h->GetBinContent(i+1, 1));

    for(int i=0; i<nbins; ++i)
        printf("%s, %f\n", h->GetXaxis()->GetBinLabel(i+1), h->GetBinContent(i+1, 2));
}
