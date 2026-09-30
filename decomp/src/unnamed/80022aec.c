/* FUN_80022aec (0x80022aec) */
struct V{int x,y,z;};
int DAT_800d1634;int DAT_800d1678;extern struct V DAT_800a6388[];
void FUN_80022aec(struct V*s){int n;if(DAT_800d1634==0){n=DAT_800d1678;if(n<8){DAT_800a6388[n]=*s;DAT_800d1678=n+1;}}}
