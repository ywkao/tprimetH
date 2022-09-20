#!/usr/bin/env python2
import subprocess
import toolbox.parallel_utils as p

def exe(command):
    subprocess.call(command, shell=True)

keys = [
    "TprimeTToTH_M-700-10p_vs_NWA",
    "TprimeTToTH_M-800-10p_vs_NWA",
    "TprimeTToTH_M-800-20p_vs_NWA",
    "TprimeTToTH_M-800-30p_vs_NWA",
    "TprimeTToTH_M-900-10p_vs_NWA",
    "TprimeTToTH_M-1000-10p_vs_NWA",
    "TprimeTToTH_M-1100-10p_vs_NWA",
    "TprimeTToTH_M-1200-10p_vs_NWA",
    "TprimeTToTH_M-1200-20p_vs_NWA",
    "TprimeTToTH_M-1200-30p_vs_NWA",
]

command_list = []
for key in keys:
    command = "./analyzer.py --key %s" % key
    command_list.append(command)
    #exe(command)

p.submit_jobs(command_list, 10)
