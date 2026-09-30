/* FUN_80043a14 (0x80043a14) */
struct VT{char pad[56];short off;short pad2;void(*fn)(char*);};
char DAT_800d19b4[8];
void DeleteFrom__5CBodyPP5CBody(char*p,char*q);void FUN_800438dc(char*p,char*q);
void FUN_80043a14(char*p,char*a){struct VT*vt=*(struct VT**)(p+72);vt->fn(p+vt->off);*(char**)(p+76)=a;DeleteFrom__5CBodyPP5CBody(p,a);FUN_800438dc(p,DAT_800d19b4);*(unsigned short*)(p+82)|=1;}
