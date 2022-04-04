#define t_cxx
#include "t.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void t::Loop()
{
    if (fChain == 0) return;
    TFile *fout = new TFile("eos/output_" + tag + ".root", "RECREATE");

    My_Cut_Values cut_SR1 = set_threshold( {0.943, 1.000}, {0.800, 1.000}, {480., 800.}  );
    My_Cut_Values cut_SR2 = set_threshold( {0.960, 1.000}, {0.800, 1.000}, {550., 1150.} );
    My_Cut_Values cut_SR3 = set_threshold( {0.950, 1.000}, {0.800, 1.000}, {650., 1600.} );
    //My_Cut_Values cut_VR1 = set_threshold( {0.780, 0.800}, {0.000, 0.800}, {0.00, 480.}  );
    My_Cut_Values cut_VR_smh = set_threshold( {0.000, 0.800}, {0.800, 1.000}, {0.00, 480.}  );
    My_Cut_Values cut_VR_sig = set_threshold( {0.800, 1.000}, {0.800, 1.000}, {0.00, 480.}  );
    My_Cut_Values cut_VR_inv = set_threshold( {0.800, 1.000}, {0.600, 0.800}, {0.00, 480.}  );
    My_Cut_Values cut_VR_inv2 = set_threshold( {0.800, 1.000}, {0.000, 0.600}, {0.00, 480.}  );

    My_Cut_Values cut_VR_val = set_threshold( {0.580, 0.780}, {0.000, 0.800}, {0.00, 480.}  );
    My_Cut_Values cut_VR_val2 = set_threshold( {0.460, 0.780}, {0.000, 0.800}, {0.00, 480.}  );

    vector<My_Cut_Values> cut_VRs;
    for(int i=0; i<40; ++i) {
        double lower = 0.780 - (double)i * 0.02;
        double upper = 0.800 - (double)i * 0.02;
        My_Cut_Values cut = set_threshold( {lower, upper}, {0.000, 0.800}, {0.00, 480.}  );
        cut_VRs.push_back(cut);
    }

    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        // mass criteria (Mgg, MT')
        if (Cut(ientry) < 0) continue;

        bool pass_low_Tprime_mass = Tprime_mass > 0. && Tprime_mass < 480.;
        if(pass_low_Tprime_mass) {
            h_map->Fill(BDTG_TprimeVsNonHiggs_M600_M700, BDTG_TprimeVsHiggs_M600_M700, weight);
        }

        // validation regions
        for(int i=0; i<40; ++i) {
            double value = 0.5 + (double)i;
            if (Cut(ientry, cut_VRs[i], BDTG_TprimeVsNonHiggs_M600_M700, BDTG_TprimeVsHiggs_M600_M700) > 0){ h_counter_validation_region->Fill(value, weight); }
        }
        if (Cut(ientry, cut_VR_smh, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ h_counter_validation_region->Fill(40.5, weight); }
        if (Cut(ientry, cut_VR_sig, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ h_counter_validation_region->Fill(41.5, weight); }
        if (Cut(ientry, cut_VR_inv, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ h_counter_validation_region->Fill(42.5, weight); }
        if (Cut(ientry, cut_VR_inv2, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)  > 0){ h_counter_validation_region->Fill(43.5, weight); }
        if (Cut(ientry, cut_VR_val, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ h_counter_validation_region->Fill(44.5, weight); }
        if (Cut(ientry, cut_VR_val2, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)  > 0){ h_counter_validation_region->Fill(45.5, weight); }

        // reference points
        if (Cut(ientry, cut_SR1, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ h_counter_signal_region->Fill(0.5, weight); }
        if (Cut(ientry, cut_SR2, BDTG_TprimeVsNonHiggs_M800_M1000 , BDTG_TprimeVsHiggs_M800_M1000)  > 0){ h_counter_signal_region->Fill(1.5, weight); }
        if (Cut(ientry, cut_SR3, BDTG_TprimeVsNonHiggs_M1100_M1200, BDTG_TprimeVsHiggs_M1100_M1200) > 0){ h_counter_signal_region->Fill(2.5, weight); }
        if (Cut(ientry, cut_SR1, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ counter_SR1 += 1; yields_SR1 += weight; }
        if (Cut(ientry, cut_SR2, BDTG_TprimeVsNonHiggs_M800_M1000 , BDTG_TprimeVsHiggs_M800_M1000)  > 0){ counter_SR2 += 1; yields_SR2 += weight; }
        if (Cut(ientry, cut_SR3, BDTG_TprimeVsNonHiggs_M1100_M1200, BDTG_TprimeVsHiggs_M1100_M1200) > 0){ counter_SR3 += 1; yields_SR3 += weight; }
    }

    Report();
    Make_plots();

    fout->cd();
    h_counter_signal_region->Write();
    h_counter_validation_region->Write();
    fout->Write();
    fout->Close();
}
