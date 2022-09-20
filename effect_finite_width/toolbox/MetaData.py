#!/usr/bin/env python2
#--------------------------------------------------
# variables to set
#--------------------------------------------------
key = ""
directory = ""
fileName1 = ""
fileName2 = ""

var = ""

counter_drawn_histograms = 0

vf, vh = {}, []

mainPad, ratPad = "", ""

#--------------------------------------------------
# constant variables
#--------------------------------------------------
path = "/afs/cern.ch/user/b/beaucero/public/ForYuWei/20220916_3T_2016_Test_FullBRew"

rootfiles = {
    "TprimeTToTH_M-700-10p_vs_NWA" : [
        "Plots_TprimeTToTH_M-700_Width-10p_RH.root",
        "Plots_TprimeTToTH_M-700_LH.root",
    ],

    "TprimeTToTH_M-800-10p_vs_NWA" : [
        "Plots_TprimeTToTH_M-800_Width-10p_RH.root",
        "Plots_TprimeTToTH_M-800_LH.root",
    ],
    "TprimeTToTH_M-800-20p_vs_NWA" : [
        "Plots_TprimeTToTH_M-800_Width-20p_RH.root",
        "Plots_TprimeTToTH_M-800_LH.root",
    ],
    "TprimeTToTH_M-800-30p_vs_NWA" : [
        "Plots_TprimeTToTH_M-800_Width-30p_RH.root",
        "Plots_TprimeTToTH_M-800_LH.root",
    ],

    "TprimeTToTH_M-900-10p_vs_NWA" : [
        "Plots_TprimeTToTH_M-900_Width-10p_RH.root",
        "Plots_TprimeTToTH_M-900_LH.root",
    ],
    "TprimeTToTH_M-1000-10p_vs_NWA" : [
        "Plots_TprimeTToTH_M-1000_Width-10p_RH.root",
        "Plots_TprimeTToTH_M-1000_LH.root",
    ],
    "TprimeTToTH_M-1100-10p_vs_NWA" : [
        "Plots_TprimeTToTH_M-1100_Width-10p_RH.root",
        "Plots_TprimeTToTH_M-1100_LH.root",
    ],
    "TprimeTToTH_M-1200-10p_vs_NWA" : [
        "Plots_TprimeTToTH_M-1200_Width-10p_RH.root",
        "Plots_TprimeTToTH_M-1200_LH.root",
    ],
    "TprimeTToTH_M-1200-20p_vs_NWA" : [
        "Plots_TprimeTToTH_M-1200_Width-20p_RH.root",
        "Plots_TprimeTToTH_M-1200_LH.root",
    ],
    "TprimeTToTH_M-1200-30p_vs_NWA" : [
        "Plots_TprimeTToTH_M-1200_Width-30p_RH.root",
        "Plots_TprimeTToTH_M-1200_LH.root",
    ],
}

rootfiles_all = [
    "Plots_TprimeTToTH_M-1000_LH.root",
    "Plots_TprimeTToTH_M-1000_Width-10p_RH.root",
    "Plots_TprimeTToTH_M-1000_Width-20p_RH.root",
    "Plots_TprimeTToTH_M-1000_Width-30p_RH.root",
    "Plots_TprimeTToTH_M-1100_LH.root",
    "Plots_TprimeTToTH_M-1100_Width-10p_RH.root",
    "Plots_TprimeTToTH_M-1200_LH.root",
    "Plots_TprimeTToTH_M-1200_Width-10p_RH.root",
    "Plots_TprimeTToTH_M-1200_Width-20p_RH.root",
    "Plots_TprimeTToTH_M-1200_Width-30p_RH.root",
    "Plots_TprimeTToTH_M-700_LH.root",
    "Plots_TprimeTToTH_M-700_Width-10p_RH.root",
    "Plots_TprimeTToTH_M-700_Width-20p_RH.root",
    "Plots_TprimeTToTH_M-800_LH.root",
    "Plots_TprimeTToTH_M-800_Width-10p_RH.root",
    "Plots_TprimeTToTH_M-800_Width-20p_RH.root",
    "Plots_TprimeTToTH_M-800_Width-30p_RH.root",
    "Plots_TprimeTToTH_M-900_LH.root",
    "Plots_TprimeTToTH_M-900_Width-10p_RH.root",
]

ref = [
    "HiggsM13"                            , #TH1F 1  Higgs Mass
    "SecondLooseBJetEta13"                , #TH1F 1  Loose B Jet #eta
]

variables = [
    #"TprimeMass13"                        , #TH1F 1  Invariant Mass Higgs+top
    "chi213"                              , #TH1F 1    #Chi^{2}
    "BtagMCId13"                          , #TH1F 1    BtagMCId
    #"Vtx13"                               , #TH1F 1 Vertices
    #"DR6j13"                              , #TH1F 1    #Delta R(T' j^{6th})
    #"HiggsM13"                            , #TH1F 1  Higgs Mass
    "TopM13"                              , #TH1F 1    Top Mass
    #"SumM13"                              , #TH1F 1    #frac{M_{top} - M_{Higgs}}{M_{top} + M_{Higgs}}
    "MET13"                               , #TH1F 1 ME_{T}
    #"Ratio2ndMass13"                      , #TH1F 1    #frac{M_{top} ^{2nd} + M_{W} ^{2nd}}{M_{Higgs}}
    "WmassFromHiggs13"                    , #TH1F 1  M_{W} ^{2nd}
    #"DiffEtaHtop13"                       , #TH1F 1 | #eta(Higgs) - #eta(top) |
    #"Ratio2ndTop13"                       , #TH1F 1 #frac{P_{T}^{2nd top} - P_{T}^{top}}{P_{T}^{2nd top}}
    "HT13"                                , #TH1F 1  H_{T}
    #"HT2p413"                             , #TH1F 1   H_{T}^{2p4}
    "RelHT13"                             , #TH1F 1   Relative H_{T}
    #"NewRelHT13"                          , #TH1F 1    New Relative H_{T}
    "DRbb13"                              , #TH1F 1    #Delta R(b_{Higgs} b_{Higgs})
    #"DRbFHbTop13"                         , #TH1F 1   #Delta R(b_{First_Higgs} b_{Top})
    #"DRbTopbSH13"                         , #TH1F 1   #Delta R(b_{Second_Higgs} b_{Top})
    "DRjj13"                              , #TH1F 1    #Delta R(j_{W} j_{W})
    #"DRHT13"                              , #TH1F 1    DR(Higgs                                           , Top)
    #"RatioPt13"                           , #TH1F 1 TpPt/HPt - TpPt/TopPt
    #"DEtaWH13"                            , #TH1F 1  DEta (W                                              , H)
    #"DPtOverTpPt13"                       , #TH1F 1 Diff Pt (H                                            , Top) /Tp Pt
    #"NbCount13"                           , #TH1F 1 Nb Combinaison
    "FirstHiggsPt13"                      , #TH1F 1    FirstHiggsPt
    "SecondHiggsPt13"                     , #TH1F 1   SecondHiggsPt
    "FirstWPt13"                          , #TH1F 1    FirstWPt
    "SecondWPt13"                         , #TH1F 1   SecondWPt
    "TopJetPt13"                          , #TH1F 1    TopJetPt
    #"Jet6Pt13"                            , #TH1F 1  Jet6Pt
    #"Jet7thPt13"                          , #TH1F 1    Jet7thPt
    #"Jet8thPt13"                          , #TH1F 1    Jet8thPt
    #"Jet9thPt13"                          , #TH1F 1    Jet9thPt
    #"BJet4Pt13"                           , #TH1F 1 BJet4Pt
    "FirstHiggsPtoM513"                   , #TH1F 1 FirstHiggsPt / M5J
    "SecondHiggsPtoM513"                  , #TH1F 1    SecondHiggsPt /M5J
    "FirstWPtoM513"                       , #TH1F 1 FirstWPt /M5J
    "SecondWPtoM513"                      , #TH1F 1    SecondWPt /M5J
    #"Jet6PtoM513"                         , #TH1F 1   Jet6Pt /M5J
    "FirstHiggsEta13"                     , #TH1F 1   FirstHiggs #eta
    "SecondHiggsEta13"                    , #TH1F 1  SecondHiggs #eta
    "FirstWEta13"                         , #TH1F 1   FirstW #eta
    "SecondWEta13"                        , #TH1F 1  SecondW #eta
    #"Jet6Eta13"                           , #TH1F 1 Jet6 #eta
    #"Jet7thEta13"                         , #TH1F 1   Jet7th #eta
    #"Jet8thEta13"                         , #TH1F 1   Jet8th #eta
    #"Jet9thEta13"                         , #TH1F 1   Jet9th #eta
    #"BJet4Eta13"                          , #TH1F 1    BJet4Eta
    "Reconstructed_TprimeEta13"           , #TH1F 1 TPrime #eta
    "Reconstructed_TprimePhi13"           , #TH1F 1 TPrime #phi
    "TopBJetEta13"                        , #TH1F 1  TopBJet #eta
    #"Reconstructed_TprimeP13"             , #TH1F 1   TPrimeP
    "FirstHiggsPhi13"                     , #TH1F 1   FirstHiggs #phi
    "SecondHiggsPhi13"                    , #TH1F 1  SecondHiggs #phi
    "FirstWPhi13"                         , #TH1F 1   FirstW #phi
    "SecondWPhi13"                        , #TH1F 1  SecondW #phi
    "TopBJetPhi13"                        , #TH1F 1  TopBJet #phi
    #"Jet6Phi13"                           , #TH1F 1 Jet6 #phi
    #"NbBTag3L13"                          , #TH1F 1    Nb Loose B-tag
    #"NbBTag3M13"                          , #TH1F 1    Nb Medium B-tag
    #"NbBTag3T13"                          , #TH1F 1    Nb Tight B-tag
    "DR(BTopJet,W)13"                     , #TH1F 1   DR(BTopJet,W)
    #"ProductDR13"                         , #TH1F 1   DRxDR
    #"Higgschi213"                         , #TH1F 1   Higgs #Chi^{2}
    "Topchi213"                           , #TH1F 1 Top #Chi^{2}
    #"Wchi213"                             , #TH1F 1   W #Chi^{2}
    #"2ndTopMass13"                        , #TH1F 1  2nd Top Mass
    #"MaxChi213"                           , #TH1F 1 Max Chi2
    #"MaxDR13"                             , #TH1F 1   Max DR
    #"Chi2PlusDR13"                        , #TH1F 1  Chi2 + DR
    "NbGoodJets13"                        , #TH1F 1  Nb Good Jets
    #"MHt_5j13"                            , #TH1F 1  MHt 5J
    #"MHt_6j13"                            , #TH1F 1  MHt 6J
    #"WHMass13"                            , #TH1F 1  Invariant Mass W+Higgs
    #"Mass6J13"                            , #TH1F 1  Invariant Mass 6 Jets
    #"Mass6th7thJ13"                       , #TH1F 1 Invariant Mass of 6th+7th
    #"Mass6th7th8thJ13"                    , #TH1F 1  Invariant Mass of 6th+7th+8th
    #"Mass6th7th8th9thJ13"                 , #TH1F 1   Invariant Mass of 6th+7th+8th+9th
    #"Mass6th8thJ13"                       , #TH1F 1 Invariant Mass of 6th+8th
    #"Mass6th8th9thJ13"                    , #TH1F 1  Invariant Mass of 6th+8th+9th
    #"Mass6th9thJ13"                       , #TH1F 1 Invariant Mass of 6th+9th
    #"Mass7th8thJ13"                       , #TH1F 1 Invariant Mass of 7th+8th
    #"Mass7th8th9thJ13"                    , #TH1F 1  Invariant Mass of 7th+8th+9th
    #"Mass7th9thJ13"                       , #TH1F 1 Invariant Mass of 7th+9th
    #"Mass8th9thJ13"                       , #TH1F 1 Invariant Mass of 8th+9th
    #"Mass4thB6thJ13"                      , #TH1F 1    Invariant Mass of 4thB+6th
    #"Mass4thB7thJ13"                      , #TH1F 1    Invariant Mass of 4thB+7th
    #"Mass4thB8thJ13"                      , #TH1F 1    Invariant Mass of 4thB+8th
    #"Mass4thB9thJ13"                      , #TH1F 1    Invariant Mass of 4thB+9th
    #"Mass4thB6th7thJ13"                   , #TH1F 1 Invariant Mass of 4thB+6th+7th
    #"Mass4thB6th8thJ13"                   , #TH1F 1 Invariant Mass of 4thB+6th+8th
    #"Mass4thB6th9thJ13"                   , #TH1F 1 Invariant Mass of 4thB+6th+9th
    #"Mass4thB7th8thJ13"                   , #TH1F 1 Invariant Mass of 4thB+7th+8th
    #"Mass4thB7th9thJ13"                   , #TH1F 1 Invariant Mass of 4thB+7th+9th
    #"Mass4thB8th9thJ13"                   , #TH1F 1 Invariant Mass of 4thB+8th+9th
    #"DR(Tprime,7th)13"                    , #TH1F 1  DR(Tprime,7th)
    #"DR(Tprime,8th)13"                    , #TH1F 1  DR(Tprime,8th)
    #"DR(Tprime,9th)13"                    , #TH1F 1  DR(Tprime,9th)
    #"MassT4thB13"                         , #TH1F 1   Invariant Mass Tprime+4th B Jets
    #"3JetMassCloseTopMass13"              , #TH1F 1    3JetMass Invariant Mass at TopMass
    #"3JetMassCloseTopMass_Jet1Jet2_13"    , #TH1F 1  3JetMass Invariant Mass at TopMassJet1Jet2
    #"3JetMassCloseTopMass_Jet1Jet3_13"    , #TH1F 1  3JetMass Invariant Mass at TopMassJet1Jet3
    #"3JetMassCloseTopMass_Jet2Jet3_13"    , #TH1F 1  3JetMass Invariant Mass at TopMassJet1Jet3
    #"3JetMassClose68013"                  , #TH1F 1    3JetMass Invariant Mass at 680
    #"3JetMassClose680_Jet1Jet2_13"        , #TH1F 1  3JetMass Invariant Mass at 680Jet1Jet2
    #"3JetMassClose680_Jet1Jet3_13"        , #TH1F 1  3JetMass Invariant Mass at 680Jet1Jet3
    #"3JetMassClose680_Jet2Jet3_13"        , #TH1F 1  3JetMass Invariant Mass at 680Jet2Jet3
    #"3JetMassBIncludedClose68013"         , #TH1F 1   3JetMassBIncluded Invariant Mass at 680
    #"3JetMassClose680_Jet1Jet2NonB_13"    , #TH1F 1  3JetMass Invariant Mass at 680Jet1Jet2NonB
    #"TotalInvMass8Jets_13"                , #TH1F 1  Invariant Mass Tprime+3jets at 680
    #"TotalInvMass8JetsWith4thB_13"        , #TH1F 1  Invariant Mass Tprime+3jetsWith4thB at 680
    #"2JetMassClose240_Jet1Jet2_13"        , #TH1F 1  2JetMass Invariant Mass at 240Jet1Jet2
    #"3JetMassFrom24013"                   , #TH1F 1 3JetMass Invariant Mass
    #"2JetMassClose240_Jet1Jet2NonB_13"    , #TH1F 1  2JetMass Invariant Mass at 240Jet1Jet2NonB
    #"3JetMassBIncludedFrom24013"          , #TH1F 1    3JetMassBIncluded Invariant Mass
    #"TotalInvMass8JetsFrom240_13"         , #TH1F 1   Invariant Mass Tprime+3jets from 240
    #"TotalInvMass8JetsWith4thBFrom240_13" , #TH1F 1   Invariant Mass Tprime+3jetsWith4thB from 240
    "WM13"                                , #TH1F 1  W Mass
    "Jet1Pt13"                            , #TH1F 1  Pt Jet 1
    "Jet2Pt13"                            , #TH1F 1  Pt Jet 2
    "Jet3Pt13"                            , #TH1F 1  Pt Jet 3
    "Jet4Pt13"                            , #TH1F 1  Pt Jet 4
    "Jet5Pt13"                            , #TH1F 1  Pt Jet 5
    #"Jet6thPt13"                          , #TH1F 1    Pt Jet 6
    "Jet1Eta13"                           , #TH1F 1  #eta Jet 1
    "Jet2Eta13"                           , #TH1F 1  #eta Jet 2
    "Jet3Eta13"                           , #TH1F 1  #eta Jet 3
    "Jet4Eta13"                           , #TH1F 1  #eta Jet 4
    "Jet5Eta13"                           , #TH1F 1  #eta Jet 5
    #"Jet6thEta13"                         , #TH1F 1    #eta Jet 6
    "CSVBJet113"                          , #TH1F 1    CSVBJet1
    "CSVBJet213"                          , #TH1F 1    CSVBJet2
    "CSVBJet313"                          , #TH1F 1    CSVBJet3
    "CSVBJet413"                          , #TH1F 1    CSVBJet4
    #"CSVBSum13"                           , #TH1F 1 CSVBSum
    #"MinCSVB13"                           , #TH1F 1 MinCSVB
    #"DPhiHT13"                            , #TH1F 1  D#phi(Higgs                                          , Top)
    #"Jet7Pt13"                            , #TH1F 1  Pt Jet 7
    #"Jet8Pt13"                            , #TH1F 1  Pt Jet 8
    #"Jet9Pt13"                            , #TH1F 1  Pt Jet 9
    #"Jet10Pt13"                           , #TH1F 1 Pt Jet 10
    #"RatioM4JM6J13"                       , #TH1F 1 M(W+H)/M(Top+H+6thJet)
    #"FirstLooseBJetEta13"                 , #TH1F 1   Loose B Jet #eta
    #"SecondLooseBJetEta13"                , #TH1F 1  Loose B Jet #eta
    #"ThirdLooseBJetEta13"                 , #TH1F 1   Loose B Jet #eta
    #"FirstMediumBJetEta13"                , #TH1F 1  Medium B Jet #eta
    #"SecondMediumBJetEta13"               , #TH1F 1 Medium B Jet #eta
    #"ThirdMediumBJetEta13"                , #TH1F 1  Medium B Jet #eta
    "FirstTightBJetEta13"                 , #TH1F 1   Tight B Jet #eta
    "SecondTightBJetEta13"                , #TH1F 1  Tight B Jet #eta
    "ThirdTightBJetEta13"                 , #TH1F 1   Tight B Jet #eta
#    "FirstLooseBJetPhi13"                 , #TH1F 1   Loose B Jet Phi
#    "SecondLooseBJetPhi13"                , #TH1F 1  Loose B Jet Phi
#    "ThirdLooseBJetPhi13"                 , #TH1F 1   Loose B Jet Phi
#    "FirstMediumBJetPhi13"                , #TH1F 1  Medium B Jet Phi
#    "SecondMediumBJetPhi13"               , #TH1F 1 Medium B Jet Phi
#    "ThirdMediumBJetPhi13"                , #TH1F 1  Medium B Jet Phi
    "FirstTightBJetPhi13"                 , #TH1F 1   Tight B Jet Phi
    "SecondTightBJetPhi13"                , #TH1F 1  Tight B Jet Phi
    "ThirdTightBJetPhi13"                 , #TH1F 1   Tight B Jet Phi
#    "FirstLooseBJetP13"                   , #TH1F 1 Loose B Jet P
#    "SecondLooseBJetP13"                  , #TH1F 1    Loose B Jet P
#    "ThirdLooseBJetP13"                   , #TH1F 1 Loose B Jet P
#    "FirstMediumBJetP13"                  , #TH1F 1    Medium B Jet P
#    "SecondMediumBJetP13"                 , #TH1F 1   Medium B Jet P
#    "ThirdMediumBJetP13"                  , #TH1F 1    Medium B Jet P
    "FirstTightBJetP13"                   , #TH1F 1 Tight B Jet P
    "SecondTightBJetP13"                  , #TH1F 1    Tight B Jet P
    "ThirdTightBJetP13"                   , #TH1F 1 Tight B Jet P
    #"MCTruthMatchedWM13"                  , #TH1F 1    W Mass
    #"MCTruthMatchedHiggsM13"              , #TH1F 1    Higgs Mass
    #"MCTruthMatchedTopM13"                , #TH1F 1  Top Mass
    #"MCTruthMatchedTprimeMass13"          , #TH1F 1    Invariant Mass Higgs+top
    #"MCTruthBtagFlavor13"                 , #TH1F 1   Flavor of B-tag jets
    #"MCTruthBtagGenPartons13"             , #TH1F 1   Gen Partons of B-tag jets
    #"BTagMass13"                          , #TH1F 1    Mass of B-tag jets
    #"WjetMass13"                          , #TH1F 1    Mass of W-jets
    #"ForwardJetEta13"                     , #TH1F 1   Forward Jet #eta
    #"ForwardJetPt13"                      , #TH1F 1    Forward Jet p_{T}
    #"TprimeMass13SigPl"                   , #TH1F 1 Invariant Mass Higgs+top (SigmaPlus)
    #"TprimeMass13SigMo"                   , #TH1F 1 Invariant Mass Higgs+top(SigmaMinus)
    #"TprimeMass13NoWeight"                , #TH1F 1  Invariant Mass Higgs+top (NoWeight)
    #"TprimeMass13L1Prefiring"             , #TH1F 1   Invariant Mass Higgs+top (NoWeight)
    #"HT2p4_3p013"                         , #TH1F 1   H_{T}^{2p4}_{3p0}
    #"HT2p4_3p013WithL1PreFiring"          , #TH1F 1    H_{T}^{2p4}_{3p0}
    #"RunPeriod13"                         , #TH1F 1   Run Period
    #"RunNumber13"                         , #TH1F 1   Run Number
    #"TriggerBits13"                       , #TH1F 1 Trigger Bits
    "TopBPhi13"                           , #TH1F 1 TopB #phi
    #"DiffHT_HT2p413"                      , #TH1F 1    (H_{T} - H_{T}^{2p4})/H_{T}
    #"DiffHT_HT2p4_3p013"                  , #TH1F 1    (H_{T} - H_{T}^{2p4-3p0})/H_{T}
    "TopPt13"                             , #TH1F 1   Top p_{T}
    "HiggsPt13"                           , #TH1F 1 Higgs p_{T}
    "TopEta13"                            , #TH1F 1  Top #eta
    "HiggsEta13"                          , #TH1F 1    Higgs #eta
    "TopPhi13"                            , #TH1F 1  Top #phi
    "HiggsPhi13"                          , #TH1F 1    Higgs #phi
    #"BTagLoosePhi13"                      , #TH1F 1    Loose BTag #phi
    #"BTagMediumPhi13"                     , #TH1F 1   Medium BTag #phi
    #"BTagTightPhi13"                      , #TH1F 1    Tight BTag #phi
    #"BTagExtraLooseEta13"                 , #TH1F 1   Extra Loose BTag #eta
    #"BTagLooseEta13"                      , #TH1F 1    Loose BTag #eta
    #"BTagMediumEta13"                     , #TH1F 1   Medium BTag #eta
    #"BTagTightEta13"                      , #TH1F 1    Tight BTag #eta
    #"BTagExtraLooseMomentum13"            , #TH1F 1  Extra Loose BTag Momentum
    #"BTagLooseMomentum13"                 , #TH1F 1   Loose BTag Momentum
    #"BTagMediumMomentum13"                , #TH1F 1  Medium BTag Momentum
    #"BTagTightMomentum13"                 , #TH1F 1   Tight BTag Momentum
    #"BTagExtraLoosePt13"                  , #TH1F 1    Extra Loose BTag Pt
    #"BTagLoosePt13"                       , #TH1F 1 Loose BTag Pt
    #"BTagMediumPt13"                      , #TH1F 1    Medium BTag Pt
    #"BTagTightPt13"                       , #TH1F 1 Tight BTag Pt
]

raw = [ #{{{
    "WeightsAs3T13"                       , #TH2F 1 WeightsAs3T
    "TprimeMass13"                        , #TH1F 1  Invariant Mass Higgs+top
    "chi213"                              , #TH1F 1    #Chi^{2}
    "BtagMCId13"                          , #TH1F 1    BtagMCId
    "Vtx13"                               , #TH1F 1 Vertices
    "DR6j13"                              , #TH1F 1    #Delta R(T' j^{6th})
    "HiggsM13"                            , #TH1F 1  Higgs Mass
    "TopM13"                              , #TH1F 1    Top Mass
    "SumM13"                              , #TH1F 1    #frac{M_{top} - M_{Higgs}}{M_{top} + M_{Higgs}}
    "MET13"                               , #TH1F 1 ME_{T}
    "Ratio2ndMass13"                      , #TH1F 1    #frac{M_{top} ^{2nd} + M_{W} ^{2nd}}{M_{Higgs}}
    "WmassFromHiggs13"                    , #TH1F 1  M_{W} ^{2nd}
    "DiffEtaHtop13"                       , #TH1F 1 | #eta(Higgs) - #eta(top) |
    "Ratio2ndTop13"                       , #TH1F 1 #frac{P_{T}^{2nd top} - P_{T}^{top}}{P_{T}^{2nd top}}
    "HT13"                                , #TH1F 1  H_{T}
    "HT2p413"                             , #TH1F 1   H_{T}^{2p4}
    "RelHT13"                             , #TH1F 1   Relative H_{T}
    "NewRelHT13"                          , #TH1F 1    New Relative H_{T}
    "DRbb13"                              , #TH1F 1    #Delta R(b_{Higgs} b_{Higgs})
    "DRbFHbTop13"                         , #TH1F 1   #Delta R(b_{First_Higgs} b_{Top})
    "DRbTopbSH13"                         , #TH1F 1   #Delta R(b_{Second_Higgs} b_{Top})
    "DRjj13"                              , #TH1F 1    #Delta R(j_{W} j_{W})
    "DRHT13"                              , #TH1F 1    DR(Higgs                                           , Top)
    "RatioPt13"                           , #TH1F 1 TpPt/HPt - TpPt/TopPt
    "DEtaWH13"                            , #TH1F 1  DEta (W                                              , H)
    "DPtOverTpPt13"                       , #TH1F 1 Diff Pt (H                                            , Top) /Tp Pt
    "NbCount13"                           , #TH1F 1 Nb Combinaison
    "FirstHiggsPt13"                      , #TH1F 1    FirstHiggsPt
    "SecondHiggsPt13"                     , #TH1F 1   SecondHiggsPt
    "FirstWPt13"                          , #TH1F 1    FirstWPt
    "SecondWPt13"                         , #TH1F 1   SecondWPt
    "TopJetPt13"                          , #TH1F 1    TopJetPt
    "Jet6Pt13"                            , #TH1F 1  Jet6Pt
    "Jet7thPt13"                          , #TH1F 1    Jet7thPt
    "Jet8thPt13"                          , #TH1F 1    Jet8thPt
    "Jet9thPt13"                          , #TH1F 1    Jet9thPt
    "BJet4Pt13"                           , #TH1F 1 BJet4Pt
    "FirstHiggsPtoM513"                   , #TH1F 1 FirstHiggsPt / M5J
    "SecondHiggsPtoM513"                  , #TH1F 1    SecondHiggsPt /M5J
    "FirstWPtoM513"                       , #TH1F 1 FirstWPt /M5J
    "SecondWPtoM513"                      , #TH1F 1    SecondWPt /M5J
    "Jet6PtoM513"                         , #TH1F 1   Jet6Pt /M5J
    "FirstHiggsEta13"                     , #TH1F 1   FirstHiggs #eta
    "SecondHiggsEta13"                    , #TH1F 1  SecondHiggs #eta
    "FirstWEta13"                         , #TH1F 1   FirstW #eta
    "SecondWEta13"                        , #TH1F 1  SecondW #eta
    "Jet6Eta13"                           , #TH1F 1 Jet6 #eta
    "Jet7thEta13"                         , #TH1F 1   Jet7th #eta
    "Jet8thEta13"                         , #TH1F 1   Jet8th #eta
    "Jet9thEta13"                         , #TH1F 1   Jet9th #eta
    "BJet4Eta13"                          , #TH1F 1    BJet4Eta
    "Reconstructed_TprimeEta13"           , #TH1F 1 TPrime #eta
    "Reconstructed_TprimePhi13"           , #TH1F 1 TPrime #phi
    "TopBJetEta13"                        , #TH1F 1  TopBJet #eta
    "Reconstructed_TprimeP13"             , #TH1F 1   TPrimeP
    "FirstHiggsPhi13"                     , #TH1F 1   FirstHiggs #phi
    "SecondHiggsPhi13"                    , #TH1F 1  SecondHiggs #phi
    "FirstWPhi13"                         , #TH1F 1   FirstW #phi
    "SecondWPhi13"                        , #TH1F 1  SecondW #phi
    "TopBJetPhi13"                        , #TH1F 1  TopBJet #phi
    "Jet6Phi13"                           , #TH1F 1 Jet6 #phi
    "NbBTag3L13"                          , #TH1F 1    Nb Loose B-tag
    "NbBTag3M13"                          , #TH1F 1    Nb Medium B-tag
    "NbBTag3T13"                          , #TH1F 1    Nb Tight B-tag
    "DR(BTopJet,W)13"                     , #TH1F 1   DR(BTopJet,W)
    "ProductDR13"                         , #TH1F 1   DRxDR
    "Higgschi213"                         , #TH1F 1   Higgs #Chi^{2}
    "Topchi213"                           , #TH1F 1 Top #Chi^{2}
    "Wchi213"                             , #TH1F 1   W #Chi^{2}
    "2ndTopMass13"                        , #TH1F 1  2nd Top Mass
    "MaxChi213"                           , #TH1F 1 Max Chi2
    "MaxDR13"                             , #TH1F 1   Max DR
    "Chi2PlusDR13"                        , #TH1F 1  Chi2 + DR
    "NbGoodJets13"                        , #TH1F 1  Nb Good Jets
    "MHt_5j13"                            , #TH1F 1  MHt 5J
    "MHt_6j13"                            , #TH1F 1  MHt 6J
    "WHMass13"                            , #TH1F 1  Invariant Mass W+Higgs
    "Mass6J13"                            , #TH1F 1  Invariant Mass 6 Jets
    "Mass6th7thJ13"                       , #TH1F 1 Invariant Mass of 6th+7th
    "Mass6th7th8thJ13"                    , #TH1F 1  Invariant Mass of 6th+7th+8th
    "Mass6th7th8th9thJ13"                 , #TH1F 1   Invariant Mass of 6th+7th+8th+9th
    "Mass6th8thJ13"                       , #TH1F 1 Invariant Mass of 6th+8th
    "Mass6th8th9thJ13"                    , #TH1F 1  Invariant Mass of 6th+8th+9th
    "Mass6th9thJ13"                       , #TH1F 1 Invariant Mass of 6th+9th
    "Mass7th8thJ13"                       , #TH1F 1 Invariant Mass of 7th+8th
    "Mass7th8th9thJ13"                    , #TH1F 1  Invariant Mass of 7th+8th+9th
    "Mass7th9thJ13"                       , #TH1F 1 Invariant Mass of 7th+9th
    "Mass8th9thJ13"                       , #TH1F 1 Invariant Mass of 8th+9th
    "Mass4thB6thJ13"                      , #TH1F 1    Invariant Mass of 4thB+6th
    "Mass4thB7thJ13"                      , #TH1F 1    Invariant Mass of 4thB+7th
    "Mass4thB8thJ13"                      , #TH1F 1    Invariant Mass of 4thB+8th
    "Mass4thB9thJ13"                      , #TH1F 1    Invariant Mass of 4thB+9th
    "Mass4thB6th7thJ13"                   , #TH1F 1 Invariant Mass of 4thB+6th+7th
    "Mass4thB6th8thJ13"                   , #TH1F 1 Invariant Mass of 4thB+6th+8th
    "Mass4thB6th9thJ13"                   , #TH1F 1 Invariant Mass of 4thB+6th+9th
    "Mass4thB7th8thJ13"                   , #TH1F 1 Invariant Mass of 4thB+7th+8th
    "Mass4thB7th9thJ13"                   , #TH1F 1 Invariant Mass of 4thB+7th+9th
    "Mass4thB8th9thJ13"                   , #TH1F 1 Invariant Mass of 4thB+8th+9th
    "DR(Tprime,7th)13"                    , #TH1F 1  DR(Tprime,7th)
    "DR(Tprime,8th)13"                    , #TH1F 1  DR(Tprime,8th)
    "DR(Tprime,9th)13"                    , #TH1F 1  DR(Tprime,9th)
    "MassT4thB13"                         , #TH1F 1   Invariant Mass Tprime+4th B Jets
    "3JetMassCloseTopMass13"              , #TH1F 1    3JetMass Invariant Mass at TopMass
    "3JetMassCloseTopMass_Jet1Jet2_13"    , #TH1F 1  3JetMass Invariant Mass at TopMassJet1Jet2
    "3JetMassCloseTopMass_Jet1Jet3_13"    , #TH1F 1  3JetMass Invariant Mass at TopMassJet1Jet3
    "3JetMassCloseTopMass_Jet2Jet3_13"    , #TH1F 1  3JetMass Invariant Mass at TopMassJet1Jet3
    "3JetMassClose68013"                  , #TH1F 1    3JetMass Invariant Mass at 680
    "3JetMassClose680_Jet1Jet2_13"        , #TH1F 1  3JetMass Invariant Mass at 680Jet1Jet2
    "3JetMassClose680_Jet1Jet3_13"        , #TH1F 1  3JetMass Invariant Mass at 680Jet1Jet3
    "3JetMassClose680_Jet2Jet3_13"        , #TH1F 1  3JetMass Invariant Mass at 680Jet2Jet3
    "3JetMassBIncludedClose68013"         , #TH1F 1   3JetMassBIncluded Invariant Mass at 680
    "3JetMassClose680_Jet1Jet2NonB_13"    , #TH1F 1  3JetMass Invariant Mass at 680Jet1Jet2NonB
    "TotalInvMass8Jets_13"                , #TH1F 1  Invariant Mass Tprime+3jets at 680
    "TotalInvMass8JetsWith4thB_13"        , #TH1F 1  Invariant Mass Tprime+3jetsWith4thB at 680
    "2JetMassClose240_Jet1Jet2_13"        , #TH1F 1  2JetMass Invariant Mass at 240Jet1Jet2
    "3JetMassFrom24013"                   , #TH1F 1 3JetMass Invariant Mass
    "2JetMassClose240_Jet1Jet2NonB_13"    , #TH1F 1  2JetMass Invariant Mass at 240Jet1Jet2NonB
    "3JetMassBIncludedFrom24013"          , #TH1F 1    3JetMassBIncluded Invariant Mass
    "TotalInvMass8JetsFrom240_13"         , #TH1F 1   Invariant Mass Tprime+3jets from 240
    "TotalInvMass8JetsWith4thBFrom240_13" , #TH1F 1   Invariant Mass Tprime+3jetsWith4thB from 240
    "WM13"                                , #TH1F 1  W Mass
    "Jet1Pt13"                            , #TH1F 1  Pt Jet 1
    "Jet2Pt13"                            , #TH1F 1  Pt Jet 2
    "Jet3Pt13"                            , #TH1F 1  Pt Jet 3
    "Jet4Pt13"                            , #TH1F 1  Pt Jet 4
    "Jet5Pt13"                            , #TH1F 1  Pt Jet 5
    "Jet6thPt13"                          , #TH1F 1    Pt Jet 6
    "Jet1Eta13"                           , #TH1F 1  #eta Jet 1
    "Jet2Eta13"                           , #TH1F 1  #eta Jet 2
    "Jet3Eta13"                           , #TH1F 1  #eta Jet 3
    "Jet4Eta13"                           , #TH1F 1  #eta Jet 4
    "Jet5Eta13"                           , #TH1F 1  #eta Jet 5
    "Jet6thEta13"                         , #TH1F 1    #eta Jet 6
    "CSVBJet113"                          , #TH1F 1    CSVBJet1
    "CSVBJet213"                          , #TH1F 1    CSVBJet2
    "CSVBJet313"                          , #TH1F 1    CSVBJet3
    "CSVBJet413"                          , #TH1F 1    CSVBJet4
    "CSVBSum13"                           , #TH1F 1 CSVBSum
    "MinCSVB13"                           , #TH1F 1 MinCSVB
    "DPhiHT13"                            , #TH1F 1  D#phi(Higgs                                          , Top)
    "Jet7Pt13"                            , #TH1F 1  Pt Jet 7
    "Jet8Pt13"                            , #TH1F 1  Pt Jet 8
    "Jet9Pt13"                            , #TH1F 1  Pt Jet 9
    "Jet10Pt13"                           , #TH1F 1 Pt Jet 10
    "RatioM4JM6J13"                       , #TH1F 1 M(W+H)/M(Top+H+6thJet)
    "FirstLooseBJetEta13"                 , #TH1F 1   Loose B Jet #eta
    "SecondLooseBJetEta13"                , #TH1F 1  Loose B Jet #eta
    "ThirdLooseBJetEta13"                 , #TH1F 1   Loose B Jet #eta
    "FirstMediumBJetEta13"                , #TH1F 1  Medium B Jet #eta
    "SecondMediumBJetEta13"               , #TH1F 1 Medium B Jet #eta
    "ThirdMediumBJetEta13"                , #TH1F 1  Medium B Jet #eta
    "FirstTightBJetEta13"                 , #TH1F 1   Tight B Jet #eta
    "SecondTightBJetEta13"                , #TH1F 1  Tight B Jet #eta
    "ThirdTightBJetEta13"                 , #TH1F 1   Tight B Jet #eta
    "FirstLooseBJetPhi13"                 , #TH1F 1   Loose B Jet Phi
    "SecondLooseBJetPhi13"                , #TH1F 1  Loose B Jet Phi
    "ThirdLooseBJetPhi13"                 , #TH1F 1   Loose B Jet Phi
    "FirstMediumBJetPhi13"                , #TH1F 1  Medium B Jet Phi
    "SecondMediumBJetPhi13"               , #TH1F 1 Medium B Jet Phi
    "ThirdMediumBJetPhi13"                , #TH1F 1  Medium B Jet Phi
    "FirstTightBJetPhi13"                 , #TH1F 1   Tight B Jet Phi
    "SecondTightBJetPhi13"                , #TH1F 1  Tight B Jet Phi
    "ThirdTightBJetPhi13"                 , #TH1F 1   Tight B Jet Phi
    "FirstLooseBJetP13"                   , #TH1F 1 Loose B Jet P
    "SecondLooseBJetP13"                  , #TH1F 1    Loose B Jet P
    "ThirdLooseBJetP13"                   , #TH1F 1 Loose B Jet P
    "FirstMediumBJetP13"                  , #TH1F 1    Medium B Jet P
    "SecondMediumBJetP13"                 , #TH1F 1   Medium B Jet P
    "ThirdMediumBJetP13"                  , #TH1F 1    Medium B Jet P
    "FirstTightBJetP13"                   , #TH1F 1 Tight B Jet P
    "SecondTightBJetP13"                  , #TH1F 1    Tight B Jet P
    "ThirdTightBJetP13"                   , #TH1F 1 Tight B Jet P
    "MCTruthMatchedWM13"                  , #TH1F 1    W Mass
    "MCTruthMatchedHiggsM13"              , #TH1F 1    Higgs Mass
    "MCTruthMatchedTopM13"                , #TH1F 1  Top Mass
    "MCTruthMatchedTprimeMass13"          , #TH1F 1    Invariant Mass Higgs+top
    "MCTruthBtagFlavor13"                 , #TH1F 1   Flavor of B-tag jets
    "MCTruthBtagGenPartons13"             , #TH1F 1   Gen Partons of B-tag jets
    "BTagMass13"                          , #TH1F 1    Mass of B-tag jets
    "WjetMass13"                          , #TH1F 1    Mass of W-jets
    "ForwardJetEta13"                     , #TH1F 1   Forward Jet #eta
    "ForwardJetPt13"                      , #TH1F 1    Forward Jet p_{T}
    "TprimeMass13SigPl"                   , #TH1F 1 Invariant Mass Higgs+top (SigmaPlus)
    "TprimeMass13SigMo"                   , #TH1F 1 Invariant Mass Higgs+top(SigmaMinus)
    "TprimeMass13NoWeight"                , #TH1F 1  Invariant Mass Higgs+top (NoWeight)
    "TprimeMass13L1Prefiring"             , #TH1F 1   Invariant Mass Higgs+top (NoWeight)
    "HT2p4_3p013"                         , #TH1F 1   H_{T}^{2p4}_{3p0}
    "HT2p4_3p013WithL1PreFiring"          , #TH1F 1    H_{T}^{2p4}_{3p0}
    "RunPeriod13"                         , #TH1F 1   Run Period
    "RunNumber13"                         , #TH1F 1   Run Number
    "TriggerBits13"                       , #TH1F 1 Trigger Bits
    "TopBPhi13"                           , #TH1F 1 TopB #phi
    "DiffHT_HT2p413"                      , #TH1F 1    (H_{T} - H_{T}^{2p4})/H_{T}
    "DiffHT_HT2p4_3p013"                  , #TH1F 1    (H_{T} - H_{T}^{2p4-3p0})/H_{T}
    "TopPt13"                             , #TH1F 1   Top p_{T}
    "HiggsPt13"                           , #TH1F 1 Higgs p_{T}
    "TopEta13"                            , #TH1F 1  Top #eta
    "HiggsEta13"                          , #TH1F 1    Higgs #eta
    "TopPhi13"                            , #TH1F 1  Top #phi
    "HiggsPhi13"                          , #TH1F 1    Higgs #phi
    "BTagLoosePhi13"                      , #TH1F 1    Loose BTag #phi
    "BTagMediumPhi13"                     , #TH1F 1   Medium BTag #phi
    "BTagTightPhi13"                      , #TH1F 1    Tight BTag #phi
    "BTagExtraLooseEta13"                 , #TH1F 1   Extra Loose BTag #eta
    "BTagLooseEta13"                      , #TH1F 1    Loose BTag #eta
    "BTagMediumEta13"                     , #TH1F 1   Medium BTag #eta
    "BTagTightEta13"                      , #TH1F 1    Tight BTag #eta
    "BTagExtraLooseMomentum13"            , #TH1F 1  Extra Loose BTag Momentum
    "BTagLooseMomentum13"                 , #TH1F 1   Loose BTag Momentum
    "BTagMediumMomentum13"                , #TH1F 1  Medium BTag Momentum
    "BTagTightMomentum13"                 , #TH1F 1   Tight BTag Momentum
    "BTagExtraLoosePt13"                  , #TH1F 1    Extra Loose BTag Pt
    "BTagLoosePt13"                       , #TH1F 1 Loose BTag Pt
    "BTagMediumPt13"                      , #TH1F 1    Medium BTag Pt
    "BTagTightPt13"                       , #TH1F 1 Tight BTag Pt
    "BTagMapEtaPhiExtraLoose13"           , #TH2F 1
    "BTagMapEtaPhiLoose13"                , #TH2F 1
    "BTagMapEtaPhiMedium13"               , #TH2F 1
    "BTagMapEtaPhiTight13"                , #TH2F 1
    "PtTprimePtBprime13"                  , #TH2F 1
    "chi2vsDRtH13"                        , #TH2F 1
    "chi2o10vsDRtHo1p513"                 , #TH2F 1
    "chi2vsProductDR13"                   , #TH2F 1
    "RelHtvs2ndMass13"                    , #TH2F 1
    "RelHtvsM5J13"                        , #TH2F 1
    "RelHtvsSumBtag13"                    , #TH2F 1
    "NewRelHtvs2ndMass13"                 , #TH2F 1
    "RelHtCubvs2ndMass13"                 , #TH2F 1
    "NewRelHtCubvs2ndMass13"              , #TH2F 1
    "EtaPhiJets13"                        , #TH2F 1
    "EtaPhiJetsB13"                       , #TH2F 1
    "EtaPhiJetsLight13"                   , #TH2F 1
    "chi2vsHiggsChi213"                   , #TH2F 1
    "chi2vsTopChi213"                     , #TH2F 1
    "chi2vsWChi213"                       , #TH2F 1
    "TopChi2vsWChi213"                    , #TH2F 1
    "HiggsChi2vsWChi213"                  , #TH2F 1
    "HiggsChi2vsTopChi213"                , #TH2F 1
    "DRTHvsHiggsChi213"                   , #TH2F 1
    "DRTHvsTopChi213"                     , #TH2F 1
    "DRTHvsWChi213"                       , #TH2F 1
    "ProductDRvsHiggsChi213"              , #TH2F 1
    "ProductDRvsTopChi213"                , #TH2F 1
    "ProductDRvsWChi213"                  , #TH2F 1
    "MaxDRvsMaxChi213"                    , #TH2F 1
    "DRbbvsHiggsChi213"                   , #TH2F 1
    "DRBWvsTopChi213"                     , #TH2F 1
    "DRWjjvsWChi213"                      , #TH2F 1
    "DRTPrimevsChi213"                    , #TH2F 1
    "2ndRatioMassvsBTagSum13"             , #TH2F 1
    "2ndRatioMassvsM5J13"                 , #TH2F 1
    "2ndTopMassvsM5J13"                   , #TH2F 1
    "TopMassvsHiggsMass13"                , #TH2F 1
    "M5JvsHiggsMass13"                    , #TH2F 1
    "M5JvsChi213"                         , #TH2F 1
    "M5JvsDRTopHiggs13"                   , #TH2F 1
    "M5JvsNbJets13"                       , #TH2F 1
    "M5JvsBTagSum13"                      , #TH2F 1
    "HTvsHT_2p413"                        , #TH2F 1
    "2ndTopMassvsJetInd13"                , #TH2F 1o
] #}}}
