/* _._11CBackground (0x8007821c) */
#include "names.h"
extern char __vt_11CBackground[];

char *BackgroundList;
unsigned short CurrentIndex;

void CBody_DeleteFrom(char *, void *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__11CBackground(char *t, int f) {
	*(char **)(t + 0x48) = __vt_11CBackground;
	CBody_DeleteFrom(t, &BackgroundList);

	CurrentIndex--;
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
