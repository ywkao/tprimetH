#include <stdio.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TChain.h>
//#include "ScanChain_tprimetHHadronic.C"
#include "ScanChain_tprimetHHadronic_signal.C"
//#include "ScanChain_tprimetHHadronic_ttH.C" //v3.1 contains bdt scores from producer

int main(int argc, char* argv[])
{
    TString location = argv[1];
    TString rootfile = argv[2];
    TString treeName = argv[3]; // "tagsDumper/trees/tHq_13TeV_THQHadronicTag"
    TString xml_file = argv[4];
    TString year     = argv[5];
    TString fullpath = location + "/" + rootfile;
    printf("[check] fullpath = %s\n", fullpath.Data());

    TChain *ch = new TChain(treeName);
    ch -> Add(fullpath);

    //TString name_output_file = "plots/hist_" + rootfile;
    TString name_output_file = "plots/hist_" + rootfile;
    printf("[check] name_output_file = %s\n", name_output_file.Data());
    ScanChain_tprimetHHadronic_signal(ch, name_output_file, treeName, xml_file, year);
    //ScanChain_tprimetHHadronic_ttH(ch, name_output_file, treeName, xml_file, year);
    //ScanChain_tprimetHHadronic(ch, name_output_file, year, "1000"); //mass_str: for picking up a json file of covariance matrix

    return 0;
}
