//---------------------------------------------------------------------------

#include <vcl.h>
#include <cmath>
#include <string>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;

#define NOSELECT -1
#define EVKLID 0
#define N_VECTOR 1
#define EVKLIDCOFCNT 2
#define KAMBERR 3
#define ANGLE_VECTOR 4
#define DOYCE 5
#define JOCKAR_NIDMAN 6
#define RUSSEL_RAO 7
#define SOKAL_SNIFF 8

#define sqr(as) ((as)*(as))
#define conf 1

unsigned int base [5][5];
unsigned int et1 [5][5] = {
					{1,0,0,0,1},
					{1,1,0,1,1},
					{1,0,1,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1}};

unsigned int et2 [5][5] = {
					{0,0,1,0,0},
					{0,1,0,1,0},
					{0,1,1,1,0},
					{0,1,0,1,0},
					{0,1,0,1,0}};

unsigned int et3 [5][5] = {
					{0,0,1,1,1},
					{0,1,0,0,1},
					{0,1,0,0,1},
					{0,1,0,0,1},
					{1,0,0,0,1}};

unsigned int et4 [5][5] = {
					{1,1,1,0,0},
					{1,0,0,1,0},
					{1,1,1,0,0},
					{1,0,0,0,0},
					{1,0,0,0,0}};

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	for (int i = 0; i < 5; i++) {
		for(int k = 0; k < 5; k++) {
            base[i][k] = 0;
		}
	}

	//"M"
	StringGrid1->Cells[0][0] = "#";
	StringGrid1->Cells[4][0] = "#";
	StringGrid1->Cells[0][1] = "#";
	StringGrid1->Cells[1][1] = "#";
	StringGrid1->Cells[3][1] = "#";
	StringGrid1->Cells[4][1] = "#";
	StringGrid1->Cells[0][2] = "#";
	StringGrid1->Cells[2][2] = "#";
	StringGrid1->Cells[4][2] = "#";
	StringGrid1->Cells[0][3] = "#";
	StringGrid1->Cells[4][3] = "#";
	StringGrid1->Cells[0][4] = "#";
	StringGrid1->Cells[4][4] = "#";

	//"A"
	StringGrid2->Cells[2][0] = "#";
	StringGrid2->Cells[1][1] = "#";
	StringGrid2->Cells[3][1] = "#";
	StringGrid2->Cells[1][2] = "#";
	StringGrid2->Cells[2][2] = "#";
	StringGrid2->Cells[3][2] = "#";
	StringGrid2->Cells[1][3] = "#";
	StringGrid2->Cells[3][3] = "#";
	StringGrid2->Cells[1][4] = "#";
	StringGrid2->Cells[3][4] = "#";

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
	StringGrid4->Cells[4][0] = "#";
	StringGrid4->Cells[1][1] = "#";
	StringGrid4->Cells[4][1] = "#";
	StringGrid4->Cells[1][2] = "#";
	StringGrid4->Cells[4][2] = "#";
	StringGrid4->Cells[1][3] = "#";
	StringGrid4->Cells[4][3] = "#";
	StringGrid4->Cells[0][4] = "#";
	StringGrid4->Cells[4][4] = "#";
}
//---------------------------------------------------------------------------




void __fastcall TForm4::StringGrid5SelectCell(TObject *Sender, int ACol, int ARow,
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
//---------------------------------------------------------------------------



void __fastcall TForm4::Button1Click(TObject *Sender)
{
	ListBox1->Clear();
	ListBox2->Clear();
	ListBox3->Clear();
	ListBox4->Clear();

	float r1 = 0;
	float r2 = 0;
	float r3 = 0;
	float r4 = 0;

	float a1 = 0;
	float a2 = 0;
	float a3 = 0;
	float a4 = 0;

	float b1 = 0;
	float b2 = 0;
	float b3 = 0;
	float b4 = 0;

	float h1 = 0;
	float h2 = 0;
	float h3 = 0;
	float h4 = 0;

	float g1 = 0;
	float g2 = 0;
	float g3 = 0;
	float g4 = 0;

	float baseVect = 0;
	float vect1 = 0;
	float vect2 = 0;
	float vect3 = 0;
	float vect4 = 0;

	switch(RadioGroup1->ItemIndex){
		case NOSELECT:
		break;

		case EVKLID:
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				r1 = r1 + sqr((base[i][j] - et1[i][j]));
				r2 = r2 + sqr((base[i][j] - et2[i][j]));
				r3 = r3 + sqr((base[i][j] - et3[i][j]));
				r4 = r4 + sqr((base[i][j] - et4[i][j]));
			}
		}
		r1 = std::sqrt(r1);
		r2 = std::sqrt(r2);
		r3 = std::sqrt(r3);
		r4 = std::sqrt(r4);
		ListBox1->Items->Add(r1);
		ListBox2->Items->Add(r2);
		ListBox3->Items->Add(r3);
		ListBox4->Items->Add(r4);
		break;

		case N_VECTOR:
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				r1 = r1 + abs((base[i][j] - et1[i][j]));
				r2 = r2 + abs((base[i][j] - et2[i][j]));
				r3 = r3 + abs((base[i][j] - et3[i][j]));
				r4 = r4 + abs((base[i][j] - et4[i][j]));
			}
		}
		ListBox1->Items->Add(r1);
		ListBox2->Items->Add(r2);
		ListBox3->Items->Add(r3);
		ListBox4->Items->Add(r4);
		break;

		case EVKLIDCOFCNT:
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				r1 = r1 + sqr(conf*(base[i][j] - et1[i][j]));
				r2 = r2 + sqr(conf*(base[i][j] - et2[i][j]));
				r3 = r3 + sqr(conf*(base[i][j] - et3[i][j]));
				r4 = r4 + sqr(conf*(base[i][j] - et4[i][j]));
			}
		}
		r1 = std::sqrt(r1);
		r2 = std::sqrt(r2);
		r3 = std::sqrt(r3);
		r4 = std::sqrt(r4);
		ListBox1->Items->Add(r1);
		ListBox2->Items->Add(r2);
		ListBox3->Items->Add(r3);
		ListBox4->Items->Add(r4);
		break;

		case KAMBERR:
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				if((base[i][j] + et1[i][j]) != 0) {
					r1 = r1 + (abs((base[i][j] - et1[i][j]))/abs((base[i][j] + et1[i][j])));
				}
				if((base[i][j] + et2[i][j]) != 0) {
					r2 = r2 + (abs((base[i][j] - et2[i][j]))/abs((base[i][j] + et2[i][j])));
				}
				if((base[i][j] + et3[i][j]) != 0) {
					r3 = r3 + (abs((base[i][j] - et3[i][j]))/abs((base[i][j] + et3[i][j])));
                }
				if((base[i][j] + et4[i][j]) != 0) {
					r4 = r4 + (abs((base[i][j] - et4[i][j]))/abs((base[i][j] + et4[i][j])));
				}
			}
		}
		ListBox1->Items->Add(r1);
		ListBox2->Items->Add(r2);
		ListBox3->Items->Add(r3);
		ListBox4->Items->Add(r4);
		break;

		case ANGLE_VECTOR:
        for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				r1 = r1 + base[i][j] * et1[i][j];
				r2 = r2 + base[i][j] * et2[i][j];
				r3 = r3 + base[i][j] * et3[i][j];
				r4 = r4 + base[i][j] * et4[i][j];

				baseVect += sqr(base[i][j]);
				vect1 += sqr(et1[i][j]);
				vect2 += sqr(et2[i][j]);
				vect3 += sqr(et3[i][j]);
				vect4 += sqr(et4[i][j]);
			}
		}

		r1 = std::acos(r1 / (abs(baseVect) * abs(vect1)));
		r2 = std::acos(r2 / (abs(baseVect) * abs(vect2)));
		r3 = std::acos(r3 / (abs(baseVect) * abs(vect3)));
		r4 = std::acos(r4 / (abs(baseVect) * abs(vect4)));

		ListBox1->Items->Add(r1);
		ListBox2->Items->Add(r2);
		ListBox3->Items->Add(r3);
		ListBox4->Items->Add(r4);
		break;

		case DOYCE:
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				a1 = a1 + base[i][j] + et1[i][j];
				a2 = a2 + base[i][j] + et2[i][j];
				a3 = a3 + base[i][j] + et3[i][j];
				a4 = a4 + base[i][j] + et4[i][j];

				b1 = b1 + (1 - base[i][j]) * (1 - et1[i][j]);
				b2 = b2 + (1 - base[i][j]) * (1 - et2[i][j]);
				b3 = b3 + (1 - base[i][j]) * (1 - et3[i][j]);
				b4 = b4 + (1 - base[i][j]) * (1 - et4[i][j]);

				g1 = g1 + et1[i][j] * (1 - base[i][j]);
				g2 = g2 + et2[i][j] * (1 - base[i][j]);
				g3 = g3 + et3[i][j] * (1 - base[i][j]);
				g4 = g4 + et4[i][j] * (1 - base[i][j]);

				h1 = h1 + base[i][j] * (1 - et1[i][j]);
				h2 = h2 + base[i][j] * (1 - et2[i][j]);
				h3 = h3 + base[i][j] * (1 - et3[i][j]);
				h4 = h4 + base[i][j] * (1 - et4[i][j]);
			}
		}

		if ((2 * a1 + g1 + h1) != 0) {
			r1 = (a1 / (2 * a1 + g1 + h1));
			ListBox1->Items->Add(r1);
		}
		else {
			ListBox1->Items->Add("Деление на ноль!");
		}

		if ((2 * a2 + g2 + h2) != 0) {
			r2 = (a2 / (2 * a2 + g2 + h2));
			ListBox2->Items->Add(r2);
		}
		else {
			ListBox2->Items->Add("Деление на ноль!");
		}

		if ((2 * a3 + g3 + h3) != 0) {
			r3 = (a3 / (2 * a3 + g3 + h3));
			ListBox3->Items->Add(r3);
		}
		else {
			ListBox3->Items->Add("Деление на ноль!");
		}

		if ((2 * a4 + g4 + h4) != 0) {
			r4 = (a4 / (2 * a4 + g4 + h4));
			ListBox4->Items->Add(r4);
		}
		else {
			ListBox4->Items->Add("Деление на ноль!");
		}
		break;

		case JOCKAR_NIDMAN:
        for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				a1 = a1 + base[i][j] + et1[i][j];
				a2 = a2 + base[i][j] + et2[i][j];
				a3 = a3 + base[i][j] + et3[i][j];
				a4 = a4 + base[i][j] + et4[i][j];

				b1 = b1 + (1 - base[i][j]) * (1 - et1[i][j]);
				b2 = b2 + (1 - base[i][j]) * (1 - et2[i][j]);
				b3 = b3 + (1 - base[i][j]) * (1 - et3[i][j]);
				b4 = b4 + (1 - base[i][j]) * (1 - et4[i][j]);

				g1 = g1 + et1[i][j] * (1 - base[i][j]);
				g2 = g2 + et2[i][j] * (1 - base[i][j]);
				g3 = g3 + et3[i][j] * (1 - base[i][j]);
				g4 = g4 + et4[i][j] * (1 - base[i][j]);

				h1 = h1 + base[i][j] * (1 - et1[i][j]);
				h2 = h2 + base[i][j] * (1 - et2[i][j]);
				h3 = h3 + base[i][j] * (1 - et3[i][j]);
				h4 = h4 + base[i][j] * (1 - et4[i][j]);
			}
		}

		if ((a1 + g1 + h1) != 0) {
			r1 = (a1 / (a1 + g1 + h1));
			ListBox1->Items->Add(r1);
		}
		else {
			ListBox1->Items->Add("Деление на ноль!");
		}

		if ((a2 + g2 + h2) != 0) {
			r2 = (a2 / (a2 + g2 + h2));
			ListBox2->Items->Add(r2);
		}
		else {
			ListBox2->Items->Add("Деление на ноль!");
		}

		if ((a3 + g3 + h3) != 0) {
			r3 = (a3 / (a3 + g3 + h3));
			ListBox3->Items->Add(r3);
		}
		else {
			ListBox3->Items->Add("Деление на ноль!");
		}

		if ((a4 + g4 + h4) != 0) {
			r4 = (a4 / (a4 + g4 + h4));
			ListBox4->Items->Add(r4);
		}
		else {
			ListBox4->Items->Add("Деление на ноль!");
		}
		break;

		case RUSSEL_RAO:
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				a1 += base[i][j] + et1[i][j];
				a2 += base[i][j] + et2[i][j];
				a3 += base[i][j] + et3[i][j];
				a4 += base[i][j] + et4[i][j];

				b1 += (1 - base[i][j]) * (1 - et1[i][j]);
				b2 += (1 - base[i][j]) * (1 - et2[i][j]);
				b3 += (1 - base[i][j]) * (1 - et3[i][j]);
				b4 += (1 - base[i][j]) * (1 - et4[i][j]);

				g1 += et1[i][j] * (1 - base[i][j]);
				g2 += et2[i][j] * (1 - base[i][j]);
				g3 += et3[i][j] * (1 - base[i][j]);
				g4 += et4[i][j] * (1 - base[i][j]);

				h1 += base[i][j] * (1 - et1[i][j]);
				h2 += base[i][j] * (1 - et2[i][j]);
				h3 += base[i][j] * (1 - et3[i][j]);
				h4 += base[i][j] * (1 - et4[i][j]);
			}
		}

		if ((a1 + b1 + g1 + h1) != 0) {
			r1 = (a1 / (a1 + b1 + g1 + h1));
			ListBox1->Items->Add(r1);
		}
		else {
			ListBox1->Items->Add("Деление на ноль!");
		}

		if ((a2 + b2 + g2 + h2) != 0) {
			r2 = (a2 / (a2 + b2 + g2 + h2));
			ListBox2->Items->Add(r2);
		}
		else {
			ListBox2->Items->Add("Деление на ноль!");
		}

		if ((a3 + b3 + g3 + h3) != 0) {
			r3 = (a3 / (a3 + b3 + g3 + h3));
			ListBox3->Items->Add(r3);
		}
		else {
			ListBox3->Items->Add("Деление на ноль!");
		}

		if ((a4 + b4 + g4 + h4) != 0) {
			r4 = (a4 / (a4 + b4 + g4 + h4));
			ListBox4->Items->Add(r4);
		}
		else {
			ListBox4->Items->Add("Деление на ноль!");
		}
		break;

		case SOKAL_SNIFF:
        for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				a1 += base[i][j] + et1[i][j];
				a2 += base[i][j] + et2[i][j];
				a3 += base[i][j] + et3[i][j];
				a4 += base[i][j] + et4[i][j];

				b1 += (1 - base[i][j]) * (1 - et1[i][j]);
				b2 += (1 - base[i][j]) * (1 - et2[i][j]);
				b3 += (1 - base[i][j]) * (1 - et3[i][j]);
				b4 += (1 - base[i][j]) * (1 - et4[i][j]);

				g1 += et1[i][j] * (1 - base[i][j]);
				g2 += et2[i][j] * (1 - base[i][j]);
				g3 += et3[i][j] * (1 - base[i][j]);
				g4 += et4[i][j] * (1 - base[i][j]);

				h1 += base[i][j] * (1 - et1[i][j]);
				h2 += base[i][j] * (1 - et2[i][j]);
				h3 += base[i][j] * (1 - et3[i][j]);
				h4 += base[i][j] * (1 - et4[i][j]);
			}
		}

		if ((a1 + 2 * (g1 + h1)) != 0) {
			r1 = (a1 / (a1 + 2 * (g1 + h1)));
			ListBox1->Items->Add(r1);
		}
		else {
			ListBox1->Items->Add("Деление на ноль!");
		}

		if ((a2 + 2 * (g2 + h2)) != 0) {
			r2 = (a2 / (a2 + 2 * (g2 + h2)));
			ListBox2->Items->Add(r2);
		}
		else {
			ListBox2->Items->Add("Деление на ноль!");
		}

		if ((a3 + 2 * (g3 + h3)) != 0) {
			r3 = (a3 / (a3 + 2 * (g3 + h3)));
			ListBox3->Items->Add(r3);
		}
		else {
			ListBox3->Items->Add("Деление на ноль!");
		}

		if ((a4 + 2 * (g4 + h4)) != 0) {
			r4 = (a4 / (a4 + 2 * (g4 + h4)));
			ListBox4->Items->Add(r4);
		}
		else {
			ListBox4->Items->Add("Деление на ноль!");
		}
		break;
	}
}
//---------------------------------------------------------------------------
