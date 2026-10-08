/* Video_SyncObsIfNeeded__Fv (0x800695f4) */
#include "names.h"
typedef struct {
	short a, b;
	int c;
} SVideoMark;

typedef struct {
	int state, f4, f8, fc;
	unsigned *p;
	unsigned buf;
	int n;
	int f1c;
	char pad[0x30];
	SVideoMark marks[14];
} SVideoInfo;

extern SVideoInfo DAT_800bf318[];

int DAT_800d1de8;

void Video_SyncObs(int);

void Video_SyncObsIfNeeded(void) {
	int n = DAT_800d1de8;

	if (n == 1) {
		if (DAT_800bf318[0].marks[0].a == 1)
			return;

		Video_SyncObs(DAT_800bf318[0].marks[0].a - 1);
	} else {
		Video_SyncObs(DAT_800bf318[0].marks[n - 1].a - DAT_800bf318[0].marks[n - 2].b - 2);
	}
}
