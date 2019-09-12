// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.1.19

#include <vector>
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