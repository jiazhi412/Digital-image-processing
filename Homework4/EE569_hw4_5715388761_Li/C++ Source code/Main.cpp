// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

#define RED 0
#define GREEN 1
#define BLUE 2

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Imagedata.h"
#include "OpencvAlgorithm.h"
#include <queue>


using namespace std;


int main(int argc, char* argv[])
{	// argv[1] image_path
	// argv[2] width
	// argv[3] height
	// argv[4] bytesPerPixel

	// Default variables
	int BytesPerPixel = 1;
	int Height = 400;
	int Width = 400;

	if (argc > 2) {
		Width = atoi(argv[2]);
		Height = atoi(argv[3]);
	}
	// Check if image is grayscale or color
	if (argc > 4) {
		BytesPerPixel = atoi(argv[4]);
	}
	const int size = Height * Width * BytesPerPixel;

	Imagedata raw(Height, Width, BytesPerPixel);
	raw.load(argv[1]);


	// Texture analysis

	//// Texture classification
	//// Feature extraction
	//vector<vector<double>> Feature_set;
	//for (int i = 0; i < 12; i++) {
	//	Imagedata texture(Height, Width, BytesPerPixel);
	//	texture.load("G:\\569\\Homework\\HW4\\Image\\HW4_images\\texture" + to_string(i+1) + ".raw");
	//	Feature_set.push_back(texture.Feature_vector());		
	//}

	////Dimension reduction PCA
	//Kernel Feature_set_matrix(Feature_set[0].size(),Feature_set.size());
	//Feature_set_matrix.Vector2Kernel(Feature_set);
	//OpencvAlgorithm A;
	////Kernel Feature_matrix_normalized = Feature_set_matrix.normalize();
	//Kernel Feature_matrix_normalized = Feature_set_matrix.Transpose().normalize();
	//vector<vector<double>> matrix_afterPCA = A.PCA(A.Kernel2Mat(Feature_matrix_normalized));

	//// K means cluster after PCA
	//cout << "K means cluster result after PCA" << endl;
	//A.k_mean_cluster(matrix_afterPCA);

	//// K means cluster without PCA
	//cout << "K means cluster result without PCA" << endl;
	//vector<vector<double>> matrix_withoutPCA = Feature_matrix_normalized.Kernel2vector2D();
	//A.k_mean_cluster(matrix_withoutPCA);
	//
	//// Strongest and weakest discriminant power of feature
	//OpencvAlgorithm OA;
	//vector<string> Laws_label = OA.Laws_label();
	//for (int i = 0; i < 25; i++) {
	//	cout << "The cluster result of single feature " << Laws_label[i] << endl;
	//	Kernel Feature_matrix_normalizeds = Feature_matrix_normalized;
	//	vector<vector<double>> single_feature = Feature_matrix_normalized.getColumn(i).Kernel2vector2D();
	//	A.k_mean_cluster(single_feature);
	//}




	// Texture segmentation

	//// Output the filter result after Laws filter
	//raw.set_doubledata();
	//vector<Imagedata> raw_filtered_normalized = raw.Feature_Extraction_filter_normalized();

	//for (int i = 0; i < raw_filtered_normalized.size(); i++) {
	//	raw_filtered_normalized[i].save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\comb" + to_string(i+1) + ".raw");
	//}



	//// Laws feature extraction
	//raw.set_doubledata();
	//vector<Imagedata> raw_filtered = raw.Feature_Extraction();

	//for (int i = 3; i < 35; i = i + 2) {
	//	// Energy feature computation
	//	int N = i; // window size
	//	OpencvAlgorithm A;
	//	vector<vector<double>> Energy_feature = A.Energy_feature_computation(raw_filtered, N);

	//	// Energy feature normalization
	//	vector<vector<double>> Energy_feature_normalization = A.Energy_feature_normalizationwithLL(Energy_feature);

	//	Kernel temp(Energy_feature_normalization[0].size(), Energy_feature_normalization.size());
	//	temp.Vector2Kernel(Energy_feature_normalization);
	//	vector<vector<double>> Energy_feature_normalization_transpose = temp.Kernel2vector2D();

	//	// Segmentation
	//	int cluster_number = 7;
	//	int iteration_number = 200;
	//	vector<vector<int>> cluster_label = A.k_mean_cluster_no_print(Energy_feature_normalization_transpose, cluster_number, iteration_number);
	//	Imagedata result(Height, Width, BytesPerPixel);
	//	result.segmentation(cluster_label);
	//	result.save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\segmentation" + to_string(N) + ".raw");
	//}



	/*Improvment1 : Adopt the PCA for feature reduction*/
	//// Laws feature extraction
	//raw.set_doubledata();
	//vector<Imagedata> raw_filtered = raw.Feature_Extraction();
	//for (int i = 3; i < 35; i = i + 2) {
	//	// Advanced texture segmentation technique
	//	// 1 PCA
	//	int N = i;
	//	OpencvAlgorithm A;
	//	vector<vector<double>> Energy_feature = A.Energy_feature_computation(raw_filtered, N);

	//	// Energy feature normalization
	//	vector<vector<double>> Energy_feature_normalization = A.Energy_feature_normalizationwithLL(Energy_feature);
	//	Kernel temp(Energy_feature_normalization[0].size(), Energy_feature_normalization.size());
	//	temp.Vector2Kernel(Energy_feature_normalization);
	//	vector<vector<double>> Energy_feature_normalization_transpose_PCA = A.PCA_no_print(A.Kernel2Mat(temp));

	//	// Segmentation
	//	int cluster_number = 7;
	//	int iteration_number = 200;
	//	vector<vector<int>> cluster_label = A.k_mean_cluster_no_print(Energy_feature_normalization_transpose_PCA, cluster_number, iteration_number);
	//	Imagedata result(Height, Width, BytesPerPixel);
	//	result.segmentation(cluster_label);
	//	result.save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\segmentation_PCA" + to_string(N) + ".raw");
	//}

	/*Improvment2 : Gaussian window*/
    // Laws feature extraction
	raw.set_doubledata();
	vector<Imagedata> raw_filtered = raw.Feature_Extraction();
	for (int i = 3; i < 43; i = i + 2) {
		//Advanced texture segmentation technique
		// 1 PCA
		int N = 33;
		OpencvAlgorithm A;
		vector<vector<double>> Energy_feature = A.Energy_feature_computation(raw_filtered, N);

		// Energy feature normalization
		vector<vector<double>> Energy_feature_normalization = A.Energy_feature_normalizationwithLL(Energy_feature);
		Kernel temp(Energy_feature_normalization[0].size(), Energy_feature_normalization.size());
		temp.Vector2Kernel(Energy_feature_normalization);
		vector<vector<double>> Energy_feature_normalization_transpose_PCA = A.PCA_no_print(A.Kernel2Mat(temp));

		// Segmentation
		int cluster_number = 7;
		int iteration_number = 200;
		vector<vector<int>> cluster_label = A.k_mean_cluster_no_print(Energy_feature_normalization_transpose_PCA, cluster_number, iteration_number);
		Imagedata result(Height, Width, BytesPerPixel);
		result.segmentation(cluster_label);	

		/*Improvment3 : Post processing*/
		// Enhance some result of segmentation
		result.Emphasize(pair<int, int>(255, 2), 0);
		//result.save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\segmentation_PCA_enhance21.raw");
		result.Emphasize(pair<int, int>(500, 500), 100);
		//result.save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\segmentation_PCA_enhance22.raw");
		result.Emphasize(pair<int, int>(2, 255), 150);
		//result.save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\segmentation_PCA_enhance23.raw");
		result.Emphasize(pair<int, int>(255, 255), 200);

		result.save("G:\\569\\Homework\\HW4\\Image\\HW4_result\\segmentation_PCA_enhance" + to_string(N) + ".raw");
	}




	//// Image feature extractor
	//// Image matching 
	//cv::Mat img_1 = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\river1.jpg");
	//cv::Mat img_2 = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\river2.jpg");
	//double thres = 1;
	//OpencvAlgorithm OA;
	////OA.SIFT(img_1, img_2, thres);
	////OA.SIFT_largestscale(img_1, img_2);
	////OA.SIFT_smallestscale(img_1, img_2);
	////OA.SIFT_firstoctave(img_1, img_2);
	////OA.SIFT_lastoctave(img_1, img_2);
	//OA.SIFT_largestdistance(img_1, img_2);



	//// Bag of words
	//OpencvAlgorithm OA;
	//// return the centroids of two cluster of bag of words
	//Mat Centroids = OA.BOWKMEANSTRAINER();
	//Kernel Centroids_kernel = OA.Mat2Kernel(Centroids);
	//// Print the statistics for first feature and second feature for each eight.jpg
	//OA.BOWHIST_STATISTIC(Centroids_kernel);

	waitKey(0);
	return 0;
}



/*int cluster_number = 7;
int iteration_number = 100;
vector<vector<double>> centroid = OA.k_mean_cluster_centroid(Descriptors_kernel.Transpose().Kernel2vector2D(), cluster_number, iteration_number);


Mat test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_1.jpg");
OA.hist_cal(test, centroid);*/