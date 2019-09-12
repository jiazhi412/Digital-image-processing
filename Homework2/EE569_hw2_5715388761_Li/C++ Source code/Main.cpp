// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.2.8

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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


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

	//Digital half-toning
	// Random_threholding
	/*Imagedata raw_Random_threholding = raw.Random_threholding();
	raw_Random_threholding.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bridge_Random_threholding.raw");*/

	//Dithering Matrix
	/*int N = 32;
	Imagedata raw_Dithering =  raw.Dithering(N);
	raw_Dithering.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bridge_Dithering" + to_string(N) +".raw");*/

	//Error diffusion
	////Floyd		
	//Imagedata raw_Floyd = raw.Floyd();
	//raw_Floyd.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bridge_Floyd.raw"); 

	////JJN
	//Imagedata raw_JJN = raw.JJN();
	//raw_JJN.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bridge_JJN.raw");

	//////Stucki
	//Imagedata raw_Stucki = raw.Stucki();
	//raw_Stucki.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bridge_Stucki.raw");

	//Color Halftoning
	////Error diffusion
	//Imagedata raw_RGB_Floyd = raw.Color_Floyd();
	//raw_RGB_Floyd.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bird_RGB_Floyd.raw");

	////MBVQ
	//Imagedata raw_MBVQ = raw.Color_MBVQ();
	//raw_MBVQ.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\bird_RGB_MBVQ.raw");

	//Edge detection
	//Sobel
	/*Imagedata raw_GRAY = raw.RGB2GRAY();
	Imagedata raw_Sobel_X = raw_GRAY.Sobel_X();
	Imagedata raw_Sobel_Y = raw_GRAY.Sobel_Y();
	raw_Sobel_X.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\Pig_Sobel_X.raw");
	raw_Sobel_Y.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\Pig_Sobel_Y.raw");

	Imagedata raw_Sobel = raw_Sobel_X.Sobel_merge(raw_Sobel_Y);

	for (int i = 1; i < 100; i++) {
		int threshold = i;
		Imagedata raw_Sobel_Thres = raw_Sobel.Tune(threshold);
		raw_Sobel_Thres.save("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\Pig_Sobel" + to_string(threshold) + ".raw");		
	}*/
	
	//Canny
	cv::Mat src = cv::imread(argv[1]);
	Algorithm A;
	int lowThreshold = 2000;
	int highThrehold = 6000;
	int kernel_size = 5;
	
	cv::Mat dst = A.Canny_edge_detection(src, lowThreshold, highThrehold, kernel_size);
	cv::imwrite("G:\\569\\Homework\\HW2\\Image\\HW2_result_images\\Pig_Canny" + to_string(lowThreshold) + "_" + to_string(highThrehold) + "_" + to_string(kernel_size) + ".jpg", dst);

	return 0;
}
