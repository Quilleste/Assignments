// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit15.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TForm2 *Form2;
TForm15 *Form15;
MerkleTree test;
int selected[2];
string data[15];


// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
	Form15 = (TForm15*)Application->MainForm;
}

__fastcall TForm2::TForm2(String _id, int _data[][15], int num,
	TComponent* Owner) : TForm(Owner) {
	id_num = num;
	status = true;
	Edit1->Text = _id;
	Form15 = (TForm15*)Application->MainForm;
	for (int i = 0; i < 15; i++) {
		if (_data[num][i] == 1) {
			StringGrid1->Cells[i][0] = "*";
		}
	}
	for (int i = 0; i < 15; i++) {
		if (StringGrid1->Cells[i][0] == "*") {
			String filename = "C:\\nsec\\";
			filename += (i + 1);
			filename += ".txt";
			string data_str;
			ifstream file;
			file.open(filename.t_str());
			if(file.is_open()) {
				file >> data_str;
				file.close();
				data[i] = data_str;
			} else {
				String edited = "C:\\nsec\\";
				edited += (i + 1);
				edited += ".txt";
				file.open(edited.t_str());
                file >> data_str;
				file.close();
				data[i] = data_str;
			}
		}
		else {
			data[i] = "";
		}
	}

	for(int i = 0; i < 15; i++) {
	if (StringGrid1->Cells[i][0] == "*") {
		Edit2->Text = data[i].c_str();
	}
	else {
		Edit2->Text = "";
	}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action) {
	status = false;
}

// ---------------------------------------------------------------------------
string TForm2::getPart(int id) {
	String filename = "C:\\nsec\\";
	filename += (id + 1);
	filename += ".txt";
	string data_str;
	ifstream file;
	file.open(filename.t_str());

	if (file.is_open()) {
		file >> data_str;
		file.close();
	}
	else {
		String edited = "C:\\nsec\\";
		edited += (id + 1);
		edited += ".txt";
		file.open(edited.t_str());
		file >> data_str;
		file.close();
	}
	return data_str;
}

void __fastcall TForm2::StringGrid1SelectCell(TObject *Sender, int ACol,
	int ARow, bool &CanSelect) {
	selected[0] = ACol;
	selected[1] = ARow;
	if (StringGrid1->Cells[ACol][0] == "*") {
		Edit2->Text = data[ACol].c_str();
	}
	else {
		Edit2->Text = "";
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender) {
	if (StringGrid1->Cells[selected[0]][selected[1]] == "*") {
		ShowMessage("This part is already in the database!");
	}
	else {
		/*if (Edit1->Text.c_str() == "e1e83c68-50fd") {
			id_num = 0;
		}
		else if (Edit1->Text.Compare("fa8badc0-50ff")) {
			id_num = 1;
		}
		else if (Edit1->Text.c_str() == "ff05d9e8-50ff") {
			id_num = 2;
		}
		else if (Edit1->Text.c_str() == "03e40278-5100") {
			id_num = 3;
		}
		else if (Edit1->Text.c_str() == "07e8a6e4-5100") {
			id_num = 4;
		}
		else if (Edit1->Text.c_str() == "0c96e5a2-5100") {
			id_num = 5;
		}
		else if (Edit1->Text.c_str() == "105a1600-5100") {
			id_num = 6;
		}
		else if (Edit1->Text.c_str() == "1400d4a6-5100") {
			id_num = 7;
		}
		else if (Edit1->Text.c_str() == "1a3f9802-5100") {
			id_num = 8;
		}
		else if (Edit1->Text.c_str() == "20ff2360-11eb") {
			id_num = 9;
		}    */
		string str = Form15->getData(selected[0], id_num);
		if(str == "") {
			ShowMessage("Can't request a part with only one active client!");
			return;
		}
		if (str == "-") {
			  return;
		}
		string hash = sha256(str);
		test = Form15->getTree();
		string proof = test.ProveBlock(selected[0]);
		if (proof.find(hash) != std::string::npos) {
			StringGrid1->Cells[selected[0]][selected[1]] = "*";
			String filename = "C:\\nsec\\";
			filename += (selected[0] + 1);
			filename += ".txt";
			string data_str;
			ifstream file;
			file.open(filename.t_str());

			if (file.is_open()) {
				file >> data_str;
				file.close();
				data[selected[0]] = data_str;
			}
			else {
				String edited = "C:\\nsec\\";
				edited += (selected[0] + 1);
				edited += ".txt";
				file.open(edited.t_str());
				file >> data_str;
				file.close();
				data[selected[0]] = data_str;
			}
		}
		else {
			ShowMessage(
				"Requested part was not verified!\nCan't add non-verified parts.");
		}
	}
}
// ---------------------------------------------------------------------------

void TForm2::requestUpdate(int upd[][15], int id) {
	for (int i = 0; i < 15; i++) {
		if (StringGrid1->Cells[i][0] == "*") {
			upd[id][i] = 1;
		}
		else {
			upd[id][i] = 0;
		}
	}
}
