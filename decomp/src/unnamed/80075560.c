/* Competition_WinLoseLogic__FR13EPausedStatusRi (0x80075560) flags=-fstructure-noalias */
#include "names.h"
/* Competition win/lose logic (COMPETITION.CPP, demo Competition_WinLoseLogic), as C; sibling of
   FUN_80076880 and written the same way. */
struct VT {
	char pad[8];
	short off;
	short p;
	void (*fn)(char *, int);
};

typedef struct O {
	char p[0x48];
	struct VT *vt;
	char q[0x160 - 0x4c];
	unsigned f160;
} O;

struct G {
	char p[0xc8];
	O *a;
	O *b;
	O *c;
	char q[0x12c - 0xd4];
	int f12c;
};

extern struct G DAT_800c0fdc;
extern int DAT_800a5f10[];
extern int DAT_800d1428;
extern int DAT_800d1780;
extern int DAT_800d1e28;

struct GA {
	char pad[0x984];
	int arr[4];
};

extern struct GA DAT_800a6844;

struct L {
	char pad[0x50];
	int x[1];
	char pad2[0x78 - 0x54];
};

extern struct L DAT_800a5398[];

struct H {
	char p[0x80a8];
	int a;
	char q[0x10154 - 0x80ac];
	int b;
};

extern struct H DAT_800a891c;
extern char DAT_800c0a48[];

struct W {
	char p[0x2e8];
	int i;
};

extern struct W *DAT_800d17c8;

void FUN_80010ac0(void);
void Flash_Reset(void);
int Flash_FadeFinished(void);
void GameFMV_PlayMovie(int);
int Mem_NewX(int, int, int);
void Mem_Delete(int);
int FUN_80073f9c(void);
int FUN_80077124(void *);
void FUN_8008f4d4(int, int, int);
int CMenu_FindEntry(int, int);
void Flash_Fade(int, int);
void Flash_Update(void);
void GameFMV_StopFMV(void);
void Mess_DeleteAll(void);
void Pad_ActuatorOff(int, int);
void Pad_ClearAll(void);
void Pad_ClearTriggers(void *);
void Pause__Fi(int);
void CMenu_SetLine(int, int);

#define DEL(o)                                                                                     \
	if (o)                                                                                         \
	(o)->vt->fn((char *)(o) + (o)->vt->off, 3)

void Competition_WinLoseLogic(int *a0, int *a1) {
	int v, e;
	struct W *gg;
	struct G *g = &DAT_800c0fdc;

	if (g->f12c) {
		Flash_Update();

		if (Flash_FadeFinished()) {
			g->f12c = 0;
			CMenu_SetLine(DAT_800d1428,
			                  CMenu_FindEntry(DAT_800d1428, DAT_800a5f10[0]) & 0xff);
			DEL(g->a);
			DEL(g->b);
			DEL(g->c);

			gg = DAT_800d17c8;
			e = DAT_800d1e28;
			g->a = 0;
			g->b = 0;
			g->c = 0;
			DAT_800a6844.arr[gg->i] |= 1 << e;
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
			GameFMV_PlayMovie(-11);
			Flash_Reset();

			DAT_800a891c.a =
			    Mem_NewX((DAT_800a5398[DAT_800d1e28].x[DAT_800d1780 - 1] + 0x17c00) * 2, 1, 1);
			DAT_800a891c.b =
			    DAT_800a891c.a + 0x17c00 + DAT_800a5398[DAT_800d1e28].x[DAT_800d1780 - 1];
			*a0 = 27;
		}
	} else {
		FUN_80010ac0();

		if (*a1) {
			if (FUN_80077124(g)) {
				v = 1;

				if (g->a) {
					int c = g->a->f160 < 40;

					v = c == 0;
				}

				if (v) {
					if (FUN_80073f9c()) {
						g->f12c = 1;
						Flash_Fade(32, 0);
						return;
					}

					*a0 = 7;
					CMenu_SetLine(DAT_800d1428,
					                  CMenu_FindEntry(DAT_800d1428, DAT_800a5f10[0]) & 0xff);
				} else
					return;
			} else {
				*a0 = 14;
			}

			DEL(g->a);
			DEL(g->b);
			DEL(g->c);

			g->a = 0;
			g->b = 0;
			g->c = 0;
			DAT_800a6844.arr[DAT_800d17c8->i] |= 1 << DAT_800d1e28;
		}
	}
}
