#!/usr/bin/env python
import subprocess

date = "20210620"

# example
filename = "20210620/TMVA_Run2_Tprime_NRB_varSet8_M600_M700_20210620.root"
filename = "20210620/TMVA_Run2_Tprime_SMH_varSet8_M600_M700_20210620.root"

def get_corMatrix(bkg, mass):
    tag = mass + "_" + date
    filename = "%s/TMVA_Run2_Tprime_%s_varSet8_%s.root" % (date, bkg, tag)
    dataset  = "dataset_Run2_Tprime_%s_varSet8_%s" % (bkg, tag)
    output   = "%s/corMatrix_%s_%s.pdf" % (date, bkg, tag)
    
    command = '''root -l -b -q 'get_correlation_matrix.C("%s", "%s", "%s")' ''' % (filename, dataset, output)
    subprocess.call(command, shell = True)

if __name__ == "__main__":
    tags = ["M600_M700", "M800_M1000", "M1100_M1200"]
    tags = ["M600_M700"]
    for tag in tags:
        get_corMatrix("NRB", tag)
        get_corMatrix("SMH", tag)
