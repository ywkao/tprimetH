#!/usr/bin/env python2
import ROOT
import toolbox.metaData as m
import toolbox.plot_utils as p
ROOT.gROOT.SetBatch(True)

path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220328_ultraLegacy/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220419_ultraLegacy_unblind/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220420_v2/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220419_ultraLegacy_unblind/myhist_combine_RunII.root"
path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220422_v4p1/myhist_combine_RunII.root"

path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/shortcut_plots/plots_20220425_v4p2_v1/myhist_combine_RunII.root"

fin = ROOT.TFile(path, 'R')

def load(fin, histname, my_signals):
    dh, legend = {}, p.init_legend()
    dh["data"]        = p.register( fin, histname, "data"       , ["Data"]                 , legend )
    dh["signals"]     = p.register( fin, histname, "signals"    , my_signals.split("|")    , legend )
    dh["smHiggs"]     = p.register( fin, histname, "smHiggs"    , m.smHiggs.split("|")     , None   )
    dh["SMH"]         = p.merge(dh["smHiggs"], "SMH", legend)
    dh["backgrounds"] = p.register( fin, histname, "backgrounds", m.backgrounds.split("|") , legend )
    dh["NRB"]         = p.merge(dh["backgrounds"], "NRB", legend)
    dh["ratio"]       = p.get_ratio( "ratio"   , histname, dh["data"][0], dh["NRB"][0] )
    dh["ratio_mc"]    = p.get_ratio( "ratio_mc", histname, dh["data"][0], dh["NRB"][0] )
    return dh, legend

def make_plot(histname):
    my_signals = p.signal_selector(histname)
    dh, legend = load(fin, histname, my_signals)

    hs = ROOT.THStack("hs", "")
    orders = [3, 5, 6, 4, 1, 2]
    for i, idx in enumerate(orders): hs.Add( dh["backgrounds"][idx-1] )

    scale = p.get_scale(histname)
    hs.SetMinimum(scale[0])
    hs.SetMaximum(scale[1])

    mainPad, ratPad = p.init_pads()

    # main pad
    c1.cd()
    mainPad.Draw()
    mainPad.cd()
    hs.Draw("hist")

    myRange = m.map_range[histname]
    #hs.GetXaxis().SetRangeUser(myRange[0], myRange[1])
    #print ">>>>> check hs: p.idx_xmin = ", p.idx_xmin
    #print ">>>>> check hs: p.idx_xmax = ", p.idx_xmax
    hs.GetXaxis().SetRange(p.idx_xmin, p.idx_xmax)
    hs.GetYaxis().SetTitle("Events")
    hs.GetYaxis().SetTitleSize(0.062)
    hs.GetYaxis().SetTitleOffset(0.80)
    hs.GetYaxis().SetLabelSize(0.038)
    hs.GetYaxis().SetLabelOffset(0.003)
    hs.GetXaxis().SetLabelSize(0)
    hs.GetXaxis().SetLabelOffset(999)

    dh["SMH"][0].Draw("hist;same")
    for h in dh["signals"]:h.Draw("hist;same")
    dh["NRB"][0].SetFillColorAlpha(ROOT.kRed, 0.25)
    dh["NRB"][0].Draw("e2;same")
    dh["data"][0].Draw("e0;x0;same")

    if len(dh["signals"]) == 1:
        dh["signals"][0].SetLineColor(ROOT.kMagenta)

    legend.Draw("same")
    ROOT.gPad.RedrawAxis()
    ROOT.gPad.SetTicks()
    p.annotate()

    # ratio pad
    c1.cd()
    ratPad.Draw()
    ratPad.cd()

    hr, hr_mc = dh["ratio"], dh["ratio_mc"]
    hr_mc.Draw("e2")
    hr.Draw("e0,x0,same")

    # save
    output = "eos/" + histname.replace("h", "THQHadronicTag_", 1)
    #output = "output/" + histname.replace("h", "THQHadronicTag_", 1)
    c1.SaveAs(output + ".png")
    c1.SaveAs(output + ".pdf")


if __name__ == "__main__":
    c1 = p.init_canvas()

    core = [
        "hMass",
        "hMass_pass_BDTG_smh_cut_mixed03",
        "hMass_pass_BDTG_smh_cut_mixed04",
        "hMass_pass_BDTG_smh_cut_mixed05",
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_n50",
        "hMVA_value_smh_varset8_mixed03_tmva_bdtg_n50",
        #"hMVA_value_nrb_varset8_mixed04_tmva_bdtg_n50",
        #"hMVA_value_nrb_varset8_mixed05_tmva_bdtg_n50",
        #"hMVA_value_smh_varset8_mixed04_tmva_bdtg_n50",
        #"hMVA_value_smh_varset8_mixed05_tmva_bdtg_n50",

        #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_fine",
        #"hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_fine",
        #"hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_fine",
        #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine",
        #"hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine",
        #"hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine",
    ]

    bdts = [
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_n50",
        "hMVA_value_nrb_varset8_mixed04_tmva_bdtg_n50",
        "hMVA_value_nrb_varset8_mixed05_tmva_bdtg_n50",
        "hMVA_value_smh_varset8_mixed03_tmva_bdtg_n50",
        "hMVA_value_smh_varset8_mixed04_tmva_bdtg_n50",
        "hMVA_value_smh_varset8_mixed05_tmva_bdtg_n50",
        "hMVA_value_nrb_varset8_mixed03_tmva_bdtg_mggWindow_n50",
        "hMVA_value_nrb_varset8_mixed04_tmva_bdtg_mggWindow_n50",
        "hMVA_value_nrb_varset8_mixed05_tmva_bdtg_mggWindow_n50",
        "hMVA_value_smh_varset8_mixed03_tmva_bdtg_mggWindow_n50",
        "hMVA_value_smh_varset8_mixed04_tmva_bdtg_mggWindow_n50",
        "hMVA_value_smh_varset8_mixed05_tmva_bdtg_mggWindow_n50",
    ]

    for histname in core:
        make_plot(histname)
