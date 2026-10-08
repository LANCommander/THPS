/* Pad_InitAtStart__Fv (0x80070878) */
#include "names.h"
typedef struct {
	char c[0x10];
} SControl;

typedef struct {
	SControl a, b, c, d;
	char _40[0x15c - 0x40];
	SControl *pa, *pc, *pb, *pd;
} Pad;

extern Pad DAT_800c0a48[];
extern char controllers[];

int Pad_IdleTime, ControlSystemInitialised;

extern void Pad_ClearAll(void);
extern void FUN_80096304(char *, char *);
extern void FUN_80096050(void);
extern void ResetMainDemoTimer(void);

void Pad_InitAtStart(void) {
	int i;

	for (i = 0; i < 2; i++) {
		DAT_800c0a48[i].pa = &DAT_800c0a48[i].a;
		DAT_800c0a48[i].pb = &DAT_800c0a48[i].c;
		DAT_800c0a48[i].pc = &DAT_800c0a48[i].b;
		DAT_800c0a48[i].pd = &DAT_800c0a48[i].d;
	}

	Pad_ClearAll();
	FUN_80096304(controllers, controllers + 34);
	FUN_80096050();

	Pad_IdleTime = 0;
	ResetMainDemoTimer();

	ControlSystemInitialised = 1;
}
