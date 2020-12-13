#!/usr/bin/env python2
import subprocess
import glob
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--tag", help = "to activate the script w/o additional tarball (any string)", type=str)
args = parser.parse_args()

#----------------------------------------------------------------------------------------------------#

def get_latest_dir(list_dir):
    # format: ntuples_v{version_number}
    index = 0
    counter = 0
    preferred_version = 1.1
    for sample in list_dir:
        version_number = sample.split('v')[-1]
        if version_number > preferred_version:
            preferred_version = version_number
            index = counter
        counter += 1
    return list_dir[index]

def update_data_format(ref_root_file):
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

#----------------------------------------------------------------------------------------------------#

mydir = os.getcwd()

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
    print "ref_root_file = %s" % ref_root_file

    # update data format (new variables, etc.)
    update_data_format(ref_root_file)

elif not args.tag == None:
    # pick up a ref file
    list_dir = glob.glob("ntuples*")
    dir_ntuples = get_latest_dir(list_dir)
    ref_root_file = glob.glob( mydir + "/rootfiles/" + dir_ntuples + "/*2016*.root")[0]
    print "dir_ntuples = %s" % dir_ntuples
    print "ref_root_file = %s" % ref_root_file

    # update data format (new variables, etc.)
    update_data_format(ref_root_file)

else:
    print "No need to update :)"

