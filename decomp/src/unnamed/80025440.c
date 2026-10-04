/* FUN_80025440 (0x80025440) */
extern int DAT_800d140c;
extern int DAT_800d1a24;
extern int DAT_800a7214[];
extern char DAT_800d2580[],DAT_800d1754[];
int DAT_800d1750,DAT_800d1844,DAT_800d1720,DAT_800d1774,DAT_800d1838,DAT_800d1770,DAT_800d1778,DAT_800d1718,DAT_800d2230,DAT_800d16fc;
int FUN_8008b900(char*,char*,int);
void Font_String__FUsUsPcUcUcUcUc(unsigned short,unsigned short,char*,unsigned char,unsigned char,unsigned char,unsigned char);
void FUN_8004c290(void);
int FUN_80025440(void){
  int a1,i,s1,t;
  if(DAT_800d140c==0){
    t=DAT_800d1750+1;
    DAT_800a7214[DAT_800d1750]=DAT_800d1a24-DAT_800d1844;
    DAT_800d1750=t;
    if(t==3) DAT_800d1750=0;
  }
  a1=0;
  i=0;
  DAT_800d1844=DAT_800d1a24;
  do{
    a1+=DAT_800a7214[i];
    i++;
  }while(i<3);
  s1=180/a1;
  if(a1>=16) a1=15;
  if(DAT_800d140c==0){
    DAT_800d1774=(a1<<8)/6;
    if(DAT_800d1720) DAT_800d1774=DAT_800d1774/4;
    DAT_800d1838=DAT_800d1838+DAT_800d1774*2;
    DAT_800d1770=DAT_800d1838>>8;
    DAT_800d1778=(DAT_800d1774*DAT_800d1774)>>8;
  }
  if(DAT_800d1718){
    DAT_800d2230=(DAT_800d2230+10)&127;
    FUN_8008b900(DAT_800d2580,DAT_800d1754,s1);
    if(DAT_800d16fc==0){
      if(s1>=25) Font_String__FUsUsPcUcUcUcUc(450,210,DAT_800d2580,50,100,50,1);
      else if(s1>=22) Font_String__FUsUsPcUcUcUcUc(450,210,DAT_800d2580,100,100,50,1);
      else Font_String__FUsUsPcUcUcUcUc(450,210,DAT_800d2580,(DAT_800d2230+50)&255,50,50,1);
      FUN_8004c290();
    }
  }
}
