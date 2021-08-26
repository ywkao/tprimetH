#!/usr/bin/env python
import glob, subprocess

#grep "dataset" 20210620/log_tmva_Tprime_NRB_varSet8_M600_M700_20210620_20210620.txt | grep ": 0" | grep "BDT"

date = "20210820"
date = "20210620"

tmp_file = "tmp.csv"
csv_file = "output/mytable_%s.csv" % date
path = "/eos/user/y/ykao/tPrimeExcessHgg/xmlfiles/";

def extract(fin, fout):
    with open(fin, 'r') as f:
        lines = f.readlines()
        for line in lines:
            if "dataset" in line and "BDT" in line and ": 0" in line:
                content = line.rstrip().split()
                for ele in content:
                    if not ('(' in ele) and ('0' in ele or 'BDT' in ele):
                        fout.write(ele + ", ")
                fout.write("\n")

def make_table():
    log_nrb = []
    log_smh = []
    
    mass_pair = {600:700,800:1000,1100:1200}
    for mass in [600, 800, 1100]:
        log_nrb += glob.glob(path + date + "/log*NRB*M%d_M%d*" % (mass, mass_pair[mass]) )
        log_smh += glob.glob(path + date + "/log*SMH*M%d_M%d*" % (mass, mass_pair[mass]) )

    log_files = log_nrb + log_smh
    with open(tmp_file, 'w') as fout:
        for log in log_files:
            fout.write(log + "\n")
            extract(log, fout)
            fout.write("\n\n")

#----------------------------------------------------------------------------------------------------#

def write_list(info, fout):
    for ele in info:
        fout.write(ele + ", ")
    fout.write("\n")

def refine_table():
    with open(csv_file, 'w') as fout:
        with open(tmp_file, 'r') as fin:
            info_bdt = []
            info_bdtg = []

            for line in fin.readlines():
                data = line.strip()
                if len(data) != 0: # prevent blank line

                    content = line.rstrip().split(",")
                    print content

                    bool_start = len(content) == 1
                    if bool_start:
                        info_bdt = []
                        info_bdtg = []
                        fout.write(line.rstrip() + "\n")

                    if len(content) == 4:
                        if content[1] == ' BDT':
                            info_bdt += content[:-1]
                        if content[1] == ' BDTG':
                            info_bdtg += content[:-1]

                    if len(content) == 6:
                        if content[1] == ' BDT':
                            info_bdt += content[2:-1]
                            write_list(info_bdt, fout)
                        if content[1] == ' BDTG':
                            info_bdtg += content[2:-1]
                            write_list(info_bdtg, fout)

#----------------------------------------------------------------------------------------------------#

if __name__ == "__main__":
    make_table()
    refine_table()
    subprocess.call("vimdiff %s" % tmp_file, shell=True)
    subprocess.call("vimdiff %s" % csv_file, shell=True)
    subprocess.call("rm %s" % tmp_file, shell=True)

