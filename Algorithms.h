#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include"structure.h"

#include <vector>
#include <string>

using namespace std ;

Metrics FCFS(Request requests[], int n, int initial_head_position);
Metrics SSTF(Request requests[], int n, int initial_head_position);
Metrics SCAN(Request requests[], int n,int initial_head_position,bool move_right);
Metrics CSCAN(Request requests[], int n,int initial_head_position);
Metrics LOOK(Request request[], int n,int initial_head_position,bool  move_right);
Metrics CLOOK(Request requests[],int n, int initial_head_position);
#endif




