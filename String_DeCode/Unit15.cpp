//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
#include "Unit1.h"
#include "File1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace boost;
TForm15 *Form15;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm15::Button1Click(TObject *Sender)
{
   Form1->Show();
}

//---------------------------------------------------------------------------
void __fastcall TForm15::Button2Click(TObject *Sender) {
	std::string str1;
	str1 = Edit2->Text.t_str();
	split_vector_type SplitVec;
	split(SplitVec, str1, is_any_of("-"), token_compress_on);
	split_vector_type splitE;
	split_vector_type splitN;
	split(splitE, SplitVec[0], is_any_of(":"), token_compress_on);
	split(splitN, SplitVec[1], is_any_of(":"), token_compress_on);
	std::string toEncode = Edit1->Text.t_str();
	long int number;
	int buf;
	std::string encoded;
	do {
		for (int i = 0; i < 8; i++) {
			if (toEncode.compare("") != 0) {
				int e = 0;
				std::stringstream sE;
				sE << std::hex << splitE[i];
				sE >> e;

				int n;
				std::stringstream sN;
				sN << std::hex << splitN[i];
				sN >> n;
				buf = toEncode[0];
				toEncode.erase(0, 1);
				double poww = (pow((float) buf, e));
				number = (unsigned long int)poww % n;
				int c = (int)number;
				buf = (char) c;
				encoded += buf;
			}
		}
	} while (toEncode != "");
	Edit3->Text = encoded.c_str();
}
// ---------------------------------------------------------------------------
