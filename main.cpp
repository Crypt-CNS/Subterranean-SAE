#include "subterranean.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

bool testFullStateRecovery() {
	bool* secretState,*recoveredBits,*isConditionPos;
	secretState = new bool[SIZE];
	recoveredBits = new bool[SIZE];
	isConditionPos = new bool[SIZE];
	for (int i = 0; i < SIZE; i++) {
		secretState[i] = rand() % 2;
		recoveredBits[i] = false;
		isConditionPos[i] = false;
	}
	Subterranean sub;
	sub.fullStateRecoveryType1(secretState,recoveredBits,isConditionPos);
	sub.fullStateRecoveryType2(secretState, recoveredBits,isConditionPos);
	bool res = true;
	for (int i = 0; i < SIZE; i++) {
		if (isConditionPos[i] && secretState[i] != recoveredBits[i]) {
			cout << i << " is wrong!" << endl;
			res = false;
			break;
		}
	}

	delete[]secretState;
	delete[]recoveredBits;
	delete[]isConditionPos;

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