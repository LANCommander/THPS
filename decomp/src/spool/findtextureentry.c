/* Spool_FindTextureEntry__FUi (0x8006f048) */
typedef struct STexture {
	char pad[0x14];
	unsigned id;
	char pad2[8];
	struct STexture *next;
} STexture;

extern STexture *DAT_800c01a8[];

STexture *Spool_FindTextureEntry__FUi(unsigned id) {
	STexture *t = DAT_800c01a8[id & 511];

	while (t && t->id != id)
		t = t->next;

	return t;
}
