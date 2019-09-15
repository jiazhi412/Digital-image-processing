// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

#include "cluster.h"

using namespace std;

double cal_distance(vector<double> a, vector<double> b)
{
	int da = a.size();
	int db = b.size();
	if (da != db) cerr << "Dimensions of two vectors must be same!!\n";
	double val = 0.0;
	for (int i = 0; i < da; i++)
	{
		val += pow((a[i] - b[i]), 2);
	}
	return pow(val, 0.5);
}
vector<Cluster> k_means(vector<vector<double> > trainX, int k, int maxepoches)
{
	const int row_num = trainX.size();
	const int col_num = trainX[0].size();

	// Initial cluster centroid
	vector<Cluster> clusters(k);
	int seed = (int)time(NULL);
	for (int i = 0; i < k; i++)
	{
		srand(seed);
		int c = rand() % row_num;
		clusters[i].centroid = trainX[c];
		seed = rand();
	}

	// iteration until converage (maxepoches represent the maximum iteration number)
	for (int it = 0; it < maxepoches; it++)
	{
		// Clear all sample information 
		for (int i = 0; i < k; i++)
		{
			clusters[i].samples.clear();
		}
		// Figure out which cluster all samples belong to
		for (int j = 0; j < row_num; j++)
		{
			// initial all sample into first clusters
			int c = 0;
			double min_distance = cal_distance(trainX[j], clusters[c].centroid);
			for (int i = 1; i < k; i++)
			{
				double distance = cal_distance(trainX[j], clusters[i].centroid);
				if (distance < min_distance)
				{
					min_distance = distance;
					c = i;
				}
			}
			clusters[c].samples.push_back(j);
		}

		// update cluster centroid
		for (int i = 0; i < k; i++)
		{
			vector<double> val(col_num, 0.0);
			for (uint j = 0; j < clusters[i].samples.size(); j++)
			{
				int sample = clusters[i].samples[j];
				for (int d = 0; d < col_num; d++)
				{
					val[d] += trainX[sample][d];
					if (j == clusters[i].samples.size() - 1)
						clusters[i].centroid[d] = val[d] / clusters[i].samples.size();
				}
			}
		}
	}
	return clusters;
}