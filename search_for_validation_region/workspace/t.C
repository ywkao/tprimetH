#define t_cxx
#include "t.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void t::Loop()
{
    if (fChain == 0) return;
    TFile *fout = new TFile("eos/output_" + tag + ".root", "RECREATE");

    My_Cut_Values cut_SR1     = set_threshold( {0.943,1.000}, {0.800,1.000}, {480.,800.}  );
    My_Cut_Values cut_SR2     = set_threshold( {0.960,1.000}, {0.800,1.000}, {550.,1150.} );
    My_Cut_Values cut_SR3     = set_threshold( {0.950,1.000}, {0.800,1.000}, {650.,1600.} );
    My_Cut_Values cut_VR1     = set_threshold( {0.780,0.800}, {0.000,0.800}, {0.00,480.}  );
    My_Cut_Values cut_VR_smh  = set_threshold( {0.000,0.800}, {0.800,1.000}, {0.00,480.}  );
    My_Cut_Values cut_VR_sig  = set_threshold( {0.800,1.000}, {0.800,1.000}, {0.00,480.}  );
    My_Cut_Values cut_VR_inv  = set_threshold( {0.800,1.000}, {0.600,0.800}, {0.00,480.}  );
    My_Cut_Values cut_VR_inv2 = set_threshold( {0.800,1.000}, {0.000,0.600}, {0.00,480.}  );
    My_Cut_Values cut_VR_val  = set_threshold( {0.580,0.780}, {0.000,0.800}, {0.00,480.}  );
    My_Cut_Values cut_VR_val2 = set_threshold( {0.460,0.780}, {0.000,0.800}, {0.00,480.}  );
    My_Cut_Values cut_VR_val3 = set_threshold( {0.180,0.780}, {0.000,0.800}, {0.00,480.}  );
    My_Cut_Values cut_check   = set_threshold( {0.000,1.000}, {0.000,1.000}, {480.,5000.} );

    double yields = 0.;
    double sumW2 = 0.;

    int nCuts = 156;
    double step = 0.005;
    vector<My_Cut_Values> cut_VRs;
    for(int i=0; i<nCuts; ++i) {
        double upper = 0.780;
        double lower = 0.775 - (double)i * step;
        My_Cut_Values cut = set_threshold( {lower,upper}, {0.000,0.800}, {0.00,480.} );
        cut_VRs.push_back(cut);
    }

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
        bool unblind_mgg_window = true;
        if (Cut(ientry, unblind_mgg_window) < 0) continue;

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // validation regions
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        if (Tprime_mass > 0. && Tprime_mass < 480.) h_validation_map->Fill(BDTG_TprimeVsNonHiggs_M600_M700, BDTG_TprimeVsHiggs_M600_M700, weight);

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

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // signal regions
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { h_counter_signal_region-> Fill(0.5 , weight); }
        if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { h_counter_signal_region-> Fill(1.5 , weight); }
        if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { h_counter_signal_region-> Fill(2.5 , weight); }
        //if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { counter_SR1 += 1; yields_SR1 += weight; }
        //if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { counter_SR2 += 1; yields_SR2 += weight; }
        //if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { counter_SR3 += 1; yields_SR3 += weight; }
        if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { h_mass_map_SR1-> Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_SR1-> Fill(dipho_mass , weight); }
        if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { h_mass_map_SR2-> Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_SR2-> Fill(dipho_mass , weight); }
        if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { h_mass_map_SR3-> Fill(dipho_mass , Tprime_mass , weight); h_mass_diphoton_SR3-> Fill(dipho_mass , weight); }

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // check yields
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        if (Cut(ientry , cut_SR1 , v_bdts_SR1) > 0) { yc_SR1.Add(weight); }
        if (Cut(ientry , cut_SR2 , v_bdts_SR2) > 0) { yc_SR2.Add(weight); }
        if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0) { yc_SR3.Add(weight); }

        //if (Cut(ientry , cut_SR3 , v_bdts_SR3) > 0)
        //{
        //    bool is_signal_window = dipho_mass > 115. && dipho_mass < 135.;
        //    if(!is_signal_window) continue;

        //    //bool specific_bin = dipho_mass > 130. && dipho_mass < 135.;
        //    //if(weight < 0. && specific_bin) {
        //    //    printf(">>> negative weight: %.2f\n", weight);
        //    //    continue;
        //    //}

        //    yields += weight;
        //    sumW2 += weight*weight;
        //}
    }

    double uncertainty = sqrt(sumW2);
    printf("result: %.2f \\pm %.2f\n", yields, uncertainty);

    Report();

    if(false && is_data) {
        Make_plots_2D_phase_space();
        Make_plots_validation_regions();
    }

    fout->cd();
    h_counter_signal_region->Write();
    h_counter_validation_region->Write();
    fout->Write();
    fout->Close();
}
