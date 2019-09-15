// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

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
	int convert(int h, int w, int p); // convert the position in a the height * width * byteperpixel to the position in a line
	int get_height(); // return height
	int get_width(); // return width
	int get_byteperpixel(); // return byteperpixel
	vector<vector<vector<double>>> get_data_double(); // get double data of imagedata

	//image operation
	Imagedata Boundaryextension(int ex); //Boundary extension
	Imagedata Crop(int N); //crop operation	
	Imagedata Boundaryextension_double(int ex); //Boundary extension for double data
	Imagedata DN_Gaussion_double(int N, double sigma); // Gaussian filter for double data
	Imagedata Convolution_double(Kernel k); // convolution for double data
	void double2usignedc(); //change double data to unsigned char data
	Imagedata Crop_double(int N); // crop operation for double data
	Imagedata Save_double(string path); // save double data to path
	double* write_double(); // write double data to buff
	void pure(unsigned char color); // set the whole image to the specific color					
	void set_color_data(int i, int j, vector<unsigned char> c); //set color data
	vector<unsigned char> get_color_data(int i, int j); //get color data
	Imagedata RGB2GRAY(); //convert RGB image to gray-level image
	Imagedata Binary(int threshold); // convert gray-level image to binary image in 0 and 255
	Imagedata Binarize(); //convert range from 0 and 255 to 0 and 1
	Imagedata RBinarize(); //convert range from 0 and 1 to 0 and 255
	Imagedata label_pixel(vector<pair<int, int>> v); // label some specific pixels
	Imagedata DN_Median(int N); // Denoise filter (Median)
	void Color_merge(Imagedata R_component, Imagedata G_component, Imagedata B_component); // Combine separable RGB channels into a RGB image(object)
	Imagedata get_RGB(int i); //get single channel data

	// Texture analysis
	// Texture classification
	vector<double> Feature_vector(); // get the 25-D feature vector of a texture
	Imagedata Sub_Mean(); // subtract mean to the image
	vector<Imagedata> Feature_Extraction();	// get a set of imagedata of the image after laws filter
	vector<Imagedata> Feature_Extraction_filter_normalized();	// get a set of imagedata of the image after laws filter
	double Average_energy(); // calculate the average energy of the filtered image
	
	// Texture Segmentation
	void segmentation(vector<vector<int>> label); // segment the image according to the label
	void Emphasize(pair<int, int> centre,unsigned char s); // label specific connected domain with s graylevel
};
#endif //CPP_IMAGEDATA_H