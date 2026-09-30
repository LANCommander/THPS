/* unloadPRE__10PREManagerPc (0x80066338) */
typedef struct { int pad; char *pre[16]; char names[16][16]; } PREManager;
extern char DAT_800d1dbc[];
int FUN_8008f6fc(char*, char*);
void FUN_8004d5d0(void*);
void unloadPRE__10PREManagerPc(PREManager *m, char *name){
  int i=0;
  char*n=m->names[0];
  char**pp=m->pre;
  for (; i < 16; i++) {
    if (!FUN_8008f6fc(n, name)) {
      n[0] = DAT_800d1dbc[0];
      if (*pp) FUN_8004d5d0(*pp);
      *pp = 0;
      return;
    }
    pp++;
    n+=16;
  }
}
