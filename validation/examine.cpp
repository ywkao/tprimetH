#include "t.C"

int main(int argc, char *argv[])
{
    TString input = argc<=1 ? "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime/output_Data_v3p8_21Jul21.root" : argv[1];
    printf(">>> %s: ", input.Data());

    TTree *tree = 0;
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(input);
    if (!f || !f->IsOpen()) { f = new TFile(input); }
    f->GetObject("t",tree);

    t mytree(tree, input);
    mytree.Loop();

    return 0;
}
