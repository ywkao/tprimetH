#!/usr/bin/env python2
import os, glob, subprocess
import parallel_utils
import sample_manager as sm
import datetime
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 

import argparse #{{{
parser = argparse.ArgumentParser()
parser.add_argument("--exe"             , help = "executte the script"  , action="store_true")
parser.add_argument("--make_histograms" , help = "make histograms"      , action="store_true")
parser.add_argument("--make_mvababies"  , help = "make mvababies"       , action="store_true")
parser.add_argument("--do_truthStudy"   , help = "do truth study"       , action="store_true")
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
to_do_truthStudy = args.do_truthStudy
#}}}

#====================================================================================================#

idx_log = 0
command_list = []

cwd = os.getcwd()
location_v3p6 = cwd + "/rootfiles/ntuples_v3.6"
location_v3p8 = cwd + "/rootfiles/ntuples_v3.8"
location = cwd + "/rootfiles/ntuples_v4.1"
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

    if to_do_truthStudy:
        exe = './bin/covMatrix_Looper'
        log = 'plots/log/log_truth_%s_%s_%d.txt' % (d["rootfile"].split('.')[0], d["datetime_tag"], idx_log)
        mass_tag = d["rootfile"].split("M-")[-1].split("_Era")[0]
        command='%s %s %s %s %s 2>&1 | tee %s' % (exe, d["location"], d["rootfile"], d["year"], mass_tag, log)

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
def print_out_elements(mylist, do_list=True): #{{{
    for command in mylist:
        l = command.split()
        rootfile = l[1] + "/" + l[2]
        if do_list:
            subprocess.call("ls %s" % rootfile, shell=True)
        else:
            print command 
#}}}
def create_commands(treename, rootfiles, another_location = "", year = ""): #{{{
    global xml_file
    loc = location

    year_determined_by_input_argument = len(year) > 0

    if len(another_location) > 0:
        loc = another_location # will change global value

    for rootfile in rootfiles:
        if not year_determined_by_input_argument: # use the following if not specified
            year = rootfile.split('_Era')[1].split('.')[0]

        #print ">>> run::create_commands %s, year = %s" % (rootfile, year)
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

#====================================================================================================#

if __name__ == "__main__":
    subprocess.call("mkdir -p plots/log/", shell=True)
    # create commands {{{
    # 3, 25, 3, 3, 3, 6, 9, 10, 10, 10
    if args.set1:
        create_commands(sm.dict_trees['Data'], sm.dict_rootfiles['Data'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['ttX'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['gammaJets'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['QCD'])
        
    if args.set2:
        create_commands(sm.dict_trees['SMH'] , sm.dict_rootfiles['smh_set1'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['diphoton'])

    if args.set3:
        create_commands(sm.dict_trees['SMH'] , sm.dict_rootfiles['smh_set2'])

    if args.set4:
        create_commands(sm.dict_trees['tHq'] , sm.signals_2016)

    if args.set5:
        create_commands(sm.dict_trees['tHq'],  sm.signals_2017)

    if args.set6:
        create_commands(sm.dict_trees['tHq'],  sm.signals_2018)

    if to_do_truthStudy:
        create_commands(sm.dict_trees['tHq'], ["TprimeBToTH_total_covStudy.root"], location, "2017")
        
        # create_commands(sm.dict_trees['tHq'] , sm.signals_2016)
        # create_commands(sm.dict_trees['tHq'],  sm.signals_2017)
        # create_commands(sm.dict_trees['tHq'],  sm.signals_2018)
    #}}}

    if args.test:
        #path = "/afs/cern.ch/work/y/ykao/workspace_ultraLegacy/CMSSW_10_6_8/src/flashgg/Systematics/test/runWS"
        #create_commands(sm.dict_trees['tHq'], ["output_TprimeBToTH_M-1000_n500_UL17_v2.root"], path, "2017")

        #create_commands(sm.dict_trees['Data'], sm.dict_rootfiles['Data'], location_v3p8)
        create_commands(sm.dict_trees['Data'], sm.dict_rootfiles['Data'])
        #create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['diphoton'])

        #create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['gammaJets'])
        #create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['QCD'])

    if False:
        create_commands(sm.dict_trees['Data'], sm.dict_rootfiles['Data'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['ttX'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['gammaJets'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['QCD'])
        create_commands(sm.dict_trees['SMH'] , sm.dict_rootfiles['smh_set1'])
        create_commands(sm.dict_trees['NRB'] , sm.dict_rootfiles['diphoton'])
        create_commands(sm.dict_trees['SMH'] , sm.dict_rootfiles['smh_set2'])
        create_commands(sm.dict_trees['tHq'] , sm.signals_2017)
        create_commands(sm.dict_trees['tHq'] , sm.signals_2018)
        create_commands(sm.dict_trees['tHq'] , sm.signals_2016)

    #----------------------------------------------------------------------------------------------------
    # Execution
    #----------------------------------------------------------------------------------------------------
    if not to_execution:
        print_out_elements(command_list)
        print_out_elements(command_list, False)
    else:
        parallel_utils.submit_jobs(command_list, 10)
