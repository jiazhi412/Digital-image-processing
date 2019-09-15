// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

#ifndef CPP_KERNEL_H
#define CPP_KERNEL_H

using namespace std;

class Kernel {

private:
	int height;
	int width;
	vector<vector<double>> data;

public:
	Kernel(); // default constructor
	Kernel(int h, int w); //constructor
	~Kernel(); //destructor
	void set_data(double d, int i, int j); //set elements(i,j) as value d
	void set_wholedata(double d);
	double sum(); //get sum
	vector<vector<double>> get_wholedata(); //return a two dimension vector as kernel
	double get_data(int i, int j); //get the value of element(i,j)
	int get_height();
	int get_width();
	Kernel EQ(); //equalization	
	void Print(); // Print the kernel	
	void resize(int h, int w); // Resize the kernel
	void Mark_Pattern(int a[]); // convert a array to a kernel
	void generate(int a[]); // convert a array to kernel
	Kernel Multiplication(Kernel other); // this * other (Matrix multiplication
	Kernel Transpose(); // Transpose opeartion for matrix
	void Vector2Kernel(vector<vector<double>> vector_set); // combine several row vectors to be a kernel
	vector<double> Kernel2vector(); // change a kernel to be a vector
	vector<vector<double>> Kernel2vector2D(); // change a kernel to be a 2-D vector
	Kernel normalize(); // normalize by each row to be a mean = 0 and variance = 1
	Kernel getRow(int i); // return row
	Kernel getColumn(int i); // return column
};
#endif //CPP_KERNEL_H
