// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.1.19

#ifndef CPP_IMAGEDATA_H
#define CPP_IMAGEDATA_H
#include "Kernel.h"

using namespace std;

class Imagedata {

private:
	int height;
	int width;
	int byteperpixel;
	vector<vector<vector<unsigned char>>> data;
	//for shot noise
	vector<vector<vector<double>>> data_double;

public:
	//basic function
	Imagedata(int h, int w, int p); //constructor
	~Imagedata(); //destructor
	void set_doubledata(); //initialize double data for shot noise
	void set_data(int d); //initialize all data with value d
	void read(unsigned char* buff); //read data from buff
	void load(string path); //load data from path
	unsigned char* write(); //write data to buff
	void save(string path); //save data to path
	Imagedata get_RGB(int i); //get single channel data
	int convert(int h, int w, int p);

	//Demosaicing
	Imagedata Boundaryextension(int ex); //Boundary extension
	Imagedata Crop(int N); //crop operation
	Imagedata Raw2RGB_BL(); //Bilinear demosaicing
	Imagedata Raw2RGB_MHC(Imagedata Imagedata_BL); //MHC demosaicing

	//Histogram
	void Histogram_create(const char* path); //create and save histogram to path
	void Histogram_cummulative(const char* path); //create and save cummulative histogram to path
	void Transfer_function(const char* path); //create and save transfer function to path
	Imagedata Hist_EQ_TR(); //histogram equalization by transfer function
	Imagedata Hist_EQ_BF(); //histogram equalization by bucket filling

	//Denoise
	Imagedata Convolution(Kernel k); //convolution operation with kernel
	Imagedata DN_Uniform(int N); //uniform filter
	Imagedata DN_Gaussion(int N,double sigma); //Gaussian filter
	Imagedata DN_Bilateral(int N, double sigmac, double sigmas); //Bilateral filter
	Imagedata DN_Nonlocalmean(int N_neighbor, int N_search, double h, double sigma); //Non-local mean filter
	Imagedata DN_Median(int N); //median filter

	double PSNR(string path); //calculate PSNR according to the noise-free image in path
	void PSNR_save(string path,double PSNR); //save PSNR to path

	//Shot noise
	Imagedata Anscombe_forward(); //Anscombe transformation
	Imagedata Anscombe_reverse_biased(); //Anscombe inverse transformation(biased)
	Imagedata Anscombe_reverse_unbiased(); //Anscombe inverse transformation(unbiased)

	Imagedata Boundaryextension_double(int ex); //Boundary extension for double data
	Imagedata DN_Gaussion_double(int N, double sigma); // Gaussian filter for double data
	Imagedata Convolution_double(Kernel k); // convolution for double data

	void double2usignedc(); //change double data to unsigned char data
	Imagedata Crop_double(int N); // crop operation for double data
	Imagedata Save_double(string path); // save double data to path
	double* write_double(); // write double data to buff
};
#endif //CPP_IMAGEDATA_H