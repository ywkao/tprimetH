#include "truth_matching.h"

truth_matching_helper::truth_matching_helper(vector<TLorentzVector> gen_particles_, vector<TLorentzVector> jets_, vector<float> gen_pdgIds_, vector<float> gen_status_, vector<float> mom_pdgIds_)
{
    pass_gen_deltaR_criterion = false;
    pass_gen_pt_ratio_criterion = false;
    bool_fill_histogram = false;
    gen_particles = gen_particles_;
    jets = jets_;
    gen_pdgIds = gen_pdgIds_;
    gen_status = gen_status_;
    mom_pdgIds = mom_pdgIds_;
    counter_bquark_matching = 0;
    counter_wquark_matching = 0;
}

truth_matching_helper::truth_matching_helper(vector<TLorentzVector> gen_particles_, vector<TLorentzVector> jets_, vector<float> gen_pdgIds_, vector<float> gen_status_, vector<float> mom_pdgIds_, TH1F* h_deltaR_partons_, TH1F* h_ptRatio_partons_)
{
    pass_gen_deltaR_criterion = false;
    pass_gen_pt_ratio_criterion = false;
    bool_fill_histogram = true;
    h_deltaR_partons = h_deltaR_partons_;
    h_ptRatio_partons = h_ptRatio_partons_;

    gen_particles = gen_particles_;
    jets = jets_;
    gen_pdgIds = gen_pdgIds_;
    gen_status = gen_status_;
    mom_pdgIds = mom_pdgIds_;
    counter_bquark_matching = 0;
    counter_wquark_matching = 0;
}

truth_matching_helper::~truth_matching_helper(){}

bool           truth_matching_helper::get_pass_gen_deltaR_criterion()   { return pass_gen_deltaR_criterion   ; }
bool           truth_matching_helper::get_pass_gen_pt_ratio_criterion() { return pass_gen_pt_ratio_criterion ; }
vector<int>    truth_matching_helper::get_register_genIndex()           { return vec_genIndex_register       ; }
vector<int>    truth_matching_helper::get_register_jetIndex()           { return vec_jetIndex_register       ; }
vector<float>  truth_matching_helper::get_register_pdgId()              { return vec_pdgId_register          ; }
vector<float>  truth_matching_helper::get_register_mompdgId()           { return vec_mompdgId_register       ; }
vector<double> truth_matching_helper::get_register_deltaR()             { return vec_deltaR_register         ; }
vector<double> truth_matching_helper::get_register_ptRatio()            { return vec_ptRatio_register        ; }

bool truth_matching_helper::perform_mc_truth_matching()
{
    for( unsigned int genLoop = 0; genLoop < gen_particles.size(); ++genLoop )
    {
        bool is_outgoing_parton = gen_status[genLoop] == 23 && abs(gen_pdgIds[genLoop]) <  6;
        if(!is_outgoing_parton) continue;
        TLorentzVector part = gen_particles[genLoop];

        vector<double> vec_deltaR;
        vector<double> vec_ptRatio;
        for( unsigned int index = 0; index < jets.size(); ++index )
        {
            TLorentzVector jet = jets[index];
            double deltaR = sqrt( (jet.Eta()-part.Eta())*(jet.Eta()-part.Eta()) + (jet.Phi()-part.Phi())*(jet.Phi()-part.Phi()) );
            double ptRatio = part.Pt() > 0. ? (jet.Pt() - part.Pt()) / part.Pt() : 1.;
            vec_deltaR.push_back(deltaR);
            vec_ptRatio.push_back(abs(ptRatio));
        }

        vector<std::pair<int, double> > vec_deltaR_sorted = sortVectorSmaller(vec_deltaR);


        //counter_before_gen_criteria += 1;
        if(bool_fill_histogram)
            h_deltaR_partons->Fill(vec_deltaR_sorted[0].second);

        pass_gen_deltaR_criterion = vec_deltaR_sorted[0].second < 0.4;
        if(!pass_gen_deltaR_criterion) continue;

        if(bool_fill_histogram)
            h_ptRatio_partons->Fill(vec_ptRatio[vec_deltaR_sorted[0].first]);

        pass_gen_pt_ratio_criterion = vec_ptRatio[vec_deltaR_sorted[0].first] < 0.5;
        if( !(pass_gen_deltaR_criterion && pass_gen_pt_ratio_criterion) ) continue;
        //counter_after_gen_criteria += 1;


        bool is_bjet = abs(gen_pdgIds[genLoop]) == 5 && abs(mom_pdgIds[genLoop]) == 6;
        bool is_wjet = abs(gen_pdgIds[genLoop]) <  5 && abs(mom_pdgIds[genLoop]) == 24;
        if(is_bjet) counter_bquark_matching += 1;
        if(is_wjet) counter_wquark_matching += 1;

        vec_genIndex_register.push_back(genLoop);
        vec_jetIndex_register.push_back(vec_deltaR_sorted[0].first);
        vec_pdgId_register.push_back(gen_pdgIds[genLoop]);
        vec_mompdgId_register.push_back(mom_pdgIds[genLoop]);
        vec_deltaR_register.push_back(vec_deltaR_sorted[0].second);
        vec_ptRatio_register.push_back(vec_ptRatio[vec_deltaR_sorted[0].first]);

    }

    bool has_reasonable_gen_matching = counter_bquark_matching >= 1 && counter_wquark_matching >= 2;
    return has_reasonable_gen_matching;
}
