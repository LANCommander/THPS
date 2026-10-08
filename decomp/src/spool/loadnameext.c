/* LoadNameExt__FPcT0 (0x80070140) */
#include "names.h"
extern char DAT_800bf654[][17];

int DAT_800d1ef8;

void LoadNameExt(char *a, char *b) {
	char *d = DAT_800bf654[DAT_800d1ef8];
	char *s = a;
	char *t = b;

	while (*s)
		*d++ = *s++;

	while (*t)
		*d++ = *t++;

	*d = 0;
}
