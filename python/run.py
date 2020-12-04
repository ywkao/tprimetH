#!/usr/bin/env python2
import subprocess
import parallel_utils

signals = [
    "TprimeBToTH_M-1000_Era2016_v2p8.root",
    "TprimeBToTH_M-1000_Era2017_v2p8.root",
    "TprimeBToTH_M-1100_Era2017_v2p8.root",
    "TprimeBToTH_M-1200_Era2017_v2p8.root",
    "TprimeBToTH_M-600_Era2016_v2p8.root",
    "TprimeBToTH_M-600_Era2017_v2p8.root",
    "TprimeBToTH_M-625_Era2017_v2p8.root",
    "TprimeBToTH_M-625_Era2018_v2p8.root",
    "TprimeBToTH_M-650_Era2017_v2p8.root",
    "TprimeBToTH_M-650_Era2018_v2p8.root",
    "TprimeBToTH_M-675_Era2017_v2p8.root",
    "TprimeBToTH_M-700_Era2017_v2p8.root",
    "TprimeBToTH_M-700_Era2018_v2p8.root",
    "TprimeBToTH_M-800_Era2016_v2p8.root",
    "TprimeBToTH_M-800_Era2017_v2p8.root",
    "TprimeBToTH_M-900_Era2016_v2p8.root",
    "TprimeBToTH_M-900_Era2017_v2p8.root",
    "TprimeBToTH_M-900_Era2018_v2p8.root"
]

command_list = []

counter = 0
for file in signals:
    counter += 1
    command='./bin/tprimetHHadronicLooper %s 2>&1 | tee dir_log/log_20201204_%d' % (file, counter)
    command_list.append(command)
    #subprocess.call(command, shell=True)

nPar = 12
parallel_utils.submit_jobs(command_list, nPar)
