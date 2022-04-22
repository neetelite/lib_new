#ifndef _ui_h
#define _ui_h

#include "./cstring.h"

enum UI_AlignV
{
	UI_ALIGN_V_NULL,

	UI_ALIGN_V_BOTTOM,
	UI_ALIGN_V_CENTER,
	UI_ALIGN_V_TOP,
};

enum UI_AlignH
{
	UI_ALIGN_H_NULL,

	UI_ALIGN_H_LEFT,
	UI_ALIGN_H_MIDDLE,
	UI_ALIGN_H_RIGHT,
};


struct UI_Align
{
	enum UI_AlignV v;
	enum UI_AlignH h;
};

/* Functions */
struct UI_Align UI_ALIGN(CString v, CString h);

#endif /* _ui_h */
