//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
#define PI 3.14159265
#define APP 7
#define DAPP 14
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm15 *Form15;

std::vector<int> data;
std::vector<int> corr_data;
std::vector<int> noizeSignal;
std::vector<int> teta;
std::vector<int> filteredSignal;
std::vector<int> linearFilterSign;

float quart = 150;
int indR[10];
int indP[10];
int indT[10];
int indS[10];
int indQ[10];
int BR[6], ER[6], BP[6], EP[6], BT[6], ET[6], BS[6], ES[6], BQ[6], EQ[6];
//полуинтервал усреднения
const int m = 10;
// массив интервалов RR
int intRR[7];

bool TForm15::sorting(int i,int j){
	return (i<j);
	}

// ---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner) : TForm(Owner) {
	std::string filename = "F:\\FILE_L1\\150HZ\\3L150_8.dat";
	std::ifstream readfile(filename.c_str(), std::ios_base::in);
	int fix;
	if (readfile.is_open()) {
		do {
			readfile >> fix;
			data.push_back(fix); // fill with data
		}
		while (!readfile.eof());
		readfile.close();
	}

	std::string rf("F:\\memory.txt");

	std::ifstream rfile(rf.c_str(), std::ios_base::in);
	if (rfile.is_open()) {
		for(int k = 0; k < 5; k++) {
			for(int i = 0; i < 10; i++) {
				rfile >> fix;
				switch(k) {
				case 0:
					indR[i] = fix;
					break;

				case 1:
					indP[i] = fix;
					break;

				case 2:
					indT[i] = fix;
					break;

				case 3:
					indQ[i] = fix;
					break;

				case 4:
					indS[i] = fix;
					break;
				}
			}
		}
		rfile.close();
	}

	//read ends and beginings
	std::string begEnd("F:\\data.txt");

	std::ifstream bEnd(begEnd.c_str(), std::ios_base::in);
	if (bEnd.is_open()) {
		for(int k = 0; k < 5; k++) {
			for(int i = 0; i < 6; i++) {
				switch(k) {
				case 0:
					bEnd >> fix;
					BR[i] = fix;
					bEnd >> fix;
					ER[i] = fix;
					break;

				case 1:
					bEnd >> fix;
					BP[i] = fix;
					bEnd >> fix;
					EP[i] = fix;
					break;

				case 2:
					bEnd >> fix;
					BT[i] = fix;
					bEnd >> fix;
					ET[i] = fix;
					break;

				case 3:
					bEnd >> fix;
					BQ[i] = fix;
					bEnd >> fix;
					EQ[i] = fix;
					break;

				case 4:
					bEnd >> fix;
					BS[i] = fix;
					bEnd >> fix;
					ES[i] = fix;
					break;
				}
			}
		}
		bEnd.close();

	int max = data[0];
	int min = data[0];
	int count = 0;
	//размах сигнала АМ до начала Q-зоны
	for(int i  = 1; i < BQ[0]; i++) {
		if(data[i] > max) {
			max = data[i];
		}

		if(data[i] < min) {
			min = data[i];
		}
	}
	//размах сигнала в середине зоны
	for(int k = 0; k < 5; k++) {
		for(int i = (ES[k] + 1); i < BQ[k+1]; i++) {
		if(data[i] > max) {
			max = data[i];
		}

		if(data[i] < min) {
			min = data[i];
		}
	}
	}
	//размах сигнала при последнем ES
	for(int i = (ES[5]+1); i < data.size(); i++) {
		if(data[i] > max) {
			max = data[i];
		}

		if(data[i] < min) {
			min = data[i];
		}
	}
	int AM = max - min;
	float shum = 0.7 * (AM/2.0);

	//генерация шума
	for(int i = 0; i < data.size(); i++) {
		teta.push_back(0);
	}

	for(int i  = 0; i < BQ[0]; i++) {
		teta[i] = (shum * sin((2*PI*1000*i)/quart));
	}
	//размах сигнала в середине зоны
	for(int k = 0; k < 5; k++) {
		for(int i = (ES[k] + 1); i < BQ[k+1]; i++) {
			teta[i] = (shum * sin((2*PI*1000*i)/quart));
		}
	}
	//размах сигнала при последнем ES
	for(int i = (ES[5]+1); i < data.size(); i++) {
		teta[i] = (shum * sin((2*PI*1000*i)/quart));
	}

	for(int i = 0; i < data.size(); i++) {
		noizeSignal.push_back(data[i] + teta[i]);
	}

	for (int i = 0; i < data.size(); i++) {
		Series1->AddXY(i, data[i], "", clBlue);
	}

	for (int i = 0; i < noizeSignal.size(); i++) {
		Series2->AddXY(i, noizeSignal[i], "", clBlue);
	}

   linearFilter();
   for (int i = 0; i < linearFilterSign.size(); i++) {
		Series3->AddXY(i, linearFilterSign[i], "", clBlue);
	}

	filter();

	for (int i = 0; i < filteredSignal.size(); i++) {
		Series4->AddXY(i, filteredSignal[i], "", clBlue);
	}
}

}

//медианный фильтр
void TForm15::filter() {

	std::vector<int> arr;

	for(int i = 0; i < data.size(); i++) {
		filteredSignal.push_back(data[i]);
	}

	for(int i  = 0; i < BQ[0]; i++) {
		for(int k = -APP; k <= APP; k++) {
			//in case it goes lower than 0
			if((k + i) < 0) {
			 //nothing
			 //no touching QRS!
			} else if((k + i) >= BQ[0]) {
				//pass
			}else {
				arr.push_back(noizeSignal[i+k]);
			}
		}
		std::sort(arr.begin(), arr.end());
		filteredSignal[i] = arr[0];
		arr.clear();
	}
   //сигнал в середине зоны
	for(int k = 0; k < 5; k++) {
		for(int i = (ES[k] + 1); i < BQ[k+1]; i++) {
			for(int s = -APP; s <= APP; s++) {
			//in case it goes into beg of Q
			if((s + i) >= BQ[k+1]) {
				//nope
			//not counting ES
			} else if((s+i) <= ES[k]) {
				//nope
			} else {
				arr.push_back(noizeSignal[i+s]);
			}
		}
		std::sort(arr.begin(), arr.end());
		filteredSignal[i] = arr[0];
		arr.clear();
		}
	}
	//cигнал при последнем ES
	for(int i = (ES[5]+1); i < noizeSignal.size(); i++) {
		for(int s = -APP; s <= APP; s++) {
			//in case it goes into beg of Q
			if((s + i) >= noizeSignal.size()) {
				//
			//not counting ES
			} else if((s+i) <= ES[5]) {
				//
			} else {
				arr.push_back(noizeSignal[i+s]);
			}
		}
		std::sort(arr.begin(), arr.end());
		filteredSignal[i] = arr[0];
		arr.clear();
	}
}

void TForm15::linearFilter() {

	for(int i = 0; i < data.size(); i++) {
		linearFilterSign.push_back(data[i]);
	}

	float val = (2*APP+1);
	val = 1.0/val;
	for(int i  = 0; i < BQ[0]; i++) {
		int sum = 0;
		for(int k = -APP; k <= APP; k++) {
			//in case it goes lower than 0
			if((k + i) < 0) {
			 sum += 0;
			 //no touching QRS!
			} else if((k + i) >= BQ[0]) {
				sum += 0;
			}else {
				sum += noizeSignal[i+k];
			}
		}
		linearFilterSign[i] = val*sum;
	}
   //сигнал в середине зоны
	for(int k = 0; k < 5; k++) {
		for(int i = (ES[k] + 1); i < BQ[k+1]; i++) {
			int sum = 0;
			for(int s = -APP; s <= APP; s++) {
			//in case it goes into beg of Q
			if((s + i) >= BQ[k+1]) {
				sum += 0;
			//not counting ES
			} else if((s+i) <= ES[k]) {
				sum += 0;
			} else {
				sum += noizeSignal[i+s];
			}
		}
		linearFilterSign[i] = val*sum;
		}
	}
	//cигнал при последнем ES
	for(int i = (ES[5]+1); i < noizeSignal.size(); i++) {
		int sum = 0;
		for(int s = -APP; s <= APP; s++) {
			//in case it goes into beg of Q
			if((s + i) >= noizeSignal.size()) {
				sum += 0;
			//not counting ES
			} else if((s+i) <= ES[5]) {
				sum += 0;
			} else {
				sum += noizeSignal[i+s];
			}
		}
		linearFilterSign[i] = val*sum;
	}
}

void __fastcall TForm15::Button1Click(TObject *Sender)
{
	Series1->Active = false;
	Series3->Active = false;
	Series2->Active = true;
	Series4->Active = false;
	Edit1->Text = "";
	Edit2->Text = "";
	Edit3->Text = "";
	Edit4->Text = "";
	Edit5->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm15::Button2Click(TObject *Sender)
{
	Series1->Active = true;
	Series2->Active = false;
	Series3->Active = false;
	Series4->Active = false;
	Edit1->Text = "";
	Edit2->Text = "";
	Edit3->Text = "";
	Edit4->Text = "";
	Edit5->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm15::Button3Click(TObject *Sender)
{
	Series1->Active = false;
	Series2->Active = false;
	Series3->Active = true;
	Series4->Active = false;
	calcMathStat(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm15::Button4Click(TObject *Sender)
{
	Series1->Active = false;
	Series2->Active = false;
	Series3->Active = false;
	Series4->Active = true;
	calcMathStat(0);
}
//---------------------------------------------------------------------------

void TForm15::calcMathStat(int var) {

	float mathBefore = 0;
	float mathAfter = 0;
	float dispBefore = 0;
	float dispAfter = 0;



	std::vector<int> calcFiltered;
	//calculate linear params if 1
	if(var == 1) {
		calcFiltered = linearFilterSign;
	} else {
		calcFiltered = filteredSignal;
	}

	//
	for(int i = 0; i < noizeSignal.size(); i++) {
		mathBefore += noizeSignal[i];
		mathAfter += (calcFiltered[i] - noizeSignal[i]);
	}
	mathBefore = mathBefore/noizeSignal.size();
	mathAfter = mathAfter/noizeSignal.size();

	float sumBefore = 0;
	float sumAfter = 0;
	for(int i = 0; i < noizeSignal.size(); i++) {
		sumBefore += pow((noizeSignal[i] -  mathBefore), 2);
		sumAfter +=  pow((float)(calcFiltered[i] - noizeSignal[i] -  mathAfter), 2);
	}

	dispBefore = sumBefore/(noizeSignal.size() - 1);
	dispAfter = sumAfter/(noizeSignal.size() - 1);

	float quality = 1.0 - sqrt(dispAfter)/sqrt(dispBefore);

	Edit1->Text = quality;
	Edit2->Text = dispBefore;
	Edit3->Text = dispAfter;
	Edit4->Text = mathBefore;
	Edit5->Text = mathAfter;
	}
