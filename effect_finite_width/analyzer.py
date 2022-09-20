#!/usr/bin/env python2
import toolbox.plot_utils as p
import toolbox.MetaData as m
import ROOT
ROOT.gROOT.SetBatch(True)

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--key", help = "key = TprimeTToTH_M-700-10p_vs_NWA, etc.", type=str)
args = parser.parse_args()
key = args.key

#--------------------------------------------------

def make_a_plot(var):
    #--------------------
    # main pad
    #--------------------
    m.mainPad, m.ratPad = p.init_pads()
    c1.cd()
    m.mainPad.Draw()
    m.mainPad.cd()

    # draw histograms
    m.var = var
    p.draw_a_histogram(m.vf[m.fileName1], ROOT.kRed)
    p.draw_a_histogram(m.vf[m.fileName2], ROOT.kBlue)
    p.set_maximum()
    p.annotate()

    ROOT.gPad.RedrawAxis()
    ROOT.gPad.SetTicks()

    # draw legend
    label = ""
    if "10p" in m.key: label = "10% width"
    if "20p" in m.key: label = "20% width"
    if "30p" in m.key: label = "30% width"

    legend = ROOT.TLegend(0.70, 0.65, 0.89, 0.85)
    legend.AddEntry(m.vh[0], label, "f")
    legend.AddEntry(m.vh[1], "NWA", "f")
    legend.Draw("same")

    #--------------------
    # ratio pad
    #--------------------
    c1.cd()
    m.ratPad.Draw()
    m.ratPad.cd()

    h = p.draw_ratio_pad()
    h.Draw("e0,x0")

    c1.SaveAs("./eos/%s/%s.png" % (m.directory, var) )
    c1.SaveAs("./eos/%s/%s.pdf" % (m.directory, var) )

#--------------------------------------------------

if __name__ == "__main__":
    c1 = p.init_canvas()

    # set root files for comparison
    m.key = key
    m.fileName1 = m.path+"/"+m.rootfiles[key][0]
    m.fileName2 = m.path+"/"+m.rootfiles[key][1]

    m.vf = {}
    p.create_directory(key)
    p.load_file(m.fileName1)
    p.load_file(m.fileName2)

    ## one plot
    #make_a_plot(m.ref[1])
    #exit()

    for var in m.variables:
        m.vh = []
        make_a_plot(var)
