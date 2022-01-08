#!/usr/bin/env python
import os, glob, ROOT, subprocess
ROOT.gROOT.SetBatch(True)
c1 = ROOT.TCanvas("c1", "", 800, 600)

def print_entries(root, name):
    f = ROOT.TFile.Open(root, "R")
    t = f.Get(name)
    entries = t.GetEntries()
    yields = t.Integral(0, t.GetSize()-1);
    print root, entries, yields

def print_yields(root, name):
    f = ROOT.TFile.Open(root, "R")
    t = f.Get(name) # need to be histogram
    yields = t.Integral(0, t.GetSize()-1);
    print root, yields

def print_content(root, name):
    f = ROOT.TFile.Open(root, "R")
    t = f.Get(name)

    try:
        import pandas
    except:
        print("Failed to import pandas.")
        exit()

    data, columns = t.AsMatrix(return_labels=True)
    df = pandas.DataFrame(data=data, columns=columns)
    print ">>> conntent:\n", df

def check_ntuples():
    rootfile = "/eos/user/p/prsaha/for_YuWei/all_Data_16_CR_Mgg120_130GeV.root"
    tree = "tagsDumper/trees/Data_13TeV_THQHadronicTag"
    print_content(rootfile, tree)

#----------------------------------------------------------------------------------------------------

def check_rootfiles_Maxime():
    directory = "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime"

    os.chdir(directory)
    rootfiles = glob.glob("*.root")
    
    for root in rootfiles:
        print_entries(root, "t")

def check_produced_ntuples():
    path = "/eos/user/y/ykao/tPrimeExcessHgg/merged_ntuples"
    tree = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"

    directory = path + "/ntuples_qcdGjet_v3p8_201?/*/"
    for root in glob.glob(directory + "*root"):
        print_entries(root, tree)

def check_merged_ntuples(directory, tag):
    path = "/eos/home-y/ykao/tPrimeExcessHgg/rootfiles/" + directory
    tree = "tagsDumper/trees/NRB_13TeV_THQHadronicTag"

    for root in glob.glob("%s/%s_Era201?.root" % (path, tag)):
        print_entries(root, tree)

    #print_entries("%s/%s_Era2016.root" % (path, tag), tree)
    #print_entries("%s/%s_Era2017.root" % (path, tag), tree)
    #print_entries("%s/%s_Era2018.root" % (path, tag), tree)

def check_myhist(tag, sample, directory = "plots"):
    hist = "hMass_sideband_%s" % sample
    hist = "hfake_photon_IDMVA_%s" % sample
    hist = "hMass_pass_BDT_smh_cut_mixed03_%s" % sample
    hist = "hMass_pass_BDTG_smh_cut_mixed03_%s" % sample
    hist = "hMass_%s" % sample

    #subprocess.call('grep "Expected Yields" %s/log/*Tprime*600*' % directory, shell=True)

    print_entries("%s/myhist_%s_Era2016.root" % (directory, tag), hist)
    print_entries("%s/myhist_%s_Era2017.root" % (directory, tag), hist)
    print_entries("%s/myhist_%s_Era2018.root" % (directory, tag), hist)

    #print_entries("plots_20210804_v2/myhist_%s_Era2016.root" % tag, hist)
    #print_entries("plots_20210804_v2/myhist_%s_Era2017.root" % tag, hist)
    #print_entries("plots_20210804_v2/myhist_%s_Era2018.root" % tag, hist)

    #print_entries("shortcut_plots/plots_20210725/myhist_%s_Era2016.root" % tag, hist)
    #print_entries("shortcut_plots/plots_20210725/myhist_%s_Era2017.root" % tag, hist)
    #print_entries("shortcut_plots/plots_20210725/myhist_%s_Era2018.root" % tag, hist)
    #print_entries("shortcut_plots/plots_20210725/myhist_combine_RunII.root", hist)

def update_to_my_webpage(myfigure):
    directory = "/eos/user/y/ykao/www/tprimetH_THQHadronic/test/"
    subprocess.call("mv %s %s" % (myfigure, directory), shell = True)

labels = { #{{{
    0  : "ttHJet"       ,
    11 : "THQ"          ,
    14 : "GluGluHToGG"  ,
    15 : "VBF"          ,
    16 : "VHToGG"       ,
    2  : "DiPhotonJets" ,
    5  : "TTGG"         ,
    6  : "TTGJets"      ,
    9  : "TTJets"       ,
    13 : "TGJets"       ,
    7  : "VG"           ,
    18 : "imputed"      ,
    4  : "QCD"          ,
    3  : "GJets"        ,
    27 : "Tprime-M600"  ,
    28 : "Tprime-M625"  ,
    29 : "Tprime-M650"  ,
    30 : "Tprime-M675"  ,
    31 : "Tprime-M700"  ,
    32 : "Tprime-M800"  ,
    33 : "Tprime-M900"  ,
    34 : "Tprime-M1000" ,
    35 : "Tprime-M1100" ,
    36 : "Tprime-M1200" ,
} #}}}
def check_mvababy_var(var):
    filename = "plots/MVABaby_combine_RunII.root"
    filename = "./shortcut_plots/plots_newBase_20210818/MVABaby_combine_RunII.root"
    filename = "./plots_20210831_oldWjetCondition/MVABaby_combine_RunII.root"
    filename = "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/plots/plots_newBase_20210818/MVABaby_combine_RunII.root"
    filename = "plots/MVABaby_combine_RunII.root"
    filename = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/shortcut_plots/plots_dataDrivenQCD_scaleHT_central/MVABaby_combine_RunII.root"
    f1 = ROOT.TFile.Open(filename, "R")
    t = f1.Get("t")

    h = ROOT.TH1D("h_%s" % var, "", 37, 0, 37)
    t.Draw("%s >> h_%s" % (var, var), "")
    #h = ROOT.gPad.GetPrimitive("h_%s" % var)
    h.SetStats(0)

    ids = [0, 11, 14, 15, 16, 2, 5, 6, 9, 7, 18, 4, 3, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36]
    ids = [0, 11, 14, 15, 16, 2, 5, 6, 9, 13, 7, 18, 4, 3, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36]
    print ">>> input file:", filename
    for id in sorted(ids):
        print ">>> id:%2d, Entry of %-15s = %d" % (id, labels[id], h.GetBinContent(id+1))

    output = "mvaBaby_%s.png" % (var)
    c1.SaveAs(output)
    update_to_my_webpage(output)
#}}}
def check_mvababy(): #{{{
    dirs = ["plots", "plots_20210821_lowPhotonID_correlation_study"]
    for d in dirs:
        for filename in glob.glob(d + "/MVA*GJet*"):
            #print d, filename
            #print_entries(filename, "t")
            print_entries(filename, "t_lowPhotonSideband")
#}}}

if __name__ == "__main__":
    check_mvababy_var("process_id_")
    #check_mvababy()

    #check_ntuples()
    #check_produced_ntuples()

    path = "/afs/cern.ch/work/y/ykao/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH"
    input_file = "%s/plots" % path

    #input_file = "%s/shortcut_plots/plots_20210703_base" % path # base 
    #check_myhist("TprimeBToTH_M-600", "TprimeBToTH_M-600", input_file)
    #input_file = "%s/shortcut_plots/plots_20210725" % path # base 
    #check_myhist("TprimeBToTH_M-600", "TprimeBToTH_M-600", input_file)
    #input_file = "%s/plots_base_20210806" % path # base 
    #check_myhist("TprimeBToTH_M-600", "TprimeBToTH_M-600", input_file)
    #check_myhist("TprimeBToTH_M-600", "TprimeBToTH_M-600")

    #check_myhist("Data", "Data", "plots_20210907_Maxime_config01")
    #check_myhist("Data", "Data", "plots_20210907_Maxime_config02")
    #check_myhist("Data", "Data")

    #check_myhist("Data", "QCD_GammaJets_imputed")
    #check_myhist("DiPhotonJets", "DiPhoton")
    #check_myhist("QCD", "QCD")
    #check_myhist("GJet_Pt", "GammaJets")

    #check_merged_ntuples("ntuples_v3.6", "QCD")
    #check_merged_ntuples("ntuples_v3.6", "GJet_Pt")
    #check_merged_ntuples("ntuples_v3.8", "QCD")
    #check_merged_ntuples("ntuples_v3.8", "GJet_Pt")
    #check_merged_ntuples("ntuples_v3.8.1", "QCD")
    #check_merged_ntuples("ntuples_v3.8.1", "GJet_Pt")
