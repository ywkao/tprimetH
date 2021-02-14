#ifndef _TRUTH_MATCHING_H_
#define _TRUTH_MATCHING_H_
#include <TLorentzVector.h>
#include <TH1F.h>
#include <vector>
#include "sorting.h"
using namespace std;

class truth_matching_helper
{
    public:
        truth_matching_helper(vector<TLorentzVector>, vector<TLorentzVector>, vector<float>, vector<float>, vector<float>);
        truth_matching_helper(vector<TLorentzVector>, vector<TLorentzVector>, vector<float>, vector<float>, vector<float>, TH1F*, TH1F*);
        ~truth_matching_helper();
        bool perform_mc_truth_matching()       ;
        bool get_pass_gen_deltaR_criterion()   ;
        bool get_pass_gen_pt_ratio_criterion() ;
        vector<int>    get_register_genIndex() ;
        vector<int>    get_register_jetIndex() ;
        vector<float>  get_register_pdgId()    ;
        vector<float>  get_register_mompdgId() ;
        vector<double> get_register_deltaR()   ;
        vector<double> get_register_ptRatio()  ;

    private:
        bool pass_gen_deltaR_criterion;
        bool pass_gen_pt_ratio_criterion;

        bool bool_fill_histogram;
        TH1F *h_deltaR_partons;
        TH1F *h_ptRatio_partons;

        vector<TLorentzVector> gen_particles;
        vector<TLorentzVector> jets;
        vector<int>    vec_genIndex_register;
        vector<int>    vec_jetIndex_register;
        vector<float>  vec_pdgId_register;
        vector<float>  vec_mompdgId_register;
        vector<double> vec_deltaR_register;
        vector<double> vec_ptRatio_register;

        vector<float> gen_pdgIds;
        vector<float> gen_status;
        vector<float> mom_pdgIds;

        int counter_bquark_matching;
        int counter_wquark_matching;
};

#endif
