#include "pch.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include <iostream>

using namespace std;

typedef struct{
	int Data[4][4] = { 0 };		//Data
	int Line[4] = { 0 };		//line existence
	int Row[4] = { 0 };			//row existence
}Matrix;

//Verified
void random(Matrix &M) {
	int x = rand() % 4;
	int y = rand() % 4;
	if (M.Data[x][y] == 0) {
		//TESTING DATA
		M.Data[x][y] = 2;
		///REAL DATA
		///M.Data[x][y] = (rand()%2 + 1) * 2;
		M.Line[x]++;
		M.Row[y]++;
	}
	else {
		random(M);
	}
}
//Verified
void initialMatrix(Matrix &M) {
	for (int i = 0; i < 3; i++) {
		random(M);
	}
}
//Verified
void cmpR(Matrix &M, int &iR) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (M.Data[i][j] != M.Data[i][j + 1]) {
				iR++;
			}
		}
	}
}
//Verified
void cmpD(Matrix &M, int &iD) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (M.Data[i][j] != M.Data[i + 1][j]) {
				iD++;
			}
		}
	}
}
//Verified
bool gameOver(Matrix &M) {
	int iR = 0;
	int iD = 0;
	cmpR(M, iR);
	cmpD(M, iD);
	if (iR + iD == 24) {
		cout << "\n\t   Game Over!!" << endl;
		system("pause");
		return true;
	}
	else{
		return false;
	}
}
//********** A Direction ************
//Verified
void moveA(Matrix &M) {
	for (int i = 0; i < 4; i++) {
		int iLoc = 0;
		if (M.Line[i] > 0) {
			for (int j = 0; j < 4; j++) {
				if (M.Data[i][j] != 0) {
					if (iLoc != j) {
						M.Data[i][iLoc] = M.Data[i][j];
						M.Data[i][j] = 0;
						M.Row[iLoc]++;
						M.Row[j]--;
					}
					iLoc++;
				}
			}
		}
	}
}
//Verified
void combA_2(Matrix &M, int &i) {
	for (int j = 0; j < 3; j++) {
		//(int)k as an increment
		for (int k = 1; k < 4 - j; k++) {
			if (M.Data[i][j] != 0 && M.Data[i][j + k] != 0) {
				if (M.Data[i][j] == M.Data[i][j + k]) {
					M.Data[i][j] += M.Data[i][j + k];
					M.Data[i][j + k] = 0;
					M.Line[i]--;
					M.Row[j + k]--;
				}
			}
		}
	}
}
//Verified
void combA_3(Matrix &M, int &i) {
	for (int j = 0; j < 3; j++) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i][j + 1] != 0) {
			if (M.Data[i][j] == M.Data[i][j + 1]) {
				M.Data[i][j] += M.Data[i][j + 1];
				M.Data[i][j + 1] = 0;
				M.Line[i]--;
				M.Row[j + 1]--;
			}
		}
		//Interval Situation
		if (j > 0) {
			if (M.Data[i][j] == 0) {
				if (M.Data[i][j - 1] != 0 && M.Data[i][j + 1] != 0) {
					if (M.Data[i][j - 1] == M.Data[i][j + 1]) {
						M.Data[i][j - 1] += M.Data[i][j + 1];
						M.Data[i][j + 1] = 0;
						M.Line[i]--;
						M.Row[j + 1]--;
					}
				}
			}
		}
	}
}
//Verified
void combA_4(Matrix &M, int &i) {
	for (int j = 0; j < 3; j++) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i][j + 1] != 0) {
			if (M.Data[i][j] == M.Data[i][j + 1]) {
				M.Data[i][j] += M.Data[i][j + 1];
				M.Data[i][j + 1] = 0;
				M.Line[i]--;
				M.Row[j + 1]--;
			}
		}
	}
}
//Verified
void combineA(Matrix &M) {
	for (int i = 0; i < 4; i++) {
		switch (M.Line[i]) {
		case 0:
		case 1:
			break;
		case 2:
			combA_2(M, i);
			break;
		case 3:
			combA_3(M, i);
			break;
		case 4:
			combA_4(M, i);
			break;
		default:
			break;
		}
	}
}
//********** D Direction ************
//Verified
void moveD(Matrix &M) {
	for (int i = 0; i < 4; i++) {
		int iLoc = 3;
		if (M.Line[i] > 0) {
			for (int j = 3; j >=0; j--) {
				if (M.Data[i][j] != 0) {
					if (iLoc != j) {
						M.Data[i][iLoc] = M.Data[i][j];
						M.Data[i][j] = 0;
						M.Row[iLoc]++;
						M.Row[j]--;
					}
					iLoc--;
				}
			}
		}
	}
}
//Verified
void combD_2(Matrix &M, int &i) {
	for (int j = 3; j > 0; j--) {
		//(int)k as an increment
		for (int k = 1; k < j + 1; k++) {
			if (M.Data[i][j] != 0 && M.Data[i][j - k] != 0) {
				if (M.Data[i][j] == M.Data[i][j - k]) {
					M.Data[i][j] += M.Data[i][j - k];
					M.Data[i][j - k] = 0;
					M.Line[i]--;
					M.Row[j - k]--;
				}
			}
		}
	}
}
//Verified
void combD_3(Matrix &M, int &i) {
	for (int j = 3; j > 0; j--) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i][j - 1] != 0) {
			if (M.Data[i][j] == M.Data[i][j - 1]) {
				M.Data[i][j] += M.Data[i][j - 1];
				M.Data[i][j - 1] = 0;
				M.Line[i]--;
				M.Row[j - 1]--;
			}
		}
		//Interval Situation
		if (j < 3) {
			if (M.Data[i][j] == 0) {
				if (M.Data[i][j - 1]!=0 && M.Data[i][j + 1]!=0)	{
					if (M.Data[i][j - 1] == M.Data[i][j + 1]) {
						M.Data[i][j + 1] += M.Data[i][j - 1];
						M.Data[i][j - 1] = 0;
						M.Line[i]--;
						M.Row[j - 1]--;
					}
				}
			}
		}
	}
}
//Verified
void combD_4(Matrix &M, int &i) {
	for (int j = 3; j > 0; j--) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i][j - 1] != 0) {
			if (M.Data[i][j] == M.Data[i][j - 1]) {
				M.Data[i][j] += M.Data[i][j - 1];
				M.Data[i][j - 1] = 0;
				M.Line[i]--;
				M.Row[j - 1]--;
			}
		}
	}
}
//Verified
void combineD(Matrix &M) {
	for (int i = 0; i < 4; i++) {
		switch (M.Line[i]) {
		case 0:
		case 1:
			break;
		case 2:
			combD_2(M, i);
			break;
		case 3:
			combD_3(M, i);
			break;
		case 4:
			combD_4(M, i);
			break;
		default:
			break;
		}
	}
}
//********** W Direction ************
//Verified
void moveW(Matrix &M) {
	for (int j = 0; j < 4; j++) {
		int iLoc = 0;
		if (M.Row[j] > 0) {
			for (int i = 0; i < 4; i++) {
				if (M.Data[i][j] != 0) {
					if (iLoc != i) {
						M.Data[iLoc][j] = M.Data[i][j];
						M.Data[i][j] = 0;
						M.Line[iLoc]++;
						M.Line[i]--;
					}	
					iLoc++;
				}
			}
		}
	}
}
//Verified
void combW_2(Matrix &M, int &j) {
	for (int i = 0; i < 3; i++) {
		//(int)k as an increment
		for (int k = 1; k < 4 - i; k++) {
			if (M.Data[i][j] != 0 && M.Data[i + k][j] != 0) {
				if (M.Data[i][j] == M.Data[i + k][j]) {
					M.Data[i][j] += M.Data[i + k][j];
					M.Data[i + k][j] = 0;
					M.Row[j]--;
					M.Line[i + k]--;
				}
			}
		}
	}
}
//Verified
void combW_3(Matrix &M, int &j) {
	for (int i = 0; i < 3; i++) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i + 1][j] != 0) {
			if (M.Data[i][j] == M.Data[i + 1][j]) {
				M.Data[i][j] += M.Data[i + 1][j];
				M.Data[i + 1][j] = 0;
				M.Row[j]--;
				M.Line[i + 1]--;
			}
		}
		//Interval Situation
		if (i > 0) {
			if (M.Data[i][j] == 0) {
				if (M.Data[i - 1][j] != 0 && M.Data[i + 1][j] != 0) {
					if (M.Data[i - 1][j] == M.Data[i + 1][j]) {
						M.Data[i - 1][j] += M.Data[i + 1][j];
						M.Data[i + 1][j] = 0;
						M.Row[j]--;			
						M.Line[i + 1]--;
					}
				}
			}
		}
	}
}
//Verified
void combW_4(Matrix &M, int &j) {
	for (int i = 0; i < 3; i++) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i + 1][j] != 0) {
			if (M.Data[i][j] == M.Data[i + 1][j]) {
				M.Data[i][j] += M.Data[i + 1][j];
				M.Data[i + 1][j] = 0;
				M.Row[j]--;
				M.Line[i + 1]--;
			}
		}
	}
}
//Verified
void combineW(Matrix &M) {
	for (int j = 0; j < 4; j++) {
		switch (M.Row[j]) {
		case 0:
		case 1:
			break;
		case 2:
			combW_2(M, j);
			break;
		case 3:
			combW_3(M, j);
			break;
		case 4:
			combW_4(M, j);
			break;
		default:
			break;
		}
	}
}
//********** S Direction ************
//Verified
void moveS(Matrix &M) {
	for (int j = 0; j < 4; j++) {
		int iLoc = 3;
		if (M.Row[j] > 0) {
			for (int i = 3; i >= 0; i--) {
				if (M.Data[i][j] != 0) {
					if (iLoc != i) {
						M.Data[iLoc][j] = M.Data[i][j];
						M.Data[i][j] = 0;
						M.Line[iLoc]++;
						M.Line[i]--;
					}
					iLoc--;
				}
			}
		}
	}
}
//Verified
void combS_2(Matrix &M, int &j) {
	for (int i = 3; i >= 0; i--) {
		//(int)k as an increment
		for (int k = 1; k < i + 1; k++) {
			if (M.Data[i][j] != 0 && M.Data[i - k][j] != 0) {
				if (M.Data[i][j] == M.Data[i - k][j]) {
					M.Data[i][j] += M.Data[i - k][j];
					M.Data[i - k][j] = 0;
					M.Row[j]--;
					M.Line[i - k]--;
				}
			}
		}
	}
}
//Verified
void combS_3(Matrix &M, int &j) {
	for (int i = 3; i > 0; i--) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i - 1][j] != 0) {
			if (M.Data[i][j] == M.Data[i - 1][j]) {
				M.Data[i][j] += M.Data[i - 1][j];
				M.Data[i - 1][j] = 0;
				M.Row[j]--;
				M.Line[i - 1]--;
			}
		}
		//Interval Situation
		if (i < 3) {
			if (M.Data[i][j] == 0) {
				if (M.Data[i - 1][j] != 0 && M.Data[i + 1][j] != 0) {
					if (M.Data[i - 1][j] == M.Data[i + 1][j]) {
						M.Data[i - 1][j] += M.Data[i + 1][j];
						M.Data[i + 1][j] = 0;
						M.Row[j]--;
						M.Line[i + 1]--;
					}
				}
			}
		}
	}
}
//Verified
void combS_4(Matrix &M, int &j) {
	for (int i = 0; i < 3; i++) {
		//Adjacent Situation
		if (M.Data[i][j] != 0 && M.Data[i - 1][j] != 0) {
			if (M.Data[i][j] == M.Data[i - 1][j]) {
				M.Data[i][j] += M.Data[i - 1][j];
				M.Data[i - 1][j] = 0;
				M.Row[j]--;
				M.Line[i - 1]--;
			}
		}
	}
}
//Verified
void combineS(Matrix &M) {
	for (int j = 0; j < 4; j++) {
		switch (M.Row[j]) {
		case 0:
		case 1:
			break;
		case 2:
			combS_2(M, j);
			break;
		case 3:
			combS_3(M, j);
			break;
		case 4:
			combS_4(M, j);
			break;
		default:
			break;
		}
	}
}

//Verified
void operations(Matrix &M) {
	char opt;
	cin >> opt;
	cin.get();
	switch (opt) {
	case 'w':
	case 'W':
		combineW(M);
		moveW(M);
		break;
	case 'a':
	case 'A':
		combineA(M);
		moveA(M);
		break;
	case 's':
	case 'S':
		combineS(M);
		moveS(M);
		break;
	case 'd':
	case 'D':
		combineD(M);
		moveD(M);
		break;
	default:
		break;
	}
}
//Verified
void printGrp(Matrix &M) {
	system("CLS");
	cout << "\t1024" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "*************************" << endl;
		for (int j = 0; j < 4; j++) {
			cout << "*" << setw(5) << M.Data[i][j];
		}
		cout << "*" << endl;
	}
	cout << "*************************" << endl;
	cout << "输入WASD进行操作:";
}
//Verified
int main(){
	Matrix M;
	srand(time(NULL));
	initialMatrix(M);
	printGrp(M);
	while(!gameOver(M)) {
		operations(M);
		random(M);
		printGrp(M);
	}
}