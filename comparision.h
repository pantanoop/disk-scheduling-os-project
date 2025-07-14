#ifndef comparision_H
#define comparision_H
# include "Algorithms.h" 
#include"structure.h"


#include <vector>
#include <string>

using namespace std ;

BestAlgorithmInfo compareMetrics(const vector<Metrics>& metrics);
void printComparisonTable(const vector<Metrics> &metrics);

#endif