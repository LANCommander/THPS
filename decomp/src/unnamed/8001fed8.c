/* FUN_8001fed8 (0x8001fed8) */
struct VT{char pad[8];short off;short pad2;void(*fn)(char*,int);};
struct O{char pad[68];struct VT*vt;};
void FUN_80043af4(char*p);
void FUN_8001fed8(char*p){struct O*o;FUN_80043af4(p);o=*(struct O**)(p+308);if(o)o->vt->fn((char*)o+o->vt->off,3);*(int*)(p+308)=0;}
