#define STB_TRUETYPE_IMPLEMENTATION

#include "../inc/stb_truetype.h"

#include "./font.h"
#include "./vector.h"
#include "./debug.h"

typedef struct GlyphResult
{
	Vec2  align_percentage;
	r32 kerning_change;
	r32 char_advance;

	n32 width;
	n32 height;
	n32 *pixels;
} GlyphResult;

typedef struct CodepointMask
{
	n32 codepoint_max_plus_one;
	n32 glyph_count;
	n32 *codepoint_from_glyph;
} CodepointMask;


i32
glyph_load(GlyphResult *result, stbtt_fontinfo *font_info,  n32 codepoint, Vec2 max_glyph_dim,
	   n32 font_size, r32 scale, r32 descent, void *memory_out)
{
	i32 width, height, offset_x, offset_y;
	/* LEARN: - Why do we pass scale twice?? */
	n8 *FontBits = stbtt_GetCodepointBitmap(font_info, scale, scale, (i32)codepoint,
						&width, &height, &offset_x, &offset_y);

	r32 kerning_change = 0;
	Vec2 align_percentage = {0.5f, 0.5f};
	r32 char_advance = 0;

	#if 0
	if(!(((width > 0) && (width <= (max_glyph_dim.x - 2))) &&
		 ((height > 0) && (height <= (max_glyph_dim.y - 2)))))
	{
		fprintf(stderr,
			"DBG_ERROR: Glyph (codepoint: %u) bound out of range, got a %ux%u with a max dim of %ux%u\n",
			codepoint, width, height, max_glyph_dim.x, max_glyph_dim.y);
	}
	#endif

	n32 Bpp = 4;

	n32 out_width  = width  + 2;
	n32 out_height = height + 2;
	n32 out_pitch  = out_width * Bpp;

	memset(memory_out, 0, out_height * out_pitch);

	result->width = out_width;
	result->height = out_height;
	result->pixels = (n32 *)memory_out;

	/* NOTE - Start on the first line and first horizontal space */
	n8 *dst_row = (n8 *)memory_out + (out_height * out_pitch) - out_pitch;
	n8 *src_row = FontBits;
	for(n32 y = 0; y < height; ++y)
	{
		n8 *src = (n8 *)src_row;
		n32 *dst = (n32 *)dst_row + 1;
		for(n32 x = 0; x < width; ++x)
		{
			n32 pixel = *src;
			n32 gray = (pixel & 0xFF);
			*dst++ = ((gray << 24) | 0x00FFFFFF);
			++src;
		}

		dst_row -= out_pitch;
		src_row += width;
	}

	i32 advance, LSB;
	stbtt_GetCodepointHMetrics(font_info, (i32)codepoint, &advance, &LSB);
	char_advance = (r32)advance * scale + offset_x;

	kerning_change = (r32)LSB * scale;

	align_percentage = VEC2(1.0f / (r32)out_width,
				(1.0f + (r32)(offset_y + height)) / (r32)out_height);

	// TODO(michiel): Move the allocation to the outside code and use MakeCodepointBitmap instead
	stbtt_FreeBitmap(FontBits, 0);

	result->align_percentage = align_percentage;
	result->kerning_change = kerning_change;
	result->char_advance = char_advance;

	return(0);
}

i32
font_extract(struct Font *font,
	     char *filename, char *font_name, n32 font_size,
	     CodepointMask *codepoint_mask)
{
	n32 path_size = PATH_MAX*2;
	char path[path_size];
	snprintf(path, path_size, "%s%s%s", os_state.path_data, "font/", filename);

	struct Font_Info *info = &font->info;
	info->glyph_count = codepoint_mask->glyph_count;
	info->codepoint_max_plus_one = codepoint_mask->codepoint_max_plus_one;

	n32 *glyph_codepoint = codepoint_mask->codepoint_from_glyph;

	//
	// NOTE(casey): Load and select the requested font
	//

	stbtt_fontinfo font_info_ = {0};
	stbtt_fontinfo *font_info = &font_info_;

	FILE *font_file = fopen(path, "rb");
	if(!font_file)
	{
		fprintf(stderr, "Unable to load font %s from %s\n", font_name, filename);
		return(-1);
	}

	fseek(font_file, 0, SEEK_END);
	size_t font_file_size = ftell(font_file);
	fseek(font_file, 0, SEEK_SET);

	n8 *font_file_buffer = (n8 *)mem_alloc(font_file_size, TRUE);
	size_t font_file_read_size = fread(font_file_buffer, 1, font_file_size, font_file);

	if(font_file_read_size != font_file_size)
	{
		fprintf(stderr, "DBG_ERROR: File read incomplete\n");
		return(-2);
	}

	if(stbtt_GetNumberOfFonts(font_file_buffer) != 1)
	{
		fprintf(stderr, "DBG_ERROR: Multiple font TTF files not supported\n");
		return(-3);
	}

	// TODO(michiel): Maybe use
	// stbtt_FindMatchingFont(font_file_buffer, font_name, 0);
	if(!stbtt_InitFont(font_info, font_file_buffer, stbtt_GetFontOffsetForIndex(font_file_buffer, 0)))
	{
		fprintf(stderr, "DBG_ERROR: Could not initialize stbtt_fontinfo\n");
		return(-4);
	}

	i32 ascent, descent, line_gap;
	stbtt_GetFontVMetrics(font_info, &ascent, &descent, &line_gap);

	r32 scale = stbtt_ScaleForPixelHeight(font_info, font_size);

	i32 min_x, min_y, max_x, max_y;
	stbtt_GetFontBoundingBox(font_info, &min_x, &min_y, &max_x, &max_y);

	Vec2 max_glyph_dim = VEC2(font_size + 2, font_size + 2);

	void *memory_out = mem_alloc(max_glyph_dim.x * max_glyph_dim.y * sizeof(n32), TRUE);

	/* INCOMPLETE - Square function */
	n32 glyphs_size = info->glyph_count * sizeof(struct Font_Glyph);
	n32 kerning_table_size = sizeof(r32) * info->glyph_count * info->glyph_count;
	n32 unicode_map_size = sizeof(n16) * info->codepoint_max_plus_one;

	font->glyphs = (struct Font_Glyph *)mem_alloc(glyphs_size, TRUE);
	font->kerning_table = (r32 *)mem_alloc(kerning_table_size, TRUE);
	font->unicode_map = (n16 *)mem_alloc(unicode_map_size, TRUE);

	memset(font->kerning_table, 0, kerning_table_size);
	memset(font->unicode_map, 0, unicode_map_size);

	// NOTE(casey): Reserve space for the null glyph
	info->ascender_height  = (r32)ascent   * scale;
	info->descender_height = (r32)descent  * scale;
	info->external_leading = (r32)line_gap * scale;

	for(n32 i = 1; i < info->glyph_count; ++i)
	{
		struct Font_Glyph *glyph = font->glyphs + i;

		n32 codepoint = glyph_codepoint[i];

		GlyphResult glyph_info;
		glyph_load(&glyph_info, font_info, codepoint, max_glyph_dim,
			   font_size, scale, info->descender_height, memory_out);

		struct GL_Texture texture = {0};
		texture.image = mem_alloc(sizeof(struct Image), TRUE);

		/* TDOO: Make this a single channel */
		struct Image *bitmap = texture.image;
		//bitmap->format = IMG_FORMAT_C;
		bitmap->format = IMG_FORMAT_BGRA;
		bitmap->separation = IMG_SEPARATION_PIXEL;
		bitmap->representation = IMG_REPRESENTATION_N8;
		bitmap->colorspace = IMG_COLORSPACE_GRAY;

		bitmap->width = glyph_info.width;
		bitmap->height = glyph_info.height;
		#if 0
		bitmap->channel_count = 1;
		bitmap->channel_padding = 3;
		#else
		bitmap->channel_count = 4;
		bitmap->channel_padding = 0;
		#endif

		img_extra_set(bitmap);
		bitmap->data = mem_alloc(bitmap->size, TRUE);

		#if 0
		for(i32 y = 0; y < bitmap->height; ++y)
		{
			for(i32 x = 0; x < bitmap->width; ++x)
			{

			}
		}
		#endif
		memcpy(bitmap->data, glyph_info.pixels, bitmap->size);

		/* NOTE: OpenGL */
		gl_texture_gen(&texture, GL_TEXTURE_2D, GL_LINEAR);

		glyph->codepoint = codepoint;
		glyph->texture = texture;
		glyph->align_percentage = glyph_info.align_percentage;

		i32 stb_glyph = stbtt_FindGlyphIndex(font_info, (i32)codepoint);

		/* NOTE: KERNING */
		for(n32 j = 0; j < info->glyph_count; ++j)
		{
			font->kerning_table[i * info->glyph_count + j] +=
				glyph_info.char_advance - glyph_info.kerning_change;

			if(j != 0)
			{
				i32 stb_other_glyph = stbtt_FindGlyphIndex(font_info, (i32)glyph_codepoint[j]);
				r32 kerning = (r32)stbtt_GetGlyphKernAdvance(font_info,
									     stb_other_glyph, stb_glyph) * scale;

				font->kerning_table[j * info->glyph_count + i] += glyph_info.kerning_change + kerning;
				font->unicode_map[glyph->codepoint] = (n16)i;
			}
		}
	}

	#if 0
	/* NOTE - Print out the kerning table to a file */
	fprintf(stdout, "	horizontal_advance = \n		");
	n32 kerning_table_count = info->glyph_count * info->glyph_count;
	for(n32 i = 0; i < kerning_table_count; ++i)
	{
		if(i)
		{
			if((i % 16) == 0)
			{
				fprintf(stdout, ",\n		");
			}
			else
			{
				fprintf(stdout, ", ");
			}
		}

		// TODO(casey): Should we support floating-point advance here?  It looks like
		// we are always actually rounding, so... I guess that's good?
		fprintf(stdout, "%3u", (n32)font->kerning_table[i]);
	}

	fprintf(stdout, ";\n");
	fprintf(stdout, "};\n");
	#endif

	return(0);
}

/* NOTE - Chareacter set functions */
#define CHAR_SET_CREATOR(name) void name(CodepointMask *mask)
typedef CHAR_SET_CREATOR(FontCharsetCreateFunc);

void
font_codepoint_include(CodepointMask *mask, n32 E0)
{
	n32 E[] = {E0};
	for(n32 i = 0; i < ARRAY_COUNT(E); ++i)
	{
		n32 codepoint = E[i];
		if(codepoint)
		{
			if(mask->codepoint_from_glyph)
			{
				mask->codepoint_from_glyph[mask->glyph_count] = codepoint;
			}

			if(mask->codepoint_max_plus_one <= codepoint)
			{
				mask->codepoint_max_plus_one = codepoint + 1;
			}

			++mask->glyph_count;
		}
	}
}

void
font_codepoint_range_include(CodepointMask *mask, n32 Mincodepoint, n32 Maxcodepoint)
{
	for(n32 Character = Mincodepoint;
		Character <= Maxcodepoint;
		++Character)
	{
		font_codepoint_include(mask, Character);
	}
}

CHAR_SET_CREATOR(ascii)
{
	font_codepoint_include(mask, ' ');
	font_codepoint_range_include(mask, '!', '~');

	// NOTE(casey): Kanji OWL!!!!!!!
	font_codepoint_include(mask, 0x00a9); /* COPYRIGHT */
	font_codepoint_include(mask, 0x5c0f);
	font_codepoint_include(mask, 0x8033);
	font_codepoint_include(mask, 0x6728);
	font_codepoint_include(mask, 0x514e);
}

typedef struct FontCharsetCreateArgs
{
	char *name;
	char *description;
	FontCharsetCreateFunc *function;
} FontCharsetCreateArgs;

FontCharsetCreateArgs charset_table[] =
{
	{"ascii", "Basic character set for testing font creation and display.", ascii},
};

i32
font_init(struct Font *font, char *filename,
	  char *font_name, n32 font_height, char *charset_name)
{
	/* NOTE: Examples */
	// "c:/Windows/Fonts/arial.ttf", "Arial", 128
	// "c:/Windows/Fonts/LiberationMono-Regular.ttf", "Liberation Mono", 20

	font->height = font_height;

	FontCharsetCreateArgs *args = 0;

	for(n32 i = 0; i < ARRAY_COUNT(charset_table); ++i)
	{
	FontCharsetCreateArgs *test = charset_table+ i;
	if(strcmp(test->name, charset_name) == 0)
	{
		args = test;
		break;
	}
	}

	if(!args)
	{
		fprintf(stderr, "DBG_ERROR: Unrecognized character set \"%s\".\n", charset_name);
		return(-1);
	}

	CodepointMask mask_counter = {0};
	mask_counter.glyph_count = 1;
	args->function(&mask_counter);

	CodepointMask mask = {0};
	mask.glyph_count = 1;
	size_t mask_size = mask_counter.glyph_count * sizeof(n32);
	mask.codepoint_from_glyph = (n32 *)mem_alloc(mask_size, TRUE);
	memset(mask.codepoint_from_glyph, 0, mask_size);

	args->function(&mask);

	font_extract(font, filename, font_name, font_height, &mask);

	return(0);
}

void
font_free(struct Font *font)
{
	mem_free(font->glyphs);
	mem_free(font->kerning_table);
	mem_free(font->unicode_map);
}

/* NOTE IMPORTANT */

#if 0
n32
GetGlyphFromCodePoint(hha_font *Info, loaded_font *Font, n32 CodePoint)
{
	n32 Result = 0;
	if(CodePoint < Info->OnePastHighestCodepoint)
	{
		Result = Font->UnicodeMap[CodePoint];
		Assert(Result < Info->GlyphCount);
	}

	return(Result);
}

r32
GetHorizontalAdvanceForPair(hha_font *Info, loaded_font *Font, n32 DesiredPrevCodePoint, n32 DesiredCodePoint)
{
	n32 PrevGlyph = GetGlyphFromCodePoint(Info, Font, DesiredPrevCodePoint);
	n32 Glyph = GetGlyphFromCodePoint(Info, Font, DesiredCodePoint);

	r32 Result = Font->HorizontalAdvance[PrevGlyph*Info->GlyphCount + Glyph];

	return(Result);
}

r32
GetLineAdvanceFor(hha_font *Info)
{
	r32 Result = Info->AscenderHeight + Info->DescenderHeight + Info->ExternalLeading;

	return(Result);
}

r32
GetStartingBaselineY(hha_font *Info)
{
	r32 Result = Info->AscenderHeight;

	return(Result);
}

bitmap_id
GetBitmapForGlyph(game_assets *Assets, hha_font *Info, loaded_font *Font, n32 DesiredCodePoint)
{
	n32 Glyph = GetGlyphFromCodePoint(Info, Font, DesiredCodePoint);
	bitmap_id Result = Font->Glyphs[Glyph].BitmapID;
	Result.Value += Font->BitmapIDOffset;

	return(Result);
}

r32
GetLineAdvanceFor(hha_font *Info)
{
	r32 Result = Info->AscenderHeight + Info->DescenderHeight + Info->ExternalLeading;

	return(Result);
}

r32
font_baseline_get(struct Font *font)
{
	r32 result = font->AscenderHeight;

	return(result);
}
#endif

/*
r32
GetStartingBaselineY(hha_font *Info)
{
    r32 Result = Info->AscenderHeight;

    return(Result);
}
*/

n32
font_glyph_id_get(struct Font *font, n32 codepoint)
{
	struct Font_Info *info = &font->info;

	n32 result = 0;
	if(codepoint < info->codepoint_max_plus_one)
	{
		result = font->unicode_map[codepoint];
		DBG_ASSERT(result < info->glyph_count);
	}
	return(result);
}


r32
font_kerning_get(struct Font *font, n32 codepoint, n32 codepoint_previous)
{
	struct Font_Info *info = &font->info;

	n32 glyph_prev = font_glyph_id_get(font, codepoint_previous);
	n32 glyph_cur  = font_glyph_id_get(font, codepoint);

	r32 result = font->kerning_table[glyph_prev * info->glyph_count + glyph_cur];

	return(result);
}

struct Image
font_glyph_bitmap_get(struct Font *font, n32 codepoint)
{
	n32 id = font_glyph_id_get(font, codepoint);
	struct Image result = *font->glyphs[id].texture.image;
	return(result);
}

struct GL_Texture
font_glyph_texture_get(struct Font *font, n32 codepoint)
{
	n32 id = font_glyph_id_get(font, codepoint);

	struct GL_Texture result = font->glyphs[id].texture;
	//result += font->bitmap_id_offset;

	return(result);
}

Vec2
font_glyph_alignment_get(struct Font *font, n32 codepoint)
{
	n32 id = font_glyph_id_get(font, codepoint);
	Vec2 result = font->glyphs[id].align_percentage;

	return(result);
}

#if 0
#define FontId n32

void
font_load(AppAssets *assets, FontId font_id)
{
	/*
	asset *Asset = Assets->Assets + ID.Value;
	Assert(Asset->State == AssetState_Unloaded);

	hha_font *Info = &Asset->HHA.Font;
	*/
	struct Font *font = &assets->font + font_id;

	/* INCOMPLETE - Square function */
	n32 kerning_table_size = sizeof(r32) * font->glyph_count * font->glyph_count;
	n32 glyphs_size = font->glyph_count * sizeof(struct Font_Glyph);
	n32 unicode_map_size = sizeof(n16) * font->codepoint_max_plus_one;
	n32 data_size = glyphs_size + kerning_table_size;
	n32 total_size = data_size + unicode_map_size;

	/*
	temporary_memory MemoryPoint = BeginTemporaryMemory(&Assets->NonRestoredMemory);
	n8 *Memory = (n8 *)PushSize(&Assets->NonRestoredMemory, SizeTotal);
	*/
	n8 memory = malloc(total_size);

	loaded_font *Font = &Asset->Font;
	font->bitmap_id_offset = GetFile(Assets, Asset->FileIndex)->AssetBase;
	font->glyphs = (struct Font_Glyph *)(memory);
	font->kerning_table = (r32 *)((n8 *)font->glyphs + glyphs_size);
	font->unicode_map = (n16 *)((n8 *)font->kerning_table + kerning_table_size);

	ZERO(font->unicode_map, unicode_map_size);

	/*
	platform_file_handle *FileHandle = GetFileHandleFor(Assets, Asset->FileIndex);
	Platform.ReadDataFromFile(FileHandle, Asset->HHA.DataOffset, SizeData, font->Glyphs);

	if(PlatformNoFileErrors(FileHandle))
	{
		hha_font *HHA = &Asset->HHA.font;
	*/
	{
		for(n32 i = 1; i < font->glyph_count; ++i)
		{
			struct Font_Glyph *glyph = font->glyphs + i;

			DBG_ASSERT(glyph->codepoint < font->codepoint_max_plus_one);
			DBG_ASSERT((n32)(n16)i == i);
			font->unicode_map[glyph->codepoint] = (n16)i;
		}

		Asset->State = AssetState_Loaded;
		KeepTemporaryMemory(MemoryPoint);
	}
	else
	{
		EndTemporaryMemory(MemoryPoint);
	}
}
#endif
