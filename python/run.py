#!/usr/bin/env python2
import subprocess
import parallel_utils
import datetime
import os
import sample_manager
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 

idx_log = 0
command_list = []

to_execution = True
to_make_histograms = False
to_make_mvababies = not to_make_histograms

#====================================================================================================#

def print_out_elements(mylist):
    for ele in mylist:
        print ele

def command_manager(d):
    global idx_log
    global command_list
    global to_make_histograms
    global to_make_mvababies

    if to_make_histograms:
        log = 'dir_log/log_looper_%s_%d' % (d["datetime_tag"], idx_log)
        command='./bin/tprimetHHadronicLooper %s %s %s %s %s 2>&1 | tee %s' % (d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
    if to_make_mvababies:
        log = 'dir_log/log_mvababy_%s_%d' % (d["datetime_tag"], idx_log)
        command='./bin/tprimetHHadronicMVABabyMaker %s %s %s %s %s 2>&1 | tee %s' % (d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
        #command='./bin/covMatrix_Looper %s %s %s %s 2>&1 | tee dir_log/log_%s_%d' % (location, rootfile, year, mass, datetime_tag, idx_log)

    command_list.append(command)
    idx_log += 1

def register_parameters(location, rootfile, treename, xml_file, year, datetime_tag):
    d = {}
    d["location"]     = location
    d["rootfile"]     = rootfile
    d["treename"]     = treename
    d["xml_file"]     = xml_file
    d["year"]         = year
    d["datetime_tag"] = datetime_tag
    return d

#====================================================================================================#

def to_study_signal():
    cwd = os.getcwd()
    location = cwd + "/rootfiles/ntuples_v2." + str(sample_manager.subversion)
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

    for rootfile in sample_manager.signals:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_data_and_bkg():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

    #----------------------------------------------------------------------------------------------------
    # data and bkg
    #----------------------------------------------------------------------------------------------------
    version = "v2p7"
    location = cwd + "/rootfiles/ntuples_v2.7_tmp_v2"
    years = [2016, 2017, 2018]
    for year in years:
        samples = ["DiPhotonJets", "GJet_Pt", "TTGG", "TTGJets", "TTJets", "VG", "Data"]
        categories = ["NRB", "NRB", "NRB", "NRB", "NRB", "NRB", "Data"]

        rootfiles = []
        for sample in samples:
            rootfiles.append( "%s_Era%d_%s.root" % (sample, year, version) )

        counter = 0
        for rootfile in rootfiles:
            treename = "tagsDumper/trees/%s_13TeV_THQHadronicTag" % categories[counter]
            my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
            command_manager(my_parameters)
            counter += 1

    #----------------------------------------------------------------------------------------------------
    # ttH samples
    #----------------------------------------------------------------------------------------------------
    location = cwd + "/rootfiles/ntuples_v3.1"
    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"
    rootfiles = ["ttHJetToGG_M125_Era2016_v3p1.root", "ttHJetToGG_M125_Era2017_v3p1.root", "ttHJetToGG_M125_Era2018_v3p1.root"]

    for rootfile in rootfiles:
        year = rootfile.split('_')[2].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#====================================================================================================#

def to_study_ttH():
    global command_list
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    location = cwd + "/rootfiles/ntuples_v3.1"

    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = ["ttHJetToGG_M125_Era2018_numEvent1027.root"]

    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"
    rootfiles = ["ttHJetToGG_M125_Era2016_v3p1.root", "ttHJetToGG_M125_Era2017_v3p1.root", "ttHJetToGG_M125_Era2018_v3p1.root"]

    counter = 0
    for rootfile in rootfiles:
        counter += 1
        year = rootfile.split('_')[2].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#====================================================================================================#

if __name__ == "__main__":
    subprocess.call("mkdir -p plots", shell=True)
    subprocess.call("mkdir -p dir_log", shell=True)

    to_study_data_and_bkg()
    to_study_signal()
    #to_study_ttH()

    #----------------------------------------------------------------------------------------------------
    # Execution
    #----------------------------------------------------------------------------------------------------
    if not to_execution:
        print_out_elements(command_list)
    else:
        parallel_utils.submit_jobs(command_list, 10)
        #parallel_utils.run(command_list[0])
