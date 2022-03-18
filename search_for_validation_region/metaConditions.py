#!/usr/bin/env python

samples = {
    "data": ["Data"],

    "nrb" : [
        "DiPhotonJets",
        "GJet_Pt",
        "QCD",
        "TGJets",
        "TTGG",
        "TTGJets",
        "TTJets",
        "WG",
        "WW",
        "WZ",
        "ZG",
        "ZZ",
    ],

    "smh" : [
        "ttHJet",
        "GluGluHToGG",
        "THQ",
        "VBF",
        "VHToGG",
    ],

    "signal" : [
        "TprimeBToTH_M-600",
        "TprimeBToTH_M-625",
        "TprimeBToTH_M-650",
        "TprimeBToTH_M-675",
        "TprimeBToTH_M-700",
        #"TprimeBToTH_M-800",
        #"TprimeBToTH_M-900",
        #"TprimeBToTH_M-1000",
        #"TprimeBToTH_M-1100",
        #"TprimeBToTH_M-1200",
    ],
}

convert_signal_title = {
    "SMH" : "SMH",
    "Data" : "Data",
    "TprimeBToTH_M-600"  : "VLQ M-600",
    "TprimeBToTH_M-625"  : "VLQ M-625",
    "TprimeBToTH_M-650"  : "VLQ M-650",
    "TprimeBToTH_M-675"  : "VLQ M-675",
    "TprimeBToTH_M-700"  : "VLQ M-700",
    "TprimeBToTH_M-800"  : "VLQ M-800",
    "TprimeBToTH_M-900"  : "VLQ M-900",
    "TprimeBToTH_M-1000" : "VLQ M-1000",
    "TprimeBToTH_M-1100" : "VLQ M-1100",
    "TprimeBToTH_M-1200" : "VLQ M-1200",
}
keywords_v1 = [
    "vs_counter_MT_less_550",
    "vs_counter_bdt_smh_800",
    "vs_counter_bdt_smh_700",
    "vs_counter_bdt_smh_600",
    "vs_counter_bdt_smh_500",
    "vs_counter_bdt_smh_400",
    "vs_counter_bdt_smh_300",
    "vs_counter_bdt_smh_200",
    "vs_counter_bdt_smh_100",
    "vs_yields_MT_less_550",
    "vs_yields_bdt_smh_800",
    "vs_yields_bdt_smh_700",
    "vs_yields_bdt_smh_600",
    "vs_yields_bdt_smh_500",
    "vs_yields_bdt_smh_400",
    "vs_yields_bdt_smh_300",
    "vs_yields_bdt_smh_200",
    "vs_yields_bdt_smh_100",
]

keywords_v2 = [
    "vs_counter_MT_less_300",
    "vs_counter_MT_less_400",
    "vs_counter_MT_less_480",
    "vs_counter_MT_less_550",
    "vs_counter_bdt_smh_800",
    "vs_counter_bdt_smh_700",
    "vs_counter_bdt_smh_600",
    "vs_counter_bdt_smh_500",
    "vs_counter_bdt_smh_400",
    "vs_counter_bdt_smh_300",
    "vs_counter_bdt_smh_200",
    "vs_counter_bdt_smh_100",
]

keywords_v3 = [
    "vs_yields_bdt_smh_800",
    "vs_yields_bdt_smh_700",
    "vs_yields_bdt_smh_600",
    "vs_yields_bdt_smh_500",
    "vs_yields_bdt_smh_400",
    "vs_yields_bdt_smh_300",
    "vs_yields_bdt_smh_200",
    "vs_yields_bdt_smh_100",
]

keywords_v4 = [
    #"vs_yields_MT_less_550",
    "vs_yields_MT_less_400",
    "vs_yields_MT_less_440",
    "vs_yields_MT_less_480",
    "vs_yields_MT_large_480",
    "vs_yields_MT_large_800",
]

keywords_sr = [
    "vs_counter_MT_less_480",
    "vs_counter_MT_large_480",
    "vs_counter_MT_large_800",

    "is_within_SR_mixed03",
    "is_within_SR_mixed04",
    "is_within_SR_mixed05",

    #"vs_counter_MT_less_400",
    #"vs_counter_MT_less_440",
    #"vs_counter_MT_less_480",
    #"vs_counter_MT_less_550",
    #"vs_counter_MT_large_480",
    #"vs_counter_MT_large_800",
]

keywords_v5 = [
    "vs_yields_bdt_nrb_800",
    "vs_yields_bdt_nrb_700",
    "vs_yields_bdt_nrb_600",
    "vs_yields_bdt_nrb_500",
    "vs_yields_bdt_nrb_400",
    "vs_yields_bdt_nrb_300",
    "vs_yields_bdt_nrb_200",
    "vs_yields_bdt_nrb_100",

    #"is_within_SR_mixed03",
    #"yields_within_SR_mixed03",
]

keywords = keywords_sr
keywords = keywords_v4
