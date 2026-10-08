/* FUN_8002a018 (0x8002a018) */
typedef struct {
	char pad[8];
	short adj;
	short pad2;
	void (*fn)(char *, int);
} VT;

extern char DAT_8009f6b8[];

void Mem_Delete__FPv(char *p);
void FUN_80027fa4(char *p, int a);
void FUN_80027d70(char *p);

void FUN_8002a018(char *p, int f) {
	int i;

	*(char **)(p + 68) = DAT_8009f6b8;

	for (i = 0; i < *(int *)(p + 72); i++) {
		char *o = ((char **)*(char **)(p + 92))[i];

		if (o) {
			VT *v = *(VT **)(o + 68);

			v->fn(o + v->adj, 3);
		}
	}

	Mem_Delete__FPv(*(char **)(p + 92));
	Mem_Delete__FPv(*(char **)(p + 88));
	FUN_80027fa4(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
