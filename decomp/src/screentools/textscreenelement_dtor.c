/* _._17TextScreenElement (0x8002da78) */
extern char DAT_8009f708[];

void Mem_Delete__FPv(void *);
void CSpecialDisplay_dtor(void *, int);
void FUN_80027d70(void *);

void TextScreenElement_dtor(char *this, int flags) {
	*(char **)(this + 0x44) = DAT_8009f708;
	Mem_Delete__FPv(*(void **)(this + 0x50));
	CSpecialDisplay_dtor(this, 0);

	if (flags & 1)
		FUN_80027d70(this);
}
