#!/usr/bin/env python2
import os
import subprocess
import toolbox
import ROOT
ROOT.gROOT.SetBatch(True)

#----------------------------------------------------------------------------------------------------#
# global variables
#----------------------------------------------------------------------------------------------------#
directory = "/eos/user/y/ykao/www/tprimetH_THQHadronic/test_01/"
directory = "/eos/user/y/ykao/www/tprimetH_THQHadronic/test/"

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
def make_manual_fit_info():
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
    latex.DrawLatex(x, y - decrement * 1, "p0 =  443.784 +/- 8.09362")
    latex.DrawLatex(x, y - decrement * 2, "p1 =   -535.2 +/- 40.6104")
    latex.DrawLatex(x, y - decrement * 3, "p2 =  1022.96 +/- 139.2")
    latex.DrawLatex(x, y - decrement * 4, "p3 = -1072.95 +/- 333.686")
    latex.DrawLatex(x, y - decrement * 5, "p4 = -1775.02 +/- 515.644")
    latex.DrawLatex(x, y - decrement * 6, "p5 =  3157.69 +/- 841.705")
    latex.DrawLatex(x, y - decrement * 7, "p6 =  3550.26 +/- 492.368")
    latex.DrawLatex(x, y - decrement * 8, "p7 = -4563.58 +/- 655.114")

def make_fake_photon_IDMVA(var, output, do_fit = False):
    filename = "rootfiles/fakePhoton_GJet.root"
    filename = "rootfiles/fakePhoton_pdf.root"
    filename = "rootfiles/fakePhoton_pdf_GJet.root"
    filename = "rootfiles/fakePhoton_pdf_v3p8.root"
    f1 = ROOT.TFile.Open(filename, "R")
    tree = f1.Get("t_fakePhotonIDMVA")

    hist = ROOT.TH1D("hist", ";Photon ID MVA; Entries", 40, -1, 1)
    hist.SetStats(0)
    tree.Draw("%s >> hist" % var)

    hist.GetXaxis().SetRangeUser(-0.9,1.0)
    if do_fit:
        hist.Fit("pol7")
    hist.Draw("e1")
    make_manual_fit_info()

    c1.SaveAs(output)
    update_to_my_webpage(output)

def check_fake_pdf(output):
    f_IDMVA_fcnc = ROOT.TF1("f_IDMVA", "[0] + [1]*x + [2]*x^2 + [3]*x^3 + [4]*x^4 + [5]*x^5 + [6]*x^6 + [7]*x^7", -1.0, 1.0)
    f_IDMVA_fcnc.SetParameter(0, 8818.17)
    f_IDMVA_fcnc.SetParameter(1, -12755.5)
    f_IDMVA_fcnc.SetParameter(2, 26130)
    f_IDMVA_fcnc.SetParameter(3, -26664.9)
    f_IDMVA_fcnc.SetParameter(4, -54741.1)
    f_IDMVA_fcnc.SetParameter(5, 76558)
    f_IDMVA_fcnc.SetParameter(6, 112245)
    f_IDMVA_fcnc.SetParameter(7, -123913)
    f_IDMVA_fcnc.SetLineColor(ROOT.kBlue)
    f_IDMVA_fcnc.SetNormalized(True)
    f_IDMVA_fcnc.Draw()

    f_IDMVA = ROOT.TF1("f_IDMVA", "[0] + [1]*x + [2]*x^2 + [3]*x^3 + [4]*x^4 + [5]*x^5 + [6]*x^6 + [7]*x^7", -1.0, 1.0)
    f_IDMVA.SetParameter(0, 435.477);
    f_IDMVA.SetParameter(1, -487.523);
    f_IDMVA.SetParameter(2, 1064.27);
    f_IDMVA.SetParameter(3, -1215.24);
    f_IDMVA.SetParameter(4, -1752.79);
    f_IDMVA.SetParameter(5, 3047.33);
    f_IDMVA.SetParameter(6, 3370.99);
    f_IDMVA.SetParameter(7, -4173.07);
    f_IDMVA.SetLineColor(ROOT.kRed)
    f_IDMVA.SetNormalized(True)
    f_IDMVA.Draw("same")

    c1.SaveAs(output)
    update_to_my_webpage(output)

colors = {
    "QCD"       : ROOT.kOrange + 6,
    "GammaJets" : ROOT.kRed + 3,
    "DiPhoton"  : ROOT.kRed + 1,
    "TTGG"      : ROOT.kGreen-2,
    "TTGJets"   : ROOT.kGreen-7,
    "TTJets"    : ROOT.kSpring+10,
    "VG"        : ROOT.kViolet-9,
}

def check_low_photon_ID_region(name, r):
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

#----------------------------------------------------------------------------------------------------#
# Execution
#----------------------------------------------------------------------------------------------------#
if __name__ == "__main__":
    #clear_directory(directory)
    create_directory(directory)

    #check_low_photon_ID_region("hMass", [100,180])
    #check_low_photon_ID_region("hPhotonMinIDMVA_fine", [-0.9,1.0])
    #check_low_photon_ID_region("hPhotonMaxIDMVA_fine", [-0.9,1.0])
    #check_low_photon_ID_region("hfake_photon_IDMVA", [-0.9,1.0])

    #check_fake_pdf("check_fake_pdf.png")

    make_fake_photon_IDMVA("idmva", "check_fake_photon_IDMVA.png", True)
    make_fake_photon_IDMVA("idmva", "check_fake_photon_IDMVA.pdf", True)
    #make_fake_photon_IDMVA("idmva", "check_fake_photon_IDMVA_GammaJets.png", True)
    #make_fake_photon_IDMVA("maxIDMVA_", "check_max_photon_IDMVA_GammaJets.png")
    #make_fake_photon_IDMVA("minIDMVA_", "check_min_photon_IDMVA_GammaJets.png")
