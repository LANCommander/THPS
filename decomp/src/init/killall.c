/* Init_KillAll__Fv (0x80071b7c) */
#include "names.h"
extern void *DAT_800d19a4, *DAT_800d2044, *DAT_800d1998, *DAT_800d19b0, *DAT_800d1fe4,
    *DAT_800d1618, *DAT_800d19b4;

void DeleteList(void *);
void TrickOb_DeleteAll(void);
void Rail_DeleteAll(void);
void Bit_DeleteAll(void);
void Mess_DeleteAll(void);

void Init_KillAll(void) {
	DeleteList(DAT_800d19a4);
	DeleteList(DAT_800d2044);
	DeleteList(DAT_800d1998);
	DeleteList(DAT_800d19b0);
	DeleteList(DAT_800d1fe4);
	DeleteList(DAT_800d1618);
	DeleteList(DAT_800d19b4);
	TrickOb_DeleteAll();
	Rail_DeleteAll();
	Bit_DeleteAll();
	Mess_DeleteAll();
}
