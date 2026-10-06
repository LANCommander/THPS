/* FUN_8005f9ec (0x8005f9ec) */
typedef struct{int x,y,z;}V;
extern int DAT_800a4118[];
extern volatile unsigned char DAT_800c0a48[];
extern int DAT_800d13cc;
extern int DAT_800d13d0;
extern short DAT_800d1658;
int DAT_800d1d5c;
int DAT_800d1d60;
int FUN_8006516c(int);
void FUN_8002357c(int);
void Pad_ClearTriggers__FP8SControl(volatile unsigned char*);
void FUN_8004b250(int,int,int);
void GameFMV_StopFMV__Fv(void);
void FUN_80023168(int);
void FUN_80022aec(V*);
void GameFMV_StartFMV__Fi(int);
void draw__6Spriteiiiiii(int,int,int,int,int,int,int);
void FUN_8005f9ec(int a){
  int v,w,u,s0,s1,s2;
  volatile unsigned char*p;volatile unsigned char*pp;
  V t;V*q;
  DAT_800d13d0=FUN_8006516c(a)==1?DAT_800a4118[1]*0x555:0;
  DAT_800d13cc=DAT_800a4118[0]*0x555;
  FUN_8002357c(0);
  p=DAT_800c0a48;
  if(p[0x81]||p[0x1ed]||p[0x91]||p[0x1fd]){
    s2=0;
    if(p[0x81]||p[0x1ed])s2=1;
    pp=DAT_800c0a48;
    Pad_ClearTriggers__FP8SControl(pp);
    Pad_ClearTriggers__FP8SControl(pp+364);
    if(FUN_8006516c(a)==0){
      w=DAT_800a4118[0]+1;
      if(s2)w=DAT_800a4118[0]-1;
      DAT_800a4118[0]=w;
      if(w<0)DAT_800a4118[0]=0;
      v=DAT_800a4118[0];
      if(v>=12){DAT_800a4118[0]=12;v=12;}
      DAT_800d13cc=v*0x555;
      FUN_8004b250(145,8192,0);
    }
    if(FUN_8006516c(a)==1){
      u=DAT_800a4118[1]+1;
      if(s2)u=DAT_800a4118[1]-1;
      DAT_800a4118[1]=u;
      if(u<0)DAT_800a4118[1]=0;
      if(DAT_800a4118[1]>=12)DAT_800a4118[1]=12;
    }
    p=DAT_800c0a48;
  }
  if(p[0xe1]||p[0x24d]||p[0x31]||p[0x19d]){
    pp=DAT_800c0a48;
    if(FUN_8006516c(a)==0){
      Pad_ClearTriggers__FP8SControl(pp);
      Pad_ClearTriggers__FP8SControl(pp+364);
      FUN_8004b250(145,8192,0);
    }
    s0=0;
    if(FUN_8006516c(a)==1){
      pp=DAT_800c0a48;
      Pad_ClearTriggers__FP8SControl(pp);
      Pad_ClearTriggers__FP8SControl(pp+364);
      GameFMV_StopFMV__Fv();
      q=&t;t.x=0;q->y=0;q->z=0;
      FUN_80023168(2);
      FUN_80022aec(&t);
      DAT_800d1658=-1;
      GameFMV_StartFMV__Fi(0);
    }
  }else s0=0;
  s1=206;
  do{
    v=32;if(s0<DAT_800a4118[0])v=128;
    draw__6Spriteiiiiii(DAT_800d1d5c,s1,204,0,v,v,v);
    v=32;if(s0<DAT_800a4118[1])v=128;
    draw__6Spriteiiiiii(DAT_800d1d60,s1,284,0,v,v,v);
    s1+=24;s0++;
  }while(s0<12);
}
