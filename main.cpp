#include "subterranean.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

bool testFullStateRecovery() {
	bool* secretState, * recoveredBits, * isConditionPos, * secondSecretState, * recoveredSecondBits, * isSecondConditionPos;
	secretState = new bool[SIZE];
	recoveredBits = new bool[SIZE];
	secondSecretState = new bool[SIZE];
	recoveredSecondBits = new bool[SIZE];
	isSecondConditionPos = new bool[SIZE];

	isConditionPos = new bool[SIZE];
	for (int i = 0; i < SIZE; i++) {
		secretState[i] = rand() % 2;
		recoveredBits[i] = false;
		isConditionPos[i] = false;
		isSecondConditionPos[i] = false;
		recoveredSecondBits[i] = false;
		secondSecretState[i] = secretState[i];
	}

	bool M0[32], M1[32];
	for (int i = 0; i < 32; i++) {
		M0[i] = 0;
		M1[i] = 0;
	}
	Subterranean sub;

	//inject M0
	for (int j = 0; j < 32; j++) {
		secondSecretState[subterranean_io_bits_0[j]] = secretState[subterranean_io_bits_0[j]] ^ M0[j];
	}
	secondSecretState[subterranean_io_bits_0[32]] ^= 1;

	//duplex M1
	sub.duplex(secondSecretState, M1, 32);

	for (int j = 0; j < 32; j++) {
		secondSecretState[subterranean_io_bits_0[j]] = secondSecretState[subterranean_io_bits_0[j]] ^ M1[j];
	}
	secondSecretState[subterranean_io_bits_0[32]] = secondSecretState[subterranean_io_bits_0[32]] ^ 1;

	sub.fullStateRecoveryType1(secretState, recoveredBits, isConditionPos);
	sub.fullStateRecoveryType2(secretState, recoveredBits, isConditionPos);
	sub.fullStateRecoveryType4(secretState, recoveredSecondBits, isSecondConditionPos);

	int t = 0;
	bool res = true;
	for (int i = 0; i < SIZE; i++) {
		if (isConditionPos[i] && secretState[i] != recoveredBits[i]) {
			cout << i << " is wrong!" << endl;
			res = false;
			//break;
		}

		if (isSecondConditionPos[i] && secondSecretState[i] != recoveredSecondBits[i]) {
			cout << i << " is wrong for type 4!" << endl;
			res = false;
			//break;
		}
	}

	delete[]secretState;
	delete[]recoveredBits;
	delete[]isConditionPos;
	delete[]secondSecretState;
	delete[]recoveredSecondBits;
	delete[]isSecondConditionPos;

	return res;
}

int main() {
	int choice;
	cout << "1 -> Distinguishing attack for 4 blank rounds (take 2^33 encryptions and will last long)" << endl;
	cout << "2 -> State recovery test (100000 experiments and will last for minutes)" << endl;
	cout << "Input your choice:";
	srand(time(NULL));

	cin >> choice;
	if (choice == 1) {
		Subterranean sub;
		sub.completeContructionDistinguisher(5);
	}
	else if(choice==2){
		int testTime = 100000;
		int successTime = 0;
		for (int i = 0; i < testTime; i++) {
			if (testFullStateRecovery()) {
				successTime++;
			}
		}
		cout << "Total experiment times:" << testTime << endl;
		cout << "Success times:" << successTime << endl;
	}
	return 0;
}
