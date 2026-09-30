/* M3d_BuildTransform__FP6CSuper (0x80085130) */
void FUN_8008b68c(char*, char*);
void FUN_8008b3d4(char*, char*);
void FUN_8008b4e0(char*, char*);
void M3d_BuildTransform(char* t){
  char* m = t + 0x164;
  if (*(unsigned*)(t+0x134) & 1) {
    FUN_8008b68c(t+0x78c, m);
    *(short*)(t+0x166) = -*(unsigned short*)(t+0x166);
    *(short*)(t+0x16c) = -*(unsigned short*)(t+0x16c);
    *(short*)(t+0x172) = -*(unsigned short*)(t+0x172);
  } else {
    FUN_8008b3d4(t+0x10, m);
  }
  if (*(unsigned short*)t & 0x200) FUN_8008b4e0(t, m);
  *(int*)(t+0x178) = *(int*)(t+4) >> 12;
  *(int*)(t+0x17c) = *(int*)(t+8) >> 12;
  *(int*)(t+0x180) = *(int*)(t+12) >> 12;
}
