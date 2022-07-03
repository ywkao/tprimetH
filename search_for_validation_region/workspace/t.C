#define t_cxx
#include "t.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void t::Loop()
{
    if (fChain == 0) return;
    TFile *fout = new TFile("eos/output_" + tag + "_hadronic.root", "RECREATE");

    //==================================================
    // embark on middle purity region study
    //==================================================
    //My_Cut_Values cut_mp_SR1 = set_threshold( {0.000,0.943}, {0.800,1.000}, {480.,800.}  );
    //My_Cut_Values cut_mp_SR1 = set_threshold( {0.000,0.910}, {0.800,1.000}, {480.,800.}  );
    //My_Cut_Values cut_mp_SR2 = set_threshold( {0.000,0.960}, {0.800,1.000}, {550.,1150.} );
    //My_Cut_Values cut_mp_SR3 = set_threshold( {0.000,0.950}, {0.800,1.000}, {650.,1600.} );

    My_Cut_Values cut_mp_SR1 = set_threshold( {0.910,0.943}, {0.700,1.000}, {480.,800.}  );
    My_Cut_Values cut_mp_SR2 = set_threshold( {0.880,0.960}, {0.700,1.000}, {550.,1150.} );
    My_Cut_Values cut_mp_SR3 = set_threshold( {0.850,0.950}, {0.700,1.000}, {650.,1600.} );

    //==================================================
    // set up for validation region scanning
    //==================================================
    bool perform_validation_search = false;

    int nCuts = 156;
    double step = 0.005;
    vector<My_Cut_Values> cut_VRs;
    for(int i=0; i<nCuts; ++i) {
        double upper = 0.780;
        double lower = 0.775 - (double)i * step;
        My_Cut_Values cut = set_threshold( {lower,upper}, {0.000,0.800}, {0.00,480.} );
        cut_VRs.push_back(cut);
    }

    //==================================================
    // event loop
    //==================================================
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        vector<double> v_bdts_SR1         = { BDTG_TprimeVsNonHiggs_M600_M700   , BDTG_TprimeVsHiggs_M600_M700   };
        vector<double> v_bdts_SR2         = { BDTG_TprimeVsNonHiggs_M800_M1000  , BDTG_TprimeVsHiggs_M800_M1000  };
        vector<double> v_bdts_SR3         = { BDTG_TprimeVsNonHiggs_M1100_M1200 , BDTG_TprimeVsHiggs_M1100_M1200 };
        vector<double> v_bdts_M600_M700   = { BDTG_TprimeVsNonHiggs_M600_M700   , BDTG_TprimeVsHiggs_M600_M700   };
        vector<double> v_bdts_M800_M1000  = { BDTG_TprimeVsNonHiggs_M800_M1000  , BDTG_TprimeVsHiggs_M800_M1000  };
        vector<double> v_bdts_M1100_M1200 = { BDTG_TprimeVsNonHiggs_M1100_M1200 , BDTG_TprimeVsHiggs_M1100_M1200 };

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // (un)-blind mgg window
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        //bool unblind_mgg_window = true;
        //if (Cut(ientry, unblind_mgg_window) < 0) continue;

        bool is_in_mgg_window = dipho_mass > 115. && dipho_mass < 135.;
        if(!is_in_mgg_window) continue;

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // 2D BDT maps
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        if (Tprime_mass > 0.   && Tprime_mass < 480.)  h_validation_map->Fill(BDTG_TprimeVsNonHiggs_M600_M700, BDTG_TprimeVsHiggs_M600_M700, weight);
        if (Tprime_mass > 480. && Tprime_mass < 800.)  h_bdt_map_SR1->Fill(BDTG_TprimeVsNonHiggs_M600_M700, BDTG_TprimeVsHiggs_M600_M700, weight);
        if (Tprime_mass > 550. && Tprime_mass < 1150.) h_bdt_map_SR2->Fill(BDTG_TprimeVsNonHiggs_M800_M1000, BDTG_TprimeVsHiggs_M800_M1000, weight);
        if (Tprime_mass > 650. && Tprime_mass < 1600.) h_bdt_map_SR3->Fill(BDTG_TprimeVsNonHiggs_M1100_M1200, BDTG_TprimeVsHiggs_M1100_M1200, weight);

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // validation regions
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        if(perform_validation_search) {
            double value = 0.5;
            if (Cut(ientry, cut_VR1, v_bdts_M600_M700) > 0){ h_counter_validation_region->Fill(value, weight); }

            for(int i=0; i<nCuts; ++i) {
                value = 0.5 + (double)(i+1);
                if (Cut(ientry, cut_VRs[i], v_bdts_M600_M700) > 0){ h_counter_validation_region->Fill(value, weight); }
            }
            
            value = 0.5 + (double)(nCuts+1);
            if (Cut(ientry , cut_VR_smh  , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+0. , weight); }
            if (Cut(ientry , cut_VR_sig  , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+1. , weight); }
            if (Cut(ientry , cut_VR_inv  , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+2. , weight); }
            if (Cut(ientry , cut_VR_inv2 , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+3. , weight); }
            if (Cut(ientry , cut_VR_val2 , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+4. , weight); }
            if (Cut(ientry , cut_VR_val3 , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+5. , weight); }
            if (Cut(ientry , cut_check   , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+6. , weight); }
            if (Cut(ientry , cut_VR_val  , v_bdts_M600_M700) > 0) { h_counter_validation_region->Fill(value+7. , weight); }
        }

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // signal regions
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        bool is_negative_bin = dipho_mass > 130. && dipho_mass < 135.;
        if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) {
            printf(">>> weight in sr1: %.2f\n", weight);
            if (is_negative_bin && weight<0.) yc_SR1.Add(0.);
            else yc_SR1.Add(weight);
        }
        if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) {
            printf(">>> weight in sr2: %.2f\n", weight);
            if (is_negative_bin && weight<0.) yc_SR2.Add(0.);
            else yc_SR2.Add(weight);
        }
        if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) {
            printf(">>> weight in sr3: %.2f\n", weight);
            if (is_negative_bin && weight<0.) yc_SR3.Add(0.);
            else yc_SR3.Add(weight);
        }

        //if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { yc_SR1.Add(weight); }
        //if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { yc_SR2.Add(weight); }
        //if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { yc_SR3.Add(weight); }
        if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { h_counter_signal_region->Fill(0.5 , weight); }
        if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { h_counter_signal_region->Fill(1.5 , weight); }
        if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { h_counter_signal_region->Fill(2.5 , weight); }
        if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { h_mass_map_SR1->Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_SR1-> Fill(dipho_mass , weight); }
        if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { h_mass_map_SR2->Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_SR2-> Fill(dipho_mass , weight); }
        if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { h_mass_map_SR3->Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_SR3-> Fill(dipho_mass , weight); }

        if (Cut(ientry , cut_mp_SR1 , v_bdts_SR1) > 0) { h_mass_map_mp_SR1->Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_mp_SR1-> Fill(dipho_mass , weight); }

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // middle-purity regions
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        if (Cut(ientry , cut_mp_SR1 , v_bdts_SR1) > 0) { yc_mp_SR1.Add(weight); }
        if (Cut(ientry , cut_mp_SR2 , v_bdts_SR2) > 0) { yc_mp_SR2.Add(weight); }
        if (Cut(ientry , cut_mp_SR3 , v_bdts_SR3) > 0) { yc_mp_SR3.Add(weight); }
    }

    Report();

    if(false && is_data) {
        Make_plots_2D_mass();
        Make_plots_2D_phase_space();
        Make_plots_validation_regions();
        Make_plots_2D_mass_middle_purity();
    }

    fout->cd();
    h_mass_map_SR1->Write();
    h_mass_map_SR2->Write();
    h_mass_map_SR3->Write();
    h_mass_map_mp_SR1->Write();
    //h_counter_signal_region->Write();
    //h_counter_validation_region->Write();
    //h_bdt_map_SR1->Write();
    //h_bdt_map_SR2->Write();
    //h_bdt_map_SR3->Write();
    fout->Write();
    fout->Close();
}
