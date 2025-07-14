#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include<numeric>
#include "Algorithms.h"
#include"structure.h"

using namespace std;



Metrics FCFS(Request requests[], int n, int initial_head_position) {
    Metrics metrics;
    metrics.id = 1;
    metrics.name="FCFS";
    metrics.totalHeadMovements = 0;
    metrics.serviceOrder.clear();
    metrics.maxSeekTime = 0;

    int current_head_position = initial_head_position;
    int total_seek_time = 0;
    vector<int> seek_times;
    metrics.serviceOrder.push_back(initial_head_position);

    for (int i = 0; i < n; ++i) {
        int seek_time = abs(requests[i].requestPosition - current_head_position);
        metrics.totalHeadMovements += seek_time;
        total_seek_time += seek_time;
        metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
        metrics.serviceOrder.push_back(requests[i].requestPosition);
        current_head_position = requests[i].requestPosition;
        seek_times.push_back(seek_time);
    }

    metrics.AST = static_cast<double>(total_seek_time) / n;
    metrics.throughput = static_cast<double>(n) * 1000 / metrics.totalHeadMovements;
    metrics.RT = metrics.AST;

    double mean = metrics.AST;
    double variance_sum = 0.0;
    for (int seek_time : seek_times) {
        variance_sum += (seek_time - mean) * (seek_time - mean);
    }
    metrics.variance = variance_sum / n;

    return metrics;
}

Metrics SSTF(Request requests[], int n, int initial_head_position) {
    Metrics metrics;
    metrics.id = 2;
    metrics.name="SSTF";
    metrics.totalHeadMovements = 0;
    metrics.serviceOrder.clear();
    metrics.maxSeekTime = 0;
    metrics.serviceOrder.push_back(initial_head_position);

    vector<bool> visited(n, false);
    int current_head_position = initial_head_position;
    int total_seek_time = 0;
    vector<int> seek_times;

    for (int i = 0; i < n; ++i) {
        int min_seek_time = INT_MAX;
        int next_index = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                int seek_time = abs(requests[j].requestPosition - current_head_position);
                if (seek_time < min_seek_time) {
                    min_seek_time = seek_time;
                    next_index = j;
                }
            }
        }
        visited[next_index] = true;
        int seek_time = abs(requests[next_index].requestPosition - current_head_position);
        metrics.totalHeadMovements += seek_time;
        total_seek_time += seek_time;
        metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
        metrics.serviceOrder.push_back(requests[next_index].requestPosition);
        current_head_position = requests[next_index].requestPosition;
        seek_times.push_back(seek_time);
    }

    metrics.AST = static_cast<double>(total_seek_time) / n;
    metrics.throughput = static_cast<double>(n) * 1000 / metrics.totalHeadMovements;
    metrics.RT = metrics.AST;

    double mean = metrics.AST;
    double variance_sum = 0.0;
    for (int seek_time : seek_times) {
        variance_sum += (seek_time - mean) * (seek_time - mean);
    }
    metrics.variance = variance_sum / n;

    return metrics;
}

Metrics SCAN(Request requests[], int n, int initial_head_position, bool move_right) {
    Metrics metrics;
    metrics.id = 3;
    metrics.name="SCAN";
    metrics.totalHeadMovements = 0;
    metrics.serviceOrder.clear();
    metrics.maxSeekTime = 0;
    metrics.serviceOrder.push_back(initial_head_position);

    vector<int> left, right;
    for (int i = 0; i < n; ++i) {
        if (requests[i].requestPosition < initial_head_position) {
            left.push_back(requests[i].requestPosition);
        } else {
            right.push_back(requests[i].requestPosition);
        }
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int current_head_position = initial_head_position;
    if (move_right) {
        for (int pos : right) {
            int seek_time = abs(pos - current_head_position);
            metrics.totalHeadMovements += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(pos);
            current_head_position = pos;
        }

        metrics.totalHeadMovements += abs(199 - current_head_position); // Move to the end
        metrics.serviceOrder.push_back(199);
        current_head_position = 199;

        for (int i = static_cast<int>(left.size()) - 1; i >= 0; --i) {
            int seek_time = abs(left[i] - current_head_position);
            metrics.totalHeadMovements += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(left[i]);
            current_head_position = left[i];
        }
    } else {
        for (int i = static_cast<int>(left.size()) - 1; i >= 0; --i) {
            int seek_time = abs(left[i] - current_head_position);
            metrics.totalHeadMovements += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(left[i]);
            current_head_position = left[i];
        }

        metrics.totalHeadMovements += abs(0 - current_head_position); // Move to the beginning
        metrics.serviceOrder.push_back(0);
        current_head_position = 0;

        for (int pos : right) {
            int seek_time = abs(pos - current_head_position);
            metrics.totalHeadMovements += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(pos);
            current_head_position = pos;
        }
    }

    metrics.AST = static_cast<double>(metrics.totalHeadMovements) / n;
    metrics.RT = metrics.AST;
    metrics.throughput = static_cast<double>(n) * 1000 / metrics.totalHeadMovements;

    double variance_sum = 0.0;
    for (int seek_time : metrics.serviceOrder) {
        variance_sum += pow(seek_time - metrics.AST, 2);
    }
    metrics.variance = variance_sum / n;

    return metrics;
}

Metrics CSCAN(Request requests[], int n, int initial_head_position) {
    Metrics metrics;
    metrics.id = 4;
    metrics.name="C-SCAN";
    metrics.totalHeadMovements = 0;
    metrics.serviceOrder.clear();
    metrics.maxSeekTime = 0;
    metrics.serviceOrder.push_back(initial_head_position);

    vector<int> left, right;

    for (int i = 0; i < n; ++i) {
        if (requests[i].requestPosition < initial_head_position) {
            left.push_back(requests[i].requestPosition);
        } else {
            right.push_back(requests[i].requestPosition);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int current_head_position = initial_head_position;

    for (int pos : right) {
        int seek_time = abs(pos - current_head_position);
        metrics.totalHeadMovements += seek_time;
        metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
        metrics.serviceOrder.push_back(pos);
        current_head_position = pos;
    }

    metrics.totalHeadMovements += abs(199 - current_head_position); 
    metrics.serviceOrder.push_back(199);
    current_head_position = 0;
    metrics.totalHeadMovements += 199;

    for (int pos : left) {
        int seek_time = abs(pos - current_head_position);
        metrics.totalHeadMovements += seek_time;
        metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
        metrics.serviceOrder.push_back(pos);
        current_head_position = pos;
    }

    metrics.AST = static_cast<double>(metrics.totalHeadMovements) / n;
    metrics.RT = metrics.AST;

    double variance_sum = 0.0;
    for (int seek_time : metrics.serviceOrder) {
        variance_sum += pow(seek_time - metrics.AST, 2);
    }
    metrics.variance = variance_sum / n;
    metrics.throughput = static_cast<double>(n) * 1000 / metrics.totalHeadMovements;

    return metrics;
}

Metrics LOOK(Request requests[], int n, int initial_head_position, bool move_right) {
    Metrics metrics;
    metrics.id = 5;
    metrics.name="LOOK";
    metrics.serviceOrder.push_back(initial_head_position);
    metrics.totalHeadMovements = 0;
    metrics.maxSeekTime = 0;

    vector<Request> sorted_requests(requests, requests + n);
    sort(sorted_requests.begin(), sorted_requests.end(), [](const Request& a, const Request& b) {
        return a.requestPosition < b.requestPosition;
    });

    int current_head_position = initial_head_position;
    int total_seek_time = 0;
    vector<int> seek_times;

    auto it = lower_bound(sorted_requests.begin(), sorted_requests.end(), Request{initial_head_position}, [](const Request& a, const Request& b) {
        return a.requestPosition < b.requestPosition;
    });

    if (move_right) {
        
        for (auto itr = it; itr != sorted_requests.end(); ++itr) {
            int seek_time = abs(itr->requestPosition - current_head_position);
            metrics.totalHeadMovements += seek_time;
            total_seek_time += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(itr->requestPosition);
            current_head_position = itr->requestPosition;
            seek_times.push_back(seek_time);
        }
        
        for (auto itr = it - 1; itr >= sorted_requests.begin(); --itr) {
            int seek_time = abs(itr->requestPosition - current_head_position);
            metrics.totalHeadMovements += seek_time;
            total_seek_time += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(itr->requestPosition);
            current_head_position = itr->requestPosition;
            seek_times.push_back(seek_time);
        }
    } else {
        for (auto itr = it - 1; itr >= sorted_requests.begin(); --itr) {
            int seek_time = abs(itr->requestPosition - current_head_position);
            metrics.totalHeadMovements += seek_time;
            total_seek_time += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(itr->requestPosition);
            current_head_position = itr->requestPosition;
            seek_times.push_back(seek_time);
        }
        for (auto itr = it; itr != sorted_requests.end(); ++itr) {
            int seek_time = abs(itr->requestPosition - current_head_position);
            metrics.totalHeadMovements += seek_time;
            total_seek_time += seek_time;
            metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
            metrics.serviceOrder.push_back(itr->requestPosition);
            current_head_position = itr->requestPosition;
            seek_times.push_back(seek_time);
        }
    }

    metrics.AST = total_seek_time / n;
    metrics.throughput = n * 1000 / metrics.totalHeadMovements;
    metrics.RT = metrics.AST;

    int mean = metrics.AST;
    int variance_sum = 0;
    for (int seek_time : seek_times) {
        variance_sum += (seek_time - mean) * (seek_time - mean);
    }
    metrics.variance = variance_sum / n;

    return metrics;
}

Metrics CLOOK(Request requests[], int n, int initial_head_position) {
    Metrics metrics;
    metrics.id = 6;
    metrics.name="C-LOOK";
    metrics.serviceOrder.push_back(initial_head_position);
    metrics.totalHeadMovements = 0;
    metrics.maxSeekTime = 0;

    vector<Request> sorted_requests(requests, requests + n);
    sort(sorted_requests.begin(), sorted_requests.end(), [](const Request& a, const Request& b) {
        return a.requestPosition < b.requestPosition;
    });

    int current_head_position = initial_head_position;
    int total_seek_time = 0;
    vector<int> seek_times;

    auto it = lower_bound(sorted_requests.begin(), sorted_requests.end(), Request{initial_head_position}, [](const Request& a, const Request& b) {
        return a.requestPosition < b.requestPosition;
    });

    for (auto itr = it; itr != sorted_requests.end(); ++itr) {
        int seek_time = abs(itr->requestPosition - current_head_position);
        metrics.totalHeadMovements += seek_time;
        total_seek_time += seek_time;
        metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
        metrics.serviceOrder.push_back(itr->requestPosition);
        current_head_position = itr->requestPosition;
        seek_times.push_back(seek_time);
    }

    for (auto itr = sorted_requests.begin(); itr != it; ++itr) {
        int seek_time = abs(itr->requestPosition - current_head_position);
        metrics.totalHeadMovements += seek_time;
        total_seek_time += seek_time;
        metrics.maxSeekTime = max(metrics.maxSeekTime, seek_time);
        metrics.serviceOrder.push_back(itr->requestPosition);
        current_head_position = itr->requestPosition;
        seek_times.push_back(seek_time);
    }

    metrics.AST = total_seek_time / n;
    metrics.throughput = n * 1000 / metrics.totalHeadMovements;
    metrics.RT = metrics.AST;

    int mean = metrics.AST;
    int variance_sum = 0;
    for (int seek_time : seek_times) {
        variance_sum += (seek_time - mean) * (seek_time - mean);
    }
    metrics.variance = variance_sum / n;

    return metrics;
}

