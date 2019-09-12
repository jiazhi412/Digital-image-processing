// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.2.8

#include <stdlib.h>
#include "Algorithm.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;


int Algorithm::RangedRandDemo(int range_min, int range_max, int n)
{
	// Generate random numbers in thehalf-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number <range_max
	int i;
	for (i = 0; i < n; i++)
	{
		int u = (double)rand() / (RAND_MAX + 1) *(range_max - range_min) // RAND_MAX = 32767
			+ range_min;
		return u;
	}
}

int Algorithm::find_closest(int a) {
	if (a <= 127) {
		return 0;
	}
	else if (a > 128) {
		return 255;
	}
}

int Algorithm::correction(double a) {
	if (a < 0) {
		return 0;
	}
	else if (a > 255) {
		return 255;
	}
	else return (int) a;
}

string Algorithm::getNearestVertex(vector<unsigned char> old) {
	int R = old[0];
	int G = old[1];
	int B = old[2];
	string vertex;
	string mbvq;

	if (R + G > 255) {
		if (G + B > 255) {
			if (R + G + B > 510) {
				mbvq = "CMYW";
			}
			else {
				mbvq = "MYGC";
			}
		}
		else {
			mbvq = "RGMY";
		}
	}
	else {
		if (G + B <= 255) {
			if (R + G + B <= 255) {
				mbvq = "KRGB";
			}
			else {
				mbvq = "RGBM";
			}
		}
		else {
			mbvq = "CMGB";
		}
	}

	// No.1 for CMYW
	if (mbvq == "CMYW") {
		vertex = "white";
		if (B < 128) {
			if (B <= R) {
				if (B <= G) {
					vertex = "yellow";
				}
			}
		}
		if (G < 128) {
			if (G <= B) {
				if (G <= R) {
					vertex = "magenta";
				}
			}
		}
		if (R < 128) {
			if (R <= B) {
				if (R <= G) {
					vertex = "cyan";
				}
			}
		}
	}

	// No.2 for MYGC
	if (mbvq == "MYGC") {
		vertex = "magenta";
		if (G >= B) {
			if (R >= B) {
				if (R >= 128) {
					vertex = "yellow";
				}
				else {
					vertex = "green";
				}
			}
		}
		if (G >= R) {
			if (B >= R) {
				if (B >= 128) {
					vertex = "cyan";
				}
				else {
					vertex = "green";
				}
			}
		}
	}

	// No.3 for RGMY
	if (mbvq == "RGMY") {
		if (B > 128) {
			if (R > 128) {
				if (B >= G) {
					vertex = "magenta";
				}
				else {
					vertex = "yellow";
				}
			}
			else {
				if (G > B + R) {
					vertex = "green";
				}
				else {
					vertex = "magenta";
				}
			}
		}
		else {
			if (R >= 128) {
				if (G >= 128) {
					vertex = "yellow";
				}
				else {
					vertex = "red";
				}
			}
			else {
				if (R >= G) {
					vertex = "red";
				}
				else {
					vertex = "green";
				}
			}
		}
	}

	// No.4 for KRGB
	if (mbvq == "KRGB") {
		vertex = "black";
		if (B > 128) {
			if (B >= R) {
				if (B >= G) {
					vertex = "blue";
				}
			}
		}
		if (G > 128) {
			if (G >= B) {
				if (G >= R) {
					vertex = "green";
				}
			}
		}
		if (R > 128) {
			if (R >= B) {
				if (R >= G) {
					vertex = "red";
				}
			}
		}
	}

	// No.5 for RGBM
	if (mbvq == "RGBM") {
		vertex = "green";
		if (R > G) {
			if (R >= B) {
				if (B < 128) {
					vertex = "red";
				}
				else {
					vertex = "magenta";
				}
			}
		}
		if (B > G) {
			if (B >= R) {
				if (R < 128) {
					vertex = "blue";
				}
				else {
					vertex = "magenta";
				}
			}
		}
	}

	// No.6 for CMGB
	if (mbvq == "CMGB") {
		if (B > 128) {
			if (R > 128) {
				if (G >= R) {
					vertex = "cyan";
				}
				else {
					vertex = "magenta";
				}
			}
			else {
				if (G > 128) {
					vertex = "cyan";
				}
				else {
					vertex = "blue";
				}
			}
		}
		else {
			if (R > 128) {
				if (R - G + B >= 128) {
					vertex = "magenta";
				}
				else {
					vertex = "green";
				}
			}
			else {
				if (G >= B) {
					vertex = "green";
				}
				else {
					vertex = "blue";
				}
			}
		}
	}

	return vertex;
}

vector<unsigned char> Algorithm::string2int_MBVQ(string vertex) {
	vector<unsigned char> res(3);
	if (vertex == "black") {
		res[0] = 0;
		res[1] = 0;
		res[2] = 0;
	}
	else if (vertex == "blue") {
		res[0] = 0;
		res[1] = 0;
		res[2] = 255;
	}
	else if (vertex == "green") {
		res[0] = 0;
		res[1] = 255;
		res[2] = 0;
	}
	else if (vertex == "red") {
		res[0] = 255;
		res[1] = 0;
		res[2] = 0;
	}
	else if (vertex == "cyan") {
		res[0] = 0;
		res[1] = 255;
		res[2] = 255;
	}
	else if (vertex == "magenta") {
		res[0] = 255;
		res[1] = 0;
		res[2] = 255;
	}
	else if (vertex == "yellow") {
		res[0] = 255;
		res[1] = 255;
		res[2] = 0;
	}
	else if (vertex == "white") {
		res[0] = 255;
		res[1] = 255;
		res[2] = 255;
	}
	return res;
}

cv::Mat Algorithm::Canny_edge_detection(cv::Mat src, int lowthreshold, int highthreshold, int kernel_size) {
	cv::Mat src_gray;
	cv::Mat src_gray_blur;
	cv::Mat dst;
	dst.create(src.size(), src.type());

	
	cv::cvtColor(src, src_gray, CV_BGR2GRAY);
	cv::blur(src_gray, src_gray_blur, cv::Size(3, 3));
	cv::Canny(src_gray_blur, dst, lowthreshold, highthreshold, kernel_size);

	return dst;
}

