// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

#ifndef CPP_ALGORITHM_H
#define CPP_ALGORITHM_H

#include <vector>
#include <string.h>
#include "Kernel.h"
#include "Patterntree.h"

using namespace std;

class Algorithm {

public:
	// Basic function
	int correction(double a);
	void combine(vector<Kernel> &ori, vector<Kernel> add); // Combine two sets of Kernel to be a bigger one
	int comp(int i); // 1 to 0 and 0 to 1
	
	// Morphological processing
	vector<Kernel> Condi_Shrink(); // Generate conditional shrink pattern set
    vector<Kernel> Condi_Thin(); // Generate conditional thin pattern set
	vector<Kernel> Condi_Skeleton(); // Generate conditional skeleton pattern set
	vector<Kernel> UCondi_ST(); // Generate unconditional shrink and thin pattern set
	vector<Kernel> UCondi_K(); // Generate unconditional skeleton pattern set
	vector<Kernel> extendABC(int arr[]); // Convert ABC label to D label in uncondition pattern
	Bnode* PATTERNS_TREE(vector<Kernel> k); // Generate the tree according to a set of kernel given
	
	// rice
	vector<vector<pair<int,int>>> cluster(vector<pair<int, int>> v); // Divide the grains into 11 cluster according their distance
	double distance(pair<int, int> a, pair<int, int> b); // Calulate the distance between two points		
};
#endif //CPP_ALGORiTHM_H