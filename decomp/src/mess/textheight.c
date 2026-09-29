extern int FUN_8001d440(const char*);
extern int FUN_8001dc9c(void);
extern int FUN_8001db80(const char*);
char DAT_800d1602;
int Mess_TextHeight(const char* s){
  int r;
  if (DAT_800d1602 == 0) { r = FUN_8001d440(s); }
  else { r = FUN_8001dc9c(); r = r + FUN_8001db80(s); }
  return r;
}
