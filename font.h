#ifndef _font_h
#define _font_h

#include "./graphics.h"

struct Font_Glyph
{
	n32 codepoint;

	//struct Image bitmap;
	struct GL_Texture texture;

	Vec2 align_percentage;
};

struct Font_Info
{
	n32 glyph_count;
	n32 glyph_max;

	/* LEARN: Are these supposed to be here */
	n32 codepoint_max_plus_one;

	r32 ascender_height;
	r32 descender_height;
	r32 external_leading;
};

struct Font
{
	struct Font_Info info;
	struct Font_Glyph *glyphs;

	r32 *kerning_table;
	n16 *unicode_map;

	n32 bitmap_id_offset;

	n32 height;
};

int font_init(struct Font *font, char *TTFFileName, char *FontName, n32 PixelHeight, char *charset_name);
void font_free(struct Font *font);
r32 font_kerning_get(struct Font *font, n32 codepoint, n32 codepoint_previous);
struct GL_Texture font_glyph_texture_get(struct Font *font, n32 codepoint);
struct Image font_glyph_bitmap_get(struct Font *font, n32 codepoint);
Vec2 font_glyph_alignment_get(struct Font *font, n32 codepoint);

#endif /* _font_h */
