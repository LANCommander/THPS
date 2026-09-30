/* QueueSoundCmd__F13ESoundCmdTypei (0x80068d98) */
typedef struct{int type,val;}SSoundCmd;
extern SSoundCmd DAT_800bf524[];
int DAT_800d1df8;
void QueueSoundCmd__F13ESoundCmdTypei(int type,int val){
  DAT_800bf524[DAT_800d1df8].type=type;
  DAT_800bf524[DAT_800d1df8].val=val;
  DAT_800d1df8=(DAT_800d1df8+1)%30;
}
