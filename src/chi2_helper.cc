#include "chi2_helper.h"

double w_boson_mass = 80.4;//GeV
double top_quark_mass = 175.;//GeV

double chi2_calculator(double w_mass, double t_mass)
{
    double chi2_value;

    TVectorD vec_mass(2);
    vec_mass(0) = w_mass - w_boson_mass;
    vec_mass(1) = t_mass - top_quark_mass;

    TMatrixD matrix(2,2);
    // Estimate variance from pdg masses
    matrix(0,0) = (0.1 * w_boson_mass) * (0.1 * w_boson_mass);
    matrix(1,1) = (0.1 * top_quark_mass) * (0.1 * top_quark_mass);
    // Ignore covariance terms for the moment
    matrix(0,1) = 0.0;
    matrix(1,0) = 0.0;

    chi2_value = matrix.Invert()*vec_mass*vec_mass;
    return chi2_value;
}

std::vector<int> get_the_best_wjets_candidate(std::vector<TLorentzVector> jets, int index_bjet, double &min_chi2_value)
{
    std::vector<int> indices_wjets(2, -999);

    TLorentzVector bjet = jets[index_bjet];

    std::size_t num_jets = jets.size();
    for(std::size_t i=0; i<num_jets; ++i){
        if(i==index_bjet) continue;
        for(std::size_t j=i+1; j<num_jets; ++j){
            if(j==index_bjet) continue;
            TLorentzVector w_candidate = jets[i] + jets[j];
            double w_mass = w_candidate.M();
            TLorentzVector top_candidate = w_candidate + bjet;
            double t_mass = top_candidate.M();
            double chi2 = chi2_calculator(w_mass, t_mass);
            if(chi2 < min_chi2_value){
                indices_wjets[0] = i;
                indices_wjets[1] = j;
                min_chi2_value = chi2;
            }
        }
    }//end of looping jets

    return indices_wjets;
}
