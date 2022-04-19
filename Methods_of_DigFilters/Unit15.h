//---------------------------------------------------------------------------

#ifndef Unit15H
#define Unit15H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <tchar.h>
#include "Series.hpp"
#include <ExtCtrls.hpp>
#include <algorithm>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <ExtCtrls.hpp>
#include "Series.hpp"
//---------------------------------------------------------------------------
class TForm15 : public TForm
{
__published:	// IDE-managed Components
	TChart *Chart1;
	TLineSeries *Series1;
	TButton *Button1;
	TLineSeries *Series2;
	TButton *Button2;
	TButton *Button3;
	TLineSeries *Series3;
	TButton *Button4;
	TLineSeries *Series4;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm15(TComponent* Owner);
	void filter();
	void linearFilter();
	bool TForm15::sorting(int i,int j);
	void TForm15::calcMathStat(int var);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm15 *Form15;
//---------------------------------------------------------------------------
#endif
