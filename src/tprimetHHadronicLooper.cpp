#include <stdio.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TChain.h>
#include "ScanChain_tprimetHHadronic.C"

int main(int argc, char* argv[])
{
    TString location = argv[1];
    TString rootfile = argv[2];
    TString fullpath = location + "/" + rootfile;
    printf("[check] fullpath = %s\n", fullpath.Data());

    TChain *ch = new TChain("tagsDumper/trees/tHq_13TeV_THQHadronicTag");
    ch -> Add(fullpath);

    // version 1
    //TString subversion = "7";
    //TString version = "v1." + subversion;
    //TString ver_str = "v1p" + subversion;
    //TChain *ch = new TChain("tagsDumper/trees/tHq_13TeV_THQHadronicTag");
    //ch -> Add("rootfiles/ntuples_" + version + "/TprimeBToTH_M-700_LH_TuneCUETP8M1_13TeV_Era2016_" + ver_str + ".root");
    //ch -> Add("rootfiles/ntuples_" + version + "/TprimeBToTH_M-700_LH_TuneCP5_13TeV_Era2017_" + ver_str + ".root");
    //ch -> Add("rootfiles/ntuples_" + version + "/TprimeBToTH_M-700_LH_TuneCP5_PSweights_13TeV_Era2018_" + ver_str + ".root");

    TString name_output_file = "plots/hist_" + rootfile;
    printf("[check] name_output_file = %s\n", name_output_file.Data());
    ScanChain_tprimetHHadronic(ch, name_output_file);
    

    //unsigned int entries = ch->GetEntries();
    //printf("entries = %d \n", entries);
    return 0;
}
