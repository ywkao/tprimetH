#!/usr/bin/env python2
import subprocess
import parallel_utils
import datetime
import os
import glob
import sample_manager
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 

idx_log = 0
command_list = []

to_execution = True
#to_execution = False
to_make_histograms = True
#to_make_histograms = False
to_make_mvababies = not to_make_histograms

cwd = os.getcwd()
location = cwd + "/rootfiles/ntuples_v3.6"
xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

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
        exe = './bin/tprimetHHadronicLooper_v3p3'
        exe = './bin/tprimetHHadronicLooper_v3p7' if 'v3.7' in d["location"] else './bin/tprimetHHadronicLooper'
        exe = './bin/tprimetHHadronicLooper'

        if 'v3.7' in d["location"]:
            log = 'plots_new/log/log_looper_%s_%s_%d' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
        else:
            log = 'plots/log/log_looper_%s_%s_%d' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)

        log = 'plots/log/log_looper_%s_%s_%d' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)

        #command='%s %s %s %s %s %s 2>&1 | tee %s' % (exe, d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
        command='%s %s %s %s %s %s 2>&1 > %s' % (exe, d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
    if to_make_mvababies:
        exe = './bin/tprimetHHadronicMVABabyMaker_v2p7' if 'v2p7' in d["rootfile"] else './bin/tprimetHHadronicMVABabyMaker'
        log = 'plots/log/log_mvababy_%s_%s_%d' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
        command='%s %s %s %s %s %s 2>&1 | tee %s' % (exe, d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
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

#----------------------------------------------------------------------------------------------------
# Signal samples
#----------------------------------------------------------------------------------------------------
def to_study_signal_2016():
    global location
    global xml_file
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"

    for rootfile in sample_manager.signals_2016:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_signal_2017():
    global location
    global xml_file
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"

    for rootfile in sample_manager.signals_2017:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_signal_2018():
    global location
    global xml_file
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"

    for rootfile in sample_manager.signals_2018:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# Data samples
#----------------------------------------------------------------------------------------------------
def to_study_data():
    #global location
    global xml_file
    location = cwd + "/rootfiles/ntuples_v3.6"
    location = cwd + "/rootfiles/ntuples_v3.7.2"
    location = cwd + "/rootfiles/ntuples_v3.7"
    location = cwd + "/rootfiles/ntuples_v3.8"
    treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    rootfiles = ["Data_Era2016.root", "Data_Era2017.root", "Data_Era2018.root"]

    #location = cwd + "/rootfiles/ntuples_v3.7.5"
    #rootfiles = ["Data_Era2018.root"]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1].split('.')[0]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# ttX samples
#----------------------------------------------------------------------------------------------------
def to_study_ttX():
    global location
    global xml_file
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"

    rootfiles = [
        "TGJets_Era2017_v3p6.root",
        "TGJets_Era2018_v3p6.root",
        "TTGG_Era2016_v3p6.root",
        "TTGG_Era2017_v3p6.root",
        "TTGG_Era2018_v3p6.root",
        "TTGJets_Era2016_v3p6.root",
        "TTGJets_Era2017_v3p6.root",
        "TTGJets_Era2018_v3p6.root",
        "TTJets_Era2016_v3p6.root",
        "TTJets_Era2017_v3p6.root",
        "TTJets_Era2018_v3p6.root",
        "WG_Era2016_v3p6.root",
        "WG_Era2017_v3p6.root",
        "WG_Era2018_v3p6.root",
        "WW_Era2016_v3p6.root",
        "WW_Era2017_v3p6.root",
        "WW_Era2018_v3p6.root",
        "WZ_Era2016_v3p6.root",
        "WZ_Era2017_v3p6.root",
        "WZ_Era2018_v3p6.root",
        "ZG_Era2016_v3p6.root",
        "ZG_Era2017_v3p6.root",
        "ZZ_Era2016_v3p6.root",
        "ZZ_Era2017_v3p6.root",
        "ZZ_Era2018_v3p6.root",
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# smh samples
#----------------------------------------------------------------------------------------------------
def to_study_smh_set1():
    global location
    global xml_file
    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"

    rootfiles = [
        "VBF_Era2016_v3p6.root",
        "VBF_Era2017_v3p6.root",
        "VBF_Era2018_v3p6.root",
        "THQ_Era2016_v3p6.root",
        "THQ_Era2017_v3p6.root",
        "THQ_Era2018_v3p6.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_smh_set2():
    global location
    global xml_file
    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"

    rootfiles = [
        "VHToGG_Era2016_v3p6.root",
        "VHToGG_Era2017_v3p6.root",
        "VHToGG_Era2018_v3p6.root",
        "GluGluHToGG_Era2016_v3p6.root",
        "GluGluHToGG_Era2017_v3p6.root",
        "GluGluHToGG_Era2018_v3p6.root",
        "ttHJet_Era2016_v3p6.root",
        "ttHJet_Era2017_v3p6.root",
        "ttHJet_Era2018_v3p6.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# GJets/QCD/diphoton samples
#----------------------------------------------------------------------------------------------------
def to_study_gammaJets():
    global location
    global xml_file
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
    rootfiles = [ "GJet_Pt_Era2016.root",  "GJet_Pt_Era2017.root",  "GJet_Pt_Era2018.root" ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[2].split('a')[1].split('.')[0]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_QCD():
    global location
    global xml_file
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
    rootfiles = [ "QCD_Era2016.root",  "QCD_Era2017.root",  "QCD_Era2018.root" ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1].split('.')[0]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_diphoton():
    global location
    global xml_file
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
    rootfiles = [ "DiPhotonJets_Era2016.root",  "DiPhotonJets_Era2017.root",  "DiPhotonJets_Era2018.root" ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1].split('.')[0]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# Manual test
#----------------------------------------------------------------------------------------------------

def to_manual_test():
    global command_list
    global xml_file
    cwd = os.getcwd()
    counter = 0

    # old {{{
    location = cwd + "/rootfiles/ntuples_v3.1"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = ["ttHJetToGG_M125_Era2018_numEvent1027.root"]

    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"
    rootfiles = ["ttHJetToGG_M125_Era2016_v3p1.root", "ttHJetToGG_M125_Era2017_v3p1.root", "ttHJetToGG_M125_Era2018_v3p1.root"]


    location = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production/consistency_check_txt"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = ["TprimeBToTH_M-1000_Era2017_v3p4.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2017_numEvent250.root"]

    study_Nan_values = False
    if study_Nan_values:
        year = "2017"

        treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
        rootfiles = [ "DiPhotonJets_Era2017.root" ]

        for rootfile in rootfiles:
            counter += 1
            my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
            command_manager(my_parameters)


        treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"
        rootfiles = [ "GluGluHToGG_Era2017_v3p6.root", "THQ_Era2017_v3p6.root" ]

        for rootfile in rootfiles:
            counter += 1
            my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
            command_manager(my_parameters)

    #}}}
    # 2nd old{{{
    location = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/rootfiles/ntuples_v3.6"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = [
        "TprimeBToTH_M-1000_Era2016_v3p6.root",
        "TprimeBToTH_M-1000_Era2017_v3p6.root",
        "TprimeBToTH_M-1000_Era2018_v3p6.root"
    ]

    location = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/rootfiles/ntuples_v3.5"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = [
        "TprimeBToTH_M-1000_Era2016_v3p5.root",
        "TprimeBToTH_M-1000_Era2017_v3p5.root",
        "TprimeBToTH_M-1000_Era2018_v3p5.root"
    ]

    location = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/rootfiles/ntuples_v3.6.1"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = [
        "TprimeBToTH_M-1000_Era2016_v3p6.root",
        "TprimeBToTH_M-1000_Era2017.root",
        "TprimeBToTH_M-1000_Era2018_v3p6.root"
    ]

    #for rootfile in rootfiles:
    #    year = rootfile.split('Era')[1].split('_')[0]
    #    counter += 1
    #    my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
    #    command_manager(my_parameters)

    treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    rootfiles = ["Data_Era2016.root", "Data_Era2017.root", "Data_Era2018.root"]

    #for rootfile in rootfiles:
    #    year = rootfile.split('Era')[1].split('.')[0]
    #    counter += 1
    #    my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
    #    command_manager(my_parameters)
    #}}}
    # trials{{{
    location = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/rootfiles/ntuples_v3.6.3"
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
    rootfiles = [
        "TGJets_Era2017_v3p6.root",
        "TTGG_Era2017_v3p6.root",
        "TTGJets_Era2017_v3p6.root",
        "TTJets_Era2017_v3p6.root",
        "TGJets_Era2018_v3p6.root",
        "TTGG_Era2018_v3p6.root",
        "TTGJets_Era2018_v3p6.root",
        "TTJets_Era2018_v3p6.root",
        "QCD_Era2017.root",
        "GJet_Pt_Era2017.root",
    ]

    location = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production"
    treename = "tagsDumper/trees/test_13TeV_THQHadronicTag"
    rootfiles = ["output_Data_2018_single_event.root"]
    rootfiles = [
            "output_Data_2016_pick_events.root",
            "output_Data_2017_pick_events.root",
            "output_Data_2018_pick_events.root"
    ]

    location = "/afs/cern.ch/work/y/ykao/ntuple_production_v5/CMSSW_10_6_8/src/flashgg/Systematics/test/ntuples_data_2018"
    treename = "tagsDumper/trees/test_13TeV_THQHadronicTag"
    rootfiles = [
            "output_EGamma_patches_01.root",
            "output_EGamma_patches_02.root",
            "output_EGamma_patches_03.root",
            "output_EGamma_patches_04.root"
    ]

    #location = "/afs/cern.ch/work/y/ykao/ntuple_production_v5/CMSSW_10_6_8/src/flashgg/Systematics/test/output_data_2018_resubmitLessSizeFile_v1"
    #treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    #os.chdir(location)
    #rootfiles = glob.glob("*root")
    #os.chdir(cwd)

    #location = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production"
    #treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    #rootfile = "output_Data_2018_strange_events.root"
    #year = 2018
    ##rootfile = "output_Data_2018_pick_events.root"
    ##year = 2018
    ##rootfile = "output_Data_2017_pick_events.root"
    ##year = 2017
    #my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
    #command_manager(my_parameters)

    #location = "/afs/cern.ch/work/y/ykao/workspace_v2/CMSSW_10_6_8/src/flashgg/Systematics/test/runWS"
    #treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    #rootfile = "output_Data_numEvent3000.root"
    #year = 2018
    #my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
    #command_manager(my_parameters)

    check_factory = False
    if check_factory:
        for i in range(13):
            num = "0" + str(i+1) if i<9 else str(i+1)

            location = "/afs/cern.ch/work/y/ykao/ntuple_production_v6/CMSSW_10_6_8/src/flashgg/Systematics/test/output_Run2018D_factory%s" % num
            treename = "tagsDumper/trees/test_13TeV_THQHadronicTag"
            os.chdir(location)
            rootfiles = glob.glob("*root")

            for rootfile in rootfiles:
                size = os.stat(rootfile).st_size * (1./1024) # KB
                if size < 1.5:
                    continue
                year = "2018"
                counter += 1
                my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
                command_manager(my_parameters)

            os.chdir(cwd)
    #}}}

    check_patches = True
    if check_patches:
        location = "/afs/cern.ch/work/y/ykao/ntuple_production_v6/CMSSW_10_6_8/src/flashgg/Systematics/test/output_data_2018_v1"
        location = "/afs/cern.ch/work/y/ykao/ntuple_production_v5/CMSSW_10_6_8/src/flashgg/Systematics/test/output_data_2018_v2"
        location = "/afs/cern.ch/work/y/ykao/ntuple_production_v5/CMSSW_10_6_8/src/flashgg/Systematics/test/output_data_2018_v1"
        location = "/afs/cern.ch/work/y/ykao/workspace_v2/CMSSW_10_6_8/src/flashgg/Systematics/test/output_data_18"
        location = "/afs/cern.ch/work/y/ykao/workspace_v2/CMSSW_10_6_8/src/flashgg/Systematics/test/backup_20210719"
        location = "/afs/cern.ch/work/y/ykao/workspace_v2/CMSSW_10_6_8/src/flashgg/Systematics/test/backup_check"
        location = "/afs/cern.ch/work/y/ykao/workspace_v2/CMSSW_10_6_8/src/flashgg/Systematics/test/backup_check"
        location = cwd + "/rootfiles/ntuples_v3.8"
        location = "/afs/cern.ch/work/y/ykao/workspace_v2/CMSSW_10_6_8/src/flashgg/Systematics/test/batch_03_ntuples/output_data_18"
        location = "/eos/home-y/ykao/tPrimeExcessHgg/merged_ntuples/ntuples_v3p8_2018/merged_ntuple_EGamma_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-Run2018B"
        os.chdir(location)

        treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"

        #rootfiles = glob.glob("*2018*root")
        #rootfiles = ["output_EGamma_spigazzi-Era2018_RR-17Sep2018_v2-legacyRun2FullV2-v0-Run2018B-17Sep2018-v1-e35808f23b4776d10c777cb2c9d2f07a_USER_60.root"]
        rootfiles = glob.glob("*root")
        for rootfile in rootfiles:
            size = os.stat(rootfile).st_size * (1./1024) # KB
            print "size = ", size
            if size < 1.5:
                continue
            year = "2018"
            counter += 1
            my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
            command_manager(my_parameters)

        os.chdir(cwd)


#====================================================================================================#

if __name__ == "__main__":
    subprocess.call("mkdir -p plots/log/", shell=True)

    # 3, 25, 3, 3, 3, 6, 9, 10, 10, 10
    to_study_data()
    #to_study_ttX()
    #to_study_gammaJets()
    #to_study_QCD()
    #to_study_diphoton()
    #to_study_smh_set1()
    #to_study_smh_set2()

    #to_study_signal_2016()
    #to_study_signal_2017()
    #to_study_signal_2018()

    #to_manual_test()

    #----------------------------------------------------------------------------------------------------
    # Execution
    #----------------------------------------------------------------------------------------------------
    if not to_execution:
        print_out_elements(command_list)
    else:
        parallel_utils.submit_jobs(command_list, 10)
        #parallel_utils.run(command_list[0])
