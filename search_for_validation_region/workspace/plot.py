#!/usr/bin/env python2
import numpy as np
import math
import ROOT
ROOT.gROOT.SetBatch(True)

def load(root):
    global vf, vh
    fin = ROOT.TFile(root, 'R')
    h = fin.Get("h_counter_validation_region")
    h.SetStats(0)
    vf.append(fin)
    vh.append(h)

def evaluate():
    global vf, vh

    n = vh[0].GetNbinsX()
    h = ROOT.TH1D("significance", ";Validation regions; SMH/#sqrt{B}", n, 0, n)
    error = np.array([0]*n)

    # loop over each validation region
    for i in range(n):
        smh = vh[1].GetBinContent(i+1)
        data_sideband = vh[0].GetBinContent(i+1)
        significance = smh / math.sqrt(data_sideband/6.) if data_sideband > 0. else 0.
        h.SetBinContent(i+1, significance)
        h.SetError(error)
        print ">>>", i+1, smh, data_sideband, significance

    vh.append(h)

def make_plot():
    global vf, vh
    c1 = ROOT.TCanvas("c1", "", 800, 600)
    c1.SetGrid()
    c1.SetTicks(1,0)
    c1.SetRightMargin(0.15)
    c1.SetLeftMargin(0.15)

    # data
    vh[0].SetMarkerStyle(20)
    vh[0].SetMarkerSize(0.7)
    vh[0].SetMarkerColor(ROOT.kBlack)
    vh[0].SetLineColor(ROOT.kBlack)
    vh[0].Draw("ep")
    c1.Update()

    # smh
    rightmax = 1.1 * vh[1].GetMaximum()
    scale = ROOT.gPad.GetUymax() / rightmax
    vh[1].SetLineColor(ROOT.kBlue-7)
    vh[1].Scale(scale)
    vh[1].Draw("hist;same")
    axis = ROOT.TGaxis(ROOT.gPad.GetUxmax()*1.12, ROOT.gPad.GetUymin(), ROOT.gPad.GetUxmax()*1.12, ROOT.gPad.GetUymax(), 0, rightmax, 510, "+L")
    axis.SetLineColor(ROOT.kBlue-7)
    axis.SetLabelColor(ROOT.kBlue-7)
    axis.Draw()

    ## signal
    #rightmax = 1.1 * vh[2].GetMaximum()
    #scale = ROOT.gPad.GetUymax() / rightmax
    #vh[2].SetLineColor(ROOT.kRed)
    #vh[2].Scale(scale)
    #vh[2].Draw("hist;same")
    #axis_sig = ROOT.TGaxis(55, ROOT.gPad.GetUymin(), 55, ROOT.gPad.GetUymax(), 0, rightmax, 510, "+L")
    #axis_sig.SetLineColor(ROOT.kRed)
    #axis_sig.SetLabelColor(ROOT.kRed)
    #axis_sig.SetLabelOffset(0.01)
    #axis_sig.Draw()

    # SMH / sqrt(B)
    rightmax = 1.1 * vh[-1].GetMaximum()
    scale = ROOT.gPad.GetUymax() / rightmax
    vh[-1].SetMarkerStyle(3)
    vh[-1].SetMarkerSize(0.7)
    vh[-1].SetMarkerColor(ROOT.kRed-7)
    vh[-1].SetLineColor(ROOT.kRed-7)
    vh[-1].Scale(scale)
    vh[-1].Draw("lp0;same")
    axis_sig = ROOT.TGaxis(ROOT.gPad.GetUxmax()*0.999, ROOT.gPad.GetUymin(), ROOT.gPad.GetUxmax()*0.999, ROOT.gPad.GetUymax(), 0, rightmax, 510, "+L")
    axis_sig.SetLineColor(ROOT.kRed-7)
    axis_sig.SetLabelColor(ROOT.kRed-7)
    axis_sig.SetLabelOffset(0.01)
    axis_sig.Draw()

    # legend
    legend = ROOT.TLegend(0.18, 0.67, 0.30, 0.87)
    #legend = ROOT.TLegend(0.20, 0.65, 0.50, 0.85)
    #legend = ROOT.TLegend(0.40, 0.40, 0.70, 0.60)
    legend.SetLineColor(0)
    legend.SetTextSize(0.03)
    legend.AddEntry(vh[0], "Data in sideband", "lep")
    legend.AddEntry(vh[1], "SMH", "f")
    #legend.AddEntry(vh[2], "VLQ-M600", "f")
    legend.AddEntry(vh[-1], "SMH/#sqrt{B}", "lp")
    legend.Draw("same")

    c1.SaveAs("eos/comparison.png")
    c1.SaveAs("eos/comparison.pdf")

if __name__ == "__main__":
    vf, vh = [], []
    load( "eos/output_data.root" )
    load( "eos/output_smh.root" )
    load( "eos/output_sig.root" )

    evaluate()

    make_plot()
