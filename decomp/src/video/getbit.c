/* GetBit__FP10SVideoInfo (0x80068d38) */
typedef struct{int state,f4,f8,fc;unsigned*p;unsigned buf;int n;}SVideoInfo;
int GetBit__FP10SVideoInfo(SVideoInfo*v){
  int b;
  if(v->n==0){v->buf=*v->p++;v->n=32;}
  v->n--;
  b=v->buf&1;
  v->buf>>=1;
  return b;
}
