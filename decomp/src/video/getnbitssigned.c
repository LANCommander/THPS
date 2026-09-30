/* GetNBitsSigned__FP10SVideoInfoi (0x80068cec) */
typedef struct SVideoInfo SVideoInfo;
unsigned GetNBitsUnsigned__FP10SVideoInfoi(SVideoInfo*,int);
int GetNBitsSigned__FP10SVideoInfoi(SVideoInfo*v,int n){
  unsigned x=GetNBitsUnsigned__FP10SVideoInfoi(v,n);
  unsigned m=1<<(n-1);
  if(x&m)x|=-(1<<n);
  return x;
}
