#define p_cxx
#include "p.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void p::Loop()
{
    if (fChain == 0) return;
    TFile *fout = new TFile("eos/output_" + tag + ".root", "RECREATE");

    My_Cut_Values cut_SR1 = set_threshold( {0.000,1.000}, {0.600,1.000}, {480.,800.}  );
    My_Cut_Values cut_SR2 = set_threshold( {0.000,1.000}, {0.400,1.000}, {550.,1150.} );
    My_Cut_Values cut_SR3 = set_threshold( {0.000,1.000}, {0.400,1.000}, {650.,1600.} );

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        if (is_SR1 && Cut(ientry,cut_SR1,MVAscore_TprimeVsNonHiggs,MVAscore_TprimeVsHiggs) > 0){ h_mass_map_SR1->Fill(dipho_mass,Tprime_mass,weight); h_mass_diphoton_SR1->Fill(dipho_mass,weight);}
        if (is_SR2 && Cut(ientry,cut_SR2,MVAscore_TprimeVsNonHiggs,MVAscore_TprimeVsHiggs) > 0){ h_mass_map_SR2->Fill(dipho_mass,Tprime_mass,weight); h_mass_diphoton_SR2->Fill(dipho_mass,weight);}
        if (is_SR3 && Cut(ientry,cut_SR3,MVAscore_TprimeVsNonHiggs,MVAscore_TprimeVsHiggs) > 0){ h_mass_map_SR3->Fill(dipho_mass,Tprime_mass,weight); h_mass_diphoton_SR3->Fill(dipho_mass,weight);}
    }

    Report();
    Make_plots();

    fout->cd();
    fout->Write();
    fout->Close();
}
