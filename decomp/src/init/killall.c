/* Init_KillAll__Fv (0x80071b7c) */
extern void *DAT_800d19a4, *DAT_800d2044, *DAT_800d1998, *DAT_800d19b0, *DAT_800d1fe4, *DAT_800d1618, *DAT_800d19b4;
void FUN_80071b00(void*);
void FUN_8004ee78(void);
void FUN_8004f624(void);
void Bit_DeleteAll__Fv(void);
void Mess_DeleteAll__Fv(void);
void Init_KillAll(void){
  FUN_80071b00(DAT_800d19a4);
  FUN_80071b00(DAT_800d2044);
  FUN_80071b00(DAT_800d1998);
  FUN_80071b00(DAT_800d19b0);
  FUN_80071b00(DAT_800d1fe4);
  FUN_80071b00(DAT_800d1618);
  FUN_80071b00(DAT_800d19b4);
  FUN_8004ee78();
  FUN_8004f624();
  Bit_DeleteAll__Fv();
  Mess_DeleteAll__Fv();
}
