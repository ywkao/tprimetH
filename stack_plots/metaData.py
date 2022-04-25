#!/usr/bin/env python2
import ROOT
ROOT.gROOT.SetBatch(True)

#make_plot(c1, vFiles[i], vNames[i], vMVAHists[j], ext, "BDT Score", vBkgs, vSigs, vWeights, 1, type, year, loose_mva_cut, f_ref, vInfo, yearIdx, doSyst, doRatio, is_MVA_scores);
#make_plot(c1, vFiles[i], vNames[i], vMVAHists[i].ReplaceAll("n2000", "n50"), ext, "BDT Score", vBkgs, vSigs, vWeights, 1, type, year, loose_mva_cut, f_ref, vInfo, yearIdx, doSyst, doRatio, is_MVA_scores);

def get_range(histname):
    if histname in map_range.keys():
        return map_range[histname]
    else:
        return None

map_xbin_range = {
    "hMass" : [41,72],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine" : [0,500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine" : [0,500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine" : [0,500],
}

map_range = {
    "hMass" : [100,180],
    "hMass_pass_BDTG_smh_cut_mixed03" : [100,180],
    "hMass_pass_BDTG_smh_cut_mixed04" : [100,180],
    "hMass_pass_BDTG_smh_cut_mixed05" : [100,180],

    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine" : [400.,900.],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine" : [450.,1250.],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine" : [550.,1700.],

    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_fine" : [480.,800.],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_fine" : [550.,1150.],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_fine" : [650.,1600.],

    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_n50" : [0., 1.],
    "hMVA_value_nrb_varset8_mixed04_tmva_bdtg_n50" : [0., 1.],
    "hMVA_value_nrb_varset8_mixed05_tmva_bdtg_n50" : [0., 1.],
    "hMVA_value_smh_varset8_mixed03_tmva_bdtg_n50" : [0., 1.],
    "hMVA_value_smh_varset8_mixed04_tmva_bdtg_n50" : [0., 1.],
    "hMVA_value_smh_varset8_mixed05_tmva_bdtg_n50" : [0., 1.],
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_mggWindow_n50" : [0., 1.],
    "hMVA_value_nrb_varset8_mixed04_tmva_bdtg_mggWindow_n50" : [0., 1.],
    "hMVA_value_nrb_varset8_mixed05_tmva_bdtg_mggWindow_n50" : [0., 1.],
    "hMVA_value_smh_varset8_mixed03_tmva_bdtg_mggWindow_n50" : [0., 1.],
    "hMVA_value_smh_varset8_mixed04_tmva_bdtg_mggWindow_n50" : [0., 1.],
    "hMVA_value_smh_varset8_mixed05_tmva_bdtg_mggWindow_n50" : [0., 1.],
}

signals = "TprimeBToTH_M-600|TprimeBToTH_M-900|TprimeBToTH_M-1200"
smHiggs = "ttH|ggH|THQ|VH|VBF"
backgrounds = "DiPhoton|QCD_GammaJets_imputed|TTGG|TTGJets|TTJets|VG" # data-driven

map_colors = {
    "TprimeBToTH_M-600"     : ROOT.kRed,
    "TprimeBToTH_M-900"     : ROOT.kBlue,
    "TprimeBToTH_M-1200"    : ROOT.kMagenta,
    "SMH"                   : ROOT.kBlack,
    "DiPhoton"              : ROOT.kRed+1,
    "QCD_GammaJets_imputed" : ROOT.kOrange+6,
    "TTGG"                  : ROOT.kGreen-2,
    "TTGJets"               : ROOT.kGreen-7,
    "TTJets"                : ROOT.kSpring+10,
    "VG"                    : ROOT.kViolet-9,
    "ttH" : ROOT.kCyan,
    "ggH" : ROOT.kCyan,
    "THQ" : ROOT.kCyan,
    "VH"  : ROOT.kCyan,
    "VBF" : ROOT.kCyan,
}

map_labels = {
    "DY"                    : "Drell-Yan",
    "DiPhoton"              : "#gamma#gamma + Jets",
    "GammaJets"             : "#gamma + Jets",
    "GammaJets_Madgraph"    : "#gamma + Jets (Madgraph)",
    "QCD"                   : "QCD",
    "TTGG"                  : "t#bar{t} + #gamma#gamma",
    "TTGJets"               : "t#bar{t} + #gamma",
    "VG"                    : "V + #gamma",
    "WJets"                 : "W+Jets",
    "TTJets"                : "t#bar{t} + Jets",
    "THQ"                   : "tHq",
    "ggH"                   : "ggH",
    "VH"                    : "VH",
    "VBF"                   : "VBF",
    "TGamma"                : "t+#gamma+Jets",
    "QCD_GammaJets_imputed" : "(#gamma) + Jets",
    "TTZ"                   : "t#bar{t}Z",
    "TTW"                   : "t#bar{t}W",
    "VV"                    : "VV",
    "tV"                    : "t + V",
    "ttH"                   : "t#bar{t}H(125)",
    "TT_FCNC_hut"           : "t#bar{t} FCNC (Hut)",
    "TT_FCNC_hct"           : "t#bar{t} FCNC (Hct)",
    "ST_FCNC_hut"           : "t FCNC (Hut)",
    "ST_FCNC_hct"           : "t FCNC (Hct)",
    "TprimeBToTH_M-600"     : "T'(600)",
    "TprimeBToTH_M-625"     : "T'(625)",
    "TprimeBToTH_M-650"     : "T'(650)",
    "TprimeBToTH_M-675"     : "T'(675)",
    "TprimeBToTH_M-700"     : "T'(700)",
    "TprimeBToTH_M-800"     : "T'(800)",
    "TprimeBToTH_M-900"     : "T'(900)",
    "TprimeBToTH_M-1000"    : "T'(1000)",
    "TprimeBToTH_M-1100"    : "T'(1100)",
    "TprimeBToTH_M-1200"    : "T'(1200)",
}

map_lumi = {
    "2016": 36.3,
    "2017": 41.5,
    "2018": 59.8,
    "RunII": 138,
    "default": 138,
}

hist_mass = [
    "hMass",
    "hMass_sideband",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine",
    "hMass_pass_BDTG_nrb_cut_mixed03",
    "hMass_pass_BDTG_nrb_cut_mixed04",
    "hMass_pass_BDTG_nrb_cut_mixed05",
    "hMass_pass_BDTG_smh_cut_mixed03",
    "hMass_pass_BDTG_smh_cut_mixed04",
    "hMass_pass_BDTG_smh_cut_mixed05",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_coarser",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_coarser",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_coarser",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_coarser",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_coarser",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_coarser",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_fine",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_fine",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_fine",
]

hist_var = [
    "hPhotonMaxIDMVA_fine",
    "hPhotonMinIDMVA_fine",
    "hNVtx",
    "hPtHiggs",
    "hDiphotonPtOverMass",
    "hPhotonDeltaR",
    "hRapidity",
    "hAbsCosHelicity",
    "hDiphotonCosPhi",
    "hPhotonLeadPt",
    "hPhotonLeadEta",
    "hPhotonLeadPhi",
    "hPhotonLeadIDMVA",
    "hPhotonLeadPToM",
    "hPhotonLeadPixelSeed",
    "hPhotonSubleadPt",
    "hPhotonSubleadEta",
    "hPhotonSubleadPhi",
    "hPhotonSubleadIDMVA",
    "hPhotonSubleadPToM",
    "hPhotonSubleadPixelSeed",
    "hPhotonMaxIDMVA",
    "hPhotonMinIDMVA",
    "hmass_wboson_cov",
    "hmass_top_cov",
    "hmass_tprime_cov",
    "hmass_tprime_tilde",
    "hcov_chi2_value",
    "hchi2_bjet_pt",
    "hchi2_wjet1_pt",
    "hchi2_wjet2_pt",
    "hchi2_bjet_eta",
    "hchi2_wjet1_eta",
    "hchi2_wjet2_eta",
    "hchi2_bjet_phi",
    "hchi2_wjet1_phi",
    "hchi2_wjet2_phi",
    "hchi2_wjets_deltaR",
    "hchi2_wboson_pt",
    "hchi2_wboson_eta",
    "hchi2_wboson_mass",
    "hchi2_wboson_deltaR_bjet",
    "hchi2_tbw_mass",
    "hchi2_tbw_pt",
    "hchi2_tbw_eta",
    "hchi2_tbw_deltaR_dipho",
    "hchi2_tprime_ptOverM",
    "hchi2_tprime_eta",
    "hchi2_tprime_deltaR_tbw",
    "hchi2_tprime_deltaR_dipho",
    "hchi2_bjet_btagScores",
    "hchi2_wjet1_btagScores",
    "hchi2_wjet2_btagScores",
    "htprime_pt_ratio",
    "hchi2_bjet_ptOverM",
    "hchi2_wjet1_ptOverM",
    "hchi2_wjet2_ptOverM",
    "hchi2_wboson_ptOverM",
    "hchi2_tbw_ptOverM",
    "hhelicity_tprime",
    "hNJets",
    "hNbLoose",
    "hNbMedium",
    "hNbTight",
    "hHT",
    "hHT_coarse",
    "hMetPt",
    "hMetPhi",
    "hMaxBTag",
    "hSecondMaxBTag",
    "hJet1pT",
    "hJet2pT",
    "hJet3pT",
    "hJet4pT",
    "hJet5pT",
    "hJet6pT",
    "hJet1Eta",
    "hJet2Eta",
    "hJet3Eta",
    "hJet4Eta",
    "hJet5Eta",
    "hJet6Eta",
    "hJet1Phi",
    "hJet2Phi",
    "hJet3Phi",
    "hJet4Phi",
    "hJet5Phi",
    "hJet6Phi",
    "hJet1BTag",
    "hJet2BTag",
    "hJet3BTag",
    "hJet4BTag",
    "hJet5BTag",
    "hJet6BTag",
    "hjet1_ptOverM",
    "hjet2_ptOverM",
    "hjet3_ptOverM",
    "hjet4_ptOverM",
    "hPhotonLeadSigmaIEtaIEta",
    "hPhotonLeadHOverE",
    "hPhotonLeadR9",
    "hPhotonLeadSigmaEOverE",
    "hPhotonSubleadSigmaIEtaIEta",
    "hPhotonSubleadHOverE",
    "hPhotonSubleadR9",
    "hPhotonSubleadSigmaEOverE",
]

map_xtitles = {
    "hMass"                                                       : "m_{#gamma#gamma} [GeV]",
    "hMass_sideband"                                              : "m_{#gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine"              : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine"              : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine"              : "m_{bjj + #gamma#gamma} [GeV]",
    "hMass_pass_BDTG_nrb_cut_mixed03"                             : "m_{#gamma#gamma} [GeV]",
    "hMass_pass_BDTG_nrb_cut_mixed04"                             : "m_{#gamma#gamma} [GeV]",
    "hMass_pass_BDTG_nrb_cut_mixed05"                             : "m_{#gamma#gamma} [GeV]",
    "hMass_pass_BDTG_smh_cut_mixed03"                             : "m_{#gamma#gamma} [GeV]",
    "hMass_pass_BDTG_smh_cut_mixed04"                             : "m_{#gamma#gamma} [GeV]",
    "hMass_pass_BDTG_smh_cut_mixed05"                             : "m_{#gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_coarser" : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_coarser" : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_coarser" : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_coarser"           : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_coarser"           : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_coarser"           : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine"              : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine"              : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine"              : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_fine"    : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_fine"    : "m_{bjj + #gamma#gamma} [GeV]",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_fine"    : "m_{bjj + #gamma#gamma} [GeV]",
    "hPhotonMaxIDMVA_fine"                                        : "Max #gamma ID",
    "hPhotonMinIDMVA_fine"                                        : "Min #gamma ID",
    "hNVtx"                                                       : "# Vertices",
    "hPtHiggs"                                                    : "DiPhoton p_{T} [GeV]",
    "hDiphotonPtOverMass"                                         : "p_{T}^{#gamma#gamma} / m_{#gamma#gamma}",
    "hPhotonDeltaR"                                               : "#Delta R(#gamma_{1}, #gamma_{2})",
    "hRapidity"                                                   : "Y_{#gamma#gamma} [GeV^{1/2}]",
    "hAbsCosHelicity"                                             : "|cos(#theta_{helicity})| (p_{#gamma #gamma})",
    "hDiphotonCosPhi"                                             : "|cos(#Delta #phi_{#gamma 1, #gamma 2})|",
    "hPhotonLeadPt"                                               : "p_{T}(#gamma_{1}) [GeV]",
    "hPhotonLeadEta"                                              : "#eta(#gamma_{1})",
    "hPhotonLeadPhi"                                              : "#phi(#gamma_{1})",
    "hPhotonLeadIDMVA"                                            : "Photon ID MVA(#gamma_{1})",
    "hPhotonLeadPToM"                                             : "p_{T}/m_{#gamma#gamma} (#gamma_{1})",
    "hPhotonLeadPixelSeed"                                        : "Lead #gamma PSV",
    "hPhotonSubleadPt"                                            : "p_{T}(#gamma_{2}) [GeV]",
    "hPhotonSubleadEta"                                           : "#eta(#gamma_{2})",
    "hPhotonSubleadPhi"                                           : "#phi(#gamma_{2})",
    "hPhotonSubleadIDMVA"                                         : "Photon ID MVA(#gamma_{2})",
    "hPhotonSubleadPToM"                                          : "p_{T}/m_{#gamma#gamma} (#gamma_{2})",
    "hPhotonSubleadPixelSeed"                                     : "Sublead #gamma PSV",
    "hPhotonMaxIDMVA"                                             : "Max #gamma ID",
    "hPhotonMinIDMVA"                                             : "Min #gamma ID",
    "hmass_wboson_cov"                                            : "W boson mass [GeV]",
    "hmass_top_cov"                                               : "top quark mass [GeV]",
    "hmass_tprime_cov"                                            : "T' quark mass [GeV]",
    "hmass_tprime_tilde"                                          : "#tildeT' quark mass [GeV]",
    "hcov_chi2_value"                                             : "Minimum #chi^{2} value",
    "hchi2_bjet_pt"                                               : "bjet p_{T} [GeV]",
    "hchi2_wjet1_pt"                                              : "wjet1 p_{T} [GeV]",
    "hchi2_wjet2_pt"                                              : "wjet2 p_{T} [GeV]",
    "hchi2_bjet_eta"                                              : "bjet #eta",
    "hchi2_wjet1_eta"                                             : "wjet1 #eta",
    "hchi2_wjet2_eta"                                             : "wjet2 #eta",
    "hchi2_bjet_phi"                                              : "bjet #phi",
    "hchi2_wjet1_phi"                                             : "wjet1 #phi",
    "hchi2_wjet2_phi"                                             : "wjet2 #phi",
    "hchi2_wjets_deltaR"                                          : "#DeltaR(wjet1,wjet2)",
    "hchi2_wboson_pt"                                             : "wboson p_{T} [GeV]",
    "hchi2_wboson_eta"                                            : "wboson #eta",
    "hchi2_wboson_mass"                                           : "wboson mass",
    "hchi2_wboson_deltaR_bjet"                                    : "#DeltaR(wboson,bjet)",
    "hchi2_tbw_mass"                                              : "Top quark mass",
    "hchi2_tbw_pt"                                                : "Top quark p_{T} [GeV]",
    "hchi2_tbw_eta"                                               : "Top quark #eta",
    "hchi2_tbw_deltaR_dipho"                                      : "#DeltaR(top quark,di-photon)",
    "hchi2_tprime_ptOverM"                                        : "tprime ptOverM",
    "hchi2_tprime_eta"                                            : "tprime #eta",
    "hchi2_tprime_deltaR_tbw"                                     : "#DeltaR(T',top quark)",
    "hchi2_tprime_deltaR_dipho"                                   : "#DeltaR(T',di-photon)",
    "hchi2_bjet_btagScores"                                       : "bjet btagScores",
    "hchi2_wjet1_btagScores"                                      : "wjet1 btagScores",
    "hchi2_wjet2_btagScores"                                      : "wjet2 btagScores",
    "htprime_pt_ratio"                                            : "tprime_pt_ratio",
    "hchi2_bjet_ptOverM"                                          : "bjet ptOverM",
    "hchi2_wjet1_ptOverM"                                         : "wjet1 ptOverM",
    "hchi2_wjet2_ptOverM"                                         : "wjet2 ptOverM",
    "hchi2_wboson_ptOverM"                                        : "wboson ptOverM",
    "hchi2_tbw_ptOverM"                                           : "Top quark ptOverM",
    "hhelicity_tprime"                                            : "|cos(#theta_{helicity}| (p_{top, #gamma#gamma})|",
    "hNJets"                                                      : "N_{jets}",
    "hNbLoose"                                                    : "N_{b-jets} (Loose)",
    "hNbMedium"                                                   : "N_{b-jets} (Medium)" ,
    "hNbTight"                                                    : "N_{b-jets} (Tight)",
    "hHT"                                                         : "HT [GeV]",
    "hHT_coarse"                                                  : "HT [GeV]",
    "hMetPt"                                                      : "E_{T}^{miss} [GeV]",
    "hMetPhi"                                                     : "#phi of MET",
    "hMaxBTag"                                                    : "max b-tag discriminant",
    "hSecondMaxBTag"                                              : "2nd max b-tag discriminant",
    "hJet1pT"                                                     : "Jet1 p_{T} [GeV]",
    "hJet2pT"                                                     : "Jet2 p_{T} [GeV]",
    "hJet3pT"                                                     : "Jet3 p_{T} [GeV]",
    "hJet4pT"                                                     : "Jet4 p_{T} [GeV]",
    "hJet5pT"                                                     : "Jet5 p_{T} [GeV]",
    "hJet6pT"                                                     : "Jet6 p_{T} [GeV]",
    "hJet1Eta"                                                    : "Jet1 #eta",
    "hJet2Eta"                                                    : "Jet2 #eta",
    "hJet3Eta"                                                    : "Jet3 #eta",
    "hJet4Eta"                                                    : "Jet4 #eta",
    "hJet5Eta"                                                    : "Jet5 #eta",
    "hJet6Eta"                                                    : "Jet6 #eta",
    "hJet1Phi"                                                    : "Jet1 #phi",
    "hJet2Phi"                                                    : "Jet2 #phi",
    "hJet3Phi"                                                    : "Jet3 #phi",
    "hJet4Phi"                                                    : "Jet4 #phi",
    "hJet5Phi"                                                    : "Jet5 #phi",
    "hJet6Phi"                                                    : "Jet6 #phi",
    "hJet1BTag"                                                   : "Jet 1 b-tag score",
    "hJet2BTag"                                                   : "Jet 2 b-tag score",
    "hJet3BTag"                                                   : "Jet 3 b-tag score",
    "hJet4BTag"                                                   : "Jet 4 b-tag score",
    "hJet5BTag"                                                   : "Jet 5 b-tag score",
    "hJet6BTag"                                                   : "Jet 6 b-tag score",
    "hjet1_ptOverM"                                               : "Jet1 ptOverM",
    "hjet2_ptOverM"                                               : "Jet2 ptOverM",
    "hjet3_ptOverM"                                               : "Jet3 ptOverM",
    "hjet4_ptOverM"                                               : "Jet4 ptOverM",
    "hPhotonLeadSigmaIEtaIEta"                                    : "#sigma_{i#etai#eta}(#gamma_{1})",
    "hPhotonLeadHOverE"                                           : "h/E(#gamma_{1})",
    "hPhotonLeadR9"                                               : "R9(#gamma_{1})",
    "hPhotonLeadSigmaEOverE"                                      : "#sigma_{E}/E (#gamma_{1})",
    "hPhotonSubleadSigmaIEtaIEta"                                 : "#sigma_{i#etai#eta}(#gamma_{2})",
    "hPhotonSubleadHOverE"                                        : "h/E(#gamma_{2})",
    "hPhotonSubleadR9"                                            : "R9(#gamma_{2})",
    "hPhotonSubleadSigmaEOverE"                                   : "#sigma_{E}/E (#gamma_{2})",

    # BDT scores
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_n50"           : "BDT-NRB score",
    "hMVA_value_nrb_varset8_mixed04_tmva_bdtg_n50"           : "BDT-NRB score",
    "hMVA_value_nrb_varset8_mixed05_tmva_bdtg_n50"           : "BDT-NRB score",
    "hMVA_value_smh_varset8_mixed03_tmva_bdtg_n50"           : "BDT-SMH score",
    "hMVA_value_smh_varset8_mixed04_tmva_bdtg_n50"           : "BDT-SMH score",
    "hMVA_value_smh_varset8_mixed05_tmva_bdtg_n50"           : "BDT-SMH score",
    "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_mggWindow_n50" : "BDT-NRB score",
    "hMVA_value_nrb_varset8_mixed04_tmva_bdtg_mggWindow_n50" : "BDT-NRB score",
    "hMVA_value_nrb_varset8_mixed05_tmva_bdtg_mggWindow_n50" : "BDT-NRB score",
    "hMVA_value_smh_varset8_mixed03_tmva_bdtg_mggWindow_n50" : "BDT-SMH score",
    "hMVA_value_smh_varset8_mixed04_tmva_bdtg_mggWindow_n50" : "BDT-SMH score",
    "hMVA_value_smh_varset8_mixed05_tmva_bdtg_mggWindow_n50" : "BDT-SMH score",
}

#--------------------------------------------------
# Define
#--------------------------------------------------

hists = hist_mass + hist_var

