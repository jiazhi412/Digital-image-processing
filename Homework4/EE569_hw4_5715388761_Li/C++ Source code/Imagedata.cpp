// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15
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
				data_double[i][j][k] = (double)data[i][j][k];
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

void Imagedata::pure(unsigned char color) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[0][i][j] = color;
		}
	}
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

Imagedata Imagedata::Binary(int threshold) {
	Imagedata res(height, width, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] <= threshold) {
				res.data[0][i][j] = 0;
			}
			else
			{
				res.data[0][i][j] = 255;
			}
		}
	}
	return res;
}

Imagedata Imagedata::DN_Median(int N) {
	int ind = (N - 1) / 2;

	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension(ind);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	Imagedata temp2(height + ind * 2, width + ind * 2, byteperpixel);
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				vector<unsigned char> tmp;
				for (int k = 0; k < N; k++) {
					for (int l = 0; l < N; l++) {
						tmp.push_back(rawdata[b][i - ind + k][j - ind + l]);
					}
				}
				sort(tmp.begin(), tmp.end());
				temp2.data[b][i][j] = tmp[(tmp.size() - 1) / 2];
			}
		}
	}
	//crop
	Imagedata res(height, width, byteperpixel);
	res = temp2.Crop(N);
	return res;
}

void Imagedata::Color_merge(Imagedata R_component, Imagedata G_component, Imagedata B_component) {
	data[0] = R_component.data[0];
	data[1] = G_component.data[0];
	data[2] = B_component.data[0];
}

Imagedata Imagedata::Binarize() {
	Imagedata res(height, width, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] == 255) {
				res.data[0][i][j] = 1;
			}
		}
	}
	return res;
}

Imagedata Imagedata::RBinarize() {
	Imagedata res(height, width, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] == 1) {
				res.data[0][i][j] = 255;
			}
		}
	}
	return res;
}

Imagedata Imagedata::label_pixel(vector<pair<int, int>> v) {
	Imagedata res(height, width, byteperpixel);
	for (int i = 0; i < v.size(); i++) {
		res.data[0][v[i].first][v[i].second] = 255;
	}
	return res;
}

Imagedata Imagedata::Sub_Mean() {
	Imagedata res(height, width, byteperpixel);
	res.set_doubledata();
	this->set_doubledata();
	int sum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			sum += data[0][i][j];
		}
	}
	double mean = (double)sum / height / width;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data_double[0][i][j] = data_double[0][i][j] - mean;
		}
	}
	return res;
}

vector<Imagedata> Imagedata::Feature_Extraction() {


	int Level[] = { 1, 4, 6, 4, 1 };
	int Edge[] = { -1,-2,0,2,1 };
	int Spot[] = { -1,0,2,0,-1 };
	int Wave[] = { -1,2,0,-2,1 };
	int Ripple[] = { 1,-4,6,-4,1 };

	Kernel L(1, 5);
	Kernel E(1, 5);
	Kernel S(1, 5);
	Kernel W(1, 5);
	Kernel R(1, 5);

	L.generate(Level);
	E.generate(Edge);
	S.generate(Spot);
	W.generate(Wave);
	R.generate(Ripple);



	vector<Kernel> Laws_filter;
	Laws_filter.push_back(L.Transpose().Multiplication(L));
	Laws_filter.push_back(L.Transpose().Multiplication(E));
	Laws_filter.push_back(L.Transpose().Multiplication(S));
	Laws_filter.push_back(L.Transpose().Multiplication(W));
	Laws_filter.push_back(L.Transpose().Multiplication(R));

	Laws_filter.push_back(E.Transpose().Multiplication(L));
	Laws_filter.push_back(E.Transpose().Multiplication(E));
	Laws_filter.push_back(E.Transpose().Multiplication(S));
	Laws_filter.push_back(E.Transpose().Multiplication(W));
	Laws_filter.push_back(E.Transpose().Multiplication(R));

	Laws_filter.push_back(S.Transpose().Multiplication(L));
	Laws_filter.push_back(S.Transpose().Multiplication(E));
	Laws_filter.push_back(S.Transpose().Multiplication(S));
	Laws_filter.push_back(S.Transpose().Multiplication(W));
	Laws_filter.push_back(S.Transpose().Multiplication(R));

	Laws_filter.push_back(W.Transpose().Multiplication(L));
	Laws_filter.push_back(W.Transpose().Multiplication(E));
	Laws_filter.push_back(W.Transpose().Multiplication(S));
	Laws_filter.push_back(W.Transpose().Multiplication(W));
	Laws_filter.push_back(W.Transpose().Multiplication(R));

	Laws_filter.push_back(R.Transpose().Multiplication(L));
	Laws_filter.push_back(R.Transpose().Multiplication(E));
	Laws_filter.push_back(R.Transpose().Multiplication(S));
	Laws_filter.push_back(R.Transpose().Multiplication(W));
	Laws_filter.push_back(R.Transpose().Multiplication(R));

	vector<Imagedata> res;

	//for (int i = 0; i < 3; i++) {
	for (int i = 0; i < Laws_filter.size(); i++) {
		res.push_back(this->Convolution_double(Laws_filter[i]));
	}
	return res;
}

vector<Imagedata> Imagedata::Feature_Extraction_filter_normalized() {


	int Level[] = { 1, 4, 6, 4, 1 };
	int Edge[] = { -1,-2,0,2,1 };
	int Spot[] = { -1,0,2,0,-1 };
	int Wave[] = { -1,2,0,-2,1 };
	int Ripple[] = { 1,-4,6,-4,1 };

	Kernel L(1, 5);
	Kernel E(1, 5);
	Kernel S(1, 5);
	Kernel W(1, 5);
	Kernel R(1, 5);

	L.generate(Level);
	E.generate(Edge);
	S.generate(Spot);
	W.generate(Wave);
	R.generate(Ripple);



	vector<Kernel> Laws_filter;
	Laws_filter.push_back(L.Transpose().Multiplication(L));
	Laws_filter.push_back(L.Transpose().Multiplication(E));
	Laws_filter.push_back(L.Transpose().Multiplication(S));
	Laws_filter.push_back(L.Transpose().Multiplication(W));
	Laws_filter.push_back(L.Transpose().Multiplication(R));

	Laws_filter.push_back(E.Transpose().Multiplication(L));
	Laws_filter.push_back(E.Transpose().Multiplication(E));
	Laws_filter.push_back(E.Transpose().Multiplication(S));
	Laws_filter.push_back(E.Transpose().Multiplication(W));
	Laws_filter.push_back(E.Transpose().Multiplication(R));

	Laws_filter.push_back(S.Transpose().Multiplication(L));
	Laws_filter.push_back(S.Transpose().Multiplication(E));
	Laws_filter.push_back(S.Transpose().Multiplication(S));
	Laws_filter.push_back(S.Transpose().Multiplication(W));
	Laws_filter.push_back(S.Transpose().Multiplication(R));

	Laws_filter.push_back(W.Transpose().Multiplication(L));
	Laws_filter.push_back(W.Transpose().Multiplication(E));
	Laws_filter.push_back(W.Transpose().Multiplication(S));
	Laws_filter.push_back(W.Transpose().Multiplication(W));
	Laws_filter.push_back(W.Transpose().Multiplication(R));

	Laws_filter.push_back(R.Transpose().Multiplication(L));
	Laws_filter.push_back(R.Transpose().Multiplication(E));
	Laws_filter.push_back(R.Transpose().Multiplication(S));
	Laws_filter.push_back(R.Transpose().Multiplication(W));
	Laws_filter.push_back(R.Transpose().Multiplication(R));

	vector<Imagedata> res;

	//for (int i = 0; i < 3; i++) {
	for (int i = 0; i < Laws_filter.size(); i++) {
		Imagedata temp = this->Convolution_double(Laws_filter[i]);
		Imagedata image_normalized(height, width, byteperpixel);
		int sum_filter = Laws_filter[i].sum();
		for (int k = 0; k < height; k++) {
			for (int l = 0; l < width; l++) {
				image_normalized.data[0][k][l] = temp.data_double[0][k][l] / sum_filter;
			}
		}
		res.push_back(image_normalized);
	}
	return res;
}

double Imagedata::Average_energy() {
	double Energy = 0;
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Energy += data_double[b][i][j] * data_double[b][i][j];
			}
		}
	}
	double average_energy = Energy / byteperpixel / height / width;
	return average_energy;
}

vector<double> Imagedata::Feature_vector() {
	Imagedata raw_Sub_mean = this->Sub_Mean();
	vector<Imagedata> raw_filtered = raw_Sub_mean.Feature_Extraction();
	vector<double> Feature_vector;
	for (int i = 0; i < raw_filtered.size(); i++) {
		Feature_vector.push_back(raw_filtered[i].Average_energy());
	}
	return Feature_vector;
}

vector<vector<vector<double>>> Imagedata::get_data_double() {
	//vector<vector<vector<double>>> res(byteperpixel,vector<vector<double>>(height,vector<double>(width,0)));	
	return data_double;
}

int Imagedata::get_height() {
	return height;
}

int Imagedata::get_width() {
	return width;
}

int Imagedata::get_byteperpixel() {
	return byteperpixel;
}

void Imagedata::segmentation(vector<vector<int>> label) {
	for (int i = 0; i < label.size(); i++) {
		for (int j = 0; j < label[i].size(); j++) {
			int c = label[i][j];
			data[0][c / 510][c % 510] = i * 42;
		}
	}
}

void Imagedata::Emphasize(pair<int, int> centre, unsigned char s) {
	queue<pair<int, int>> q;
	Imagedata label(height, width, byteperpixel);
	q.push(centre);
	label.data[0][centre.first][centre.second] = 255;
	int tag = data[0][centre.first][centre.second];
	data[0][centre.first][centre.second] = s;
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		// select some points	
		if (data[0][p.first - 1][p.second] == tag && label.data[0][p.first - 1][p.second] == 0 && p.first > 1) {
			pair<int, int> temp(p.first - 1, p.second);
			q.push(temp);
			label.data[0][p.first - 1][p.second] = 255;
			data[0][p.first][p.second] = s;
		}
		if (data[0][p.first + 1][p.second] == tag && label.data[0][p.first + 1][p.second] == 0 && p.first < height - 2) {
			pair<int, int> temp(p.first + 1, p.second);
			q.push(temp);
			data[0][p.first][p.second] = s;
			label.data[0][p.first + 1][p.second] = 255;
		}
		if (data[0][p.first][p.second - 1] == tag && label.data[0][p.first][p.second - 1] == 0 && p.second > 1) {
			pair<int, int> temp(p.first, p.second - 1);
			q.push(temp);
			data[0][p.first][p.second] = s;
			label.data[0][p.first][p.second - 1] = 255;
		}
		if (data[0][p.first][p.second + 1] == tag && label.data[0][p.first][p.second + 1] == 0 && p.second < width - 2) {
			pair<int, int> temp(p.first, p.second + 1);
			q.push(temp);
			data[0][p.first][p.second] = s;
			label.data[0][p.first][p.second + 1] = 255;
		}
	}
	//label.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_label_test.raw");	
}