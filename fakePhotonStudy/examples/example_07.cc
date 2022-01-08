{
    using namespace RooFit;
    
    // observables
    RooRealVar mass("mass","mass",0.,2.);
    RooCategory channel("channel","channel");
    channel.defineType("decay1",1);
    channel.defineType("decay2",2);
    
    // models for decay #1
    RooRealVar ch1_mu("ch1_mu","mu",1.0,0.5,1.5);
    RooRealVar ch1_sigma("ch1_sigma","sigma",0.05,0.001,0.15);
    RooGaussian ch1_gaus("ch1_gaus","gaus",mass,ch1_mu,ch1_sigma);
    RooRealVar ch1_slope("ch1_slope","slope",-0.4,-10.,10.);
    RooPolynomial ch1_linear("ch1_linear","linear",mass,RooArgSet(ch1_slope));

    // models for decay #2
    RooRealVar ch2_mu("ch2_mu","mu",1.0,0.5,1.5);
    RooRealVar ch2_sigma("ch2_sigma","sigma",0.10,0.001,0.15);
    RooGaussian ch2_gaus("ch2_gaus","gaus",mass,ch2_mu,ch2_sigma);
    RooRealVar ch2_slope("ch2_slope","slope",-0.2,-10.,10.);
    RooPolynomial ch2_linear("ch2_linear","linear",mass,RooArgSet(ch2_slope));
    
    // key parameter to be extract from the fit
    RooRealVar XS("XS","cross section",0.2,0.0,0.5);
    
    // norm = luminosity * acceptance * efficiency
    RooRealVar ch1_norm("ch1_norm","decay1 norm",4000.);
    RooRealVar ch2_norm("ch2_norm","decay2 norm",6000.);
    
    RooProduct ch1_ns("ch1_ns","decay1 ns", RooArgList(XS,ch1_norm));
    RooProduct ch2_ns("ch2_ns","decay2 ns", RooArgList(XS,ch2_norm));
    RooRealVar ch1_nb("ch1_nb","decay1 nb",4000,0.,20000.);
    RooRealVar ch2_nb("ch2_nb","decay2 nb",7000,0.,20000.);

    RooAddPdf ch1_model("ch1_model","decay1 model",
                        RooArgList(ch1_gaus,ch1_linear),RooArgList(ch1_ns,ch1_nb));
    RooAddPdf ch2_model("ch2_model","decay2 model",
                        RooArgList(ch2_gaus,ch2_linear),RooArgList(ch2_ns,ch2_nb));
    
    // now build the simultaneous model by adding two channels
    RooSimultaneous model("model","model",channel);
    model.addPdf(ch1_model,"decay1");
    model.addPdf(ch2_model,"decay2");
    
    // generate toy data
    RooDataSet* ch1_data = ch1_model.generate(mass);
    RooDataSet* ch2_data = ch2_model.generate(mass);
    
    // joint two data sets, fit together
    RooDataSet data("data","joint data",mass,Index(channel),
                    Import("decay1",*ch1_data),Import("decay2",*ch2_data));
    model.fitTo(data,Minos(true));
    
    TCanvas *c1 = new TCanvas("c1","c1",1200,400);
    c1->Divide(3);

    c1->cd(1); // sum of the two channels
    RooPlot* frame1 = mass.frame();
    data.plotOn(frame1);
    model.plotOn(frame1,ProjWData(channel,data));
    frame1->Draw();
    
    c1->cd(2); // decay1 only
    RooPlot* frame2 = mass.frame();
    data.plotOn(frame2,Cut("channel==1"));
    model.plotOn(frame2,Slice(channel,"decay1"),ProjWData(channel,data));
    frame2->Draw();

    c1->cd(3); // decay2 only
    RooPlot* frame3 = mass.frame();
    data.plotOn(frame3,Cut("channel==2"));
    model.plotOn(frame3,Slice(channel,"decay2"),ProjWData(channel,data));
    frame3->Draw();

    c1->SaveAs("eos_test/example_07.png");
}
