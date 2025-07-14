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
#include "comparision.h" 
# define TOTAL_ALGO 6

using namespace std;

void printMetrics(const vector<Metrics>& metrics, int initial_head_position) {
    for (const auto& metric : metrics) {
        cout<<metric.name<<endl;
        cout << "Algorithm ID: " << metric.id << endl;
        cout << "Total Head Movements: " << metric.totalHeadMovements << endl;
        cout << "Service Order: ";
        for (int position : metric.serviceOrder) {
            cout << position << " ";
        }
        cout << endl;
        cout << "Average Seek Time (AST): " << metric.AST << endl;
        cout << "Throughput: " << metric.throughput << endl;
        cout << "Response Time (RT): " << metric.RT << endl;
        cout << "Maximum Seek Time: " << metric.maxSeekTime << endl;
        cout << "Variance: " << metric.variance << endl;
        cout << endl;
    }
}

vector<Metrics> collectMetrics(Request requests[], int n, int initial_head_position, bool move_right, BestAlgorithmInfo& bestAlgorithmInfo) {
    Metrics FCFS_OBJ, SSTF_OBJ, SCAN_OBJ, CSCAN_OBJ, LOOK_OBJ, CLOOK_OBJ;
    FCFS_OBJ = FCFS(requests, n, initial_head_position);
    FCFS_OBJ.name = "FCFS";
    SSTF_OBJ = SSTF(requests, n, initial_head_position);
    SSTF_OBJ.name = "SSTF";
    SCAN_OBJ = SCAN(requests, n, initial_head_position, move_right);
    SCAN_OBJ.name = "SCAN";
    CSCAN_OBJ = CSCAN(requests, n, initial_head_position);
    CSCAN_OBJ.name = "C-SCAN";
    LOOK_OBJ = LOOK(requests, n, initial_head_position, move_right);
    LOOK_OBJ.name = "LOOK";
    CLOOK_OBJ = CLOOK(requests, n, initial_head_position);
    CLOOK_OBJ.name = "C-LOOK";

    vector<Metrics> metrics = {FCFS_OBJ, SSTF_OBJ, SCAN_OBJ, CSCAN_OBJ, LOOK_OBJ, CLOOK_OBJ};

    bestAlgorithmInfo = compareMetrics(metrics);

    return metrics;
}

void writeToCsv(const vector<struct Metrics>& metrics, const string& filename) {
    ofstream file(filename);
    ofstream file2("Seek_Order.csv");
    if (!file.is_open() || !file2.is_open()) {
        cout << "Error while opening CSV file\n";
        exit(1);
    }

    file << "Algorithms,Total Head Movements,Throughput,Average Seek Time,Max Seek Time\n";
    file << fixed << setprecision(1);
    for (int i = 0; i < TOTAL_ALGO; i++) {
        file <<metrics[i].name << "," <<metrics[i].totalHeadMovements<<","<<metrics[i].RT<<metrics[i].throughput<<","<< metrics[i].AST << "," << metrics[i].maxSeekTime << "\n";
    }

    file2 << "Algorithms,Seek Order\n";
    for (int i = 0; i < TOTAL_ALGO; i++) {
        file2 << metrics[i].name;
        for (int j = 0; j < metrics[i].serviceOrder.size(); j++) {
            file2 << "," << metrics[i].serviceOrder[j];
        }
        file2 << "\n";
    }

    file.close();
    file2.close();
}

void writeBestAlgoToCsv(const BestAlgorithmInfo& bestAlgorithmInfo, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error while opening CSV file\n";
        exit(1);
    }

    const Metrics& metric = bestAlgorithmInfo.bestMetric;
    file << "Best Algorithm," << metric.name << "\n";
    file << "Total Head Movements," << metric.totalHeadMovements << "\n";
    file << "Average Seek Time (AST)," << metric.AST << "\n";
    file << "Throughput," << metric.throughput << "\n";
    file << "Response Time (RT)," << metric.RT << "\n";
    file << "Maximum Seek Time," << metric.maxSeekTime << "\n";
    file << "Variance," << metric.variance << "\n";

    file.close();
}

void plotGraph() {
    const char* cmd = "python plot.py"; 
    int exitStatus = system(cmd);
    if (exitStatus == 0) {
        cout << "Graphs Formed Successfully\n";
    } else {
        cout << "Error while making Graphs\n";
    }
}

void plotbar() {
    const char* cmd = "python result.py"; 
    int exitStatus = system(cmd);
    if (exitStatus == 0) {
        cout << "Graphs Formed Successfully\n";
    } else {
        cout << "Error while making Graphs\n";
    }
}

void plotbarBestAlgo() {
    const char* cmd = "python bestAlgo.py"; 
    int exitStatus = system(cmd);
    if (exitStatus == 0) {
        cout << "Graphs Formed Successfully\n";
    } else {
        cout << "Error while making Graphs\n";
    }
}


vector<Request> read_numbers(const string& filename, int n) {
    vector<Request> requests;
    requests.reserve(n); 

    ifstream infile(filename);
    if (infile.is_open()) {
        int number;
        for (int i = 0; i < n; ++i) {
            if (infile >> number) {
                requests.push_back({number});  
            } else {
                requests.push_back({0}); 
            }
        }
        infile.close();
    } else {
        cerr << "Unable to open file";
    }

    return requests;
}

int main() {
    int n;
    cout<<"enter the no. of requests:";
    cin >>n;
    vector<Request> result = read_numbers("input.txt", n);
    Request requests[n];
    for(int i=0;i<result.size();i++){
        requests[i]=result[i];
    }

    int initial_head_position = 53;
    bool move_right = true; 
    BestAlgorithmInfo bestAlgorithmInfo;
    vector<Metrics> allMetrics = collectMetrics(requests, n, initial_head_position, move_right, bestAlgorithmInfo);
    printMetrics(allMetrics, initial_head_position);
    cout << "Best Algorithm for the given input: " << bestAlgorithmInfo.bestMetric.name << endl;
    cout << "Differentiating Parameter: " << bestAlgorithmInfo.bestParameter << endl;
    cout<<endl;
    cout<<"Comparision Table"<<endl;
    printComparisonTable(allMetrics);
    writeToCsv(allMetrics,"Result.csv");
    writeBestAlgoToCsv(bestAlgorithmInfo,"bestAlgo.csv");
    plotGraph();
    plotbar();
    plotbarBestAlgo();
    return 0;
    
}
