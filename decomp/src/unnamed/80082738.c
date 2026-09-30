/* FUN_80082738 (0x80082738) */
struct B{int x;int pad[7];int g[20][20];};
extern struct B DAT_800c4e0c[];
void FUN_80082738(int a){int i,j;if(a<2){DAT_800c4e0c[a].x=0;for(i=0;i<20;i++)for(j=0;j<20;j++)DAT_800c4e0c[a].g[i][j]=0;}}
