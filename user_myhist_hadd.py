#!/usr/bin/env python
import glob
import subprocess

def customize_hadd():
    combine = ""
    #rootfiles = glob.glob("plots_20220425_v4p1_v1/myhist*root")
    #rootfiles = glob.glob("shortcut_plots/plots_20220412_ultraLegacy_blind/myhist*root")
    #rootfiles = glob.glob("plots_20220426_mgg_115_135_v4p1/myhist*root")
    rootfiles = glob.glob("shortcut_plots/plots_20220412_ultraLegacy_blind/myhist*root")
    for root in rootfiles:
        if 'combine' in root: continue
        if 'Data' in root: continue
        combine = combine + root + " "
    
    target = "plots_20220425_v4p2_v1"
    target = "plots_20220425_unblind_v4p2"
    target = "plots"
    combine += "%s/myhist_Data*.root " % target
    subprocess.call("hadd -f %s/myhist_combine_RunII.root %s" % (target, combine), shell = True)

def usuall_hadd(prefix, directory="plots"):
    combine = ""
    rootfiles = glob.glob("%s/%s*root" % (directory, prefix))
    for root in rootfiles:
        if 'combine' in root: continue
        combine = combine + root + " "
    
    command = "hadd -f %s/%s_combine_RunII.root %s" % (directory, prefix, combine)
    subprocess.call(command, shell = True)

#----------------------------------------------------------------------------------------------------

def hadd_ul1718(prefix, directory="plots"):
    combine = ""
    rootfiles = glob.glob("%s/%s*root" % (directory, prefix))
    for root in rootfiles:
        if 'combine' in root: continue
        if '2016' in root: continue
        combine = combine + root + " "
    command = "hadd -f fakePhotonStudy/rootfiles/%s_combine_UL1718_RunII.root %s" % (prefix, combine)
    subprocess.call(command, shell = True)

def hadd_reReco16(prefix, directory="plots"):
    combine = ""
    rootfiles = glob.glob("%s/%s*root" % (directory, prefix))
    if prefix == "MVABaby":
        for root in rootfiles:
            if 'combine' in root: continue
            if '2017' in root or '2018' in root: continue
            combine = combine + root + " "
            command = "cp -p %s fakePhotonStudy/rootfiles/" % (combine)
    else:
        for root in rootfiles:
            if 'combine' in root: continue
            if '2017' in root or '2018' in root: continue
            combine = combine + root + " "
        command = "hadd -f fakePhotonStudy/rootfiles/%s_combine_ReReco16_RunII.root %s" % (prefix, combine)
    subprocess.call(command, shell = True)

#----------------------------------------------------------------------------------------------------

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
    
    #subprocess.call("hadd -f %s/fakePhoton_pdf_v3p8.root plots/MVABaby*GJet*.root plots/MVABaby*QCD*.root" % (directory), shell = True)
    subprocess.call("hadd -f %s/fakePhoton_pdf_v4p1.root plots/MVABaby*GJet*.root plots/MVABaby*QCD*.root" % (directory), shell = True)

    #subprocess.call("hadd -f fakePhotonStudy/myhist_combine_2016.root plots/myhist*2016.root", shell = True)
    #myhist_QCD_Era2016.root
    #myhist_GJet_Pt_Era2016.root
    #myhist_Data_Era2016.root

def prepare_data_for_simultaneous_fit(directory="plots"):
    subprocess.call("hadd -f fakePhotonStudy/rootfiles/MVABaby_Data_simultaneousFit.root %s/MVA*Data*.root" % directory, shell = True)
    #subprocess.call("hadd -f fakePhotonStudy/rootfiles/MVABaby_Data_UL1718.root %s/MVABaby_Data_Era201[78].root" % directory, shell = True)
    #subprocess.call("cp -p %s/MVABaby_Data_Era2016.root fakePhotonStudy/rootfiles/" % directory, shell = True)

def merge_cov_root_files(directory="plots"):
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-600_merged.root %s/*600*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-625_merged.root %s/*625*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-650_merged.root %s/*650*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-675_merged.root %s/*675*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-700_merged.root %s/*700*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-800_merged.root %s/*800*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-900_merged.root %s/*900*Era*.root"   % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-1000_merged.root %s/*1000*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-1100_merged.root %s/*1100*Era*.root" % (directory, directory), shell = True)
    subprocess.call("hadd -f %s/covMatrix_TprimeBToTH_M-1200_merged.root %s/*1200*Era*.root" % (directory, directory), shell = True)

if __name__ == "__main__":

    #customize_hadd()
    #exit()

    #usuall_hadd("myhist")
    #usuall_hadd("MVABaby")

    merge_cov_root_files()

    #hadd_ul1718("MVABaby")
    #hadd_reReco16("MVABaby")
    #hadd_ul1718("myhist"  , "plots_20220309_updateLumi_forSimultaneousFit")
    #hadd_reReco16("myhist", "plots_20220309_updateLumi_forSimultaneousFit")

    #prepare_data_for_simultaneous_fit()
    #prepare_data_for_simultaneous_fit("plots_20220113_ultraLegacy")
    #usuall_hadd("myhist", "plots_20220113_ultraLegacy")
    #low_photon_ID_sideband_study()

    #prepare_data_for_simultaneous_fit()
    #prepare_data_for_simultaneous_fit("plots_newBase_20210818")

    #usuall_hadd("myhist", "plots_dataDrivenQCD_scaleHT_central")
    #combine_only_signal("myhist")
    #usuall_hadd("myhist", "plots_20210907_Maxime_config01")
    #usuall_hadd("myhist", "plots_20210907_Maxime_config02")
    #usuall_hadd("myhist", "plots_20210908_Maxime_verification")
    #usuall_hadd("MVABaby", "plots_newBase_20210818")

