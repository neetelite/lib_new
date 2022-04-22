#ifndef _text_h
#define _text_h

#include "./scalar/real.h"
#include "./cstring.h"
#include "./vector.h"
#include "./matrix.h"
#include "./font.h"
#include "./ui.h"

void cstr_draw(CString text, Vec3 pos, struct UI_Align align, Mat4 mat_view, Vec4 color);

#endif /* _text_h */
