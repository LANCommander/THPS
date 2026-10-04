/* Spool_PSX__FPciii (0x800701b0) */
/* C++ (SPOOL.CPP). Fuzzy demo twin (0.68); locals from its MAIN.SYM. Returns the region already
   holding Name, or one from the recent-load cache (an entry matches when Name is a prefix ending
   at the '.' of the cached file name). Otherwise claims a free region, records the name and
   queues the load. Retail drops the demo's KeepTextures argument. */
typedef unsigned char uchar;
struct SRegion {
	char Name[64];
};
struct SPSXCache {
	char Name[13];
	uchar Used;          /* 13 */
	uchar Type;          /* 14 */
	uchar Region;        /* 15 */
	uchar Heap;          /* 16 */
};
extern SRegion DAT_800bf7a8[40];
extern SPSXCache DAT_800bf654[20];
extern char DAT_800d1f00[];
int DAT_800d1ef8;
int Utils_CompareStrings(const char *, const char *, unsigned int);
void LoadNameExt(char *, char *);

int Spool_PSX(char *Name, int IsEnviro, int WhichHeap)
{
	int freeregion;
	{
		int i;
		for (i = 0; i < 40; i++)
			if (DAT_800bf7a8[i].Name[0] && Utils_CompareStrings(Name, DAT_800bf7a8[i].Name, -1))
				return i;
	}
	{
		int i;
		for (i = 0; i < 20; i++) {
			if (DAT_800bf654[i].Used) {
				char *pQName = DAT_800bf654[i].Name;
				char *pPSXName = Name;
				int Identical = 1;
				while (*pPSXName) {
					if (*pPSXName != *pQName) {
						Identical = 0;
						break;
					}
					pPSXName++;
					pQName++;
				}
				if (Identical && *pQName != '.')
					Identical = 0;
				if (Identical)
					return DAT_800bf654[i].Region;
			}
		}
	}
	freeregion = -1;
	{
		int i;
		for (i = 0; i < 40; i++) {
			if (!DAT_800bf7a8[i].Name[0]) {
				freeregion = i;
				break;
			}
		}
	}
	if (IsEnviro == 0 || IsEnviro == 2) {
		char *pNew = Name;
		char *pDest = DAT_800bf7a8[freeregion].Name;
		int c;
		for (c = 0; *pNew && c < 9; c++)
			*pDest++ = *pNew++;
		*pDest = 0;
	}
	LoadNameExt(Name, DAT_800d1f00);
	if (IsEnviro != 2)
		DAT_800bf654[DAT_800d1ef8].Type = IsEnviro != 0;
	else
		DAT_800bf654[DAT_800d1ef8].Type = IsEnviro;
	DAT_800bf654[DAT_800d1ef8].Region = freeregion;
	DAT_800bf654[DAT_800d1ef8].Used = 1;
	DAT_800bf654[DAT_800d1ef8].Heap = WhichHeap;
	DAT_800d1ef8 = (DAT_800d1ef8 + 1) % 20;
	return freeregion;
}
