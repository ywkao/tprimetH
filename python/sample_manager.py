#!/usr/bin/env python2
import glob

version = "v3"
subversion = 6 # for signal
signals = [
    "TprimeBToTH_M-600_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1000_Era2017_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1000_Era2018_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2018_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2018_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-600_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1100_Era2017_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2017_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-625_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1000_Era2016_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2016_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2016_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-600_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2016_v3p%s.root"   %  str(subversion)
]
 
signals_2016 = [
    "TprimeBToTH_M-600_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2016_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1000_Era2016_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2016_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2016_v3p%s.root"  %  str(subversion)
]

signals_2017 = [
    "TprimeBToTH_M-600_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2017_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1000_Era2017_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2017_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2017_v3p%s.root"  %  str(subversion)
]

signals_2018 = [
    "TprimeBToTH_M-600_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2018_v3p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1000_Era2018_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2018_v3p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2018_v3p%s.root"  %  str(subversion)
]

samples_2016 = [
    "DiPhotonJetsBox_M40_80-Sherpa_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "VBFHToGG_M125_13TeV_amcatnlo_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WW_TuneCUETP8M1_13TeV-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WZ_TuneCUETP8M1_13TeV-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WminusH_HToGG_WToAll_M120_13TeV_powheg_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WminusH_HToGG_WToAll_M125_13TeV_powheg_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WminusH_HToGG_WToAll_M130_13TeV_powheg_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "WplusH_HToGG_WToAll_M130_13TeV_powheg_pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3",
    "ZZ_TuneCUETP8M1_13TeV-pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3"
]

samples_2017 = [
    "DiPhotonJetsBox1BJet_MGG-80toInf_13TeV-Sherpa_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v1-RunIIFall17MiniAODv2",
    "DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "DiPhotonJetsBox_M40_80-Sherpa_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "THW_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_TuneCP5_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "VBFHToGG_M-125_13TeV_powheg_pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "VBFHToGG_M125_13TeV_amcatnlo_pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "WW_TuneCP5_13TeV-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "WZ_TuneCP5_13TeV-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "WminusH_HToGG_WToAll_M125_13TeV_powheg_pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "WminusH_HToGG_WToAll_M130_13TeV_powheg_pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "WplusH_HToGG_WToAll_M120_13TeV_powheg_pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "ZNuNuGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2",
    "ZZ_TuneCP5_13TeV-pythia8_spigazzi-Era2017_RR-31Mar2018_v2-legacyRun2FullV1-v0-RunIIFall17MiniAODv2"
]

samples_2018 = [
    "DiPhotonJetsBox1BJet_MGG-80toInf_13TeV-Sherpa_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "DiPhotonJetsBox_M40_80-Sherpa_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "VBFHToGG_M-125_13TeV_powheg_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "VBFHToGG_M125_13TeV_amcatnlo_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "WZ_TuneCP5_13TeV-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "WminusH_HToGG_WToAll_M120_13TeV_powheg_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "WminusH_HToGG_WToAll_M125_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "WplusH_HToGG_WToAll_M125_13TeV_powheg_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "WplusH_HToGG_WToAll_M130_13TeV_powheg_pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ZH_HToGG_ZToAll_M120_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ZH_HToGG_ZToAll_M130_TuneCP5_13TeV-powheg-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ZNuNuGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "ZZ_TuneCP5_13TeV-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD",
    "bbHToGG_M-125_4FS_yb2_TuneCP5-13TeV-amcatnlo-pythia8_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-RunIIAutumn18MiniAOD"
]

def little_babies(baby, year):
  path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production/merged_ntuples/merged_ntuples_%s_%s/" % (version, year)
  babies = glob.glob(path + "merged_ntuple_" + baby + "/merged_ntuple*.root")
  return babies

