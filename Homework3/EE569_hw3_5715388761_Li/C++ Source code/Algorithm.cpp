// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

#include <stdlib.h>
#include "Algorithm.h"

using namespace std;

int Algorithm::correction(double a) {
	if (a < 0) {
		return 0;
	}
	else if (a > 255) {
		return 255;
	}
	else return (int)a;
}

vector<Kernel> Algorithm::Condi_Shrink() {
	vector<Kernel> CONDI_PATTERNS;
	Kernel K(3, 3);

	////test
	//int t[] = { 0,0,0,0,0,0,0,0,0 };
	//K.Mark_Pattern(t);
	//CONDI_PATTERNS.push_back(K);


	// S Bond = 1
	int a1[] = { 0,0,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a1);
	CONDI_PATTERNS.push_back(K);
	int a2[] = { 1,0,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a2);
	CONDI_PATTERNS.push_back(K);
	int a3[] = { 0,0,0,0,1,0,1,0,0 };
	K.Mark_Pattern(a3);
	CONDI_PATTERNS.push_back(K);
	int a4[] = { 0,0,0,0,1,0,0,0,1 };
	K.Mark_Pattern(a4);
	CONDI_PATTERNS.push_back(K);

	// S Bond = 2
	int a5[] = { 0,0,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a5);
	CONDI_PATTERNS.push_back(K);
	int a6[] = { 0,1,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a6);
	CONDI_PATTERNS.push_back(K);
	int a7[] = { 0,0,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a7);
	CONDI_PATTERNS.push_back(K);
	int a8[] = { 0,0,0,0,1,0,0,1,0 };
	K.Mark_Pattern(a8);
	CONDI_PATTERNS.push_back(K);

	// S Bond = 3
	int a9[] = { 0,0,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a9);
	CONDI_PATTERNS.push_back(K);
	int a10[] = { 0,1,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a10);
	CONDI_PATTERNS.push_back(K);
	int a11[] = { 1,1,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a11);
	CONDI_PATTERNS.push_back(K);
	int a12[] = { 1,0,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a12);
	CONDI_PATTERNS.push_back(K);
	int a13[] = { 0,0,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a13);
	CONDI_PATTERNS.push_back(K);
	int a14[] = { 0,0,0,0,1,0,1,1,0 };
	K.Mark_Pattern(a14);
	CONDI_PATTERNS.push_back(K);
	int a15[] = { 0,0,0,0,1,0,0,1,1 };
	K.Mark_Pattern(a15);
	CONDI_PATTERNS.push_back(K);
	int a16[] = { 0,0,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a16);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 4
	int a17[] = { 0,0,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a17);
	CONDI_PATTERNS.push_back(K);
	int a18[] = { 1,1,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a18);
	CONDI_PATTERNS.push_back(K);
	int a19[] = { 1,0,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a19);
	CONDI_PATTERNS.push_back(K);
	int a20[] = { 0,0,0,0,1,0,1,1,1 };
	K.Mark_Pattern(a20);
	CONDI_PATTERNS.push_back(K);

	// ST Bond = 5
	int a21[] = { 1,1,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a21);
	CONDI_PATTERNS.push_back(K);
	int a22[] = { 0,1,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a22);
	CONDI_PATTERNS.push_back(K);
	int a23[] = { 0,1,1,1,1,0,0,0,0 };
	K.Mark_Pattern(a23);
	CONDI_PATTERNS.push_back(K);
	int a24[] = { 0,0,1,0,1,1,0,1,0 };
	K.Mark_Pattern(a24);
	CONDI_PATTERNS.push_back(K);
	int a25[] = { 0,1,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a25);
	CONDI_PATTERNS.push_back(K);
	int a26[] = { 1,1,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a26);
	CONDI_PATTERNS.push_back(K);
	int a27[] = { 0,0,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a27);
	CONDI_PATTERNS.push_back(K);
	int a28[] = { 0,0,0,0,1,1,0,1,1 };
	K.Mark_Pattern(a28);
	CONDI_PATTERNS.push_back(K);


	// ST Bond = 6
	int a61[] = { 1,1,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a61);
	CONDI_PATTERNS.push_back(K);
	int a62[] = { 0,1,1,1,1,0,1,0,0 };
	K.Mark_Pattern(a62);
	CONDI_PATTERNS.push_back(K);


	// STK 6
	int a63[] = { 1,1,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a63);
	CONDI_PATTERNS.push_back(K);
	int a64[] = { 0,1,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a64);
	CONDI_PATTERNS.push_back(K);
	int a65[] = { 1,1,1,1,1,0,0,0,0 };
	K.Mark_Pattern(a65);
	CONDI_PATTERNS.push_back(K);
	int a66[] = { 1,1,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a66);
	CONDI_PATTERNS.push_back(K);
	int a67[] = { 1,0,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a67);
	CONDI_PATTERNS.push_back(K);
	int a68[] = { 0,0,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a68);
	CONDI_PATTERNS.push_back(K);
	int a69[] = { 0,0,0,0,1,1,1,1,1 };
	K.Mark_Pattern(a69);
	CONDI_PATTERNS.push_back(K);
	int a60[] = { 0,0,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a60);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 7
	int a71[] = { 1,1,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a71);
	CONDI_PATTERNS.push_back(K);
	int a72[] = { 1,1,1,1,1,0,1,0,0 };
	K.Mark_Pattern(a72);
	CONDI_PATTERNS.push_back(K);
	int a73[] = { 1,0,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a73);
	CONDI_PATTERNS.push_back(K);
	int a74[] = { 0,0,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a74);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 8
	int a81[] = { 0,1,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a81);
	CONDI_PATTERNS.push_back(K);
	int a82[] = { 1,1,1,1,1,1,0,0,0 };
	K.Mark_Pattern(a82);
	CONDI_PATTERNS.push_back(K);
	int a83[] = { 1,1,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a83);
	CONDI_PATTERNS.push_back(K);
	int a84[] = { 0,0,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a84);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 9
	int a91[] = { 1,1,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a91);
	CONDI_PATTERNS.push_back(K);
	int a92[] = { 0,1,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a92);
	CONDI_PATTERNS.push_back(K);
	int a93[] = { 1,1,1,1,1,1,1,0,0 };
	K.Mark_Pattern(a93);
	CONDI_PATTERNS.push_back(K);
	int a94[] = { 1,1,1,1,1,1,0,0,1 };
	K.Mark_Pattern(a94);
	CONDI_PATTERNS.push_back(K);
	int a95[] = { 1,1,1,1,1,0,1,1,0 };
	K.Mark_Pattern(a95);
	CONDI_PATTERNS.push_back(K);
	int a96[] = { 1,1,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a96);
	CONDI_PATTERNS.push_back(K);
	int a97[] = { 1,0,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a97);
	CONDI_PATTERNS.push_back(K);
	int a98[] = { 0,0,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a98);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 10
	int a101[] = { 1,1,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a101);
	CONDI_PATTERNS.push_back(K);
	int a102[] = { 1,1,1,1,1,1,1,0,1 };
	K.Mark_Pattern(a102);
	CONDI_PATTERNS.push_back(K);
	int a103[] = { 1,1,1,1,1,0,1,1,1 };
	K.Mark_Pattern(a103);
	CONDI_PATTERNS.push_back(K);
	int a104[] = { 1,0,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a104);
	CONDI_PATTERNS.push_back(K);

	// deer
	//	// K 11
	//int a111[] = { 1,1,1,1,1,1,0,1,1 };
	//K.Mark_Pattern(a111);
	//CONDI_PATTERNS.push_back(K);
	//int a112[] = { 1,1,1,1,1,1,1,1,0 };
	//K.Mark_Pattern(a112);
	//CONDI_PATTERNS.push_back(K);
	//int a113[] = { 1,1,0,1,1,1,1,1,1 };
	//K.Mark_Pattern(a113);
	//CONDI_PATTERNS.push_back(K);
	//int a114[] = { 0,1,1,1,1,1,1,1,1 };
	//K.Mark_Pattern(a114);
	//CONDI_PATTERNS.push_back(K);

	return CONDI_PATTERNS;
}

vector<Kernel> Algorithm::Condi_Thin() {
	vector<Kernel> CONDI_PATTERNS;
	Kernel K(3, 3);

	// TK Bond = 4
	int a5[] = { 0,1,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a5);
	CONDI_PATTERNS.push_back(K);
	int a6[] = { 0,1,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a6);
	CONDI_PATTERNS.push_back(K);
	int a7[] = { 0,0,0,1,1,0,0,1,0 };
	K.Mark_Pattern(a7);
	CONDI_PATTERNS.push_back(K);
	int a8[] = { 0,0,0,0,1,1,0,1,0 };
	K.Mark_Pattern(a8);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 4
	int a17[] = { 0,0,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a17);
	CONDI_PATTERNS.push_back(K);
	int a18[] = { 1,1,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a18);
	CONDI_PATTERNS.push_back(K);
	int a19[] = { 1,0,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a19);
	CONDI_PATTERNS.push_back(K);
	int a20[] = { 0,0,0,0,1,0,1,1,1 };
	K.Mark_Pattern(a20);
	CONDI_PATTERNS.push_back(K);

	// ST Bond = 5
	int a21[] = { 1,1,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a21);
	CONDI_PATTERNS.push_back(K);
	int a22[] = { 0,1,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a22);
	CONDI_PATTERNS.push_back(K);
	int a23[] = { 0,1,1,1,1,0,0,0,0 };
	K.Mark_Pattern(a23);
	CONDI_PATTERNS.push_back(K);
	int a24[] = { 0,0,1,0,1,1,0,1,0 };
	K.Mark_Pattern(a24);
	CONDI_PATTERNS.push_back(K);
	int a25[] = { 0,1,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a25);
	CONDI_PATTERNS.push_back(K);
	int a26[] = { 1,1,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a26);
	CONDI_PATTERNS.push_back(K);
	int a27[] = { 0,0,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a27);
	CONDI_PATTERNS.push_back(K);
	int a28[] = { 0,0,0,0,1,1,0,1,1 };
	K.Mark_Pattern(a28);
	CONDI_PATTERNS.push_back(K);


	// ST Bond = 6
	int a61[] = { 1,1,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a61);
	CONDI_PATTERNS.push_back(K);
	int a62[] = { 0,1,1,1,1,0,1,0,0 };
	K.Mark_Pattern(a62);
	CONDI_PATTERNS.push_back(K);

	// STK 6
	int a63[] = { 1,1,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a63);
	CONDI_PATTERNS.push_back(K);
	int a64[] = { 0,1,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a64);
	CONDI_PATTERNS.push_back(K);
	int a65[] = { 1,1,1,1,1,0,0,0,0 };
	K.Mark_Pattern(a65);
	CONDI_PATTERNS.push_back(K);
	int a66[] = { 1,1,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a66);
	CONDI_PATTERNS.push_back(K);
	int a67[] = { 1,0,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a67);
	CONDI_PATTERNS.push_back(K);
	int a68[] = { 0,0,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a68);
	CONDI_PATTERNS.push_back(K);
	int a69[] = { 0,0,0,0,1,1,1,1,1 };
	K.Mark_Pattern(a69);
	CONDI_PATTERNS.push_back(K);
	int a60[] = { 0,0,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a60);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 7
	int a71[] = { 1,1,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a71);
	CONDI_PATTERNS.push_back(K);
	int a72[] = { 1,1,1,1,1,0,1,0,0 };
	K.Mark_Pattern(a72);
	CONDI_PATTERNS.push_back(K);
	int a73[] = { 1,0,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a73);
	CONDI_PATTERNS.push_back(K);
	int a74[] = { 0,0,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a74);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 8
	int a81[] = { 0,1,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a81);
	CONDI_PATTERNS.push_back(K);
	int a82[] = { 1,1,1,1,1,1,0,0,0 };
	K.Mark_Pattern(a82);
	CONDI_PATTERNS.push_back(K);
	int a83[] = { 1,1,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a83);
	CONDI_PATTERNS.push_back(K);
	int a84[] = { 0,0,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a84);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 9
	int a91[] = { 1,1,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a91);
	CONDI_PATTERNS.push_back(K);
	int a92[] = { 0,1,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a92);
	CONDI_PATTERNS.push_back(K);
	int a93[] = { 1,1,1,1,1,1,1,0,0 };
	K.Mark_Pattern(a93);
	CONDI_PATTERNS.push_back(K);
	int a94[] = { 1,1,1,1,1,1,0,0,1 };
	K.Mark_Pattern(a94);
	CONDI_PATTERNS.push_back(K);
	int a95[] = { 1,1,1,1,1,0,1,1,0 };
	K.Mark_Pattern(a95);
	CONDI_PATTERNS.push_back(K);
	int a96[] = { 1,1,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a96);
	CONDI_PATTERNS.push_back(K);
	int a97[] = { 1,0,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a97);
	CONDI_PATTERNS.push_back(K);
	int a98[] = { 0,0,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a98);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 10
	int a101[] = { 1,1,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a101);
	CONDI_PATTERNS.push_back(K);
	int a102[] = { 1,1,1,1,1,1,1,0,1 };
	K.Mark_Pattern(a102);
	CONDI_PATTERNS.push_back(K);
	int a103[] = { 1,1,1,1,1,0,1,1,1 };
	K.Mark_Pattern(a103);
	CONDI_PATTERNS.push_back(K);
	int a104[] = { 1,0,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a104);
	CONDI_PATTERNS.push_back(K);

	return CONDI_PATTERNS;
}

vector<Kernel> Algorithm::Condi_Skeleton() {
	vector<Kernel> CONDI_PATTERNS;
	Kernel K(3, 3);

	// TK Bond = 4
	int a5[] = { 0,1,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a5);
	CONDI_PATTERNS.push_back(K);
	int a6[] = { 0,1,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a6);
	CONDI_PATTERNS.push_back(K);
	int a7[] = { 0,0,0,1,1,0,0,1,0 };
	K.Mark_Pattern(a7);
	CONDI_PATTERNS.push_back(K);
	int a8[] = { 0,0,0,0,1,1,0,1,0 };
	K.Mark_Pattern(a8);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 4
	int a17[] = { 0,0,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a17);
	CONDI_PATTERNS.push_back(K);
	int a18[] = { 1,1,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a18);
	CONDI_PATTERNS.push_back(K);
	int a19[] = { 1,0,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a19);
	CONDI_PATTERNS.push_back(K);
	int a20[] = { 0,0,0,0,1,0,1,1,1 };
	K.Mark_Pattern(a20);
	CONDI_PATTERNS.push_back(K);

	// STK 6	
	int a63[] = { 1,1,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a63);
	CONDI_PATTERNS.push_back(K);
	int a64[] = { 0,1,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a64);
	CONDI_PATTERNS.push_back(K);
	int a65[] = { 1,1,1,1,1,0,0,0,0 };
	K.Mark_Pattern(a65);
	CONDI_PATTERNS.push_back(K);
	int a66[] = { 1,1,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a66);
	CONDI_PATTERNS.push_back(K);
	int a67[] = { 1,0,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a67);
	CONDI_PATTERNS.push_back(K);
	int a68[] = { 0,0,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a68);
	CONDI_PATTERNS.push_back(K);
	int a69[] = { 0,0,0,0,1,1,1,1,1 };
	K.Mark_Pattern(a69);
	CONDI_PATTERNS.push_back(K);
	int a60[] = { 0,0,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a60);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 7
	int a71[] = { 1,1,1,0,1,1,0,0,1 };
	K.Mark_Pattern(a71);
	CONDI_PATTERNS.push_back(K);
	int a72[] = { 1,1,1,1,1,0,1,0,0 };
	K.Mark_Pattern(a72);
	CONDI_PATTERNS.push_back(K);
	int a73[] = { 1,0,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a73);
	CONDI_PATTERNS.push_back(K);
	int a74[] = { 0,0,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a74);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 8
	int a81[] = { 0,1,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a81);
	CONDI_PATTERNS.push_back(K);
	int a82[] = { 1,1,1,1,1,1,0,0,0 };
	K.Mark_Pattern(a82);
	CONDI_PATTERNS.push_back(K);
	int a83[] = { 1,1,0,1,1,0,1,1,0 };
	K.Mark_Pattern(a83);
	CONDI_PATTERNS.push_back(K);
	int a84[] = { 0,0,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a84);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 9
	int a91[] = { 1,1,1,0,1,1,0,1,1 };
	K.Mark_Pattern(a91);
	CONDI_PATTERNS.push_back(K);
	int a92[] = { 0,1,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a92);
	CONDI_PATTERNS.push_back(K);
	int a93[] = { 1,1,1,1,1,1,1,0,0 };
	K.Mark_Pattern(a93);
	CONDI_PATTERNS.push_back(K);
	int a94[] = { 1,1,1,1,1,1,0,0,1 };
	K.Mark_Pattern(a94);
	CONDI_PATTERNS.push_back(K);
	int a95[] = { 1,1,1,1,1,0,1,1,0 };
	K.Mark_Pattern(a95);
	CONDI_PATTERNS.push_back(K);
	int a96[] = { 1,1,0,1,1,0,1,1,1 };
	K.Mark_Pattern(a96);
	CONDI_PATTERNS.push_back(K);
	int a97[] = { 1,0,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a97);
	CONDI_PATTERNS.push_back(K);
	int a98[] = { 0,0,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a98);
	CONDI_PATTERNS.push_back(K);

	// STK Bond = 10
	int a101[] = { 1,1,1,0,1,1,1,1,1 };
	K.Mark_Pattern(a101);
	CONDI_PATTERNS.push_back(K);
	int a102[] = { 1,1,1,1,1,1,1,0,1 };
	K.Mark_Pattern(a102);
	CONDI_PATTERNS.push_back(K);
	int a103[] = { 1,1,1,1,1,0,1,1,1 };
	K.Mark_Pattern(a103);
	CONDI_PATTERNS.push_back(K);
	int a104[] = { 1,0,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a104);
	CONDI_PATTERNS.push_back(K);

	// K 11
	int a111[] = { 1,1,1,1,1,1,0,1,1 };
	K.Mark_Pattern(a111);
	CONDI_PATTERNS.push_back(K);
	int a112[] = { 1,1,1,1,1,1,1,1,0 };
	K.Mark_Pattern(a112);
	CONDI_PATTERNS.push_back(K);
	int a113[] = { 1,1,0,1,1,1,1,1,1 };
	K.Mark_Pattern(a113);
	CONDI_PATTERNS.push_back(K);
	int a114[] = { 0,1,1,1,1,1,1,1,1 };
	K.Mark_Pattern(a114);
	CONDI_PATTERNS.push_back(K);

	return CONDI_PATTERNS;
}

vector<Kernel> Algorithm::UCondi_ST() {
	// extend abc to d
	//A2 B3 C4 D5

	vector<Kernel> UCONDI_PATTERNS;
	Kernel K(3, 3);

	// Spur
	int a1[] = { 0,0,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a1);
	UCONDI_PATTERNS.push_back(K);
	int a2[] = { 1,0,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a2);
	UCONDI_PATTERNS.push_back(K);

	// Single 4-connection
	int a3[] = { 0,0,0,0,1,0,0,1,0 };
	K.Mark_Pattern(a3);
	UCONDI_PATTERNS.push_back(K);
	int a4[] = { 0,0,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a4);
	UCONDI_PATTERNS.push_back(K);

	// L Cluster
	int a5[] = { 0,0,1,0,1,1,0,0,0 };
	K.Mark_Pattern(a5);
	UCONDI_PATTERNS.push_back(K);
	int a6[] = { 0,1,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a6);
	UCONDI_PATTERNS.push_back(K);
	int a7[] = { 1,1,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a7);
	UCONDI_PATTERNS.push_back(K);
	int a8[] = { 1,0,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a8);
	UCONDI_PATTERNS.push_back(K);
	int a9[] = { 0,0,0,1,1,0,1,0,0 };
	K.Mark_Pattern(a9);
	UCONDI_PATTERNS.push_back(K);
	int a10[] = { 0,0,0,0,1,0,1,1,0 };
	K.Mark_Pattern(a10);
	UCONDI_PATTERNS.push_back(K);
	int a11[] = { 0,0,0,0,1,0,0,1,1 };
	K.Mark_Pattern(a11);
	UCONDI_PATTERNS.push_back(K);
	int a12[] = { 0,0,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a12);
	UCONDI_PATTERNS.push_back(K);

	// 4-connected Offset
	int a13[] = { 0,1,1,1,1,0,0,0,0 };
	K.Mark_Pattern(a13);
	UCONDI_PATTERNS.push_back(K);
	int a14[] = { 1,1,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a14);
	UCONDI_PATTERNS.push_back(K);
	int a15[] = { 0,1,0,0,1,1,0,0,1 };
	K.Mark_Pattern(a15);
	UCONDI_PATTERNS.push_back(K);
	int a16[] = { 0,0,1,0,1,1,0,1,0 };
	K.Mark_Pattern(a16);
	UCONDI_PATTERNS.push_back(K);

	// Spur corner Cluster

	int a17[] = { 0,2,1,0,1,3,1,0,0 };
	combine(UCONDI_PATTERNS, extendABC(a17));
	int a18[] = { 1,3,0,2,1,0,0,0,1 };
	combine(UCONDI_PATTERNS, extendABC(a18));
	int a182[] = { 0,0,1,2,1,0,1,3,0 };
	combine(UCONDI_PATTERNS, extendABC(a182)); 
	int a19[] = { 1,0,0,0,1,3,0,2,1 };
	combine(UCONDI_PATTERNS, extendABC(a19));

	// Corner Cluster

	int a20[] = { 1,1,5,1,1,5,5,5,5 };
	K.Mark_Pattern(a20);
	UCONDI_PATTERNS.push_back(K);

	// Tee Branch
	int a21[] = { 5,1,0,1,1,1,5,0,0 };
	K.Mark_Pattern(a21);
	UCONDI_PATTERNS.push_back(K);
	int a22[] = { 0,1,5,1,1,1,0,0,5 };
	K.Mark_Pattern(a22);
	UCONDI_PATTERNS.push_back(K);
	int a23[] = { 0,0,5,1,1,1,0,1,5 };
	K.Mark_Pattern(a23);
	UCONDI_PATTERNS.push_back(K);
	int a24[] = { 5,0,0,1,1,1,5,1,0 };
	K.Mark_Pattern(a24);
	UCONDI_PATTERNS.push_back(K);
	int a25[] = { 5,1,5,1,1,0,0,1,0 };
	K.Mark_Pattern(a25);
	UCONDI_PATTERNS.push_back(K);
	int a26[] = { 0,1,0,1,1,0,5,1,5 };
	K.Mark_Pattern(a26);
	UCONDI_PATTERNS.push_back(K);
	int a27[] = { 0,1,0,0,1,1,5,1,5 };
	K.Mark_Pattern(a27);
	UCONDI_PATTERNS.push_back(K);
	int a28[] = { 5,1,5,0,1,1,0,1,0 };
	K.Mark_Pattern(a28);
	UCONDI_PATTERNS.push_back(K);


	// Vee Branch
	int a29[] = { 1,5,1,5,1,5,2,3,4 };
	combine(UCONDI_PATTERNS, extendABC(a29));
	int a30[] = { 1,5,4,5,1,3,1,5,2 };
	combine(UCONDI_PATTERNS, extendABC(a30));
	int a31[] = { 4,3,2,5,1,5,1,5,1 };
	combine(UCONDI_PATTERNS, extendABC(a31));
	int a32[] = { 2,5,1,3,1,5,4,5,1 };
	combine(UCONDI_PATTERNS, extendABC(a32));

	// Diagonal Branch

	int a33[] = { 5,1,0,0,1,1,1,0,5 };
	K.Mark_Pattern(a33);
	UCONDI_PATTERNS.push_back(K);
	int a34[] = { 0,1,5,1,1,0,5,0,1 };
	K.Mark_Pattern(a34);
	UCONDI_PATTERNS.push_back(K);
	int a35[] = { 5,0,1,1,1,0,0,1,5 };
	K.Mark_Pattern(a35);
	UCONDI_PATTERNS.push_back(K);
	int a36[] = { 1,0,5,0,1,1,5,1,0 };
	K.Mark_Pattern(a36);
	UCONDI_PATTERNS.push_back(K);
		
	return UCONDI_PATTERNS;
}

vector<Kernel> Algorithm::UCondi_K() {
	// extend abc to d
	//A2 B3 C4 D5

	vector<Kernel> UCONDI_PATTERNS;
	Kernel K(3, 3);

	// Spur
	int a1[] = { 0,0,0,0,1,0,0,0,1 };
	K.Mark_Pattern(a1);
	UCONDI_PATTERNS.push_back(K);
	int a2[] = { 0,0,0,0,1,0,1,0,0 };
	K.Mark_Pattern(a2);	
	UCONDI_PATTERNS.push_back(K);
	int a3[] = { 0,0,1,0,1,0,0,0,0 };
	K.Mark_Pattern(a3);
	UCONDI_PATTERNS.push_back(K);
	int a4[] = { 1,0,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a4);
	UCONDI_PATTERNS.push_back(K);
	
	

	// Single 4-connection
	int a5[] = { 0,0,0,0,1,0,0,1,0 };
	K.Mark_Pattern(a5);
	UCONDI_PATTERNS.push_back(K);
	int a6[] = { 0,0,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a6);
	UCONDI_PATTERNS.push_back(K);
	int a7[] = { 0,0,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a7);
	UCONDI_PATTERNS.push_back(K);
	int a8[] = { 0,1,0,0,1,0,0,0,0 };
	K.Mark_Pattern(a8);
	UCONDI_PATTERNS.push_back(K);

	// L Corner
	int a9[] = { 0,1,0,0,1,1,0,0,0 };
	K.Mark_Pattern(a9);
	UCONDI_PATTERNS.push_back(K);
	int a10[] = { 0,1,0,1,1,0,0,0,0 };
	K.Mark_Pattern(a10);
	UCONDI_PATTERNS.push_back(K);
	int a11[] = { 0,0,0,0,1,1,0,1,0 };
	K.Mark_Pattern(a11);
	UCONDI_PATTERNS.push_back(K);
	int a12[] = { 0,0,0,1,1,0,0,1,0 };
	K.Mark_Pattern(a12);
	UCONDI_PATTERNS.push_back(K);
			

	

	// Corner Cluster
	int a13[] = { 1,1,5,1,1,5,5,5,5 };
	K.Mark_Pattern(a13);
	UCONDI_PATTERNS.push_back(K);
	int a14[] = { 5,5,5,5,1,1,5,1,1 };
	K.Mark_Pattern(a14);
	UCONDI_PATTERNS.push_back(K);

	// Tee Branch
	int a15[] = { 5,1,5,1,1,1,5,5,5 };
	K.Mark_Pattern(a15);
	UCONDI_PATTERNS.push_back(K);
	int a16[] = { 5,1,5,1,1,5,5,1,5 };
	K.Mark_Pattern(a16);
	UCONDI_PATTERNS.push_back(K);
	int a17[] = { 5,5,5,1,1,1,5,1,5 };
	K.Mark_Pattern(a17);
	UCONDI_PATTERNS.push_back(K);
	int a18[] = { 5,1,5,5,1,1,5,1,5 };
	K.Mark_Pattern(a18);
	UCONDI_PATTERNS.push_back(K);
	


	// Vee Branch
	int a19[] = { 1,5,1,5,1,5,2,3,4 };
	combine(UCONDI_PATTERNS, extendABC(a19));
	int a20[] = { 1,5,4,5,1,3,1,5,2 };
	combine(UCONDI_PATTERNS, extendABC(a20));
	int a21[] = { 4,3,2,5,1,5,1,5,1 };
	combine(UCONDI_PATTERNS, extendABC(a21));
	int a22[] = { 2,5,1,3,1,5,4,5,1 };
	combine(UCONDI_PATTERNS, extendABC(a22));


	// Diagonal Branch

	int a33[] = { 5,1,0,0,1,1,1,0,5 };
	K.Mark_Pattern(a33);
	UCONDI_PATTERNS.push_back(K);
	int a34[] = { 0,1,5,1,1,0,5,0,1 };
	K.Mark_Pattern(a34);
	UCONDI_PATTERNS.push_back(K);
	int a35[] = { 5,0,1,1,1,0,0,1,5 };
	K.Mark_Pattern(a35);
	UCONDI_PATTERNS.push_back(K);
	int a36[] = { 1,0,5,0,1,1,5,1,0 };
	K.Mark_Pattern(a36);
	UCONDI_PATTERNS.push_back(K);

	return UCONDI_PATTERNS;

}

Bnode* Algorithm::PATTERNS_TREE(vector<Kernel> k) {
	Bnode* root = new Bnode(-1);
	Tree t1(root);
	for (int i = 0; i < k.size(); i++) {
		Kernel ke = k[i];
		queue<int> q;
		for (int m = 0; m < ke.get_height(); m++) {
			for (int n = 0; n < ke.get_width(); n++) {
				q.push(ke.get_data(m,n));
			}
		}
		q.push(1);
		Bnode* res = t1.create_tree(q);
		t1.reconstruct(res);
	}		
	return root;
}

void Algorithm::combine(vector<Kernel> &ori, vector<Kernel> add)
{
	for (int i = 0; i < add.size(); i++) {
		ori.push_back(add[i]);
	}
}

vector<Kernel> Algorithm::extendABC(int arr[]) {	
	const int size = 9;	
	Kernel K(3,3);
	vector<Kernel> res;
	int s[2][size];
	int s2[3][size];

	// extend abc to d
	//A2 B3 C4 D5

	int a = -1;
	int b = -1;
	int c = -1;
	for (int i = 0; i < size; i++) {
		if (arr[i] == 2) {
			a = i;
		}
		if (arr[i] == 3) {
			b = i;
		}
		if (arr[i] == 4) {
			c = i;
		}
	}
	if (c == -1) {		
		for (int i = 0; i < size; i++) {
			s[0][i] = arr[i];
			s[1][i] = arr[i];
		}
		s[0][a] = 1;
		s[0][b] = 5;
		s[1][a] = 0;
		s[1][b] = 1;	
		K.Mark_Pattern(s[0]);
		res.push_back(K);
		K.Mark_Pattern(s[1]);
		res.push_back(K);		
	}
	else {	
		for (int i = 0; i < size; i++) {
			s2[0][i] = arr[i];
			s2[1][i] = arr[i];
			s2[2][i] = arr[i];
		}
		s2[0][a] = 1;
		s2[0][b] = 5;
		s2[0][c] = 5;
		s2[1][a] = 0;
		s2[1][b] = 1;
		s2[1][c] = 5;
		s2[2][a] = 0;
		s2[2][b] = 0;
		s2[2][c] = 1;		
		K.Mark_Pattern(s2[0]);
		res.push_back(K);
		K.Mark_Pattern(s2[1]);
		res.push_back(K);
		K.Mark_Pattern(s2[2]);
		res.push_back(K);		
	}
	return res;
}

int Algorithm::comp(int i) {
	if (i == 0) {
		return 1;
	}
	else if (i == 1) {
		return 0;
	}
}

vector<vector<pair<int, int>>> Algorithm::cluster(vector<pair<int, int>> v) {
	Algorithm A;
	vector<pair<int, int>> foo = v;
	vector<vector<pair<int, int>>> res(11);
	for (int k = 0; k < 11; k++) {
		vector<pair<int,int>> foo2;		
		vector<double> dist(foo.size());
		for (int i = 0; i < foo.size(); i++) {
			dist[i] = A.distance(foo[0], foo[i]);			
		}
		vector<double> dummy = dist;
		sort(dummy.begin(), dummy.end());	
		for (int j = 0; j < foo.size(); j++) {
			if (dist[j] <= dummy[4]) {
				res[k].push_back(foo[j]);
			}
			else {
				foo2.push_back(foo[j]);
			}
		}
		foo = foo2;
	}	
	return res;
}

double Algorithm::distance(pair<int, int> a, pair<int, int> b) {
	return sqrt(pow(a.first - b.first,2) + pow(a.second - b.second,2));
}

