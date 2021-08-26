{
    TString datasetname = "dataset_Run2_TprimeVsHiggs";
    TString filepath = "TMVA_Run2_TprimeVsHiggs.root";
    TString isRegression = false; // If classification
    TMVA::correlations(datasetname, filepath, isRegression, true, true);
    TCanvas & c = *dynamic_cast<TCanvas *>(gROOT->FindObject("CorrelationMatrixS"));
    TH2F & h2 = *(TH2F *)c.GetPrimitive("CorrelationMatrixS");
    
    // TODO: Change size of labels
    //h2.SetLabelSize(0.01);
    
    c.Draw();
}
