#!/usr/bin/env python2
import ROOT
import metaData as m
import plot_utils as p
ROOT.gROOT.SetBatch(True)

path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220328_ultraLegacy/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220419_ultraLegacy_unblind/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220420_v2/myhist_combine_RunII.root"

path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots/myhist_combine_RunII.root"
path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots_20220419_ultraLegacy_unblind/myhist_combine_RunII.root"
fin = ROOT.TFile(path, 'R')

def load(fin, histname, my_signals):
    dh, legend = {}, p.init_legend()
    dh["data"]        = p.register( fin, histname, "data"       , ["Data"]                 , legend )
    dh["signals"]     = p.register( fin, histname, "signals"    , my_signals.split("|")    , legend )
    dh["smHiggs"]     = p.register( fin, histname, "smHiggs"    , m.smHiggs.split("|")     , None   )
    dh["SMH"]         = p.merge(dh["smHiggs"], legend)
    dh["backgrounds"] = p.register( fin, histname, "backgrounds", m.backgrounds.split("|") , legend )
    dh["NRB"]         = p.merge(dh["backgrounds"], None)
    dh["ratio"]       = p.get_ratio( histname, dh["data"][0], dh["NRB"][0] )
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
    hs.GetXaxis().SetRangeUser(myRange[0], myRange[1])
    hs.GetYaxis().SetTitle("Events")
    hs.GetYaxis().SetTitleSize(0.04)
    hs.GetXaxis().SetLabelOffset(999)
    hs.GetXaxis().SetLabelSize(0)

    dh["data"][0].Draw("ep;same")
    dh["SMH"][0].Draw("hist;same")
    for h in dh["signals"]:h.Draw("hist;same")

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
    hr = dh["ratio"]
    hr.GetXaxis().SetRangeUser(myRange[0], myRange[1])
    hr.Draw("e1")

    # save
    output = "eos/" + histname.replace("h", "THQHadronicTag_", 1)
    #output = "output/" + histname.replace("h", "THQHadronicTag_", 1)
    c1.SaveAs(output + ".png")
    c1.SaveAs(output + ".pdf")


if __name__ == "__main__":
    c1 = p.init_canvas()

    core = [
        #"hMass",
        #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine",
        #"hMass_pass_BDTG_smh_cut_mixed03",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine",
        "hMass_pass_BDTG_smh_cut_mixed04",
        "hMass_pass_BDTG_smh_cut_mixed05",
    ]

    for histname in core:
        make_plot(histname)
