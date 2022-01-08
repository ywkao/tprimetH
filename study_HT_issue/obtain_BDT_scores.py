#!/usr/bin/env python
import subprocess
import ctypes
import array
import math
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat("e")
ROOT.gStyle.SetOptFit(1111)

from plot_utils import *
from my_plot_setup import *

path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/"
dir_output = path + "study_HT_issue/EOS_output_ht"
rootfile = path + "shortcut_plots/plots_check_BDT_scaleHT/myhist_combine_RunII.root"
rootfile = path + "/plots/myhist_combine_RunII.root"
rootfile = path + "/plots_dataDriven_n30000/myhist_combine_RunII.root" # only QCD_GammaJets_imputed in it
rootfile = path + "/plots_dataDriven_n30000_equalScale/myhist_combine_RunII.root" # only QCD_GammaJets_imputed in it
fin = ROOT.TFile.Open(rootfile, "R")

lshift, rshift = 0.03, 0.00
c1 = ROOT.TCanvas("c1", "", 800, 600)
c1.SetGrid()
c1.SetTicks(1,1)
c1.SetLeftMargin(0.12+lshift)
c1.SetRightMargin(0.08)

def make_plot(varName, myMasses, plotType, pauseFit): #{{{
    c1.cd()
    nameTag = varName + "_" + plotType
    legend = get_my_legend(0.60, 0.73, 0.72, 0.85)

    backgrounds = "DiPhoton|QCD|GammaJets|TTGG|TTGJets|TTJets|VG" # pure MC
    backgrounds = "DiPhoton|QCD_GammaJets_imputed|TTGG|TTGJets|TTJets|TGamma|VG|VV"
    backgrounds = "QCD_GammaJets_imputed|QCD|GammaJets"
    backgrounds = "QCD_GammaJets_imputed"
    processes = backgrounds.split('|')

    # load hists
    v_hists, v_herrs = load_histograms(fin, processes, varName)

    # loop over hists
    for i, h in enumerate(v_hists):
        h_err = v_herrs[i]

        if plotType == "normalized":
            unc = ctypes.c_double(0.) 
            nbins = h.GetSize()-1
            tot_yields = h.IntegralAndError(0, nbins, unc)
            if tot_yields > 0.:
                h.Scale(1./tot_yields)
                h_err.Scale(1./tot_yields)

        set_the_hist(h, varName, ranges[varName], plotType, xtitles[varName], ytitles[plotType][varName], default_color_scheme[processes[i]], dataLike=(i==0))
        set_the_error_band(h_err)

        # normalization from a simultaneous fit to photon IDMVAs
        if processes[i]=="QCD_GammaJets_imputed":
            h.Scale(1.076398)
            h_err.Scale(1.076398)

        print ">>> ", i, processes[i], get_total_yields(h)

    legend.AddEntry(v_hists[0], myLabel[processes[0]], "lep")

    # wrap up
    maximum = get_maximum(v_hists)
    scaleTags = ["linear", "log"]
    for scaleTag in scaleTags:
        set_scope(c1, v_hists[0], scaleTag, maximum)

        v_hists[0].Draw("ep")
        legend.Draw("same")

        annotate(lshift, rshift)
        output = dir_output + "/" + nameTag + "_" + scaleTag
        c1.SaveAs(output + ".png")
        c1.SaveAs(output + ".pdf")

        init_hist_collector()
        break # skip log plot
#}}}
def make_comparison_plot(v_varName, myMasses, plotType, pauseFit): #{{{
    c1.cd()
    nameTag = v_varName[0] + "_" + plotType
    legend = get_my_legend(0.50, 0.60, 0.72, 0.85)
    processes = ["QCD_GammaJets_imputed"] # only one process in this case
    color_scheme = [ROOT.kBlack, ROOT.kRed, ROOT.kBlue]

    my_hists = []
    for x, varName in enumerate(v_varName):
        # load hists
        v_hists, v_herrs = load_histograms(fin, processes, varName)

        # loop over hists
        for i, h in enumerate(v_hists):
            h_err = v_herrs[i]
            set_the_hist(h, varName, [0., 1.], plotType, "BDT-NRB", "Yields / 0.02", color_scheme[x])
            set_the_error_band(h_err)

            # normalization from a simultaneous fit to photon IDMVAs
            if processes[i]=="QCD_GammaJets_imputed":
                h.Scale(1.076398)
                h_err.Scale(1.076398)

            print ">>> ", i, processes[i], h.GetEntries(), get_total_yields(h)

        # store hists
        my_hists.append(v_hists[0])
        legend.AddEntry(v_hists[0], myLabel[varName], "lep")

    # wrap up
    v_hists = my_hists
    maximum = get_maximum(v_hists)
    scaleTags = ["linear", "log"]
    for scaleTag in scaleTags:
        set_scope(c1, v_hists[0], scaleTag, maximum)

        v_hists[0].Draw("ep")
        v_hists[1].Draw("ep;same")
        v_hists[2].Draw("ep;same")
        legend.Draw("same")

        annotate(lshift, rshift)
        output = dir_output + "/" + nameTag + "_" + scaleTag
        output = dir_output + "/" + nameTag + "_" + scaleTag + "_equalScale"
        c1.SaveAs(output + ".png")
        c1.SaveAs(output + ".pdf")

        init_hist_collector()
        #break # skip log plot
#}}}

def run():
    #make_plot("hMVA_value_nrb_varset8_mixed03_tmva_bdtg_difference", masses, plotType, pauseFit=False)
    #make_plot("hMVA_value_nrb_varset8_mixed03_tmva_bdtg_relativeDifference", masses, plotType, pauseFit=False)
    make_comparison_plot(my_list_hists, masses, plotType, pauseFit=False)

    exit()
    make_plot("hHT", masses, plotType, pauseFit=False)


if __name__ == "__main__":
    plotType = "yields" #"normalized"
    my_list_hists = [
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_central_n100",
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_up_n100",
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_scaleHT_down_n100",
    ]

    run()
    subprocess.call("ls -lhrt %s" % dir_output, shell=True)



