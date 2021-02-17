#!/usr/bin/env python2
import os
import subprocess
import datetime
import glob
import array
import math
import toolbox
import transfer_helper
import ROOT
ROOT.gROOT.SetBatch(True)

# options
trend_wrt_tprime_mass = False
check_mass_diphoton = True
check_mass_pt_dependency = False 
make_all_plots = False
make_individual_plots = False
os.chdir("./plots") #os.chdir("./stashed/plots_20210213/")

# common
ext = "png"
today = datetime.datetime.today()
datetime_tag = today.strftime("%Y%m%d") 
target = "/eos/user/y/ykao/www/plots/%s" % (datetime_tag)
transfer_helper.prepare_index_php(target)
    


if trend_wrt_tprime_mass:
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    nbins  = 10 
    masses = array.array( 'f', [600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200 ] )
    width  = array.array( 'f', [0., 0., 0., 0., 0., 0., 0., 0., 0., 0.] )

    # std hist{{{
    # 2016 std hist
    masses_wboson = array.array( 'f', [81.20, 81.35, 81.40, 81.62, 81.58, 82.32, 82.95, 83.65, 84.18, 84.63 ] )
    masses_top    = array.array( 'f', [169.31, 169.54, 169.74, 170.07, 170.11, 171.25, 172.51, 173.77, 174.66, 175.73 ] )
    error_wboson  = array.array( 'f', [11.41, 11.41, 11.39, 11.36, 11.41, 11.50, 11.55, 11.92, 12.54, 13.02 ] )
    error_top     = array.array( 'f', [19.32, 19.23, 19.04, 18.88, 18.95, 18.50, 18.37, 18.14, 18.49, 18.31 ] )
    graph_stdhist_2016_wboson = ROOT.TGraphErrors(nbins, masses, masses_wboson, width, error_wboson)
    graph_stdhist_2016_top = ROOT.TGraphErrors(nbins, masses, masses_top, width, error_top)

    # 2017 std hist
    masses_wboson = array.array( 'f', [81.39, 81.50, 81.58, 81.86, 81.94, 82.49, 83.05, 83.74, 84.26, 84.84 ] )
    masses_top    = array.array( 'f', [169.07, 169.05, 169.43, 169.84, 169.95, 171.03, 172.02, 173.32, 174.34, 175.41 ] )
    error_wboson  = array.array( 'f', [11.75, 11.77, 11.79, 11.74, 11.76, 11.80, 11.97, 12.23, 12.69, 13.48 ] )
    error_top     = array.array( 'f', [19.81, 19.75, 19.77, 19.52, 19.39, 19.05, 18.95, 18.69, 18.61, 18.96 ] )
    graph_stdhist_2017_wboson = ROOT.TGraphErrors(nbins, masses, masses_wboson, width, error_wboson)
    graph_stdhist_2017_top = ROOT.TGraphErrors(nbins, masses, masses_top, width, error_top)

    # 2018 std hist
    masses_wboson = array.array( 'f', [81.36, 81.42, 81.49, 81.65, 81.80, 82.38, 83.03, 83.69, 84.17, 84.82 ] )
    masses_top    = array.array( 'f', [168.89, 169.08, 169.22, 169.53, 169.89, 170.84, 172.02, 173.17, 174.17, 175.42 ] )
    error_wboson  = array.array( 'f', [11.79, 11.69, 11.75, 11.72, 11.66, 11.71, 11.94, 12.15, 12.61, 13.38 ] )
    error_top     = array.array( 'f', [19.57, 19.55, 19.62, 19.38, 19.25, 18.94, 18.91, 18.57, 18.60, 18.69 ] )
    graph_stdhist_2018_wboson = ROOT.TGraphErrors(nbins, masses, masses_wboson, width, error_wboson)
    graph_stdhist_2018_top = ROOT.TGraphErrors(nbins, masses, masses_top, width, error_top)
    #}}}
    # fit mode{{{
    # 2016
    masses_wboson = array.array( 'f', [85.07, 83.86, 85.50, 83.74, 81.51, 83.17, 86.26, 86.71, 84.90, 85.76 ] )
    masses_top    = array.array( 'f', [170.83, 170.88, 171.03, 173.27, 170.88, 174.11, 171.53, 168.21, 178.17, 178.48 ] )
    error_wboson  = array.array( 'f', [11.49, 11.11, 11.43, 10.90, 10.95, 10.73, 11.04, 11.00, 10.86, 11.07 ] )
    error_top     = array.array( 'f', [19.11, 18.98, 18.73, 18.62, 18.57, 18.05, 17.87, 18.62, 17.74, 17.39 ] )
    graph_fitmode_2016_wboson = ROOT.TGraphErrors(nbins, masses, masses_wboson, width, error_wboson)
    graph_fitmode_2016_top = ROOT.TGraphErrors(nbins, masses, masses_top, width, error_top)
    
    # 2017
    masses_wboson = array.array( 'f', [89.71, 80.49, 85.59, 80.86, 82.01, 83.99, 79.31, 84.33, 87.15, 84.90 ] )
    masses_top    = array.array( 'f', [166.10, 172.73, 178.71, 169.91, 168.47, 172.41, 174.24, 174.67, 179.26, 173.78 ] )
    error_wboson  = array.array( 'f', [14.21, 11.49, 11.92, 11.43, 11.27, 11.14, 12.02, 11.00, 11.49, 11.37 ] )
    error_top     = array.array( 'f', [19.92, 19.72, 21.59, 19.40, 19.32, 18.59, 18.42, 17.86, 18.28, 18.05 ] )
    graph_fitmode_2017_wboson = ROOT.TGraphErrors(nbins, masses, masses_wboson, width, error_wboson)
    graph_fitmode_2017_top = ROOT.TGraphErrors(nbins, masses, masses_top, width, error_top)
    
    # 2018
    masses_wboson = array.array( 'f', [81.79, 79.64, 85.10, 78.41, 85.22, 81.24, 82.53, 84.03, 84.71, 84.75] )
    masses_top    = array.array( 'f', [171.50, 164.41, 170.91, 171.21, 165.35, 167.28, 177.46, 172.35, 176.27, 175.01] )
    error_wboson  = array.array( 'f', [11.73, 11.60, 11.72, 12.04, 11.52, 11.28, 11.17, 11.07, 11.15, 11.42] )
    error_top     = array.array( 'f', [19.56, 20.04, 19.35, 19.04, 19.75, 19.08, 18.87, 17.86, 17.76, 17.78] )
    graph_fitmode_2018_wboson = ROOT.TGraphErrors(nbins, masses, masses_wboson, width, error_wboson)
    graph_fitmode_2018_top = ROOT.TGraphErrors(nbins, masses, masses_top, width, error_top)
    #}}}

    toolbox.set_tgraph(graph_stdhist_2016_top, 100., 260, ROOT.kGreen+4)
    toolbox.set_tgraph(graph_stdhist_2017_top, 100., 260, ROOT.kBlue)
    toolbox.set_tgraph(graph_stdhist_2018_top, 100., 260, ROOT.kRed)
    toolbox.set_tgraph(graph_stdhist_2016_wboson, 40., 150, ROOT.kGreen+4)
    toolbox.set_tgraph(graph_stdhist_2017_wboson, 40., 150, ROOT.kBlue)
    toolbox.set_tgraph(graph_stdhist_2018_wboson, 40., 150, ROOT.kRed)

    toolbox.set_tgraph(graph_fitmode_2016_top, 100., 260, ROOT.kGreen+4)
    toolbox.set_tgraph(graph_fitmode_2017_top, 100., 260, ROOT.kBlue)
    toolbox.set_tgraph(graph_fitmode_2018_top, 100., 260, ROOT.kRed)
    toolbox.set_tgraph(graph_fitmode_2016_wboson, 40., 150, ROOT.kGreen+4)
    toolbox.set_tgraph(graph_fitmode_2017_wboson, 40., 150, ROOT.kBlue)
    toolbox.set_tgraph(graph_fitmode_2018_wboson, 40., 150, ROOT.kRed)

    # std hist
    title = "Std. stat. of truth-matched W candidate; Hypothesized T' mass (GeV); Mass of W candidate (GeV)"
    toolbox.make_tgraph(graph_stdhist_2016_wboson, graph_stdhist_2017_wboson, graph_stdhist_2018_wboson, 80.379, title, "std_hist_wboson.png")
    title = "Std. stat. of truth-matched top candidate; Hypothesized T' mass (GeV); Mass of top candidate (GeV)"
    toolbox.make_tgraph(graph_stdhist_2016_top, graph_stdhist_2017_top, graph_stdhist_2018_top, 172.76, title, "std_hist_top.png")

    # two gaussian
    title = "Fit result of truth-matched W candidate; Hypothesized T' mass (GeV); Mass of W candidate (GeV)"
    toolbox.make_tgraph(graph_fitmode_2016_wboson, graph_fitmode_2017_wboson, graph_fitmode_2018_wboson, 80.379, title, "fit_mode_wboson.png")
    title = "Fit result of truth-matched top candidate; Hypothesized T' mass (GeV); Mass of top candidate (GeV)"
    toolbox.make_tgraph(graph_fitmode_2016_top, graph_fitmode_2017_top, graph_fitmode_2018_top, 172.76, title, "fit_mode_top.png")


    target = "/eos/user/y/ykao/www/plots/"
    subprocess.call("mv fit_mode_*.png %s; ls -ld %s;" % (target, target), shell=True)
    subprocess.call("mv std_hist_*.png %s; ls -ld %s;" % (target, target), shell=True)



if check_mass_diphoton:
    # future study: fit with gaussian + DCB and then check mass trend !!
    masses = [ 600, 700, 800, 900, 1000, 1100, 1200 ]
    colors = [ ROOT.kRed-10, ROOT.kRed-7, ROOT.kRed-0, ROOT.kRed+1, ROOT.kRed+2, ROOT.kRed+3, ROOT.kBlack ]
    styles = [1, 1, 1, 1, 1, 1, 1 ]
    texts = []
    xytitles = ["Diphoton invariant mass GeV /^{}c^{2}", "p.d.f."]
    #colors = [ ROOT.kBlue-10, ROOT.kBlue-9, ROOT.kBlue-7, ROOT.kBlue-4, ROOT.kBlue+0, ROOT.kBlue+1, ROOT.kBlue+2, ROOT.kBlue+3, ROOT.kBlue+4 ]
    #colors = [ ROOT.kBlack, ROOT.kRed+3, ROOT.kRed+2, ROOT.kRed+1, ROOT.kRed-0, ROOT.kRed-7, ROOT.kRed-10 ]
    #xytitles = ["Diphoton invariant mass GeV /^{}c^{2}", "Entries"]

    fin_collection = []
    for mass in masses:
        rootfile = "hist_TprimeBToTH_M-" + str(mass) + "_Era2017_v2p4.root"
        fin = ROOT.TFile.Open(rootfile, "R")
        fin_collection.append(fin)
        print rootfile

        text = "M_{T'} = %d" % mass
        texts.append(text)

    hists = []
    for fin in fin_collection:
        h = fin.Get("h_mass_diphoton")
        hists.append(h)

    toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_mass_diphoton_check.%s" % ext, 2017, "hist", "l", False, [0.60, 0.20], [0.20, 0.60], True)
    transfer_helper.move_files("*mass_diphoton*png", target)



if check_mass_pt_dependency:
    fin_collection = []
    #masses = [ 600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200 ]
    #colors = [ ROOT.kBlue-10, ROOT.kBlue-8, ROOT.kBlue-9, ROOT.kBlue-7, ROOT.kBlue-4, ROOT.kBlue+0, ROOT.kBlue+1, ROOT.kBlue+2, ROOT.kBlue+3, ROOT.kBlue+4 ]
    masses = [ 600, 700, 800, 900, 1000, 1100, 1200 ]
    colors = [ ROOT.kBlue-10, ROOT.kBlue-9, ROOT.kBlue-7, ROOT.kBlue-4, ROOT.kBlue+0, ROOT.kBlue+1, ROOT.kBlue+2, ROOT.kBlue+3, ROOT.kBlue+4 ]

    for mass in masses:
        rootfile = "hist_TprimeBToTH_M-" + str(mass) + "_Era2017_v2p4.root"
        fin = ROOT.TFile.Open(rootfile, "R")
        fin_collection.append(fin)
        print rootfile

    toolbox.make_mass_pt_2D_plot("top", 40, 0, 1000, 32, 100, 260, fin_collection, masses)
    toolbox.make_mass_pt_2D_plot("wboson", 40, 0, 1000, 40, 40, 130, fin_collection, masses)

    # top mass w/ pt cut
    toolbox.make_plot_from_ntuple_from_various_files("top", "mass", 32, 100, 260, fin_collection, masses, colors, 0, 0)
    toolbox.make_plot_from_ntuple_from_various_files("top", "mass", 32, 100, 260, fin_collection, masses, colors, 100, 200)
    toolbox.make_plot_from_ntuple_from_various_files("top", "mass", 32, 100, 260, fin_collection, masses, colors, 200, 300)
    toolbox.make_plot_from_ntuple_from_various_files("top", "mass", 32, 100, 260, fin_collection, masses, colors, 300, 400)
    toolbox.make_plot_from_ntuple_from_various_files("top", "mass", 32, 100, 260, fin_collection, masses, colors, 400, 500)
    toolbox.make_plot_from_ntuple_from_various_files("top", "pt", 40, 0, 1000, fin_collection, masses, colors, 0, 0)
    # wboson mass w/ pt cut
    toolbox.make_plot_from_ntuple_from_various_files("wboson", "mass", 40, 40, 130, fin_collection, masses, colors, 0, 0)
    toolbox.make_plot_from_ntuple_from_various_files("wboson", "mass", 40, 40, 130, fin_collection, masses, colors, 100, 200)
    toolbox.make_plot_from_ntuple_from_various_files("wboson", "pt", 40, 0, 1000, fin_collection, masses, colors, 0, 0)

    check_pt_all_mass_points = False
    if check_pt_all_mass_points: #{{{
        # top pt
        max_scope = 0.
        counter = 0

        for fin in fin_collection:
            h_pt_top = fin.Get( "h_pt_top" )
            toolbox.set_hist_and_draw(h_pt_top, masses[counter], colors[counter], legend, counter)
            counter += 1
                
        legend.Draw()
        ROOT.gPad.SetTicky()
        toolbox.set_preliminary_tlatex(2017)
        c1.SaveAs("h_tm_pt_top_Era2017.png")

        # wboson pt
        max_scope = 0.
        counter = 0

        for fin in fin_collection:
            h_pt_wboson = fin.Get( "h_pt_wboson" )
            toolbox.set_hist_and_draw(h_pt_wboson, masses[counter], colors[counter], legend, counter)
            counter += 1
                
        legend.Draw()
        ROOT.gPad.SetTicky()
        toolbox.set_preliminary_tlatex(2017)
        c1.SaveAs("h_tm_pt_wboson_Era2017.png")
    #}}}

    # place png file to personal web
    transfer_helper.move_files("*wboson*png" , target )
    transfer_helper.move_files("*top*png"    , target )
    #transfer_helper.move_files("*wboson*png" , target + "/02_Wboson"       )
    #transfer_helper.move_files("*top*png"    , target + "/03_Top"          )



if make_all_plots:
    rootfiles = glob.glob("hist_*root")
    #rootfiles = glob.glob("hist_*1000*2017*root")
    
    for file in rootfiles:
        print file
        era = file.split('_')[3]
        year = era.split('a')[1]
        mass = file.split('_')[2]
        tag = era + "_signal_" + mass
    
        fin = ROOT.TFile.Open(file, "R")
        
        #------------------------------------------------- Histograms -------------------------------------------------#
        h_gen_pdgIds                         = fin.Get("h_gen_pdgIds"                         )
        h_mom_pdgIds                         = fin.Get("h_mom_pdgIds"                         )
        h_num_bquarks                        = fin.Get("h_num_bquarks"                        )
        h_num_wquarks                        = fin.Get("h_num_wquarks"                        )
        h_num_gen_particles                  = fin.Get("h_num_gen_particles"                  )
        h_mass_wboson_gen                    = fin.Get("h_mass_wboson_gen"                    )
        h_mass_top_gen                       = fin.Get("h_mass_top_gen"                       )
        h_num_jets                           = fin.Get("h_num_jets"                           )
        h_mass_diphoton                      = fin.Get("h_mass_diphoton"                      )
        h_mass_diphoton_v2                   = fin.Get("h_mass_diphoton_v2"                   )
        h_mass_wboson                        = fin.Get("h_mass_wboson"                        )
        h_mass_top                           = fin.Get("h_mass_top"                           )
        h_mass_tprime                        = fin.Get("h_mass_tprime"                        )
        h_mass_wboson_tm                     = fin.Get("h_mass_wboson_tm"                     )
        h_mass_top_tm                        = fin.Get("h_mass_top_tm"                        )
        h_pt_wboson_tm                       = fin.Get("h_pt_wboson_tm"                       )
        h_pt_top_tm                          = fin.Get("h_pt_top_tm"                          )
        h_mass_tprime_tm                     = fin.Get("h_mass_tprime_tm"                     )
        h_mass_wboson_cov                    = fin.Get("h_mass_wboson_cov"                    )
        h_mass_top_cov                       = fin.Get("h_mass_top_cov"                       )
        h_mass_tprime_cov                    = fin.Get("h_mass_tprime_cov"                    )
        h_mass_wboson_subspace               = fin.Get("h_mass_wboson_subspace"               )
        h_mass_top_subspace                  = fin.Get("h_mass_top_subspace"                  )
        h_mass_tprime_subspace               = fin.Get("h_mass_tprime_subspace"               )
        h_mass_wboson_cov_subspace           = fin.Get("h_mass_wboson_cov_subspace"           )
        h_mass_top_cov_subspace              = fin.Get("h_mass_top_cov_subspace"              )
        h_mass_tprime_cov_subspace           = fin.Get("h_mass_tprime_cov_subspace"           )
        h_deltaR_wjets                       = fin.Get("h_deltaR_wjets"                       )
        h_ptRatio_partons                    = fin.Get("h_ptRatio_partons"                    )
        h_deltaR_partons                     = fin.Get("h_deltaR_partons"                     )
        h_chi2_value                         = fin.Get("h_chi2_value"                         )
        h_chi2_mass_wboson                   = fin.Get("h_chi2_mass_wboson"                   )
        h_chi2_mass_top                      = fin.Get("h_chi2_mass_top"                      )
        h_chi2_value                         = fin.Get("h_chi2_value"                         )
        h_chi2_cut_eff                       = fin.Get("h_chi2_cut_eff"                       )
        h_chi2_cut_eff_subspace                       = fin.Get("h_chi2_cut_eff_subspace"                       )
        h_cov_chi2_value                     = fin.Get("h_cov_chi2_value"                     )
        h_cov_chi2_cut_eff                   = fin.Get("h_cov_chi2_cut_eff"                   )
        h_cov_chi2_cut_eff_subspace                   = fin.Get("h_cov_chi2_cut_eff_subspace"                   )
        h_cov_chi2_mass_wboson               = fin.Get("h_cov_chi2_mass_wboson"               )
        h_cov_chi2_mass_top                  = fin.Get("h_cov_chi2_mass_top"                  )
        h_numerator_vs_chi2Cut               = fin.Get("h_numerator_vs_chi2Cut"               )
        h_denominator_vs_chi2Cut             = fin.Get("h_denominator_vs_chi2Cut"             )
        h_cov_numerator_vs_chi2Cut           = fin.Get("h_cov_numerator_vs_chi2Cut"           )
        h_cov_denominator_vs_chi2Cut         = fin.Get("h_cov_denominator_vs_chi2Cut"         )
        h_numerator_vs_chi2Bins              = fin.Get("h_numerator_vs_chi2Bins"              )
        h_denominator_vs_chi2Bins            = fin.Get("h_denominator_vs_chi2Bins"            )
        h_cov_numerator_vs_chi2Bins          = fin.Get("h_cov_numerator_vs_chi2Bins"          )
        h_cov_denominator_vs_chi2Bins        = fin.Get("h_cov_denominator_vs_chi2Bins"        )
        h_matchingEff_vs_chi2Cut             = fin.Get("h_matchingEff_vs_chi2Cut"             )
        h_cov_matchingEff_vs_chi2Cut         = fin.Get("h_cov_matchingEff_vs_chi2Cut"         )
        h_matchingEff_vs_chi2Bins            = fin.Get("h_matchingEff_vs_chi2Bins"            )
        h_cov_matchingEff_vs_chi2Bins        = fin.Get("h_cov_matchingEff_vs_chi2Bins"        )
        h_matchingEff_vs_chi2Cut             = fin.Get("h_matchingEff_vs_chi2Cut"             )
        h_cov_matchingEff_vs_chi2Cut         = fin.Get("h_cov_matchingEff_vs_chi2Cut"         )
        h_matchingEff_vs_chi2Bins            = fin.Get("h_matchingEff_vs_chi2Bins"            )
        h_cov_matchingEff_vs_chi2Bins        = fin.Get("h_cov_matchingEff_vs_chi2Bins"        )
        h_matchingEff_vs_chi2Cut_rebase      = fin.Get("h_matchingEff_vs_chi2Cut_rebase"      )
        h_cov_matchingEff_vs_chi2Cut_rebase  = fin.Get("h_cov_matchingEff_vs_chi2Cut_rebase"  )
        h_matchingEff_vs_chi2Bins_rebase     = fin.Get("h_matchingEff_vs_chi2Bins_rebase"     )
        h_cov_matchingEff_vs_chi2Bins_rebase = fin.Get("h_cov_matchingEff_vs_chi2Bins_rebase" )
        h_chi2_value_subspace                = fin.Get("h_chi2_value_subspace"                )
        h_cov_chi2_value_subspace            = fin.Get("h_cov_chi2_value_subspace"            )

        nt_chi2_matchingEff_vs_cutEff              = fin.Get("nt_chi2_matchingEff_vs_cutEff")
        nt_chi2_matchingEff_vs_cutEff_subspace     = fin.Get("nt_chi2_matchingEff_vs_cutEff_subspace")
        nt_cov_chi2_matchingEff_vs_cutEff          = fin.Get("nt_cov_chi2_matchingEff_vs_cutEff")
        nt_cov_chi2_matchingEff_vs_cutEff_subspace = fin.Get("nt_cov_chi2_matchingEff_vs_cutEff_subspace")


        #------------------------------------------------- Make plots ---------------------------------------------------#
        if make_individual_plots:
            #toolbox.make_plot(h_gen_pdgIds        , "h_gen_pdgIds_%s.%s"        %  (tag , ext) )
            #toolbox.make_plot(h_mom_pdgIds        , "h_mom_pdgIds_%s.%s"        %  (tag , ext) )
            #toolbox.make_plot(h_mass_diphoton_v2  , "h_mass_diphoton_v2_%s.%s"  %  (tag , ext) )
            #toolbox.make_plot(h_numerator_vs_chi2Cut           , "h_numerator_vs_chi2Cut_%s.%s"       %  (tag , ext)   , "e1p"  , True )
            #toolbox.make_plot(h_denominator_vs_chi2Cut         , "h_denominator_vs_chi2Cut_%s.%s"     %  (tag , ext)   , "e1p"  , True )
            #toolbox.make_plot(h_cov_numerator_vs_chi2Cut       , "h_cov_numerator_vs_chi2Cut_%s.%s"   %  (tag , ext)   , "e1p"  , True )
            #toolbox.make_plot(h_cov_denominator_vs_chi2Cut     , "h_cov_denominator_vs_chi2Cut_%s.%s" %  (tag , ext)   , "e1p"  , True )
            #toolbox.make_plot_matching_efficiency(h_matchingEff_vs_chi2Cut       , "h_matchingEff_vs_chi2Cut_%s.%s"       % (tag  , ext)  , "e1p"  , True )
            #toolbox.make_plot_matching_efficiency(h_cov_matchingEff_vs_chi2Cut   , "h_cov_matchingEff_vs_chi2Cut_%s.%s"   % (tag  , ext)  , "e1p"  , True )
            #toolbox.make_plot_matching_efficiency(h_matchingEff_vs_chi2Bins      , "h_matchingEff_vs_chi2Bins_%s.%s"      % (tag  , ext)  , "e1p"  , True )
            #toolbox.make_plot_matching_efficiency(h_cov_matchingEff_vs_chi2Bins  , "h_cov_matchingEff_vs_chi2Bins_%s.%s"  % (tag  , ext)  , "e1p"  , True )
            toolbox.make_plot(h_num_bquarks              , "h_num_bquarks_%s.%s"               % (tag , ext) )
            toolbox.make_plot(h_num_wquarks              , "h_num_wquarks_%s.%s"               % (tag , ext) )
            toolbox.make_plot(h_num_gen_particles        , "h_num_gen_particles_%s.%s"         % (tag , ext) )
            toolbox.make_plot(h_num_jets                 , "h_num_jets_%s.%s"                  % (tag , ext) )
            toolbox.make_plot(h_mass_wboson_gen          , "h_mass_wboson_gen_%s.%s"           % (tag , ext) )
            toolbox.make_plot(h_mass_top_gen             , "h_mass_top_gen_%s.%s"              % (tag , ext) )
            toolbox.make_plot(h_mass_diphoton            , "h_mass_diphoton_%s.%s"             % (tag , ext) )
            toolbox.make_plot(h_mass_wboson              , "h_mass_wboson_%s.%s"               % (tag , ext) )
            toolbox.make_plot(h_mass_top                 , "h_mass_top_%s.%s"                  % (tag , ext) )
            toolbox.make_plot(h_mass_tprime              , "h_mass_tprime_%s.%s"               % (tag , ext) )
            toolbox.make_plot(h_mass_wboson_tm           , "h_mass_wboson_tm_%s.%s"            % (tag , ext) )
            toolbox.make_plot(h_mass_top_tm              , "h_mass_top_tm_%s.%s"               % (tag , ext) )
            toolbox.make_plot(h_pt_wboson_tm             , "h_pt_wboson_tm_%s.%s"              % (tag , ext) )
            toolbox.make_plot(h_pt_top_tm                , "h_pt_top_tm_%s.%s"                 % (tag , ext) )
            toolbox.make_plot(h_mass_tprime_tm           , "h_mass_tprime_tm_%s.%s"            % (tag , ext) )
            toolbox.make_plot(h_mass_tprime_cov          , "h_mass_tprime_cov_%s.%s"           % (tag , ext) )
            toolbox.make_plot(h_mass_top_cov             , "h_mass_top_cov_%s.%s"              % (tag , ext) )
            toolbox.make_plot(h_mass_wboson_cov          , "h_mass_wboson_cov_%s.%s"           % (tag , ext) )
            toolbox.make_plot(h_mass_wboson_subspace     , "h_mass_wboson_subspace_%s.%s"      % (tag , ext) )
            toolbox.make_plot(h_mass_top_subspace        , "h_mass_top_subspace_%s.%s"         % (tag , ext) )
            toolbox.make_plot(h_mass_tprime_subspace     , "h_mass_tprime_subspace_%s.%s"      % (tag , ext) )
            toolbox.make_plot(h_mass_wboson_cov_subspace , "h_mass_wboson_cov_subspace_%s.%s"  % (tag , ext) )
            toolbox.make_plot(h_mass_top_cov_subspace    , "h_mass_top_cov_subspace_%s.%s"     % (tag , ext) )
            toolbox.make_plot(h_mass_tprime_cov_subspace , "h_mass_tprime_cov_subspace_%s.%s"  % (tag , ext) )
            toolbox.make_plot(h_deltaR_wjets             , "h_deltaR_wjets_%s.%s"              % (tag , ext) )
            toolbox.make_plot(h_chi2_value               , "h_chi2_value_%s.%s"                % (tag , ext)   , "hist" , False  , True)
            toolbox.make_plot(h_chi2_value_subspace      , "h_chi2_value_subspace_%s.%s"       % (tag , ext)   , "hist" , False  , True)
            toolbox.make_plot(h_cov_chi2_value           , "h_cov_chi2_value_%s.%s"            % (tag , ext)   , "hist" , False  , True)
            toolbox.make_plot(h_cov_chi2_value_subspace  , "h_cov_chi2_value_subspace_%s.%s"   % (tag , ext)   , "hist" , False  , True)
            toolbox.make_plot(h_chi2_cut_eff             , "h_chi2_cut_eff_%s.%s"              % (tag , ext)   , "e1p"  , True )
            toolbox.make_plot(h_chi2_mass_wboson         , "h_chi2_mass_wboson_%s.%s"          % (tag , ext)   , "colz" , True )
            toolbox.make_plot(h_chi2_mass_top            , "h_chi2_mass_top_%s.%s"             % (tag , ext)   , "colz" , True )
            toolbox.make_plot(h_cov_chi2_cut_eff         , "h_cov_chi2_cut_eff_%s.%s"          % (tag , ext)   , "e1p"  , True )
            toolbox.make_plot(h_cov_chi2_mass_wboson     , "h_cov_chi2_mass_wboson_%s.%s"      % (tag , ext)   , "colz" , True )
            toolbox.make_plot(h_cov_chi2_mass_top        , "h_cov_chi2_mass_top_%s.%s"         % (tag , ext)   , "colz" , True )


        # diphoton inv mass
        toolbox.make_plot(h_mass_diphoton            , "h_mass_diphoton_%s.%s"             % (tag , ext) )

        # cut efficiency related
        toolbox.make_plot_cut_efficiency(h_deltaR_partons  , "h_deltaR_partons_%s.%s"  % (tag , ext)   , 0.4 )
        toolbox.make_plot_cut_efficiency(h_ptRatio_partons , "h_ptRatio_partons_%s.%s" % (tag , ext)   , 0.5 )
    

        # matching efficiency related
        ### figures for check
        colors = [ROOT.kBlue, ROOT.kBlue, ROOT.kRed, ROOT.kRed]
        styles = [1, 2, 1, 2]
        texts = [ "numerator", "denominator", "cov_numerator", "cov_denominator" ]

        xytitles = ["chi-2 cut values", "Entries"]
        hists = [ h_numerator_vs_chi2Cut, h_denominator_vs_chi2Cut, h_cov_numerator_vs_chi2Cut, h_cov_denominator_vs_chi2Cut ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_matchingEff_chi2Cut_check_%s.%s" % (tag, ext))

        xytitles = ["chi-2 values", "Entries"]
        hists = [ h_numerator_vs_chi2Bins, h_denominator_vs_chi2Bins, h_cov_numerator_vs_chi2Bins, h_cov_denominator_vs_chi2Bins ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_matchingEff_chi2Bins_check_%s.%s" % (tag, ext))
    
        ### figures for presentation
        xytitles = ["Selection efficiency", "Matching efficiency"]
        labels = ["w/o covariance matrix", "with covariance matrix"]

        nts = [nt_chi2_matchingEff_vs_cutEff, nt_cov_chi2_matchingEff_vs_cutEff]
        histnames = ["h_chi2_matchingEff_vs_cutEff", "h_cov_chi2_matchingEff_vs_cutEff"]
        toolbox.make_2d_plot_from_ntuple(nts, xytitles, labels, histnames, "matchingEff:cutEff" , "" , 100 , 0. , 1. , 100 , 0. , 1.)

        nts = [nt_chi2_matchingEff_vs_cutEff_subspace, nt_cov_chi2_matchingEff_vs_cutEff_subspace]
        histnames = ["h_chi2_matchingEff_vs_cutEff_subspace", "h_cov_chi2_matchingEff_vs_cutEff_subspace"]
        toolbox.make_2d_plot_from_ntuple(nts, xytitles, labels, histnames, "matchingEff:cutEff" , "" , 100 , 0. , 1. , 100 , 0. , 1., True)

        #toolbox.make_2d_plot_from_ntuple(nt_chi2_matchingEff_vs_cutEff              , "h_chi2_matchingEff_vs_cutEff"              , "matchingEff:cutEff" , "" , 100 , 0. , 1. , 100 , 0. , 1.)
        #toolbox.make_2d_plot_from_ntuple(nt_chi2_matchingEff_vs_cutEff_subspace     , "h_chi2_matchingEff_vs_cutEff_subspace"     , "matchingEff:cutEff" , "" , 100 , 0. , 1. , 100 , 0. , 1.)
        #toolbox.make_2d_plot_from_ntuple(nt_cov_chi2_matchingEff_vs_cutEff          , "h_cov_chi2_matchingEff_vs_cutEff"          , "matchingEff:cutEff" , "" , 100 , 0. , 1. , 100 , 0. , 1.)
        #toolbox.make_2d_plot_from_ntuple(nt_cov_chi2_matchingEff_vs_cutEff_subspace , "h_cov_chi2_matchingEff_vs_cutEff_subspace" , "matchingEff:cutEff" , "" , 100 , 0. , 1. , 100 , 0. , 1.)

        colors = [ROOT.kBlue, ROOT.kRed]
        styles = [1, 1]
        texts = [ "w/o covariance matrix", "with covariance matrix" ]

        xytitles = ["chi-2 cut values", "Selection Efficiency"]
        hists = [ h_chi2_cut_eff, h_cov_chi2_cut_eff ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_selectionEff_vs_chi2Cut_%s.%s" % (tag, ext), 2017, "ep", "epl")
        hists = [ h_chi2_cut_eff_subspace, h_cov_chi2_cut_eff_subspace ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_selectionEff_vs_chi2Cut_subspace_%s.%s" % (tag, ext), 2017, "ep", "epl")

        xytitles = ["chi-2 cut values", "Matching Efficiency"]
        hists = [ h_matchingEff_vs_chi2Cut, h_cov_matchingEff_vs_chi2Cut ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_matchingEff_vs_chi2Cut_%s.%s" % (tag, ext), 2017, "ep", "epl")
        hists = [ h_matchingEff_vs_chi2Cut_rebase, h_cov_matchingEff_vs_chi2Cut_rebase ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_matchingEff_vs_chi2Cut_rebase_%s.%s" % (tag, ext), 2017, "ep", "epl")

        xytitles = ["chi-2 values", "Matching Efficiency"]
        hists = [ h_matchingEff_vs_chi2Bins, h_cov_matchingEff_vs_chi2Bins ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_matchingEff_vs_chi2Bins_%s.%s" % (tag, ext), 2017, "ep", "epl")
        hists = [ h_matchingEff_vs_chi2Bins_rebase, h_cov_matchingEff_vs_chi2Bins_rebase ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_matchingEff_vs_chi2Bins_rebase_%s.%s" % (tag, ext), 2017, "ep", "epl")

        xytitles = ["chi-2 values", "Entries"]
        hists = [ h_chi2_value, h_cov_chi2_value ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_chi2_values_%s.%s" % (tag, ext), 2017, "hist", "l", True)
        hists = [ h_chi2_value_subspace, h_cov_chi2_value_subspace ]
        toolbox.make_plot_multi_hists(hists, colors, styles, texts, xytitles, "h_compare_chi2_values_subspace_%s.%s" % (tag, ext), 2017, "hist", "l", True)


        # mass relatted
        toolbox.make_plot_three_hists(h_mass_wboson          , "Minimum chi-2" , h_mass_wboson_cov          , "Covariant matrix" , h_mass_wboson_tm , "Truth-Matched" , year , mass , "h_woNorm_covReco_mass_wboson_%s.%s"   % (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_top             , "Minimum chi-2" , h_mass_top_cov             , "Covariant matrix" , h_mass_top_tm    , "Truth-Matched" , year , mass , "h_woNorm_covReco_mass_top_%s.%s"      % (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_tprime          , "Minimum chi-2" , h_mass_tprime_cov          , "Covariant matrix" , h_mass_tprime_tm , "Truth-Matched" , year , mass , "h_woNorm_covReco_mass_tprime_%s.%s"   % (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_wboson_subspace , "Minimum chi-2" , h_mass_wboson_cov_subspace , "Covariant matrix" , h_mass_wboson_tm , "Truth-Matched" , year , mass , "h_subsace_covReco_mass_wboson_%s.%s"  % (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_top_subspace    , "Minimum chi-2" , h_mass_top_cov_subspace    , "Covariant matrix" , h_mass_top_tm    , "Truth-Matched" , year , mass , "h_subsace_covReco_mass_top_%s.%s"     % (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_tprime_subspace , "Minimum chi-2" , h_mass_tprime_cov_subspace , "Covariant matrix" , h_mass_tprime_tm , "Truth-Matched" , year , mass , "h_subsace_covReco_mass_tprime_%s.%s"  % (tag , ext) )
    
        toolbox.normalize_to_unity( h_mass_wboson     )
        toolbox.normalize_to_unity( h_mass_top        )
        toolbox.normalize_to_unity( h_mass_tprime     )
        toolbox.normalize_to_unity( h_mass_wboson_tm  )
        toolbox.normalize_to_unity( h_mass_top_tm     )
        toolbox.normalize_to_unity( h_mass_tprime_tm  )
        toolbox.normalize_to_unity( h_mass_wboson_cov )
        toolbox.normalize_to_unity( h_mass_top_cov    )
        toolbox.normalize_to_unity( h_mass_tprime_cov )
    
        toolbox.make_plot_two_hists(h_mass_wboson , "Min. #chi^{2} method" , h_mass_wboson_tm  , "MC-truth matching" , year , mass , "h_tmReco_mass_wboson_%s.%s"   %  (tag , ext) )
        toolbox.make_plot_two_hists(h_mass_top    , "Min. #chi^{2} method" , h_mass_top_tm     , "MC-truth matching" , year , mass , "h_tmReco_mass_top_%s.%s"      %  (tag , ext) )
        toolbox.make_plot_two_hists(h_mass_tprime , "Min. #chi^{2} method" , h_mass_tprime_tm  , "MC-truth matching" , year , mass , "h_tmReco_mass_tprime_%s.%s"   %  (tag , ext) )
    
        toolbox.make_plot_three_hists(h_mass_wboson , "Minimum chi-2" , h_mass_wboson_cov , "Covariant matrix" , h_mass_wboson_tm  , "Truth-Matched" , year , mass , "h_covReco_mass_wboson_%s.%s"   %  (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_top    , "Minimum chi-2" , h_mass_top_cov    , "Covariant matrix" , h_mass_top_tm     , "Truth-Matched" , year , mass , "h_covReco_mass_top_%s.%s"      %  (tag , ext) )
        toolbox.make_plot_three_hists(h_mass_tprime , "Minimum chi-2" , h_mass_tprime_cov , "Covariant matrix" , h_mass_tprime_tm  , "Truth-Matched" , year , mass , "h_covReco_mass_tprime_%s.%s"   %  (tag , ext) )
    
    
    
    subprocess.call("rm -r %s;" % (target), shell=True)
    
    transfer_helper.copy_files("*gen*png"        , target + "/06_MCtruth"              )
    transfer_helper.copy_files("*quark*png"      , target + "/06_MCtruth"              )
    transfer_helper.copy_files("*chi2_value*png" , target + "/07_Xtt0"                 )
    transfer_helper.copy_files("*chi2*png"       , target + "/08_Minimum_Chi2_Methods" )
    transfer_helper.copy_files("*cov*png"        , target + "/09_CovMatrix"            )

    transfer_helper.move_files("*chi2*value*png" , target + "/00_MatchingEff"          )
    transfer_helper.move_files("*chi2Bins*png"   , target + "/00_MatchingEff"          )
    transfer_helper.move_files("*chi2Cut*png"    , target + "/00_MatchingEff"          )
    transfer_helper.move_files("*chi2*Eff*png"   , target + "/00_MatchingEff"          )
    transfer_helper.move_files("*num*png"        , target + "/01_Multiplicity"         )
    transfer_helper.move_files("*diphoton*png"   , target + "/02_Diphoton"             )
    transfer_helper.move_files("*wboson*png"     , target + "/03_Wboson"               )
    transfer_helper.move_files("*top*png"        , target + "/04_Top"                  )
    transfer_helper.move_files("*tprime*png"     , target + "/05_Tprime"               )
    transfer_helper.move_files("*parton*png"     , target + "/06_MCtruth"              )
    transfer_helper.move_files("*png"            , target + "/10_Others"               )
    
    subprocess.call("echo %s; ls -ld %s;" % (target, target), shell=True)
