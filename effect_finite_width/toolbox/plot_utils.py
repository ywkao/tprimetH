#!/usr/bin/env python2
import math
import subprocess
import ROOT
import MetaData as m
ROOT.gROOT.SetBatch(True)

def exe(command):
    subprocess.call(command, shell=True)

def create_directory(directory):
    subprocess.call("mkdir -p ./eos/%s" % directory, shell=True)
    subprocess.call("cp -p ./eos/index.php ./eos/%s" % directory, shell=True)
    m.directory = directory

def init_canvas():
    c1 = ROOT.TCanvas("c1", "", 800, 600)
    c1.SetGrid()
    c1.SetTicks()
    #c1.SetLogy()
    return c1

def init_pads():
    mainPad = ROOT.TPad("p_main", "p_main", 0.0, 0.3, 1.0, 1.0)
    mainPad.SetTopMargin(0.075)
    mainPad.SetBottomMargin(0.01)
    mainPad.SetRightMargin(0.07)
    mainPad.SetLeftMargin(0.15)

    ratPad = ROOT.TPad( "p_rat", "p_rat", 0.0, 0.0, 1.0, 0.3)
    ratPad.SetTopMargin(0.10)
    ratPad.SetBottomMargin(0.35)
    ratPad.SetRightMargin(0.07)
    ratPad.SetLeftMargin(0.15)
    ratPad.SetGridy()
    ratPad.SetTicks()

    return mainPad, ratPad

def annotate():
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(42)
    latex.SetTextAlign(13)
    latex.SetTextSize(0.04)
    latex.DrawLatex( 0.18, 0.890, "#bf{CMS} #it{Preliminary}" )

    #latex.SetTextSize(0.03)
    #latex.DrawLatex( 0.73, 0.97, "#scale[1.2]{138 fb^{-1} (13#scale[0.75]{ }TeV)}" )

def load_file(fileName):
    command = "ls %s" % fileName
    exe(command)

    fin = ROOT.TFile(fileName, 'R')
    m.vf[fileName] = fin

def draw_a_histogram(fin, color):
    h = fin.Get(m.var)

    nbins = h.GetSize()-2
    area = h.Integral(1, nbins+1)
    if area > 0.: h.Scale(1./area)

    h.SetTitle("")
    h.SetStats(0)
    h.SetLineWidth(2)
    h.SetLineColor(color)

    m.vh.append(h)

    if m.counter_drawn_histograms == 0:
        h.Draw("hist")
        m.counter_drawn_histograms += 1
    else:
        h.Draw("hist,same")

def get_ratio_hist(h1, h2):
    hr = h1.Clone()

    #xmin = h1.GetXaxis().GetXmin()
    #xmax = h1.GetXaxis().GetXmax()
    #nbins = h1.GetSize()-2
    #hr = ROOT.TH1D("ratio_%s" % m.var, "", nbins+1, xmin, xmax)

    for i in range(nbins+1):
        ibin = i+1
        v1 = h1.GetBinContent(ibin)
        v2 = h2.GetBinContent(ibin)
        if v2 == 0: continue
        ratio = v1 / v2

        if v1 == 0:
            error = 0.
        else:
            e1 = h1.GetBinError(ibin) / v1
            e2 = h2.GetBinError(ibin) / v2
            error = ratio * math.sqrt(math.pow(e1,2) + math.pow(e2,2))
        
        hr.SetBinContent(ibin, ratio)
        hr.SetBinError(ibin, error)

    return hr

def draw_ratio_pad():
    h = m.vh[0].Clone() # FW
    h_nwa = m.vh[1].Clone() # NWA

    h.Divide(h_nwa)
    #h = Divide(h_fw, h_nwa)
    #h = get_ratio_hist(h_fw, h_nwa)
    h.SetMarkerStyle(20)
    h.SetMarkerSize(1.25)
    h.SetMarkerColor(ROOT.kBlack)
    h.SetLineColor(ROOT.kBlack)

    # common
    h.SetStats(0)
    h.SetMaximum(2.)
    h.SetMinimum(0.)

    # label
    h.GetYaxis().SetNdivisions(5)
    h.GetYaxis().SetLabelSize(0.08)
    h.GetXaxis().SetLabelOffset()
    h.GetXaxis().SetLabelSize(0.08)

    # titles
    h.GetYaxis().SetTitle("#frac{#color[%d]{FW}}{#color[%d]{NWA}}" % (ROOT.kRed, ROOT.kBlue))
    h.GetYaxis().SetTitleSize(0.13)
    h.GetYaxis().SetTitleOffset(0.40)
    h.GetYaxis().CenterTitle()

    h.GetXaxis().SetLabelSize(0.10)
    h.GetYaxis().SetLabelSize(0.10)
    h.GetXaxis().SetLabelOffset(0.035)
    h.GetYaxis().SetLabelOffset(0.010)

    xtitle = m.var
    h.GetXaxis().SetTitle(xtitle)
    h.GetXaxis().SetTitleOffset(1.1)
    h.GetXaxis().SetTitleSize(0.13)

    return h

    #h.Draw("e0,x0")
    #h.Draw()

def set_maximum():
    values = [h.GetMaximum() for h in m.vh]
    maximum = max(values)
    for h in m.vh: h.SetMaximum(maximum*1.2)
