//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm15 *Form15;
vector<string> open;
vector<bool> status;
int infoBlock[10][15];
bool tenUp;
//---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner)
	: TForm(Owner)
{
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
		for (int k = 0; k < 15; k++) {
			file >> infoBlock[i][k];
		}
	}
	file.close();

	tenUp = false;
	open.push_back("e1e83c68-50fd");
	open.push_back("fa8badc0-50ff");
	open.push_back("ff05d9e8-50ff");
	open.push_back("03e40278-5100");
	open.push_back("07e8a6e4-5100");
	open.push_back("0c96e5a2-5100");
	open.push_back("105a1600-5100");
	open.push_back("1400d4a6-5100");
	open.push_back("1a3f9802-5100");
	open.push_back("20ff2360-11eb");
	for(int i = 0; i < 10; i++) {
    	status.push_back(false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm15::Button1Click(TObject *Sender)
{
	Form1 = new TForm1(this);
	Form1->Show();
	Button1->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm15::Button2Click(TObject *Sender)
{
	if(Cform1 == NULL) {
		Cform1 = new TForm2(open[0].c_str(), infoBlock, 0, this);
		Cform1->Show();
		Form1->status[0] = 1;
	} else if(Cform2 == NULL) {
		Cform2 = new TForm2(open[1].c_str(), infoBlock, 1, this);
		Cform2->Show();
		Form1->status[1] = 1;
	} else if(Cform3 == NULL) {
		Cform3 = new TForm2(open[2].c_str(), infoBlock, 2, this);
		Cform3->Show();
		Form1->status[2] = 1;
	} else if(Cform4 == NULL) {
		Cform4 = new TForm2(open[3].c_str(), infoBlock, 3, this);
		Cform4->Show();
		Form1->status[3] = 1;
	} else if(Cform5 == NULL) {
		Cform5 = new TForm2(open[4].c_str(), infoBlock, 4, this);
		Cform5->Show();
		Form1->status[4] = 1;
	} else if(Cform6 == NULL) {
		Cform6 = new TForm2(open[5].c_str(), infoBlock, 5, this);
		Cform6->Show();
		Form1->status[5] = 1;
	} else if(Cform7 == NULL) {
		Cform7 = new TForm2(open[6].c_str(), infoBlock, 6, this);
		Cform7->Show();
		Form1->status[6] = 1;
	} else if(Cform8 == NULL) {
		Cform8 = new TForm2(open[7].c_str(), infoBlock, 7, this);
		Cform8->Show();
		Form1->status[7] = 1;
	} else if(Cform9 == NULL) {
		Cform9 = new TForm2(open[8].c_str(), infoBlock, 8, this);
		Cform9->Show();
		Form1->status[8] = 1;
	} else if(Cform10 == NULL) {
		Cform10 = new TForm2(open[9].c_str(), infoBlock, 9, this);
		Cform10->Show();
		Form1->status[9] = 1;
		tenUp = true;
	} else {
		status[0] = Cform1->status;
		status[1] = Cform2->status;
		status[2] = Cform3->status;
		status[3] = Cform4->status;
		status[4] = Cform5->status;
		status[5] = Cform6->status;
		status[6] = Cform7->status;
		status[7] = Cform8->status;
		status[8] = Cform9->status;
		status[9] = Cform10->status;

		if (!status[0]) {
			Cform1->Show();
		}
		else if (!status[1]) {
			Cform2->Show();
		}
		else if (!status[2]) {
			Cform3->Show();
		}
		else if (!status[3]) {
			Cform4->Show();
		}
		else if (!status[4]) {
			Cform5->Show();
		}
		else if (!status[5]) {
			Cform6->Show();
		}
		else if (!status[6]) {
			Cform7->Show();
		}
		else if (!status[7]) {
			Cform8->Show();
		}
		else if (!status[8]) {
			Cform9->Show();
		}
		else if (!status[9]) {
			Cform10->Show();
		} else {
			ShowMessage("Capacity reached.");
		}
	}

}
//---------------------------------------------------------------------------

string TForm15::getCform(int form, int id, MerkleTree* tree) {

	String filename = "C:\\nsec\\";
	filename += (id + 1);
	filename += ".txt";
	string data;
	ifstream file;
	file.open(filename.t_str());
	if (file.is_open()) {
		file >> data;
		file.close();
	}
	else {
		String edited = "C:\\nsec\\";
		edited += (id + 1);
		edited += ".txt";
		file.open(edited.t_str());
		file >> data;
		file.close();
	}


	string res;
	if(sha256(tree->ReadBlock(id)) == sha256(data)) {
		return data;
	} else {
		ShowMessage("Block was not verified!");
	}
}

string TForm15::verify(int form, int id, MerkleTree* tree) {
	String filename = "C:\\nsec\\";
	filename += (id + 1);
	filename += ".txt";
	string data;
	ifstream file;
	file.open(filename.t_str());
	if (file.is_open()) {
		file >> data;
		file.close();
	}
	else {
		String edited = "C:\\nsec\\";
		edited += (id + 1);
		edited += ".txt";
		file.open(edited.t_str());
		file >> data;
		file.close();
	}
	string res;
	if(tree->ProveBlock(id) == "") {
		ShowMessage("Block was not verified!");
	} else {
		return tree->ProveBlock(id);
	}
}

string TForm15::getData(int id, int request) {
	updateInfoBlock();
	int stat = 0;
	for(int i = 0; i < 10; i++) {
		if(status[i] == 1) {
			stat++;
		}
	}

	if(stat <= 1) {
		return "";
	}

	int carrier = -1;
	for(int i = 0; i < 10; i++) {
		if(infoBlock[i][id] == 1) {
			if(status[i]) {
				carrier = i;
				break;
			} else continue;
		}
	}
	if(carrier == (-1)) {
		ShowMessage("No client has this part!");
		return "-";
	} else {
		Form1->updateBlock(request, id);
		if(carrier == 0) {
			return Cform1->getPart(id);
		} else if(carrier == 1) {
			return Cform2->getPart(id);
		} else if(carrier == 2) {
			return Cform3->getPart(id);
		} else if(carrier == 3) {
			return Cform4->getPart(id);
		} else if(carrier == 4) {
			return Cform5->getPart(id);
		} else if(carrier == 5) {
			return Cform6->getPart(id);
		} else if(carrier == 6) {
			return Cform7->getPart(id);
		} else if(carrier == 7) {
			return Cform8->getPart(id);
		} else if(carrier == 8) {
			return Cform9->getPart(id);
		} else if(carrier == 9) {
			return Cform10->getPart(id);
		}
	}
}

void TForm15::updateInfoBlock() {
	if(tenUp) {
	status[0] = Cform1->status;
	status[1] = Cform2->status;
	status[2] = Cform3->status;
	status[3] = Cform4->status;
	status[4] = Cform5->status;
	status[5] = Cform6->status;
	status[6] = Cform7->status;
	status[7] = Cform8->status;
	status[8] = Cform9->status;
	status[9] = Cform10->status;

	} else {
	if(Cform1 != NULL) {
		status[0] = Cform1->status;
	}
	if(Cform2 != NULL) {
		status[1] = Cform2->status;
	}
	if(Cform3 != NULL) {
		status[2] = Cform3->status;
	}
	if(Cform4 != NULL) {
		status[3] = Cform4->status;
	}
	if(Cform5 != NULL) {
		status[4] = Cform5->status;
	}
	if(Cform6 != NULL) {
		status[5] = Cform6->status;
	}
	if(Cform7 != NULL) {
		status[6] = Cform7->status;
	}
	if(Cform8 != NULL) {
		status[7] = Cform8->status;
	}
	if(Cform9 != NULL) {
		status[8] = Cform9->status;
	}
	if(Cform10 != NULL) {
		status[9] = Cform10->status;
	}

	}

	if (status[0] == 1) {
		Cform1->requestUpdate(infoBlock, 0);
	}
	if (status[1] == 1) {
		Cform2->requestUpdate(infoBlock, 1);
	}
	if (status[2] == 1) {
		Cform3->requestUpdate(infoBlock, 2);
	}
	if (status[3] == 1) {
		Cform4->requestUpdate(infoBlock, 3);
	}
	if (status[4] == 1) {
		Cform5->requestUpdate(infoBlock, 4);
	}
	if (status[5] == 1) {
		Cform6->requestUpdate(infoBlock, 5);
	}
	if (status[6] == 1) {
		Cform7->requestUpdate(infoBlock, 6);
	}
	if (status[7] == 1) {
		Cform8->requestUpdate(infoBlock, 7);
	}
	if (status[8] == 1) {
		Cform9->requestUpdate(infoBlock, 8);
	}
	if (status[9] == 1) {
		Cform10->requestUpdate(infoBlock, 9);
	}
}

MerkleTree TForm15::getTree() {
	return Form1->sendTree();
}
