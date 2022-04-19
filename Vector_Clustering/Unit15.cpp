//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm15 *Form15;
//рамерность
const int n = 12;
//кол-во входных векторов
const int q = 9;
//макс кол-во классов
const int m = 9;

const int L = 2;

//параметр подобности
float p = 0.5;

float W1[n][m];
float W2[n][m];

float UoutY[q];
float UoutS[n];


int v1[] = {1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
int v2[] = {1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
int v3[] = {1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
int v4[] = {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0};
int v5[] = {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0};
int v6[] = {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0};
int v7[] = {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
int v8[] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
int v9[] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
//---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Lines->Add("Входные вектора для кластеризации:");
	Memo1->Lines->Add("-------------------------------------");
	std::stringstream ss;
	ss << "v1: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v1[i] << " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v2: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v2[i] << " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v3: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v3[i] << " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v4: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v4[i]<< " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v5: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v5[i]<< " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v6: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v6[i]<< " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v7: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v7[i]<< " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v8: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v8[i]<< " |";
	}
	Memo1->Lines->Add(ss.str().c_str());

	ss.str("");
	ss << "v9: ";
	for(int i = 0; i < 12; i++) {
		ss << "| ";
		ss << v9[i]<< " |";
	}
	Memo1->Lines->Add(ss.str().c_str());
	Memo1->Lines->Add("-------------------------------------");

	for(int i = 0; i < n; i++) {
		for(int k = 0; k < m; k++) {
			W1[i][k] = 1.0/(1.0 + n);
			W2[i][k] = 1;
		}
	}

	Memo1->Lines->Add("Вывод начальных W1 и W2: ");
	Memo1->Lines->Add("-------------------------------------");

	outW1_W2();
	for (int i = 0; i < 10; i++) {
		bool end = true;
		float oldW1[12][9];
		float oldW2[12][9];
		for(int i = 0; i < 12; i++) {
			for(int k = 0; k < 9; k++) {
				oldW1[i][k] = W1[i][k];
				oldW2[i][k] = W2[i][k];
			}
		}


		Memo1->Lines->Add("-------------------------------------");
		std::stringstream ss;
		ss << "Эпоха №" << (i+1) << ".";
		Memo1->Lines->Add(ss.str().c_str());
		Memo1->Lines->Add("-------------------------------------");
		if(!calculate(v1)) {
		Memo1->Lines->Add("Невозможно распознать 1.");
		}
		if(!calculate(v2)) {
		Memo1->Lines->Add("Невозможно распознать 2.");
		}
		if(!calculate(v3)) {
		Memo1->Lines->Add("Невозможно распознать 3.");
		}
		if(!calculate(v4)) {
		Memo1->Lines->Add("Невозможно распознать 4.");
		}
		if(!calculate(v5)) {
		Memo1->Lines->Add("Невозможно распознать 5.");
		}
		if(!calculate(v6)) {
		Memo1->Lines->Add("Невозможно распознать 6.");
		}
		if(!calculate(v7)) {
		Memo1->Lines->Add("Невозможно распознать 7.");
		}
		if(!calculate(v8)) {
		Memo1->Lines->Add("Невозможно распознать 8.");
		}
		if(!calculate(v9)) {
		Memo1->Lines->Add("Невозможно распознать 9.");
		}
		outW1_W2();

        for(int i = 0; i < 12; i++) {
			for(int k = 0; k < 9; k++) {
				if((oldW2[i][k] != W2[i][k]) || (oldW1[i][k] != W1[i][k])) {
					end = false;
				}
			}
		}

		if(end) {
        	break;
		}
	}
	Memo1->Lines->Add("-------------------------------------");
	Memo1->Lines->Add("Конец кластеризации.");
	Memo1->Lines->Add("-------------------------------------");

}
// ---------------------------------------------------------------------------

bool TForm15::calculate(int* vector) {
	float UinZ[12];
	float UoutZ[12];

	float UinY[9];

	for(int i = 0; i < 9; i++) {
		UoutY[i] = 0;
	}
	float UoutNS = 0;
	for(int i = 0; i < 12; i++) {
		UoutS[i] = vector[i];
		UoutNS += vector[i];
		UoutZ[i] = vector[i];
		UinZ[i] = vector[i];
	}
	UoutNS = abs((long)UoutNS);
	bool noEnd = true;
	do {
	for(int i = 0; i < 9; i++) {
		UinY[i] = 0;
		if(UoutY[i] != -1) {
			for(int k = 0; k < 12; k++) {
				UinY[i] += W1[k][i] * UoutZ[k];
				}
				UoutY[i] = UinY[i];
		}
	}

	float UoutMax = UoutY[8];
	int J = 8;

	for(int i = 8; i >= 0; i--) {
		if((UoutMax <= UoutY[i]) && (UoutY[i] != -1)) {
			UoutMax = UoutY[i];
			J = i;
		}
	}

	//не может быть распознан
	if(UoutMax == -1) {
		return false;
	}

	for (int i = 0; i < 12; i++) {
		UoutZ[i] = UoutS[i] * W2[J][i];
	}

	float UoutNZ = 0;
	for(int i = 0; i < 12; i++) {
		UoutNZ += UoutZ[i];
	}

	UoutNZ = abs((long)UoutNZ);

	if((UoutNZ/UoutNS) < p) {
		UoutY[J] = -1;
	} else if((UoutNZ/UoutNS) >= p) {
		for(int i = 0; i < 12; i++) {
			W1[i][J] = (L*UoutZ[i])/(L-1.0+UoutNZ);
			W2[i][J] = UoutZ[i];
		}
		noEnd = false;
	}
	} while (noEnd);
	return true;
}

void TForm15::outW1_W2() {
  Memo1->Lines->Add("-------------------------------------");
  Memo1->Lines->Add("Вывод W1: ");
  Memo1->Lines->Add("-------------------------------------");
  for(int i = 0; i < 12; i++) {
	std::stringstream sW1;
	sW1 << "| ";
	for(int k = 0; k < 9; k++) {
		sW1 << (floor(W1[i][k]*1000)/1000) << " | ";
	}
	Memo1->Lines->Add(sW1.str().c_str());
  }
  Memo1->Lines->Add("-------------------------------------");
  Memo1->Lines->Add("Вывод W2: ");
  Memo1->Lines->Add("-------------------------------------");
  for(int i = 0; i < 12; i++) {
	std::stringstream sW2;
	sW2 << "| ";
	for(int k = 0; k < 9; k++) {
		sW2 << (floor(W2[i][k]*1000)/1000)  << " | ";
	}
	Memo1->Lines->Add(sW2.str().c_str());
  }
  Memo1->Lines->Add("-------------------------------------");
}
