#!/usr/bin/env python2
import ROOT
ROOT.gROOT.SetBatch(True)

def make_table_reco_mass_v2(name_tex_file, version, years, masses):
    f = open(name_tex_file, "w")
    
    list_objects = ["wboson", "top", "tprime"]
    for obj in list_objects:
        counter = 0
        mass_title     = ""
        mass_2016    = "\multirow{2}{*}{2016}"
        mass_2017    = "\multirow{2}{*}{2017}"
        mass_2018    = "\multirow{2}{*}{2018}"
        mass_tm_2016 = ""
        mass_tm_2017 = ""
        mass_tm_2018 = ""
        for mass in masses:
            fin_2016 = ROOT.TFile.Open( "plots/hist_TprimeBToTH_M-%s_Era2016_%s.root" % (str(mass), version) )
            fin_2017 = ROOT.TFile.Open( "plots/hist_TprimeBToTH_M-%s_Era2017_%s.root" % (str(mass), version) )
            fin_2018 = ROOT.TFile.Open( "plots/hist_TprimeBToTH_M-%s_Era2018_%s.root" % (str(mass), version) )
            h_mass_2016 = fin_2016.Get("h_mass_" + obj)
            h_mass_2017 = fin_2017.Get("h_mass_" + obj)
            h_mass_2018 = fin_2018.Get("h_mass_" + obj)
            h_mass_tm_2016 = fin_2016.Get("h_mass_tm_" + obj)
            h_mass_tm_2017 = fin_2017.Get("h_mass_tm_" + obj)
            h_mass_tm_2018 = fin_2018.Get("h_mass_tm_" + obj)

            mass_title     += " & %d" % mass
            mass_2016    += " & \\textcolor{blue}{%.2f $\pm$ %.2f}"  % (h_mass_2016.GetMean(), h_mass_2016.GetStdDev())
            mass_2017    += " & \\textcolor{blue}{%.2f $\pm$ %.2f}"  % (h_mass_2017.GetMean(), h_mass_2017.GetStdDev())
            mass_2018    += " & \\textcolor{blue}{%.2f $\pm$ %.2f}"  % (h_mass_2018.GetMean(), h_mass_2018.GetStdDev())
            mass_tm_2016 += " & \\textcolor{myred}{%.2f $\pm$ %.2f}" % (h_mass_tm_2016.GetMean(), h_mass_tm_2016.GetStdDev())
            mass_tm_2017 += " & \\textcolor{myred}{%.2f $\pm$ %.2f}" % (h_mass_tm_2017.GetMean(), h_mass_tm_2017.GetStdDev())
            mass_tm_2018 += " & \\textcolor{myred}{%.2f $\pm$ %.2f}" % (h_mass_tm_2018.GetMean(), h_mass_tm_2018.GetStdDev())
    
            counter += 1
    
        mass_title += " \\\\\n"
        mass_2016  += " \\\\\n"
        mass_2017  += " \\\\\n"
        mass_2018  += " \\\\\n"
        mass_tm_2016  += " \\\\\n"
        mass_tm_2017  += " \\\\\n"
        mass_tm_2018  += " \\\\\n"

        f.write("{\n\\renewcommand{\\arraystretch}{1.0}\n")
        f.write("\\begin{center}\n")
        f.write("\\begin{small}\n")
        f.write("\captionof{table}{Mass of %s candidates with various hypothetical tprime masses for three years}\n" % obj)
        f.write("\\begin{tabular}{ccccccccccc}\n")
        f.write("\hline\hline\n")
        f.write(mass_title)
        f.write("\hline\n")
        f.write(mass_2016)
        f.write(mass_tm_2016)
        f.write("\hline\n")
        f.write(mass_2017)
        f.write(mass_tm_2017)
        f.write("\hline\n")
        f.write(mass_2018)
        f.write(mass_tm_2018)
        f.write("\hline\hline\n")
        f.write("\end{tabular}\n")
        f.write("\end{small}\n")
        f.write("\end{center}\n")
        f.write("}\n\n")
    
    f.close()

def make_table_reco_mass(name_tex_file, version, years, masses):
    f = open(name_tex_file, "w")
    
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
