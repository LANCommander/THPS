/* Spool_FindAnim__FPc (0x80070064) */
typedef struct SAnimNode{unsigned*data;struct SAnimNode*next;}SAnimNode;
typedef struct{char name[8];unsigned n;}SAnim;
SAnimNode*DAT_800d1efc;
void*Spool_FindAnim__FPc(char*name){
  SAnimNode*node;
  void*result=0;
  for(node=DAT_800d1efc;node;node=node->next){
    unsigned*d=node->data;
    unsigned cnt=d[0];
    SAnim*a=(SAnim*)(d+1);
    int found=0;
    unsigned i;
    for(i=0;i<cnt;i++){
      char*p=name,*q=a->name;
      int k=0;
      int c1,c2;
      c1=*p;c2=*q;
      while(1){
        c1&=0xdf;c2&=0xdf;
        if(c1!=c2)break;
        if(!c2)goto match;
        if(k>=8)break;
        p++;q++;c1=*p;c2=*q;k++;
      }
      if((!c1&&!c2)||k==8){match:found=1;break;}
      a=(SAnim*)((char*)a+(a->n*8+12));
    }
    if(found){result=(char*)a+12;break;}
  }
  return result;
}
