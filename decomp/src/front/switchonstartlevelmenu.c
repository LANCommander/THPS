/* Front_SwitchOnStartLevelMenu__Fv (0x8001a5b8) */
int DAT_800d13e8;

void CommonSwitchOnMenuCode__Fv(void);

void Front_SwitchOnStartLevelMenu(void) {
	DAT_800d13e8 = 33;
	CommonSwitchOnMenuCode__Fv();
}
