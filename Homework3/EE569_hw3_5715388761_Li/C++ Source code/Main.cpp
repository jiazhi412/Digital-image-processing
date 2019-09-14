// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

#define RED 0
#define GREEN 1
#define BLUE 2

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Imagedata.h"
#include "Algorithm.h"
#include "Patterntree.h"
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



	//// Geometric transformation
	//Imagedata raw_rotation = raw.rotation();
	//Imagedata raw_rotation_DN = raw_rotation.DN_Median(3);
	//raw_rotation.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse_rotation1_forward.raw");
	//raw_rotation_DN.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse_rotation_DN1.raw");

	//Imagedata raw_counter_clock = raw_rotation;
	//Imagedata raw_scale = raw_counter_clock.scale(160, 160);
	//raw_scale.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse1.raw");

	// filling the holes
	Imagedata A(160, 160, 1);
	A.load("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse1.raw");
	Imagedata B(160, 160, 1);
	B.load("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse2.raw");
	Imagedata C(160, 160, 1);
	C.load("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse3.raw");

	Imagedata result = raw.insert(A, B, C);
	result.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\lighthouse.raw");


	//// Spatial Warping
	//vector<Imagedata> raw_seperate = raw.seperate();		
	//// 1:down 2:up 3:left 4:right
	//Imagedata result_SW(Height, Width, BytesPerPixel);
	//result_SW.Spatial_combine(raw_seperate[0], raw_seperate[1], raw_seperate[2], raw_seperate[3]);
	//result_SW.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\hat_SW.raw");

	//Imagedata result_SW_reverse(Height, Width, BytesPerPixel);
	//result_SW_reverse.Spatial_combine_reverse(raw_seperate[0], raw_seperate[1], raw_seperate[2], raw_seperate[3]);
	//result_SW_reverse.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\hat_SW_reverse.raw");


	// Morphological processing
	/*Imagedata raw_Shrinking = raw.Shrinking();
	raw_Shrinking.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\p4s.raw");

	Imagedata raw_Thinning = raw.Thinning();
	raw_Thinning.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\p4t.raw");

	Imagedata raw_Skeleton = raw.Skeleton();
	raw_Skeleton.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\p4k.raw");
	Imagedata raw_Skeleton_bridge = raw_Skeleton.Binarize().Bridge();
	raw_Skeleton_bridge.RBinarize().save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\p4kb.raw");
	*/

	//// Test
	//Imagedata rectangle(200, 200, BytesPerPixel);
	//rectangle.rectangle(100, 100);
	//rectangle.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rec.raw");
	//rectangle.Shrinking().save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rect.raw");


	//// Deer
	//raw.boundary_modify();
	//Imagedata raw_shrink1 = raw.Shrinking();
	//raw_shrink1.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\deer_S.raw");
	//Imagedata raw_thin1 = raw.Thinning();
	//raw_thin1.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\deer_T.raw");
	//vector<pair<int, int>> defect = raw.find_defect();
	//raw.emphasize_defect(defect,4);
	//raw.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\deer_emphasize.raw");
	//raw.delete_defect(defect);
	//raw.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\deer_defectless.raw");
	//Imagedata raw_shrink2 = raw.Shrinking();
	//raw_shrink2.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\deer_defectless_S.raw");
	//Imagedata raw_thin2 = raw.Thinning();
	//raw_thin2.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\deer_defectless_T.raw");



	// Rice	
	// Part1 : Get clean image
	//// Single threshold solution
	//int thre = 77;
	//Imagedata raw_final = raw.RGB2GRAY().Binary(thre);		
	//raw_final.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_Binary_" + to_string(thre) + ".raw");


	//// Single threshold solution with median filter
	//int N = 3;
	//int thre = 77;
	//Imagedata raw_final = raw.DN_Median(N).RGB2GRAY().Binary(thre);
	//raw_final.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_Binary_Median_" + to_string(thre) + ".raw");

   
	//// Using position offset
 //   int N = 3;
	//int offset = 4;
	//Imagedata raw_value_offset = raw.DN_Median(N).Grain_segmentation_position_offset(offset);
	//Imagedata raw_GRAY = raw_value_offset.RGB2GRAY();	
	//Imagedata raw_GRAY_Median = raw_GRAY.DN_Median(5);
	//Imagedata raw_final = raw_GRAY_Median.Binary(0);
	//raw_final.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_position_offset_" + to_string(offset) + ".raw");


	//// Best solution with value offset   		
	//int N = 3;
	//int offset = 14;
	//Imagedata raw_value_offset = raw.DN_Median(N).Grain_segmentation_value_offset(offset);
	//Imagedata raw_GRAY = raw_value_offset.RGB2GRAY();
	//Imagedata raw_GRAY_Median = raw_GRAY.DN_Median(5);
	//Imagedata raw_final = raw_GRAY_Median.Binary(0);
	//raw_final.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_perfect.raw");

	

	//// Part2 : count the number
	//// Count the number of rice grains by shrink
	//Imagedata raw_shrink = raw_final.Shrinking();
	//raw_shrink.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_shrink.raw");
	//vector<pair<int, int>> grains = raw_shrink.Binarize().find_grain();
	//cout << "The total number of rice grains is " << grains.size() << endl;

	//// Categorize rice grains by cluster algorithm
	//Algorithm A;
	//vector<vector<pair<int, int>>> cluster = A.cluster(grains);
	//for (int i = 0; i < cluster.size(); i++) {		
	//	Imagedata test = raw_final.cluster_label(cluster[i]);
	//	test.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice" + to_string(i + 1) + ".raw");
	//}

	//// Calculate the size of each rice grain by connected domain detection
	//vector<pair<int, double>> statistic = raw_final.average_area(cluster);

	//// Rank the grain’s size from small to large in terms of type
	//vector<double> average_size;
	//for (int i = 0; i < cluster.size(); i++) {
	//	average_size.push_back(statistic[i].second);
	//}
	//sort(average_size.begin(),average_size.end());
	//for (int i = 0; i < cluster.size(); i++) {
	//	int check = average_size[i];
	//	for (int j = 0; j < cluster.size(); j++) {
	//		if ((int) statistic[j].second == check) {
	//			Imagedata rank = raw_final.cluster_label(cluster[j]);
	//			rank.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_rank" + to_string(i + 1) +"_" +to_string(check) + ".raw");
	//		//	rank.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_rank" + to_string(i + 1) + ".raw");

	//			Imagedata rank_RGB = raw.cluster_label_RGB(rank);
	//			rank_RGB.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_rank_RGB" + to_string(i + 1) + "_" + to_string(check) + ".raw");
	//		//	rank_RGB.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_rank_RGB" + to_string(i + 1) + ".raw");
	//			break;
	//		}
	//	}
	//}
	return 0;
}
