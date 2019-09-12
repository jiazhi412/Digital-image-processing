// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.2.8

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
	void initialize(int d); //initialize all data with value d
	void read(unsigned char* buff); //read data from buff
	void load(string path); //load data from path
	unsigned char* write(); //write data to buff
	void save(string path); //save data to path
	Imagedata get_RGB(int i); //get single channel data
	int convert(int h, int w, int p);

	//image operation
	Imagedata Boundaryextension(int ex); //Boundary extension
	Imagedata Crop(int N); //crop operation
	Imagedata Convolution(Kernel k); //convolution operation with kernel
	Imagedata Boundaryextension_double(int ex); //Boundary extension for double data
	Imagedata DN_Gaussion_double(int N, double sigma); // Gaussian filter for double data
	Imagedata Convolution_double(Kernel k); // convolution for double data
	void double2usignedc(); //change double data to unsigned char data
	Imagedata Crop_double(int N); // crop operation for double data
	Imagedata Save_double(string path); // save double data to path
	double* write_double(); // write double data to buff

	//Edge detection
	Imagedata RGB2GRAY(); //convert RGB image to gray-level image
	Imagedata Sobel_X(); //Get the x-gradient values
	Imagedata Sobel_Y(); //Get the y-gradient values
	Imagedata Sobel_merge(Imagedata Sobel_Y); //Combine x and y gradient into whole gradient image
	Imagedata Tune(int threshold); //Get the edge map according to threshold

	//Digital halftoning
	//Dithering
	Imagedata Random_threholding(); //Random thresholding
	Imagedata Dithering(int index); //Generate dithering matrix

	//Error diffusion
	Imagedata Error_diffusion(Kernel k); //Error diffusion with kernel k
	Imagedata Floyd(); //Floyd-Steinberg's error diffusion
	Imagedata JJN(); //JJN error diffusion
	Imagedata Stucki(); //Stucki error diffusion

	//Color Halftoning with error diffusion
	Imagedata RGB2CMY(); //convert RGB image to CMY image
	Imagedata CMY2RGB(); //convert CMY image to RGB image
	Imagedata Color_Floyd(); //Separable error diffusion
	void Color_merge(Imagedata R_component, Imagedata G_component, Imagedata B_component); //Combine three separable channel image into RGB image
	Imagedata Color_MBVQ(); //MBVQ-based error diffusion
	
	void set_color_data(int i, int j, vector<unsigned char> c); //set color data
	vector<unsigned char> get_color_data(int i, int j); //get color data
};
#endif //CPP_IMAGEDATA_H