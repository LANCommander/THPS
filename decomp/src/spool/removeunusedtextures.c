/* Spool_RemoveUnusedTextures__Fv (0x8006f1f8) */
#include "names.h"
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

void GotoStartOfTextureList(void);
STexture *NextTexture(void);
void Pack_Unpack(short, short);
void RemoveTextureEntry(STexture *);

void Spool_RemoveUnusedTextures(void) {
	STexture *t;

	GotoStartOfTextureList();

	while ((t = NextTexture())) {
		if ((t->u.flags & 0xf0000) && !t->u.usage) {
			t->pal->refs--;
			Pack_Unpack(t->px, t->py);
			RemoveTextureEntry(t);
		}
	}
}
