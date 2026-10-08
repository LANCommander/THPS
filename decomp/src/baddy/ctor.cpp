/* __6CBaddy (0x8003fa34) flags=-fstructure-noalias */
/* C++ (BADDY.CPP). Demo twin (statement order from its line table). Counts baddies and sets the
   script/collision defaults. */
#pragma interface

typedef unsigned short ushort;

class CItem {
  public:
	char pad0[0x48];
	virtual ~CItem();
};

class CSuper : public CItem {
  public:
	char pad4c[0xdc - 0x4c];
	int mDC;    /* 0x0dc */
	short mE0;  /* 0x0e0 */
	ushort mE2; /* 0x0e2 */
	char pade4[0x190 - 0xe4];
	CSuper();
};

class CBaddy : public CSuper {
  public:
	char pad190[0x1a8 - 0x190];
	short m1A8; /* 0x1a8 */
	char pad1aa[0x1e0 - 0x1aa];
	int m1E0; /* 0x1e0 */
	char pad1e4[0x1fc - 0x1e4];
	short m1FC; /* 0x1fc */
	char pad1fe[0x210 - 0x1fe];
	int m210; /* 0x210 */
	int m214; /* 0x214 */
	CBaddy();
	virtual ~CBaddy();
};

int NumBaddies;

CBaddy::CBaddy() {
	NumBaddies++;
	mE2 = 0xffff;
	mE0 = 128;
	m1FC = 0;
	m1A8 = 32;
	mDC = 64;
	m1E0 = 0;
	m210 = 0;
	m214 = -1;
}
