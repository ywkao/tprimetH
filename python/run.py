#!/usr/bin/env python2
import subprocess

signals = [
            "rootfiles/ntuples_v1.4/TprimeBToTH_M-700_LH_TuneCUETP8M1_13TeV_Era2016_v1p4.root",
            "rootfiles/ntuples_v1.4/TprimeBToTH_M-700_LH_TuneCP5_13TeV_Era2017_v1p4.root",
            "rootfiles/ntuples_v1.4/TprimeBToTH_M-700_LH_TuneCP5_PSweights_13TeV_Era2018_v1p4.root"
]

for file in signals:
    command='./bin/tprimetHHadronicLooper %s' % file
    subprocess.call(command, shell=True)
    break
