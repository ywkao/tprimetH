#!/usr/bin/env python
import subprocess
import ctypes
import array
import ROOT
ROOT.gROOT.SetBatch(True)

do_individual=True
do_individual=False

dir_output = "EOS_output_mass"
rootfile = "plots_20211126/myhist_signal.root"
rootfile = "plots_20211127_v2/myhist_combine_RunII.root"
rootfile = "shortcut_plots/plots_20211128/myhist_combine_RunII.root"
rootfile = "plots_20220215_ultraLegacy/myhist_combine_RunII.root"
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

lumi={"2016":35.9,"2017":41.5,"2018":59.76,"RunII":137}

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
def annotate(lshift=0): #{{{
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(24)
    latex.DrawLatex( 0.12, 0.912, "#bf{CMS} #it{work in progress}" )
    latex.DrawLatex( 0.72+lshift, 0.912, "%s fb^{-1} (13 TeV)" % str(lumi["RunII"]) )

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

def make_collective_plot(v_varName, v_myMasses, plotType):
    nameTag = "collective_" + v_varName[-1] + "_" + plotType

    isHiggs = 'hMass' in v_varName[0]
    isTprime = not isHiggs

    legend = ROOT.TLegend(0, 0, 0, 0)
    if isTprime and plotType == "normalized":
        c2.cd()
        legend = ROOT.TLegend(0.70, 0.25, 0.90, 0.85)
    else:
        c2.cd()
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
        annotate(0.06)
        v_hists[0].SetMaximum(2)
        v_hists[0].SetMinimum(3e-3)
        c2.SetLogy(1)
        c2.SaveAs(output + ".png")
        c2.SaveAs(output + ".pdf")

        #c1.SaveAs(output + ".png")
        #c1.SaveAs(output + ".pdf")
#}}}

def run():
    plotTypes = ["normalized"]
    plotTypes = ["yields", "normalized"]
    for plotType in plotTypes:
        #make_collective_plot(["hMass_fine"], [masses], plotType)
        #make_collective_plot(["hmass_tprime_cov_fine"], [masses], plotType)

        make_collective_plot(["hmass_tprime_cov_fine"], [masses], plotType)

        break

        v_myMasses = [mass_M600_M700, mass_M800_M1000, mass_M1100_M1200]
        v_varName = ["hMass_pass_BDTG_smh_cut_mixed03_fine", "hMass_pass_BDTG_smh_cut_mixed04_fine", "hMass_pass_BDTG_smh_cut_mixed05_fine"]
        make_collective_plot(v_varName, v_myMasses, plotType)
        v_varName = ["hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine", "hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine", "hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine"]
        make_collective_plot(v_varName, v_myMasses, plotType)

        continue 

        make_plot("hMass_fine", masses, plotType, pauseFit=False)
        make_plot("hMass_pass_BDTG_smh_cut_mixed03_fine", mass_M600_M700, plotType, pauseFit=True);
        make_plot("hMass_pass_BDTG_smh_cut_mixed04_fine", mass_M800_M1000, plotType, pauseFit=True);
        make_plot("hMass_pass_BDTG_smh_cut_mixed05_fine", mass_M1100_M1200, plotType, pauseFit=False);

        make_plot("hmass_tprime_cov_fine", masses, plotType, pauseFit=False)
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed03_SR_fine", mass_M600_M700, plotType, pauseFit=True);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed04_SR_fine", mass_M800_M1000, plotType, pauseFit=True);
        make_plot("hTprime_Mass_pass_BDTG_smh_cut_mixed05_SR_fine", mass_M1100_M1200, plotType, pauseFit=False);

def make_efficiency(): #{{{
    c1.cd()
    # efficiency = # in SR / # in preselection
    raw_M600_M700 = [0.27, 0.32, 0.35, 0.37, 0.37, 0.21, 0.06, 0.04, 0.02, 0.02]
    raw_M800_M1000 = [0.03, 0.04, 0.07, 0.11, 0.16, 0.38, 0.51, 0.54, 0.46, 0.24]
    raw_M1100_1200 = [0.01, 0.01, 0.01, 0.02, 0.02, 0.09, 0.29, 0.50, 0.62, 0.68]

    # efficiency = yields in SR / lumi * xsec * BF
    raw_M600_M700  = [0.08, 0.09, 0.11, 0.11, 0.11, 0.07, 0.02, 0.01, 0.01, 0.01]
    raw_M800_M1000 = [0.01, 0.01, 0.02, 0.03, 0.05, 0.12, 0.18, 0.20, 0.17, 0.09]
    raw_M1100_1200 = [0.00, 0.00, 0.00, 0.01, 0.01, 0.03, 0.10, 0.19, 0.23, 0.27]

    raw_M600_M700  = [0.07882, 0.09317, 0.10533, 0.11234, 0.10923, 0.08903, 0.06883, 0.04574, 0.02264, 0.01763, 0.01262, 0.01020, 0.00778, 0.00658, 0.00539]
    raw_M800_M1000 = [0.00810, 0.01266, 0.02134, 0.03390, 0.04737, 0.08605, 0.12473, 0.15204, 0.17935, 0.18855, 0.19774, 0.18349, 0.16925, 0.13075, 0.09225]
    raw_M1100_1200 = [0.00242, 0.00311, 0.00408, 0.00535, 0.00699, 0.01878, 0.03057, 0.06607, 0.10157, 0.14412, 0.18667, 0.20925, 0.23183, 0.24890, 0.26597]

    raw_M600_M700  = [0.07882, 0.09317, 0.10533, 0.11234, 0.10923, 0.06883, 0.02264, 0.01262, 0.00778, 0.00539]
    raw_M800_M1000 = [0.00810, 0.01266, 0.02134, 0.03390, 0.04737, 0.12473, 0.17935, 0.19774, 0.16925, 0.09225]
    raw_M1100_1200 = [0.00242, 0.00311, 0.00408, 0.00535, 0.00699, 0.03057, 0.10157, 0.18667, 0.23183, 0.26597]

    # Maxime opt2 + UL samples
    raw_M600_M700  = [ 0.07114, 0.08517, 0.09706, 0.10479, 0.10776, 0.06358, 0.01886, 0.01027, 0.00700, 0.00462 ]
    raw_M800_M1000 = [ 0.01006, 0.01513, 0.02305, 0.03451, 0.04970, 0.12768, 0.18943, 0.21193, 0.18650, 0.09700 ]
    raw_M1100_1200 = [ 0.00320, 0.00438, 0.00594, 0.00822, 0.01101, 0.03480, 0.10923, 0.20500, 0.26490, 0.29458 ]

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

    set_graph(gr1, "Efficiency", ROOT.kRed)
    set_graph(gr2, "Efficiency", ROOT.kGreen+3)
    set_graph(gr3, "Efficiency", ROOT.kBlue)

    gr1.SetMaximum(0.5)

    gr1.Draw('ACP')
    gr2.Draw('CP')
    gr3.Draw('CP')

    # local leg
    legend = ROOT.TLegend(0.17, 0.60, 0.42, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.Clear()
    legend.AddEntry(gr1, "[600, 700]", "lp")
    legend.AddEntry(gr2, "[800, 1000]", "lp")
    legend.AddEntry(gr3, "[1100, 1200]", "lp")
    legend.Draw("same")

    # wrap up
    annotate()
    output = dir_output + "/signal_efficiency"
    c1.SaveAs(output + ".png")
    c1.SaveAs(output + ".pdf")
#}}}

if __name__ == "__main__":
    #run()
    make_efficiency()
    subprocess.call("ls -lhrt %s" % dir_output, shell=True)

