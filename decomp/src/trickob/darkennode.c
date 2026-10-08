/* TrickOb_DarkenNode__Fi (0x8004f24c) */
#include "names.h"
typedef struct Node {
	int _0;
	unsigned key;
	unsigned short id;
	unsigned char used;
	unsigned char b;
	unsigned short w;
	short _e;
	struct Node *next;
	struct Item *it;
} Node;

typedef struct Item {
	unsigned short flags;
	char _2[0x1e];
	unsigned c;
} Item;

extern int DAT_800d16a4;

Node *DAT_800d1b70;
unsigned char DAT_800d1b8c;
unsigned short DAT_800d1b90;

Item *Spool_FindEnviroItem(unsigned);

void TrickOb_DarkenNode(int id) {
	Node *n;

	if (DAT_800d16a4 == 8) {
		for (n = DAT_800d1b70; n; n = n->next) {
			if (n->id == id) {
				Item *it;

				if (n->used && DAT_800d16a4 != 8)
					return;

				it = Spool_FindEnviroItem(n->key);
				n->w = DAT_800d1b90;
				n->it = it;
				n->b = DAT_800d1b8c;
				it->c = 0x202020;
				it->flags |= 0x400;
				n->used = 1;
				return;
			}
		}
	}
}
