//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include<string>
#include <stdlib.h>
#pragma hdrstop

#include "Unit12.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm12 *Form12;

float receptSA[6][20];
float receptAR[6];

float connect[2][6];

float masRand[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

int W[5][20];
int base[5][4];
int et1 [5][4] = { {0, 1, 1, 0},
				{ 1, 0, 0, 1},
				{1, 0, 0, 1},
				{1, 0, 0, 1},
				{0, 1, 1, 0}};

int et2 [5][4] = { {1, 1, 1, 0},
				 {1, 0, 0, 1},
				 {1, 1, 1, 0},
				 {1, 0, 0, 0},
				 {1, 0, 0, 0}};

int et3 [5][4] = {{-1, -1, -1, 1},
				  {-1, 1, 1, -1},
				  {-1, -1, -1, 1},
				  {-1, 1, 1, -1},
				  {-1, -1, -1, 1}};

int et4 [5][4] = {{1, 1, -1, -1},
				  {1, -1, 1, -1},
				  {1, -1, 1, -1},
				  {1, -1, 1, -1},
				  {-1, 1, 1, -1}};

int et6 [5][4] = {{1, 1, -1, 1},
				  {1, -1, -1, 1},
				  {1, -1, -1, 1},
				  {1, -1, -1, 1},
				  {-1, 1, 1, -1}};



int recept[5][5];

float min = 0;
float max = 0;
float awg = 0;

void addW(int col, int W[][20]);
void addLine(std::string st, int et[][4]);
bool checkReaction(int et[][4], int neyron, int num);
void corect(int et [][4], int num, int neyron);
void check();
void fillOut();
void fillBase();

//---------------------------------------------------------------------------
__fastcall TForm12::TForm12(TComponent* Owner)
	: TForm(Owner)
{

	//"O"
	StringGrid1->Cells[1][0] = "#";
	StringGrid1->Cells[2][0] = "#";
	StringGrid1->Cells[0][1] = "#";
	StringGrid1->Cells[3][1] = "#";
	StringGrid1->Cells[0][2] = "#";
	StringGrid1->Cells[3][2] = "#";
	StringGrid1->Cells[0][3] = "#";
	StringGrid1->Cells[3][3] = "#";
	StringGrid1->Cells[1][4] = "#";
	StringGrid1->Cells[2][4] = "#";

	//"P"
	StringGrid2->Cells[0][0] = "#";
	StringGrid2->Cells[1][0] = "#";
	StringGrid2->Cells[2][0] = "#";
	StringGrid2->Cells[0][1] = "#";
	StringGrid2->Cells[3][1] = "#";
	StringGrid2->Cells[0][2] = "#";
	StringGrid2->Cells[1][2] = "#";
	StringGrid2->Cells[2][2] = "#";
	StringGrid2->Cells[0][3] = "#";
	StringGrid2->Cells[0][4] = "#";

	fillRand();
	Memo1->Lines->Add("-------------------------------------");
	for(int i = 0; i < 6; i++) {
		String temp = "A";
		temp += (i+1);
		temp += ": ";
		for(int k = 0; k < 20; k++) {
			temp += (floor(receptSA[i][k]*100)/100);
			temp += " | ";	
		}
		Memo1->Lines->Add(temp);	
	}
	Memo1->Lines->Add("-------------------------------------");

		String temp = "R";
		temp += ": ";
		for(int k = 0; k < 6; k++) {
			temp += (floor(receptAR[k]*100)/100);
			temp += " | ";
		}
		Memo1->Lines->Add(temp);
	Memo1->Lines->Add("-------------------------------------");
	calcPrintA(et1, 0);
	calcPrintA(et2, 1);
	min = connect[0][0]; 
	for(int i = 0; i < 2; i++) {
		for(int k = 0; k < 6; k++) {
			if(min > connect[i][k]) {
				min = connect[i][k]; 
			}

			if(max < connect[i][k]) {
				max = connect[i][k]; 
			}
		}
	}
	Memo1->Lines->Add("-------------------------------------");
	
	String str;
	str += (floor(min*100)/100);
	Memo1->Lines->Add("Нижняя граница: " + str);
	str.Delete(1, str.Length());
	str += (floor(max*100)/100);
	Memo1->Lines->Add("Верхняя граница: " + str);
	Memo1->Lines->Add("-------------------------------------");

	awg = (min+max)/2.0;
	str.Delete(1, str.Length());
	str += (floor(awg*100)/100);

	Memo1->Lines->Add("Порог: " + str);
	Memo1->Lines->Add("-------------------------------------");

	str.Delete(1, str.Length());
	float UReact1 = 0;
	str += "При заданном пороге для эталона 1 возбуждаются: ";
	for (int i = 0; i < 6; i++) {
		float tmp = (floor(connect[0][i]*100)/100);
		if(tmp >= awg) {
			str += "A";
			str += (i+1);
			str += "; ";
			UReact1 += connect[0][i] * receptAR[i];
			}
	}
	str += "Выходная величина: ";
	str += UReact1;
	Memo1->Lines->Add(str);
	Memo1->Lines->Add("-------------------------------------");

	float UReact2 = 0;
	str.Delete(1, str.Length());
	str += "При заданном пороге для эталона 2 возбуждаются: ";
	for (int i = 0; i < 6; i++) {
		float tmp = (floor(connect[1][i]*100)/100);
		if(tmp >= awg) {
			str += "A";
			str += (i+1);
			str += "; ";
			UReact2 += connect[1][i] * receptAR[i];
		}
	}
	str += "Выходная величина: ";
	str += UReact2;
	Memo1->Lines->Add(str);
	Memo1->Lines->Add("-------------------------------------");
}
//---------------------------------------------------------------------------

void __fastcall TForm12::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid1->Cells[ACol][ARow] == "#") {
		StringGrid1->Cells[ACol][ARow] = "";
		et1[ARow][ACol] = 0;
	} else {
		StringGrid1->Cells[ACol][ARow] = "#";
		et1[ARow][ACol] = 1;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm12::StringGrid2SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid2->Cells[ACol][ARow] == "#") {
		StringGrid2->Cells[ACol][ARow] = "";
		et2[ARow][ACol] = 0;
	} else {
		StringGrid2->Cells[ACol][ARow] = "#";
		et2[ARow][ACol] = 1;
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm12::StringGrid5SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid5->Cells[ACol][ARow] == "#") {
		StringGrid5->Cells[ACol][ARow] = "";
		base[ARow][ACol] = 0;
	} else {
		StringGrid5->Cells[ACol][ARow] = "#";
		base[ARow][ACol] = 1;
	}
}

void addLine(std::string st, int et[][4]) {
	char p[17];
	std::string str = st + "{ ";
	for(int i = 0; i < 5; i++) {
		for(int k = 0; k < 4; k++) {
			itoa(et[i][k], p, 10);
			str.append(p);
			str.append(" ");
		}
	}
	str.append("}");
	Form12->Memo1->Lines->Add(str.c_str());
}

void addW(int col, int W[][20]) {
	char p[17];
	itoa((col + 1), p, 10);
	std::string str = "W";
	str.append(p);
	str.append(": { ");
	for (int k = 0; k < 20; k++) {
		itoa(W[col][k], p, 10);
		str.append(p);
		str.append(" ");
	}
	str.append(" }");
	Form12->Memo1->Lines->Add(str.c_str());
}

 void corect(int et [][4], int num, int neyron) {
    int a = 0;
	int s = 0;
	for(int i = 0; i < 20; i++) {
		W[neyron][i] = W[neyron][i] + et[a][s] * recept[num][neyron];
		s++;
		if (s == 5) {
			s = 0;
			a++;
		}
	}
}

void TForm12::fillRand() {
	for(int i = 0; i < 6; i++) {
		for (int k = 0; k < 20; k++) {
			int rd = rand() % 9;
			receptSA[i][k] = masRand[rd];
		}
	}

	for(int i = 0; i < 6; i++) {
		int rd = rand() % 9;
		receptAR[i] = masRand[rd];	
	}
}

void TForm12::calcPrintA(int et[][4], int pos) {
	
	for(int i = 0; i < 6; i++) {
		float sum = 0;
		int a = 0;
		int s = 0;
		for(int k = 0; k < 20; k++) {

			sum += et[a][s] * receptSA[i][k];
			s++;
			if (s == 5) {
				s = 0;
				a++;
			}
		}
		connect[pos][i] = sum;
	}

	String str = "Для эталона ";
	str += (pos +1);
	str += " A равны: ";
	Memo1->Lines->Add(str);
	String nums;
	for(int i = 0; i < 6; i++) {
		nums += (floor(connect[pos][i]*100)/100);
		nums += " | ";
	}
	Memo1->Lines->Add(nums);
}


bool checkReaction(int et[][4], int neyron, int num) {

	std::string str;
	int arr[4];
	bool res;
	arr[neyron] = 0;
	char p[17];

	int a = 0;
	int s = 0;

	for(int i = 0; i < 20; i++) {
		arr[neyron] = arr[neyron] + W[neyron][i] * et[a][s];
		s++;
		if (s == 5) {
			s = 0;
			a++;
		}
	}
	itoa(num, p, 10);
	str = "Буква ";
	str.append(p);
	str += " подается на выход ";
	itoa((neyron + 1), p, 10);
	str.append(p);
	str += ".";
	Form12->Memo1->Lines->Add(str.c_str());
	str.clear();
	str += "S = ";
	itoa(arr[neyron], p, 10);
	str.append(p);
	Form12->Memo1->Lines->Add(str.c_str());
	if(arr[neyron] <= 0) {
		arr[neyron] = -1;
	} else {
		arr[neyron] = 1;
	}
	res = true;
	if(arr[neyron] != recept[(num-1)][neyron]) {
		res = false;
		Form12->Memo1->Lines->Add("Необходимо выполнить пересчет весов.");
	}
	 return res;
 }

 void check() {
	 int sum[5];
	 int min;
	 int a = 0;
	 int s = 0;

	 for(int i = 0; i < 5; i++) {
		 sum[i] = 0;
	 }
	 for(int i = 0; i < 5; i++) {
		 for(int k = 0; k < 20; k ++) {
			sum[i] = sum[i] + W[i][k] * base[a][s];
			s++;
			if (s == 5) {
				s = 0;
				a++;
			}
		 }
		 s = a = 0;
	 }

	 min = sum[0];
	 std::string str;
	 char p[17];
	 int num = 0;
	 for (int i = 0; i < 5; i++) {
		str = "S = ";
		itoa(sum[i], p, 10);
		str.append(p);
		if(sum[i] < min) {
			min = sum[i];
			num = i;
		}
		Form12->Memo1->Lines->Add(str.c_str());
	 }
	 str.clear();
	 str = "Введенная буква соответствует букве ";
	 itoa((num + 1), p, 10);
	 str.append(p);
	 str += ".";
	 Form12->Memo1->Lines->Add(str.c_str());
}
void __fastcall TForm12::Button2Click(TObject *Sender)
{
	fillBase();
	check();
}

void fillOut() {
	for (int i = 0; i < 5; i++) {
		for(int j = 0; j < 4; j++) {
			base[i][j] = 1;
		}
	}

	for (int i = 0; i < 5; i++) {
		for(int k = 0; k < 20; k++) {
			W[i][k] = 0;
		}
	}

	for (int i = 0 ; i < 5; i++) {
		for(int k = 0; k < 5; k++) {
			recept[i][k] = 1;
		}
	}

	recept[0][0] = -1;
	recept[1][1] = -1;
	recept[2][2] = -1;
	recept[3][3] = -1;
	recept[4][4] = -1;
}

void fillBase() {
	for (int i = 0; i < 5; i++){
		for (int k = 0; k < 4; k++) {
			if(Form12->StringGrid5->Cells[k][i] == "#") {
				base[i][k] = -1;
			}
			else {
				base[i][k] = 1;
			}
		}
	}
}
// ---------------------------------------------------------------------------

/*

//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include<string>
#include <stdlib.h>
#pragma hdrstop

#include "Unit12.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm12 *Form12;

int W[4][20];
int base[5][4];
int et1 [5][4] = { {1, -1, -1, 1},
				{ -1, 1, 1, -1},
				{-1, 1, 1, -1},
				{-1, 1, 1, -1},
				{1, -1, -1, 1}};

int et2 [5][4] = { {-1, -1, -1, 1},
				 {-1, 1, 1, -1},
				 {-1, -1, -1, 1},
				 {-1, 1, 1, 1},
				 {-1, 1, 1, 1}};

int et3 [5][4] = {{-1, -1, -1, 1},
				  {-1, 1, 1, -1},
				  {-1, -1, -1, 1},
				  {-1, 1, 1, -1},
				  {-1, -1, -1, 1}};

int et4 [5][4] = {{1, 1, -1, -1},
				  {1, -1, 1, -1},
				  {1, -1, 1, -1},
				  {1, -1, 1, -1},
				  {-1, 1, 1, -1}};

int recept[4][4];

void addW(int col, int W[][20]);
void addLine(std::string st, int et[][4]);
bool checkReaction(int et[][4], int neyron, int num);
void corect(int et [][4], int num, int neyron);
void check();
void fillOut();
void fillBase();

//---------------------------------------------------------------------------
__fastcall TForm12::TForm12(TComponent* Owner)
	: TForm(Owner)
{

	//"O"
	StringGrid1->Cells[1][0] = "#";
	StringGrid1->Cells[2][0] = "#";
	StringGrid1->Cells[0][1] = "#";
	StringGrid1->Cells[3][1] = "#";
	StringGrid1->Cells[0][2] = "#";
	StringGrid1->Cells[3][2] = "#";
	StringGrid1->Cells[0][3] = "#";
	StringGrid1->Cells[3][3] = "#";
	StringGrid1->Cells[1][4] = "#";
	StringGrid1->Cells[2][4] = "#";

	//"P"
	StringGrid2->Cells[0][0] = "#";
	StringGrid2->Cells[1][0] = "#";
	StringGrid2->Cells[2][0] = "#";
	StringGrid2->Cells[0][1] = "#";
	StringGrid2->Cells[3][1] = "#";
	StringGrid2->Cells[0][2] = "#";
	StringGrid2->Cells[1][2] = "#";
	StringGrid2->Cells[2][2] = "#";
	StringGrid2->Cells[0][3] = "#";
	StringGrid2->Cells[0][4] = "#";

	//"B"
	StringGrid3->Cells[0][0] = "#";
	StringGrid3->Cells[1][0] = "#";
	StringGrid3->Cells[2][0] = "#";
	StringGrid3->Cells[0][1] = "#";
	StringGrid3->Cells[3][1] = "#";
	StringGrid3->Cells[0][2] = "#";
	StringGrid3->Cells[1][2] = "#";
	StringGrid3->Cells[2][2] = "#";
	StringGrid3->Cells[0][3] = "#";
	StringGrid3->Cells[3][3] = "#";
	StringGrid3->Cells[0][4] = "#";
	StringGrid3->Cells[1][4] = "#";
	StringGrid3->Cells[2][4] = "#";

	//"Л"
	StringGrid4->Cells[2][0] = "#";
	StringGrid4->Cells[3][0] = "#";
	StringGrid4->Cells[1][1] = "#";
	StringGrid4->Cells[3][1] = "#";
	StringGrid4->Cells[1][2] = "#";
	StringGrid4->Cells[3][2] = "#";
	StringGrid4->Cells[1][3] = "#";
	StringGrid4->Cells[3][3] = "#";
	StringGrid4->Cells[0][4] = "#";
	StringGrid4->Cells[3][4] = "#";
	Button2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm12::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid1->Cells[ACol][ARow] == "#") {
		StringGrid1->Cells[ACol][ARow] = "";
		et1[ARow][ACol] = 1;
	} else {
		StringGrid1->Cells[ACol][ARow] = "#";
		et1[ARow][ACol] = -1;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm12::StringGrid2SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid2->Cells[ACol][ARow] == "#") {
		StringGrid2->Cells[ACol][ARow] = "";
		et2[ARow][ACol] = 1;
	} else {
		StringGrid2->Cells[ACol][ARow] = "#";
		et2[ARow][ACol] = -1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm12::StringGrid3SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid3->Cells[ACol][ARow] == "#") {
		StringGrid3->Cells[ACol][ARow] = "";
		et3[ARow][ACol] = 1;
	} else {
		StringGrid3->Cells[ACol][ARow] = "#";
		et3[ARow][ACol] = -1;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm12::StringGrid4SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid4->Cells[ACol][ARow] == "#") {
		StringGrid4->Cells[ACol][ARow] = "";
		et4[ARow][ACol] = 1;
	} else {
		StringGrid4->Cells[ACol][ARow] = "#";
		et4[ARow][ACol] = -1;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm12::StringGrid5SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	if(StringGrid5->Cells[ACol][ARow] == "#") {
		StringGrid5->Cells[ACol][ARow] = "";
		base[ARow][ACol] = 1;
	} else {
		StringGrid5->Cells[ACol][ARow] = "#";
		base[ARow][ACol] = -1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm12::Button1Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	int century[3];
	int max;
	for(int i = 0; i < 3; i++) {
		century[i] = 1;
	}
	fillOut();
	addLine("Et1: ", et1);
	addLine("Et2: ", et2);
	addLine("Et3: ", et3);
	addLine("Et4: ", et4);
	Memo1->Lines->Add("");
	Memo1->Lines->Add("Инициализация W:");
	addW(0, W);
	addW(1, W);
	addW(2, W);
	addW(3, W);
	Memo1->Lines->Add("--------------------");
	Memo1->Lines->Add("Recept: ");

	std::string str;
	char num[17];
	for(int i = 0; i < 4; i++) {
		itoa((i + 1), num, 10);
		str.append("Число ");
		str.append(num);
		str.append(": ");
		for(int k = 0; k < 4; k++) {
			itoa(recept[i][k], num, 10);
			str.append(num);
			str.append(" ");
		}
		Memo1->Lines->Add(str.c_str());
		str.clear();
	}
	Memo1->Lines->Add("--------------------");

	int a = 0;
	int s = 0;
	for (int i = 0; i < 4; i++) {
		for(int k = 0; k < 20; k++) {
				W[i][k] = W[i][k] + et1[a][s]*recept[0][i];
				s++;
				if (s == 5) {
					s = 0;
					a++;
				}
		}
		a = s = 0;
	}
	addW(0, W);
	addW(1, W);
	addW(2, W);
	addW(3, W);
	checkReaction(et1, 0, 1);
	checkReaction(et1, 1, 1);
	checkReaction(et1, 2, 1);
	checkReaction(et1, 3, 1);
	Form12->Memo1->Lines->Add("");
	for(int i = 0; i < 4; i++) {
		while(!(checkReaction(et2, i, 2))) {
			corect(et2, 1, i);
			century[0] += 1;
		}
	}
	Form12->Memo1->Lines->Add("");
	for(int i = 0; i < 4; i++) {
		while(!(checkReaction(et3, i, 3))) {
			corect(et3, 2, i);
			century[1] += 1;
		}
	}
	Form12->Memo1->Lines->Add("");
	for(int i = 0; i < 4; i++) {
		while(!(checkReaction(et4, i, 4))) {
			corect(et4, 3, i);
			century[2] += 1;
		}
	}
	max = century[0];
	for(int i = 1; i < 3; i++) {
		if(max < century[i]) {
			max = century[i];
		}
	}
	itoa(max, num, 10);
	str.clear();
	str = "Прошло поколений: ";
	str.append(num);
	Memo1->Lines->Add(str.c_str());
	Memo1->Lines->Add("--------------------");
	addW(0, W);
	addW(1, W);
	addW(2, W);
	addW(3, W);
	Memo1->Lines->Add("--------------------");
	Button2->Enabled = true;
}
//---------------------------------------------------------------------------

void addLine(std::string st, int et[][4]) {
	char p[17];
	std::string str = st + "{ ";
	for(int i = 0; i < 5; i++) {
		for(int k = 0; k < 4; k++) {
			itoa(et[i][k], p, 10);
			str.append(p);
			str.append(" ");
		}
	}
	str.append("}");
	Form12->Memo1->Lines->Add(str.c_str());
}

void addW(int col, int W[][20]) {
	char p[17];
	itoa((col + 1), p, 10);
	std::string str = "W";
	str.append(p);
	str.append(": { ");
	for (int k = 0; k < 20; k++) {
		itoa(W[col][k], p, 10);
		str.append(p);
		str.append(" ");
	}
	str.append(" }");
	Form12->Memo1->Lines->Add(str.c_str());
}

 void corect(int et [][4], int num, int neyron) {
    int a = 0;
	int s = 0;
	for(int i = 0; i < 20; i++) {
		W[neyron][i] = W[neyron][i] + et[a][s] * recept[num][neyron];
		s++;
		if (s == 5) {
			s = 0;
			a++;
		}
	}
}

bool checkReaction(int et[][4], int neyron, int num) {

	std::string str;
	int arr[4];
	bool res;
	arr[neyron] = 0;
	char p[17];

	int a = 0;
	int s = 0;

	for(int i = 0; i < 20; i++) {
		arr[neyron] = arr[neyron] + W[neyron][i] * et[a][s];
		s++;
		if (s == 5) {
			s = 0;
			a++;
		}
	}
	itoa(num, p, 10);
	str = "Буква ";
	str.append(p);
	str += " подается на выход ";
	itoa((neyron + 1), p, 10);
	str.append(p);
	str += ".";
	Form12->Memo1->Lines->Add(str.c_str());
	str.clear();
	str += "S = ";
	itoa(arr[neyron], p, 10);
	str.append(p);
	Form12->Memo1->Lines->Add(str.c_str());
	if(arr[neyron] <= 0) {
		arr[neyron] = -1;
	} else {
		arr[neyron] = 1;
	}
	res = true;
	if(arr[neyron] != recept[(num-1)][neyron]) {
		res = false;
		Form12->Memo1->Lines->Add("Необходимо выполнить пересчет весов.");
	}
	 return res;
 }

 void check() {
	 int sum[4];
	 int min;
	 int a = 0;
	 int s = 0;

	 for(int i = 0; i < 4; i++) {
		 sum[i] = 0;
	 }
	 for(int i = 0; i < 4; i++) {
		 for(int k = 0; k < 20; k ++) {
			sum[i] = sum[i] + W[i][k] * base[a][s];
			s++;
			if (s == 5) {
				s = 0;
				a++;
			}
		 }
		 s = a = 0;
	 }

	 min = sum[0];
	 std::string str;
	 char p[17];
	 int num = 0;
	 for (int i = 0; i < 4; i++) {
		str = "S = ";
		itoa(sum[i], p, 10);
		str.append(p);
		if(sum[i] < min) {
			min = sum[i];
			num = i;
		}
		Form12->Memo1->Lines->Add(str.c_str());
	 }
	 str.clear();
	 str = "Введенная буква соответствует букве ";
	 itoa((num + 1), p, 10);
	 str.append(p);
	 str += ".";
	 Form12->Memo1->Lines->Add(str.c_str());
}
void __fastcall TForm12::Button2Click(TObject *Sender)
{
	fillBase();
	check();
}

void fillOut() {
	for (int i = 0; i < 5; i++) {
		for(int j = 0; j < 4; j++) {
			base[i][j] = 1;
		}
	}

	for (int i = 0; i < 4; i++) {
		for(int k = 0; k < 20; k++) {
			W[i][k] = 0;
		}
	}

	for (int i = 0 ; i < 4; i++) {
		for(int k = 0; k < 4; k++) {
			recept[i][k] = 1;
		}
	}

	recept[0][0] = -1;
	recept[1][1] = -1;
	recept[2][2] = -1;
	recept[3][3] = -1;
}

void fillBase() {
	for (int i = 0; i < 5; i++){
		for (int k = 0; k < 4; k++) {
			if(Form12->StringGrid5->Cells[k][i] == "#") {
				base[i][k] = -1;
			}
			else {
				base[i][k] = 1;
			}
		}
	}
}       */
// --------------------------------------------------------------------

