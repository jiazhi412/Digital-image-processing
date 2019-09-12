// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.1.19

#define R 0
#define G 1
#define B 2

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Imagedata.h"


using namespace std;

int main(int argc, char* argv[])
{	// argv[1] image_path
	// argv[2] width
	// argv[3] height
	// argv[4] bytesPerPixel

	// Default variables
	int BytesPerPixel=1;
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





	//// Bilinear (BL)
	//int ex = 1;
	//Imagedata raw_BE(Height + ex * 2, Width + ex * 2, BytesPerPixel);
	//Imagedata RGB_BL(Height, Width, BytesPerPixel * 3);
	//	
	//raw_BE = raw.Boundaryextension(ex);
	//RGB_BL = raw_BE.Raw2RGB_BL();
	//double PSNR_BL = RGB_BL.PSNR("G:\\569\\HW1_images\\HW1_images\\cat_ori.raw");

	//RGB_BL.save("G:\\569\\HW1_images\\Image_result\\cat_BL.raw");
	





	//// MHC		
	//ex = 2;
	//Imagedata raw_BE_MHC(Height + ex * 2, Width + ex * 2, BytesPerPixel);		
	//Imagedata RGB_MHC(Height, Width, BytesPerPixel * 3);
	//
	//raw_BE_MHC = raw.Boundaryextension(ex);		// for MHC ex = 2
	//RGB_MHC = raw_BE_MHC.Raw2RGB_MHC(RGB_BL);
	////double PSNR_MHC = RGB_MHC.PSNR("G:\\569\\HW1_images\\HW1_images\\cat_ori.raw");

	//RGB_BL.save("G:\\569\\HW1_images\\Image_result\\cat_MHC.raw");


	

	////Histogram  Manipulation
	////Method A : Transfer function TR	
	//Imagedata raw_TR(Height, Width, BytesPerPixel);
	//
	//raw_TR = raw.Hist_EQ_TR();

	//raw.Histogram_create("G:\\569\\HW1_images\\Image_result\\Hist_Rose_mix.raw");
	//raw.Transfer_function("G:\\569\\HW1_images\\Image_result\\TF_Rose_mix_TR.raw");
	//raw_TR.Histogram_create("G:\\569\\HW1_images\\Image_result\\Hist_Rose_mix_TR.raw");
	//
	//
	//raw_TR.save("G:\\569\\HW1_images\\Image_result\\Rose_mix_TR.raw");







	////Method B : Bucket filling	BF
	//Imagedata raw_BF(Height, Width, BytesPerPixel);

	//raw_BF = raw.Hist_EQ_BF();

	//raw.Histogram_create("G:\\569\\HW1_images\\Image_result\\Hist_Rose_mix.raw");
	//raw.Histogram_cummulative("G:\\569\\HW1_images\\Image_result\\CHist_Rose_mix_TR.raw");
	//raw_BF.Histogram_create("G:\\569\\HW1_images\\Image_result\\Hist_Rose_mix_BF.raw");
	//
	//raw_BF.save("G:\\569\\HW1_images\\Image_result\\Rose_mix_BF.raw");





	////Denoise
	//Uniform
	//int N = 5; // size of window
	//Imagedata raw_DN_Uniform(Height, Width, BytesPerPixel);	
	///*double PSNR_test = raw.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper.raw ");*/

	//raw_DN_Uniform = raw.DN_Uniform(N);

	//double PSNR = raw_DN_Uniform.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper.raw");
	//raw_DN_Uniform.save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Uniform" + to_string(N) + ".raw");
	//raw_DN_Uniform.PSNR_save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Uniform" + to_string(N) + ".raw",PSNR);







	//Gaussion 	
	//for (int i = 3; i < 23; i = i + 2) {
	//	for (double j = 0.5; j < 5; j = j + 0.5) {
	//		int N = i; // size of window
	//		double sigma = j; // standard deviation of kernel
	//		Imagedata raw_DN_Gaussion(Height, Width, BytesPerPixel);

	//		raw_DN_Gaussion = raw.DN_Gaussion(N, sigma);

	//		double PSNR = raw_DN_Gaussion.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper.raw");
	//		string sigma_str = to_string(sigma);
	//		sigma_str = sigma_str.substr(0, sigma_str.size() - 5);
	//		raw_DN_Gaussion.save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Gaussion" + to_string(N) + "_" + sigma_str + ".raw");
	//		raw_DN_Gaussion.PSNR_save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Gaussion" + to_string(N) + "_" + sigma_str + ".raw", PSNR);
	//	}
	//}
	






	//////Bilateral
	//int N = 3; // size of window
	//double sigmac = 1.5;
	//double sigmas = 145;
	//Imagedata raw_DN_Bilateral(Height, Width, BytesPerPixel);	
	//
	//raw_DN_Bilateral = raw.DN_Bilateral(N, sigmac,sigmas);

	//double PSNR = raw_DN_Bilateral.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper.raw");
	//string sigmac_str = to_string(sigmac);
	//sigmac_str = sigmac_str.substr(0, sigmac_str.size() - 5);
	//string sigmas_str = to_string(sigmas);
	//sigmas_str = sigmas_str.substr(0, sigmas_str.size() - 5);
	//raw_DN_Bilateral.save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Bilateral" + to_string(N) +"_"+ sigmac_str +"_"+ sigmas_str + ".raw");
	//raw_DN_Bilateral.PSNR_save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Bilateral" + to_string(N) + "_" + sigmac_str + "_" + sigmas_str + ".raw",PSNR);






	//////Non local mean
	//int N_neighbor = 3; // size of neighbor window
	//int N_search = 9; // size of search window
	//double h = 31;
	//double sigma = 1;
	//Imagedata raw_DN_Nonlocalmean(Height, Width, BytesPerPixel);	
	//
	//raw_DN_Nonlocalmean = raw.DN_Nonlocalmean(N_neighbor, N_search, h, sigma);

	//double PSNR = raw_DN_Nonlocalmean.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper.raw");
	//string h_str = to_string(h);
	//h_str = h_str.substr(0, h_str.size() - 5);
	//string sigma_str = to_string(sigma);
	//sigma_str = sigma_str.substr(0, sigma_str.size() - 5);
	//raw_DN_Nonlocalmean.save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Nonlocalmean" + to_string(N_neighbor) + "_" + to_string(N_search) + "_" + h_str + "_" + sigma_str + ".raw");
	//raw_DN_Nonlocalmean.PSNR_save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Nonlocalmean" + to_string(N_neighbor) + "_" + to_string(N_search) + "_" + h_str + "_" + sigma_str + ".raw",PSNR);






	////Median
	//int N = 3; // size of window	
	//Imagedata raw_DN_Median(Height, Width, BytesPerPixel);
	//	
	//raw_DN_Median = raw.DN_Median(N);

	//double PSNR = raw_DN_Median.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper.raw");
	//raw_DN_Median.save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Median" + to_string(N) + ".raw");
	//raw_DN_Median.PSNR_save("G:\\569\\HW1_images\\Image_result\\Pepper_uni_DN_Median" + to_string(N) + ".raw",PSNR);







    //color image
   // get the gray level in RGB channel 
   /* Imagedata raw_R = raw.get_RGB(R);
	raw_R.save("G:\\569\\HW1_images\\HW1_images\\rose_color_R.raw");
	Imagedata raw_G = raw.get_RGB(G);
	raw_G.save("G:\\569\\HW1_images\\HW1_images\\rose_color_G.raw");
	Imagedata raw_B = raw.get_RGB(B);
	raw_B.save("G:\\569\\HW1_images\\HW1_images\\rose_color_B.raw");*/

    //Uniform
	//int N = 5; // size of window
	//Imagedata raw_DN_Uniform(Height, Width, BytesPerPixel);	
	//Imagedata raw_DN_Uniform_NL(Height, Width, BytesPerPixel);
	//Imagedata raw_DN_Uniform_NL_G(Height, Width, BytesPerPixel);
	//raw_DN_Uniform = raw.DN_Uniform(N);

	//int N_neighbor = 5; // size of neighbor window
	//int N_search = 5; // size of search window
	//double h = 3;
	//double sigma = 3;

	//raw_DN_Uniform_NL = raw_DN_Uniform.DN_Nonlocalmean(N_neighbor, N_search, h, sigma);

	//N = 15; // size of window
	//sigma = 1; // standard deviation of kernel
	
	//raw_DN_Uniform_NL_G = raw_DN_Uniform_NL.DN_Gaussion(N, sigma);
	//raw.save("G:\\569\\HW1_images\\HW1_images\\rose_color_filted.raw");
	//raw_DN_Uniform.save("G:\\569\\HW1_images\\HW1_images\\rose_color_filted1.raw");
	//raw_DN_Uniform_NL.save("G:\\569\\HW1_images\\HW1_images\\rose_color_filted2.raw");
	//raw_DN_Uniform_NL_G.save("G:\\569\\HW1_images\\HW1_images\\rose_color_filted3.raw");
	//double PSNR = raw_DN_Uniform_NL_G.PSNR("G:\\569\\HW1_images\\HW1_images\\rose_color.raw");
	//raw_DN_Uniform_NL_G.PSNR_save("G:\\569\\HW1_images\\HW1_images\\rose_color_filted3.txt", PSNR);









	//Shot noise
    //Imagedata raw_Anscombe = raw.Anscombe_forward();
    //for (int i = 3; i < 5; i = i +2) {
    //	for (double j = 0.1; j < 1; j = j + 0.1) {
    //		int N = i; // size of window
    //		double sigma = j;
    //		Imagedata raw_Ansocombe_DN_Gaussian = raw_Anscombe.DN_Gaussion_double(N, sigma);
    //		Imagedata raw_DN_Gaussian = raw_Ansocombe_DN_Gaussian.Anscombe_reverse_biased();
    //		raw_DN_Gaussian.double2usignedc();
    //
    //		string sigma_str = to_string(sigma);
    //		sigma_str = sigma_str.substr(0, sigma_str.size() - 5);
    //		double PSNR = raw_DN_Gaussian.PSNR("G:\\569\\HW1_images\\HW1_images\\pepper_dark.raw");
    //		raw_DN_Gaussian.save("G:\\569\\HW1_images\\Image_result\\pepper_dark_noise_baised" + to_string(N) + "_" + sigma_str + ".raw");
    //		raw_DN_Gaussian.PSNR_save("G:\\569\\HW1_images\\Image_result\\pepper_dark_noise_baised" + to_string(N) + "_" + sigma_str + ".raw",PSNR);
    //	}
    //	}
	
	return 0;
}
