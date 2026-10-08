/* SetVariable__9CPlatformUs (0x8003f45c) */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int x, y, z;
	void Set(int px, int py, int pz) {
		x = px;
		y = py;
		z = pz;
	}
};

struct CSVector {
	short x, y, z;
	void Set(short px, short py, short pz) {
		x = px;
		y = py;
		z = pz;
	}
};

uint Spool_GetModel(uint, int);

struct CBaddy {
	ushort mFlags;
	char pad0[0x0e];
	CSVector sv10;
	ushort mModel;
	char pad1[3];
	uchar mRegion;
	char pad2[0x50];
	CVector v6c;
	char pad3[0x10];
	CSVector sv88;
	CSVector sv8e;
	char pad4[0x10a];
	uchar b19e;
	char pad5[0x11];
	ushort *mpScript;
	int GetScriptValue();
	void SetVariable(ushort);
};

struct CPlatform : CBaddy {
	void SetVariable(ushort variable);
};

void CPlatform::SetVariable(ushort variable) {
	switch (variable) {
		case 8483:
			b19e = *(uchar *)mpScript;
			mpScript++;
			break;
		case 8484:
			mModel = *mpScript++;
			break;
		case 8495: {
			uint *p_checksum = (uint *)(((int)mpScript + 3) & -4);

			mModel = Spool_GetModel(*p_checksum, mRegion);
			mpScript = (ushort *)(p_checksum + 1);
			mFlags &= ~1;
			break;
		}
		case 8500: {
			short a = GetScriptValue();
			short b = GetScriptValue();
			short c = GetScriptValue();

			v6c.Set(a << 12, b << 12, c << 12);
			break;
		}
		case 8503: {
			short a = GetScriptValue();
			short b = GetScriptValue();
			short c = GetScriptValue();

			sv10.Set(a, b, c);
			break;
		}
		case 8487: {
			short a = GetScriptValue();
			short b = GetScriptValue();
			short c = GetScriptValue();

			sv88.Set(a, b, c);
			break;
		}
		case 8488: {
			short a = GetScriptValue();
			short b = GetScriptValue();
			short c = GetScriptValue();

			sv8e.Set(a, b, c);
			break;
		}
		default:
			CBaddy::SetVariable(variable);
			break;
	}
}
