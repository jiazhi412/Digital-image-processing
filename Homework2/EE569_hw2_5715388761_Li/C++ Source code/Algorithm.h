// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.2.8

#ifndef CPP_ALGORITHM_H
#define CPP_ALGORITHM_H

#include <vector>
#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class Algorithm {

public:

	int RangedRandDemo(int range_min, int range_max, int n); //Generate random number in range[min,max]
	int find_closest(int a); //Find the close binary value to 0 or 255
	int correction(double a); //Correct the gray-level in range[0,255]
	
	string getNearestVertex(vector<unsigned char> old); //Find the nearest vertex according to MBVQ
	vector<unsigned char> string2int_MBVQ(string vertex); //Convert the string to integer

	cv::Mat Canny_edge_detection(cv::Mat src, int lowthreshold, int highthreshold, int kernel_size); //Apply Canny_edge_detection
};
#endif //CPP_ALGORiTHM_H