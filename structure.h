#ifndef structure_H
#define structure_H
# include <iostream>
# include <vector>
# include <fstream>
# include <iomanip>
# include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

using namespace std ;

struct Request {
    int requestPosition;
};

struct Metrics {
    int id;
    string name;
    int totalHeadMovements;
    vector<int> serviceOrder;
    double AST;         
    int throughput;  
    double RT;          
    int maxSeekTime;    
    double variance;    
};

struct BestAlgorithmInfo {
    Metrics bestMetric;
    string bestParameter;
};

#endif