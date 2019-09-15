// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

#ifndef CPP_OpencvALGORITHM_H
#define CPP_OpencvALGORITHM_H

#include <vector>
#include <string.h>
#include "Kernel.h"
#include "Patterntree.h"
#include "cluster.h"
#include "Imagedata.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"opencv.hpp"

#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/features2d.hpp>  

using namespace cv;

class OpencvAlgorithm {

public:

	// SIFT
	vector<string> Laws_label(); // return a string vector with Laws filter labels	
	void SIFT(Mat img_1, Mat img_2, double thres); // The warp for SIFT and Brute Force matching
	void SIFT_largestscale(Mat img_1, Mat img_2); // key point with largest scale, this time image with samllest scale
	void SIFT_smallestscale(Mat img_1, Mat img_2); // key point with smallest scale, this time image with largest scale
	void SIFT_firstoctave(Mat img_1, Mat img_2); // key point in first octave
	void SIFT_lastoctave(Mat img_1, Mat img_2); // key point in last octave
	void SIFT_largestdistance(Mat img_1, Mat img_2); // the match point with the largest l2 norm distance
	void SIFT_feature(Mat image,string path); // show the iamge and save the image to path
	
	// Texture classification
	vector<vector<double>> PCA(cv::Mat pcaSet); // wrapping for PCA
	vector<vector<double>> PCA_no_print(cv::Mat pcaSet); // wrapping for PCA without print
	cv::Mat Kernel2Mat(Kernel k); // convert kernel to cv::Mat
	Kernel Mat2Kernel(cv::Mat mat); // convert cv::Mat to kernel

	// K means
	void k_mean_cluster(vector<vector<double>> data); // wrapping for k-means cluster 
	// Kmean with centroid without print
	vector<vector<int>> k_mean_cluster_no_print(vector<vector<double>> data, int cluster_number, int iteration_number);
	// Kmean with centroid as return value
	vector<vector<double>> k_mean_cluster_centroid(vector<vector<double>> data, int cluster_number, int iteration_number);
	// Energy feature vector calculation
	vector<vector<double>> Energy_feature_computation(vector<Imagedata> Image, int window_size);
	// Energy feature vector normalized
	vector<vector<double>> Energy_feature_normalizationwithLL(vector<vector<double>> Energy_feature);

	// Bag of words
	vector<int> hist_cal(Mat test, vector<vector<double>> centroids); // calculate the histogram for test according to centroids
	Mat BOWKMEANSTRAINER(); // return the centroids of two cluster of bag of words
	void BOWHIST_STATISTIC(Kernel Centroids); // Count the score for first feature and second feature for each eight.jpg
};
#endif //CPP_OpencvALGORiTHM_H