#!/usr/bin/env python
import ROOT
ROOT.gROOT.SetBatch(True)

myLabel = {
    "QCD_GammaJets_imputed" : "Data-driven (#gamma)+jets",
    "QCD": "MC (#gamma)+jets",
    #"QCD": "MC QCD",
    "GammaJets" : "MC #gamma+jets",

    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_central_n100" : "central HT weight",
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_up_n100" : "central HT weight #times 150%",
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_down_n100" : "central HT weight #times 50%",
    #"hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_up_n100" : "#plus 50 % HT weight",
    #"hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_down_n100" : "#minus 50 % HT weight",
}

# setup {{{
d_fit_const = {"central":[], "error":[]}
d_fit_mean  = {"central":[], "error":[]}
d_fit_sigma = {"central":[], "error":[]}

#--------------------------------------------------

masses = [600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200]
masses_v2 = [600, 625, 650, 675, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200]
mass_M600_M700 = [600, 625, 650, 675, 700]
mass_M800_M1000 = [800, 900, 1000]
mass_M1100_M1200 = [1100, 1200]

ytitles = {
    "yields": {
        "hHT":"Yields / 20 GeV",
        "hJet1pT":"Yields / 20 GeV",
        "hJet2pT":"Yields / 20 GeV",
        "hJet3pT":"Yields / 20 GeV",
        "hJet4pT":"Yields / 20 GeV",
        "hjet1_ptOverM":"Yields / 0.5",
        "hjet2_ptOverM":"Yields / 0.5",
        "hjet3_ptOverM":"Yields / 0.5",
        "hjet4_ptOverM":"Yields / 0.5",
        "hMass_fine":"Yields / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed03_fine":"Yields / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed04_fine":"Yields / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed05_fine":"Yields / 0.5 GeV",
        "hmass_tprime_cov_fine":"Yields / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"Yields / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"Yields / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"Yields / 5 GeV",

        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_difference":"Yields / 0.02",
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_relativeDifference":"Yields / 0.02",
    },
    "normalized": {
        "hHT":"Arbitrary unit / 20 GeV",
        "hJet1pT":"Arbitrary unit / 20 GeV",
        "hJet2pT":"Arbitrary unit / 20 GeV",
        "hJet3pT":"Arbitrary unit / 20 GeV",
        "hJet4pT":"Arbitrary unit / 20 GeV",
        "hjet1_ptOverM":"Arbitrary unit / 0.5",
        "hjet2_ptOverM":"Arbitrary unit / 0.5",
        "hjet3_ptOverM":"Arbitrary unit / 0.5",
        "hjet4_ptOverM":"Arbitrary unit / 0.5",
        "hMass_fine":"Arbitrary unit / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed03_fine":"Arbitrary unit / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed04_fine":"Arbitrary unit / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed05_fine":"Arbitrary unit / 0.5 GeV",
        "hmass_tprime_cov_fine":"Arbitrary unit / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"Arbitrary unit / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"Arbitrary unit / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"Arbitrary unit / 5 GeV",

        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_difference":"Arbitrary unit / 0.02",
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_relativeDifference":"#frac{New BDT #minus Old BDT}{Old BDT}",
    },
}

xtitles = {
    "hHT":"H_{T} [GeV]",
    "hJet1pT":"Jet1 p_{T} [GeV]",
    "hJet2pT":"Jet2 p_{T} [GeV]",
    "hJet3pT":"Jet3 p_{T} [GeV]",
    "hJet4pT":"Jet4 p_{T} [GeV]",
    "hjet1_ptOverM":"Jet1 p_{T} / M_{top}",
    "hjet2_ptOverM":"Jet2 p_{T} / M_{top}",
    "hjet3_ptOverM":"Jet3 p_{T} / M_{top}",
    "hjet4_ptOverM":"Jet4 p_{T} / M_{top}",
    "hMass_fine":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed03_fine":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed04_fine":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed05_fine":"M_{#gamma#gamma} (GeV)",
    "hmass_tprime_cov_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"M_{bjj#gamma#gamma} (GeV)",

    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_difference":"New BDT #minus Old BDT",
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_relativeDifference":"#frac{New BDT #minus Old BDT}{Old BDT}",
}

v_set1 = {
    #600  : ROOT.kMagenta,
    #625  : ROOT.kMagenta+2,
    600  : ROOT.kRed-9,
    625  : ROOT.kRed-7,
    650  : ROOT.kRed,
    675  : ROOT.kRed+2,
    700  : ROOT.kRed+4,
    800  : ROOT.kGreen-5,
    900  : ROOT.kGreen+1,
    1000 : ROOT.kGreen+3,
    1100 : ROOT.kBlue,
    1200 : ROOT.kBlue+2,
}

v_set2 = {
    600  : ROOT.kOrange,
    625  : ROOT.kOrange+2,
    650  : ROOT.kRed,
    675  : ROOT.kRed+3,
    700  : ROOT.kBlack,
    800  : ROOT.kGreen+1,
    900  : ROOT.kGreen+3,
    1000 : ROOT.kCyan,
    1100 : ROOT.kBlue,
    1200 : ROOT.kBlue+2,
}

v_blue = {
    600  : ROOT.kBlue-10,
    625  : ROOT.kBlue-9,
    650  : ROOT.kBlue-7,
    675  : ROOT.kBlue-4,
    700  : ROOT.kBlue,
    800  : ROOT.kBlue+1,
    900  : ROOT.kBlue+2,
    1000 : ROOT.kBlue+3,
    1100 : ROOT.kBlue+4,
    1200 : ROOT.kBlack
}

v_red = {
    600  : ROOT.kRed-10,
    625  : ROOT.kRed-9,
    650  : ROOT.kRed-7,
    675  : ROOT.kRed-4,
    700  : ROOT.kRed,
    800  : ROOT.kRed+1,
    900  : ROOT.kRed+2,
    1000 : ROOT.kRed+3,
    1100 : ROOT.kRed+4,
    1200 : ROOT.kBlack
}

default_color_scheme = {
    #"QCD_GammaJets_imputed" : ROOT.kBlue-7,
    #"GammaJets"             : ROOT.kRed+3,
    "Data"                  : ROOT.kBlack,
    "QCD_GammaJets_imputed" : ROOT.kOrange+6,
    "QCD"                   : ROOT.kOrange+6,
    #"QCD"                   : ROOT.kRed+1,
    "GammaJets"             : ROOT.kRed+3,
    "DiPhoton"              : ROOT.kRed+1,
    "TTGG"                  : ROOT.kGreen-2,
    "TTGJets"               : ROOT.kGreen-7,
    "TTJets"                : ROOT.kSpring+10,
    "VG"                    : ROOT.kViolet-9,
    "DY"                    : ROOT.kCyan-7,
    "GammaJets_Madgraph"    : ROOT.kRed,
    "WJets"                 : ROOT.kBlue+2,
    "TGamma"                : ROOT.kYellow-9,
    "TTZ"                   : ROOT.kAzure+1,
    "TTW"                   : ROOT.kRed,
    "tV"                    : ROOT.kPink-6,
    "VV"                    : ROOT.kPink+6,
    "ttH"                   : ROOT.kCyan-9
}

colors = {
    "hMass_fine":v_set1,
    "hMass_pass_BDTG_smh_cut_mixed03_fine":v_set1,
    "hMass_pass_BDTG_smh_cut_mixed04_fine":v_set1,
    "hMass_pass_BDTG_smh_cut_mixed05_fine":v_set1,
    "hmass_tprime_cov_fine":v_set1,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":v_set1,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":v_set1,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":v_set1,
    "collective":v_set2,
    "hHT":default_color_scheme,
    "hJet1pT":default_color_scheme,
    "hJet2pT":default_color_scheme,
    "hJet3pT":default_color_scheme,
    "hJet4pT":default_color_scheme,
    "hjet1_ptOverM":default_color_scheme,
    "hjet2_ptOverM":default_color_scheme,
    "hjet3_ptOverM":default_color_scheme,
    "hjet4_ptOverM":default_color_scheme,
    #"hMass_fine":v_blue,
    #"hMass_pass_BDTG_smh_cut_mixed03_fine":v_blue,
    #"hMass_pass_BDTG_smh_cut_mixed04_fine":v_blue,
    #"hMass_pass_BDTG_smh_cut_mixed05_fine":v_blue,
    #"hmass_tprime_cov_fine":v_red,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":v_red,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":v_red,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":v_red,
}

ranges = {
    "hHT":[0,1000],
    "hJet1pT":[0,500],
    "hJet2pT":[0,500],
    "hJet3pT":[0,500],
    "hJet4pT":[0,500],
    "hjet1_ptOverM":[0,10.],
    "hjet2_ptOverM":[0,10.],
    "hjet3_ptOverM":[0,10.],
    "hjet4_ptOverM":[0,10.],
    "hMass_fine":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed03_fine":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed04_fine":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed05_fine":[100,180],
    "hmass_tprime_cov_fine":[200,2500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":[480,800],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":[630,1150],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":[750,1600],
    "fullTprime":[350, 1650],
    #"fullTprime":[450, 1650],

    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_difference":[-0.5, 0.5],
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_relativeDifference":[-1, 1],
}

leg_pos_set1 = {
    # key = number of mass points to be ploted in a figure
    10 : [0.58, 0.25, 0.85, 0.85],
    5  : [0.58, 0.55, 0.85, 0.85],
    3  : [0.58, 0.67, 0.85, 0.85],
    2  : [0.58, 0.73, 0.85, 0.85],
}

leg_pos_set2 = {
    # key = number of mass points to be ploted in a figure
    10 : [0.58, 0.25, 0.85, 0.85],
    3  : [0.58, 0.67, 0.85, 0.85],
    2  : [0.58, 0.73, 0.85, 0.85],
    5  : [0.12, 0.55, 0.30, 0.85],
}

leg_pos_set3 = [0.15, 0.75, 0.35, 0.87]
leg_pos_set4 = [0.17, 0.45, 0.35, 0.57]
leg_pos_set5 = [0.57, 0.20, 0.87, 0.35]

legend_position = {
    "hHT":leg_pos_set1,
    "hJet1pT":leg_pos_set1,
    "hJet2pT":leg_pos_set1,
    "hJet3pT":leg_pos_set1,
    "hJet4pT":leg_pos_set1,
    "hjet1_ptOverM":leg_pos_set1,
    "hjet2_ptOverM":leg_pos_set1,
    "hjet3_ptOverM":leg_pos_set1,
    "hjet4_ptOverM":leg_pos_set1,
    "hMass_fine":leg_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed03_fine":leg_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed04_fine":leg_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed05_fine":leg_pos_set1,
    "hmass_tprime_cov_fine":leg_pos_set2,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":leg_pos_set2,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":leg_pos_set2,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":leg_pos_set2,
    # individual plot with fit
    "tprime":leg_pos_set5,
    600 :leg_pos_set3,
    625 :leg_pos_set3,
    650 :leg_pos_set3,
    675 :leg_pos_set4,
    700 :leg_pos_set4,
    800 :leg_pos_set3,
    900 :leg_pos_set3,
    1000:leg_pos_set4,
    1100:leg_pos_set3,
    1200:leg_pos_set3,
}

stat_pos_set1 = [0.89, 0.87, 0.20, 0.20]
stat_pos_set2 = [0.89, 0.87, 0.15, 0.15]
stat_pos_set3 = [0.43, 0.87, 0.15, 0.15]
stat_position = {
    "hHT":stat_pos_set1,
    "hMass_fine":stat_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed03_fine":stat_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed04_fine":stat_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed05_fine":stat_pos_set1,
    "hmass_tprime_cov_fine":stat_pos_set1,
    600 :stat_pos_set2,
    625 :stat_pos_set2,
    650 :stat_pos_set2,
    675 :stat_pos_set3,
    700 :stat_pos_set3,
    800 :stat_pos_set2,
    900 :stat_pos_set2,
    1000:stat_pos_set3,
    1100:stat_pos_set2,
    1200:stat_pos_set2,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":stat_pos_set2,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":stat_pos_set2,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":stat_pos_set2,
}

fit_ranges = {
    # for fit summary
    "mgg"   :{ "range":[122., 128.] , "mean" :[123.5, 125.5], "sigma":[1.0, 1.8] },
    "tprime":{ "range":[500., 1300.], "mean" :[500., 1300.] , "sigma":[0., 80.] },

    # for individual fit
    600 :{ "range":[550. ,650.]  },
    625 :{ "range":[575. ,675.]  },
    650 :{ "range":[600. ,700.]  },
    675 :{ "range":[625. ,725.]  },
    700 :{ "range":[650. ,750.]  },
    800 :{ "range":[740. ,860.]  },
    900 :{ "range":[840. ,960.]  },
    1000:{ "range":[940. ,1060.] },
    1100:{ "range":[1020.,1180.] },
    1200:{ "range":[1120.,1280.] },

    #600 :{ "range":[540. ,660.]  },
    #625 :{ "range":[565. ,685.]  },
    #650 :{ "range":[590. ,710.]  },
    #675 :{ "range":[615. ,735.]  },
    #700 :{ "range":[640. ,760.]  },
    #800 :{ "range":[720. ,880.]  },
    #900 :{ "range":[820. ,980.]  },
    #1000:{ "range":[920. ,1080.] },
    #1100:{ "range":[1020.,1180.] },
    #1200:{ "range":[1120.,1280.] },
}

fit_ytitles = {
    "mgg":{
        "range":"Mean and sigma of m(#gamma#gamma) from Gaussian fit",
        "mean" :"Mean of m(#gamma#gamma) from Gaussian fit",
        "sigma":"Sigma of m(#gamma#gamma) from Gaussian fit",
    },
    "tprime":{
        "range":"Mean and sigma of M_{bjj#gamma#gamma} from Gaussian fit",
        "mean" :"Mean of M_{bjj#gamma#gamma} from Gaussian fit",
        "sigma":"Sigma of M_{bjj#gamma#gamma} from Gaussian fit",
    },
}

labels = {
    "Data": "Data",
    "DiPhoton": "#gamma#gamma + Jets",
    "GammaJets": "#gamma + Jets",
    "QCD": "QCD",
    "TTGG": "t#bar{t} + #gamma#gamma",
    "TTGJets": "t#bar{t} + #gamma",
    "VG": "V + #gamma",
    "WJets": "W+Jets",
    "TTJets": "t#bar{t} + Jets", 
    "THQ": "tHq",
    "ggH": "ggH",
    "VH": "VH",
    "VBF": "VBF",
    "TGamma": "t+#gamma+Jets",
    "QCD_GammaJets_imputed": "(#gamma) + Jets",
    "TTZ": "t#bar{tZ}",
    "TTW": "t#bar{tW}",
    "VV": "VV",
    "tV": "t + V",
    "ttH": "t#bar{tH}(125)",
    "TT_FCNC_hut": "t#bar{t} FCNC (Hut)",
    "TT_FCNC_hct": "t#bar{t} FCNC (Hct)",
    "ST_FCNC_hut": "t FCNC (Hut)",
    "ST_FCNC_hct": "t FCNC (Hct)",
    "TprimeBToTH_M-600" : "T'(600)",
    "TprimeBToTH_M-625" : "T'(625)",
    "TprimeBToTH_M-650" : "T'(650)",
    "TprimeBToTH_M-675" : "T'(675)",
    "TprimeBToTH_M-700" : "T'(700)",
    "TprimeBToTH_M-800" : "T'(800)",
    "TprimeBToTH_M-900" : "T'(900)",
    "TprimeBToTH_M-1000": "T'(1000)",
    "TprimeBToTH_M-1100": "T'(1100)",
    "TprimeBToTH_M-1200": "T'(1200)"
}
#}}}
