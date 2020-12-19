#include "sorting.h"

bool sortByGreaterValue(const pair<int,double>& pair1, const pair<int,double>& pair2 ) {
  return pair1.second > pair2.second;
}

bool sortBySmallerValue(const pair<int,double>& pair1, const pair<int,double>& pair2 ) {
  return pair1.second < pair2.second;
}

vector< pair<int, double> > sortVectorGreater(const vector<double> v) {
  vector< pair<int, double> > v2;
  for (int i = 0; i < v.size(); i++)
    v2.push_back(pair<int, double>(i, v[i]));
  sort(v2.begin(), v2.end(), sortByGreaterValue);
  return v2;
}

vector< pair<int, double> > sortVectorSmaller(const vector<double> v) {
  vector< pair<int, double> > v2;
  for (int i = 0; i < v.size(); i++)
    v2.push_back(pair<int, double>(i, v[i]));
  sort(v2.begin(), v2.end(), sortBySmallerValue);
  return v2;
}
