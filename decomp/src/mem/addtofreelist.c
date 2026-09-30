/* AddToFreeList__FP12SBlockHeaderi (0x8004ce54) */
typedef struct SBlockHeader{struct SBlockHeader*next;unsigned size;}SBlockHeader;
SBlockHeader*DAT_800d1b64[2];
void AddToFreeList__FP12SBlockHeaderi(SBlockHeader*b,int idx){
  SBlockHeader*cur=DAT_800d1b64[idx];
  SBlockHeader*prev=0;
  while(cur<b&&cur){
    prev=cur;
    cur=cur->next;
  }
  if(prev){
    unsigned psz=prev->size;
    unsigned pu=psz>>4;
    unsigned pu8=pu+8;
    if((SBlockHeader*)((char*)prev+pu8)==b){
      unsigned bu=b->size>>4;
      if((SBlockHeader*)((char*)b+(bu+8))==cur){
        unsigned t=pu+16;
        prev->next=cur->next;
        t+=(b->size>>4)+(cur->size>>4);
        prev->size=(psz&15)|(t<<4);
      }else{
        prev->size=(psz&15)|((pu8+bu)<<4);
      }
      return;
    }
    prev->next=b;
  }else{
    DAT_800d1b64[idx]=b;
  }
  {
    unsigned bsz=b->size;
    unsigned bu8=(bsz>>4)+8;
    if((SBlockHeader*)((char*)b+bu8)==cur){
      b->next=cur->next;
      b->size=(bsz&15)|((bu8+(cur->size>>4))<<4);
    }else{
      b->next=cur;
    }
  }
}
