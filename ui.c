#include "./ui.h"
#include "./debug.h"

/* Constructors */
struct UI_Align
UI_ALIGN(CString v, CString h)
{
	struct UI_Align result = {0};

	if(0) {}
	else if(cstr_eql_n(v, "null", 4))	result.v = UI_ALIGN_V_NULL;
	else if(cstr_eql_n(v, "top", 3))    result.v = UI_ALIGN_V_TOP;
	else if(cstr_eql_n(v, "center", 6)) result.v = UI_ALIGN_V_CENTER;
	else if(cstr_eql_n(v, "bottom", 6)) result.v = UI_ALIGN_V_BOTTOM;
	else DBG_ERROR("Bad alignment\n");

	if(0) {}
	else if(cstr_eql_n(h, "null", 4))	result.h = UI_ALIGN_H_NULL;
	else if(cstr_eql_n(h, "left", 4))   result.h = UI_ALIGN_H_LEFT;
	else if(cstr_eql_n(h, "middle", 6)) result.h = UI_ALIGN_H_MIDDLE;
	else if(cstr_eql_n(h, "right", 5))  result.h = UI_ALIGN_H_RIGHT;
	else DBG_ERROR("Bad alignment\n");

	return(result);
}
