//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <tchar.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "patient.h"
//---------------------------------------------------------------------------
#pragma argsused

struct dich {
	std::string name;
	int mas[2][2];
};

void koefPierson(std::vector<patient> casefile, float matrix[][8], int matrixSt[][8]);
void dichotomyCase(std::vector<patient> casefile, std::vector<patient> &caseDich);
void soprDich(std::vector<patient> &caseDich, dich mas[36]);

int _tmain(int argc, _TCHAR* argv[])
{
	std::system("chcp 1251");

	dich mas[36];
	for(int i = 0; i < 36; i++) {
		mas[i].mas[0][0] = 0;
		mas[i].mas[0][1] = 0;
		mas[i].mas[1][0] = 0;
		mas[i].mas[1][1] = 0;
	}
	u_int id;
	float tglobulin;
	float msom_gen;
	float iglobulin_A;
	float iglobulin_M;
	float iglobulin_G;
	float imunCom;
	float lizocim;
	float actComp;
	float res;
	float matrixPierson[8][8];
	int matrixSt[8][8];
	std::cout << "Input the path to the file: ";
	std::string filename;
	std::cin >> filename;
	std::vector<patient> casefile;
	std::vector<patient> caseDichotomy;

	std::ifstream readfile(filename.c_str(), std::ios_base::in);
	if(readfile.is_open()) {
	do {
		//std::getline(readfile, id, "\t");
		readfile >> id >> tglobulin >> msom_gen >> iglobulin_A >>
			  iglobulin_M >> iglobulin_G >> imunCom >> lizocim >> actComp >> res;
		casefile.push_back(patient(id, tglobulin, msom_gen, iglobulin_A,
			  iglobulin_M, iglobulin_G, imunCom, lizocim, actComp, res));   //set due to output from file
	} while (!readfile.eof( ));
	readfile.close();
	std::cout << "----------------------------------------------" << std::endl;
	koefPierson(casefile, matrixPierson, matrixSt);
	dichotomyCase(casefile, caseDichotomy);

	} else {
		MessageBox(NULL, "?????? ???????? ?????.", "Error", MB_OK);
	}
	return 0;
}
//---------------------------------------------------------------------------

void koefPierson(std::vector<patient> casefile, float matrix[8][8], int matrixSt[][8]) {

	for(int i = 0; i < 8; i++) {
		for(int k = 0; k < 8; k++) {
			if(i == k) {
				matrix[i][k] = 1;
				matrixSt[i][k] = 1;
			}
		}
	}
	double Stkr = 1.975; //???????? ????????? ??? ??????? ???-?? ?????? ? ??????????? 0,05

	double xGlobulin = 0; //sum of first param
	double xMsom_gen = 0; //sum of second param
	double xIglobulin_A = 0;
	double xIglobulin_M = 0;
	double xIglobulin_G = 0;
	double xImunCom = 0;
	double xLizocim = 0;
	double xActComp = 0; //sum of eigth param

	double mulSum;
	double mul = 0;

	double sqrtRes;
	double powxGlobulin = 0;
	double powxMsom_gen = 0;
	double powxIglobulin_A = 0;
	double powxIglobulin_M = 0;
	double powxIglobulin_G = 0;
	double powxImunCom = 0;
	double powxLizocim = 0;
	double powxActComp = 0;

	for(int i = 0; i < (casefile.size() - 1); i++) {
		xGlobulin += casefile[i].getTglobulin();
		xMsom_gen += casefile[i].getMsom_gen();
		xIglobulin_A += casefile[i].getIglobulin_A();
		xIglobulin_M += casefile[i].getIglobulin_M();
		xIglobulin_G += casefile[i].getIglobulin_G();
		xImunCom += casefile[i].getImunCom();
		xLizocim += casefile[i].getLizocim();
		xActComp += casefile[i].getActComp();

		powxGlobulin += casefile[i].getTglobulin() * casefile[i].getTglobulin();
		powxMsom_gen += casefile[i].getMsom_gen() * casefile[i].getMsom_gen();
		powxIglobulin_A += casefile[i].getIglobulin_A() * casefile[i].getIglobulin_A();
		powxIglobulin_M += casefile[i].getIglobulin_M() * casefile[i].getIglobulin_M();
		powxIglobulin_G += casefile[i].getIglobulin_G() * casefile[i].getIglobulin_G();
		powxImunCom += casefile[i].getImunCom() * casefile[i].getImunCom();
		powxLizocim += casefile[i].getLizocim() * casefile[i].getLizocim();
		powxActComp += casefile[i].getActComp() * casefile[i].getActComp();
	}

	//size*sum(x(param)^2)
	powxGlobulin *= (casefile.size() - 1);
	powxMsom_gen *= (casefile.size() - 1);
	powxIglobulin_A *= (casefile.size() - 1);
	powxIglobulin_M *= (casefile.size() - 1);
	powxIglobulin_G *= (casefile.size() - 1);
	powxImunCom *= (casefile.size() - 1);
	powxLizocim *= (casefile.size() - 1);
	powxActComp *= (casefile.size() - 1);

	//1-2 parameters
	//sum(xGlobulin)*sum(xMsom_gen)
	mulSum = xGlobulin * xMsom_gen;

	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getMsom_gen();
	}

	//size*sum(xGlobulin*xMsom_gen)
	mul *= (casefile.size() - 1);

	
	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxMsom_gen - pow(xMsom_gen, 2)));
	double teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	double tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][1] = matrix[1][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][1] = matrixSt[1][0] = 0;
	} else {
		if(matrix[0][1] < 0) {
			matrixSt[0][1] = matrixSt[1][0] = -1;
		} else {
			matrixSt[0][1] = matrixSt[1][0] = 1;
		}
	}



	//1-3 parameters
	//sum(xGlobulin)*sum(xIglobulin_A)
	mulSum = xGlobulin * xIglobulin_A;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getIglobulin_A();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxIglobulin_A - pow(xIglobulin_A, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][2] = matrix[2][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][2] = matrixSt[2][0] = 0;
	} else {
		if(matrix[0][2] < 0) {
			matrixSt[0][2] = matrixSt[2][0] = -1;
		} else {
			matrixSt[0][2] = matrixSt[2][0] = 1;
		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//1-4 parameters
	//sum(xGlobulin)*sum(xIglobulin_M)
	mulSum = xGlobulin * xIglobulin_M;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getIglobulin_M();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxIglobulin_M - pow(xIglobulin_M, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][3] = matrix[3][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][3] = matrixSt[3][0] = 0;
	} else {
		if(matrix[0][3] < 0) {
			matrixSt[0][3] = matrixSt[3][0] = -1;
		} else {
			matrixSt[0][3] = matrixSt[3][0] = 1;
		}
	}


	//1-5 parameters
	//sum(xGlobulin)*sum(xIglobulin_G)
	mulSum = xGlobulin * xIglobulin_G;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getIglobulin_G();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxIglobulin_G - pow(xIglobulin_G, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][4] = matrix[4][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][4] = matrixSt[4][0] = 0;
	} else {
		if(matrix[0][4] < 0) {
			matrixSt[0][4] = matrixSt[4][0] = -1;
		} else {
			matrixSt[0][4] = matrixSt[4][0] = 1;
		}
	}

	//1-6 parameters
	//sum(xGlobulin)*sum(xImunCom)
	mulSum = xGlobulin * xImunCom;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getImunCom();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxImunCom - pow(xImunCom, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][5] = matrix[5][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][5] = matrixSt[5][0] = 0;
	} else {
		if(matrix[0][5] < 0) {
			matrixSt[0][5] = matrixSt[5][0] = -1;
		} else {
			matrixSt[0][5] = matrixSt[5][0] = 1;
		}
	}

	//1-7 parameters
	//sum(xGlobulin)*sum(xLizocim)
	mulSum = xGlobulin * xLizocim;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getLizocim();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxLizocim - pow(xLizocim, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][6] = matrix[6][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][6] = matrixSt[6][0] = 0;
	} else {
		if(matrix[0][6] < 0) {
			matrixSt[0][6] = matrixSt[6][0] = -1;
		} else {
			matrixSt[0][6] = matrixSt[6][0] = 1;
		}
	}


	//1-8 parameters
	//sum(xGlobulin)*sum(xActComp)
	mulSum = xGlobulin * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getTglobulin() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxGlobulin - pow(xGlobulin, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[0][7] = matrix[7][0] = teta;
	if(tkr < Stkr) {
		matrixSt[0][7] = matrixSt[7][0] = 0;
	} else {
		if(matrix[0][7] < 0) {
			matrixSt[0][7] = matrixSt[7][0] = -1;
		} else {
			matrixSt[0][7] = matrixSt[7][0] = 1;
		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//2-3 parameters
	//sum(xMsom_gen)*sum(xIglobulin_A)
	mulSum = xMsom_gen * xIglobulin_A;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getMsom_gen() * casefile[i].getIglobulin_A();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxMsom_gen - pow(xMsom_gen, 2)) * (powxIglobulin_A - pow(xIglobulin_A, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[1][2] = matrix[2][1] = teta;
	if(tkr < Stkr) {
		matrixSt[1][2] = matrixSt[2][1] = 0;
	} else {
		if(matrix[1][2] < 0) {
			matrixSt[1][2] = matrixSt[2][1] = -1;
		} else {
			matrixSt[1][2] = matrixSt[2][1] = 1;
		}
	}

	//2-4 parameters
	//sum(xMsom_gen)*sum(xIglobulin_M)
	mulSum = xMsom_gen * xIglobulin_M;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getMsom_gen() * casefile[i].getIglobulin_M();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxMsom_gen - pow(xMsom_gen, 2)) * (powxIglobulin_M - pow(xIglobulin_M, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[1][3] = matrix[3][1] = teta;
	if(tkr < Stkr) {
		matrixSt[1][3] = matrixSt[3][1] = 0;
	} else {
		if(matrix[1][3] < 0) {
			matrixSt[1][3] = matrixSt[3][1] = -1;
		} else {
			matrixSt[1][3] = matrixSt[3][1] = 1;
		}
	}

	//2-5 parameters
	//sum(xMsom_gen)*sum(xIglobulin_G)
	mulSum = xMsom_gen * xIglobulin_G;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getMsom_gen() * casefile[i].getIglobulin_G();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxMsom_gen - pow(xMsom_gen, 2)) * (powxIglobulin_G - pow(xIglobulin_G, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[1][4] = matrix[4][1] = teta;
	if(tkr < Stkr) {
		matrixSt[1][4] = matrixSt[4][1] = 0;
	} else {
		if(matrix[1][4] < 0) {
			matrixSt[1][4] = matrixSt[4][1] = -1;
		} else {
			matrixSt[1][4] = matrixSt[4][1] = 1;
		}
	}

	//2-6 parameters
	//sum(xMsom_gen)*sum(xImunCom)
	mulSum = xMsom_gen * xImunCom;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getMsom_gen() * casefile[i].getImunCom();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxMsom_gen - pow(xMsom_gen, 2)) * (powxImunCom - pow(xImunCom, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[1][5] = matrix[5][1] = teta;
	if(tkr < Stkr) {
		matrixSt[1][5] = matrixSt[5][1] = 0;
	} else {
		if(matrix[1][5] < 0) {
			matrixSt[1][5] = matrixSt[5][1] = -1;
		} else {
			matrixSt[1][5] = matrixSt[5][1] = 1;
		}
	}

	//2-7 parameters
	//sum(xMsom_gen)*sum(xLizocim)
	mulSum = xMsom_gen * xLizocim;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getMsom_gen() * casefile[i].getLizocim();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxMsom_gen - pow(xMsom_gen, 2)) * (powxLizocim - pow(xLizocim, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[1][6] = matrix[6][1] = teta;
	if(tkr < Stkr) {
		matrixSt[1][6] = matrixSt[6][1] = 0;
	} else {
		if(matrix[1][6] < 0) {
			matrixSt[1][6] = matrixSt[6][1] = -1;
		} else {
			matrixSt[1][6] = matrixSt[6][1] = 1;
		}
	}

	//2-8 parameters
	//sum(xMsom_gen)*sum(xActComp)
	mulSum = xMsom_gen * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getMsom_gen() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxMsom_gen - pow(xMsom_gen, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[1][7] = matrix[7][1] = teta;
	if(tkr < Stkr) {
		matrixSt[1][7] = matrixSt[7][1] = 0;
	} else {
		if(matrix[1][7] < 0) {
			matrixSt[1][7] = matrixSt[7][1] = -1;
		} else {
			matrixSt[1][7] = matrixSt[7][1] = 1;
		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//3-4 parameters
	//sum(xIglobulin_A)*sum(xIglobulin_M)
	mulSum = xIglobulin_A * xIglobulin_M;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_A() * casefile[i].getIglobulin_M();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_A - pow(xIglobulin_A, 2)) * (powxIglobulin_M - pow(xIglobulin_M, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[2][3] = matrix[3][2] = teta;
	if(tkr < Stkr) {
		matrixSt[2][3] = matrixSt[3][2] = 0;
	} else {
		if(matrix[2][3] < 0) {
			matrixSt[2][3] = matrixSt[3][2] = -1;
		} else {
			matrixSt[2][3] = matrixSt[3][2] = 1;
		}
	}

	//3-5 parameters
	//sum(xIglobulin_A)*sum(xIglobulin_G)
	mulSum = xIglobulin_A * xIglobulin_G;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_A() * casefile[i].getIglobulin_G();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_A - pow(xIglobulin_A, 2)) * (powxIglobulin_G - pow(xIglobulin_G, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[2][4] = matrix[4][2] = teta;
	if(tkr < Stkr) {
		matrixSt[2][4] = matrixSt[4][2] = 0;
	} else {
		if(matrix[2][4] < 0) {
			matrixSt[2][4] = matrixSt[4][2] = -1;
		} else {
			matrixSt[2][4] = matrixSt[4][2] = 1;
		}
	}

	//3-6 parameters
	//sum(xIglobulin_A)*sum(xImunCom)
	mulSum = xIglobulin_A * xImunCom;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_A() * casefile[i].getImunCom();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_A - pow(xIglobulin_A, 2)) * (powxImunCom - pow(xImunCom, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[2][5] = matrix[5][2] = teta;
	if(tkr < Stkr) {
		matrixSt[2][5] = matrixSt[5][2] = 0;
	} else {
		if(matrix[2][5] < 0) {
			matrixSt[2][5] = matrixSt[5][2] = -1;
		} else {
			matrixSt[2][5] = matrixSt[5][2] = 1;
		}
	}

	//3-7 parameters
	//sum(xIglobulin_A)*sum(xLizocim)
	mulSum = xIglobulin_A * xLizocim;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_A() * casefile[i].getLizocim();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_A - pow(xIglobulin_A, 2)) * (powxLizocim - pow(xLizocim, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[2][6] = matrix[6][2] = teta;
	if(tkr < Stkr) {
		matrixSt[2][6] = matrixSt[6][2] = 0;
	} else {
		if(matrix[2][6] < 0) {
			matrixSt[2][6] = matrixSt[6][2] = -1;
		} else {
			matrixSt[2][6] = matrixSt[6][2] = 1;
		}
	}

	//3-8 parameters
	//sum(xIglobulin_A)*sum(xActComp)
	mulSum = xIglobulin_A * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_A() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_A - pow(xIglobulin_A, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[2][7] = matrix[7][2] = teta;
	if(tkr < Stkr) {
		matrixSt[2][7] = matrixSt[7][2] = 0;
	} else {
		if(matrix[2][7] < 0) {
			matrixSt[2][7] = matrixSt[7][2] = -1;
		} else {
			matrixSt[2][7] = matrixSt[7][2] = 1;
		}
	}

	//4-5 parameters
	//sum(xIglobulin_M)*sum(xIglobulin_G)
	mulSum = xIglobulin_M * xIglobulin_G;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_M() * casefile[i].getIglobulin_G();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_M - pow(xIglobulin_M, 2)) * (powxIglobulin_G - pow(xIglobulin_G, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[3][4] = matrix[4][3] = teta;
	if(tkr < Stkr) {
		matrixSt[3][4] = matrixSt[4][3] = 0;
	} else {
		if(matrix[3][4] < 0) {
			matrixSt[3][4] = matrixSt[4][3] = -1;
		} else {
			matrixSt[3][4] = matrixSt[4][3] = 1;
		}
	}

	//4-6 parameters
	//sum(xIglobulin_M)*sum(xImunCom)
	mulSum = xIglobulin_M * xImunCom;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_M() * casefile[i].getImunCom();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_M - pow(xIglobulin_M, 2)) * (powxImunCom - pow(xImunCom, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[3][5] = matrix[5][3] = teta;
	if(tkr < Stkr) {
		matrixSt[3][5] = matrixSt[5][3] = 0;
	} else {
		if(matrix[3][5] < 0) {
			matrixSt[3][5] = matrixSt[5][3] = -1;
		} else {
			matrixSt[3][5] = matrixSt[5][3] = 1;
		}
	}

	//4-7 parameters
	//sum(xIglobulin_M)*sum(xLizocim)
	mulSum = xIglobulin_M * xLizocim;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_M() * casefile[i].getLizocim();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_M - pow(xIglobulin_M, 2)) * (powxLizocim - pow(xLizocim, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[3][6] = matrix[6][3] = teta;
	if(tkr < Stkr) {
		matrixSt[3][6] = matrixSt[6][3] = 0;
	} else {
		if(matrix[3][6] < 0) {
			matrixSt[3][6] = matrixSt[6][3] = -1;
		} else {
			matrixSt[3][6] = matrixSt[6][3] = 1;
		}
	}

	//4-8 parameters
	//sum(xIglobulin_M)*sum(xActComp)
	mulSum = xIglobulin_M * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_M() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_M - pow(xIglobulin_M, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[3][7] = matrix[7][3] = teta;
	if(tkr < Stkr) {
		matrixSt[3][7] = matrixSt[7][3] = 0;
	} else {
		if(matrix[3][7] < 0) {
			matrixSt[3][7] = matrixSt[7][3] = -1;
		} else {
			matrixSt[3][7] = matrixSt[7][3] = 1;
		}
	}

	//5-6 parameters
	//sum(xIglobulin_G)*sum(xImunCom)
	mulSum = xIglobulin_G * xImunCom;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_G() * casefile[i].getImunCom();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_G - pow(xIglobulin_G, 2)) * (powxImunCom - pow(xImunCom, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[4][5] = matrix[5][4] = teta;
	if(tkr < Stkr) {
		matrixSt[4][5] = matrixSt[5][4] = 0;
	} else {
		if(matrix[4][5] < 0) {
			matrixSt[4][5] = matrixSt[5][4] = -1;
		} else {
			matrixSt[4][5] = matrixSt[5][4] = 1;
		}
	}

	//5-7 parameters
	//sum(xIglobulin_G)*sum(xLizocim)
	mulSum = xIglobulin_G * xLizocim;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_G() * casefile[i].getLizocim();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_G - pow(xIglobulin_G, 2)) * (powxLizocim - pow(xLizocim, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[4][6] = matrix[6][4] = teta;
	if(tkr < Stkr) {
		matrixSt[4][6] = matrixSt[6][4] = 0;
	} else {
		if(matrix[4][6] < 0) {
			matrixSt[4][6] = matrixSt[6][4] = -1;
		} else {
			matrixSt[4][6] = matrixSt[6][4] = 1;
		}
	}

	//5-8 parameters
	//sum(xIglobulin_G)*sum(xActComp)
	mulSum = xIglobulin_G * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getIglobulin_G() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxIglobulin_G - pow(xIglobulin_G, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[4][7] = matrix[7][4] = teta;
	if(tkr < Stkr) {
		matrixSt[4][7] = matrixSt[7][4] = 0;
	} else {
		if(matrix[4][7] < 0) {
			matrixSt[4][7] = matrixSt[7][4] = -1;
		} else {
			matrixSt[4][7] = matrixSt[7][4] = 1;
		}
	}

	//6-7 parameters
	//sum(xImunCom)*sum(xLizocim)
	mulSum = xImunCom * xLizocim;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getImunCom() * casefile[i].getLizocim();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxImunCom - pow(xImunCom, 2)) * (powxLizocim - pow(xLizocim, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[5][6] = matrix[6][5] = teta;
	if(tkr < Stkr) {
		matrixSt[5][6] = matrixSt[6][5] = 0;
	} else {
		if(matrix[5][6] < 0) {
			matrixSt[5][6] = matrixSt[6][5] = -1;
		} else {
			matrixSt[5][6] = matrixSt[6][5] = 1;
		}
	}

	//6-8 parameters
	//sum(xImunCom)*sum(xActComp)
	mulSum = xImunCom * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getImunCom() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxImunCom - pow(xImunCom, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[5][7] = matrix[7][5] = teta;
	if(tkr < Stkr) {
		matrixSt[5][7] = matrixSt[7][5] = 0;
	} else {
		if(matrix[5][7] < 0) {
			matrixSt[5][7] = matrixSt[7][5] = -1;
		} else {
			matrixSt[5][7] = matrixSt[7][5] = 1;
		}
	}

	//7-8 parameters
	//sum(xLizocim)*sum(xActComp)
	mulSum = xLizocim * xActComp;
	mul = 0;
	for(int i = 0; i < (casefile.size() - 1); i++) {
		mul += casefile[i].getLizocim() * casefile[i].getActComp();
	}

	mul *= (casefile.size() - 1);

	sqrtRes = sqrt((powxLizocim - pow(xLizocim, 2)) * (powxActComp - pow(xActComp, 2)));
	teta = (mul - mulSum)/sqrtRes;
	//???????? ?????????? ????. ?????????? ???????
	tkr = (abs(teta)*sqrt((float)(casefile.size() - 3)))/sqrt(1 - pow(teta, 2));

	matrix[6][7] = matrix[7][6] = teta;
	if(tkr < Stkr) {
		matrixSt[6][7] = matrixSt[7][6] = 0;
	} else {
		if(matrix[6][7] < 0) {
			matrixSt[6][7] = matrixSt[7][6] = -1;
		} else {
			matrixSt[6][7] = matrixSt[7][6] = 1;
		}
	}

	std::cout << "???????? ????????? ??? ??????????? 0.05: " << Stkr << std::endl;
	std::cout << "----------------------------------------------" << std::endl;

	std::cout << "??????? ????????????? ??????????: " << std::endl << std::endl << std::setprecision(4);
	for(int i = 0; i < 8; i++) {
		for(int k = 0; k < 8; k++) {
			std::cout << std::setw(12) << matrix[i][k] << " ";
			if(k == 7) {
				std::cout << std::endl;
			}
		}
	}

	std::cout << std::endl;

	std::cout << "??????? ??????????? ????????????? ??????????: " << std::endl << std::endl;
	for(int i = 0; i < 8; i++) {
		for(int k = 0; k < 8; k++) {
			std::cout << std::setw(4) << matrixSt[i][k] << " ";
			if(k == 7) {
				std::cout << std::endl;
			}
		}
	}

}



void dichotomyCase(std::vector<patient> casefile, std::vector<patient> &caseDich) {

	u_int id;
	float tglobulin, msom_gen, iglobulin_A, iglobulin_M,
			iglobulin_G, imunCom, lizocim, actComp;

	for (int i = 0; i < (casefile.size() - 1); i++) {
		if(casefile[i].getTglobulin() < 230) {
			tglobulin = 0;
		} else tglobulin = 1;

		if(casefile[i].getMsom_gen() < 300) {
			msom_gen = 0;
		} else msom_gen = 1;

		if((casefile[i].getIglobulin_A() > 1.5) && (casefile[i].getIglobulin_A() < 3.5)) {
			iglobulin_A = 0;
		} else iglobulin_A = 1;

		if((casefile[i].getIglobulin_M()) > 0.6 && (casefile[i].getIglobulin_M() < 1.5)) {
			iglobulin_M = 0;
		} else iglobulin_M = 1;

		if((casefile[i].getIglobulin_G()) > 9 && (casefile[i].getIglobulin_G() < 18)) {
			iglobulin_G = 0;
		} else iglobulin_G = 1;

		if(casefile[i].getImunCom() < 50) {
			imunCom = 0;
		} else imunCom = 1;

		if((casefile[i].getLizocim() > 35) && (casefile[i].getLizocim() < 45)) {
			lizocim = 0;
		} else lizocim = 1;

		if((casefile[i].getActComp() > 12) && (casefile[i].getActComp() < 14)) {
			actComp = 0;
		} else actComp = 1;
		caseDich.push_back(patient(casefile[i].getId(), tglobulin, msom_gen,
				iglobulin_A, iglobulin_M, iglobulin_G, imunCom,
				lizocim, actComp, casefile[i].getRes()));
	}
}

void soprDich(std::vector<patient> &caseDich, dich mas[36]) {
	for(int i = 0; i < (caseDich.size() - 1); i++) {

		mas[i].mas[0][0] = 0;
		mas[i].mas[0][1] = 0;
		mas[i].mas[1][0] = 0;
		mas[i].mas[1][1] = 0;
		mas[0].mas[0][0]

	}
}
