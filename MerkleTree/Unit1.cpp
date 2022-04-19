//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit15.h"
#include <fstream>
#include <iostream>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TForm15 *Form15;
vector<Node*> leaves;
MerkleTree* tree;
int selected[2];
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form15 =
	(TForm15*) Application->MainForm;
	tree = new MerkleTree(20);
	ifstream file_check;
	file_check.open("C:\\nsec\\full.txt");
	if(file_check.is_open()) {
		file_check.close();
		tree->Build("C:\\nsec\\full.txt");
	} else {
		tree->Build("C:\\nsec\\full.txt");
	}


	StringGrid1->Cells[0][0] = "e1e83c68-50fd";
	StringGrid1->Cells[0][1] = "fa8badc0-50ff";
	StringGrid1->Cells[0][2] = "ff05d9e8-50ff";
	StringGrid1->Cells[0][3] = "03e40278-5100";
	StringGrid1->Cells[0][4] = "07e8a6e4-5100";
	StringGrid1->Cells[0][5] = "0c96e5a2-5100";
	StringGrid1->Cells[0][6] = "105a1600-5100";
	StringGrid1->Cells[0][7] = "1400d4a6-5100";
	StringGrid1->Cells[0][8] = "1a3f9802-5100";
	StringGrid1->Cells[0][9] = "20ff2360-11eb";

	ifstream file;
	file.open("C:\\nsec\\chunks.txt");

	if (file.is_open()) {
	}
	else {
		String edited = "C:\\nsec\\";
		edited += "chunks.txt";
		file.open(edited.t_str());
	}

	for (int i = 0; i < 10; i++) {
		status[i] = 0;
		for (int k = 0; k < 15; k++) {
			file >> infoBlock[i][k];
		}
	}
	file.close();
	for(int i = 0; i < 10; i++) {
		for(int k = 0; k < 15; k++) {
			if(infoBlock[i][k] == 1) {
				StringGrid2->Cells[k][i] = "*";
			}
		}
	}

}

//---------------------------------------------------------------------------


/* запитуємо частину файла. На вхід подається merkle root цого
файлу, індекс блоку. На вихід дається контент
файлу або помилка, якщо такого блоку немає */
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(infoBlock[selected[1]][selected[0]] == 0) {
		ShowMessage("The client doesn't have this part.");
		return;
	}
	if(status[selected[1]] == 0) {
		ShowMessage("The client is offline.");
		return;
	}
	string res = Form15->getCform(selected[1], selected[0], tree);
	Edit1->Text = res.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	selected[0] = ACol;
	selected[1] = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{

	if(status[selected[1]] == 0) {
		ShowMessage("The client is offline.");
		return;
	}
	if(infoBlock[selected[1]][selected[0]] == 0) {
		ShowMessage("The client doesn't have this part.");
		return;
	}

	string res = Form15->verify(selected[1], selected[0], tree);
	Edit1->Text = res.c_str();
}
//---------------------------------------------------------------------------

MerkleTree TForm1::sendTree() {
	return *tree;
}

void TForm1::updateBlock(int row, int col) {
	this->infoBlock[row][col] = 1;
	StringGrid2->Cells[col][row] = "*";
}
