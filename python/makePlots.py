#!/usr/bin/env python2
import os
import subprocess
import datetime
import glob
import toolbox
import ROOT
ROOT.gROOT.SetBatch(True)

os.chdir("./plots")
rootfiles = glob.glob("hist_*root")

ext = "png"

for file in rootfiles:
    print file
    era = file.split('_')[3]
    year = era.split('a')[1]
    mass = file.split('_')[2]
    tag = era + "_signal_" + mass

    fin = ROOT.TFile.Open(file, "R")
    
    h_gen_pdgIds        = fin.Get("h_gen_pdgIds"        )
    h_mom_pdgIds        = fin.Get("h_mom_pdgIds"        )
    h_num_bquarks       = fin.Get("h_num_bquarks"       )
    h_num_wquarks       = fin.Get("h_num_wquarks"       )
    h_num_gen_particles = fin.Get("h_num_gen_particles" )
    h_mass_gen_wboson   = fin.Get("h_mass_gen_wboson"   )
    h_mass_gen_top      = fin.Get("h_mass_gen_top"      )
    h_num_jets          = fin.Get("h_num_jets"          )
    h_mass_diphoton     = fin.Get("h_mass_diphoton"     )
    h_mass_diphoton_v2  = fin.Get("h_mass_diphoton_v2"  )
    h_mass_wboson       = fin.Get("h_mass_wboson"       )
    h_mass_top          = fin.Get("h_mass_top"          )
    h_mass_tm_wboson    = fin.Get("h_mass_tm_wboson"    )
    h_mass_tm_top       = fin.Get("h_mass_tm_top"       )
    h_mass_tprime       = fin.Get("h_mass_tprime"       )
    h_mass_tm_tprime    = fin.Get("h_mass_tm_tprime"    )
    h_deltaR_wjets      = fin.Get("h_deltaR_wjets"      )
    h_ptRatio_partons   = fin.Get("h_ptRatio_partons"   )
    h_deltaR_partons    = fin.Get("h_deltaR_partons"    )
    h_chi2_value        = fin.Get("h_chi2_value"        )
    h_chi2_mass_wboson  = fin.Get("h_chi2_mass_wboson"  )
    h_chi2_mass_top     = fin.Get("h_chi2_mass_top"     )
    h_chi2_value        = fin.Get("h_chi2_value"        )
    h_chi2_cut_eff      = fin.Get("h_chi2_cut_eff"      )
    
    #------------------------------------------------- Make plots ---------------------------------------------------#
    #toolbox.make_plot(h_gen_pdgIds        , "h_gen_pdgIds_%s.%s"        %  (tag , ext) )
    #toolbox.make_plot(h_mom_pdgIds        , "h_mom_pdgIds_%s.%s"        %  (tag , ext) )
    #toolbox.make_plot(h_mass_diphoton_v2  , "h_mass_diphoton_v2_%s.%s"  %  (tag , ext) )
    toolbox.make_plot(h_num_bquarks       , "h_num_bquarks_%s.%s"       %  (tag , ext) )
    toolbox.make_plot(h_num_wquarks       , "h_num_wquarks_%s.%s"       %  (tag , ext) )
    toolbox.make_plot(h_num_gen_particles , "h_num_gen_particles_%s.%s" %  (tag , ext) )
    toolbox.make_plot(h_num_jets          , "h_num_jets_%s.%s"          %  (tag , ext) )
    toolbox.make_plot(h_mass_gen_wboson   , "h_mass_gen_wboson_%s.%s"   %  (tag , ext) )
    toolbox.make_plot(h_mass_gen_top      , "h_mass_gen_top_%s.%s"      %  (tag , ext) )
    toolbox.make_plot(h_mass_diphoton     , "h_mass_diphoton_%s.%s"     %  (tag , ext) )
    toolbox.make_plot(h_mass_wboson       , "h_mass_wboson_%s.%s"       %  (tag , ext) )
    toolbox.make_plot(h_mass_top          , "h_mass_top_%s.%s"          %  (tag , ext) )
    toolbox.make_plot(h_mass_tprime       , "h_mass_tprime_%s.%s"       %  (tag , ext) )
    toolbox.make_plot(h_mass_tm_wboson    , "h_mass_tm_wboson_%s.%s"    %  (tag , ext) )
    toolbox.make_plot(h_mass_tm_top       , "h_mass_tm_top_%s.%s"       %  (tag , ext) )
    toolbox.make_plot(h_mass_tm_tprime    , "h_mass_tm_tprime_%s.%s"    %  (tag , ext) )
    toolbox.make_plot(h_deltaR_wjets      , "h_deltaR_wjets_%s.%s"      %  (tag , ext) )
    toolbox.make_plot(h_chi2_value        , "h_chi2_value_%s.%s"        %  (tag , ext) , "hist" , False , True)
    toolbox.make_plot(h_chi2_cut_eff      , "h_chi2_cut_eff_%s.%s"      %  (tag , ext) , "e1p", True )
    toolbox.make_plot(h_chi2_mass_wboson  , "h_chi2_mass_wboson_%s.%s"  %  (tag , ext) , "colz" , True )
    toolbox.make_plot(h_chi2_mass_top     , "h_chi2_mass_top_%s.%s"     %  (tag , ext) , "colz" , True )

    toolbox.make_plot_cut_efficiency(h_ptRatio_partons   , "h_ptRatio_partons_%s.%s"   %  (tag , ext), 1.0 )
    toolbox.make_plot_cut_efficiency(h_deltaR_partons    , "h_deltaR_partons_%s.%s"    %  (tag , ext), 0.4 )
    
    toolbox.make_plot_two_hists(h_mass_wboson , "Minimum chi-2" , h_mass_tm_wboson  , "Truth-Matched" , year , mass , "h_tmReco_mass_wboson_%s.%s"   %  (tag , ext) )
    toolbox.make_plot_two_hists(h_mass_top    , "Minimum chi-2" , h_mass_tm_top     , "Truth-Matched" , year , mass , "h_tmReco_mass_top_%s.%s"      %  (tag , ext) )
    toolbox.make_plot_two_hists(h_mass_tprime , "Minimum chi-2" , h_mass_tm_tprime  , "Truth-Matched" , year , mass , "h_tmReco_mass_tprime_%s.%s"   %  (tag , ext) )



def prepare_index_php(target):
    index_php = "/eos/user/y/ykao/www/index.php"
    subprocess.call("mkdir -p %s; cp -p %s %s;" % (target, index_php, target), shell=True)

def copy_files(keyword, target):
    prepare_index_php(target)
    png_files = glob.glob(keyword)
    for png in png_files:
        subprocess.call("cp %s %s" % (png, target), shell=True)

def move_files(keyword, target):
    prepare_index_php(target)
    png_files = glob.glob(keyword)
    for png in png_files:
        subprocess.call("mv %s %s" % (png, target), shell=True)



today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 
target = "/eos/user/y/ykao/www/plots/%s" % (datetime_tag)
prepare_index_php(target)

copy_files("*num*png"      , target + "/06_Multiplicity" )
copy_files("*chi2*png"     , target + "/07_Xtt0"         )

move_files("*diphoton*png" , target + "/01_Diphoton"     )
move_files("*wboson*png"   , target + "/02_Wboson"       )
move_files("*top*png"      , target + "/03_Top"          )
move_files("*tprime*png"   , target + "/04_Tprime"       )
move_files("*gen*png"      , target + "/05_MCtruth"      )
move_files("*quark*png"    , target + "/05_MCtruth"      )
move_files("*parton*png"   , target + "/05_MCtruth"      )
#move_files("*pdgId*png"    , target + "/05_MCtruth"      )
move_files("*png"          , target + "/08_Others"       )

subprocess.call("echo %s; ls -ld %s;" % (target, target), shell=True)
