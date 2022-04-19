
//---------------------------------------------------------------------------

#ifndef Unit15H
#define Unit15H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"
#include "merkleTree.h"
//---------------------------------------------------------------------------
class TForm15 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
TForm1 *Form1;
TForm2 *Cform1;
TForm2 *Cform2;
TForm2 *Cform3;
TForm2 *Cform4;
TForm2 *Cform5;
TForm2 *Cform6;
TForm2 *Cform7;
TForm2 *Cform8;
TForm2 *Cform9;
TForm2 *Cform10;
void updateInfoBlock();
public:		// User declarations
	__fastcall TForm15(TComponent* Owner);
	string getCform(int form, int id, MerkleTree* tree);
	string verify(int form, int id, MerkleTree* tree);
	string getData(int id, int request);
	MerkleTree getTree();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm15 *Form15;
//---------------------------------------------------------------------------
#endif
