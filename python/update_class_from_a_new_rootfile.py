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
    #--------------------------------------------------
    # signal
    #--------------------------------------------------
    my_own_tag = ""
    classname  = "tprimetHHadronic"
    treename   = "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    namespace  = "tprime"

    #--------------------------------------------------
    # ttH
    #--------------------------------------------------
    my_own_tag = "v3p1"
    classname  = "tprimetHHadronic"
    treename   = "tagsDumper/trees/SMH_13TeV_THQHadronicTag"
    namespace  = "tprime"

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
    print "Remember to modify input files in python/run.py :)"

#----------------------------------------------------------------------------------------------------#

if __name__ == "__main__":
    mydir = os.getcwd()
    rootfile = args.inputfile
    rootfile = mydir + "/rootfiles/ntuples_v3.1/ttH_Era2016_v3p1.root"
    update_data_format(rootfile)

    #if rootfile == '':
    #    print "Please input a root file, e.g. ./rootfiles/ntuples_v3.1/ttH_Era2016_v3p1.root"
    #else:
    #    update_data_format(rootfile)
