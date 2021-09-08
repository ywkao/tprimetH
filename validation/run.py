#!/usr/bin/env python
import subprocess
path = "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime"

def run():
    files = [
        "output_Data_v3p8_21Jul21.root",
        "output_TprimeBToTH_M-600_v3p6_21Jul21.root",
        "output_TprimeBToTH_M-650_v3p6_21Jul21.root",
        "output_TprimeBToTH_M-700_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-800_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-900_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-675_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-625_v3p6_21Jul21.root",
        #"output_VHToGG_v3p6_21Jul21.root",
        #"output_VBF_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-1000_v3p6_21Jul21.root",
        #"output_GluGluHToGG_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-1100_v3p6_21Jul21.root",
        #"output_ttHJet_v3p6_21Jul21.root",
        #"output_TprimeBToTH_M-1200_v3p6_21Jul21.root",
        #"output_THQ_v3p6_21Jul21.root",
    ]
    
    for f in files:
        subprocess.call("./examine %s/%s" % (path, f), shell=True)
    
    print ">>> finished!"

if __name__ == "__main__":
    subprocess.call("make", shell=True)
    run()
