/* FUN_80071d60 (0x80071d60) */
typedef struct{short x,y,w,h;}R;
extern char DAT_800c5b00[];extern char* DAT_800d2160;extern char* DAT_800d2164;extern R DAT_800d1f8c[];void FUN_80047870(void);
int FUN_80096b84(void);void FUN_80014d5c(int a);void Pad_InitAtStart__Fv(void);void FUN_800971a4(void);void FUN_8008c1a0(int a);void FUN_8008c314(int a);void FUN_800491a0(void);
void FUN_8008c5ec(R*r,int a,int b,int c);void FUN_80096c14(void(*a)(void));void FUN_8008c3d0(int a);void FUN_800785cc(int a);void FUN_8004b038(void);void FileIO_Init__Fv(void);void FUN_80022b4c(void);
void FUN_80071d60(void){
R r;
DAT_800d2160=DAT_800c5b00;
DAT_800d2164=DAT_800c5b00+3200;
FUN_80096b84();FUN_80014d5c(1);Pad_InitAtStart__Fv();FUN_800971a4();FUN_8008c1a0(0);FUN_8008c314(0);FUN_800491a0();
r=DAT_800d1f8c[0];
FUN_8008c5ec(&r,0,0,0);
FUN_80096c14(FUN_80047870);FUN_8008c3d0(1);FUN_800785cc(0x9f6ad);FUN_8004b038();FileIO_Init__Fv();FUN_80022b4c();
}
