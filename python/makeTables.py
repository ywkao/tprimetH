#!/usr/bin/env python2
import os
import subprocess
import ROOT
ROOT.gROOT.SetBatch(True)

version = "v2p4"
years = [ 2016, 2017, 2018 ]
masses = [ 600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200 ]

f = open("tables/table_reco_mass.tex", "w")

for year in years:
    counter = 0
    mass_title     = ""
    mass_wboson    = "\multirow{2}{*}{W boson}"
    mass_top       = "\multirow{2}{*}{top}"
    mass_tprime    = "\multirow{2}{*}{tprime}"
    mass_tm_wboson = ""
    mass_tm_top    = ""
    mass_tm_tprime = ""
    for mass in masses:
        fin = ROOT.TFile.Open( "plots/hist_TprimeBToTH_M-%s_Era%s_%s.root" % (str(mass), str(year), version) )
        h_mass_wboson    = fin.Get( "h_mass_wboson"    )
        h_mass_top       = fin.Get( "h_mass_top"       )
        h_mass_tprime    = fin.Get( "h_mass_tprime"    )
        h_mass_tm_wboson = fin.Get( "h_mass_tm_wboson" )
        h_mass_tm_top    = fin.Get( "h_mass_tm_top"    )
        h_mass_tm_tprime = fin.Get( "h_mass_tm_tprime" )

        mass_title     += " & %d" % mass
        mass_wboson    += " & \\textcolor{blue}{%.2f $\pm$ %.2f}"    % (h_mass_wboson.GetMean(), h_mass_wboson.GetStdDev())
        mass_top       += " & \\textcolor{blue}{%.2f $\pm$ %.2f}"    % (h_mass_top.GetMean(), h_mass_top.GetStdDev())
        mass_tprime    += " & \\textcolor{blue}{%.2f $\pm$ %.2f}"    % (h_mass_tprime.GetMean(), h_mass_tprime.GetStdDev())
        mass_tm_wboson += " & \\textcolor{myred}{%.2f $\pm$ %.2f}" % (h_mass_tm_wboson.GetMean(), h_mass_tm_wboson.GetStdDev())
        mass_tm_top    += " & \\textcolor{myred}{%.2f $\pm$ %.2f}" % (h_mass_tm_top.GetMean(), h_mass_tm_top.GetStdDev())
        mass_tm_tprime += " & \\textcolor{myred}{%.2f $\pm$ %.2f}" % (h_mass_tm_tprime.GetMean(), h_mass_tm_tprime.GetStdDev())

        counter += 1

    mass_title     += " \\\\\n"
    mass_wboson    += " \\\\\n"
    mass_top       += " \\\\\n"
    mass_tprime    += " \\\\\n"
    mass_tm_wboson += " \\\\\n"
    mass_tm_top    += " \\\\\n"
    mass_tm_tprime += " \\\\\n"

    f.write("{\n\\renewcommand{\\arraystretch}{1.0}\n")
    f.write("\\begin{center}\n")
    f.write("\\begin{small}\n")
    f.write("\captionof{table}{Table: Mean and standard deviation of reconstruted particles for %d signal samples}\n" % year)
    f.write("\\begin{tabular}{ccccccccccc}\n")
    f.write("\hline\hline\n")
    f.write(mass_title)
    f.write("\hline\n")
    f.write(mass_wboson)
    f.write(mass_tm_wboson)
    f.write("\hline\n")
    f.write(mass_top)
    f.write(mass_tm_top)
    f.write("\hline\n")
    f.write(mass_tprime)
    f.write(mass_tm_tprime)
    f.write("\hline\hline\n")
    f.write("\end{tabular}\n")
    f.write("\end{small}\n")
    f.write("\end{center}\n")
    f.write("}\n\n")

f.close()

os.chdir("./tables")
subprocess.call("./compile.sh", shell=True)
