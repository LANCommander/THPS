/* FUN_80061ef4 (0x80061ef4) */
typedef struct{void*f0;int f4,f8,fc,f10;unsigned short*f14;int f18,f1c,f20,f24;short f28;short pad;int f2c,f30;}S;
extern char DAT_800a21a0[];
extern unsigned short* FUN_8004d068(int,int,int);
extern void FUN_8004d5d0(void*);
S* FUN_80061ef4(S*s,unsigned short*src,int w,int h,int cw,int ch,int bpp,unsigned short fl){
  unsigned short *d,*p,*u;
  int i,j,k,r,k2,j2;
  s->f0=DAT_800a21a0;
  s->f2c=0;
  s->f24=bpp;
  s->f28=fl;
  if(bpp==8)w=w>>1;
  if(cw==0)cw=w;
  if(ch==0)ch=h;
  s->f4=w;
  s->f8=h;
  s->fc=cw;
  s->f10=ch;
  s->f18=0;
  s->f1c=w/cw;
  s->f20=(h+ch-1)/ch;
  s->f14=FUN_8004d068(w*h*2,1,1);
  d=s->f14;
  p=src;
  for(i=0;i<s->f1c;i++){
    for(j=0;j<s->f8;j++){
      for(k=0;k<s->fc;k++){*d++=*p++;}
      p+=s->f4-s->fc;
    }
    p+=s->fc-s->f4*s->f8;
  }
  r=s->f4-s->f1c*s->fc;
  if(r>0){
    for(j2=0;j2<s->f8;j2++){
      for(k2=0;k2<r;k2++){*d++=*p++;}
      p+=s->f4-r;
    }
    s->f1c=s->f1c+1;
  }
  FUN_8004d5d0(src);
  s->f30=0;
  return s;
}
