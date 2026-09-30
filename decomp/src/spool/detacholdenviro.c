/* DetachOldEnviro__FUc (0x8006fbe4) */
typedef struct{char name[10];unsigned char f0a,f0b;unsigned*models;unsigned*f10;char*f14;char pad[0x28];}SRegion;
extern SRegion DAT_800bf7a8[];
typedef struct SEnviro{char pad[0x1c];struct SEnviro*next;}SEnviro;
SEnviro*DAT_800d1eec;
int DAT_800d1ed0[2];
int DAT_800d1ee4[2];
void DetachOldEnviro__FUc(unsigned char idx){
  SEnviro*other=0;
  SEnviro*cur;
  int o;
  DAT_800d1ee4[idx]=0;
  cur=(SEnviro*)(DAT_800bf7a8[DAT_800d1ed0[idx]].f14+12);
  o=DAT_800d1ed0[idx^1];
  if(o!=-1)other=(SEnviro*)(DAT_800bf7a8[o].f14+12);
  if(!other){DAT_800d1eec=0;return;}
  if(cur==DAT_800d1eec){DAT_800d1eec=other;return;}
  {
    SEnviro*p=other;
    while(p->next!=cur)p=p->next;
    p->next=0;
  }
}
