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
    TString xml_file = argv[3];
    TString year     = argv[4];
    TString mass     = argv[5];
    TString fullpath = location + "/" + rootfile;
    printf("[check] fullpath = %s\n", fullpath.Data());

    TChain *ch = new TChain("tagsDumper/trees/tHq_13TeV_THQHadronicTag");
    ch -> Add(fullpath);

    TString name_output_file = "plots/hist_" + rootfile;

    BabyMaker *looper = new BabyMaker();
    looper->ScanChain(ch, name_output_file, "RunII", "", "impute", year, "");

    return 0;
}
