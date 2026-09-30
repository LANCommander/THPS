/* Options_RemapControllers__Fv (0x80010518) */
typedef struct{char e[4][16];char pad[284];char*f[4];}SPad;
extern SPad DAT_800c0a48[];
extern int DAT_800a7194[2][4];
void Options_RemapControllers__Fv(void){
  int i,j;
  for(i=0;i<2;i++){
    for(j=0;j<4;j++){
      switch(DAT_800a7194[i][j]){
        case 0:DAT_800c0a48[i].f[0]=DAT_800c0a48[i].e[j];break;
        case 1:DAT_800c0a48[i].f[1]=DAT_800c0a48[i].e[j];break;
        case 2:DAT_800c0a48[i].f[2]=DAT_800c0a48[i].e[j];break;
        case 3:DAT_800c0a48[i].f[3]=DAT_800c0a48[i].e[j];break;
      }
    }
  }
}
