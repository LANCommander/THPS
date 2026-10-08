/* _._17TextScreenElement (0x8002da78) */
#include "names.h"
extern char DAT_8009f708[];

void Mem_Delete(void *);
void CSpecialDisplay_dtor(void *, int);
void __dl__4CBitPv(void *);

void TextScreenElement_dtor(char *this, int flags) {
	*(char **)(this + 0x44) = DAT_8009f708;
	Mem_Delete(*(void **)(this + 0x50));
	CSpecialDisplay_dtor(this, 0);

	if (flags & 1)
		__dl__4CBitPv(this);
}
