/* Utils_KillObjectsInBox__FRC7CVectorT0P5CBodyb (0x80048278) */
/* C++ (UTILS.CPP). Demo twin; locals from its MAIN.SYM. Kills every live body in the list whose
   position lies inside the box: Die() or a straight delete. Returns how many went. */
#pragma interface

struct CVector {
	int vx, vy, vz;
};

class CBody {
  public:
	char pad0[4];
	CVector mPos; /* 0x04 */
	char pad10[0x1c - 0x10];
	CBody *mpNext; /* 0x1c */
	char pad20[0x48 - 0x20];
	virtual ~CBody();
	virtual void Die();
};

extern "C" int IsDead__C5CBody(CBody *);

int Utils_KillObjectsInBox(const CVector &min, const CVector &max, CBody *p_list, bool use_die) {
	int killed = 0;

	while (p_list) {
		CBody *p_next = p_list->mpNext;

		if (!IsDead__C5CBody(p_list)) {
			CVector pos = p_list->mPos;

			if (pos.vx >= min.vx && max.vx >= pos.vx && pos.vz >= min.vz && max.vz >= pos.vz &&
			    pos.vy >= min.vy && max.vy >= pos.vy) {
				if (use_die)
					p_list->Die();
				else
					delete p_list;

				killed++;
			}
		}

		p_list = p_next;
	}

	return killed;
}
