#!/usr/bin/env python
import subprocess
import ctypes
import array
import math
import ROOT
ROOT.gROOT.SetBatch(True)

do_individual=False
do_individual=True

dir_output = "EOS_output_mass"
rootfile = "plots_20211126/myhist_signal.root"
rootfile = "plots_20211127_v2/myhist_combine_RunII.root"
rootfile = "plots_20211128/myhist_combine_RunII.root"
rootfile = "shortcut_plots/plots_20211128/myhist_combine_RunII.root"
rootfile = "shortcut_plots/plots_20220120_results_ReReco/myhist_combine_RunII.root"
rootfile = "shortcut_plots/plots_20220215_ultraLegacy/myhist_combine_RunII.root"
fin = ROOT.TFile.Open(rootfile, "R")

ROOT.gStyle.SetOptStat("e")
ROOT.gStyle.SetOptFit(1111)

v_hist_collector, v_herrs_collector = [], []

# setup {{{
c1 = ROOT.TCanvas("c1", "", 800, 600)
c1.SetGrid()
c1.SetLeftMargin(0.12)
c1.SetRightMargin(0.08)

c2 = ROOT.TCanvas("c2", "", 1200, 600)
c2.SetGrid()
c2.SetLeftMargin(0.12)
c2.SetRightMargin(0.08)

d_fit_const = {"central":[], "error":[]}
d_fit_mean  = {"central":[], "error":[]}
d_fit_sigma = {"central":[], "error":[]}

#--------------------------------------------------

lumi={"2016":35.9,"2017":41.5,"2018":59.76,"RunII":137.2}

masses = [600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200]
masses_v2 = [600, 625, 650, 675, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200]
mass_M600_M700 = [600, 625, 650, 675, 700]
mass_M800_M1000 = [800, 900, 1000]
mass_M1100_M1200 = [1100, 1200]

ytitles = {
    "yields": {
        "hMass_fine":"Yields / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed03_fine":"Yields / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed04_fine":"Yields / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed05_fine":"Yields / 0.5 GeV",
        "hmass_tprime_cov_fine":"Yields / 5 GeV",
        "h_mass_tm_tprime":"Yields / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"Yields / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"Yields / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"Yields / 5 GeV",
    },
    "normalized": {
        "hMass_fine":"Arbitrary unit / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed03_fine":"Arbitrary unit / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed04_fine":"Arbitrary unit / 0.5 GeV",
        "hMass_pass_BDTG_smh_cut_mixed05_fine":"Arbitrary unit / 0.5 GeV",
        "hmass_tprime_cov_fine":"Arbitrary unit / 5 GeV",
        "h_mass_tm_tprime":"Arbitrary unit / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"Arbitrary unit / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"Arbitrary unit / 5 GeV",
        "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"Arbitrary unit / 5 GeV",
    },
}

xtitles = {
    "hMass_fine":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed03_fine":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed04_fine":"M_{#gamma#gamma} (GeV)",
    "hMass_pass_BDTG_smh_cut_mixed05_fine":"M_{#gamma#gamma} (GeV)",
    "hmass_tprime_cov_fine":"M_{bjj#gamma#gamma} (GeV)",
    "h_mass_tm_tprime":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":"M_{bjj#gamma#gamma} (GeV)",
}

v_set1 = {
    #600  : ROOT.kMagenta,
    #625  : ROOT.kMagenta+2,
    600  : ROOT.kRed-9,
    625  : ROOT.kRed-7,
    650  : ROOT.kRed,
    675  : ROOT.kRed+2,
    700  : ROOT.kRed+4,
    800  : ROOT.kGreen-5,
    900  : ROOT.kGreen+1,
    1000 : ROOT.kGreen+3,
    1100 : ROOT.kBlue,
    1200 : ROOT.kBlue+2,
}

v_set2 = {
    600  : ROOT.kOrange,
    625  : ROOT.kOrange+2,
    650  : ROOT.kRed,
    675  : ROOT.kRed+3,
    700  : ROOT.kBlack,
    800  : ROOT.kGreen+1,
    900  : ROOT.kGreen+3,
    1000 : ROOT.kCyan,
    1100 : ROOT.kBlue,
    1200 : ROOT.kBlue+2,
}

v_blue = {
    600  : ROOT.kBlue-10,
    625  : ROOT.kBlue-9,
    650  : ROOT.kBlue-7,
    675  : ROOT.kBlue-4,
    700  : ROOT.kBlue,
    800  : ROOT.kBlue+1,
    900  : ROOT.kBlue+2,
    1000 : ROOT.kBlue+3,
    1100 : ROOT.kBlue+4,
    1200 : ROOT.kBlack
}

v_red = {
    600  : ROOT.kRed-10,
    625  : ROOT.kRed-9,
    650  : ROOT.kRed-7,
    675  : ROOT.kRed-4,
    700  : ROOT.kRed,
    800  : ROOT.kRed+1,
    900  : ROOT.kRed+2,
    1000 : ROOT.kRed+3,
    1100 : ROOT.kRed+4,
    1200 : ROOT.kBlack
}

colors = {
    "hMass_fine":v_set1,
    "hMass_pass_BDTG_smh_cut_mixed03_fine":v_set1,
    "hMass_pass_BDTG_smh_cut_mixed04_fine":v_set1,
    "hMass_pass_BDTG_smh_cut_mixed05_fine":v_set1,
    "hmass_tprime_cov_fine":v_set1,
    "h_mass_tm_tprime":v_set1,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":v_set1,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":v_set1,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":v_set1,
    "collective":v_set2,
    #"hMass_fine":v_blue,
    #"hMass_pass_BDTG_smh_cut_mixed03_fine":v_blue,
    #"hMass_pass_BDTG_smh_cut_mixed04_fine":v_blue,
    #"hMass_pass_BDTG_smh_cut_mixed05_fine":v_blue,
    #"hmass_tprime_cov_fine":v_red,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":v_red,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":v_red,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":v_red,
}

ranges = {
    "hMass_fine":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed03_fine":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed04_fine":[100,180],
    "hMass_pass_BDTG_smh_cut_mixed05_fine":[100,180],
    "hmass_tprime_cov_fine":[200,2500],
    "h_mass_tm_tprime":[200,2500],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":[480,800],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":[630,1150],
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":[750,1600],
    "fullTprime":[350, 1650],
    #"fullTprime":[450, 1650],
}

leg_pos_set1 = {
    # key = number of mass points to be ploted in a figure
    10 : [0.58, 0.25, 0.85, 0.85],
    5  : [0.58, 0.55, 0.85, 0.85],
    3  : [0.58, 0.67, 0.85, 0.85],
    2  : [0.58, 0.73, 0.85, 0.85],
}

leg_pos_set2 = {
    # key = number of mass points to be ploted in a figure
    10 : [0.58, 0.25, 0.85, 0.85],
    3  : [0.58, 0.67, 0.85, 0.85],
    2  : [0.58, 0.73, 0.85, 0.85],
    5  : [0.12, 0.55, 0.30, 0.85],
}

leg_pos_set3 = [0.15, 0.75, 0.35, 0.87]
leg_pos_set4 = [0.17, 0.45, 0.35, 0.57]
leg_pos_set5 = [0.57, 0.20, 0.87, 0.35]

legend_position = {
    "hMass_fine":leg_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed03_fine":leg_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed04_fine":leg_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed05_fine":leg_pos_set1,
    "hmass_tprime_cov_fine":leg_pos_set2,
    "h_mass_tm_tprime":leg_pos_set2,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":leg_pos_set2,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":leg_pos_set2,
    "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":leg_pos_set2,
    # individual plot with fit
    "tprime":leg_pos_set5,
    600 :leg_pos_set3,
    625 :leg_pos_set3,
    650 :leg_pos_set3,
    675 :leg_pos_set4,
    700 :leg_pos_set4,
    800 :leg_pos_set3,
    900 :leg_pos_set3,
    1000:leg_pos_set4,
    1100:leg_pos_set3,
    1200:leg_pos_set3,
}

stat_pos_set1 = [0.89, 0.87, 0.20, 0.20]
stat_pos_set2 = [0.89, 0.87, 0.15, 0.15]
stat_pos_set3 = [0.43, 0.87, 0.15, 0.15]
stat_position = {
    "hMass_fine":stat_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed03_fine":stat_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed04_fine":stat_pos_set1,
    "hMass_pass_BDTG_smh_cut_mixed05_fine":stat_pos_set1,
    "hmass_tprime_cov_fine":stat_pos_set1,
    "h_mass_tm_tprime":stat_pos_set1,
    600 :stat_pos_set2,
    625 :stat_pos_set2,
    650 :stat_pos_set2,
    675 :stat_pos_set3,
    700 :stat_pos_set3,
    800 :stat_pos_set2,
    900 :stat_pos_set2,
    1000:stat_pos_set3,
    1100:stat_pos_set2,
    1200:stat_pos_set2,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine":stat_pos_set2,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine":stat_pos_set2,
    #"hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine":stat_pos_set2,
}

fit_ranges = {
    # for fit summary
    "mgg"   :{ "range":[122., 128.] , "mean" :[123.5, 125.5], "sigma":[1.0, 1.8] },
    "tprime":{ "range":[500., 1300.], "mean" :[500., 1300.] , "sigma":[0., 80.] },

    # for individual fit
    600 :{ "range":[550. ,650.]  },
    625 :{ "range":[575. ,675.]  },
    650 :{ "range":[600. ,700.]  },
    675 :{ "range":[625. ,725.]  },
    700 :{ "range":[650. ,750.]  },
    800 :{ "range":[740. ,860.]  },
    900 :{ "range":[840. ,960.]  },
    1000:{ "range":[940. ,1060.] },
    1100:{ "range":[1020.,1180.] },
    1200:{ "range":[1120.,1280.] },

    #600 :{ "range":[540. ,660.]  },
    #625 :{ "range":[565. ,685.]  },
    #650 :{ "range":[590. ,710.]  },
    #675 :{ "range":[615. ,735.]  },
    #700 :{ "range":[640. ,760.]  },
    #800 :{ "range":[720. ,880.]  },
    #900 :{ "range":[820. ,980.]  },
    #1000:{ "range":[920. ,1080.] },
    #1100:{ "range":[1020.,1180.] },
    #1200:{ "range":[1120.,1280.] },
}

fit_ytitles = {
    "mgg":{
        "range":"Mean and sigma of m(#gamma#gamma) from Gaussian fit",
        "mean" :"Mean of m(#gamma#gamma) from Gaussian fit",
        "sigma":"Sigma of m(#gamma#gamma) from Gaussian fit",
    },
    "tprime":{
        "range":"Mean and sigma of M_{bjj#gamma#gamma} from Gaussian fit",
        "mean" :"Mean of M_{bjj#gamma#gamma} from Gaussian fit",
        "sigma":"Sigma of M_{bjj#gamma#gamma} from Gaussian fit",
    },
}
#}}}
def get_maximum(v): #{{{
    result = 0.
    for h in v:
        hmax = h.GetMaximum()
        if hmax > result:
            result = hmax

    return result
#}}}
def annotate(rshift=0): #{{{
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(24)
    latex.DrawLatex( 0.12, 0.912, "#bf{CMS} #it{work in progress}" )
    latex.DrawLatex( 0.69+rshift, 0.912, "%s fb^{-1} (13 TeV)" % str(lumi["RunII"]) )

    #latex.DrawLatex( 0.60, 0.800, "Pre-selection" )
#}}}
def set_the_hist(h, varName, rangeTag, plotType, color): #{{{
    h.SetStats(0)
    #h.SetLineColor(colors[varName][myMasses[i]])
    h.SetLineColor(color)
    h.SetLineWidth(2)
    h.GetXaxis().SetTitleOffset(1.2)
    h.GetYaxis().SetTitle(ytitles[plotType][varName])
    h.GetXaxis().SetTitle(xtitles[varName])
    h.GetXaxis().SetRangeUser(ranges[rangeTag][0], ranges[rangeTag][1])
#}}}
def set_the_error_band(h): #{{{
    #h.SetFillStyle(3144)
    h.SetFillStyle(3001)
    h.SetFillColorAlpha(ROOT.kBlack, 0.5)
    h.SetMarkerStyle(20)
    h.SetMarkerSize(0.)
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
def init_fit_containers(): #{{{
    global d_fit_const, d_fit_mean, d_fit_sigma
    d_fit_const = {"central":[], "error":[]}
    d_fit_mean  = {"central":[], "error":[]}
    d_fit_sigma = {"central":[], "error":[]}
#}}}
def init_hist_collector(): #{{{
    global v_hist_collector, v_herrs_collector
    v_hist_collector, v_herrs_collector = [], []
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
def make_fit_summary(d_raw, v_bound, ytitle, output): #{{{
    n = len(d_raw["central"]) 
    x = array.array('d')
    y = array.array('d')
    ex = array.array('d')
    ey = array.array('d')

    for i in range(n):
        x.append(masses[i])
        y.append(d_raw["central"][i]) 
        ex.append(0.)
        ey.append(d_raw["error"][i])

    gr = ROOT.TGraphErrors(n, x, y, ex, ey)
    set_graph(gr, ytitle, ROOT.kBlack)
    gr.Draw('ACP')

    gr.SetMinimum(v_bound[0])
    gr.SetMaximum(v_bound[1])

    # local leg
    #legend = ROOT.TLegend(0.15, 0.60, 0.40, 0.85)
    #legend.SetLineColor(0)
    #legend.SetTextSize(0.04)
    #legend.AddEntry(gr1, "[600, 700]", "lp")
    #legend.AddEntry(gr2, "[800, 1000]", "lp")
    #legend.AddEntry(gr3, "[1100, 1200]", "lp")
    #legend.Draw("same")
    print ">>>>> central:", output, d_raw["central"]
    print ">>>>> error:  ", output, d_raw["error"]

    # wrap up
    annotate()
    output = dir_output + "/fitSummary_" + output + ".png"
    c1.SaveAs(output)
#}}}
def make_plot(varName, myMasses, plotType, pauseFit): #{{{
    c1.cd()
    nameTag = varName + "_" + plotType

    pos = legend_position[varName][len(myMasses)]
    legend = ROOT.TLegend(pos[0], pos[1], pos[2], pos[3])
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.Clear()
    if len(myMasses)==5 and 'prime' in varName: legend.SetTextSize(0.03)

    # load hists {{{
    v_hists, v_herrs = [], []
    for m in myMasses:
        histName = varName + "_TprimeBToTH_M-" + str(m)
        h = fin.Get(histName)
        v_hists.append(h)

        h_err = h.Clone()
        v_herrs.append(h_err)
    #}}}
    # loop over hists
    for i, h in enumerate(v_hists):
        h_err = v_herrs[i]

        # normalize area #{{{
        if plotType == "normalized":
            unc = ctypes.c_double(0.) 
            nbins = h.GetSize()-1
            tot_yields = h.IntegralAndError(0, nbins, unc)
            if tot_yields > 0.:
                h.Scale(1./tot_yields)
                h_err.Scale(1./tot_yields)
        #}}}
        if do_individual: #{{{
            my_fit_range = fit_ranges["mgg"]["range"] if 'hMass' in varName else fit_ranges[myMasses[i]]["range"]
            set_the_hist(h, varName, varName, plotType, ROOT.kBlack)

            h.SetMaximum( h.GetMaximum()*1.2 )
            h.Draw("hist")
            h.Fit("gaus", "", "", my_fit_range[0], my_fit_range[1])

            # necessary for showing fit curves
            h_err = h.Clone()
            set_the_error_band(h_err)
            h_err.Draw("E2;same")

            my_leg_pos = legend_position[myMasses[i]] if 'prime' in varName and 'BDTG' in varName else legend_position["tprime"]
            leg = ROOT.TLegend(my_leg_pos[0],my_leg_pos[1],my_leg_pos[2],my_leg_pos[3])
            leg.SetLineColor(0)
            leg.SetTextSize(0.04)
            leg.AddEntry(h, "M_{T'} = " + str(myMasses[i]) + " GeV", "l")
            leg.AddEntry(h_err, "Stat. unc.", "f")
            leg.Draw("same")

            h.SetStats(1)
            record_fit_result( h.GetListOfFunctions().FindObject("gaus") )
            
            my_stat_pos = stat_position[myMasses[i]] if 'prime' in varName and 'BDTG' in varName else stat_position[varName]
            ROOT.gStyle.SetStatX(my_stat_pos[0])
            ROOT.gStyle.SetStatY(my_stat_pos[1])
            ROOT.gStyle.SetStatW(my_stat_pos[2])
            ROOT.gStyle.SetStatH(my_stat_pos[3])

            annotate()
            output = dir_output + "/individual_" + nameTag + "_" + str(myMasses[i]) + ".png"
            c1.SaveAs(output)
            output = dir_output + "/individual_" + nameTag + "_" + str(myMasses[i]) + ".pdf"
            c1.SaveAs(output)
        #}}}
        else: # multi hists {{{
            set_the_hist(h, varName, varName, plotType, colors[varName][myMasses[i]])
            set_the_error_band(h_err)

            legend.AddEntry(h, "M_{T'} = " + str(myMasses[i]) + " GeV", "l")
            if i == 0: h.Draw("hist")
            else: h.Draw("hist;same")
            h_err.Draw("E2;same")
        #}}}

    # wrap up #{{{
    if do_individual:
        if not pauseFit:
            my_fit_range = fit_ranges["mgg"] if 'hMass' in varName else fit_ranges["tprime"]
            my_fit_ytitle = fit_ytitles["mgg"] if 'hMass' in varName else fit_ytitles["tprime"]
            d_fit = {"central":d_fit_mean["central"], "error":d_fit_sigma["central"]}
            make_fit_summary(d_fit       , my_fit_range['range'] , my_fit_ytitle['range'], nameTag + "_Gaussian")
            make_fit_summary(d_fit_mean  , my_fit_range['mean']  , my_fit_ytitle['mean' ], nameTag + "_Mean")
            make_fit_summary(d_fit_sigma , my_fit_range['sigma'] , my_fit_ytitle['sigma'], nameTag + "_Sigma")

            init_fit_containers()

    else:
        if not pauseFit:
            maximum = get_maximum(v_hists)
            v_hists[0].SetMaximum(maximum*1.2)

            annotate()
            legend.Draw("same")
            output = dir_output + "/" + nameTag + ".png"
            c1.SaveAs(output)

            init_hist_collector()
    #}}}
#}}}
def make_collective_plot(v_varName, v_myMasses, plotType): #{{{
    nameTag = "collective_" + v_varName[-1] + "_" + plotType

    isHiggs = 'hMass' in v_varName[0]
    isTprime = not isHiggs

    c2.cd()
    legend = ROOT.TLegend(0, 0, 0, 0)
    if isTprime and plotType == "normalized":
        legend = ROOT.TLegend(0.70, 0.25, 0.90, 0.85)
    else:
        legend = ROOT.TLegend(0.70, 0.25, 0.90, 0.87)

    legend.SetLineColor(0)
    legend.SetTextSize(0.04)

    # load hists {{{
    v_hists, v_herrs, myMasses, myVarName= [], [], [], []
    for i, varName in enumerate(v_varName):
        for m in v_myMasses[i]:
            histName = varName + "_TprimeBToTH_M-" + str(m)
            h = fin.Get(histName)
            v_hists.append(h)

            h_err = h.Clone()
            v_herrs.append(h_err)
            
            myMasses.append(m)
            myVarName.append(varName)

            entries = h.GetEntries()
            print ">>> load:", histName, entries
    #}}}
    # loop over hists
    for i, h in enumerate(v_hists):
        h_err = v_herrs[i]

        # normalize area #{{{
        if plotType == "normalized":
            unc = ctypes.c_double(0.) 
            nbins = h.GetSize()-1
            tot_yields = h.IntegralAndError(0, nbins, unc)
            if tot_yields > 0.:
                h.Scale(1./tot_yields)
                h_err.Scale(1./tot_yields)
        #}}}

        rangeTag = "fullTprime" if isTprime else myVarName[i]
        set_the_hist(h, myVarName[i], rangeTag, plotType, colors["collective"][myMasses[i]])
        set_the_error_band(h_err)

        legend.AddEntry(h, "M_{T'} = " + str(myMasses[i]) + " GeV", "l")
        if i == 0: h.Draw("hist")
        else: h.Draw("hist;same")
        h_err.Draw("E2;same")

    maximum = get_maximum(v_hists)
    v_hists[0].SetMaximum(maximum*1.2)

    legend.Draw("same")
    output = dir_output + "/" + nameTag

    if isTprime and plotType == "normalized":
        annotate()
        c2.SetLogy(0)
        c2.SaveAs(output + ".png")
        c2.SaveAs(output + ".pdf")
    else:
        annotate(0.08)
        v_hists[0].SetMaximum(2)
        v_hists[0].SetMinimum(3e-3)
        c2.SetLogy(1)
        c2.SaveAs(output + ".png")
        c2.SaveAs(output + ".pdf")
        #c1.SaveAs(output + ".png")
        #c1.SaveAs(output + ".pdf")
#}}}

def truth_matched_make_plot(varName, myMasses, plotType, pauseFit): #{{{
    c1.cd()
    nameTag = varName + "_" + plotType

    pos = legend_position[varName][len(myMasses)]
    legend = ROOT.TLegend(pos[0], pos[1], pos[2], pos[3])
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.Clear()

    # load hists {{{
    v_fins, v_hists, v_herrs = [], [], []
    for m in myMasses:
        #_truthMatching_v1
        rootfile = "shortcut_plots/plots_20220219_ultraLegacy_truthMatchStudy/covMatrix_TprimeBToTH_M-%d_merged.root" % m
        fin = ROOT.TFile.Open(rootfile, "R")
        histName = varName
        h = fin.Get(histName)
        v_hists.append(h)
        h_err = h.Clone()
        v_herrs.append(h_err)

        v_fins.append(fin)
    #}}}
    # loop over hists
    for i, h in enumerate(v_hists):
        h_err = v_herrs[i]

        # normalize area #{{{
        if plotType == "normalized":
            unc = ctypes.c_double(0.) 
            nbins = h.GetSize()-1
            tot_yields = h.IntegralAndError(0, nbins, unc)
            if tot_yields > 0.:
                h.Scale(1./tot_yields)
                h_err.Scale(1./tot_yields)
        #}}}
        if do_individual: #{{{
            my_fit_range = fit_ranges["mgg"]["range"] if 'hMass' in varName else fit_ranges[myMasses[i]]["range"]
            set_the_hist(h, varName, varName, plotType, ROOT.kBlack)

            h.SetMaximum( h.GetMaximum()*1.2 )
            h.Draw("hist")
            h.Fit("gaus", "", "", my_fit_range[0], my_fit_range[1])

            # necessary for showing fit curves
            h_err = h.Clone()
            set_the_error_band(h_err)
            h_err.Draw("E2;same")

            my_leg_pos = legend_position[myMasses[i]] if 'prime' in varName and 'BDTG' in varName else legend_position["tprime"]
            leg = ROOT.TLegend(my_leg_pos[0],my_leg_pos[1],my_leg_pos[2],my_leg_pos[3])
            leg.SetLineColor(0)
            leg.SetTextSize(0.04)
            leg.AddEntry(h, "M_{T'} = " + str(myMasses[i]) + " GeV", "l")
            leg.AddEntry(h_err, "Stat. unc.", "f")
            leg.Draw("same")

            h.SetStats(1)
            record_fit_result( h.GetListOfFunctions().FindObject("gaus") )
            
            my_stat_pos = stat_position[myMasses[i]] if 'prime' in varName and 'BDTG' in varName else stat_position[varName]
            ROOT.gStyle.SetStatX(my_stat_pos[0])
            ROOT.gStyle.SetStatY(my_stat_pos[1])
            ROOT.gStyle.SetStatW(my_stat_pos[2])
            ROOT.gStyle.SetStatH(my_stat_pos[3])

            annotate()
            output = dir_output + "/individual_" + nameTag + "_" + str(myMasses[i]) + ".png"
            c1.SaveAs(output)
            output = dir_output + "/individual_" + nameTag + "_" + str(myMasses[i]) + ".pdf"
            c1.SaveAs(output)
        #}}}
        else: # multi hists {{{
            set_the_hist(h, varName, varName, plotType, colors[varName][myMasses[i]])
            set_the_error_band(h_err)

            legend.AddEntry(h, "M_{T'} = " + str(myMasses[i]) + " GeV", "l")
            if i == 0: h.Draw("hist")
            else: h.Draw("hist;same")
            h_err.Draw("E2;same")
        #}}}

    # wrap up #{{{
    if do_individual:
        if not pauseFit:
            my_fit_range = fit_ranges["mgg"] if 'hMass' in varName else fit_ranges["tprime"]
            my_fit_ytitle = fit_ytitles["mgg"] if 'hMass' in varName else fit_ytitles["tprime"]
            d_fit = {"central":d_fit_mean["central"], "error":d_fit_sigma["central"]}
            make_fit_summary(d_fit       , my_fit_range['range'] , my_fit_ytitle['range'], nameTag + "_Gaussian")
            make_fit_summary(d_fit_mean  , my_fit_range['mean']  , my_fit_ytitle['mean' ], nameTag + "_Mean")
            make_fit_summary(d_fit_sigma , my_fit_range['sigma'] , my_fit_ytitle['sigma'], nameTag + "_Sigma")

            init_fit_containers()

    else:
        if not pauseFit:
            maximum = get_maximum(v_hists)
            v_hists[0].SetMaximum(maximum*1.2)

            annotate()
            legend.Draw("same")
            output = dir_output + "/" + nameTag + ".png"
            c1.SaveAs(output)

            init_hist_collector()
    #}}}
#}}}
def truth_matched_make_collective_plot(v_varName, v_myMasses, plotType): #{{{
    nameTag = "collective_" + v_varName[-1] + "_" + plotType

    isHiggs = 'hMass' in v_varName[0]
    isTprime = not isHiggs

    c2.cd()
    legend = ROOT.TLegend(0, 0, 0, 0)
    if isTprime and plotType == "normalized":
        legend = ROOT.TLegend(0.70, 0.25, 0.90, 0.85)
        legend.SetTextSize(0.04)
    else:
        #legend = ROOT.TLegend(0.62, 0.40, 0.87, 0.87)
        legend = ROOT.TLegend(0.70, 0.25, 0.90, 0.87)
        legend.SetTextSize(0.03)

    legend.SetLineColor(0)
    legend.SetTextSize(0.04)

    # load hists {{{
    v_fins, v_hists, v_herrs, myMasses, myVarName = [], [], [], [], []
    for i, varName in enumerate(v_varName):
        for m in v_myMasses[i]:
            rootfile = "shortcut_plots/plots_20220219_ultraLegacy_truthMatchStudy/covMatrix_TprimeBToTH_M-%d_merged.root" % m
            fin = ROOT.TFile.Open(rootfile, "R")
            histName = varName
            h = fin.Get(histName)
            v_hists.append(h)

            h_err = h.Clone()
            v_herrs.append(h_err)
            
            myMasses.append(m)
            myVarName.append(varName)

            v_fins.append(fin)

            entries = h.GetEntries()
            print ">>> load:", histName, entries
    #}}}
    # loop over hists
    for i, h in enumerate(v_hists):
        h_err = v_herrs[i]

        # normalize area #{{{
        if plotType == "normalized":
            unc = ctypes.c_double(0.) 
            nbins = h.GetSize()-1
            tot_yields = h.IntegralAndError(0, nbins, unc)
            if tot_yields > 0.:
                h.Scale(1./tot_yields)
                h_err.Scale(1./tot_yields)
        #}}}

        rangeTag = "fullTprime" if isTprime else myVarName[i]
        set_the_hist(h, myVarName[i], rangeTag, plotType, colors["collective"][myMasses[i]])
        set_the_error_band(h_err)

        legend.AddEntry(h, "M_{T'} = " + str(myMasses[i]) + " GeV", "l")
        if i == 0: h.Draw("hist")
        else: h.Draw("hist;same")
        h_err.Draw("E2;same")

    maximum = get_maximum(v_hists)
    v_hists[0].SetMaximum(maximum*1.2)

    legend.Draw("same")
    output = dir_output + "/" + nameTag

    if isTprime and plotType == "normalized":
        annotate(0.08)
        c2.SaveAs(output + ".png")
        c2.SaveAs(output + ".pdf")
    else:
        #v_hists[0].SetMaximum(maximum*1e+3)
        #annotate()
        #c1.SetLogy(1)
        #c1.SaveAs(output + ".png")
        #c1.SaveAs(output + ".pdf")

        annotate(0.08)
        v_hists[0].SetMaximum(2e-2)
        v_hists[0].SetMinimum(5e-5)
        c2.SetLogy(1)
        c2.SaveAs(output + ".png")
        c2.SaveAs(output + ".pdf")
#}}}
def run():
    plotTypes = ["yields", "normalized"]
    for plotType in plotTypes:
        #truth_matched_make_collective_plot(["h_mass_tm_tprime"], [masses], plotType)
        #truth_matched_make_plot("h_mass_tm_tprime", masses, plotType, pauseFit=False)

        make_collective_plot(["hmass_tprime_cov_fine"], [masses], plotType)
        make_plot("hmass_tprime_cov_fine", masses, plotType, pauseFit=False)
        #make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine", mass_M600_M700, plotType, pauseFit=True);
        #make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine", mass_M800_M1000, plotType, pauseFit=True);
        #make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine", mass_M1100_M1200, plotType, pauseFit=False);

        break

        # truth-matched tprime mass
        truth_matched_make_plot("h_mass_tm_tprime", masses, plotType, pauseFit=False)
        truth_matched_make_collective_plot(["h_mass_tm_tprime"], [masses], plotType)

        # collective mass at pre-selection
        make_collective_plot(["hMass_fine"], [masses], plotType)
        make_collective_plot(["hmass_tprime_cov_fine"], [masses], plotType)

        # collective mass in SRs
        v_myMasses = [mass_M600_M700, mass_M800_M1000, mass_M1100_M1200]
        v_varName = ["hMass_pass_BDTG_smh_cut_mixed03_fine", "hMass_pass_BDTG_smh_cut_mixed04_fine", "hMass_pass_BDTG_smh_cut_mixed05_fine"]
        make_collective_plot(v_varName, v_myMasses, plotType)
        v_varName = ["hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine", "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine", "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine"]
        make_collective_plot(v_varName, v_myMasses, plotType)

        # individual tprime mass
        make_plot("hmass_tprime_cov_fine", masses, plotType, pauseFit=False)
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine", mass_M600_M700, plotType, pauseFit=True);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine", mass_M800_M1000, plotType, pauseFit=True);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine", mass_M1100_M1200, plotType, pauseFit=False);

        # individual diphoton mass
        make_plot("hMass_fine", masses, plotType, pauseFit=False)
        make_plot("hMass_pass_BDTG_smh_cut_mixed03_fine", mass_M600_M700, plotType, pauseFit=True);
        make_plot("hMass_pass_BDTG_smh_cut_mixed04_fine", mass_M800_M1000, plotType, pauseFit=True);
        make_plot("hMass_pass_BDTG_smh_cut_mixed05_fine", mass_M1100_M1200, plotType, pauseFit=False);

# myParameterSets {{{
myParameterSets = {
    "eff":{
        "ybound" : [0.0, 0.5],
        "legend" : [0.17, 0.60, 0.42, 0.85],
    },
    "ratio":{
        "ybound" : [0.8, 2.0],
        "legend" : [0.60, 0.60, 0.85, 0.85],
    },
    "significance":{
        "ybound" : [0., 0.1],
        "legend" : [0.17, 0.60, 0.42, 0.85],
    },
}
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
    "set3":{
        # UL signal efficiency of opt2
        "raw_M600_M700"  : [ 0.07114, 0.08517, 0.09706, 0.10479, 0.10776, 0.06358, 0.01886, 0.01027, 0.00701, 0.00462 ],
        "raw_M800_M1000" : [ 0.01006, 0.01513, 0.02305, 0.03451, 0.04970, 0.12768, 0.18943, 0.21193, 0.18650, 0.09700 ],
        "raw_M1100_1200" : [ 0.00320, 0.00438, 0.00594, 0.00822, 0.01101, 0.03480, 0.10923, 0.20500, 0.26490, 0.29458 ],
    },
}
#}}}
# collection_background {{{
collection_background = {
    "set1":{"SR1":13., "SR2":13., "SR3":15.},
    "set2":{"SR1":13., "SR2":13., "SR3":19.},
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
def get_significance(tag, key): #{{{
    result = []
    efficiency = collection_efficiency[tag][key]
    for i in range(len(efficiency)):
        if i<5: nbkg = collection_background[tag]["SR1"]
        elif i<8: nbkg = collection_background[tag]["SR2"]
        else: nbkg = collection_background[tag]["SR3"]

        significance = efficiency[i] / math.sqrt(nbkg)
        result.append( significance )
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
    elif tag == "ratio":
        raw_M600_M700  = get_ratio_list("raw_M600_M700")
        raw_M800_M1000 = get_ratio_list("raw_M800_M1000")
        raw_M1100_1200 = get_ratio_list("raw_M1100_1200")
    elif "significance" in tag:
        subtag = tag.split(',')[0]
        raw_M600_M700  = get_significance(subtag, "raw_M600_M700")
        raw_M800_M1000 = get_significance(subtag, "raw_M800_M1000")
        raw_M1100_1200 = get_significance(subtag, "raw_M1100_1200")
    else:
        print ">>> [ERROR] The tag is not defined. Please check the code."
        return


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
def print_table(): #{{{
    d_truthMatched = {
        # UL
        "central" : {
            "mean"  : [591.7422245535906, 616.7964678175068, 641.9047186627778, 667.3478854771507, 692.3606143580628, 792.0191005498772, 892.4164252671072, 992.6634130718895, 1090.1128494807404, 1189.938400902008],
            "sigma" : [33.40508596772729, 34.20618757373258, 34.50885359376469, 35.04579960480873, 35.80212050685839, 38.792532761728026, 41.36244636938451, 43.70585311373045, 48.62135898031542, 51.10782569213134],
        },
        "error" : {
            "mean" : [0.15837716001231042, 0.16484834775422239, 0.16365022172250895, 0.16692821854651974, 0.1720523169764633, 0.15840150753714166, 0.17760178590559034, 0.2035290555776958, 0.21565871974897613, 0.22941976666599112],
            "sigma" : [0.18223440669885704, 0.19492125961547302, 0.19587963206512882, 0.20274542003327412, 0.21328739171438826, 0.1822684420800016, 0.21807604905107425, 0.26264968718811943, 0.235612971307539, 0.2618688427925555],
        },
        # re-reco
        #"mean"  : [591.6356280075765, 617.0505835075256, 641.7154687861536, 667.2351406292238, 691.9987463351088, 791.8962036666315, 892.404825524083, 992.3640684839321, 1090.1008777524553, 1189.7729364519132],
        #"sigma" : [33.47260805675623, 33.64542645597922, 34.75886025719647, 34.96547808286919, 36.09416659587231, 38.84964860907429, 41.66784483821874, 43.77282160024162, 47.88652410255988, 50.95605874794532],
    }
    
    d_chi2Reco = {
        # UL
        "central" : {
            "mean"  : [594.4624161244712, 619.4435721482763, 644.3618195271547, 670.1065013996899, 694.6075424249361, 794.3459354102622, 894.7819784051075, 995.4243019532349, 1094.9337136248432, 1196.2570310956594],
            "sigma" : [42.505079436417596, 43.05969017577434, 42.96212829444454, 43.318045977212954, 44.01516163583761, 48.1275650345531, 50.034969946084104, 53.305246378014814, 61.48481629383566, 64.997354327005],
        },
        "error" : {
            "mean" : [0.1872437624688, 0.19388744757311074, 0.1912572137345035, 0.19240116113910952, 0.19980871854810295, 0.18789903288597729, 0.2032028693325588, 0.23340595973935124, 0.23766980974557345, 0.255301617418865],
            "sigma" : [0.2916677337105753, 0.3072521263809591, 0.2998432774143005, 0.30725343579861786, 0.32028291079482685, 0.27930035173433865, 0.31560937630962016, 0.3860828961652416, 0.34836561102383357, 0.39834118844757427],
        },
        # re-reco
        #"mean"  : [594.5139804215879, 619.6000533950236, 644.3287027625523, 669.8153555829203, 694.6125449011694, 794.5142070223213, 894.8067276613455, 995.0613712066372, 1094.8835918972766, 1196.290542653962],
        #"sigma" : [42.292654944597054, 42.837103189639755, 43.66046201681102, 43.216809922131155, 44.34587740990952, 48.366166248595555, 50.47963630239109, 53.399695259135484, 60.92999143647047, 65.25723594233416],
    }

    d_optimizedSRs = {
        # UL
        "mean"  : [599.0794873121029, 622.2173375901691, 646.0866086326679, 670.8964323419657, 694.7780728183799, 796.9769300765835, 895.5581385152174, 995.254029915167, 1096.1191328943892, 1196.1605032706486],
        "sigma" : [36.3324058100035, 38.17465830328524, 37.62849983402401, 38.327823063790184, 39.48041605717497, 43.06817618168014, 46.03411687158084, 49.71573618608189, 58.165514497174506, 62.49492133972582],
        # re-reco
        #"mean"  : [598.2945430239862, 622.0008032250128, 645.5207252048275, 670.693154707722, 694.6167128213145, 796.889235945871, 895.4720117244987, 994.6950616907042, 1095.5454900556917, 1196.0433062029094],
        #"sigma" : [36.802685605145996, 37.534065345159945, 38.59124791321471, 38.62303670409102, 39.96873417547624, 43.804972473451556, 46.60216411747778, 49.900477862828545, 57.70042792695089, 62.767913101575516],
    }

    d = d_chi2Reco
    d = d_truthMatched
    for i, mass in enumerate(masses):
        pairs = []
        pairs.append( "%6.1f $\\pm$ %.1f" % (d_chi2Reco    ["central"]["mean"][i]  , d_chi2Reco    ["error"]["mean"][i])  )
        pairs.append( "%4.1f $\\pm$ %.1f" % (d_chi2Reco    ["central"]["sigma"][i] , d_chi2Reco    ["error"]["sigma"][i]) )

        pairs.append( "%6.1f $\\pm$ %.1f" % (d_truthMatched["central"]["mean"][i]  , d_truthMatched["error"]["mean"][i])  )
        pairs.append( "%4.1f $\\pm$ %.1f" % (d_truthMatched["central"]["sigma"][i] , d_truthMatched["error"]["sigma"][i]) )

        print "%4d & %s & %s & %s & %s \\\\" % (mass, pairs[0], pairs[1], pairs[2], pairs[3])
        #print "%4d & %5.1f & %.1f & %5.1f & %.1f \\\\" % (mass, v[0], v[1], v[2], v[3])
        #print "%d, %.2f, %.2f" % (mass, d["mean"][i], d["sigma"][i])
#}}}

if __name__ == "__main__":
    #run()
    print_table()

    #make_efficiency("Efficiency"         ,  myParameterSets["eff"]           ,  "set0"               ,  "signal_efficiency_old"        )
    #make_efficiency("Efficiency"         ,  myParameterSets["eff"]           ,  "set1"               ,  "signal_efficiency"            )
    #make_efficiency("Efficiency"         ,  myParameterSets["eff"]           ,  "set2"               ,  "signal_efficiency_newOpt"     )
    #make_efficiency("Efficiency"         ,  myParameterSets["eff"]           ,  "set3"               ,  "signal_efficiency"     )
    #make_efficiency("Ratio (Opt2/Opt1)"  ,  myParameterSets["ratio"]         ,  "ratio"              ,  "signal_efficiency_comparison" )
    #make_efficiency("Significance"       ,  myParameterSets["significance"]  ,  "set1,significance"  ,  "significance_opt1"            )
    #make_efficiency("Significance"       ,  myParameterSets["significance"]  ,  "set2,significance"  ,  "significance_opt2"            )

    subprocess.call("ls -lhrt %s" % dir_output, shell=True)

