// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {
	int primes[] = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
		71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
		149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199
	};
	std::string str_private;
	std::string str_open;
	char it[30];

	int *p = new int[8];
	int *q = new int[8];
	int *n = new int[8];
	int *f = new int[8];
	int *d = new int[8];
	int *em = new int[8];
	int *k = new int[8];
	std::stringstream sstream;

	bool prime = true;
	int cou;
	for (int i = 0; i < 8; i++) {
		p[i] = primes[(int)(rand() % 46)];
		q[i] = primes[(int)(rand() % 46)];
		n[i] = p[i] * q[i];
		f[i] = (p[i] - 1) * (q[i] - 1);
		do {
			prime = true;
			k[i] = rand() % 5 + 2;
			cou = k[i] * f[i] + 1;
			for (int j = 2; j <= sqrt((double)cou); j++) {
				if (cou % j == 0) {
					prime = false;
					break;
				}
			}
			em[i] = rand() % 229 + 3;
		}
		while (prime);
		do {
			em[i]--;
			if (em[i] < 2) {
				em[i] = rand() % 254 + 2;
			}
		}
		while (((k[i] * f[i] + 1) % em[i]) != 0);
		d[i] = (k[i] * f[i] + 1) / em[i];
	}
	for (int i = 0; i < 8; i++) {
		itoa(em[i], it, 16);
		str_open += it;
		if (i != 7) {
			str_open += ":";
		}

		itoa(d[i], it, 16);
		str_private += it;
		if (i != 7) {
			str_private += ":";
		}
	}

	str_private += "-";
	str_open += "-";
	for (int i = 0; i < 8; i++) {
		itoa(n[i], it, 16);
		str_open += it;
		if (i != 7) {
			str_open += ":";
		}

		itoa(n[i], it, 16);
		str_private += it;
		if (i != 7) {
			str_private += ":";
		}
	}
	Edit1->Text = str_open.c_str();
	Edit2->Text = str_private.c_str();
}
// ---------------------------------------------------------------------------
