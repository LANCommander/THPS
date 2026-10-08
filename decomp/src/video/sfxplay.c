/* Video_SFXPlay__Fisi (0x80068e8c) */
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

void QueueSoundCmd__F13ESoundCmdTypei(int, int);

void Video_SFXPlay__Fisi(int a, short b, int c) {
	if (DAT_800bf318[0].state == 1 && DAT_800d140c == 0)
		QueueSoundCmd__F13ESoundCmdTypei(1, a);
}
