/* Trig_ExecuteRestart__Fv (0x80044c84) */
/* C++ (TRIG.CPP). Fuzzy demo twin (0.82); locals from its MAIN.SYM. Puts every skater on the
   current restart node, runs its command list, and in mode 2 (unless state 7) nudges the skater
   and moves it to the restart node named DAT_800d19fc. */
#pragma interface
typedef unsigned short ushort;
struct CVector {
	int vx, vy, vz;
	CVector &operator+=(const CVector &);
};
CVector operator*(const CVector &, const int &);
struct CSVector { short vx, vy, vz; };
class CBody;
class CBruce {
public:
	char pad0[4];
	CVector mPos;              /* 0x04 */
	CSVector mAngles;          /* 0x10 */
	char pad16[0x1c - 0x16];
	CBruce *mNext;             /* 0x1c */
	char pad20[0xf0 - 0x20];
	CVector mOldPos;           /* 0xf0 */
	char padfc[0x7d8 - 0xfc];
	CVector m7D8;              /* 0x7d8 */
};
extern CBruce *DAT_800d19a4;
extern int DAT_800d1780;
extern int DAT_800d16a4;
extern char DAT_800d19fc[];
int DAT_800d19e4;
short **DAT_800d19e8;
int DAT_800d19ec;
CSVector *Trig_GetPosition(CVector &, int);
void FudgeAngles(CBruce *);
int Utils_CompareStrings(const char *, const char *, unsigned int);
extern "C" {
void FUN_8008c190(void *, int, int, int);
void FUN_80046374(ushort *, int, int);
extern char DAT_800a0f3c[];
}

void Trig_ExecuteRestart()
{
	CVector StartPos;
	CSVector *pAngles;
	CBruce *MechListCopy;
	char *pName;
	CBruce *pMan;

	pAngles = Trig_GetPosition(StartPos, DAT_800d19e4);
	for (MechListCopy = DAT_800d19a4; MechListCopy; MechListCopy = MechListCopy->mNext) {
		MechListCopy->mPos = StartPos;
		MechListCopy->mOldPos = StartPos;
		MechListCopy->mAngles = *pAngles;
		FUN_8008c190(DAT_800a0f3c, MechListCopy->mAngles.vx, MechListCopy->mAngles.vy, MechListCopy->mAngles.vz);
		FudgeAngles(MechListCopy);
	}
	pName = (char *)(pAngles + 1);
	while (*pName)
		pName++;
	pName++;
	pName += (int)pName & 1;
	FUN_80046374((ushort *)pName, DAT_800d19e4, 1);
	if (DAT_800d1780 == 2 && DAT_800d16a4 != 7) {
		int i;
		pMan = DAT_800d19a4;
		pMan->mPos += pMan->m7D8 * 100;
		for (i = 0; i < DAT_800d19ec; i++) {
			short *pNode = DAT_800d19e8[i];
			CVector Dummy;
			if (*pNode == 8 && Utils_CompareStrings((char *)(Trig_GetPosition(Dummy, i) + 1), DAT_800d19fc, -1)) {
				CVector StartPos;
				pAngles = Trig_GetPosition(StartPos, i);
				pMan->mPos = StartPos;
				pMan->mOldPos = StartPos;
				pMan->mAngles = *pAngles;
				FudgeAngles(pMan);
			}
		}
	}
}
