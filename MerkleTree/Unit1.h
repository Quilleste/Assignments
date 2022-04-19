
//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "merkleTree.h"

#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TPanel *Panel1;
	TButton *Button1;

	TStringGrid *StringGrid1;
	TStringGrid *StringGrid2;
	TButton *Button2;
	TEdit *Edit1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall StringGrid2SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
	//TForm15 *Form15;
public:		// User declarations
	int infoBlock[10][15];
	int status[10];
	__fastcall TForm1(TComponent* Owner);
	MerkleTree sendTree();
	void updateBlock(int row, int col);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
