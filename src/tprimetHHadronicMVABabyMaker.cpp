#include <stdio.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TChain.h>
#include "MakeMVABabies_tprimetHHadronic.C"

int main(int argc, char* argv[])
{
    TString location = argv[1];
    TString rootfile = argv[2];
    TString treeName = argv[3]; // "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    TString xml_file = argv[4];
    TString year     = argv[5];
    TString mass     = argv[6];
    TString fullpath = location + "/" + rootfile;
    printf("[check] fullpath = %s\n", fullpath.Data());

    TChain *ch = new TChain(treeName);
    ch -> Add(fullpath);

    TString name_output_file = "plots/hist_" + rootfile;

    BabyMaker *looper = new BabyMaker();
    looper->ScanChain(ch, name_output_file, treeName, "RunII", "", "impute", year, "");

    return 0;
}
