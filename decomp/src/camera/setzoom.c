/* SetZoom__7CCameraUsUs (0x8007b0c4) */
typedef struct {
	char pad[0x488];
	int zoom;
	unsigned short frames;
	short pad2;
	int step;
} C;

void SetZoom(C *c, unsigned short target, unsigned short frames) {
	c->frames = frames;

	if (frames)
		c->step = (int)(target - c->zoom) / (int)c->frames;
	else
		c->zoom = target;
}
