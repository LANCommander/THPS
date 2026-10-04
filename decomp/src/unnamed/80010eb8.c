/* FUN_80010eb8 (0x80010eb8) */
typedef struct{char p[0x4c];int f4c;char q[0x78-0x50];}E;
extern E DAT_800a5398[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;
int DAT_800d10ec;
int FUN_8004b250(int,short,int);
void FUN_80010eb8(int Speed){
  int Volume;
  if(DAT_800a5398[DAT_800d1e28].f4c){
    if(DAT_800d16a4==1){
      Volume=(Speed<<14)/80;
      DAT_800d10ec++;
      if(Volume>16384)Volume=16384;
      if(Volume<2048)Volume=2048;
      FUN_8004b250(49,Volume,0);
    }
  }
}
