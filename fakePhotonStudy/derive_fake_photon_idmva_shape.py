#!/usr/bin/env python2
import os
import subprocess
import toolbox
import ROOT
ROOT.gROOT.SetBatch(True)

#----------------------------------------------------------------------------------------------------#
# global variables
#----------------------------------------------------------------------------------------------------#
directory = "eos_fakePhotonStudy/"
c1 = ROOT.TCanvas("c1", "", 800, 600)

#----------------------------------------------------------------------------------------------------#
# Auxiliary functions
#----------------------------------------------------------------------------------------------------#
def clear_directory(d):
    if os.path.exists(d):
        subprocess.call("rm -r %s" % d, shell=True)

def create_directory(dir_output):
    php_index = "/eos/user/y/ykao/www/index.php"
    subprocess.call( "mkdir -p %s" % dir_output, shell=True)
    subprocess.call( "cp -p %s %s" % (php_index, dir_output), shell=True)

def update_to_my_webpage(myfigure):
    subprocess.call("mv %s %s" % (myfigure, directory), shell = True)

#----------------------------------------------------------------------------------------------------
# retrieve fake photon IDMVA
#----------------------------------------------------------------------------------------------------#
def make_manual_fit_info(d): #{{{
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(26)

    f = ""
    for i in range(8):
        term = "p%dx^{%d}" % (i, i)
        if len(f) == 0:
            f = term
        else:
            f += " + " + term

    x = 0.40
    y = 0.80
    decrement = 0.06
    latex.DrawLatex(x, y + decrement / 3, "Seventh order polynomial")
    latex.DrawLatex(x, y - decrement * 1, "p0 = %8.2f #pm %7.3f" % (d[0]["m"], d[0]["e"]))
    latex.DrawLatex(x, y - decrement * 2, "p1 = %8.2f #pm %7.3f" % (d[1]["m"], d[1]["e"]))
    latex.DrawLatex(x, y - decrement * 3, "p2 = %8.2f #pm %7.3f" % (d[2]["m"], d[2]["e"]))
    latex.DrawLatex(x, y - decrement * 4, "p3 = %8.2f #pm %7.3f" % (d[3]["m"], d[3]["e"]))
    latex.DrawLatex(x, y - decrement * 5, "p4 = %8.2f #pm %7.3f" % (d[4]["m"], d[4]["e"]))
    latex.DrawLatex(x, y - decrement * 6, "p5 = %8.2f #pm %7.3f" % (d[5]["m"], d[5]["e"]))
    latex.DrawLatex(x, y - decrement * 7, "p6 = %8.2f #pm %7.3f" % (d[6]["m"], d[6]["e"]))
    latex.DrawLatex(x, y - decrement * 8, "p7 = %8.2f #pm %7.3f" % (d[7]["m"], d[7]["e"]))
#}}}
def make_fake_photon_IDMVA(var, output, do_fit = False): #{{{
    path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/shortcut_plots/plots_20220110_fakePhotonStudy/"
    filename = "rootfiles/fakePhoton_GJet.root"
    filename = "rootfiles/fakePhoton_pdf.root"
    filename = "rootfiles/fakePhoton_pdf_GJet.root"
    filename = "rootfiles/fakePhoton_pdf_v3p8.root"
    filename = path + "MVABaby_GJet_Pt_combined.root"
    f1 = ROOT.TFile.Open(filename, "R")
    tree = f1.Get("t_fakePhotonIDMVA")

    hist = ROOT.TH1D("hist", ";Photon ID MVA; Entries", 40, -1, 1)
    hist.SetStats(0)
    tree.Draw("%s >> hist" % var)

    hist.GetXaxis().SetRangeUser(-0.9,1.0)
    if do_fit:
        result = hist.Fit("pol7")
    hist.Draw("e1")

    fit_function = hist.GetFunction("pol7")

    d = {}
    for i in range(8):
        m, e = fit_function.GetParameter(i), fit_function.GetParError(i)
        d[i] = {"m":m, "e":e}
        print ">>> parameter %d: %f +/- %f" % (i, m, e)

    make_manual_fit_info(d)

    c1.SaveAs(output+".png")
    c1.SaveAs(output+".pdf")
    update_to_my_webpage(output+".png")
    update_to_my_webpage(output+".pdf")
#}}}
def check_fake_pdf(output): #{{{
    f_IDMVA_fcnc = ROOT.TF1("f_IDMVA", "[0] + [1]*x + [2]*x^2 + [3]*x^3 + [4]*x^4 + [5]*x^5 + [6]*x^6 + [7]*x^7", -1.0, 1.0)
    f_IDMVA_fcnc.SetParameter(0, 8818.17)
    f_IDMVA_fcnc.SetParameter(1, -12755.5)
    f_IDMVA_fcnc.SetParameter(2, 26130)
    f_IDMVA_fcnc.SetParameter(3, -26664.9)
    f_IDMVA_fcnc.SetParameter(4, -54741.1)
    f_IDMVA_fcnc.SetParameter(5, 76558)
    f_IDMVA_fcnc.SetParameter(6, 112245)
    f_IDMVA_fcnc.SetParameter(7, -123913)
    f_IDMVA_fcnc.SetLineColor(ROOT.kBlack)
    f_IDMVA_fcnc.SetNormalized(True)
    f_IDMVA_fcnc.Draw()

    f_IDMVA_tprime = ROOT.TF1("f_IDMVA", "[0] + [1]*x + [2]*x^2 + [3]*x^3 + [4]*x^4 + [5]*x^5 + [6]*x^6 + [7]*x^7", -1.0, 1.0)
    f_IDMVA_tprime.SetParameter(0, 435.477)
    f_IDMVA_tprime.SetParameter(1, -487.523)
    f_IDMVA_tprime.SetParameter(2, 1064.27)
    f_IDMVA_tprime.SetParameter(3, -1215.24)
    f_IDMVA_tprime.SetParameter(4, -1752.79)
    f_IDMVA_tprime.SetParameter(5, 3047.33)
    f_IDMVA_tprime.SetParameter(6, 3370.99)
    f_IDMVA_tprime.SetParameter(7, -4173.07)
    f_IDMVA_tprime.SetLineColor(ROOT.kBlue)
    f_IDMVA_tprime.SetNormalized(True)
    f_IDMVA_tprime.Draw("same")

    f_IDMVA = ROOT.TF1("f_IDMVA", "[0] + [1]*x + [2]*x^2 + [3]*x^3 + [4]*x^4 + [5]*x^5 + [6]*x^6 + [7]*x^7", -1.0, 1.0)
    f_IDMVA.SetParameter(0, 178.267  )
    f_IDMVA.SetParameter(1, -196.404 )
    f_IDMVA.SetParameter(2, 332.454  )
    f_IDMVA.SetParameter(3, -524.491 )
    f_IDMVA.SetParameter(4, -760.702 )
    f_IDMVA.SetParameter(5, 1831.3   )
    f_IDMVA.SetParameter(6, 1624.34  )
    f_IDMVA.SetParameter(7, -2449.23 )
    f_IDMVA.SetLineColor(ROOT.kRed)
    f_IDMVA.SetNormalized(True)
    f_IDMVA.Draw("same")

    legend = ROOT.TLegend(0.60, 0.70, 0.85, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.AddEntry(f_IDMVA_fcnc   , "fcnc"          , "l")
    legend.AddEntry(f_IDMVA_tprime , "tprime ReReco" , "l")
    legend.AddEntry(f_IDMVA        , "tprime UL"     , "l")
    legend.Draw("same")

    c1.SaveAs(output+".png")
    c1.SaveAs(output+".pdf")
    update_to_my_webpage(output+".png")
    update_to_my_webpage(output+".pdf")
#}}}
def check_low_photon_ID_region(name, r): #{{{
    colors = {
        "QCD"       : ROOT.kOrange + 6,
        "GammaJets" : ROOT.kRed + 3,
        "DiPhoton"  : ROOT.kRed + 1,
        "TTGG"      : ROOT.kGreen-2,
        "TTGJets"   : ROOT.kGreen-7,
        "TTJets"    : ROOT.kSpring+10,
        "VG"        : ROOT.kViolet-9,
    }

    output = "hist_low_photon_Id_study_%s_2016.png" % name

    samples = ["QCD_GammaJets_imputed", "QCD", "GammaJets", "DiPhoton", "TTGG", "TTGJets", "TTJets", "VG"]
    samples = ["Data", "QCD", "GammaJets", "DiPhoton", "TTGG", "TTGJets", "TTJets", "VG"]
    samples = ["QCD_GammaJets_imputed", "QCD", "GammaJets"] # imputed, process_id_ = 18
    samples = ["Data", "QCD", "GammaJets", "DiPhoton"]
    #samples = ["Data", "VG", "TTJets", "TTGJets", "TTGG", "DiPhoton", "GammaJets", "QCD"]

    tail = "Year_0" # 2016
    tail = ""

    filename = "fakePhoton_study.root"
    filename = "myhist_combine_2016.root"
    #filename = "lowPhotonIdRegion_study.root"
    f1 = ROOT.TFile.Open(filename, "R")
    hs = ROOT.THStack("hs", ";M_{#gamma#gamma}GeV;Yields");
    hists = {} 
    for process in samples:
        histname = name + "_" + process + tail
        h = f1.Get(histname)

        print histname, h.Integral(0, h.GetSize()-1)

        if process == "QCD_GammaJets_imputed":
            process = "Data"

        if process == "Data": 
            h.SetMarkerStyle(20)
        else:
            h.SetFillColor(colors[process])
            hs.Add(h)

        hists[process] = h

    hists["Data"].Draw("ep")
    hs.Draw("hist,same")

    hists["Data"].GetXaxis().SetRangeUser(r[0], r[1])
    hs.GetHistogram().GetXaxis().SetRangeUser(r[0], r[1])

    c1.SaveAs(output)
    update_to_my_webpage(output)
#}}}
#----------------------------------------------------------------------------------------------------#
# Execution
#----------------------------------------------------------------------------------------------------#
if __name__ == "__main__":
    make_fake_photon_IDMVA("idmva", "check_fake_photon_IDMVA", True)
    check_fake_pdf("check_fake_pdf")

    #make_fake_photon_IDMVA("idmva", "check_fake_photon_IDMVA_GammaJets.png", True)
    #make_fake_photon_IDMVA("maxIDMVA_", "check_max_photon_IDMVA_GammaJets.png")
    #make_fake_photon_IDMVA("minIDMVA_", "check_min_photon_IDMVA_GammaJets.png")

    #check_low_photon_ID_region("hMass", [100,180])
    #check_low_photon_ID_region("hPhotonMinIDMVA_fine", [-0.9,1.0])
    #check_low_photon_ID_region("hPhotonMaxIDMVA_fine", [-0.9,1.0])
    #check_low_photon_ID_region("hfake_photon_IDMVA", [-0.9,1.0])


