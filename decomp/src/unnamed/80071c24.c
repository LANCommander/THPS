/* FUN_80071c24 (0x80071c24) */
typedef struct {
	int x, y, z;
} V;

extern short DAT_800a679e[];
extern char DAT_800a5be9[];
extern int DAT_800d16e4, DAT_800d1768, DAT_800d19c0;
extern int DAT_800d16f0, DAT_800d16f4;

void FUN_8004b8e0(void);
void FUN_8004b8e8(void);
void FUN_8004ba34(void);
void GameFMV_StopFMV__Fv(void);
void Init_KillAll__Fv(void);
void FUN_800448b8(void);
void FUN_8004e1e0(void);
void FUN_8004bb5c(void);
void FUN_8004b180(void);
void SFX_ReverbOff__Fv(void);
void Spool_ClearAllPSXs__Fv(void);
void Trig_RemoveDualBuffer__Fv(void);
void Trig_DeleteTrigFile__Fv(void);
void Pack_DefragmentFully__Fv(void);
void Spool_ClearEnvironmentRegions__Fv(void);
void Redbook_InitialRand__Fi(int);
void Trig_ClearTrigMenu__Fv(void);
void FUN_800827ac(void);
void Flash_Reset__Fv(void);
void FUN_8004ee24(void);
void FUN_8004f5d0(void);
void FUN_8002ef24(V *);
void Pad_ClearAll__Fv(void);

static inline void VI(V *p, int x, int y, int z) {
	p->x = x;
	p->y = y;
	p->z = z;
}

void FUN_80071c24(int a) {
	V v;

	FUN_8004b8e0();
	FUN_8004b8e8();
	FUN_8004ba34();

	DAT_800a679e[0] = 256;
	GameFMV_StopFMV__Fv();
	Init_KillAll__Fv();
	FUN_800448b8();
	FUN_8004e1e0();

	if (a == 0) {
		FUN_8004bb5c();
		FUN_8004b180();
		SFX_ReverbOff__Fv();
		Spool_ClearAllPSXs__Fv();
		Trig_RemoveDualBuffer__Fv();
		Trig_DeleteTrigFile__Fv();
		Pack_DefragmentFully__Fv();

		DAT_800a5be9[0] = 0;
	} else {
		Spool_ClearEnvironmentRegions__Fv();
	}

	Redbook_InitialRand__Fi(0x12a6cc58);
	Trig_ClearTrigMenu__Fv();
	FUN_800827ac();
	Flash_Reset__Fv();
	FUN_8004ee24();
	FUN_8004f5d0();
	VI(&v, 0, 0x8000, 0);
	FUN_8002ef24(&v);

	DAT_800d16e4 = 0;
	Pad_ClearAll__Fv();

	DAT_800d19c0 = 13000;
	DAT_800d1768 = 0;
	DAT_800d16f0 = 0x7fffffff;
	DAT_800d16f4 = 0x7fffffff;
}
