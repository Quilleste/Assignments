//---------------------------------------------------------------------------

#ifndef Unit15H
#define Unit15H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <cstdlib>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
//---------------------------------------------------------------------------
class TForm15 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TForm15(TComponent* Owner);
	bool calculate(int* vector);
	void outW1_W2();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm15 *Form15;
//---------------------------------------------------------------------------
#endif
