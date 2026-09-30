/* _._6CSuper (0x80043d5c) */
extern char DAT_800a0574[];
void FUN_8004d5d0(void*);
void FUN_80043860(char*, int);
void FUN_80043530(char*);
void __dt__6CSuper(char* t, int f){
  *(char**)(t+0x48) = DAT_800a0574;
  if (*(void**)(t+0x184)) FUN_8004d5d0(*(void**)(t+0x184));
  if (*(void**)(t+0x188)) FUN_8004d5d0(*(void**)(t+0x188));
  if (*(void**)(t+0x13c)) FUN_8004d5d0(*(void**)(t+0x13c));
  if (*(void**)(t+0x138)) FUN_8004d5d0(*(void**)(t+0x138));
  FUN_80043860(t, 0);
  if (f & 1) FUN_80043530(t);
}
