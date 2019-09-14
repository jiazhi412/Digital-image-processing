// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

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
#include "Patterntree.h"


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

Imagedata Imagedata::Shrinking() {
	Algorithm A;
	// Condition Mark Patterns
	vector<Kernel> CONDI_PATTERNS_S = A.Condi_Shrink();

	//// print for test
	//for (int i = 0; i < CONDI_PATTERNS_S.size(); i++) {
	//	CONDI_PATTERNS_S[i].Print();
	//}

	// Condition Patterns tree
	Tree PATTERNS_TREE_S = Tree(A.PATTERNS_TREE(CONDI_PATTERNS_S));
	// UCondition Mark Patterns
	vector<Kernel> UCONDI_PATTERNS_S = A.UCondi_ST();
	// Condition Patterns tree
	Tree UCONDI_PATTERNS_S_TREE = Tree(A.PATTERNS_TREE(UCONDI_PATTERNS_S));

	//// print for test
	//for (int i = 0; i < CONDI_PATTERNS_S.size(); i++) {
	//	UCONDI_PATTERNS_S[i].Print();
	//}

	// Convert in range[0,1]
	Imagedata b = this->Binarize();
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] == 255) {
				b.data[0][i][j] = 1;
			}
		}
	}

	bool flag = true;
	int trials = 0;
	while (flag) {
		//Boundaryextension	
		Imagedata temp_ex = b.Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

		Imagedata M(height, width, byteperpixel);
		// compare
		int ind = 1;
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				if (rawdata[0][i][j] == 0) {
					continue;
				}
				queue<int> q;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						q.push(rawdata[0][i - ind + k][j - ind + l]);
					}
				}
				if (PATTERNS_TREE_S.compare(q)) {
					M.data[0][i - ind][j - ind] = 1;
				}
			}
		}

		//Boundaryextension	
		Imagedata temp_ex2 = M.Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata2 = temp_ex2.data;

		Imagedata P(height, width, byteperpixel);
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				if (rawdata2[0][i][j] == 0) {
					continue;
				}
				queue<int> q;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						q.push(rawdata2[0][i - ind + k][j - ind + l]);
					}
				}
				if (UCONDI_PATTERNS_S_TREE.compare(q)) {
					P.data[0][i - ind][j - ind] = 1;
				}
			}
		}

		// M inverse
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (M.data[0][i][j] == 1) {
					M.data[0][i][j] = 0;
				}
				else M.data[0][i][j] = 1;
			}
		}
		// unchange count 
		int count = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (b.data[0][i][j] == b.data[0][i][j] & (M.data[0][i][j] | P.data[0][i][j])) {
					count++;
				}
				b.data[0][i][j] = b.data[0][i][j] & (M.data[0][i][j] | P.data[0][i][j]);				
			}
		}
		if (count == height * width) {
			flag = false;
		}
		trials++;
		//if (trials == 70) {
		//	/*for (int i = 0; i < height; i++) {
		//		for (int j = 0; j < width; j++) {
		//			if (M.data[0][i][j] == 1) {
		//				M.data[0][i][j] = 255;
		//			}
		//		}
		//	}
		//	return M;*/
		//	break;
		//}
	}
			
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (b.data[0][i][j] == 1) {
				b.data[0][i][j] = 255;
			}			
		}
	}
	return b;	
}

Imagedata Imagedata::Thinning() {
	Algorithm A;
	// Condition Mark Patterns
	vector<Kernel> CONDI_PATTERNS_T = A.Condi_Thin();
	// Condition Patterns tree
	Tree CONDI_PATTERNS_T_TREE = Tree(A.PATTERNS_TREE(CONDI_PATTERNS_T));
	// UCondition Mark Patterns
	vector<Kernel> UCONDI_PATTERNS_T = A.UCondi_ST();
	// Condition Patterns tree
	Tree UCONDI_PATTERNS_T_TREE = Tree(A.PATTERNS_TREE(UCONDI_PATTERNS_T));

//	// print for test
//for (int i = 0; i < CONDI_PATTERNS_T.size(); i++) {
//	CONDI_PATTERNS_T[i].Print();
//}

	// Convert in range[0,1]
	Imagedata b(height, width, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] == 255) {
				b.data[0][i][j] = 1;
			}
		}
	}

	bool flag = true;
	int trials = 0;
	while (flag) {
		//Boundaryextension	
		Imagedata temp_ex = b.Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

		Imagedata M(height, width, byteperpixel);
		// compare
		int ind = 1;
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				if (rawdata[0][i][j] == 0) {
					continue;
				}
				queue<int> q;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						q.push(rawdata[0][i - ind + k][j - ind + l]);
					}
				}
				if (CONDI_PATTERNS_T_TREE.compare(q)) {
					M.data[0][i - ind][j - ind] = 1;
				}
			}
		}

		//Boundaryextension	
		Imagedata temp_ex2 = M.Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata2 = temp_ex2.data;

		Imagedata P(height, width, byteperpixel);
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				if (rawdata2[0][i][j] == 0) {
					continue;
				}
				queue<int> q;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						q.push(rawdata2[0][i - ind + k][j - ind + l]);
					}
				}
				if (UCONDI_PATTERNS_T_TREE.compare(q)) {
					P.data[0][i - ind][j - ind] = 1;
				}
			}
		}

		// M inverse
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (M.data[0][i][j] == 1) {
					M.data[0][i][j] = 0;
				}
				else M.data[0][i][j] = 1;
			}
		}
		// unchange count 
		int count = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (b.data[0][i][j] == b.data[0][i][j] & (M.data[0][i][j] | P.data[0][i][j])) {
					count++;
				}
				b.data[0][i][j] = b.data[0][i][j] & (M.data[0][i][j] | P.data[0][i][j]);
			}
		}
		if (count == height * width) {
			flag = false;
		}
		trials++;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (b.data[0][i][j] == 1) {
				b.data[0][i][j] = 255;
			}
		}
	}
	return b;
}

Imagedata Imagedata::Skeleton() {
	Algorithm A;
	// Condition Mark Patterns
	vector<Kernel> CONDI_PATTERNS_K = A.Condi_Skeleton();
	// Condition Patterns tree
	Tree CONDI_PATTERNS_K_TREE = Tree(A.PATTERNS_TREE(CONDI_PATTERNS_K));
	// UCondition Mark Patterns
	vector<Kernel> UCONDI_PATTERNS_K = A.UCondi_K();
	// Condition Patterns tree
	Tree UCONDI_PATTERNS_K_TREE = Tree(A.PATTERNS_TREE(UCONDI_PATTERNS_K));

	// print for test
//for (int i = 0; i < CONDI_PATTERNS_K.size(); i++) {
//	CONDI_PATTERNS_K[i].Print();
//}

	// Convert in range[0,1]
	Imagedata b(height, width, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] == 255) {
				b.data[0][i][j] = 1;
			}
		}
	}			

	bool flag = true;
	int trials = 0;
	while (flag) {
		//Boundaryextension	
		Imagedata temp_ex = b.Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

		Imagedata M(height, width, byteperpixel);
		// compare
		int ind = 1;
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				if (rawdata[0][i][j] == 0) {
					continue;
				}
				queue<int> q;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						q.push(rawdata[0][i - ind + k][j - ind + l]);
					}
				}
				if (CONDI_PATTERNS_K_TREE.compare(q)) {
					M.data[0][i - ind][j - ind] = 1;
				}
			}
		}

		//Boundaryextension	
		Imagedata temp_ex2 = M.Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata2 = temp_ex2.data;

		Imagedata P(height, width, byteperpixel);
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				if (rawdata2[0][i][j] == 0) {
					continue;
				}
				queue<int> q;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						q.push(rawdata2[0][i - ind + k][j - ind + l]);
					}
				}
				if (UCONDI_PATTERNS_K_TREE.compare(q)) {
					P.data[0][i - ind][j - ind] = 1;
				}
			}
		}

		// M inverse
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (M.data[0][i][j] == 1) {
					M.data[0][i][j] = 0;
				}
				else M.data[0][i][j] = 1;
			}
		}
		// unchange count 
		int count = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (b.data[0][i][j] == b.data[0][i][j] & (M.data[0][i][j] | P.data[0][i][j])) {
					count++;
				}
				b.data[0][i][j] = b.data[0][i][j] & (M.data[0][i][j] | P.data[0][i][j]);
			}
		}
		if (count == height * width) {
			flag = false;
		}
		trials++;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (b.data[0][i][j] == 1) {
				b.data[0][i][j] = 255;
			}
		}
	}	
	return b;
}

Imagedata Imagedata::Bridge() {
	Imagedata res(height, width, byteperpixel);
	//Boundaryextension	
	Imagedata temp_ex = this->Boundaryextension(1);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	Algorithm A;
	int ind = 1;
	for (int i = ind; i < height + ind; i++) {
		for (int j = ind; j < width + ind; j++) {
			int x = rawdata[0][i][j];
			int x0 = rawdata[0][i][j + 1];
			int x1 = rawdata[0][i-1][j + 1];
			int x2 = rawdata[0][i-1][j];
			int x3 = rawdata[0][i-1][j-1];
			int x4 = rawdata[0][i][j -1];
			int x5 = rawdata[0][i+1][j - 1];
			int x6 = rawdata[0][i+1][j];
			int x7 = rawdata[0][i+1][j + 1];			
			int L1 = A.comp(x) & A.comp(x0) & x1 & A.comp(x2) & x3 & A.comp(x4)& A.comp(x5)& A.comp(x6)& A.comp(x7);
			int L2 = A.comp(x) & A.comp(x0) & A.comp(x1) & A.comp(x2) & x3 & A.comp(x4)& x5 & A.comp(x6)& A.comp(x7);
			int L3 = A.comp(x) & A.comp(x0) & A.comp(x1) & A.comp(x2) & A.comp(x3) & A.comp(x4)& x5 & A.comp(x6)& x7;
			int L4 = A.comp(x) & A.comp(x0) & x1 & A.comp(x2) & A.comp(x3) & A.comp(x4)& A.comp(x5) & A.comp(x6)& x7;
			int Pq = L1 | L2 | L3 | L4;
			int P1 = A.comp(x2) & A.comp(x6) & (x3 | x4 | x5) & (x0 | x1 | x7) & A.comp(Pq);
			int P2 = A.comp(x0) & A.comp(x4) & (x1 | x2 | x3) & (x5 | x6 | x7) & A.comp(Pq);
			int P3 = A.comp(x0) & A.comp(x6) & x7 & (x2 | x3 | x4);
			int P4 = A.comp(x0) & A.comp(x2) & x1 & (x4 | x5 | x6);
			int P5 = A.comp(x2) & A.comp(x4) & x3 & (x0 | x6 | x7);
			int P6 = A.comp(x4) & A.comp(x6) & x5 & (x0 | x1 | x2);
			res.data[0][i-ind][j-ind] = x | (P1 | P2 | P3 | P4 | P5 | P6);
		}
	}
	return res;
}

vector<pair<int, int>> Imagedata::find_defect() {
	Kernel ke(3, 3);
	ke.set_wholedata(255);
	ke.set_data(0, 1, 1);
	vector<pair<int, int>> res;
	

	
		//Boundaryextension	
		Imagedata temp_ex = this->Boundaryextension(1);
		vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	
		int ind = 1;
		for (int i = ind; i < height+ind; i++) {
			for (int j = ind; j < width+ind; j++) {												
					bool flag = true;
					for (int k = 0; k < ke.get_height() && flag == true; k++) {
						for (int l = 0; l < ke.get_width(); l++) {
							if (rawdata[0][i-ind+k][j-ind+l] != ke.get_data(k, l))
							{
								flag = false;
								break;
							}
						}
					}
					if (flag == true) {
						pair<int, int> p;
						p.first = i - ind;
						p.second = j - ind;
						res.push_back(p);										
					}				
			}
		}
		return res;
}

void Imagedata::emphasize_defect(vector<pair<int, int>> defect,int size) {
	
	for (int i = 0; i < defect.size(); i++) {
		for (int k = -size; k < size+1; k++) {			
			data[0][defect[i].first + size][defect[i].second + k] = 0;
			data[0][defect[i].first - size][defect[i].second + k] = 0;
			data[0][defect[i].first + k][defect[i].second + size] = 0;
			data[0][defect[i].first + k][defect[i].second - size] = 0;
		}		
	}
}

void Imagedata::delete_defect(vector<pair<int, int>> defect) {
	for (int i = 0; i < defect.size(); i++) {		
		data[0][defect[i].first][defect[i].second] = 255;
	}
}

void Imagedata::boundary_modify() {
	for (int i = 0; i < height; i++) {
		data[0][i][0] = 0;
		data[0][i][width - 1] = 0;
	}
	for (int j = 0; j < width; j++) {
		data[0][0][j] = 0;
		data[0][height - 1][j] = 0;
	}
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

Imagedata Imagedata::Grain_segmentation_value_offset(int offset) {
	Imagedata res(height, width, byteperpixel);
	
	for (int b = 0; b < byteperpixel; b++) {
		int background = data[b][0][0];
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (data[b][i][j] <= background + offset && data[b][i][j] >= background - offset) {
					res.data[b][i][j] = 0;
				}
				else
				{
					res.data[b][i][j] = 255;
				}
			}
		}
	}	
	return res;
}

Imagedata Imagedata::Grain_segmentation_position_offset(int offset) {
	Imagedata res(height, width, byteperpixel);	
	int background_label = 255;

	//Boundaryextension	
	Imagedata temp_ex = this->Boundaryextension(offset);
	vector<vector<vector<unsigned char>>> rawdata = temp_ex.data;

	Imagedata label(height, width, byteperpixel);
	for (int b = 0; b < byteperpixel;  b++) {
		int background = data[b][0][0];
		for (int i = offset; i < height + offset; i++) {
			for (int j = offset; j < width + offset; j++) {
				if (rawdata[b][i][j] == background) {
					label.data[b][i - offset][j - offset] = background_label;
					res.data[b][i - offset][j - offset] = 0;
				}
				/*	if (data[b][i][j] == background) {
						int count = 0;
						for (int k = 0; k < offset * 2 + 1; k++) {
							for (int l = 0; l < offset * 2 + 1; l++) {
								if (data[b][i - offset + k][j - offset + l] == background) {
									count++;
								}
							}
						}
						if (count >= (offset * 2 + 1) * (offset * 2 + 1) / 10.0 * 9.0) {
							label.data[b][i][j] = background_label;
							res.data[b][i][j] = 0;
						}
					}			*/
			}
		}
	}

	//Boundaryextension	
	Imagedata temp_ex2 = label.Boundaryextension(offset);
	vector<vector<vector<unsigned char>>> labeldata = temp_ex2.data;

	for (int b = 0; b < byteperpixel; b++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				bool flag = true;
				for (int k = 0; k < offset * 2 + 1 && flag == true; k++) {
					for (int l = 0; l < offset * 2 + 1; l++) {
						if (labeldata[b][i + k][j + l] == background_label) {
							res.data[b][i][j] = 0;
							flag = false;
							break;
						}
					}
				}
				if (flag) {
					res.data[b][i][j] = 255;
				}
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

vector<pair<int, int>> Imagedata::find_grain() {
	vector<pair<int, int>> res;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] == 1) {
				pair<int, int> p;
				p.first = i;
				p.second = j;
				res.push_back(p);
			}
		}
	}
	return res;
}

int Imagedata::area_grain(pair<int, int> centre) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> vec;
	Imagedata label(height, width, byteperpixel);
	q.push(centre);
	vec.push_back(centre);
	label.data[0][centre.first][centre.second] = 255;
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();		
		if (data[0][p.first - 1][p.second] == 255 && label.data[0][p.first - 1][p.second] == 0) {
			pair<int, int> temp(p.first - 1, p.second);
			q.push(temp);		
			vec.push_back(temp);
			label.data[0][p.first - 1][p.second] = 255;
		}
		if (data[0][p.first+1][p.second] == 255 && label.data[0][p.first+1][p.second] == 0) {
			pair<int, int> temp(p.first +1, p.second);
			q.push(temp);			
			vec.push_back(temp);
			label.data[0][p.first + 1][p.second] = 255;
		}
		if (data[0][p.first][p.second-1] == 255 && label.data[0][p.first][p.second-1] == 0) {
			pair<int, int> temp(p.first, p.second-1);
			q.push(temp);			
			vec.push_back(temp);
			label.data[0][p.first][p.second - 1] = 255;
		}
		if (data[0][p.first][p.second+1] == 255 && label.data[0][p.first][p.second+1] == 0) {
			pair<int, int> temp(p.first, p.second+1);
			q.push(temp);			
			vec.push_back(temp); 
			label.data[0][p.first][p.second + 1] = 255;
		}
	}
    //label.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\rice_label_test.raw");
	return vec.size();
}

Imagedata Imagedata::cluster_label(vector<pair<int, int>> cluster_single) {
	Imagedata label(height, width, byteperpixel);

	for (int s = 0; s < cluster_single.size(); s++) {
		queue<pair<int, int>> q;
		vector<pair<int, int>> vec;
		pair<int, int> centre = cluster_single[s];
		q.push(centre);
		vec.push_back(centre);
		label.data[0][centre.first][centre.second] = 255;
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			if (data[0][p.first - 1][p.second] == 255 && label.data[0][p.first - 1][p.second] == 0) {
				pair<int, int> temp(p.first - 1, p.second);
				q.push(temp);
				vec.push_back(temp);
				label.data[0][p.first - 1][p.second] = 255;
			}
			if (data[0][p.first + 1][p.second] == 255 && label.data[0][p.first + 1][p.second] == 0) {
				pair<int, int> temp(p.first + 1, p.second);
				q.push(temp);
				vec.push_back(temp);
				label.data[0][p.first + 1][p.second] = 255;
			}
			if (data[0][p.first][p.second - 1] == 255 && label.data[0][p.first][p.second - 1] == 0) {
				pair<int, int> temp(p.first, p.second - 1);
				q.push(temp);
				vec.push_back(temp);
				label.data[0][p.first][p.second - 1] = 255;
			}
			if (data[0][p.first][p.second + 1] == 255 && label.data[0][p.first][p.second + 1] == 0) {
				pair<int, int> temp(p.first, p.second + 1);
				q.push(temp);
				vec.push_back(temp);
				label.data[0][p.first][p.second + 1] = 255;
			}
		}
	}		
	

	
	return label;
}

Imagedata Imagedata::cluster_label_RGB(Imagedata cluster_label_Binary) {
	Imagedata res = *this;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (cluster_label_Binary.data[0][i][j] != 255) {
				res.data[RED][i][j] = data[RED][0][0];
				res.data[GREEN][i][j] = data[GREEN][0][0];
				res.data[BLUE][i][j] = data[BLUE][0][0];
			}
		}
	}
	return res;
}

vector<pair<int, double>> Imagedata::average_area(vector<vector<pair<int, int>>> cluster) {
	vector < pair<int, double>> res;
	for (int i = 0; i < cluster.size(); i++) {
		double sum = 0;
		for (int j = 0; j < cluster[i].size(); j++) {
			sum += this->area_grain(cluster[i][j]);
		}
		res.push_back(pair<int,double> (i, sum / 5.0));
	}
	return res;
}

vector<pair<int, int>> Imagedata::find_corner() {
	vector<pair<int, int>> res;
	// up
	int flag = true;
	for (int i = 0; i < height && flag; i++) {		
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] != 255) {
				pair<int, int> p;
				p.first = i;
				p.second = j;
				res.push_back(p);
				flag = false;
				break;
			}
		}	
	}

	// down
	flag = true;
	for (int i = height-1; i > -1 && flag; i--) {
		for (int j = 0; j < width; j++) {
			if (data[0][i][j] != 255) {
				pair<int, int> p;
				p.first = i;
				p.second = j;
				res.push_back(p);
				flag = false;
				break;
			}
		}	
	}

	// left
	flag = true;
	for (int i = 0; i < width && flag; i++) {
		for (int j = 0; j < height; j++) {
			if (data[0][j][i] != 255) {
				pair<int, int> p;
				p.first = j;
				p.second = i;
				res.push_back(p);
				flag = false;
				break;
			}
		}	
	}

	// right
	flag = true;
	for (int i = width-1; i > -1 && flag; i--) {
		for (int j = 0; j < height; j++) {
			if (data[0][j][i] != 255) {
				pair<int, int> p;
				p.first = j;
				p.second = i;
				res.push_back(p);
				flag = false;
				break;
			}
		}	
	}
	return res;
}

Imagedata Imagedata::rotation() {	
	vector<pair<int,int>> v = this->find_corner();
	//this->test_find_corner(v).save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\corner1.raw");
	Imagedata label = this->Binary(254);
	pair<int, int> v1 = v[0]; // up
	pair<int, int> v2 = v[1]; // down
	pair<int, int> v3 = v[2]; // left
	pair<int, int> v4 = v[3]; // right
	double theta = atan((double) abs(v2.first - v3.first) / (double) abs(v2.second - v3.second));
	double h = sqrt(pow(v1.second - v3.second, 2) + pow(v1.first - v3.first, 2)) + 4;
	double w = sqrt(pow(v1.second - v4.second, 2) + pow(v1.first - v4.first, 2)) + 2;
	
	// correction for lighthouse1 & 3
	theta -= 0.025;		
	
	// //forward mapping
	//Imagedata res(h + 100, w + 100, byteperpixel);
	//res.pure(255);
	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {					
	//		if (label.data[0][i][j] == 0) {
	//			int i_c = i - v1.first;
	//			int j_c = j - v1.second;
	//			double x = (double)i_c * cos(theta) - (double)j_c * sin(theta);
	//			double y = (double)i_c * sin(theta) + (double)j_c * cos(theta);
	//			res.data[0][x+50][y+50] = data[0][i][j];
	//		}		  
	//	}
	//}
	//Imagedata res2 = res.modify_edge(h, w);
	//return res2;

	// reverse mapping
	Imagedata res(h, w, byteperpixel);
	res.pure(255);
	for (int i = 0; i < (int)h; i++) {
		for (int j = 0; j < (int)w; j++) {						
				double x = (double)j * cos(theta) - (double)i * sin(theta);
				double y = (double)j * sin(theta) + (double)i * cos(theta);
				res.data[0][i][j] = data[0][v1.first+y][v1.second+x];			
		}
	}
	return res;
}

Imagedata Imagedata::modify_edge(int hei,int wid) {
	Imagedata res(wid,hei + 4,byteperpixel);

	// start point (50,50)
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i >= 49 && i < 49 + wid && j >= 50 && j < 54 + hei) {
				res.data[0][i - 49][j - 50] = data[0][i][j];
			}
			/*else {
				res.data[0][i][j] = 255;
			}*/
		}
	}		
	return res;
}

Imagedata Imagedata::counter_clock() {
	Imagedata res(width, height, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data[0][width - 1 - j][i] = data[0][i][j];
		}
	}
	return res;
}

Imagedata Imagedata::scale(int hei,int wid) {
	Imagedata res(hei, wid, byteperpixel);
	Imagedata label(hei, wid, byteperpixel);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			double hei_new = (double)i * hei / height;		
			double wid_new = (double)j * wid / width;
			res.data[0][hei_new][wid_new] = data[0][i][j];
			label.data[0][hei_new][wid_new] = 255;
		}
	}	
	// Bilinear interpolation
	if (hei > height || wid > width) {
		double hei_coef = (double) height / hei;
		double wid_coef = (double) width / wid;
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				if (label.data[0][i][j] != 255) {
					double x = wid_coef * j;
					double y = hei_coef * i;
					double dx = x - (int)x;
					double dy = y - (int)y;
					if (x >= width-1 && y < height - 1) {
						res.data[0][i][j] = (1 - dx) * (1 - dy) * data[0][y][x] + dx * (1 - dy) * data[0][y + 1][x];
					}
					else if(y >= height-1 && x < width - 1) {
						res.data[0][i][j] = (1 - dx) * (1 - dy) * data[0][y][x] + (1 - dx) * dy * data[0][y][x + 1];
					}
					else if (y >= height-1 && x >= width-1) {
						res.data[0][i][j] = (1 - dx) * (1 - dy) * data[0][y][x];
					}
					else {
						res.data[0][i][j] = (1 - dx) * (1 - dy) * data[0][y][x] + dx * (1 - dy) * data[0][y + 1][x] + (1 - dx) * dy * data[0][y][x + 1] + dx * dy * data[0][y + 1][x + 1];
					}					
				}
			}
		}
	}
	return res;
}

Imagedata Imagedata::test_find_corner(vector<pair<int, int>> v) {
	Imagedata res(height, width, byteperpixel);
	for (int i = 0; i < v.size(); i++) {
		res.data[0][v[i].first][v[i].second] = 255;
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

Imagedata Imagedata::insert(Imagedata A, Imagedata B, Imagedata C) {
	Imagedata res(height, width, byteperpixel);
	res = *this;
	vector<pair<int, int>> Position;	
	for (int i = 0; i < height - 159; i++) {
		for (int j = 0; j < width - 159; j++) {
			if (data[0][i][j] == 255 && data[0][i+159][j+159] == 255 && data[0][i][j + 159] == 255 && data[0][i + 159][j] == 255) {
				Position.push_back(pair<int, int>(i, j));								
			}			
		}
	}
	for (int i = 0; i < 3; i++) {
		Position.push_back(pair<int, int>(Position[i].first + 159, Position[i].second + 159));
		Position.push_back(pair<int, int>(Position[i].first, Position[i].second + 159));
		Position.push_back(pair<int, int>(Position[i].first + 159, Position[i].second));
	}
	this->test_find_corner(Position).save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\corner2.raw");
	pair<int, int> BP = Position[0];
	for (int i = BP.first; i < BP.first + 160; i++) {
		for (int j = BP.second; j < BP.second + 160; j++) {
			res.data[0][i][j+2] = B.data[0][i - BP.first][j - BP.second];
		}
	}
	pair<int, int> AP = Position[1];
	for (int i = AP.first; i < AP.first + 160; i++) {
		for (int j = AP.second; j < AP.second + 160; j++) {
			res.data[0][i][j] = A.data[0][i - AP.first][j - AP.second];
		}
	}
	pair<int, int> CP = Position[2];
	for (int i = CP.first; i < CP.first + 160; i++) {
		for (int j = CP.second; j < CP.second + 160; j++) {
			res.data[0][i][j] = C.data[0][i - CP.first][j - CP.second];
		}
	}

	// correction A
	for (int i = AP.first; i < AP.first + 160; i++) {
		//left
		for (int j = 0; j < 2; j++) {
			res.data[0][i][AP.second + j] = res.data[0][i][AP.second - j -1];
		}
		//right
		for (int j = 0; j < 2; j++) {
			res.data[0][i][AP.second - j + 159] = res.data[0][i][AP.second + 160 + j];
		}
	}
	for (int i = AP.second; i < AP.second + 160; i++) {
		// down
		for (int j = 0; j < 2; j++) {
			res.data[0][AP.first + 159 - j][i] = res.data[0][AP.first + 160+j][i];
		}
		// up
		for (int j = 0; j < 4; j++) {
			res.data[0][AP.first + j][i] = res.data[0][AP.first - j - 1][i];
		}
	}


	// correction B
	for (int i = BP.first; i < BP.first + 160; i++) {
		// left
		for (int j = 0; j < 2; j++) {
			res.data[0][i][BP.second + j] = res.data[0][i][BP.second - j - 1];
		}
		// right
		for (int j = 0; j < 4; j++) {
			res.data[0][i][BP.second - j + 159+2] = res.data[0][i][BP.second + 160 + j+2];
		}
	}
	for (int i = BP.second; i < BP.second + 160; i++) {
		// down
		for (int j = 0; j < 2; j++) {
			res.data[0][BP.first + 159 - j][i] = res.data[0][BP.first + 160 + j][i];
		}
		// up
		for (int j = 0; j < 4; j++) {
			res.data[0][BP.first + j][i] = res.data[0][BP.first - j - 1][i];
		}
	}

	// correction C
	for (int i = CP.first; i < CP.first + 160; i++) {
		// left
		for (int j = 0; j < 1; j++) {
			res.data[0][i][CP.second + j] = res.data[0][i][CP.second - j - 1];
		}
		// right
		for (int j = 0; j < 1; j++) {
			res.data[0][i][CP.second - j + 159] = res.data[0][i][CP.second + 160 + j];
		}
	}
	return res;
}

vector<Imagedata> Imagedata::seperate() {
	// 1:down 2:up 3:left 4:right
	vector<Imagedata> res;
	Imagedata down(height, width, byteperpixel);
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {			
			down.data[0][i][j] = data[0][i][j];
		}
	}
	Imagedata this_left = this->counter_clock();
	Imagedata left(height, width, byteperpixel);
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			left.data[0][i][j] = this_left.data[0][i][j];
		}
	}
	Imagedata this_up = this->counter_clock().counter_clock();
	Imagedata up(height, width, byteperpixel);
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			up.data[0][i][j] = this_up.data[0][i][j];
		}
	}
	Imagedata this_right = this->counter_clock().counter_clock().counter_clock();
	Imagedata right(height, width, byteperpixel);
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			right.data[0][i][j] = this_right.data[0][i][j];
		}
	}
	res.push_back(down);
	res.push_back(up);
	res.push_back(left);
	res.push_back(right);	
	/*down.save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\down.raw");
	left.counter_clock().counter_clock().counter_clock().save("G:\\569\\Homework\\HW3\\Image\\HW3_result\\left.raw");*/
	return res;
}

Imagedata Imagedata::Spatial_warping() {
	Kernel ke(2, 6);
	ke.set_data(1, 0, 1);
	ke.set_data(-1.002, 1, 1);
	ke.set_data(2.002, 1, 2);
	ke.set_data(0.002, 1, 3);
	ke.set_data(-0.002, 1, 5);

	Imagedata res(height, width, byteperpixel);
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			int x = j;
			int y = i;
			Kernel vector(6, 1);
			vector.set_data(1, 0, 0);
			vector.set_data(x, 1, 0);
			vector.set_data(y, 2, 0);
			vector.set_data(pow(x,2), 3, 0);
			vector.set_data(x*y, 4, 0);
			vector.set_data(pow(y,2), 5, 0);
			Kernel UV = ke.Multiplication(vector);
			res.data[0][round(UV.get_data(1,0))][round(UV.get_data(0,0))] = data[0][i][j];
		}
	}
	return res;
}

Imagedata Imagedata::Spatial_warping_reverse() {
	Kernel ke(2, 6);
	ke.set_data(1, 0, 1);
	ke.set_data(4.0236, 1, 1);
	ke.set_data(-3.0236, 1, 2);
	ke.set_data(-0.0079, 1, 3);
	ke.set_data(0.0079, 1, 5);

	Imagedata res(height, width, byteperpixel);
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			int x = j;
			int y = i;
			Kernel vector(6, 1);
			vector.set_data(1, 0, 0);
			vector.set_data(x, 1, 0);
			vector.set_data(y, 2, 0);
			vector.set_data(pow(x, 2), 3, 0);
			vector.set_data(x*y, 4, 0);
			vector.set_data(pow(y, 2), 5, 0);
			Kernel XY = ke.Multiplication(vector);
			if (round(XY.get_data(1, 0)) >= 0 && round(XY.get_data(1, 0)) < height && round(XY.get_data(0, 0)) >= 0 && round(XY.get_data(0, 0)) < width) {
				res.data[0][i][j] = data[0][round(XY.get_data(1, 0))][round(XY.get_data(0, 0))];
			}
			else {
				res.data[0][i][j] = 0;
			}
		}
	}
	return res;
}

void Imagedata::Spatial_combine(Imagedata down, Imagedata up, Imagedata left, Imagedata right) {
	Imagedata down_SW = down.Spatial_warping();
	Imagedata up_SW = up.Spatial_warping();
	Imagedata left_SW = left.Spatial_warping();
	Imagedata right_SW = right.Spatial_warping();
	*this = down_SW;
	*this = this->counter_clock();
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			data[0][i][j] = left_SW.data[0][i][j];
		}
	}
	*this = this->counter_clock();
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			data[0][i][j] = up_SW.data[0][i][j];
		}
	}
	*this = this->counter_clock();
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			data[0][i][j] = right_SW.data[0][i][j];
		}
	}
	*this = this->counter_clock();
}

void Imagedata::Spatial_combine_reverse(Imagedata down, Imagedata up, Imagedata left, Imagedata right) {
	Imagedata down_SW = down.Spatial_warping_reverse();
	Imagedata up_SW = up.Spatial_warping_reverse();
	Imagedata left_SW = left.Spatial_warping_reverse();
	Imagedata right_SW = right.Spatial_warping_reverse();
	*this = down_SW;
	*this = this->counter_clock();
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			data[0][i][j] = left_SW.data[0][i][j];
		}
	}
	*this = this->counter_clock();
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			data[0][i][j] = up_SW.data[0][i][j];
		}
	}
	*this = this->counter_clock();
	for (int i = 256; i < height; i++) {
		for (int j = 511 - i; j < i + 1; j++) {
			data[0][i][j] = right_SW.data[0][i][j];
		}
	}
	*this = this->counter_clock();
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

void Imagedata::square(int size) {
	int center_column = width / 2;
	int center_row = height / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			data[0][i + center_row - size / 2][j + center_column - size / 2] = 255;
		}
	}
}

void Imagedata::rectangle(int h,int w) {
	int center_column = width / 2;
	int center_row = height / 2;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			data[0][i + center_row - h / 2][j + center_column - w / 2] = 255;
		}
	}
}

//for (int i = 0; i < height; i++) {
//	for (int j = 0; j < width; j++) {
//		if (M.data[0][i][j] == 1) {
//			M.data[0][i][j] = 255;
//		}
//	}
//}

		/*Imagedata M(height, width, byteperpixel);
		int ind = 1;
		for (int i = ind; i < height+ind; i++) {
			for (int j = ind; j < width+ind; j++) {
				if (rawdata[0][i][j] == 0) {
					continue;
				}
				for (int ke = 0; ke < CONDI_PATTERNS_S.size(); ke++) {
					Kernel current = CONDI_PATTERNS_S[ke];
					bool flag = true;
					for (int k = 0; k < current.get_height() && flag == true; k++) {
						for (int l = 0; l < current.get_width(); l++) {
							if (rawdata[0][i-ind+k][j-ind+l] != current.get_data(k, l))
							{
								flag = false;
								break;
							}
						}
					}
					if (flag == true) {
						M.data[0][i-ind][j-ind] = 255;
						break;
					}
				}
			}
		}*/
