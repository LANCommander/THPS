/* Card_GetDirAndFreeBlocks__Fii (0x80015164) */
extern int DAT_800a5880[];
extern char DAT_800a584d[];
extern char DAT_800a5869[];
extern char DAT_800a58bc[];
extern char DAT_8009e118[];
int FUN_8008b900(char*,char*,int,int);
char*FUN_8008ec1c(char*,char*);
char*FUN_8008ea58(char*);
int Utils_CompareStrings__FPCcT0Ui(char*,char*,unsigned);
int Card_GetDirAndFreeBlocks__Fii(int a,int b){
  char buf[32];
  int total,i;
  char*p;
  total=0;
  for(i=total;i<15;i++)DAT_800a5880[i]=3;
  FUN_8008b900(buf,DAT_8009e118,a,b);
  p=DAT_800a58bc;
  if(FUN_8008ec1c(buf,p)==p){
    i=0;
    do{
      total+=*(int*)(p+24);
      if(Utils_CompareStrings__FPCcT0Ui(p,DAT_800a584d,17))DAT_800a5880[i]=0;
      else if(Utils_CompareStrings__FPCcT0Ui(p,DAT_800a5869,17))DAT_800a5880[i]=1;
      i++;
      p+=40;
    }while(FUN_8008ea58(p)==p);
  }
  total/=8192;
  return 15-total;
}
