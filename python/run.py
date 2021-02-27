#!/usr/bin/env python2
import subprocess
import parallel_utils
import datetime
import os
import sample_manager
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 

to_study_signal = True
to_run_whole_samples = False
years = "2016,2017,2018"
#years = "2016"

#----------------------------------------------------------------------------------------------------#

if to_study_signal:
    subprocess.call("mkdir -p plots", shell=True)
    cwd = os.getcwd()
    location = cwd + "/rootfiles/ntuples_v2." + str(sample_manager.subversion)
    
    counter = 0
    command_list = []
    for rootfile in sample_manager.signals:
        counter += 1
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        command='./bin/tprimetHHadronicLooper %s %s %s %s 2>&1 | tee dir_log/log_%s_%d' % (location, rootfile, year, mass, datetime_tag, counter)
        #command='./bin/covMatrix_Looper %s %s %s %s 2>&1 | tee dir_log/log_%s_%d' % (location, rootfile, year, mass, datetime_tag, counter)
    
        command_list.append(command)
        break
    
    nPar = 12
    parallel_utils.submit_jobs(command_list, nPar)

#----------------------------------------------------------------------------------------------------#

if to_run_whole_samples:
    idx = 0
    command_list = []
    if "2016" in years:
        for baby in sample_manager.samples_2016:
            for little_baby in sample_manager.little_babies(baby, "2016"):
                command = 'echo "(%3d)"; ls %s;' % (idx, little_baby)
                command_list.append(command)
                idx += 1
    if "2017" in years:
        for baby in sample_manager.samples_2017:
            for little_baby in sample_manager.little_babies(baby, "2017"):
                command = 'echo "(%3d)"; ls %s;' % (idx, little_baby)
                command_list.append(command)
                idx += 1
    if "2018" in years:
        for baby in sample_manager.samples_2018:
            for little_baby in sample_manager.little_babies(baby, "2018"):
                command = 'echo "(%3d)"; ls %s;' % (idx, little_baby)
                command_list.append(command)
                idx += 1

    for command in command_list:
        print command
    #nPar = 12
    #parallel_utils.submit_jobs(command_list, nPar)
