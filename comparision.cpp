# include <iostream>
# include <vector>
# include <fstream>
# include <iomanip>
# include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>
#include"structure.h"
# include "Algorithms.h" 

BestAlgorithmInfo compareMetrics(const vector<Metrics>& metrics) {
    Metrics bestMetric = metrics[0];
    std::string bestParameter = "Total Head Movements";

    for (const auto& metric : metrics) {
        if (metric.totalHeadMovements < bestMetric.totalHeadMovements) {
            bestMetric = metric;
            bestParameter = "Total Head Movements";
        } else if (metric.totalHeadMovements == bestMetric.totalHeadMovements) {
            if (metric.AST < bestMetric.AST) {
                bestMetric = metric;
                bestParameter = "Average Seek Time (AST)";
            } else if (metric.AST == bestMetric.AST) {
                if (metric.throughput > bestMetric.throughput) {
                    bestMetric = metric;
                    bestParameter = "Throughput";
                } else if (metric.throughput == bestMetric.throughput) {
                    if (metric.RT < bestMetric.RT) {
                        bestMetric = metric;
                        bestParameter = "Response Time (RT)";
                    } else if (metric.RT == bestMetric.RT) {
                        if (metric.maxSeekTime < bestMetric.maxSeekTime) {
                            bestMetric = metric;
                            bestParameter = "Maximum Seek Time";
                        } else if (metric.maxSeekTime == bestMetric.maxSeekTime) {
                            if (metric.variance < bestMetric.variance) {
                                bestMetric = metric;
                                bestParameter = "Variance";
                            }
                        }
                    }
                }
            }
        }
    }

    return {bestMetric, bestParameter};
}

void printComparisonTable(const vector<Metrics> &metrics) {
  
  const int totalWidth = 146 + 5; // Adjust the +5 value to control the extension length

  // Print the top border extending beyond variance
  cout << setfill('-') << setw(totalWidth) << "-" << endl;
  cout << setfill(' ');

  // Print the header row
  cout << "| " << setw(10) << left << "Algorithm" 
       << " | " << setw(20) << right << "Total Head Movements" 
       << " | " << setw(25) << right << "Average Seek Time (AST)" 
       << " | " << setw(20) << right << "Throughput" 
       << " | " << setw(20) << right << "Response Time (RT)" 
       << " | " << setw(20) << right << "Maximum Seek Time" 
       << " | " << setw(16) << right << "Variance" << " |" << endl;

  // Print the header bottom border extending beyond variance
  cout << setfill('-') << setw(totalWidth) << "-" << endl;
  cout << setfill(' ');

  // Print each row of the table
  for (const Metrics &metric : metrics) {
    cout << "| " << setw(7) << left << metric.name<<"("<<metric.id<<")"
         << " | " << setw(20) << right << metric.totalHeadMovements 
         << " | " << setw(25) << right << fixed << setprecision(3) << metric.AST 
         << " | " << setw(20) << right << fixed << setprecision(4) << metric.throughput 
         << " | " << setw(20) << right << fixed << setprecision(3) << metric.RT 
         << " | " << setw(20) << right << metric.maxSeekTime 
         << " | " << setw(16) << right << fixed << setprecision(2) << metric.variance << " |" << endl;

    // Print the row bottom border extending beyond variance
    cout << setfill('-') << setw(totalWidth) << "-" << endl;
    cout << setfill(' ');
  }
}