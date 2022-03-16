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
        "TprimeBToTH_M-800",
        "TprimeBToTH_M-900",
        "TprimeBToTH_M-1000",
        "TprimeBToTH_M-1100",
        "TprimeBToTH_M-1200",
    ],
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
    "vs_counter_MT_less_550",
    "vs_counter_bdt_smh_800",
    "vs_counter_bdt_smh_700",
    "vs_counter_bdt_smh_600",
    "vs_counter_bdt_smh_500",

    "vs_yields_MT_less_550",
    "vs_yields_bdt_smh_800",
    "vs_yields_bdt_smh_700",
    "vs_yields_bdt_smh_600",
    "vs_yields_bdt_smh_500",

    #"vs_counter_bdt_smh_400",
    #"vs_counter_bdt_smh_300",
    #"vs_counter_bdt_smh_200",
    #"vs_counter_bdt_smh_100",
    #"vs_yields_bdt_smh_400",
    #"vs_yields_bdt_smh_300",
    #"vs_yields_bdt_smh_200",
    #"vs_yields_bdt_smh_100",
]

keywords = keywords_v2
