#ifndef _CHI2_HELPER_
#define _CHI2_HELPER_

#include <vector>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TLorentzVector.h>

double chi2_calculator(double w_mass, double t_mass);
std::vector<int> get_the_best_wjets_candidate(std::vector<TLorentzVector> jets, int index_bjet, double &min_chi2_value);

#endif
