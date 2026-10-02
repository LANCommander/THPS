/* FUN_8005e4ec (0x8005e4ec) */
struct VT{char pad[8];short off;short pad2;void(*fn)(char*,int);short off2;short pad3;void(*fn2)(char*);};
typedef struct{struct VT*vt;}O;
extern unsigned char DAT_800c0a48[];
void Pad_ClearTriggers__FP8SControl(unsigned char*);
O* __nw__5CItemUi(int);
O* FUN_800652e4(O*,int,int,int,int,int,int,int,int);
O* FUN_80063e34(O*,int);
void FUN_8005c934(void);
void FUN_80070ff4(void);
void FUN_800242cc(void);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void FUN_8006b26c(void);
void FUN_8004b250(int,int,int);
void erase__12VerticalMenu(O*);
int FUN_8005e4ec(int a,int b,int c){
  int r,i;
  O*m;O*n;
  r=0;
  Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
  Pad_ClearTriggers__FP8SControl(DAT_800c0a48+364);
  m=__nw__5CItemUi(820);
  if(m) m=FUN_800652e4(m,100,398,15,a,b,0,0,0);
  n=__nw__5CItemUi(284);
  if(n) n=FUN_80063e34(n,-1);
  do{
    FUN_8005c934();
    FUN_80070ff4();
    FUN_800242cc();
    FUN_8006b240();
    FUN_80061ea0();
    m->vt->fn2((char*)m+m->vt->off2);
    FUN_8006b26c();
    if(DAT_800c0a48[0xe1]||DAT_800c0a48[0x24d]||DAT_800c0a48[0x31]||DAT_800c0a48[0x19d]||DAT_800c0a48[1]||DAT_800c0a48[0x16d]){
      Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
      Pad_ClearTriggers__FP8SControl(DAT_800c0a48+364);
      FUN_8004b250(145,0x2000,0);
      r=-1;
    }
    if(c!=-1){
      c--;
      if(c<0) r=-1;
    }
  }while(r==0);
  i=0;
  do{
    i++;
    FUN_8006b240();
    FUN_80061ea0();
    erase__12VerticalMenu(m);
    FUN_8006b26c();
  }while(i<2);
  if(m) m->vt->fn((char*)m+m->vt->off,3);
  if(n) n->vt->fn((char*)n+n->vt->off,3);
  return r;
}
