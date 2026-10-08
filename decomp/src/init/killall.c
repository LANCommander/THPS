/* Init_KillAll__Fv (0x80071b7c) */
extern void *DAT_800d19a4, *DAT_800d2044, *DAT_800d1998, *DAT_800d19b0, *DAT_800d1fe4,
    *DAT_800d1618, *DAT_800d19b4;

void DeleteList__FP5CBody(void *);
void TrickOb_DeleteAll__Fv(void);
void Rail_DeleteAll__Fv(void);
void Bit_DeleteAll__Fv(void);
void Mess_DeleteAll__Fv(void);

void Init_KillAll(void) {
	DeleteList__FP5CBody(DAT_800d19a4);
	DeleteList__FP5CBody(DAT_800d2044);
	DeleteList__FP5CBody(DAT_800d1998);
	DeleteList__FP5CBody(DAT_800d19b0);
	DeleteList__FP5CBody(DAT_800d1fe4);
	DeleteList__FP5CBody(DAT_800d1618);
	DeleteList__FP5CBody(DAT_800d19b4);
	TrickOb_DeleteAll__Fv();
	Rail_DeleteAll__Fv();
	Bit_DeleteAll__Fv();
	Mess_DeleteAll__Fv();
}
