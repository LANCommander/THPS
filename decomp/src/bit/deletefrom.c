/* DeleteFrom__4CBitPv (0x80027dbc) */
void DeleteFrom__4CBitPv(void **t, void **head) {
	if (t[1])
		((void **)t[1])[0] = t[0];

	if (t[0])
		((void **)t[0])[1] = t[1];

	if (*head == t)
		*head = t[1];
}
