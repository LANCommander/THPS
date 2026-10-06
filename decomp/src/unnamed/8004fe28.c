/* FUN_8004fe28 (0x8004fe28) */
extern char DAT_800a1360[];
extern char DAT_800a136c[];
extern char DAT_800a1378[];
extern char DAT_800c0a48[];
int DAT_800d1b98[1];
void FUN_8001d250(int);
int FUN_8001dc9c(char*);
void FUN_8001e114(int,int,char*,int,int,int,int);
void FUN_800242cc(void);
void FUN_800491e8(void);
void FUN_80049474(void);
void FUN_800494dc(void);
void FUN_8004b250(int,int,int);
int FUN_8004c8a4(char*);
void FUN_8004cb10(char*);
void FUN_8004cdd0(void);
char* FUN_8004d068(int,int,int);
void FUN_8004d5d0(char*);
void FUN_8005027c(int,int,int);
void FUN_8005c780(void);
void FUN_80061d44(int,int,int,int,int,int,int);
void FUN_80061e00(int,int,int,int);
void FUN_80061ea0(void);
void FUN_8006af64(void);
void FUN_80070ff4(void);
void FUN_8008eebc(int);
void Front_ClearScreen__Fv(void);
void Mess_LoadFont__FPciii(char*,int,int,int);
void Mess_SetRGB__FUcUcUci(int,int,int,int);
void Mess_SetScale__Fi(int);
int Mess_TextHeight__FPCc(char*);
void Mess_UnloadFont__Fv(void);
void Pack_DefragmentFully__Fv(void);
void Pad_ClearTriggers__FP8SControl(char*);
void FUN_8004fe28(int a0,int a1){
  char*s0;char*a2;char*out;unsigned char*p;int c;
  int s7,i,s6,s3,s4,fp,s2,s1x,th,top,bot,tog,off,s0i;char*s1;
  tog=0;
  if(a1)FUN_8006af64();
  else Front_ClearScreen__Fv();
  Pack_DefragmentFully__Fv();
  if(a0==0)s0i=FUN_8004c8a4(DAT_800a1360);
  if(a0==1)s0i=FUN_8004c8a4(DAT_800a136c);
  s0=FUN_8004d068(s0i,1,1);
  FUN_8004cb10(s0);
  s7=0;
  FUN_8004cdd0();
  out=FUN_8004d068(12000,1,1);
  p=(unsigned char*)s0;
  a2=out;
  while(1){
    c=*p;
    if((unsigned char)c==35)break;
    i=0;
    if((unsigned char)c!=13){
      for(;;){
        if(c!=35){
          a2[i]=c;
          i++;
          p++;
          if(i<29){
            c=*p;
            if(c!=13)continue;
          }
        }
        break;
      }
    }
    a2[i]=0;
    if(*p==13)p+=2;
    s7++;
    a2+=30;
    if(s7<400)continue;
    break;
  }
  FUN_8004d5d0(s0);
  Mess_LoadFont__FPciii(DAT_800a1378,-1,-1,-1);
  FUN_8001d250(0);
  Mess_SetScale__Fi(255);
  Mess_SetRGB__FUcUcUci(150,100,25,0);
  s6=0;
  s3=FUN_8001dc9c(out)+256;
  th=Mess_TextHeight__FPCc(out)+8;
  bot=-th;
  top=s3;
  off=a0*4;
  s4=*(int*)((char*)DAT_800d1b98+off);
  Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
  Pad_ClearTriggers__FP8SControl(DAT_800c0a48+364);
  fp=0;
  FUN_800491e8();
  FUN_8005027c(a0,0,a1);
  while(1){
    s2=s6;
    FUN_8005c780();
    FUN_80049474();
    FUN_80061ea0();
    FUN_80061e00(0,tog<<8,512,240);
    FUN_80061d44(0,0,512,240,0,0,0);
    tog=1-tog;
    if(!(s6<s7))break;
    s0i=s3;
    if(s3<top){
      s1=out+fp;
      do{
        FUN_8001e114(256,s0i,s1,1,0,256,0);
        s1+=30;
        s2++;
        s0i+=th;
      }while(s2<s7&&s0i<top);
    }
    s4--;
    if(s4==0){
      s3--;
      s4=*(int*)((char*)DAT_800d1b98+off);
    }
    if(s3<bot){
      fp+=30;
      s6++;
      s3+=th;
    }
    FUN_8008eebc(0);
    FUN_8005027c(a0,1,a1);
    FUN_8008eebc(0);
    FUN_800494dc();
    FUN_80070ff4();
    FUN_800242cc();
    if(DAT_800c0a48[49]||DAT_800c0a48[413]||DAT_800c0a48[225]||DAT_800c0a48[589]||DAT_800c0a48[241]||DAT_800c0a48[605]){
      Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
      Pad_ClearTriggers__FP8SControl(DAT_800c0a48+364);
      FUN_8004b250(145,8192,0);
      break;
    }
  }
  FUN_8005027c(a0,2,a1);
  FUN_8004d5d0(out);
  Mess_UnloadFont__Fv();
}
