#!/usr/bin/env python
import subprocess
import ctypes
import array
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat("e")
ROOT.gStyle.SetOptFit(1111)

c1 = ROOT.TCanvas("c1", "", 800, 600)
c1.SetGrid()
c1.SetLeftMargin(0.12)
c1.SetRightMargin(0.08)

dir_output = "."
masses = [600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200]
lumi={"2016":35.9,"2017":41.5,"2018":59.76,"RunII":137}

def annotate(): #{{{
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(24)
    latex.DrawLatex( 0.12, 0.912, "#bf{CMS} #it{work in progress}" )
    latex.DrawLatex( 0.72, 0.912, "%s fb^{-1} (13 TeV)" % str(lumi["RunII"]) )

    #latex.DrawLatex( 0.60, 0.800, "Pre-selection" )
#}}}
def set_graph(gr, ytitle, color): #{{{
    gr.SetTitle("")
    gr.SetLineColor(color)
    gr.SetLineWidth(2)
    gr.SetMarkerStyle(20)
    gr.SetMarkerColor(color)
    gr.GetXaxis().SetTitle("Hypothetical M_{T'} (GeV)")
    gr.GetYaxis().SetTitle(ytitle)
    gr.GetXaxis().SetTitleOffset(1.2)
#}}}

# collection_efficiency {{{
collection_efficiency = {
    "set0":{
        # original
        "raw_M600_M700"  : [ 0.07882, 0.09317, 0.10533, 0.11234, 0.10923, 0.06883, 0.02264, 0.01262, 0.00778, 0.00539 ],
        "raw_M800_M1000" : [ 0.00810, 0.01266, 0.02134, 0.03390, 0.04737, 0.12473, 0.17935, 0.19774, 0.16925, 0.09225 ],
        "raw_M1100_1200" : [ 0.00242, 0.00311, 0.00408, 0.00535, 0.00699, 0.03057, 0.10157, 0.18667, 0.23183, 0.26597 ],
    },
    "set1":{
        # signal efficiency of opt1; from log messages && double check from validation code
        "raw_M600_M700"  : [ 0.07882, 0.09316, 0.10531, 0.11233, 0.10923, 0.06886, 0.02265, 0.01258, 0.00790, 0.00568 ],
        "raw_M800_M1000" : [ 0.00810, 0.01267, 0.02135, 0.03389, 0.04737, 0.12472, 0.17937, 0.19774, 0.16941, 0.09232 ],
        "raw_M1100_1200" : [ 0.00214, 0.00280, 0.00364, 0.00491, 0.00635, 0.02916, 0.09825, 0.17936, 0.21772, 0.23706 ],
    },
    "set2":{
        # signal efficiency of opt2
        "raw_M600_M700"  : [ 0.07882, 0.09316, 0.10531, 0.11233, 0.10923, 0.06886, 0.02265, 0.01258, 0.00790, 0.00568 ],
        "raw_M800_M1000" : [ 0.01154, 0.01693, 0.02616, 0.03833, 0.05153, 0.13028, 0.18590, 0.20395, 0.17460, 0.09648 ],
        "raw_M1100_1200" : [ 0.00315, 0.00411, 0.00581, 0.00791, 0.01048, 0.03536, 0.10861, 0.19710, 0.24494, 0.28062 ],
    },
}
#}}}
def get_ratio_list(key): #{{{
    result = []
    opt1 = collection_efficiency["set1"][key]
    opt2 = collection_efficiency["set2"][key]
    for i in range(len(opt1)):
        ratio = opt2[i] / opt1[i]
        result.append( ratio )
    return result
#}}}
def make_efficiency(ytitle, myParameters, tag, output_stem): #{{{
    c1.cd()
    ymin = myParameters["ybound"][0]
    ymax = myParameters["ybound"][1]
    leg = myParameters["legend"]

    if tag in collection_efficiency.keys():
        raw_M600_M700  = collection_efficiency[tag]["raw_M600_M700"]
        raw_M800_M1000 = collection_efficiency[tag]["raw_M800_M1000"]
        raw_M1100_1200 = collection_efficiency[tag]["raw_M1100_1200"]
    else:
        raw_M600_M700  = get_ratio_list("raw_M600_M700")
        raw_M800_M1000 = get_ratio_list("raw_M800_M1000")
        raw_M1100_1200 = get_ratio_list("raw_M1100_1200")

    n = len(raw_M600_M700) 
    x = array.array('d')
    efficiency_M600_M700  = array.array('d')
    efficiency_M800_M1000 = array.array('d')
    efficiency_M1100_1200 = array.array('d')

    for i in range(n):
        #x.append(masses_v2[i])
        x.append(masses[i])
        efficiency_M600_M700.append(raw_M600_M700[i]) 
        efficiency_M800_M1000.append(raw_M800_M1000[i])
        efficiency_M1100_1200.append(raw_M1100_1200[i])

    gr1 = ROOT.TGraph(n, x, efficiency_M600_M700)
    gr2 = ROOT.TGraph(n, x, efficiency_M800_M1000)
    gr3 = ROOT.TGraph(n, x, efficiency_M1100_1200)

    set_graph(gr1, ytitle, ROOT.kRed)
    set_graph(gr2, ytitle, ROOT.kGreen+3)
    set_graph(gr3, ytitle, ROOT.kBlue)

    gr1.SetMaximum(ymax)
    gr1.SetMinimum(ymin)

    gr1.Draw('ACP')
    gr2.Draw('CP')
    gr3.Draw('CP')

    # local leg
    legend = ROOT.TLegend(leg[0], leg[1], leg[2], leg[3])
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.Clear()
    legend.AddEntry(gr1, "[600, 700]", "lp")
    legend.AddEntry(gr2, "[800, 1000]", "lp")
    legend.AddEntry(gr3, "[1100, 1200]", "lp")
    legend.Draw("same")

    # wrap up
    annotate()
    output = dir_output + "/" + output_stem
    c1.SaveAs(output + ".png")
    c1.SaveAs(output + ".pdf")
#}}}

myParameterSets = {
    "eff":{
        "ybound" : [0.0, 0.5],
        "legend" : [0.17, 0.60, 0.42, 0.85],
    },
    "ratio":{
        "ybound" : [0.8, 2.0],
        "legend" : [0.60, 0.60, 0.85, 0.85],
    },
}

if __name__ == "__main__":
    make_efficiency("Efficiency"        , myParameterSets["eff"]   , "set0"  , "signal_efficiency_old")
    make_efficiency("Efficiency"        , myParameterSets["eff"]   , "set1"  , "signal_efficiency")
    make_efficiency("Efficiency"        , myParameterSets["eff"]   , "set2"  , "signal_efficiency_newOpt")
    make_efficiency("Ratio (Opt2/Opt1)" , myParameterSets["ratio"] , "ratio" , "signal_efficiency_comparison")
    subprocess.call("ls -lhrt %s" % dir_output, shell=True)
