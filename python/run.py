#!/usr/bin/env python2
import subprocess
import parallel_utils
import datetime
import os
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 
subversion = 4
cwd = os.getcwd()
location = cwd + "/rootfiles/ntuples_v2." + str(subversion)

signals = [
    "TprimeBToTH_M-1000_Era2017_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1000_Era2018_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2018_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2018_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-600_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2018_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1100_Era2017_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2017_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-600_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2017_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-1000_Era2016_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1100_Era2016_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-1200_Era2016_v2p%s.root"  %  str(subversion),
    "TprimeBToTH_M-600_Era2016_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-625_Era2016_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-650_Era2016_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-675_Era2016_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-700_Era2016_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-800_Era2016_v2p%s.root"   %  str(subversion),
    "TprimeBToTH_M-900_Era2016_v2p%s.root"   %  str(subversion)
]

subprocess.call("mkdir -p plots", shell=True)

command_list = []

counter = 0
for rootfile in signals:
    counter += 1
    year = rootfile.split('_')[2].split('a')[1]
    mass = rootfile.split('_')[1].split('-')[1]
    command='./bin/tprimetHHadronicLooper %s %s %s %s 2>&1 | tee dir_log/log_%s_%d' % (location, rootfile, year, mass, datetime_tag, counter)
    #command='./bin/covMatrix_Looper %s %s %s %s 2>&1 | tee dir_log/log_%s_%d' % (location, rootfile, year, mass, datetime_tag, counter)

    command_list.append(command)
    break

nPar = 12
parallel_utils.submit_jobs(command_list, nPar)
