#include "chi2_helper.h"
#include "json/json.h"

double w_boson_mass = 80.4;//GeV
double top_quark_mass = 175.;//GeV

TMatrixD get_cov_matrix_2x2(TString json_file)
{
    TMatrixD matrix(2,2);

    Json::Value root;
    Json::Reader reader;
    std::ifstream ifs(json_file.Data());

    if(!reader.parse(ifs, root)) printf("fail to parse\n");
    else{
        matrix(0,0) = root["covMatrix_00"].asDouble();
        matrix(0,1) = root["covMatrix_01"].asDouble();
        matrix(1,0) = root["covMatrix_10"].asDouble();
        matrix(1,1) = root["covMatrix_11"].asDouble();
    }

    return matrix;
}

TMatrixD get_cov_matrix_3x3(TString json_file)
{
    TMatrixD matrix(3,3);

    Json::Value root;
    Json::Reader reader;
    std::ifstream ifs(json_file.Data());

    //if(ifs==NULL) printf("json file does not exist\n");
    if(!reader.parse(ifs, root)) printf("fail to parse\n");
    else{
        matrix(0,0) = root["covMatrix_00"].asDouble();
        matrix(0,1) = root["covMatrix_01"].asDouble();
        matrix(0,2) = root["covMatrix_02"].asDouble();
        matrix(1,0) = root["covMatrix_10"].asDouble();
        matrix(1,1) = root["covMatrix_11"].asDouble();
        matrix(1,2) = root["covMatrix_12"].asDouble();
        matrix(2,0) = root["covMatrix_20"].asDouble();
        matrix(2,1) = root["covMatrix_21"].asDouble();
        matrix(2,2) = root["covMatrix_22"].asDouble();
    }

    return matrix;
}

double chi2_calculator_2x2(double w_mass, double t_mass, TString json_file)
{
    // load value
    TVectorD vec_mean_values(2);

    Json::Value root;
    Json::Reader reader;
    std::ifstream ifs(json_file.Data());

    if(!reader.parse(ifs, root)) printf("fail to parse\n");
    else{
        vec_mean_values(0) = root["mass_reco_w"].asDouble();
        vec_mean_values(1) = root["mass_reco_top"].asDouble();
    }

    // evaluation
    TVectorD vec_mass(2);
    vec_mass(0) = w_mass - vec_mean_values(0);
    vec_mass(1) = t_mass - vec_mean_values(1);

    TMatrixD matrix = get_cov_matrix_2x2(json_file);

    double chi2_value = matrix.Invert()*vec_mass*vec_mass;

    return chi2_value;
}

double chi2_calculator_3x3(double w_mass, double t_mass, double tprime_mass, TString json_file)
{
    // load value
    TVectorD vec_mean_values(3);

    Json::Value root;
    Json::Reader reader;
    std::ifstream ifs(json_file.Data());

    if(!reader.parse(ifs, root)) printf("fail to parse\n");
    else{
        vec_mean_values(0) = root["mass_reco_w"].asDouble();
        vec_mean_values(1) = root["mass_reco_top"].asDouble();
        vec_mean_values(2) = root["mass_reco_tprime"].asDouble();
    }

    // evaluation
    TVectorD vec_mass(3);
    vec_mass(0) = w_mass - vec_mean_values(0);
    vec_mass(1) = t_mass - vec_mean_values(1);
    vec_mass(2) = tprime_mass - vec_mean_values(2);

    TMatrixD matrix = get_cov_matrix_3x3(json_file);

    double chi2_value = matrix.Invert()*vec_mass*vec_mass;

    return chi2_value;
}

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

bool get_the_best_wjets_candidate(std::vector<int> &indices_wjets, std::vector<TLorentzVector> jets, int index_bjet, double &min_chi2_value)
{
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

    bool has_resonable_reco_chi2 = indices_wjets[0] >= 0 && indices_wjets[1] >= 0;
    return has_resonable_reco_chi2;
}

double pfDeepCSV_btag_loose_wp = 0.1522;

bool get_the_best_bjj_candidate(std::vector<int> &indices_bjj, std::vector<TLorentzVector> jets, TLorentzVector diphoton, std::vector<double> btag_scores, double &min_chi2_value, TString json_file)
{
    std::size_t num_jets = jets.size();
    for(std::size_t i = 0; i < num_jets; ++i ){ // b-jet
        if (btag_scores[i] < pfDeepCSV_btag_loose_wp) continue;
        for(std::size_t j = 0; j < num_jets-1; ++j ){ // w-jet1
            if(j==i) continue;
            for(std::size_t k = j+1; k < num_jets; ++k ){ // w-jet2
                if(k==i) continue;

                TLorentzVector bjet = jets[i];
                TLorentzVector w_candidate = jets[j] + jets[k];
                TLorentzVector top_candidate = w_candidate + bjet;
                TLorentzVector tprime_candidate = top_candidate + diphoton;
                double w_mass = w_candidate.M();
                double t_mass = top_candidate.M();
                double tprime_mass = tprime_candidate.M();
                //double chi2 = chi2_calculator_3x3(w_mass, t_mass, tprime_mass, json_file);
                double chi2 = chi2_calculator_2x2(w_mass, t_mass, json_file);
                if(chi2 < min_chi2_value){
                    indices_bjj[0] = i;
                    indices_bjj[1] = j;
                    indices_bjj[2] = k;
                    min_chi2_value = chi2;
                }
            }
        }
    }//end of looping jets

    bool has_resonable_reco = indices_bjj[0] >= 0 && indices_bjj[1] >= 0 && indices_bjj[2] >= 0;
    return has_resonable_reco;
}

bool matching_teller(std::vector<int> v_true, std::vector<int> v_test)
{
    bool is_non_negative = v_test[0]>=0 && v_test[1]>=0 && v_test[2]>=0;
    bool bjet_is_matched = v_true[0] == v_test[0];
    bool wjets_is_matched = (v_true[1] == v_test[1] && v_true[2] == v_test[2]) || (v_true[1] == v_test[2] && v_true[2] == v_test[1]);

    bool is_matched = is_non_negative && bjet_is_matched && wjets_is_matched;

    return is_matched;
}
