/* Video_SFXPlay__Fisi (0x80068e8c) */
#include "names.h"
typedef struct {
	int state, f4, f8, fc;
	unsigned *p;
	unsigned buf;
	int n;
	int f1c;
	char pad[0xa0];
} SVideoInfo;

extern SVideoInfo DAT_800bf318[];
extern int DAT_800d140c;

void QueueSoundCmd(int, int);

void Video_SFXPlay(int a, short b, int c) {
	if (DAT_800bf318[0].state == 1 && DAT_800d140c == 0)
		QueueSoundCmd(1, a);
}
