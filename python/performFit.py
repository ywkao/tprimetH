#!/usr/bin/env python2
import os
import glob
import subprocess
import transfer_helper
import parallel_utils
#import datetime
#today = datetime.datetime.today()
#datetime_tag = today.strftime("%Y%m%d") 

to_fit_chi2_value = True
to_fit_mass = False

#target = "/eos/user/y/ykao/www/plots/fit_result"
target = "/eos/user/y/ykao/www/plots/20210208"
transfer_helper.prepare_index_php(target)
rootfiles = glob.glob("plots/hist_*root")


if to_fit_chi2_value:
    command_list = []
    for rootfile in rootfiles:
        era = rootfile.split('_')[3]
        year = era.split('a')[1]
        mass = rootfile.split('_')[2].split('-')[1]
        log = "stashed/fit_result_chi2_value_" + mass + "_" + era + ".txt"

        command = "root -l -b -q 'macro/fit_chi2_value.C(\"%s\", \"%s\", \"%s\", %f, %f, %f, %f, %f, %f, %f, %f)' | tee -a %s" % ("chi2_value", year, mass, 10, 0., 150, 20, 110, 100, 180, 50, log)
        command_list.append(command)

    nPar = 15
    parallel_utils.submit_jobs(command_list, nPar)
    subprocess.call("mv plots/fit_chi2_* %s" %(target), shell=True)


if to_fit_mass:
    command_list = []
    #for file in rootfiles:
    #    era = file.split('_')[3]
    #    year = era.split('a')[1]
    #    mass = file.split('_')[2].split('-')[1]
    #
    #    #log = "stashed/fit_result_mass_" + mass + "_" + era + ".txt"
    #    log = "stashed/fit_result_mass_" + mass + "_" + era + "_diphoton.txt"
    #
    #    command = "root -l -b -q 'macro/fitdata_two_gaussian.C(\"%s\", \"%s\", \"%s\", %f, %f, %f, %f, %f, %f, %f, %f)' | tee -a %s" % ("diphoton", year, mass, 125, 100, 150, 20, 110, 100, 180, 50, log)
    #    command_list.append(command)
    #
    #    #command = "root -l -b -q 'macro/fitdata_two_gaussian.C(\"%s\", \"%s\", \"%s\", %f, %f, %f, %f, %f, %f, %f, %f)' | tee -a %s" % ("top", year, mass, 170, 80, 280, 18, 140, 100, 180, 18, log)
    #    #command_list.append(command)
    #
    #    #command = "root -l -b -q 'macro/fitdata_two_gaussian.C(\"%s\", \"%s\", \"%s\", %f, %f, %f, %f, %f, %f, %f, %f)' | tee -a %s" % ("wboson", year, mass, 80, 40, 120, 13, 60, 40, 100, 13, log)
    #    #command_list.append(command)
    #
    #    #command = "root -l -b -q 'macro/fitdata_one_gaussian.C(\"%s\", \"%s\", \"%s\", %f, %f, %f, %f)'" % ("top", year, mass, 170, 100, 400, 18)
    #    #command_list.append(command)
    #
    #    #command = "root -l -b -q 'macro/fitdata_one_gaussian.C(\"%s\", \"%s\", \"%s\", %f, %f, %f, %f)'" % ("wboson", year, mass, 80, 40, 200, 13)
    #    #command_list.append(command)
    #
    #nPar = 15
    #parallel_utils.submit_jobs(command_list, nPar)
    
    #subprocess.call("cp -p plots/fit*.png %s" % target, shell=True)
    #years = [2016, 2017, 2018]
    #objects = ["top", "wboson"]
    #for year in years:
    #    subdir = "%s/%d" % (target, year)
    #    transfer_helper.prepare_index_php(subdir)
    #    for obj in objects:
    #        subdir = "%s/%d/%s" % (target, year, obj)
    #        transfer_helper.prepare_index_php(subdir)
    #        subprocess.call("mv %s/*%s*%d*.png %s" %(target, obj, year, subdir), shell=True)
    #
    #print "plots/fit*png are updated to the directory: %s" % target
    
    
    #subdir = "%s/2016/top" % target
    #transfer_helper.prepare_index_php(subdir)
    #subprocess.call("mv %s/2016/*top*.png %s" %(target, subdir), shell=True)
    #
    #subdir = "%s/2016/wboson" % target
    #transfer_helper.prepare_index_php(subdir)
    #subprocess.call("mv %s/2016/*wboson*.png %s" %(target, subdir), shell=True)
    #
    #subdir = "%s/2017/top" % target
    #transfer_helper.prepare_index_php(subdir)
    #subprocess.call("mv %s/2017/*top*.png %s" %(target, subdir), shell=True)
    #
    #subdir = "%s/2017/wboson" % target
    #transfer_helper.prepare_index_php(subdir)
    #subprocess.call("mv %s/2017/*wboson*.png %s" %(target, subdir), shell=True)
    #
    #subdir = "%s/2018/top" % target
    #transfer_helper.prepare_index_php(subdir)
    #subprocess.call("mv %s/2018/*top*.png %s" %(target, subdir), shell=True)
    #
    #subdir = "%s/2018/wboson" % target
    #transfer_helper.prepare_index_php(subdir)
    #subprocess.call("mv %s/2018/*wboson*.png %s" %(target, subdir), shell=True)
