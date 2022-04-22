struct OS_Window
os_window_find(CString window_name)
{
	/* TODO: Error checking */
	Atom atom = XInternAtom(os_display.handle, "_NET_CLIENT_LIST", TRUE);

	Atom actual_type;
	i32 format;
	n64 item_count;
	n64 byte_after_count;
	unsigned char *data;

	i32 ret = XGetWindowProperty(os_display.handle, os_display.window_root.handle,
								 atom, 0L, (~0L), FALSE,
								 AnyPropertyType, &actual_type, &format,
								 &item_count, &byte_after_count, &data
		);

	struct OS_Window result = os_window_init();
	if(ret < 0 || item_count <= 0) return(result);

	char *window_name_tmp;
	Bool found = FALSE;

	Window *window_list = (Window *)data;
	for(i32 i = 0; i < item_count; ++i)
	{
		ret = XFetchName(os_display.handle, window_list[i], &window_name_tmp);
		if(ret < 0) continue;

		if(cstr_eql(window_name_tmp, window_name))
		{
			found = TRUE;
			result.handle = window_list[i];
			break;
		}
	}

	if(found == TRUE) XGetWindowAttributes(os_display.handle, result.handle, &result.attributes);

	XFree(window_name_tmp);
	XFree(data);

	return(result);
}
