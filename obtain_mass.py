#!/usr/bin/env python
import subprocess
import ctypes
import array
import ROOT
ROOT.gROOT.SetBatch(True)

# setup {{{
dir_output = "eos_output_mass"
masses = [600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200]
v_blue = [ROOT.kBlue-10, ROOT.kBlue-9, ROOT.kBlue-7, ROOT.kBlue-4, ROOT.kBlue, ROOT.kBlue+1, ROOT.kBlue+2, ROOT.kBlue+3, ROOT.kBlue+4, ROOT.kBlack]
v_red = [ROOT.kRed-10, ROOT.kRed-9, ROOT.kRed-7, ROOT.kRed-4, ROOT.kRed, ROOT.kRed+1, ROOT.kRed+2, ROOT.kRed+3, ROOT.kRed+4, ROOT.kBlack]

lumi={"2016":35.9,"2017":41.5,"2018":59.76,"RunII":137}
ytitles = {"yields":"Yields", "normalized":"Arbitrary unit"}

xtitles = {
    "hMass":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed03":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed04":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed05":"M_{#gamma#gamma} (GeV)",
    "hmass_tprime_cov":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
}

colors = {
    "hMass":v_blue,
    "hMass_pass_BDTG_smh_cut_mixed03":v_blue,
    "hMass_pass_BDTG_smh_cut_mixed04":v_blue,
    "hMass_pass_BDTG_smh_cut_mixed05":v_blue,
    "hmass_tprime_cov":v_red,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":v_red,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":v_red,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":v_red,
}

ranges = {
    "hMass":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed03":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed04":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed05":[100,180],
    "hmass_tprime_cov":[200,2500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":[200,2500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":[200,2500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":[200,2500],
}
#}}}
global_plotType = None

rootfile = "plots/myhist_signal.root"
fin = ROOT.TFile.Open(rootfile, "R")

c1 = ROOT.TCanvas("c1", "", 800, 600)
c1.SetGrid()

legend = ROOT.TLegend(0.58, 0.35, 0.85, 0.85)
legend.SetLineColor(0)
legend.SetTextSize(0.04)

def get_maximum(v): #{{{
    result = 0.
    for h in v:
        hmax = h.GetMaximum()
        if hmax > result:
            result = hmax

    return result
#}}}
def annotate(): #{{{
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(24)
    latex.DrawLatex( 0.10, 0.912, "#bf{CMS} #it{work in progress}" )
    latex.DrawLatex( 0.70, 0.912, "%s fb^{-1} (13 TeV)" % str(lumi["RunII"]) )

    #if global_plotType == "normalized":
    #    latex.DrawLatex( 0.48, 0.912, "Area normalized to unity (13 TeV)" )
    #else:
    #    latex.DrawLatex( 0.70, 0.912, "%s fb^{-1} (13 TeV)" % str(lumi["RunII"]) )

    #latex.DrawLatex( 0.60, 0.800, "Pre-selection" )
#}}}
def make_plot(varName, plotType): #{{{
    legend.Clear()
    global global_plotType
    global_plotType = plotType

    v_hists = []
    for m in masses:
        histName = varName + "_TprimeBToTH_M-" + str(m)
        h = fin.Get(histName)
        v_hists.append(h)
        #break


    for i, h in enumerate(v_hists):
        # set the hist
        h.SetStats(0)
        h.SetLineColor(colors[varName][i])
        h.GetXaxis().SetTitleOffset(1.2)
        h.GetYaxis().SetTitle(ytitles[plotType])
        h.GetXaxis().SetTitle(xtitles[varName])
        h.GetXaxis().SetRangeUser(ranges[varName][0], ranges[varName][1])
        legend.AddEntry(h, "M_{T'} = " + str(masses[i]) + " GeV", "l")

        # normalize area
        if plotType == "normalized":
            unc = ctypes.c_double(0.) 
            nbins = h.GetSize()-1
            tot_yields = h.IntegralAndError(0, nbins, unc)
            if tot_yields > 0.:
                h.Scale(1./tot_yields)

        # draw the hist
        if i == 0:
            h.Draw("hist")
        else:
            h.Draw("hist;same")

    # set scope
    maximum = get_maximum(v_hists)
    v_hists[0].SetMaximum(maximum*1.2)

    # wrap up
    annotate()
    legend.Draw("same")
    output = dir_output + "/" + varName + "_" + plotType + ".png"
    c1.SaveAs(output)
#}}}
def run(): #{{{
    plotTypes = ["yields", "normalized"]
    for plotType in plotTypes:
        make_plot("hMass", plotType)
        make_plot("hmass_tprime_cov", plotType)

        make_plot("hMass_pass_BDTG_smh_cut_mixed03", plotType);
        make_plot("hMass_pass_BDTG_smh_cut_mixed04", plotType);
        make_plot("hMass_pass_BDTG_smh_cut_mixed05", plotType);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine", plotType);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine", plotType);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine", plotType);
#}}}
def set_graph(gr, color): #{{{
    gr.SetTitle("")
    gr.SetLineColor(color)
    gr.SetLineWidth(2)
    gr.SetMarkerStyle(20)
    gr.SetMarkerColor(color)
    gr.GetXaxis().SetTitle("M_{T'} (GeV)")
    gr.GetYaxis().SetTitle("Efficiency")
    gr.GetXaxis().SetTitleOffset(1.2)
#}}}
def make_efficiency(): #{{{
    raw_M600_M700 = [0.27, 0.32, 0.35, 0.37, 0.37, 0.21, 0.06, 0.04, 0.02, 0.02]
    raw_M800_M1000 = [0.03, 0.04, 0.07, 0.11, 0.16, 0.38, 0.51, 0.54, 0.46, 0.24]
    raw_M1100_1200 = [0.01, 0.01, 0.01, 0.02, 0.02, 0.09, 0.28, 0.48, 0.59, 0.60]

    n = 10
    x = array.array('d')
    efficiency_M600_M700  = array.array('d')
    efficiency_M800_M1000 = array.array('d')
    efficiency_M1100_1200 = array.array('d')

    for i in range(n):
        x.append(masses[i])
        efficiency_M600_M700.append(raw_M600_M700[i]) 
        efficiency_M800_M1000.append(raw_M800_M1000[i])
        efficiency_M1100_1200.append(raw_M1100_1200[i])

    gr1 = ROOT.TGraph(n, x, efficiency_M600_M700)
    gr2 = ROOT.TGraph(n, x, efficiency_M800_M1000)
    gr3 = ROOT.TGraph(n, x, efficiency_M1100_1200)

    set_graph(gr1, ROOT.kRed)
    set_graph(gr2, ROOT.kGreen+3)
    set_graph(gr3, ROOT.kBlue)

    gr1.SetMaximum(1.0)

    gr1.Draw('ACP')
    gr2.Draw('CP')
    gr3.Draw('CP')

    # local leg
    legend = ROOT.TLegend(0.15, 0.60, 0.40, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.Clear()
    legend.AddEntry(gr1, "[600, 700]", "lp")
    legend.AddEntry(gr2, "[800, 1000]", "lp")
    legend.AddEntry(gr3, "[1100, 1200]", "lp")
    legend.Draw("same")

    # wrap up
    annotate()
    output = dir_output + "/signal_efficiency.png"
    c1.SaveAs(output)
#}}}

if __name__ == "__main__":
    #run()
    make_efficiency()
    subprocess.call("ls -lhrt %s" % dir_output, shell=True)

