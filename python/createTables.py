#!/usr/bin/env python2
import os
import subprocess
import mytables

version = "v2p4"
years = [ 2016, 2017, 2018 ]
masses = [ 600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200 ]

mytables.make_table_reco_mass_v2("tables/table_reco_mass.tex", version, years, masses)

os.chdir("./tables")
subprocess.call("./compile.sh", shell=True)
