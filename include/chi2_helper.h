#ifndef _CHI2_HELPER_
#define _CHI2_HELPER_

#include <fstream>
#include <vector>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TString.h>
#include <TLorentzVector.h>

TMatrixD get_cov_matrix_2x2(TString json_file);
TMatrixD get_cov_matrix_3x3(TString json_file);
double chi2_calculator(double w_mass, double t_mass);
double chi2_calculator_2x2(double w_mass, double t_mass, TString json_file);
double chi2_calculator_3x3(double w_mass, double t_mass, double tprime_mass, TString json_file);
bool get_the_best_wjets_candidate(std::vector<int> &indices_wjets, std::vector<TLorentzVector> jets, int index_bjet, double &min_chi2_value);
bool get_the_best_bjj_candidate(std::vector<int> &indices_bjj, std::vector<TLorentzVector> jets, TLorentzVector diphoton, std::vector<double> btag_scores, double &min_chi2_value, TString json_file);
bool matching_teller(std::vector<int> v_true, std::vector<int> v_test);

#endif
