/* Font_Number__FUsUsiUcUcUcUc (0x8004c20c) flags=-fstructure-noalias */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct SString {
	int End;
	ushort X;
	ushort Y;
	char *pString;
	uint CodeBGR;
	uchar Is3d;
	uchar BigText;
	int Pos[3];
};

SString *DAT_800d1aec;
uint DAT_800d1ae0;
char *DAT_800d1af0;

void WriteNumber(int);

void Font_Number(ushort X, ushort Y, int Number, uchar r, uchar g, uchar b, uchar BigText) {
	DAT_800d1aec->End = 0;
	DAT_800d1aec->X = X;
	DAT_800d1aec->Y = Y;
	DAT_800d1aec->Is3d = 0;
	DAT_800d1aec->BigText = BigText;
	DAT_800d1aec->pString = DAT_800d1af0;
	DAT_800d1aec->CodeBGR = DAT_800d1ae0 | (b << 16) | (g << 8) | r;
	WriteNumber(Number);

	DAT_800d1aec++;
	DAT_800d1aec->End = 1;
}
