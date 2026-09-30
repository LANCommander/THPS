/* SetPos__4CBitRC7CVector (0x80027e24) */
typedef struct{int x,y,z;}V;
void SetPos__4CBitRC7CVector(char* t, V* v){ *(V*)(t+0x18) = *v; }
