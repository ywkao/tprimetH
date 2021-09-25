#!/usr/bin/env python2
import os, glob, subprocess
import parallel_utils
import sample_manager
import datetime
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 

import argparse #{{{
parser = argparse.ArgumentParser()
parser.add_argument("--exe"             , help = "executte the script"  , action="store_true")
parser.add_argument("--make_histograms" , help = "make histograms"      , action="store_true")
parser.add_argument("--make_mvababies"  , help = "make mvababies"       , action="store_true")
parser.add_argument("--set1"            , help = "process set1 samples" , action="store_true")
parser.add_argument("--set2"            , help = "process set2 samples" , action="store_true")
parser.add_argument("--set3"            , help = "process set3 samples" , action="store_true")
parser.add_argument("--set4"            , help = "process set4 samples" , action="store_true")
parser.add_argument("--set5"            , help = "process set5 samples" , action="store_true")
parser.add_argument("--set6"            , help = "process set6 samples" , action="store_true")
parser.add_argument("--test"            , help = "process test samples" , action="store_true")
parser.add_argument("--dataOnly"        , help = "process data samples" , action="store_true")
args = parser.parse_args()

to_execution = args.exe
to_make_histograms = args.make_histograms
to_make_mvababies = args.make_mvababies
#}}}

#====================================================================================================#

idx_log = 0
command_list = []

cwd = os.getcwd()
location = cwd + "/rootfiles/ntuples_v3.6"
xml_file = "mva/Hadronic__tprime_impute_hct__bdt.xml"

#====================================================================================================#

def command_manager(d): #{{{
    global idx_log
    global command_list
    global to_make_histograms
    global to_make_mvababies

    if to_make_histograms:
        exe = './bin/tprimetHHadronicLooper'
        log = 'plots/log/log_looper_%s_%s_%d.txt' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
        command='%s %s %s %s %s %s 2>&1 | tee %s' % (exe, d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)

    if to_make_mvababies:
        exe = './bin/tprimetHHadronicMVABabyMaker_v2p7' if 'v2p7' in d["rootfile"] else './bin/tprimetHHadronicMVABabyMaker'
        log = 'plots/log/log_mvababy_%s_%s_%d.txt' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
        command='%s %s %s %s %s %s 2>&1 | tee %s' % (exe, d["location"], d["rootfile"], d["treename"], d["xml_file"], d["year"], log)
        #command='./bin/covMatrix_Looper %s %s %s %s 2>&1 | tee dir_log/log_%s_%d' % (location, rootfile, year, mass, datetime_tag, idx_log)

    command_list.append(command)
    idx_log += 1
#}}}
def register_parameters(location, rootfile, treename, xml_file, year, datetime_tag): #{{{
    d = {}
    d["location"]     = location
    d["rootfile"]     = rootfile
    d["treename"]     = treename
    d["xml_file"]     = xml_file
    d["year"]         = year
    d["datetime_tag"] = datetime_tag
    return d
#}}}
def print_out_elements(mylist): #{{{
    for ele in mylist:
        print ele
#}}}
def create_commands(treename, rootfiles, another_location = ""): #{{{
    global xml_file
    loc = location
    if len(another_location) > 0:
        loc = another_location # will change global value

    for rootfile in rootfiles:
        year = rootfile.split('_Era')[1].split('.')[0]
        my_parameters = register_parameters(loc, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)
#}}}
def create_test_commands(treename, year, location): #{{{
    global command_list
    global xml_file
    cwd = os.getcwd()
    counter = 0

    os.chdir(location)
    rootfiles = glob.glob("*root")
    for rootfile in rootfiles:
        size = os.stat(rootfile).st_size * (1./1024) # KB
        if size < 1.5:
            print "[WARNING] size smaller than 1.5 KB: ", rootfile, size
            continue
        counter += 1
        my_parameters = register_parameters(location, rootfile, treename, xml_file, year, datetime_tag)
        command_manager(my_parameters)

    os.chdir(cwd)
#}}}
# trees & rootfiles {{{
dict_trees = {
    "NRB" : "tagsDumper/trees/NRB_13TeV_THQHadronicTag",
    "SMH" : "tagsDumper/trees/SMH_13TeV_THQHadronicTag",
    'tHq' : "tagsDumper/trees/tHq_13TeV_THQHadronicTag",
    'Data': "tagsDumper/trees/Data_13TeV_THQHadronicTag"
}

dict_rootfiles = {
    'gammaJets' : [ "GJet_Pt_Era2016.root"      , "GJet_Pt_Era2017.root"      , "GJet_Pt_Era2018.root"      , ] ,
    'QCD'       : [ "QCD_Era2016.root"          , "QCD_Era2017.root"          , "QCD_Era2018.root"          , ] ,
    'diphoton'  : [ "DiPhotonJets_Era2016.root" , "DiPhotonJets_Era2017.root" , "DiPhotonJets_Era2018.root" , ] ,
    'smh_set1'  : [ "VBF_Era2016.root"          , "VBF_Era2017.root"          , "VBF_Era2018.root"          ,
                    "THQ_Era2016.root"          , "THQ_Era2017.root"          , "THQ_Era2018.root"          , ] ,
    'smh_set2'  : [ "VHToGG_Era2016.root"       , "VHToGG_Era2017.root"       , "VHToGG_Era2018.root"       ,
                    "GluGluHToGG_Era2016.root"  , "GluGluHToGG_Era2017.root"  , "GluGluHToGG_Era2018.root"  ,
                    "ttHJet_Era2016.root"       , "ttHJet_Era2017.root"       , "ttHJet_Era2018.root"       , ] ,
    'ttX'       : [ "TGJets_Era2017.root"       , "TGJets_Era2018.root"       ,
                    "TTGG_Era2016.root"         , "TTGG_Era2017.root"         , "TTGG_Era2018.root"         ,
                    "TTGJets_Era2016.root"      , "TTGJets_Era2017.root"      , "TTGJets_Era2018.root"      ,
                    "TTJets_Era2016.root"       , "TTJets_Era2017.root"       , "TTJets_Era2018.root"       ,
                    "WG_Era2016.root"           , "WG_Era2017.root"           , "WG_Era2018.root"           ,
                    "WW_Era2016.root"           , "WW_Era2017.root"           , "WW_Era2018.root"           ,
                    "WZ_Era2016.root"           , "WZ_Era2017.root"           , "WZ_Era2018.root"           ,
                    "ZG_Era2016.root"           , "ZG_Era2017.root"           ,
                    "ZZ_Era2016.root"           , "ZZ_Era2017.root"           , "ZZ_Era2018.root"           , ] ,
    'Data'      : ["Data_Era2016.root"          , "Data_Era2017.root"         , "Data_Era2018.root"         , ] ,

}
#}}}

#====================================================================================================#

if __name__ == "__main__":
    subprocess.call("mkdir -p plots/log/", shell=True)
    # create commands {{{
    # 3, 25, 3, 3, 3, 6, 9, 10, 10, 10
    location_data = cwd + "/rootfiles/ntuples_v3.8"

    if args.set1:
        create_commands(dict_trees['Data'], dict_rootfiles['Data'], location_data)
        create_commands(dict_trees['NRB'], dict_rootfiles['ttX'])
        create_commands(dict_trees['NRB'], dict_rootfiles['gammaJets'], location_data)
        create_commands(dict_trees['NRB'], dict_rootfiles['QCD'], location_data)
        
    if args.set2:
        create_commands(dict_trees['SMH'], dict_rootfiles['smh_set1'])
        create_commands(dict_trees['NRB'], dict_rootfiles['diphoton'])

    if args.set3:
        create_commands(dict_trees['SMH'], dict_rootfiles['smh_set2'])

    if args.set4:
        create_commands(dict_trees['tHq'], sample_manager.signals_2016)

    if args.set5:
        create_commands(dict_trees['tHq'], sample_manager.signals_2017)

    if args.set6:
        create_commands(dict_trees['tHq'], sample_manager.signals_2018)

    if args.dataOnly:
        create_commands(dict_trees['Data'], dict_rootfiles['Data'], location_data)
    #}}}

    if args.test:
        path = "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/ntuples_v3.8"
        #create_commands(dict_trees['NRB'], dict_rootfiles['gammaJets'], path)
        #create_commands(dict_trees['NRB'], dict_rootfiles['QCD'], path)
        create_commands(dict_trees['Data'], dict_rootfiles['Data'], location_data)

        #path = "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/ntuples_v3.8.1"
        ##create_commands(dict_trees['Data'], ["Data_Era2016.root"], location_data)
        #create_commands(dict_trees['Data'], dict_rootfiles['Data'], location_data)
        #create_commands(dict_trees['NRB'], ["QCD_Era2016.root"], path)
        #create_commands(dict_trees['NRB'], ["GJet_Pt_Era2016.root"], path)
        #create_commands(dict_trees['NRB'], ["QCD_Era2017.root"], path)
        #create_commands(dict_trees['NRB'], ["GJet_Pt_Era2017.root"], path)
        #create_commands(dict_trees['NRB'], ["QCD_Era2018.root"])
        #create_commands(dict_trees['NRB'], ["GJet_Pt_Era2018.root"])
        #create_commands(dict_trees['NRB'], dict_rootfiles['diphoton'])

        # set1
        #path = "/eos/home-y/ykao/tPrimeExcessHgg/merged_ntuples/ntuples_v3p6p4_2016"
        #dir_01 = "merged_ntuple_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3"
        #dir_02 = "merged_ntuple_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8_spigazzi-Era2016_RR-17Jul2018_v2-legacyRun2FullV1-v0-RunIISummer16MiniAODv3"
        #create_test_commands(dict_trees['NRB'], 2016, path + "/" + dir_01)
        #create_test_commands(dict_trees['NRB'], 2016, path + "/" + dir_02)

        # set2
        #create_commands(dict_trees['Data'], dict_rootfiles['Data'], location_data)
        #create_commands(dict_trees['NRB'], dict_rootfiles['gammaJets'])
        #create_commands(dict_trees['NRB'], dict_rootfiles['QCD'])

    #----------------------------------------------------------------------------------------------------
    # Execution
    #----------------------------------------------------------------------------------------------------
    if not to_execution:
        print_out_elements(command_list)
    else:
        parallel_utils.submit_jobs(command_list, 10)
        #parallel_utils.run(command_list[0])
