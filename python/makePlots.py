#!/usr/bin/env python2
import os
import glob
import toolbox
import ROOT
ROOT.gROOT.SetBatch(True)

os.chdir("./plots")
rootfiles = glob.glob("hist_*root")

for file in rootfiles:
    print file
    era = file.split('_')[3]
    mass = file.split('_')[2]
    tag = era + "_signal_" + mass

    fin = ROOT.TFile.Open(file, "R")
    
    h_mass_diphoton    = fin.Get("h_mass_diphoton"    )
    h_mass_diphoton_v2 = fin.Get("h_mass_diphoton_v2" )
    h_mass_wboson      = fin.Get("h_mass_wboson"      )
    h_mass_top         = fin.Get("h_mass_top"         )
    h_mass_gen_wboson  = fin.Get("h_mass_gen_wboson"  )
    h_mass_gen_top     = fin.Get("h_mass_gen_top"     )
    h_mass_tm_wboson   = fin.Get("h_mass_tm_wboson"   )
    h_mass_tm_top      = fin.Get("h_mass_tm_top"      )
    h_mass_tprime      = fin.Get("h_mass_tprime"      )
    
    toolbox.make_plot(h_mass_diphoton    , "h_mass_diphoton_%s.pdf"     %  tag )
    toolbox.make_plot(h_mass_diphoton_v2 , "h_mass_diphoton_v2_%s.pdf"  %  tag )
    toolbox.make_plot(h_mass_wboson      , "h_mass_wboson_%s.pdf"       %  tag )
    toolbox.make_plot(h_mass_top         , "h_mass_top_%s.pdf"          %  tag )
    toolbox.make_plot(h_mass_gen_wboson  , "h_mass_gen_wboson_%s.pdf"   %  tag )
    toolbox.make_plot(h_mass_gen_top     , "h_mass_gen_top_%s.pdf"      %  tag )
    toolbox.make_plot(h_mass_tm_wboson   , "h_mass_tm_wboson_%s.pdf"    %  tag )
    toolbox.make_plot(h_mass_tm_top      , "h_mass_tm_top_%s.pdf"       %  tag )
    toolbox.make_plot(h_mass_tprime      , "h_mass_tprime_%s.pdf"       %  tag )
    
    toolbox.make_plot_2D(h_mass_wboson , h_mass_gen_wboson , "h_genReco_mass_wboson_%s.pdf"  %  tag )
    toolbox.make_plot_2D(h_mass_top    , h_mass_gen_top    , "h_genReco_mass_top_%s.pdf"     %  tag )
    toolbox.make_plot_2D(h_mass_wboson , h_mass_tm_wboson  , "h_tmReco_mass_wboson_%s.pdf"   %  tag )
    toolbox.make_plot_2D(h_mass_top    , h_mass_tm_top     , "h_tmReco_mass_top_%s.pdf"      %  tag )
