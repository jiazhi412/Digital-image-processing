// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

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

    // Geometric Transformation
	vector<pair<int, int>> find_corner(); // find the corner for sub-image
	Imagedata rotation(); // wrap the rotation
	Imagedata modify_edge(int hei, int wid); // modify the edge after rotation
	Imagedata counter_clock(); // make a 90 degree counter clock rotation
	Imagedata scale(int hei, int wid); // shrink or enlarge the image into a specific size with height(hei) and width(wid)
	Imagedata insert(Imagedata A, Imagedata B, Imagedata C); // Insert three sub-image to the bigger image
	Imagedata test_find_corner(vector<pair<int, int>> v); // test the corner found 

	// Spatial warping
	vector<Imagedata> seperate(); // seperate RGB image into three separable images
	Imagedata Spatial_warping(); // wrap for spatial warping (forward)
	Imagedata Spatial_warping_reverse(); // wrap for spatial warping (reverse)
	void Spatial_combine(Imagedata down, Imagedata up, Imagedata left, Imagedata right); // combine four different direction image into a complete image (forward)
	void Spatial_combine_reverse(Imagedata down, Imagedata up, Imagedata left, Imagedata right); // combine four different direction image into a complete image (reverse)

	Imagedata Sobel_X(); // X Sobel edge detector
	Imagedata Sobel_Y(); // Y Sobel edge detector

	// Morphological Processing
	void square(int size); // generate a square with size
	void rectangle(int h, int w); // generate a rectangle with height(h) and width(w)
	Imagedata Shrinking(); // wrap for shrinking
	Imagedata Skeleton(); // wrap for skeleton
	Imagedata Bridge(); // wrap for bridge after skeleton
	Imagedata Thinning(); // wrap for thinning

	// Defect Detection and Correction (deer)
	vector<pair<int, int>> find_defect(); // find the defect in the body of deer
	void emphasize_defect(vector<pair<int,int>> defect,int size); // Circle the defect with a rectangle
	void delete_defect(vector<pair<int, int>> defect); // Delete the defect area
	void boundary_modify(); // Set the boundary of the image to 0 to get the frame

	// Object analysis (Rice)
	// Segment the grains in gray scale image to black(0)-and-white(255) image where grains is 255 and background is 0 according the offset of background gray value
	Imagedata Grain_segmentation_value_offset(int offset); 
	// Segment the grains in gray scale image to black(0)-and-white(255) image where grains is 255 and background is 0 according the offset of background position
	Imagedata Grain_segmentation_position_offset(int offset);
	vector<pair<int, int>> find_grain(); // find grains in shrinking image
	int area_grain(pair<int, int> centre); // calculate the area of grains by the centre in segmentation image
	vector<pair<int,double>> average_area(vector<vector<pair<int, int>>> cluster); // calculate the average area of each cluster in segmentation image
	Imagedata cluster_label(vector<pair<int, int>> cluster_single); // Generate a gray-level image with the single cluster
	Imagedata cluster_label_RGB(Imagedata cluster_label_Binary); // Generate a RGB image with the single cluster
};
#endif //CPP_IMAGEDATA_H