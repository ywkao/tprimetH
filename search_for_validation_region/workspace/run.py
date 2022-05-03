#!/usr/bin/env python2
import subprocess

path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/shortcut_plots/plots_20220404_ntuple_for_validation_region_search"

def process(root):
    log = root.replace("root", "txt").replace("output", "log")
    #command = "./bin/examine %s/%s 2>&1 > log/%s" % (path, root, log)
    command = "./bin/examine %s/%s" % (path, root)
    print ">>>", command
    subprocess.call(command, shell=True)

def create_2D_plots():
    process( "output_Data_v4p2.root" )
    process( "output_Data_600_700_leptonic.root" )
    process( "output_Data_800_1000_leptonic.root" )
    process( "output_Data_1100_1200_leptonic.root" )

def process_VLQ_signal():
    process( "output_TprimeBToTH_M-600.root" )
    process( "output_TprimeBToTH_M-625.root" )
    process( "output_TprimeBToTH_M-650.root" )
    process( "output_TprimeBToTH_M-675.root" )
    process( "output_TprimeBToTH_M-700.root" )
    process( "output_TprimeBToTH_M-800.root" )
    process( "output_TprimeBToTH_M-900.root" )
    process( "output_TprimeBToTH_M-1000.root" )
    process( "output_TprimeBToTH_M-1100.root" )
    process( "output_TprimeBToTH_M-1200.root" )

def process_NRB():
    #process( "output_imputedQCD.root" )
    process( "output_DiPhotonJets.root" )
    process( "output_imputedQCD_v4p2.root" )
    process( "output_TTGG.root" )
    process( "output_TTGJets.root" )
    process( "output_TTJets.root" )
    process( "output_WG.root" )
    process( "output_NRB_v4p2.root" )

def process_SMH():
    process( "output_ttHJet.root" )
    process( "output_GluGluHToGG.root" )
    process( "output_THQ.root" )
    process( "output_VBF.root" )
    process( "output_VHToGG.root" )

if __name__ == "__main__":
    subprocess.call("make", shell=True)
    subprocess.call("mkdir -p eos/signal_region", shell=True)
    subprocess.call("mkdir -p ./log", shell=True)

    #process( "output_Data.root" )
    #process( "output_Data_v4p2.root" )
    create_2D_plots()

    exit()

    process( "output_Data_v4p2.root" )
    process( "output_SMH.root" )
    process_VLQ_signal()
    subprocess.call("./check_yields.sh", shell=True)

    exit()

    process_NRB()
    process_SMH()

