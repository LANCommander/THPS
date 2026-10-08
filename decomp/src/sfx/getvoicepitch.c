/* SFX_GetVoicePitch__FUi (0x8004b590) */
typedef struct {
	short left, right;
} VOL;

typedef struct {
	unsigned long voice;
	unsigned long mask;
	VOL volume;
	VOL volmode;
	VOL volumex;
	unsigned short pitch;
	unsigned short note;
	unsigned short sample_note;
	short envx;
	unsigned long addr;
	unsigned long loop_addr;
	long a_mode;
	long s_mode;
	long r_mode;
	unsigned short ar, dr, sr, rr, sl, adsr1, adsr2;
} VATTR;

int DAT_800d1a9c;

extern void FUN_80094f70(VATTR *);

int SFX_GetVoicePitch(unsigned v) {
	VATTR a;

	if (DAT_800d1a9c)
		return 1000;

	if (v) {
		a.voice = v;
		FUN_80094f70(&a);
		return a.pitch;
	}
}
