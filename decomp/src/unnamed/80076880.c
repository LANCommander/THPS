/* Competition_EndGameLogic__FR13EPausedStatusRi (0x80076880) flags=-fstructure-noalias */
#include "names.h"
/* Competition end-of-game logic (COMPETITION.CPP, demo Competition_EndGameLogic), as C: after the
   results flash, kills the medal objects, records the medal, and reloads/plays the ending; else
   waits for the prompt and offers the continue menu. */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	char pad[72];
	struct VT *vt;
	char pad2[0x160 - 0x4c];
	unsigned u160;
};

struct J {
	char pad[0xc8];
	struct O *o1;
	struct O *o2;
	struct O *o3;
	char pad2[0x12c - 0xd4];
	int f;
};

struct S {
	char pad[12];
	int f;
	char q[104];
};

extern struct J DAT_800c0fdc;

struct G {
	char pad[0x984];
	int arr[4];
};

struct B {
	char pad[0x80a8];
	int a;
	char pad2[0x10154 - 0x80ac];
	int b;
};

struct L {
	char pad[0x50];
	int x[1];
	char pad2[0x78 - 0x54];
};

extern struct G DAT_800a6844;
extern struct B DAT_800a891c;
extern struct L DAT_800a5398[];
extern char DAT_800c0a48[];
extern char *DAT_800d17c8;
extern int DAT_800d1e28;
extern int DAT_800d1780;
extern int DAT_800d13d8;
extern char *DAT_800d1428;
extern char *DAT_800a5f10[];

void Flash_Update(void);
int Flash_FadeFinished(void);
void GameFMV_StopFMV(void);
void Pad_ClearAll(void);
void Pad_ClearTriggers(char *);
void Pad_ActuatorOff(int, int);
void Mess_DeleteAll(void);
void FUN_8008f4d4(int, int, int);
void Pause__Fi(int);
void Mem_Delete(int);
void GameFMV_PlayMovie(int);
void Flash_Reset(void);
int Mem_NewX(int, int, int);
int CMenu_FindEntry(char *, char *);
void CMenu_SetLine(char *, unsigned char);
int FUN_8007401c(void);
void Flash_Fade(int, int);

void Competition_EndGameLogic(int *a, int *b) {
	char *g;
	int e;

	if (DAT_800c0fdc.f) {
		Flash_Update();

		if (Flash_FadeFinished()) {
			DAT_800c0fdc.f = 0;

			if (DAT_800c0fdc.o1)
				DAT_800c0fdc.o1->vt->fn((char *)DAT_800c0fdc.o1 + DAT_800c0fdc.o1->vt->off, 3);

			if (DAT_800c0fdc.o2)
				DAT_800c0fdc.o2->vt->fn((char *)DAT_800c0fdc.o2 + DAT_800c0fdc.o2->vt->off, 3);

			if (DAT_800c0fdc.o3)
				DAT_800c0fdc.o3->vt->fn((char *)DAT_800c0fdc.o3 + DAT_800c0fdc.o3->vt->off, 3);

			e = DAT_800d1e28;
			g = DAT_800d17c8;
			DAT_800c0fdc.o1 = 0;
			DAT_800c0fdc.o2 = 0;
			DAT_800c0fdc.o3 = 0;
			DAT_800a6844.arr[*(int *)(g + 744)] |= 1 << e;
			GameFMV_StopFMV();
			Pad_ClearAll();
			Pad_ClearTriggers(DAT_800c0a48);
			Pad_ClearTriggers(DAT_800c0a48 + 364);
			Pad_ActuatorOff(0, 0);
			Pad_ActuatorOff(0, 1);
			Mess_DeleteAll();
			FUN_8008f4d4(8, 0, 0);
			Pause__Fi(10);
			Mem_Delete(DAT_800a891c.a);
			GameFMV_PlayMovie(-(*(int *)(DAT_800d17c8 + 744) + 12));
			Flash_Reset();

			DAT_800a891c.a =
			    Mem_NewX((DAT_800a5398[DAT_800d1e28].x[DAT_800d1780 - 1] + 0x17c00) * 2, 1, 1);
			DAT_800a891c.b =
			    DAT_800a891c.a + 0x17c00 + DAT_800a5398[DAT_800d1e28].x[DAT_800d1780 - 1];
			*a = 7;
		}
	} else if (*b) {
		int v = 1;

		if (DAT_800c0fdc.o1) {
			int c = DAT_800c0fdc.o1->u160 < 40;

			v = c == 0;
		}

		if (v) {
			DAT_800d13d8 = 1;
			CMenu_SetLine(DAT_800d1428, CMenu_FindEntry(DAT_800d1428, DAT_800a5f10[0]));

			if (FUN_8007401c()) {
				DAT_800c0fdc.f = 1;
				Flash_Fade(32, 0);
				return;
			}

			*a = 7;

			if (DAT_800c0fdc.o1)
				DAT_800c0fdc.o1->vt->fn((char *)DAT_800c0fdc.o1 + DAT_800c0fdc.o1->vt->off, 3);

			if (DAT_800c0fdc.o2)
				DAT_800c0fdc.o2->vt->fn((char *)DAT_800c0fdc.o2 + DAT_800c0fdc.o2->vt->off, 3);

			if (DAT_800c0fdc.o3)
				DAT_800c0fdc.o3->vt->fn((char *)DAT_800c0fdc.o3 + DAT_800c0fdc.o3->vt->off, 3);

			DAT_800c0fdc.o1 = 0;
			DAT_800c0fdc.o2 = 0;
			DAT_800c0fdc.o3 = 0;
			DAT_800a6844.arr[*(int *)(DAT_800d17c8 + 744)] |= 1 << DAT_800d1e28;
		}
	}
}
