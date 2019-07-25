#ifndef SUBTERRANEAN
#define SUBTERRANEAN

#include <vector>
#include "gurobi_c++.h"
using namespace std;

#define SIZE 257
#define GUESSED_NUM 18
typedef unsigned int UINT32;
typedef unsigned long long UINT64;

const unsigned int PI[257] = { 0, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 156, 168, 180, 192, 204, 216, 228, 240, 252, 7, 19, 31, 43, 55, 67, 79, 91, 103, 115, 127, 139, 151, 163, 175, 187, 199, 211, 223, 235, 247, 2, 14, 26, 38, 50, 62, 74, 86, 98, 110, 122, 134, 146, 158, 170, 182, 194, 206, 218, 230, 242, 254, 9, 21, 33, 45, 57, 69, 81, 93, 105, 117, 129, 141, 153, 165, 177, 189, 201, 213, 225, 237, 249, 4, 16, 28, 40, 52, 64, 76, 88, 100, 112, 124, 136, 148, 160, 172, 184, 196, 208, 220, 232, 244, 256, 11, 23, 35, 47, 59, 71, 83, 95, 107, 119, 131, 143, 155, 167, 179, 191, 203, 215, 227, 239, 251, 6, 18, 30, 42, 54, 66, 78, 90, 102, 114, 126, 138, 150, 162, 174, 186, 198, 210, 222, 234, 246, 1, 13, 25, 37, 49, 61, 73, 85, 97, 109, 121, 133, 145, 157, 169, 181, 193, 205, 217, 229, 241, 253, 8, 20, 32, 44, 56, 68, 80, 92, 104, 116, 128, 140, 152, 164, 176, 188, 200, 212, 224, 236, 248, 3, 15, 27, 39, 51, 63, 75, 87, 99, 111, 123, 135, 147, 159, 171, 183, 195, 207, 219, 231, 243, 255, 10, 22, 34, 46, 58, 70, 82, 94, 106, 118, 130, 142, 154, 166, 178, 190, 202, 214, 226, 238, 250, 5, 17, 29, 41, 53, 65, 77, 89, 101, 113, 125, 137, 149, 161, 173, 185, 197, 209, 221, 233, 245 };
const unsigned int subterranean_io_bits_0[33] = { 1, 176, 136, 35, 249, 134, 197, 234, 64, 213, 223, 184, 2, 95, 15, 70, 241, 11, 137, 211, 128, 169, 189, 111, 4, 190, 30, 140, 225, 22, 17, 165, 256 };
const unsigned int subterranean_io_bits_1[32] = { 256, 81, 121, 222, 8, 123, 60, 23, 193, 44, 34, 73, 255, 162, 242, 187, 16, 246, 120, 46, 129, 88, 68, 146, 253, 67, 227, 117, 32, 235, 240, 92 };

const UINT64 EXP[34] = {
	0x1,0x2,0x4,0x8,
	0x10,0x20,0x40,0x80,
	0x100,0x200,0x400,0x800,
	0x1000,0x2000,0x4000,0x8000,
	0x10000,0x20000,0x40000,0x80000,
	0x100000,0x200000,0x400000,0x800000,
	0x1000000,0x2000000,0x4000000,0x8000000,
	0x10000000,0x20000000,0x40000000,0x80000000,
	0x100000000,0x200000000
};

class Subterranean {
private:
	UINT32 IPI[SIZE];	
	int injection[32];
	int map[SIZE];
	bool K[4][SIZE];
	bool N[4][SIZE];
	int inverse_subterranean_io_bits_0[SIZE];
public:
	Subterranean();
	void permutation(bool state[]);
	void blank(bool state[], int rounds);
	void duplex(bool state[], bool sigma[], int injectSize);
	void extract(bool state[], bool value_out[32]);

	void completeContructionDistinguisher(int blankRounds);

	void readInjection();

	//full-state recovery attack
	bool recoverSingleBitType1(bool  secretState[], int v0, int v1[], int size, int round);
	void fullStateRecoveryType1(bool secretState[],bool recoveredValue[],bool isConditionPos[]);//Start recovering full state

	bool recoverSingleBitType2(bool  secretState[], int v0, int v1);
	void fullStateRecoveryType2(bool secretState[], bool recoveredValue[],bool isConditionPos[]);//Start recovering full state
};

#endif // SUBTERRANEAN
