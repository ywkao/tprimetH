#include <stdio.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TChain.h>
#include "covMatrix_ScanChain.C"

int main(int argc, char* argv[])
{
    TString location = argv[1];
    TString rootfile = argv[2];
    TString year     = argv[3];
    TString mass     = argv[4];
    TString fullpath = location + "/" + rootfile;
    printf("[check] fullpath = %s\n", fullpath.Data());

    TChain *ch = new TChain("tagsDumper/trees/tHq_13TeV_THQHadronicTag");
    ch -> Add(fullpath);

    TString name_output_file = "plots/covMatrix_" + rootfile;
    printf("[check] name_output_file = %s\n", name_output_file.Data());
    covMatrix_ScanChain(ch, name_output_file, year, mass);

    return 0;
}
