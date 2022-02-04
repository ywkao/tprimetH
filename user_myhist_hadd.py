#!/usr/bin/env python
import glob
import subprocess

def customize_hadd():
    combine = ""
    rootfiles = glob.glob("plots*base/myhist*root")
    rootfiles = glob.glob("plots_20210707/myhist*root")
    rootfiles = glob.glob("collection/plots_20210703_base/myhist*root")
    rootfiles = glob.glob("plots_20210804_v2/myhist*root")
    rootfiles = glob.glob("plots/myhist*root")
    rootfiles = glob.glob("plots_20210907_Maxime_config01/myhist*root")
    rootfiles = glob.glob("plots_20210907_Maxime_config02/myhist*root")
    for root in rootfiles:
        if 'combine' in root:
            continue
        combine = combine + root + " "
    
    #combine += "shortcut_plots/plots_20210828_oldWjetsCondition_newBDT/myhist_VBF*.root "
    #combine += "shortcut_plots/plots_20210828_oldWjetsCondition_newBDT/myhist_THQ*.root "
    #combine += "shortcut_plots/plots_20210828_oldWjetsCondition_newBDT/myhist_DiPhoton*.root "

    combine += "shortcut_plots/plots_20210905_newBase_newBDT_previousCutValues/myhist_VBF*.root "
    combine += "shortcut_plots/plots_20210905_newBase_newBDT_previousCutValues/myhist_THQ*.root "
    combine += "shortcut_plots/plots_20210905_newBase_newBDT_previousCutValues/myhist_DiPhoton*.root "
    
    subprocess.call("hadd -f plots_20210907_Maxime_config02/myhist_combine_RunII.root %s" % combine, shell = True)
    #subprocess.call("hadd -f plots/myhist_combine_RunII.root %s" % combine, shell = True)

def usuall_hadd(prefix, directory="plots"):
    combine = ""
    rootfiles = glob.glob("%s/%s*root" % (directory, prefix))
    for root in rootfiles:
        if 'combine' in root:
            continue
        combine = combine + root + " "
    
    command = "hadd -f %s/%s_combine_RunII.root %s" % (directory, prefix, combine)
    subprocess.call(command, shell = True)

def combine_only_signal(prefix, directory="plots"):
    combine = ""
    rootfiles = glob.glob("%s/%s*TprimeBToTH*root" % (directory, prefix))
    for root in rootfiles:
        if 'combine' in root:
            continue
        combine = combine + root + " "
    
    command = "hadd -f %s/%s_combine_RunII.root %s" % (directory, prefix, combine)
    subprocess.call(command, shell = True)

def low_photon_ID_sideband_study():
    directory = "fakePhotonStudy/rootfiles"
    tag = "low_photon_sideband"
    #subprocess.call("hadd -f %s/myhist_%s.root plots/myhist*.root" % (directory, tag), shell = True)
    #subprocess.call("hadd -f %s/MVABaby_%s_MC.root plots/MVABaby*GJet*.root plots/MVABaby*QCD*.root" % (directory, tag), shell = True)

    #subprocess.call("hadd -f %s/MVABaby_%s_Data.root plots/MVABaby*Data*.root" % (directory, tag), shell = True)
    #subprocess.call("hadd -f %s/MVABaby_%s_GJet.root plots/MVABaby*GJet*.root" % (directory, tag), shell = True)
    #subprocess.call("hadd -f %s/MVABaby_%s_QCD.root plots/MVABaby*QCD*.root" % (directory, tag), shell = True)
    
    subprocess.call("hadd -f %s/fakePhoton_pdf_v3p8.root plots/MVABaby*GJet*.root plots/MVABaby*QCD*.root" % (directory), shell = True)

    #subprocess.call("hadd -f fakePhotonStudy/myhist_combine_2016.root plots/myhist*2016.root", shell = True)
    #myhist_QCD_Era2016.root
    #myhist_GJet_Pt_Era2016.root
    #myhist_Data_Era2016.root

def prepare_data_for_simultaneous_fit(directory="plots"):
    subprocess.call("hadd -f fakePhotonStudy/MVABaby_Data_simultaneousFit.root %s/MVA*Data*.root" % directory, shell = True)

def merge_cov_root_files(directory="plots"):
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-600_merged.root %s/*600*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-625_merged.root %s/*625*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-650_merged.root %s/*650*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-675_merged.root %s/*675*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-700_merged.root %s/*700*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-800_merged.root %s/*800*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-900_merged.root %s/*900*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-1000_merged.root %s/*1000*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-1100_merged.root %s/*1100*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-1200_merged.root %s/*1200*Era*.root" % (directory, directory), shell = True)

if __name__ == "__main__":
    #customize_hadd()
    #usuall_hadd("myhist")
    #usuall_hadd("myhist", "plots_dataDrivenQCD_scaleHT_central")
    #combine_only_signal("myhist")
    #usuall_hadd("myhist", "plots_20210907_Maxime_config01")
    #usuall_hadd("myhist", "plots_20210907_Maxime_config02")
    #usuall_hadd("myhist", "plots_20210908_Maxime_verification")

    merge_cov_root_files()

    #low_photon_ID_sideband_study()
    #prepare_data_for_simultaneous_fit()
    #prepare_data_for_simultaneous_fit("plots_newBase_20210818")

    #usuall_hadd("MVABaby")
    #usuall_hadd("MVABaby", "plots_newBase_20210818")
