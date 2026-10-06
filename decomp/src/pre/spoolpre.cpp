/* spoolPRE__10PREManagerPc (0x8006623c) */
/* C++ (PRE.CPP). Demo twin; locals from its MAIN.SYM. Loads a .PRE archive into the first free slot
   and records its name (THPS1 copies the name with an inline loop instead of strcpy). */
class CClass {
public:
	virtual ~CClass();
};
class PREManager : public CClass {
public:
	char *mPre[16];            /* 0x04 (after the CClass vptr) */
	char mPreName[16][16];     /* 0x44 */
	void spoolPRE(char *pre_name);
};
extern char DAT_800a20e8[];
extern char DAT_800a2104[];
int FileIO_Open(const char *);
extern "C" {
char *FUN_8004d3a4(int);
void FUN_8004cb10(char *);
void FUN_8008c190(char *, ...);
}

void PREManager::spoolPRE(char *pre_name)
{
	int slot;
	for (slot = 0; slot < 16; slot++)
		if (!mPre[slot])
			break;
	if (slot == 16) {
		FUN_8008c190(DAT_800a20e8);
		return;
	}
	if ((mPre[slot] = FUN_8004d3a4(FileIO_Open(pre_name))))
		FUN_8004cb10(mPre[slot]);
	else
		FUN_8008c190(DAT_800a2104, pre_name);
	{
		char *d = (char *)(slot * 16 + (int)this);
		char *s = pre_name;
		d += 68;
		while (*s)
			*d++ = *s++;
		*d = 0;
	}
}
