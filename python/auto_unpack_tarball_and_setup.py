#!/usr/bin/env python2
import subprocess
import glob
import os

mydir = "/wk_cms/ykao/work/CMSSW_10_6_8"

os.chdir("./rootfiles")
tarball = glob.glob("ntuples*")[-1]
do_unpack = True if "tar.gz" in tarball else False

if do_unpack:
    # unpack the latest tarball
    print "unpack a tarball: %s" % tarball
    subprocess.call("tar -zxvf %s" % tarball, shell=True)

    # pick up a ref file
    dir_ntuples = tarball.split(".tar.gz")[0]
    ref_root_file = glob.glob( mydir + "/rootfiles/" + dir_ntuples + "/*2016*.root")[0]

    # update data format (new variables, etc.)
    os.chdir("../src/history")
    command = '''
    root -l << EOF
        .L makeCMS3ClassFiles.C++
        makeCMS3ClassFiles("%s", "tagsDumper/trees/tHq_13TeV_THQHadronicTag", "tprimetHHadronic", "tprime", "analyzer");
        .q
    EOF
    ''' % (ref_root_file)
    subprocess.call(command, shell=True)
    subprocess.call("cp tprimetHHadronic.h tprimetHHadronic.cc ../../include/", shell=True)
    subprocess.call("ls -lhrt ../../include", shell=True)
    
    print "Remember to modify input files in src/tprimetHHadronicLooper.cpp :)"

else:
    print "No need to update :)"
