#ifndef _image_h
#define _image_h

#include "./scalar/integer.h"
#include "./file.h"
#include "./vector.h"
#include "./memory.h"
#include "./kernel.h"

/* Structures */
enum Image_Format
{
	IMG_FORMAT_NULL,

	IMG_FORMAT_ARGB,
	IMG_FORMAT_RGBA,
	IMG_FORMAT_BGRA,

	IMG_FORMAT_RGB,
	IMG_FORMAT_BGR,

	IMG_FORMAT_C, /* COLOR */
};

enum Image_Separation
{
	IMG_SEPARATION_NULL,

	IMG_SEPARATION_PIXEL, /* Array of structures */
	IMG_SEPARATION_CHANNEL, /* Structure of arrays */
};

enum Image_Representation
{
	IMG_REPRESENTATION_NULL,

	IMG_REPRESENTATION_N8,  /* 0 to 255 */
	IMG_REPRESENTATION_R32, /* 0 to 1 */
};

enum Image_ChannelType
{
	IMG_CHANNEL_RED,
	IMG_CHANNEL_GREEN,
	IMG_CHANNEL_BLUE,
	IMG_CHANNEL_ALPHA,

	IMG_CHANNEL_HUE,
	IMG_CHANNEL_SATURATION,
	IMG_CHANNEL_VALUE,
	IMG_CHANNEL_LIGHTNESS,

	IMG_CHANNEL_INTENSITY,
};

enum Image_ColorSpace
{
	IMG_COLORSPACE_NULL,

	IMG_COLORSPACE_GRAY, /* Grayscale */
	IMG_COLORSPACE_RGB, /* Red, Green, Blue */
	IMG_COLORSPACE_HSL, /* Hue, Saturation, Lightness */
	IMG_COLORSPACE_HSV, /* Hue, Saturation, Value (aka. HSB) */
};

struct Image
{
	/* Info */
	enum Image_Format format;
	enum Image_Separation separation;
	enum Image_Representation representation;
	enum Image_ColorSpace colorspace;

	/* Primary */
	union
	{
		Vec2i dim;
		struct
		{
			i32 width;
			i32 height;
		};
	};
	n8 channel_count;
	n8 channel_padding;

	/* Content */
	void *data;

	/* Extra */
	n32 size_channel;
	n32 size_pixel;
	n32 size_block; /* Also includes padding */
	n32 size_line;
	n64 size;
};

/* Functions */
void img_read(struct Image *image, String *path);
void img_read_from_file(struct Image *image, struct File *file);

void img_extra_set(struct Image *image);
void img_format_rgba_from_bgra(struct Image *image);
void img_representation_r32_from_n8_out(r32 *dst_data, n8 *src_data, n32 width, n32 height, n32 channel_count, n32 channel_padding);
void img_colorspace_hsv_from_rgb(struct Image *image);

void *img_pixel_get(struct Image *image, i32 w, i32 h);
void *img_pixel_channel_get(struct Image *image, i32 w, i32 h, i32 c);
void img_kernel_apply(struct Image *image_src, struct Image *image_dst, struct Kernel *kernel);
void img_kernel_apply_with_skip(struct Image *image_src, struct Image *image_dst, struct Kernel *kernel);
void img_difference(struct Image *image_new, struct Image *image_old, struct Image *image_dst);

#endif /* _image_h */
