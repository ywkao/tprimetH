#!/usr/bin/env python2
import math
import ROOT
import metaData as m
ROOT.gROOT.SetBatch(True)

# init bins for x range
idx_xmin, idx_xmax = 1, 50

def register(fin, histname, tag, samples, legend):
    global idx_xmin, idx_xmax
    vh, tot_yields, tot_unc = [], 0., 0.

    for s in samples:
        name = histname + "_" + s
        h = fin.Get(name)

        rebin_factor = 5 if 'fine' in histname else 1
        h.Rebin(rebin_factor)

        nbins = h.GetSize()-2

        if tag == "data":
            h.SetLineWidth(2)
            h.SetLineColor(ROOT.kBlack)
            h.SetMarkerStyle(20)
            h.SetMarkerSize(1.25)
            h.SetMarkerColor(ROOT.kBlack)
            legend.AddEntry(h, "Data", 'ep')

            # obtain idx of bins for x range
            for i in range(0, nbins):
                idx = nbins - i
                idx_yields = h.GetBinContent(idx)
                if idx_yields > 0:
                    idx_xmax = idx
                    break

            for i in range(0, nbins):
                idx = i+1
                idx_yields = h.GetBinContent(idx)
                if idx_yields > 0:
                    idx_xmin = idx
                    break

        elif tag == "signals" or tag == "smHiggs":
            h.SetLineWidth(3)
            h.SetLineColor(m.map_colors[s])
            if tag == "signals":
                legend.AddEntry(h, m.map_labels[s], 'f')

        elif tag == "backgrounds":
            h.SetLineWidth(0)
            h.SetLineColor(m.map_colors[s])
            h.SetFillColor(m.map_colors[s])
            legend.AddEntry(h, m.map_labels[s], 'f')

        #print ">>>>> check: idx_xmin = ", idx_xmin
        #print ">>>>> check: idx_xmax = ", idx_xmax
        h.GetXaxis().SetRange(idx_xmin, idx_xmax)

        h.GetYaxis().SetLabelSize(0.10)
        h.GetYaxis().SetLabelOffset(0.010)

        overflow = h.Integral(idx_xmax+1, nbins+1)
        h.AddBinContent(idx_xmax, overflow)

        vh.append(h)

        #++++++++++++++++++++++++++++++++++++++++++++++++++
        # calculate yields
        #++++++++++++++++++++++++++++++++++++++++++++++++++
        unc = ROOT.Double(0)
        yields = h.IntegralAndError(0, nbins+1, unc);
        if tag == "backgrounds" or tag == "smHiggs":
            tot_yields += yields
            tot_unc += pow(unc, 2)
        #print ">>> %-12s, %-25s, %.2f \\pm %.2f" % (tag, s, yields, unc)

        #++++++++++++++++++++++++++++++++++++++++++++++++++
        # calculate yields in sideband
        #++++++++++++++++++++++++++++++++++++++++++++++++++
        #if histname == "hMass":

        #++++++++++++++++++++++++++++++++++++++++++++++++++
        # mgg negative bin study
        #++++++++++++++++++++++++++++++++++++++++++++++++++
        # print out each of four bins of [115, 135]
        if tag == "backgrounds":
            result, mybins = "", [24, 25, 26, 27]
            for i, ele in enumerate(mybins):
                content = "%.2f \\pm %.2f" % (h.GetBinContent(ele), h.GetBinError(ele))
                if i==0: result += content
                else: result += ",  " + content
            #print ">>> %-12s, %-25s, %s" % (tag, s, result)

    # report yields in mgg [115, 135]
    print_bkg_info = 'Tprime_Mass' in histname and (tag == "backgrounds" or tag == "smHiggs")
    if print_bkg_info:
        tot_unc = math.sqrt(tot_unc)
        print ">>> %-12s, %.2f \\pm %.2f" % (tag, tot_yields, tot_unc)

    return vh

def merge(samples, tag, legend):
    h_tot = samples[0].Clone()
    for i, h in enumerate(samples):
        if i == 0: continue
        h_tot.Add(h)

    h_tot.SetLineColor(ROOT.kBlack)
    if legend:
        if tag == "SMH":
            legend.AddEntry(h_tot, "SMH", 'f')
        elif tag == "NRB":
            legend.AddEntry(h_tot, "Stat. Unc.", 'f')

    return [h_tot]

def get_ratio(ratioName, histname, h_data, h_nrb):
    global idx_xmin, idx_xmax
    h = h_data.Clone()

    if ratioName == 'ratio_mc':
        for i in range(idx_xmin, idx_xmax+1):
            relative_error = h_nrb.GetBinError(i) / h_nrb.GetBinContent(i)
            h.SetBinContent(i, 1.)
            h.SetBinError(i, relative_error)

        h.SetLineColor(ROOT.kRed)
        h.SetMarkerSize(0)
        h.SetFillColorAlpha(ROOT.kRed, 0.25)

    else:
        h.Divide(h_nrb)
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
    #h.GetYaxis().SetTitle("#frac{Data}{MC}")
    h.GetYaxis().SetTitle("Data / MC")
    h.GetYaxis().SetTitleSize(0.13)
    h.GetYaxis().SetTitleOffset(0.40)
    h.GetYaxis().CenterTitle()

    h.GetXaxis().SetLabelSize(0.10)
    h.GetYaxis().SetLabelSize(0.10)
    h.GetXaxis().SetLabelOffset(0.035)
    h.GetYaxis().SetLabelOffset(0.010)

    xtitle = m.map_xtitles[histname]
    h.GetXaxis().SetTitle(xtitle)
    h.GetXaxis().SetTitleOffset(1.1)
    h.GetXaxis().SetTitleSize(0.13)

    #print ">>>>> check ratio: idx_xmin = ", idx_xmin
    #print ">>>>> check ratio: idx_xmax = ", idx_xmax
    h.GetXaxis().SetRange(idx_xmin, idx_xmax)
    return h

def init_canvas():
    #c1 = ROOT.TCanvas("c1", "", 600, 800)
    c1 = ROOT.TCanvas("c1", "", 600, 700)
    c1.SetGrid()
    c1.SetTicks()
    c1.SetLogy()
    return c1

def init_legend():
    #legend = ROOT.TLegend(0.37, 0.70, 0.92, 0.91)
    #legend = ROOT.TLegend(0.35, 0.70, 0.90, 0.91)
    #legend = ROOT.TLegend(0.33, 0.62, 0.88, 0.82)
    legend = ROOT.TLegend(0.25, 0.65, 0.90, 0.84)
    legend.SetTextSize(0.04)
    legend.SetNColumns(4)
    legend.SetLineColor(0)
    return legend

def init_pads():
    mainPad = ROOT.TPad("p_main", "p_main", 0.0, 0.3, 1.0, 1.0)
    mainPad.SetTopMargin(0.075)
    mainPad.SetBottomMargin(0.01)
    mainPad.SetRightMargin(0.07)
    mainPad.SetLeftMargin(0.15)
    mainPad.SetLogy()
    #mainPad.SetGrid()

    # this is not work ??
    mainPad.SetTicks()
    
    ratPad = ROOT.TPad( "p_rat", "p_rat", 0.0, 0.0, 1.0, 0.3)
    ratPad.SetTopMargin(0.10)
    ratPad.SetBottomMargin(0.35)
    ratPad.SetRightMargin(0.07)
    ratPad.SetLeftMargin(0.15)
    mainPad.SetTicks(1,0)
    ratPad.SetGridy()
    ratPad.SetTicks()

    return mainPad, ratPad

def annotate():
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(42)
    latex.SetTextAlign(13)
    latex.SetTextSize(0.04)
    #latex.DrawLatex( 0.18, 0.890, "#bf{CMS} #it{Preliminary}" )
    latex.DrawLatex( 0.18, 0.890, "#bf{CMS}" )

    latex.SetTextSize(0.04)
    latex.DrawLatex( 0.67, 0.98, "#scale[1.2]{138 fb^{-1} (13#scale[0.75]{ }TeV)}" )
    #latex.DrawLatex( 0.73, 0.97, "#scale[1.2]{138 fb^{-1} (13#scale[0.75]{ }TeV)}" )

def signal_selector(histname):
    if   histname == "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine" : return "TprimeBToTH_M-600"
    elif histname == "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine" : return "TprimeBToTH_M-900"
    elif histname == "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine" : return "TprimeBToTH_M-1200"
    elif histname == "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_MggWindow_fine" : return "TprimeBToTH_M-600"
    elif histname == "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_MggWindow_fine" : return "TprimeBToTH_M-900"
    elif histname == "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_MggWindow_fine" : return "TprimeBToTH_M-1200"
    else: return m.signals

def get_scale(histname):

    # Mgg in SRs
    if 'hMass_pass_BDTG_smh_cut_mixed0' in histname:
        return [1e-4, 1e+5]

    # Mbjjgg in SRs
    elif 'hTprime_Mass_pass_BDTG_smh_cut_mixed0' in histname:
        return [1e-2, 1e+2]

    # others
    else:
        return [1e-3, 1e+9]
