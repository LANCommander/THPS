/* Spool_RemoveUnusedTextures__Fv (0x8006f1f8) */
typedef struct {
	char pad[4];
	unsigned short refs;
} SPalette;

typedef struct STexture {
	char pad[0x10];
	union {
		unsigned flags;
		unsigned short usage;
	} u;
	int f14;
	SPalette *pal;
	short px, py;
} STexture;

void FUN_8006f094(void);
STexture *NextTexture__Fv(void);
void Pack_Unpack__Fss(short, short);
void FUN_8006efb8(STexture *);

void Spool_RemoveUnusedTextures__Fv(void) {
	STexture *t;

	FUN_8006f094();

	while ((t = NextTexture__Fv())) {
		if ((t->u.flags & 0xf0000) && !t->u.usage) {
			t->pal->refs--;
			Pack_Unpack__Fss(t->px, t->py);
			FUN_8006efb8(t);
		}
	}
}
