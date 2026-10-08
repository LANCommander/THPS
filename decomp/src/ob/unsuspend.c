/* UnSuspend__5CBody (0x80043a80) */
#include "names.h"
void *SuspendedList;

void CBody_DeleteFrom(char *, void *);
void CBody_AttachTo(char *, int);

void CBody_UnSuspend(char *t) {
	int notSuspended =
	    !(*(unsigned short *)(t + 0x52) & 1); /* materialised bool (inline IsSuspended) */

	if (notSuspended)
		return;

	CBody_DeleteFrom(t, &SuspendedList);
	CBody_AttachTo(t, *(int *)(t + 0x4c));

	*(unsigned short *)(t + 0x52) &= ~1;
}
