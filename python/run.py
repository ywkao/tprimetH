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
#to_execution = False
to_make_histograms = True
#to_make_histograms = False
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
        exe = './bin/tprimetHHadronicLooper_v3p3'
        exe = './bin/tprimetHHadronicLooper_v2p7' if 'v2p7' in d["rootfile"] else './bin/tprimetHHadronicLooper'
        log = 'plots/log_looper_%s_%s_%d' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
        command='%s %s %s %s %s %s 2>&1 | tee %s' % (exe, d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
    if to_make_mvababies:
        exe = './bin/tprimetHHadronicMVABabyMaker_v2p7' if 'v2p7' in d["rootfile"] else './bin/tprimetHHadronicMVABabyMaker'
        log = 'plots/log_mvababy_%s_%s_%d' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
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
    cwd = os.getcwd()
    location = cwd + "/rootfiles/ntuples_v2." + str(sample_manager.subversion)
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

    for rootfile in sample_manager.signals_2016:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_signal_2017():
    cwd = os.getcwd()
    location = cwd + "/rootfiles/ntuples_v2." + str(sample_manager.subversion)
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

    for rootfile in sample_manager.signals_2017:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_signal_2018():
    cwd = os.getcwd()
    location = cwd + "/rootfiles/ntuples_v2." + str(sample_manager.subversion)
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

    for rootfile in sample_manager.signals_2018:
        year = rootfile.split('_')[2].split('a')[1]
        mass = rootfile.split('_')[1].split('-')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# Data samples
#----------------------------------------------------------------------------------------------------
def to_study_data():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    location = cwd + "/rootfiles/ntuples_v3.1"
    rootfiles = ["Data_Era2016_v3p1.root", "Data_Era2017_v3p1.root", "Data_Era2018_v3p1.root"]

    location = cwd + "/rootfiles/ntuples_v3.3"
    rootfiles = ["Data_Era2016_v3p3.root", "Data_Era2017_v3p3.root", "Data_Era2018_v3p3.root"]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# ttX samples
#----------------------------------------------------------------------------------------------------
def to_study_ttX():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"

    location = cwd + "/rootfiles/ntuples_v3.2"
    rootfiles = [
        "TTGG_Era2016_v3p2.root",
        "TTGJets_Era2016_v3p2.root",
        "TTJets_Era2016_v3p2.root",
        "TGJets_Era2017_v3p2.root",
        "TTGG_Era2017_v3p2.root",
        "TTGJets_Era2017_v3p2.root",
        "TTJets_Era2017_v3p2.root",
        "TGJets_Era2018_v3p2.root",
        "TTGG_Era2018_v3p2.root",
        "TTJets_Era2018_v3p2.root",
        "TTGJets_Era2018_v3p2.root"
    ]

    location = cwd + "/rootfiles/ntuples_v3.3"
    rootfiles = [
        "TTGG_Era2016_v3p3.root",
        "TTGJets_Era2016_v3p3.root",
        "TTJets_Era2016_v3p3.root",
        "WG_Era2016_v3p3.root",
        "WW_Era2016_v3p3.root",
        "WZ_Era2016_v3p3.root",
        "ZG_Era2016_v3p3.root",
        "ZZ_Era2016_v3p3_10.root",
        "TGJets_Era2017_v3p3.root",
        "TTGG_Era2017_v3p3.root",
        "TTGJets_Era2017_v3p3.root",
        "TTJets_Era2017_v3p3.root",
        "WG_Era2017_v3p3.root",
        "WW_Era2017_v3p3.root",
        "WZ_Era2017_v3p3.root",
        "ZG_Era2017_v3p3_10.root",
        "ZZ_Era2017_v3p3_11.root",
        "TGJets_Era2018_v3p3.root",
        "TTGG_Era2018_v3p3.root",
        "TTGJets_Era2018_v3p3.root",
        "TTJets_Era2018_v3p3.root",
        "WG_Era2018_v3p3.root",
        "WW_Era2018_v3p3.root",
        "WZ_Era2018_v3p3.root",
        "ZZ_Era2018_v3p3_10.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# smh samples
#----------------------------------------------------------------------------------------------------
def to_study_smh_set1():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"

    location = cwd + "/rootfiles/ntuples_v3.3"
    rootfiles = [
        #"ggH_Era2016_v3p3.root",
        #"VH_Era2016_v3p3.root",
        #"ttH_Era2016_v3p3.root",
        #"ggH_Era2017_v3p3.root",
        #"VH_Era2017_v3p3.root",
        #"bbH_Era2017_v3p3.root",
        #"ttH_Era2017_v3p3.root",
        #"ggH_Era2018_v3p3.root",
        #"VH_Era2018_v3p3.root",
        #"bbH_Era2018_v3p3.root",
        #"ttH_Era2018_v3p3.root"

        "VBF_Era2016_v3p3.root",
        "VBF_Era2017_v3p3.root",
        "VBF_Era2018_v3p3.root",
        "THQ_Era2016_v3p3.root",
        "THQ_Era2017_v3p3.root",
        "THQ_Era2018_v3p3.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_smh_set2():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    treename = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"

    location = cwd + "/rootfiles/ntuples_v3.3"
    rootfiles = [
        "VHToGG_Era2016_v3p3.root",
        "VHToGG_Era2017_v3p3.root",
        "VHToGG_Era2018_v3p3.root",
        "GluGluHToGG_Era2016_v3p3.root",
        "GluGluHToGG_Era2017_v3p3.root",
        "GluGluHToGG_Era2018_v3p3.root",
        "ttHJet_Era2016_v3p3.root",
        "ttHJet_Era2017_v3p3.root",
        "ttHJet_Era2018_v3p3.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# GJets samples
#----------------------------------------------------------------------------------------------------
def to_study_gammaJets():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    location = cwd + "/rootfiles/ntuples_v3.2"
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
    rootfiles = [ "GJet_Pt_Era2016_v3p2.root",  "GJet_Pt_Era2017_v3p2.root",  "GJet_Pt_Era2018_v3p2.root" ]

    location = cwd + "/rootfiles/ntuples_v3.4"
    rootfiles = [
        "GJet_Pt_Era2016_v3p4_0.root",
        "GJet_Pt_Era2016_v3p4_1.root",
        "GJet_Pt_Era2017_v3p4_0.root",
        "GJet_Pt_Era2017_v3p4_1.root",
        "GJet_Pt_Era2018_v3p4_0.root",
        "GJet_Pt_Era2018_v3p4_1.root",
        "GJet_Pt_Era2018_v3p4_2.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[2].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

def to_study_QCD():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    location = cwd + "/rootfiles/ntuples_v3.4"
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"

    rootfiles = [
        "QCD_Era2016_v3p4_2.root",
        "QCD_Era2016_v3p4_3.root",
        "QCD_Era2017_v3p4_2.root",
        "QCD_Era2017_v3p4_3.root",
        "QCD_Era2017_v3p4_4.root",
        "QCD_Era2018_v3p4_3.root",
        "QCD_Era2018_v3p4_4.root"
    ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# Diphoton samples
#----------------------------------------------------------------------------------------------------
def to_study_diphoton():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"
    treename = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"

    location = cwd + "/rootfiles/ntuples_v3.2"
    rootfiles = [ "DiPhotonJets_Era2016_v3p2.root",  "DiPhotonJets_Era2017_v3p2.root",  "DiPhotonJets_Era2018_v3p2.root" ]

    location = cwd + "/rootfiles/ntuples_v3.3"
    rootfiles = [ "DiPhotonJets_Era2016_v3p3.root",  "DiPhotonJets_Era2017_v3p3.root",  "DiPhotonJets_Era2018_v3p3.root" ]

    for rootfile in rootfiles:
        year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#----------------------------------------------------------------------------------------------------
# Other samples
#----------------------------------------------------------------------------------------------------
def to_study_bkg():
    cwd = os.getcwd()
    xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

    #----------------------------------------------------------------------------------------------------
    # Non-resonant bkg
    #----------------------------------------------------------------------------------------------------
    version = "v2p7"
    location = cwd + "/rootfiles/ntuples_v2.7_tmp_v2"
    years = [2016, 2017, 2018]
    for year in years:
        samples = ["DiPhotonJets", "GJet_Pt", "TTGG", "TTGJets", "TTJets", "VG"]
        categories = ["NRB", "NRB", "NRB", "NRB", "NRB", "NRB"]
        samples = ["DiPhotonJets", "GJet_Pt", "VG"]
        categories = ["NRB", "NRB", "NRB"]

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


    location = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production/consistency_check_txt"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent10033.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent10034.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent10035.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent250.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent12036.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent25036.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent25037.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent50038.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2018_numEvent250.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2017_numEvent250.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2017_v3p4.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2017_v3p5.root"] # check v33
    rootfiles = ["TprimeBToTH_M-1000_Era2017_v3p4p1.root"] # check v32
    rootfiles = [
        "TprimeBToTH_M-1000_Era2016_v3p5.root",
        "TprimeBToTH_M-1000_Era2017_v3p5.root",
        "TprimeBToTH_M-1000_Era2018_v3p5.root"
    ]

    rootfiles = ["TprimeBToTH_M-1000_Era2017_v3p4.root"]
    rootfiles = ["TprimeBToTH_M-1000_Era2017_numEvent250.root"]

    #location = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production"
    #treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    #rootfiles = ["TprimeBToTH_M-1000_Era2017_nnumEvent250_v3p5.root"]

    #location = cwd + "/rootfiles/ntuples_v3.4"
    #treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    #rootfiles = ["tmpV2_Data_Era2018_v3p4.root"]

    #treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    #rootfiles = ["TprimeBToTH_M-1000_Era2018_v3p4.root"]

    #location = cwd + "/rootfiles/ntuples_v3.3"
    #treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    #rootfiles = ["Data_Era2018_v3p3.root"]

    counter = 0
    for rootfile in rootfiles:
        counter += 1
        year = rootfile.split('_')[2].split('a')[1]
        #year = rootfile.split('_')[1].split('a')[1]
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

#====================================================================================================#

if __name__ == "__main__":
    subprocess.call("mkdir -p plots", shell=True)
    subprocess.call("mkdir -p dir_log", shell=True)

    #to_study_bkg()
    #to_study_gammaJets()
    #to_study_QCD()

    #to_study_data()
    #to_study_diphoton()
    #to_study_ttX()
    #to_study_smh_set2()

    #to_study_smh_set1()

    #to_study_signal_2016()
    #to_study_signal_2017()
    #to_study_signal_2018()

    to_study_ttH()

    #----------------------------------------------------------------------------------------------------
    # Execution
    #----------------------------------------------------------------------------------------------------
    if not to_execution:
        print_out_elements(command_list)
    else:
        parallel_utils.submit_jobs(command_list, 10)
        #parallel_utils.run(command_list[0])
