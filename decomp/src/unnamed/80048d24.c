/* FUN_80048d24 (0x80048d24) */
typedef struct { char p0[0x70]; int f70; int f74; int f78; int f7c; int f80; int arr[(0x80ac-0x84)/4]; } E;
extern E DAT_800a891c[];
extern int FUN_80048c74(void);
extern int FUN_8008c94c(void *a);
extern int FUN_8008c8dc(void *a);
void FUN_80048d24(void){
  int i; int *q;
  for(i=0;i<2;i++){
    if(DAT_800a891c[i].f74){
      if(!DAT_800a891c[i].f78 && !DAT_800a891c[1-i].f78 && !DAT_800a891c[i].f70){
        DAT_800a891c[i].f74=0;
        DAT_800a891c[i].f78=1;
        FUN_8008c94c(&DAT_800a891c[i]);
        q=&DAT_800a891c[i].arr[FUN_80048c74()];
        FUN_8008c8dc(q-1);
      }
    }
  }
}
