/* getFile__10PREManagerPcPi (0x800663d8) */
typedef struct { int pad; char *pre[16]; char names[16][16]; } PREManager;
char *parsePRE__10PREManagerPcT1Pi(PREManager*, char*, char*, int*);
char *PREManager_getFile(PREManager *m, char *name, int *size){
  char *r = 0;
  int i;
  for (i = 0; i < 16; i++)
    if (m->pre[i]) r = parsePRE__10PREManagerPcT1Pi(m, m->pre[i], name, size);
  return r;
}
