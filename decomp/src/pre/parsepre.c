/* parsePRE__10PREManagerPcT1Pi (0x80066460) */
int FUN_8008f6ec(char*);
int FUN_8008f6fc(char*, char*);
char *parsePRE__10PREManagerPcT1Pi(void *m, char *buf, char *name, int *size){
  int n = *(int*)buf;
  int i;
  buf += 4;
  for (i = 0; i < n; i++) {
    char *nm;
    int sz,len;
    len = FUN_8008f6ec(buf);
    nm = buf;
    buf += (len + 4) & ~3;
    sz = *(int*)buf;
    buf += 4;
    if (!FUN_8008f6fc(nm, name)) { *size = sz; return buf; }
    buf += (sz + 3) & ~3;
  }
  return 0;
}
