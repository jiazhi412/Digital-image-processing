// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.1.19

#ifndef CPP_KERNEL_H
#define CPP_KERNEL_H

using namespace std;

class Kernel {

private:
	int height;
	int width;
	vector<vector<double>> data;

public:
	Kernel(int h, int w); //constructor
	~Kernel(); //destructor
	void set_data(double d, int i, int j); //set elements(i,j) as value d
	double sum(); //get sum
	vector<vector<double>> get_wholedata(); //return a two dimension vector as kernel
	double get_data(int i, int j); //get the value of element(i,j)
	Kernel EQ(); //equalization
	Kernel Dithering_matric(int index);
};
#endif //CPP_KERNEL_H
