#!/usr/bin/env python2
import os
import subprocess
import toolbox
import ROOT
ROOT.gROOT.SetBatch(True)

import sort

#----------------------------------------------------------------------------------------------------#
# global variables
#----------------------------------------------------------------------------------------------------#
path = "../plots_lowPhotonIDstudy_fakePhotonStudy_20210815/"
path = "./rootfiles_ReReco/"
path = "./rootfiles/"
directory = "/eos/user/y/ykao/www/tprimetH_THQHadronic/test/"
directory = "/eos/user/y/ykao/www/tprimetH_THQHadronic/fake_photon_correlation/"
directory = "/eos/user/y/ykao/www/tprimetH_THQHadronic/fake_photon_correlation_ul/"
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

#----------------------------------------------------------------------------------------------------#
# Main functions
#----------------------------------------------------------------------------------------------------#
variables = [ "maxIDMVA_", "minIDMVA_", "max1_btag_", "max2_btag_", "dipho_delta_R", "njets_", "nbjets_", "ht_", "leadptoM_", "subleadptoM_", "lead_eta_", "sublead_eta_", "jet1_ptOverM_", "jet1_eta_", "jet1_btag_", "jet2_ptOverM_", "jet2_eta_", "jet2_btag_", "jet3_ptOverM_", "jet3_eta_", "jet3_btag_", "jet4_ptOverM_", "jet4_eta_", "jet4_btag_", "leadPSV_", "subleadPSV_", "dipho_cosphi_", "dipho_rapidity_", "met_", "dipho_pt_over_mass_", "helicity_angle_", "chi2_value_", "chi2_bjet_ptOverM_", "chi2_bjet_eta_", "chi2_bjet_btagScores_", "chi2_wjet1_ptOverM_", "chi2_wjet1_eta_", "chi2_wjet1_btagScores_", "chi2_wjet2_ptOverM_", "chi2_wjet2_eta_", "chi2_wjet2_btagScores_", "chi2_wjets_deltaR_", "chi2_wboson_ptOverM_", "chi2_wboson_eta_", "chi2_wboson_mass_", "chi2_wboson_deltaR_bjet_", "chi2_tbw_mass_", "chi2_tbw_ptOverM_", "chi2_tbw_eta_", "chi2_tprime_ptOverM_", "chi2_tprime_eta_", "tprime_pt_ratio_", "helicity_tprime_" ]
#variables = [ "maxIDMVA_", "minIDMVA_", "max1_btag_", "max2_btag_"]

bins = { #{{{
    "maxIDMVA_"                : [ 20 , -1   , 1     ] ,
    "minIDMVA_"                : [ 20 , -1   , 1     ] ,
    "dipho_delta_R"            : [ 20 , 0    , 6     ] ,
    "njets_"                   : [ 16 , -0.5 , 15.5  ] ,
    "nbjets_"                  : [ 8  , -0.5 , 7.5   ] ,
    "ht_"                      : [ 20 , 0    , 3000  ] ,
    "leadPSV_"                 : [ 2  , -0.5 , 1.5   ] ,
    "subleadPSV_"              : [ 2  , -0.5 , 1.5   ] ,
    "dipho_cosphi_"            : [ 20 , 0    , 1     ] ,
    "dipho_rapidity_"          : [ 20 , -3   , 3     ] ,
    "met_"                     : [ 20 , 0    , 200   ] ,
    "helicity_angle_"          : [ 20 , 0    , 1     ] ,
    "chi2_value_"              : [ 20 , 0    , 100   ] ,
    "chi2_wjets_deltaR_"       : [ 20 , 0    , 4     ] ,
    "chi2_wboson_deltaR_bjet_" : [ 20 , 0    , 6     ] ,
    "tprime_pt_ratio_"         : [ 20 , 0    , 4.    ] ,
    "helicity_tprime_"         : [ 20 , 0    , 1.    ] ,
    "chi2_wboson_mass_"        : [ 20 , 0    , 200   ] ,
    "chi2_tbw_mass_"           : [ 20 , 0    , 360   ] ,
    "leadptoM_"                : [ 20 , 0    , 1.5   ] ,
    "subleadptoM_"             : [ 20 , 0    , 1.5   ] ,
    "dipho_pt_over_mass_"      : [ 20 , 0    , 6     ] ,
    "jet1_ptOverM_"            : [ 20 , 0    , 3     ] ,
    "jet2_ptOverM_"            : [ 20 , 0    , 3     ] ,
    "jet3_ptOverM_"            : [ 20 , 0    , 3     ] ,
    "jet4_ptOverM_"            : [ 20 , 0    , 3     ] ,
    "chi2_bjet_ptOverM_"       : [ 20 , 0    , 3     ] ,
    "chi2_wjet1_ptOverM_"      : [ 20 , 0    , 3     ] ,
    "chi2_wjet2_ptOverM_"      : [ 20 , 0    , 3     ] ,
    "chi2_wboson_ptOverM_"     : [ 20 , 0    , 4     ] ,
    "chi2_tbw_ptOverM_"        : [ 20 , 0    , 3     ] ,
    "chi2_tprime_ptOverM_"     : [ 20 , 0    , 2     ] ,
    "lead_eta_"                : [ 20 , -4   , 4     ] ,
    "sublead_eta_"             : [ 20 , -4   , 4     ] ,
    "jet1_eta_"                : [ 20 , -4   , 4     ] ,
    "jet2_eta_"                : [ 20 , -4   , 4     ] ,
    "jet3_eta_"                : [ 20 , -4   , 4     ] ,
    "jet4_eta_"                : [ 20 , -4   , 4     ] ,
    "chi2_bjet_eta_"           : [ 20 , -4   , 4     ] ,
    "chi2_wjet1_eta_"          : [ 20 , -4   , 4     ] ,
    "chi2_wjet2_eta_"          : [ 20 , -4   , 4     ] ,
    "chi2_wboson_eta_"         : [ 20 , -4   , 4     ] ,
    "chi2_tbw_eta_"            : [ 20 , -4   , 4     ] ,
    "chi2_tprime_eta_"         : [ 20 , -4   , 4     ] ,
    "max1_btag_"               : [ 20 , 0    , 1.    ] ,
    "max2_btag_"               : [ 20 , 0    , 1.    ] ,
    "jet1_btag_"               : [ 20 , 0    , 1.    ] ,
    "jet2_btag_"               : [ 20 , 0    , 1.    ] ,
    "jet3_btag_"               : [ 20 , 0    , 1.    ] ,
    "jet4_btag_"               : [ 20 , 0    , 1.    ] ,
    "chi2_bjet_btagScores_"    : [ 20 , 0    , 1.    ] ,
    "chi2_wjet1_btagScores_"   : [ 20 , 0    , 1.    ] ,
    "chi2_wjet2_btagScores_"   : [ 20 , 0    , 1.    ] ,
} #}}}
#
#bins = { #{{{
#    "maxIDMVA_"                : [ 20 , -1   , 1     ] ,
#    "minIDMVA_"                : [ 20 , -1   , 1     ] ,
#    "dipho_delta_R"            : [ 25 , 0    , 6     ] ,
#    "njets_"                   : [ 16 , -0.5 , 15.5  ] ,
#    "nbjets_"                  : [ 16 , -0.5 , 15.5  ] ,
#    "ht_"                      : [ 50 , 0    , 5000  ] ,
#    "leadPSV_"                 : [ 2  , -0.5 , 1.5   ] ,
#    "subleadPSV_"              : [ 2  , -0.5 , 1.5   ] ,
#    "dipho_cosphi_"            : [ 25 , -1   , 1     ] ,
#    "dipho_rapidity_"          : [ 25 , -3   , 3     ] ,
#    "met_"                     : [ 25 , 0    , 200   ] ,
#    "helicity_angle_"          : [ 10 , 0    , 1     ] ,
#    "chi2_value_"              : [ 50 , 0    , 100   ] ,
#    "chi2_wjets_deltaR_"       : [ 25 , 0    , 6     ] ,
#    "chi2_wboson_deltaR_bjet_" : [ 25 , 0    , 6     ] ,
#    "tprime_pt_ratio_"         : [ 20 , 0    , 10.   ] ,
#    "helicity_tprime_"         : [ 10 , 0    , 1.    ] ,
#    "chi2_wboson_mass_"        : [ 40 , 0    , 200   ] ,
#    "chi2_tbw_mass_"           : [ 36 , 0    , 360   ] ,
#    "leadptoM_"                : [ 20 , 0    , 10    ] ,
#    "subleadptoM_"             : [ 20 , 0    , 10    ] ,
#    "dipho_pt_over_mass_"      : [ 20 , 0    , 10    ] ,
#    "jet1_ptOverM_"            : [ 20 , 0    , 5     ] ,
#    "jet2_ptOverM_"            : [ 20 , 0    , 5     ] ,
#    "jet3_ptOverM_"            : [ 20 , 0    , 5     ] ,
#    "jet4_ptOverM_"            : [ 20 , 0    , 5     ] ,
#    "chi2_bjet_ptOverM_"       : [ 20 , 0    , 5     ] ,
#    "chi2_wjet1_ptOverM_"      : [ 20 , 0    , 5     ] ,
#    "chi2_wjet2_ptOverM_"      : [ 20 , 0    , 5     ] ,
#    "chi2_wboson_ptOverM_"     : [ 20 , 0    , 5     ] ,
#    "chi2_tbw_ptOverM_"        : [ 20 , 0    , 5     ] ,
#    "chi2_tprime_ptOverM_"     : [ 20 , 0    , 5     ] ,
#    "lead_eta_"                : [ 25 , -5   , 5     ] ,
#    "sublead_eta_"             : [ 25 , -5   , 5     ] ,
#    "jet1_eta_"                : [ 25 , -5   , 5     ] ,
#    "jet2_eta_"                : [ 25 , -5   , 5     ] ,
#    "jet3_eta_"                : [ 25 , -5   , 5     ] ,
#    "jet4_eta_"                : [ 25 , -5   , 5     ] ,
#    "chi2_bjet_eta_"           : [ 25 , -5   , 5     ] ,
#    "chi2_wjet1_eta_"          : [ 25 , -5   , 5     ] ,
#    "chi2_wjet2_eta_"          : [ 25 , -5   , 5     ] ,
#    "chi2_wboson_eta_"         : [ 25 , -5   , 5     ] ,
#    "chi2_tbw_eta_"            : [ 25 , -5   , 5     ] ,
#    "chi2_tprime_eta_"         : [ 25 , -5   , 5     ] ,
#    "max1_btag_"               : [ 50 , 0    , 1.    ] ,
#    "max2_btag_"               : [ 50 , 0    , 1.    ] ,
#    "jet1_btag_"               : [ 50 , 0    , 1.    ] ,
#    "jet2_btag_"               : [ 50 , 0    , 1.    ] ,
#    "jet3_btag_"               : [ 50 , 0    , 1.    ] ,
#    "jet4_btag_"               : [ 50 , 0    , 1.    ] ,
#    "chi2_bjet_btagScores_"    : [ 50 , 0    , 1.    ] ,
#    "chi2_wjet1_btagScores_"   : [ 50 , 0    , 1.    ] ,
#    "chi2_wjet2_btagScores_"   : [ 50 , 0    , 1.    ] ,
#} #}}}
#
def annotation(info):
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.12, 0.912, "#bf{CMS} #it{work in progress}")
    latex.DrawLatex( 0.15, 0.85, "r = %s" % info)
    #latex.DrawLatex( 0.70, 0.912, "%s (13TeV)" % str(year) )
    #latex.DrawLatex( 0.15, 0.75, "Correlation factor:" )
    #latex.DrawLatex( 0.15, 0.65, info )

def check_correlation(sample="GJet"):
    filename = path + "MVABaby_low_photon_sideband_MC.root"
    filename = path + "MVABaby_low_photon_sideband_%s.root" % sample
    f1 = ROOT.TFile.Open(filename, "R")
    t = f1.Get("t_lowPhotonSideband")

    fout = open('log.txt', 'w')
    fout.write("# %s Entries = %d\n" % (sample, t.GetEntries()) )
    fout.write("# Correlation_factors_of_fake_photon_IDVMVA\n")
    for var in variables:
        # Next: use fill method to take evt weight into account
        c1.SetLogz()
        #t.Draw("%s:minIDMVA_ >> h_%s(20, -1., 1., %d, %f, %f)" % (var, var, bins[var][0], bins[var][1],bins[var][2]), "weight", "colz")
        #t.Draw("%s:maxIDMVA_ >> h_%s(20, -1., 1., %d, %f, %f)" % (var, var, bins[var][0], bins[var][1],bins[var][2]), "weight", "colz")
        t.Draw("%s:idmva >> h_%s(20, -1., 1., %d, %f, %f)" % (var, var, bins[var][0], bins[var][1],bins[var][2]), "weight", "colz")
        h = ROOT.gPad.GetPrimitive("h_%s" % var)
        h.SetTitle("")
        h.GetXaxis().SetTitle("Fake #gamma ID MVA")
        h.GetYaxis().SetTitle(var)
        h.SetStats(0)
        correlation = h.GetCorrelationFactor()

        var = var[:-1] if var[-1] == "_" else var
        annotation("%f" % correlation)
        fout.write("%-25s, %f\n" % (var, correlation) )
        #fout.write( ">>> correlation (idmva vs %s): %f\n" % (var, correlation) )
        
        output = "correlation_%s_%s.png" % (sample, var)
        output = "correlation_%s_%s.pdf" % (sample, var)
        c1.SaveAs(output)
        update_to_my_webpage(output)

    fout.close()

#----------------------------------------------------------------------------------------------------#
# Execution
#----------------------------------------------------------------------------------------------------#
if __name__ == "__main__":
    #clear_directory(directory)
    create_directory(directory)
    check_correlation()
    sort.sort()
    #check_correlation("QCD")

    #check_correlation("GJet_Pt")
    #check_correlation("Data") # not reasonable. How to ensure identity of fake photons?
