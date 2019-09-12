// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.1.19

#define R 0
#define G 1
#define B 2
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
				data_double[i][j][k] = (double) data[i][j][k];
			}
		}
	}
}

void Imagedata::set_data(int d) {
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
		//extense column_
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

Imagedata Imagedata::Raw2RGB_BL() {
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height - 2, width - 2, 3);
	vector<vector<vector<unsigned char>>> tmpdata = res.data;
	for (int i = 0; i < height-2; i++) {
		for (int j = 0; j < width-2; j++) {
			// even row and even column G 00
			if (i % 2 == 0 && j % 2 == 0) {
				tmpdata[R][i][j] = (rawdata[0][i + 1][j] + rawdata[0][i + 1][j + 2]) / 2; //R
				tmpdata[G][i][j] = rawdata[0][i + 1][j + 1]; //G
				tmpdata[B][i][j] = (rawdata[0][i][j + 1] + rawdata[0][i + 2][j + 1]) / 2; //B
			}
			// odd row and odd column G 11
			else if (i % 2 == 1 && j % 2 == 1) {
				tmpdata[R][i][j] = (rawdata[0][i][j + 1] + rawdata[0][i + 2][j + 1]) / 2; //R
				tmpdata[G][i][j] = rawdata[0][i + 1][j + 1]; //G
				tmpdata[B][i][j] = (rawdata[0][i + 1][j] + rawdata[0][i + 1][j + 2]) / 2; //B
			}
			//odd row and even column B 10
			else if (i % 2 == 1 && j % 2 == 0) {
				tmpdata[B][i][j] = rawdata[0][i + 1][j + 1]; //B
				tmpdata[G][i][j] = (rawdata[0][i][j + 1] + rawdata[0][i + 2][j + 1] + rawdata[0][i + 1][j] + rawdata[0][i + 1][j + 2]) / 4;//G
				tmpdata[R][i][j] = (rawdata[0][i + 2][j] + rawdata[0][i][j] + rawdata[0][i][j + 2] + rawdata[0][i + 2][j + 2]) / 4; //R
			}
			//even row and odd column R 01
			else if (i % 2 == 0 && j % 2 == 1) {
				tmpdata[B][i][j] = (rawdata[0][i][j] + rawdata[0][i + 2][j] + rawdata[0][i][j +2] + rawdata[0][i + 2][j + 2]) / 4; //B
				tmpdata[G][i][j] = (rawdata[0][i][j + 1] + rawdata[0][i + 2][j + 1] + rawdata[0][i + 1][j] + rawdata[0][i + 1][j + 2]) / 4; //G
				tmpdata[R][i][j] = rawdata[0][i + 1][j + 1]; //R
			}
		}
	}
	res.data = tmpdata;
	return res;
}

Imagedata Imagedata::Raw2RGB_MHC(Imagedata Imagedata_BL) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height - 4, width - 4, 3);	
	vector<vector<vector<unsigned char>>> tmpdata = Imagedata_BL.data;
	for (int i = 2; i < height - 2; i++) {
		for (int j = 2; j < width - 2; j++) {
			// even row and odd column R 01
			if (i % 2 == 0 && j % 2 == 1) {
				tmpdata[G][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 2][j] + rawdata[0][i - 2][j] + rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 4) / 2;//G at R locations
				tmpdata[B][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 2][j] + rawdata[0][i - 2][j] + rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 4) * 3 / 4; //B at red in R row, R column 
			}
			// even row and even column G 00
			if (i % 2 == 0 && j % 2 == 0) {
				tmpdata[R][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 1][j + 1] + rawdata[0][i + 1][j - 1] + rawdata[0][i - 1][j + 1] + rawdata[0][i - 1][j - 1] + rawdata[0][i + 2][j] + rawdata[0][i - 2][j]) / 5 + (rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 10) * 5 / 8;// R at green in B row, R column			
				tmpdata[B][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 1][j + 1] + rawdata[0][i + 1][j - 1] + rawdata[0][i - 1][j + 1] + rawdata[0][i - 1][j - 1] + rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 5 + (rawdata[0][i + 2][j] + rawdata[0][i - 2][j]) / 10) * 5 / 8;//B at green in B row, R column
			}
			// odd row and odd column G 11
			else if (i % 2 == 1 && j % 2 == 1) {
				tmpdata[R][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 1][j + 1] + rawdata[0][i + 1][j - 1] + rawdata[0][i - 1][j + 1] + rawdata[0][i - 1][j - 1] + rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 5 + (rawdata[0][i + 2][j] + rawdata[0][i - 2][j]) / 10) * 5 / 8; //R at green in R row, B column				
				tmpdata[B][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 1][j + 1] + rawdata[0][i + 1][j - 1] + rawdata[0][i - 1][j + 1] + rawdata[0][i - 1][j - 1] + rawdata[0][i + 2][j] + rawdata[0][i - 2][j]) / 5 + (rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 10) * 5 / 8; //B at green in R row, B column
			}						
			// odd row and even column B 10
			else if (i % 2 == 1 && j % 2 == 0) {
				tmpdata[R][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 2][j] + rawdata[0][i - 2][j] + rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 4) * 3 / 4; //R at blue in B row, B column
				tmpdata[G][i - 2][j - 2] += (rawdata[0][i][j] - (rawdata[0][i + 2][j] + rawdata[0][i - 2][j] + rawdata[0][i][j + 2] + rawdata[0][i][j - 2]) / 4) / 2; //G at B locations				
			}
		}
	}
	res.data = tmpdata;
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

void Imagedata::Histogram_create(const char* path) {
	vector<vector<vector<unsigned char>>> rawdata = data;	
	map<unsigned char, int> m;	
	int size = 300; //size of the whole picture, height = 300, width = 300,	
	Imagedata Hist(size, size, 1);
	int Hist_size = 256;// size of the histgram 256 * 256
	Hist.set_data(255);
	vector<vector<vector<unsigned char>>> Hist_data = Hist.data;
	// x-axis
	for (int i = 22; i < Hist_size + 22; i++) {
		Hist_data[0][Hist_size + 21][i] = 0;
	}
	// y-axis
	for (int i = 22; i < Hist_size + 22; i++) {
		Hist_data[0][i][21] = 0;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m[rawdata[0][i][j]]++;
		}
	}	
	int max = 0;
	int max_ind;
	for (int i = 0; i < 256; i++) {		
		if (m[i] > max) {
			max = m[i];			
		}
	}
	for (int i = 0; i < 256; i++) {
		m[i] = m[i] * 256 / max ;
	}
	for (int i = 0; i < 256; i++) {
		for (int j = m[i] - 1; j > 0; j--) {
			Hist_data[0][255+22-j][i + 22] = 0;
		}
	}
	Hist.data = Hist_data;
	Hist.save(path);
}

void Imagedata::Histogram_cummulative(const char* path) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	map<unsigned char, int> m;
	int size = 300; //size of the whole picture, height = 300, width = 300,	
	Imagedata Hist(size, size, 1);
	int Hist_size = 256;// size of the histgram 256 * 256
	Hist.set_data(255);
	vector<vector<vector<unsigned char>>> Hist_data = Hist.data;

	// x-axis
	for (int i = 22; i < Hist_size + 22; i++) {
		Hist_data[0][Hist_size + 21][i] = 0;
	}
	// y-axis
	for (int i = 22; i < Hist_size + 22; i++) {
		Hist_data[0][i][21] = 0;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m[rawdata[0][i][j]]++;
		}
	}
	int max = 0;
	int max_ind;
	for (int i = 0; i < 256; i++) {
		if (m[i] > max) {
			max = m[i];
		}
	}
	vector<int> n;
	int temp = 0;
	for (int i = 0; i < 256; i++) {
		temp += m[i];
		n.push_back(temp);
	}
	for (int i = 0; i < 256; i++) {
		n[i] = n[i] * 256 / 160000;
	}
	for (int i = 0; i < 256; i++) {
		for (int j = n[i] - 1; j > 0; j--) {
			Hist_data[0][255 + 22 - j][i + 22] = 0;
		}
	}
	Hist.data = Hist_data;
	Hist.save(path);
}

void Imagedata::Transfer_function(const char* path) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	map<unsigned char, int> m;
	int size = 300; //size of the whole picture, height = 300, width = 300,	
	Imagedata Hist(size, size, 1);
	int Hist_size = 256;// size of the histgram 256 * 256
	Hist.set_data(255);
	vector<vector<vector<unsigned char>>> Hist_data = Hist.data;
	// x-axis
	for (int i = 22; i < Hist_size + 22; i++) {
		Hist_data[0][Hist_size + 21][i] = 0;
	}
	// y-axis
	for (int i = 22; i < Hist_size + 22; i++) {
		Hist_data[0][i][21] = 0;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m[rawdata[0][i][j]]++;
		}
	}
	int max = 0;
	int max_ind;
	for (int i = 0; i < 256; i++) {
		if (m[i] > max) {
			max = m[i];
		}
	}
	vector<int> n;
	int temp = 0;
	for (int i = 0; i < 256; i++) {
		temp += m[i];
		n.push_back(temp);
	}
	for (int i = 0; i < 256; i++) {
		n[i] = n[i] * 256 / 160000;
	}
	for (int i = 0; i < 256; i++) {
		int j = n[i] - 1;
		Hist_data[0][255 + 22 - j][i + 22] = 0;		
	}
	Hist.data = Hist_data;
	Hist.save(path);
}

Imagedata Imagedata::Hist_EQ_TR() {
	vector<vector<vector<unsigned char>>> rawdata = data;	
	Imagedata res(height, width, byteperpixel);	
	map<unsigned char, int> m;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m[rawdata[0][i][j]]++;
		}
	}
	vector<int> cdf(256, 0);	
	// Generate cdf
	cdf[0] = m[0];
	for (int i = 1; i < 256; i++) {
		cdf[i] = cdf[i-1] + m[i];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rawdata[0][i][j] = 255 * cdf[rawdata[0][i][j]] / (height * width);
		}
	}
	res.data = rawdata;
	return res;
}

Imagedata Imagedata::Hist_EQ_BF() {
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height, width, byteperpixel);	
	map<unsigned char,queue<pair<int,int>>> m;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m[rawdata[0][i][j]].push(make_pair(i, j));
		}
	}
	queue<pair<int, int>> stock;
	for (int i = 0; i < 256;) {
		if (m[i].empty())
		{
			i++;
			continue;
		}
		pair<int, int> temp = m[i].front();
		stock.push(temp);
		m[i].pop();			
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 625; j++) {
			pair<int, int> temp = stock.front();
			rawdata[0][temp.first][temp.second] = i;
			stock.pop();
		}
	}
	res.data = rawdata;
	return res;
}

Imagedata Imagedata::Convolution(Kernel k) {	
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
				temp2.data[b][i][j] = sum;
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

Imagedata Imagedata::DN_Uniform(int N) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height, width, byteperpixel);

	Kernel k(N,N);	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {			
			k.set_data(1.0 / N / N,i,j);
		}
	}
	res = this->Convolution(k);
	return res;
}

Imagedata Imagedata::DN_Gaussion(int N,double sigma) {
	vector<vector<vector<unsigned char>>> rawdata = data;
	Imagedata res(height, width, byteperpixel);

	int ind = (N - 1) / 2;
	// Generate kernel (Gaussian)
	Kernel k(N,N);	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			k.set_data(1 / sqrt(2 * pi) / sigma * exp(-(pow((i - ind), 2) + pow((j - ind), 2)) / 2 / pow(sigma, 2)),i,j);
		}
	}		
	res = this->Convolution(k.EQ());
	return res;
}

Imagedata Imagedata::DN_Bilateral(int N, double sigmac, double sigmas) {		
	int ind = (N - 1) / 2;
	// Generate kernel (Gaussian)
	Kernel kernel(N,N);	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			kernel.set_data(exp(-(pow((i - ind), 2) + pow((j - ind), 2)) / 2 / pow(sigmac, 2)), i, j);
		}
	}
	
	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension(ind);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	//Convolution
	Imagedata temp2(height + ind * 2, width + ind * 2, byteperpixel);
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				Kernel k_real = kernel;
				double temp = 0;
				for (int k = 0; k < N; k++) {
					for (int l = 0; l < N; l++) {
						k_real.set_data(kernel.get_data(k, l) * exp(-pow((rawdata[b][i][j] - rawdata[b][i - ind + k][j - ind + l]), 2) / 2 / pow(sigmas, 2)), k, l);
						temp += rawdata[b][i - ind + k][j - ind + l] * k_real.get_data(k, l);
					}
				}
				double s = k_real.sum();
				temp2.data[b][i][j] = min(temp / s, 255.0);
			}
		}
	}
	
	//crop
	Imagedata res(height, width, byteperpixel);
	res = temp2.Crop(N);
	return res;
}

Imagedata Imagedata::DN_Nonlocalmean(int N_neighbor, int N_search, double h, double sigma) {
	int ind_neighbor = (N_neighbor - 1) / 2;
	int ind_search = (N_search - 1) / 2;
	int ind = ind_neighbor + ind_search;

	//Boundaryextension
	Imagedata temp = *this;
	Imagedata temp_ex = temp.Boundaryextension(ind);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	//Convolution
	Imagedata temp2(height + ind * 2, width + ind * 2, byteperpixel);
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				Kernel kernel_neighbor(N_neighbor, N_neighbor);
				double temp_neighbor = 0;
				for (int k = 0; k < N_neighbor; k++) {
					for (int l = 0; l < N_neighbor; l++) {
						Kernel kernel_search(N_search, N_search);
						double temp_search = 0;
						for (int m = 0; m < N_search; m++) {
							for (int n = 0; n < N_search; n++) {
								double p = 1 / sqrt(2 * pi) / sigma * exp(-(pow((m - ind_search), 2) + pow((n - ind_search), 2)) / 2 / pow(sigma, 2));
								kernel_search.set_data(pow(rawdata[b][i - ind + k + m][j - ind + l + n] - rawdata[b][i - ind_search + m][j - ind_search + n], 2) * p, m, n);
							}
						}
						kernel_neighbor.set_data(exp(-kernel_search.sum() / pow(h, 2)), k, l);
						temp_neighbor += rawdata[b][i - ind_neighbor + k][j - ind_neighbor + l] * kernel_neighbor.get_data(k, l);
					}
				}
				double s = kernel_neighbor.sum();
				temp2.data[b][i][j] = min(temp_neighbor / s, 255.0);
			}
		}
	}
	//crop
	Imagedata res(height, width, byteperpixel);
	res = temp2.Crop(N_neighbor + N_search);
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
						tmp.push_back(rawdata[0][i - ind + k][j - ind + l]);
					}
				}
				sort(tmp.begin(), tmp.end());
				temp2.data[0][i][j] = tmp[(tmp.size() - 1) / 2];
			}
		}
	}
	//crop
	Imagedata res(height, width, byteperpixel);
	res = temp2.Crop(N);
	return res;
}

double Imagedata::PSNR(string path) {	
	FILE *file;
	// Read image (filename specified by first argument) into image data matrix
	unsigned char *buff = NULL;
	buff = new unsigned char[height*width*byteperpixel];

	if (!(file = fopen(path.data(), "rb"))) {
		cout << "Cannot open file: " << path.data() << endl;
		exit(1);
	}
	fread(buff, sizeof(unsigned char), height*width*byteperpixel, file);
	fclose(file);

	Imagedata raw_noise_free(height, width, byteperpixel);
	raw_noise_free.read(buff);

	double MSE = 0;
	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				MSE += pow(this->data[b][i][j] - raw_noise_free.data[b][i][j], 2) / (height * width);
			}
		}
	}
	double PSNR = 10 * log10(255 * 255 / MSE);
	return PSNR;
}

void Imagedata::PSNR_save(string path,double PSNR) {
	string path_str = path.substr(0, path.size() - 3);
	ofstream fout(path_str + "txt");
	fout << to_string(PSNR) << endl;

	fout.close();
}

Imagedata Imagedata::Anscombe_forward() {	
	this->set_doubledata();
	Imagedata res(height, width, byteperpixel);
	res.set_doubledata();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data_double[0][i][j] = sqrt(data_double[0][i][j] + 0.375) * 2;
		}
	}
	return res;
}

Imagedata Imagedata::Anscombe_reverse_biased() {	
	Imagedata res(height, width, byteperpixel);
	res.set_doubledata();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data_double[0][i][j] = pow(data_double[0][i][j] / 2, 2) - 0.375;
		}
	}
	return res;
}

Imagedata Imagedata::Anscombe_reverse_unbiased() {
	Imagedata res(height, width, byteperpixel);
	res.set_doubledata();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data_double[0][i][j] = pow(data_double[0][i][j] / 2, 2) - 0.125;
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