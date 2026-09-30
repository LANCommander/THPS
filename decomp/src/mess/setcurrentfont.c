/* Mess_SetCurrentFont__FPc (0x8001f144) */
typedef struct{char name[0x1a];unsigned short scale;char pad2[8];}Font;
int DAT_800d15e0;
int DAT_800d15e4;
extern Font DAT_800a6110[];
extern int FUN_8008f6fc(char*,char*);
void Mess_SetCurrentFont(char*name){
  int i;
  for(i=0;i<DAT_800d15e0;i++){
    if(!FUN_8008f6fc(name,DAT_800a6110[i].name)) break;
  }
  DAT_800d15e4=i;
}
