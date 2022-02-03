#!/usr/bin/env python
import subprocess
path = "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime/ntuples_BDTG_dataDriven_16Oct21"

lumi = 137.2
brHgg = 0.00227
xsec = [176.4, 148.85, 121.3, 104.95, 88.6, 45.9, 25.1, 14.5, 8.67, 5.36]

def run():
    data = [
        "output_Data_v3p8_16Oct21.root",
    ]

    signals = [
        "output_TprimeBToTH_M-600_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-625_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-650_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-675_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-700_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-800_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-900_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-1000_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-1100_v3p6_16Oct21.root",
        "output_TprimeBToTH_M-1200_v3p6_16Oct21.root",
    ]
    
    for f in data:
        subprocess.call("./examine %s/%s" % (path, f), shell=True)

    for i, f in enumerate(signals):
        expected_yields = lumi * brHgg * xsec[i]
        subprocess.call("./examine %s/%s %f" % (path, f, expected_yields), shell=True)
    
    print ">>> finished!"

if __name__ == "__main__":
    subprocess.call("make", shell=True)
    run()
