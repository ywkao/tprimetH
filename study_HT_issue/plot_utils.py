#!/usr/bin/env python
import math
import ROOT
ROOT.gROOT.SetBatch(True)

lumi={"2016":35.9,"2017":41.5,"2018":59.76,"RunII":137}

def get_maximum(v): #{{{
    result = 0.
    for h in v:
        hmax = h.GetMaximum()
        if hmax > result:
            result = hmax

    return result
#}}}
def annotate(lshift=0, rshift=0): #{{{
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(24)
    latex.DrawLatex( 0.12 + lshift, 0.912, "#bf{CMS} #it{work in progress}" )
    #latex.DrawLatex( 0.72 - rshift, 0.912, "%s fb^{-1} (13 TeV)" % str(lumi["RunII"]) )
    latex.DrawLatex( 0.82 - rshift, 0.912, "13 TeV" )

    #latex.DrawLatex( 0.60, 0.800, "Pre-selection" )
#}}}
def set_the_hist(h, varName, ranges, plotType, xtitle, ytitle, color, dataLike = False): #{{{
    h.SetStats(0)
    #h.SetLineColor(colors[varName][myMasses[i]])
    if not dataLike:
        h.SetFillColor(color)
        h.SetLineColor(color)
        h.SetLineWidth(2)
    else:
        h.SetMarkerStyle(20)
        h.SetLineColor(ROOT.kBlack)
        h.SetLineWidth(1)

    h.GetYaxis().SetTitle(ytitle)
    h.GetXaxis().SetTitleOffset(1.02)
    h.GetYaxis().SetTitleSize(0.05)
    h.GetYaxis().SetLabelSize(0.04)

    h.GetXaxis().SetTitleOffset(1.2)
    h.GetXaxis().SetTitle(xtitle)
    h.GetXaxis().SetRangeUser(ranges[0], ranges[1])

    # hide label of upper plot when making ratio plots
    #h.GetXaxis().SetLabelOffset(999)
    #h.GetXaxis().SetLabelSize(0)
#}}}
def set_ratio_hist(h, xtitle): #{{{
  h.SetTitle("")
  h.SetStats(0)
  h.SetMarkerStyle(20)

  h.GetYaxis().SetRangeUser(0.0,2.0)
  h.GetYaxis().SetLabelSize(0.08)
  h.GetYaxis().SetNdivisions(5)
  h.GetYaxis().SetTitle("#frac{Data}{MC}")
  h.GetYaxis().SetTitleSize(0.10)
  h.GetYaxis().SetTitleOffset(0.50)
  h.GetYaxis().CenterTitle()

  h.GetXaxis().SetTitle(xtitle)
  h.GetXaxis().SetTitleOffset(1.1)
  h.GetXaxis().SetTitleSize(0.13)
  h.GetXaxis().SetLabelOffset()
  h.GetXaxis().SetLabelSize(0.08)
#}}}

def set_the_error_band(h): #{{{
    #h.SetFillStyle(3144)
    h.SetFillStyle(3001)
    h.SetFillColorAlpha(ROOT.kBlack, 0.5)
    h.SetMarkerStyle(20)
    h.SetMarkerSize(0.)
#}}}
def set_graph(gr, ytitle, xtitle, color): #{{{
    gr.SetTitle("")
    gr.SetLineColor(color)
    gr.SetLineWidth(2)
    gr.SetMarkerStyle(20)
    gr.SetMarkerColor(color)
    #gr.GetXaxis().SetTitle("Hypothetical M_{T'} (GeV)")
    gr.GetXaxis().SetTitle(xtitle)
    gr.GetYaxis().SetTitle(ytitle)
    gr.GetXaxis().SetTitleOffset(1.2)
#}}}
def init_fit_containers(): #{{{
    global d_fit_const, d_fit_mean, d_fit_sigma
    d_fit_const = {"central":[], "error":[]}
    d_fit_mean  = {"central":[], "error":[]}
    d_fit_sigma = {"central":[], "error":[]}
#}}}
def record_fit_result(func): #{{{
    global d_fit_const, d_fit_mean, d_fit_sigma

    fit_const = func.GetParameter(0)
    fit_mean  = func.GetParameter(1)
    fit_sigma = func.GetParameter(2)
    fitError_const = func.GetParError(0)
    fitError_mean  = func.GetParError(1)
    fitError_sigma = func.GetParError(2)
    print ">>> result:", fit_const, fit_mean, fit_sigma 
    print ">>> fit error:", fitError_const, fitError_mean, fitError_sigma 
    
    d_fit_const["central"].append( func.GetParameter(0) )
    d_fit_mean ["central"].append( func.GetParameter(1) )
    d_fit_sigma["central"].append( func.GetParameter(2) )
    d_fit_const[ "error" ].append( func.GetParError(0)  )
    d_fit_mean [ "error" ].append( func.GetParError(1)  )
    d_fit_sigma[ "error" ].append( func.GetParError(2)  )
#}}}

v_hist_collector, v_herrs_collector = [], []
def init_hist_collector(): #{{{
    global v_hist_collector, v_herrs_collector
    v_hist_collector, v_herrs_collector = [], []
#}}}

def get_total_yields(h, n=0): #{{{
    if n==0: n = h.GetSize()-1
    return h.Integral(0, n)
#}}}
def calclate_eff_unc(yd, ymc, emc): #{{{
    if yd == 0. or ymc == 0.:
        return 0.

    eff = yd/ymc
    rel_ed = math.sqrt(yd) / yd
    rel_emc = emc / ymc
    unc = eff * math.sqrt( pow(rel_ed,2) + pow(rel_emc,2) )
    return unc
#}}}

def get_my_legend(xlow, ylow, xhigh, yhigh): #{{{
    #legend = ROOT.TLegend(0.58, 0.60, 0.90, 0.85)
    #legend = ROOT.TLegend(0.50, 0.73, 0.72, 0.85)
    legend = ROOT.TLegend(xlow, ylow, xhigh, yhigh)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.Clear()
    return legend
#}}}
def set_scope(c1, h, scaleTag, maximum): #{{{
    if scaleTag == "linear":
        h.SetMaximum(maximum*1.5)
        h.SetMinimum(0.)
    else:
        h.SetMaximum(2e+5)
        h.SetMinimum(1)
        c1.SetLogy(1)
#}}}
def load_histograms(fin, processes, varName): #{{{
    v_hists, v_herrs = [], []
    for p in processes:
        histName = varName + "_" + str(p) + "Year_0"
        histName = varName + "_" + str(p) + "Year_1"
        histName = varName + "_" + str(p) + "Year_2"
        histName = varName + "_" + str(p)
        h = fin.Get(histName)
        v_hists.append(h)

        h_err = h.Clone()
        v_herrs.append(h_err)

    return v_hists, v_herrs
#}}}
