/* ReplaceTexture__FUiPc (0x800247a8) */
typedef struct { char pad[24]; unsigned char *info; unsigned short w, h; } STexEntry;
extern int DAT_800d1a90;
extern int DAT_800d1a8c;
STexEntry *Spool_FindTextureEntry__FUi(unsigned);
void *FUN_8004c8a4(char*);
char *FUN_8004d068(void*, int, int);
void FUN_8004cb10(char*);
void FUN_8004cdd0(void);
void DownloadBMP__FPciiii(char*, int, int, int, int);
void FUN_8004d5d0(char*);
void ReplaceTexture(unsigned id, char *name){
  STexEntry *e = Spool_FindTextureEntry__FUi(id);
  if (e) {
    unsigned char *info = e->info;
    int pal = DAT_800d1a90;
    int w = e->w;
    int h = e->h;
    int k;
    char *bmp;
    pal += info[2];
    k = DAT_800d1a8c;
    bmp = FUN_8004d068(FUN_8004c8a4(name), 1, 1);
    FUN_8004cb10(bmp);
    FUN_8004cdd0();
    DownloadBMP__FPciiii(bmp, w, h, k, pal);
    FUN_8004d5d0(bmp);
  }
}
