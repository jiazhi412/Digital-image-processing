// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.2.8

#define RED 0
#define GREEN 1
#define BLUE 2
#define pi 3.1415926

#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <algorithm>
#include "Imagedata.h"
#include "Kernel.h"
#include "Algorithm.h"


using namespace std;

Imagedata::Imagedata(int h, int w, int p) {
	height = h;
	width = w;
	byteperpixel = p;
	data.resize(p);
	for (int i = 0; i < p; i++) {
		data[i].resize(height);
		for (int j = 0; j < height; j++) {
			data[i][j].resize(width);
		}
	}
}

Imagedata::~Imagedata() {}

void Imagedata::set_doubledata() {
	data_double.resize(byteperpixel);
	for (int i = 0; i < byteperpixel; i++) {
		data_double[i].resize(height);
		for (int j = 0; j < height; j++) {
			data_double[i][j].resize(width);
		}
	}
	for (int i = 0; i < byteperpixel; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				data_double[i][j][k] = (double) data[i][j][k];
			}
		}
	}
}

void Imagedata::initialize(int d) {
	for (int i = 0; i < byteperpixel; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				data[i][j][k] = d;
			}
		}
	}
}

void Imagedata::read(unsigned char* buff) {
	int ind = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int b = 0; b < byteperpixel; b++) {
					data[b][i][j] = buff[ind];
					ind++;
				}				
			}
		}
}

void Imagedata::load(string path) {
	// Define file pointer and variables
	FILE* file;	
	int size = height * width * byteperpixel;
	// Read image (filename specified by first argument) into image data matrix
	unsigned char *buff = NULL;
	buff = new unsigned char[size];
	if (!(file = fopen(path.data(), "rb"))) {
		cout << "Cannot open file: " << path.data() << endl;
		exit(1);
	}
	fread(buff, sizeof(unsigned char), size, file);
	fclose(file);
	this->read(buff);
}

void Imagedata::save(string path) {
	//Write image data (filename specified by second argument) from image data matrix
	FILE *file;
	int size = height * width * byteperpixel;
	unsigned char *result = NULL;
	result = new unsigned char[size];
	result = this->write();	

	if (!(file = fopen(path.data(), "wb"))) {
		cout << "cannot open file: " << path << endl;
		exit(1);
	}
	fwrite(result, sizeof(unsigned char), size, file);
	fclose(file);
}

Imagedata Imagedata::get_RGB(int i) {
	Imagedata res(height, width, 1);
	vector<vector<unsigned char>> data = this->data[i];
	res.data[0] = data;
	return res;
}

Imagedata Imagedata::Boundaryextension(int ex) {	
	vector<vector<vector<unsigned char>>> rawdata = data;	
	int height_ex = height + ex * 2;
	int width_ex = width + ex * 2;
	Imagedata res(height_ex, width_ex, byteperpixel);	
	vector<vector<vector<unsigned char>>> data_ex = res.data;

	for (int b = 0; b < byteperpixel; b++) {
		//Center
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				data_ex[b][i + ex][j + ex] = rawdata[b][i][j];
			}
		}			
		//extense row_up
		for (int i = 0; i < ex; i++) {
			vector<unsigned char> data_row = rawdata[b][i];
			for (int j = 0; j < width; j++) {
				data_ex[b][ex - i - 1][j + ex] = data_row[j];
			}
		}
		//extense row_down
		for (int i = 0; i < ex; i++) {
			vector<unsigned char> data_row = rawdata[b][height - i - 1];
			for (int j = 0; j < width; j++) {
				data_ex[b][height_ex - ex + i][j + ex] = data_row[j];
			}
		}
		//extense column_left
		for (int i = 0; i < ex; i++) {
			vector<unsigned char> data_column;
			for (int j = 0; j < height_ex; j++) {
				data_column.push_back(data_ex[b][j][ex + i]);
			}
			for (int j = 0; j < height_ex; j++) {
				data_ex[b][j][ex - i - 1] = data_column[j];
			}
		}
		//extense column_right
		for (int i = 0; i < ex; i++) {
			vector<unsigned char> data_column;
			for (int j = 0; j < height_ex; j++) {
				data_column.push_back(data_ex[b][j][width_ex - ex - i - 1]);
			}
			for (int j = 0; j < height_ex; j++) {
				data_ex[b][j][width_ex - ex + i] = data_column[j];
			}
		}
	}
	res.data = data_ex;
	return res;
}

unsigned char* Imagedata::write() {
	vector<vector<vector<unsigned char>>> tmpdata = data;
	unsigned char *res = NULL;
	res = new unsigned char[height * width * byteperpixel];
	for (int i = 0; i < byteperpixel; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				res[convert(j, k, i)] = data[i][j][k];
			}
		}
	}	
	return res;
}
			
int Imagedata::convert(int h, int w, int p) {
	return p + w * byteperpixel + h * byteperpixel * width;
}

Imagedata Imagedata::Convolution(Kernel k) {	
	Algorithm A;
	vector<vector<double>> kernel = k.get_wholedata();
	int m = kernel.size();
	int n = kernel[0].size();
	int ind = (m - 1) / 2;
		
	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension(ind);	
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	//Convolution
	Imagedata temp2(height + ind * 2, width + ind *2 , byteperpixel);	
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				double sum = 0;
				for (int k = 0; k < m; k++) {
					for (int l = 0; l < n; l++) {
						sum += rawdata[b][i - ind + k][j - ind + l] * kernel[k][l];
					}
				}
				temp2.data[b][i][j] = A.correction(sum);
			}
		}
	}
	
	//crop
	Imagedata res(height, width, byteperpixel);	
	res = temp2.Crop(m);
	return res;
}

Imagedata Imagedata::Crop(int N) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	int ind = (N - 1) / 2;
	Imagedata res(height - ind * 2, width - ind * 2, byteperpixel);

	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height - ind * 2; i++) {
			for (int j = 0; j < width - ind * 2; j++) {
				res.data[b][i][j] = rawdata[b][i + ind][j + ind];
			}
		}
	}
	return res;
}

Imagedata Imagedata::DN_Gaussion_double(int N, double sigma) {
	vector<vector<vector<double>>> rawdata = data_double;
	Imagedata res(height, width, byteperpixel);
	res.set_doubledata();
	int ind = (N - 1) / 2;
	// Generate kernel (Gaussian)
	Kernel k(N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			k.set_data(1 / sqrt(2 * pi) / sigma * exp(-(pow((i - ind), 2) + pow((j - ind), 2)) / 2 / pow(sigma, 2)), i, j);
		}
	}
	res = this->Convolution_double(k.EQ());
	return res;
}

Imagedata Imagedata::Convolution_double(Kernel k) {
	vector<vector<double>> kernel = k.get_wholedata();
	int m = kernel.size();
	int n = kernel[0].size();
	int ind = (m - 1) / 2;

	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension_double(ind);
	vector<vector<vector<double>>> rawdata = temp_ex.data_double;

	//Convolution
	Imagedata temp_ex_Conv(height + ind * 2, width + ind * 2, byteperpixel);
	temp_ex_Conv.set_doubledata();
	for (int i = ind; i < height + ind; i++) {
		for (int j = ind; j < width + ind; j++) {
			for (int k = 0; k < m; k++) {
				for (int l = 0; l < n; l++) {
					temp_ex_Conv.data_double[0][i][j] += rawdata[0][i - ind + k][j - ind + l] * kernel[k][l];
				} 
			}
		}
	}
	//crop
	Imagedata res(height, width, byteperpixel);
	res.set_doubledata();
	res = temp_ex_Conv.Crop_double(m);
	return res;
}

Imagedata Imagedata::Crop_double(int N) {
	vector<vector<vector<double>>> rawdata = data_double;
	int ind = (N - 1) / 2;
	Imagedata res(height - ind * 2, width - ind * 2, byteperpixel);
	res.set_doubledata();

	for (int i = 0; i < height - ind * 2; i++) {
		for (int j = 0; j < width - ind * 2; j++) {
			res.data_double[0][i][j] = rawdata[0][i + ind][j + ind];
		}
	}
	return res;
}

Imagedata Imagedata::Save_double(string path) {
	//Write image data (filename specified by second argument) from image data matrix
	FILE *file;
	int size = height * width * byteperpixel;
	double *result = NULL;
	result = new double[size];
	result = this->write_double();

	if (!(file = fopen(path.data(), "wb"))) {
		cout << "cannot open file: " << path << endl;
		exit(1);
	}
	fwrite(result, sizeof(double), size, file);
	fclose(file);
}

double* Imagedata::write_double() {
	vector<vector<vector<double>>> tmpdata = data_double;
	double *res = NULL;
	res = new double[height * width * byteperpixel];

	for (int i = 0; i < byteperpixel; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				res[convert(j, k, i)] = data_double[i][j][k];
			}
		}
	}
	return res;
}

Imagedata Imagedata::Boundaryextension_double(int ex) {
	vector<vector<vector<double>>> rawdata = data_double;
	int height_ex = height + ex * 2;
	int width_ex = width + ex * 2;
	Imagedata res(height_ex, width_ex, byteperpixel);
	res.set_doubledata();
	vector<vector<vector<double>>> data_ex = res.data_double;


	//Center
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data_ex[0][i + ex][j + ex] = rawdata[0][i][j];
		}
	}
	//extense row_up
	for (int i = 0; i < ex; i++) {
		vector<double> data_row = rawdata[0][i];
		for (int j = 0; j < width; j++) {
			data_ex[0][ex - i - 1][j + ex] = data_row[j];
		}
	}
	//extense row_down
	for (int i = 0; i < ex; i++) {
		vector<double> data_row = rawdata[0][height - i - 1];
		for (int j = 0; j < width; j++) {
			data_ex[0][height_ex - ex + i][j + ex] = data_row[j];
		}
	}
	//extense column_left
	for (int i = 0; i < ex; i++) {
		vector<double> data_column;
		for (int j = 0; j < height_ex; j++) {
			data_column.push_back(data_ex[0][j][ex + i]);
		}
		for (int j = 0; j < height_ex; j++) {
			data_ex[0][j][ex - i - 1] = data_column[j];
		}
	}
	//extense column_
	for (int i = 0; i < ex; i++) {
		vector<double> data_column;
		for (int j = 0; j < height_ex; j++) {
			data_column.push_back(data_ex[0][j][width_ex - ex - i - 1]);
		}
		for (int j = 0; j < height_ex; j++) {
			data_ex[0][j][width_ex - ex + i] = data_column[j];
		}
	}
	res.data_double = data_ex;
	return res;
}

void Imagedata::double2usignedc() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[0][i][j] = (unsigned char)data_double[0][i][j];
		}
	}
}

Imagedata Imagedata::Random_threholding() {
	Algorithm A;
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height,width,byteperpixel);
	vector<vector<vector<unsigned char>>> tempdata = res.data;

	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int rand = A.RangedRandDemo(0, 255, 1);
				if (rawdata[b][i][j] < rand) tempdata[b][i][j] = 0;
				else tempdata[b][i][j] = 255;
			}
		}
	}
	res.data = tempdata;
	return res;
}

Imagedata Imagedata::Dithering(int index) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height, width, byteperpixel);
	vector<vector<vector<unsigned char>>> tempdata = res.data;
	Kernel dummy(1, 1);
	Kernel Dmatric = dummy.Dithering_matric(index);
	vector<vector<double>> threhold = Dmatric.get_wholedata();
	

	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {				
				if (rawdata[b][i][j] <= (int)threhold[i%index][j%index]) {
					tempdata[b][i][j] = 0;
				}
				else if (rawdata[b][i][j] > (int)threhold[i%index][j%index]) {
					tempdata[b][i][j] = 255;
				}
			}
		}
	}
	res.data = tempdata;
	return res;
}

Imagedata Imagedata::Error_diffusion(Kernel k) {
	Algorithm A;
	vector<vector<double>> kernel = k.get_wholedata();
	int m = k.get_height();
	int n = k.get_width();
	int ind = (m - 1) / 2;
	Imagedata res(height + ind * 2, width + ind * 2, byteperpixel);
	vector<vector<vector<unsigned char>>> newdata = res.data;

	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension(ind);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;
	
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = ind; i < height + ind; i++) {
			//odd row
			if ((i-ind) % 2 == 0) {
				for (int j = ind; j < width + ind; j++) {
					newdata[b][i][j] = A.find_closest(rawdata[b][i][j]);
					int error = rawdata[b][i][j] - newdata[b][i][j];
					for (int k = 0; k < m; k++) {
						for (int l = 0; l < n; l++) {
							double tep = rawdata[b][i - ind + k][j - ind + l] + error * kernel[k][l];							
							rawdata[b][i - ind + k][j - ind + l] = A.correction(tep);
						}
					}
				}
			}
			//even row
			else if ((i-ind) % 2 == 1) {
				for (int j = width + ind - 1; j > ind - 1; j--) {
					newdata[b][i][j] = A.find_closest(rawdata[b][i][j]);
					int error = rawdata[b][i][j] - newdata[b][i][j];
					for (int k = 0; k < m; k++) {
						for (int l = 0; l < n; l++) {
							double tep = rawdata[b][i - ind + k][j - ind + l] + error * kernel[k][n - l - 1];
							rawdata[b][i - ind + k][j - ind + l] = A.correction(tep);
						}
					}
				}
			}
		}
	}
	//crop
	res.data = newdata;		
	return res.Crop(m);
}

Imagedata Imagedata::Floyd() {
	Kernel k(3, 3);
	k.set_data(0.4375, 1, 2);
	k.set_data(0.1875, 2, 0);
	k.set_data(0.3125, 2, 1);
	k.set_data(0.0625, 2, 2);	
	return this->Error_diffusion(k);
}

Imagedata Imagedata::JJN() {
	Kernel k(5, 5);
	k.set_data(7.0 / 48, 2, 3);
	k.set_data(5.0 / 48, 2, 4);
	k.set_data(3.0 / 48, 3, 0);
	k.set_data(5.0 / 48, 3, 1);
	k.set_data(7.0 / 48, 3, 2);
	k.set_data(5.0 / 48, 3, 3);
	k.set_data(3.0 / 48, 3, 4);
	k.set_data(1.0 / 48, 4, 0);
	k.set_data(3.0 / 48, 4, 1);
	k.set_data(5.0 / 48, 4, 2);
	k.set_data(3.0 / 48, 4, 3);
	k.set_data(1.0 / 48, 4, 4);
	return this->Error_diffusion(k);
}

Imagedata Imagedata::Stucki() {
	Kernel k(5, 5);
	k.set_data(8.0 / 42, 2, 3);
	k.set_data(4.0 / 42, 2, 4);
	k.set_data(2.0 / 42, 3, 0);
	k.set_data(4.0 / 42, 3, 1);
	k.set_data(8.0 / 42, 3, 2);
	k.set_data(4.0 / 42, 3, 3);
	k.set_data(2.0 / 42, 3, 4);
	k.set_data(1.0 / 42, 4, 0);
	k.set_data(2.0 / 42, 4, 1);
	k.set_data(4.0 / 42, 4, 2);
	k.set_data(2.0 / 42, 4, 3);
	k.set_data(1.0 / 42, 4, 4);
	return this->Error_diffusion(k);
}

Imagedata Imagedata::RGB2CMY() {
	Imagedata res(height, width, byteperpixel);	
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				res.data[b][i][j] = 255 - data[b][i][j];
			}
		}
	}
	return res;
}

Imagedata Imagedata::CMY2RGB() {
	Imagedata res(height, width, byteperpixel);
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				res.data[b][i][j] = 255 - data[b][i][j];
			}
		}
	}
	return res;
}

void Imagedata::Color_merge(Imagedata R_component, Imagedata G_component, Imagedata B_component) {	
	data[0] = R_component.data[0];
	data[1] = G_component.data[0];
	data[2] = B_component.data[0];	
}

Imagedata Imagedata::Color_Floyd() {
	Imagedata raw_CMY = this->RGB2CMY();
	Imagedata raw_C = raw_CMY.get_RGB(0); //get C channel
	Imagedata raw_M = raw_CMY.get_RGB(1); //get M channel
	Imagedata raw_Y = raw_CMY.get_RGB(2); //get Y channel
	Imagedata raw_C_Floyd = raw_C.Floyd();
	Imagedata raw_M_Floyd = raw_M.Floyd();
	Imagedata raw_Y_Floyd = raw_Y.Floyd();
	Imagedata raw_CMY_Floyd(height, width, byteperpixel);
    raw_CMY_Floyd.Color_merge(raw_C_Floyd, raw_M_Floyd, raw_Y_Floyd);
	Imagedata raw_RGB_Floyd = raw_CMY_Floyd.CMY2RGB();
	return raw_RGB_Floyd;
}

Imagedata Imagedata::Color_MBVQ() {
	Algorithm A;
	Kernel k(3, 3);
	k.set_data(0.4375, 1, 2);
	k.set_data(0.1875, 2, 0);
	k.set_data(0.3125, 2, 1);
	k.set_data(0.0625, 2, 2);	

	
	vector<vector<double>> kernel = k.get_wholedata();
	int m = k.get_height();
	int n = k.get_width();
	int ind = (m - 1) / 2;
	Imagedata res(height + ind * 2, width + ind * 2, byteperpixel);

	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension(ind);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	for (int i = ind; i < height + ind; i++) {
		//odd row
		if ((i - ind) % 2 == 0) {
			for (int j = ind; j < width + ind; j++) {
				vector<unsigned char> ori_pixel = temp_ex.get_color_data(i, j);
				string label = A.getNearestVertex(ori_pixel);
				vector<unsigned char> new_pixel = A.string2int_MBVQ(label);
				res.set_color_data(i, j, new_pixel);
				for (int b = 0; b < byteperpixel; b++) {
					int error = ori_pixel[b] - new_pixel[b];
					for (int k = 0; k < m; k++) {
						for (int l = 0; l < n; l++) {
							double tep = temp_ex.data[b][i - ind + k][j - ind + l] + error * kernel[k][l];
							temp_ex.data[b][i - ind + k][j - ind + l] = A.correction(tep);
						}
					}
				}
			}
		}
		//even row
		if ((i - ind) % 2 == 1) {
			for (int j = width + ind - 1; j > ind - 1; j--) {
				vector<unsigned char> ori_pixel = temp_ex.get_color_data(i, j);
				string label = A.getNearestVertex(ori_pixel);
				vector<unsigned char> new_pixel = A.string2int_MBVQ(label);
				res.set_color_data(i, j, new_pixel);
				for (int b = 0; b < byteperpixel; b++) {
					int error = ori_pixel[b] - new_pixel[b];
					for (int k = 0; k < m; k++) {
						for (int l = 0; l < n; l++) {
							double tep = temp_ex.data[b][i - ind + k][j - ind + l] + error * kernel[k][l];
							temp_ex.data[b][i - ind + k][j - ind + l] = A.correction(tep);
						}
					}
				}
			}
		}
	}

	//crop	
	return res.Crop(m);
}

void Imagedata::set_color_data(int i, int j, vector<unsigned char> c) {
	for (int b = 0; b < byteperpixel; b++) {
		data[b][i][j] = c[b];
	}
}

vector<unsigned char> Imagedata::get_color_data(int i, int j) {
	vector<unsigned char> res;
	for (int b = 0; b < byteperpixel; b++) {
		res.push_back(data[b][i][j]);
	}
	return res;
}

Imagedata Imagedata::RGB2GRAY() {
	Imagedata res(height, width, 1);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data[0][i][j] = data[RED][i][j] * 0.299 + data[GREEN][i][j] * 0.587 + data[BLUE][i][j] * 0.114;
		}
	}
	return res;
}

Imagedata Imagedata::Sobel_X() {
	Kernel k(3, 3);
	k.set_data(1, 0, 0);
	k.set_data(-1, 0, 2);
	k.set_data(2, 1, 0);
	k.set_data(-2, 1, 2);
	k.set_data(1, 2, 0);
	k.set_data(-1, 2, 2);
	return this->Convolution(k);
}

Imagedata Imagedata::Sobel_Y() {
	Kernel k(3, 3);
	k.set_data(1, 0, 0);
	k.set_data(2, 0, 1);
	k.set_data(1, 0, 2);
	k.set_data(-1, 2, 0);
	k.set_data(-2, 2, 1);
	k.set_data(-1, 2, 2);
	return this->Convolution(k);
}

Imagedata Imagedata::Tune(int threshold) {
	int thres = height * width * threshold / 100;
	Imagedata res(height, width, byteperpixel);
	map<unsigned char, int> m;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m[data[0][i][j]]++;
		}
	}
	int sum = 0;
	int ind = 0;
	for (int i = 0; i < m.size(); i++) {
		sum += m[i];
		if (sum > thres) {
			ind = i;
			break;
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] >= ind) {
				res.data[0][i][j] = 0;
			}
			else {
				res.data[0][i][j] = 255;
			}
		}
	}
	return res;
}

Imagedata Imagedata::Sobel_merge(Imagedata Sobel_Y) {
	Imagedata res(height, width, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data[0][i][j] = sqrt(pow(Sobel_Y.data[0][i][j], 2) + pow(data[0][i][j], 2));
		}
	}
	return res;
}
