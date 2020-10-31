#!/usr/bin/env python2
import subprocess

signals = [
            "signal_ntuples_2016/TprimeBToTH_M-700_LH_TuneCUETP8M1_13TeV_Era2016.root",
            "signal_ntuples_2017/TprimeBToTH_M-700_LH_TuneCP5_13TeV_Era2017.root",
            "signal_ntuples_2018/TprimeBToTH_M-700_LH_TuneCP5_PSweights_13TeV_Era2018.root"
]

for file in signals:
    command='./bin/tprimetHHadronicLooper %s' % file
    subprocess.call(command, shell=True)
    break
