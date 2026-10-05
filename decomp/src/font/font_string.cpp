/* Font_String__FUsUsPcUcUcUcUc (0x8004c1a8) psyq=4.6: exact only with the PsyQ 4.6 cc1plus (gcc 2.95.2), see README */
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
void Font_String(ushort X, ushort Y, char *pString, uchar r, uchar g, uchar b, uchar BigText)
{
	DAT_800d1aec->End = 0;
	DAT_800d1aec->X = X;
	DAT_800d1aec->Y = Y;
	DAT_800d1aec->Is3d = 0;
	DAT_800d1aec->BigText = BigText;
	DAT_800d1aec->pString = pString;
	DAT_800d1aec->CodeBGR = DAT_800d1ae0 | (b << 16) | (g << 8) | r;
	DAT_800d1aec++;
	DAT_800d1aec->End = 1;
}
