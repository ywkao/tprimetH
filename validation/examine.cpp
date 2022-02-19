#include "t.C"

int main(int argc, char *argv[])
{
    TString input = argc<=1 ? "/eos/user/y/ykao/tPrimeExcessHgg/rootfiles/forMaxime/output_Data_v3p8_21Jul21.root" : argv[1];
    double expected_yields = argc<=2 ? 1. : atof(argv[2]);
    printf(">>> %s: %f\n", input.Data(), expected_yields);

    TTree *tree = 0;
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(input);
    if (!f || !f->IsOpen()) { f = new TFile(input); }
    f->GetObject("t",tree);

    t mytree(tree, input, expected_yields);
    mytree.Loop();

    return 0;
}
