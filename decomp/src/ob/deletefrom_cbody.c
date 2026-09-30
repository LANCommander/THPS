/* DeleteFrom__5CBodyPP5CBody (0x80043908) */
typedef struct CBody{char pad[0x1c];struct CBody* next;char pad2[0x30-0x20];struct CBody* prev;char pad3[0x52-0x34];unsigned short flags;}CBody;

CBody* DAT_800d19b4;
void UnSuspend__5CBody(CBody*);
void DeleteFrom__5CBodyPP5CBody(CBody* t, CBody** head){
  if ((t->flags & 1) && head != &DAT_800d19b4)
    UnSuspend__5CBody(t);
  if (t->next) t->next->prev = t->prev;
  if (t->prev) t->prev->next = t->next;
  if (*head == t) *head = t->next;
}
