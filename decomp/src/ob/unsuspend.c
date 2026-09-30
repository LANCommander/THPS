/* UnSuspend__5CBody (0x80043a80) */
void* DAT_800d19b4;
void DeleteFrom__5CBodyPP5CBody(char*, void*);
void FUN_800438dc(char*, int);
void UnSuspend__5CBody(char* t){
  int notSuspended = !(*(unsigned short*)(t+0x52) & 1); /* materialised bool (inline IsSuspended) */
  if (notSuspended) return;
  DeleteFrom__5CBodyPP5CBody(t, &DAT_800d19b4);
  FUN_800438dc(t, *(int*)(t+0x4c));
  *(unsigned short*)(t+0x52) &= ~1;
}
