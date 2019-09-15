#pragma once
// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

#ifndef CPP_CLUSTER_H
#define CPP_CLUSTER_H
#include<iostream>
#include<cmath>
#include<vector>
#include<ctime>
using namespace std;
typedef unsigned int uint;

struct Cluster
{
	vector<double> centroid;
	vector<uint> samples;
};

double cal_distance(vector<double> a, vector<double> b); // calculate the distance of two vectors
vector<Cluster> k_means(vector<vector<double>> trainX, int k, int maxepoches); // return cluster result according to training set

#endif //CPP_CLUSTER_H