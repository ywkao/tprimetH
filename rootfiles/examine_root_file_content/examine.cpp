#include "t.C"

int main()
{
    //TFile *fin = TFile::Open("MVABaby_ttHHadronic_v5.7_tprimetH_impute_hct_BDT_FCNC.root");
    //TTree *t = (TTree*) fin->Get("t");

    t t;
    t.Loop();

    return 0;
}
