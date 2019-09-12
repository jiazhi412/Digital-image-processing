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


Kernel Kernel::Dithering_matric(int index) {	
	Kernel res(index, index);
	int size = 1;
	for (int i = 0; i < index / 2; i++) {
		int size = size * 2;
		Kernel temp(size, size);
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				if (j < size / 2 && k < size / 2) {
					temp.data[j][k] = temp.data[j][k] * 4 + 1;
				}
				else if (j < size / 2 && k >= size / 2) {
					temp.data[j][k] = temp.data[j][k] * 4 + 2;
				}
				else if (j >= size / 2 && k < size / 2) {
					temp.data[j][k] = temp.data[j][k] * 4 + 3;
				}
				else if (j >= size / 2 && k >= size / 2) {
					temp.data[j][k] = temp.data[j][k] * 4 ;
				}
			}
		}
		res = temp;
	}

	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			res.data[i][j] = (res.data[i][j] + 0.5) * 255.0 / pow(index, 2);
		}
	}
	return res;
}