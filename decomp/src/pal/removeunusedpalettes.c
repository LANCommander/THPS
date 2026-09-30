/* Pal_RemoveUnusedPalettes__Fv (0x8004ac2c) */
typedef struct SPalette{char pad[2];unsigned char slot,flags;unsigned short usage;char pad6[10];struct SPalette*next;}SPalette;
SPalette*DAT_800d1a80;
extern unsigned char DAT_800d2a10[],DAT_800d2b10[];
void FUN_8004ab88(SPalette*);
void Pal_RemoveUnusedPalettes__Fv(void){
  SPalette*p=DAT_800d1a80;
  while(p){
    SPalette*next=p->next;
    if(!p->usage){
      if(p->flags&1)DAT_800d2a10[p->slot]=1;
      if(p->flags&2)DAT_800d2b10[p->slot]=1;
      FUN_8004ab88(p);
    }
    p=next;
  }
}
