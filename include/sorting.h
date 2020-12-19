#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <algorithm>
using namespace std;

bool sortByGreaterValue(const pair<int,double>& pair1, const pair<int,double>& pair2 );
bool sortBySmallerValue(const pair<int,double>& pair1, const pair<int,double>& pair2 );
vector< pair<int, double> > sortVectorGreater(const vector<double> v);
vector< pair<int, double> > sortVectorSmaller(const vector<double> v);

#endif
