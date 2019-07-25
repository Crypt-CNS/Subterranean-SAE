#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include "gurobi_c++.h"
#include "subterranean.h"
using namespace std;

Subterranean::Subterranean() {
	//compute the inverse of PI
	for (int i = 0; i < SIZE; i++) {
		IPI[PI[i]] = i;
	}

	for (int i = 0; i < SIZE; i++) {
		inverse_subterranean_io_bits_0[i] = SIZE;
	}
	for (int i = 0; i < 33; i++) {
		inverse_subterranean_io_bits_0[subterranean_io_bits_0[i]] = i;
	}
}

void Subterranean::permutation(bool state[]){
	bool temp_state[SIZE];
	bool temp_0, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7;
	int i = 0;
	/* Chi step*/
	for (i = 0; i < (SIZE - 2); i++) {
		/*if (i == 197 || i == 200 || i == 205) {
			//system("pause");
		}*/
		temp_state[i] = state[i] ^ ((1 ^ state[i + 1]) & state[i + 2]);
	}
	temp_state[i] = state[i] ^ ((1 ^ state[i + 1]) & state[0]);
	i++;
	temp_state[i] = state[i] ^ ((1 ^ state[0]) & state[1]);

	/* Iota step*/
	temp_state[0] ^= 1;

	/* Theta step*/
	temp_0 = temp_state[0] ^ temp_state[3] ^ temp_state[8];
	temp_1 = temp_state[1] ^ temp_state[4] ^ temp_state[9];
	temp_2 = temp_state[2] ^ temp_state[5] ^ temp_state[10];
	temp_3 = temp_state[3] ^ temp_state[6] ^ temp_state[11];
	temp_4 = temp_state[4] ^ temp_state[7] ^ temp_state[12];
	temp_5 = temp_state[5] ^ temp_state[8] ^ temp_state[13];
	temp_6 = temp_state[6] ^ temp_state[9] ^ temp_state[14];
	temp_7 = temp_state[7] ^ temp_state[10] ^ temp_state[15];
	for (i = 8; i < (SIZE - 8); i++) {
		temp_state[i] = temp_state[i] ^ temp_state[i + 3] ^ temp_state[i + 8];
	}
	temp_state[i] = temp_state[i] ^ temp_state[i + 3] ^ temp_state[0];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[i + 3] ^ temp_state[1];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[i + 3] ^ temp_state[2];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[i + 3] ^ temp_state[3];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[i + 3] ^ temp_state[4];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[0] ^ temp_state[5];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[1] ^ temp_state[6];
	i++;
	temp_state[i] = temp_state[i] ^ temp_state[2] ^ temp_state[7];
	temp_state[0] = temp_0;
	temp_state[1] = temp_1;
	temp_state[2] = temp_2;
	temp_state[3] = temp_3;
	temp_state[4] = temp_4;
	temp_state[5] = temp_5;
	temp_state[6] = temp_6;
	temp_state[7] = temp_7;


	/* Pi step*/
	for (i = 0; i < (SIZE); i++) {
		/*if (i == 51) {
			system("pause");
		}*/
		state[i] = temp_state[PI[i]];
	}
}

void Subterranean::blank(bool state[SIZE], int rounds) {
	for (int i = 0; i < rounds; i++) {
		duplex(state, NULL, 0);
	}
}

void Subterranean::duplex(bool state[], bool sigma[], int injectSize) {
	permutation(state);
	/* sbar <= sbar + sigma */
	int j = 0;
	for (j = 0; j < injectSize; j++) {
		state[subterranean_io_bits_0[j]] ^= sigma[j];
	}
	/* sbar <= sbar + (1||0*) */
	state[subterranean_io_bits_0[j]] ^= 1;
}

void Subterranean::extract(bool state[], bool value_out[32]) {
	unsigned char j;
	/* value_out <= extract */
	for (j = 0; j < 32; j++) {
		value_out[j] = state[subterranean_io_bits_0[j]] ^ state[subterranean_io_bits_1[j]];
	}
}

void Subterranean::completeContructionDistinguisher(int blankRounds) {
	//generate a rand starting state
	bool state[SIZE];
	for (int i = 0; i < SIZE; i++) {
		if (rand() % 2 == 0) {
			state[i] = 0;
		}
		else {
			state[i] = 1;
		}
	}

	bool sigmal3[33];
	bool sigmal2[33];
	bool message[32];
	bool output[32];
	bool sum[32];
	//At first, duplex
	//Initilaize sigmal2 and sigmal3
	for (int i = 0; i < 32; i++) {
		sigmal2[i] = 0;
		sigmal3[i] = 0;
		message[i] = 0;
		output[i] = 0;
		sum[i] = 0;
	}
	sigmal2[32] = 0;
	sigmal3[32] = 0;

	int inver_subterranean_io_bits_0[SIZE];
	for (int i = 0; i < 32; i++) {
		inver_subterranean_io_bits_0[subterranean_io_bits_0[i]] = i;
	}

	bool tmpState[SIZE];
	int cubePos[29] = { 176, 35, 249, 134, 197, 234, 64, 213, 223, 184, 2, 95, 15, 70, 241, 11, 137, 211, 128, 169, 111, 4, 190, 30, 140, 225, 22, 17, 165};
	int cubePos1[4] = { 30,111,137,223 };
	for (UINT64 i = 0; i < EXP[33]; i++) {
		for (int j = 0; j < 29; j++) {
			sigmal3[inver_subterranean_io_bits_0[cubePos[j]]] = (i >> j) & 0x1;
		}
		for (int j = 0; j < 4; j++) {
			sigmal2[inver_subterranean_io_bits_0[cubePos1[j]]] = (i >> (j+29)) & 0x1;
		}

		for (int j = 0; j < SIZE; j++) {
			tmpState[j] = state[j];
		}
		duplex(tmpState, sigmal2, 33);//N2
		duplex(tmpState, sigmal3, 33);//N3
		duplex(tmpState, message, 0);//NULL
		blank(tmpState, 4);//Blank
		duplex(tmpState, message, 0);//NULL Associated data
		extract(tmpState, output);//Output

		for (int j = 0; j < 32; j++) {
			sum[j] = sum[j] ^ output[j];
		}
	}
	cout << endl;
	for (int i = 0; i < 32; i++) {
		cout << sum[i];
	}
	cout << endl;
}

void Subterranean::readInjection() {
	ifstream inFile("injection.txt");
	vector<int> injectPos;
	injectPos.clear();

	int index, value;
	while (inFile >> index) {
		inFile >> value;
		injectPos.push_back(value);
	}

	sort(injectPos.begin(), injectPos.end());

	for (int i = 0; i < injectPos.size(); i++) {
		injection[i] = injectPos[i];
	}

	for (int i = 0; i < injectPos.size() - 1; i++) {
		map[injectPos[i]] = i;
	}
}

//Start recovering full state
bool Subterranean::recoverSingleBitType1(bool  secretState[], int v0Pos, int v1Pos[], int size, int round) {
	//v0 is the conditional variable in M0
    //v1 is the cube variable in M1
    //conditionPos denotes the position of bit which influence the multiplying relation between v0 and v1

	bool* startState, * tmpState;
	startState = new bool[SIZE];
	tmpState = new bool[SIZE];

	for (int i = 0; i < SIZE; i++) {
		startState[i] = secretState[i];
		tmpState[i] = startState[i];
	}

	bool M0[32], M1[32], M2[32];
	bool sum[32], output[32];
	for (int i = 0; i < 32; i++) {
		M0[i] = 0;
		M1[i] = 0;
		M2[i] = 0;
		sum[i] = 0;
	}

	for (UINT32 i = 0; i < EXP[size + 1]; i++) {
		M0[inverse_subterranean_io_bits_0[v0Pos]] = i & 0x1;

		for (int k = 0; k < size; k++) {
			M1[inverse_subterranean_io_bits_0[v1Pos[k]]] = (i >> (1 + k)) & 0x1;
		}

		for (int j = 0; j < SIZE; j++) {
			startState[j] = tmpState[j];
		}

		//inject M0
		for (int j = 0; j < 32; j++) {
			startState[subterranean_io_bits_0[j]] ^= M0[j];
		}
		startState[subterranean_io_bits_0[32]] ^= 1;

		duplex(startState, M1, 32);
		duplex(startState, M2, 32);

		if (round == 2) {
			duplex(startState, M2, 32);
		}
		extract(startState, output);

		for (int j = 0; j < 32; j++) {
			sum[j] = sum[j] ^ output[j];
		}
	}
	delete[]startState;
	delete[]tmpState;

	for (int i = 0; i < 32; i++) {
		if (sum[i]) {
			return false;
		}
	}
	return true;
}

bool Subterranean::recoverSingleBitType2(bool  secretState[], int v0Pos, int v1Pos) {
	//v0 is the conditional variable in M0
	//v1 is the cube variable in M1
	//conditionPos denotes the position of bit which influence the multiplying relation between v0 and v1

	int inverse_subterranean_io_bits_0[SIZE];
	for (int i = 0; i < SIZE; i++) {
		inverse_subterranean_io_bits_0[i] = SIZE;
	}
	for (int i = 0; i < 33; i++) {
		inverse_subterranean_io_bits_0[subterranean_io_bits_0[i]] = i;
	}

	bool* startState, * tmpState;
	startState = new bool[SIZE];
	tmpState = new bool[SIZE];

	for (int i = 0; i < SIZE; i++) {
		startState[i] = secretState[i];
		tmpState[i] = startState[i];
	}

	bool M0[32], M1[32], M2[32];
	bool sum[32], output[32];
	bool wholeSum[SIZE];
	for (int i = 0; i < 32; i++) {
		M0[i] = 0;
		M1[i] = 0;
		M2[i] = 0;
		sum[i] = 0;
	}

	for (UINT32 i = 0; i < 4; i++) {
		M0[inverse_subterranean_io_bits_0[v0Pos]] = i & 0x1;
		M2[inverse_subterranean_io_bits_0[v1Pos]] = (i >> 1) & 0x1;

		for (int j = 0; j < SIZE; j++) {
			startState[j] = tmpState[j];
		}

		//inject M0
		for (int j = 0; j < 32; j++) {
			startState[subterranean_io_bits_0[j]] ^= M0[j];
		}
		startState[subterranean_io_bits_0[32]] ^= 1;

		duplex(startState, M1, 32);
		duplex(startState, M2, 32);
		duplex(startState, M1, 32);
		extract(startState, output);

		for (int j = 0; j < 32; j++) {
			sum[j] = sum[j] ^ output[j];
		}
	}
	delete[]startState;
	delete[]tmpState;

	for (int i = 0; i < 32; i++) {
		if (sum[i]) {
			return false;
		}
	}
	return true;
}

void Subterranean::fullStateRecoveryType1(bool secretState[], bool recoveredValue[],bool isConditionPos[]) {
	//read parameter
	int v0;
	int arra[2];
	int size;
	int round;
	int conditionPos;
	int value;
	int parSize = 0;
	bool flag = true;

	ifstream readPar("parameter1.txt");
	readPar >> parSize;
	for (int i = 0; i < parSize; i++) {
		readPar >> v0;
		readPar >> size;
		if (size == 1) {
			readPar >> arra[0];
			round = 1;
		}
		else {
			readPar >> arra[0] >> arra[1];
			round = 2;
		}
		readPar >> conditionPos >> value;

		if (conditionPos == 256) {
			value = value ^ 1;
		}
		isConditionPos[conditionPos] = true;

		flag = recoverSingleBitType1(secretState,v0, arra, size, round);
		if (flag) {//Conditiona holds!
			recoveredValue[conditionPos] = value;
		}
		else {
			recoveredValue[conditionPos] = value ^ 1;
		}
	}
}

void Subterranean::fullStateRecoveryType2(bool secretState[], bool recoveredValue[],bool isConditionPos[]) {
	//read parameter
	int v0;
	int v1;
	int size;
	int round;
	int conditionPos;
	int value;
	int parSize = 0;
	bool flag = true;

	ifstream readPar("parameter2.txt");
	readPar >> parSize;
	for (int i = 0; i < parSize; i++) {
		readPar >> v0 >> v1;
		readPar >> conditionPos >> value;

		if (conditionPos == 256) {
			value = value ^ 1;
		}
		isConditionPos[conditionPos] = true;

		flag = recoverSingleBitType2(secretState, v0, v1);
		if (flag) {//Conditiona holds!
			recoveredValue[conditionPos] = value;
		}
		else {
			recoveredValue[conditionPos] = value ^ 1;
		}
	}
}