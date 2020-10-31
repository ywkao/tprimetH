#include <stdio.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TChain.h>
#include "ScanChain.C"

int main(int argc, char* argv[])
{
    printf("argc = %d, ", argc);
    printf("argv = %s\n", argv[1]);

    TString location = "/wk_cms/ykao/work/CMSSW_10_6_8/rootfiles";
    TString name = argv[1];
    TString fullname = location + "/" + name;

    TChain *ch = new TChain("tagsDumper/trees/tHq_13TeV_THQHadronicTag");
    //ch -> Add(fullname);
    ch -> Add("rootfiles/signal_ntuples_2016/TprimeBToTH_M-700_LH_TuneCUETP8M1_13TeV_Era2016.root");
    ch -> Add("rootfiles/signal_ntuples_2017/TprimeBToTH_M-700_LH_TuneCP5_13TeV_Era2017.root");
    ch -> Add("rootfiles/signal_ntuples_2018/TprimeBToTH_M-700_LH_TuneCP5_PSweights_13TeV_Era2018.root");

    ScanChain(ch);
    //unsigned int entries = ch->GetEntries();
    //printf("entries = %d \n", entries);
    return 0;
}
