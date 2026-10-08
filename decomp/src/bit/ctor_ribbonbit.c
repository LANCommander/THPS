/* __10CRibbonBit (0x80029d80) */
extern char DAT_8009f6d0[];

void __16CLinked2EndedBit(char *, int);

char *CRibbonBit_ctor(char *this, int n) {
	__16CLinked2EndedBit(this, n);

	*(char **)(this + 0x44) = DAT_8009f6d0;
	return this;
}
