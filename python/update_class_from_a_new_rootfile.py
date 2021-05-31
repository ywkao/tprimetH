#!/usr/bin/env python2
import subprocess
import glob
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("-i", "--inputfile", help = "input root file", default = '', type=str)
args = parser.parse_args()

#----------------------------------------------------------------------------------------------------#

def update_data_format(filename):
    print "filename = %s" % filename

    namespace  = "tprime"
    classname  = "tprimetHHadronic"

    #--------------------------------------------------
    # signal
    #--------------------------------------------------
    my_own_tag = ""
    treename   = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    #--------------------------------------------------
    # ttH
    #--------------------------------------------------
    my_own_tag = "v3p1"
    treename   = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"
    #--------------------------------------------------
    # ttX
    #--------------------------------------------------
    my_own_tag = "v3p2"
    treename   = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"
    #--------------------------------------------------
    # root file frome test command
    #--------------------------------------------------
    my_own_tag = "v3p3p2"
    treename = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    #--------------------------------------------------
    # data
    #--------------------------------------------------
    my_own_tag = "v3p3"
    treename = "tagsDumper/trees/Data_13TeV_THQHadronicTag"


    #--------------------------------------------------
    # make class
    #--------------------------------------------------
    # Reminder: makeCMS3ClassFiles(filename, treename, classname, namespace, objname, paranoia = 0)
    command = '''
    root -l << EOF
        .L makeCMS3ClassFiles.C++
        makeCMS3ClassFiles("%s", "%s", "%s" , "%s", "analyzer");
        .q
    EOF
    ''' % (filename, treename, classname, namespace)

    os.chdir("./src/history")
    subprocess.call(command, shell=True)
    subprocess.call("cp %s.h ../../include/%s_%s.h" % (classname, classname, my_own_tag), shell=True)
    subprocess.call("cp %s.cc ../../include/%s_%s.cc" % (classname, classname, my_own_tag), shell=True)
    subprocess.call("ls -lhrt ../../include", shell=True)
    print ">>> Remember to modify header file in include/tprimetHHadronic_*.cc & include/ScanChain.h :)"

#----------------------------------------------------------------------------------------------------#

if __name__ == "__main__":
    mydir = os.getcwd()
    rootfile = args.inputfile
    rootfile = mydir + "/rootfiles/ntuples_v3.1/ttH_Era2016_v3p1.root"
    rootfile = mydir + "/rootfiles/ntuples_v3.2/TTGJet_Era2018_v3p2.root"
    rootfile = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/ntuple_production/TprimeBToTH_M-1000_Era2018_numEvent10034.root"
    rootfile = mydir + "/rootfiles/ntuples_v3.3/Data_Era2018_v3p3.root"

    update_data_format(rootfile)
