#include "t.C"
#include "p.C"

int main(int argc, char *argv[])
{
    if(argc<=1)
    {
        printf(">>> Please specify an input root file\n");
        return 1;
    }

    TString input = argv[1];
    printf(">>> %s\n", input.Data());

    TTree *tree = 0;
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(input);
    if (!f || !f->IsOpen()) { f = new TFile(input); }

    bool is_leptonic = input.Contains("leptonic");

    //--- hadronic channel ---//
    if(!is_leptonic) {
        printf(">>> hadronic channel: %s\n", input.Data());

        f->GetObject("t",tree);
        t mytree(tree, input);
        mytree.Loop();

    //--- leptonic channel ---//
    } else {
        f->GetObject("Data_13TeV_THQLeptonicTag",tree);
        p mytree(tree, input);
        mytree.Loop();
    }

    return 0;
}
