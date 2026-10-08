/* _._6CGLine (0x800275ec) */
extern char DAT_8009f628[];
extern char DAT_800d18fc[];

void DeleteFrom__4CBitPv(void *, void *);
void FUN_80027e80(void *, int);
void __dl__4CBitPv(void *);

void CGLine_dtor(char *this, int flags) {
	*(char **)(this + 0x44) = DAT_8009f628;
	DeleteFrom__4CBitPv(this, DAT_800d18fc);
	FUN_80027e80(this, 0);

	if (flags & 1)
		__dl__4CBitPv(this);
}
