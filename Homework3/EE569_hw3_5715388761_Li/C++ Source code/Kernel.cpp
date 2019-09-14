// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "Kernel.h"
using namespace std;

Kernel::Kernel(int h, int w) {
	height = h;
	width = w;
	vector<vector<double>> temp(h);
	data = temp;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			data[i].push_back(0);
		}
	}
}

Kernel::~Kernel() {

}

void Kernel::set_data(double d, int i, int j) {
	data[i][j] = d;
}

void Kernel::set_wholedata(double d) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i][j] = d;
		}
	}
}

double Kernel::sum() {
	double sum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			sum = sum + data[i][j];
		}
	}
	return sum;
}

double Kernel::get_data(int i, int j) {
	return data[i][j];
}

vector<vector<double>> Kernel::get_wholedata() {
	return data;
}

Kernel Kernel::EQ() {
	Kernel res(height, width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			res.data[i][j] = data[i][j] / this->sum();
		}
	}
	return res;
}

void Kernel::resize(int h, int w) {		
	Kernel temp(h, w);
	for(int i = 0; i < min(h,height);i++) {
		for (int j = 0; j < min(w,width); j++) {
			temp.data[i][j] = data[i][j];
		}
	}
	height = h;
	width = w;
	data = temp.data;
}

int Kernel::get_height() {
	return height;
}

int Kernel::get_width() {
	return width;
}

void Kernel::Mark_Pattern(int a[]) {
	int s = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i][j] = a[s];
			s++;
		}
	}
}

void Kernel::generate(int a[]) {
	int s = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i][j] = a[s];
			s++;
		}
	}
}

void Kernel::Print() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout<< data[i][j] << " ";
		}
		cout<<endl;	
	}
	cout << endl;
}

Kernel Kernel::Multiplication(Kernel other) {
	Kernel res(height, other.width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < other.width; j++) {
			for (int k = 0; k < width; k++) {				
				res.data[i][j] += data[i][k] * other.data[k][j];
			}			
		}
	}
	return res;
}