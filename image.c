#include "./image.h"
#include "./image/bmp.h"
#include "./memory.h"
#include "./debug.h"

void
img_read_from_file(struct Image *image, struct File *file)
{
	if(0);
	else if(str_eql(&file->extension, &STR("bmp"))) img_bmp_read(image, file);
	//else if(str_eql(&file->extension, &STR("png"))) img_png_read(image, file);
	else
	{
		DBG_ERROR("Unsupported extension: %s!\n", file->extension.data);
	}
}

void
img_read(struct Image *image, String *path)
{
	struct File file = file_init(path);
	file_open(&file, FILE_OPEN_MODE_BYTE_READ);
	img_read_from_file(image, &file);
	file_close(&file);
}

void
img_extra_set(struct Image *image)
{
	switch(image->representation)
	{
	case IMG_REPRESENTATION_N8: image->size_channel = sizeof(n8);
	case IMG_REPRESENTATION_R32: image->size_channel = sizeof(r32);
	}

	image->size_pixel = image->channel_count * image->size_channel;
	image->size_block = (image->channel_count + image->channel_padding) * image->size_channel;
	image->size_line = image->width * image->size_block;
	image->size = image->height * image->size_line;
}

/* Format */
void
img_format_rgba_from_bgra(struct Image *image)
{
	if(image->format == IMG_FORMAT_RGBA) return;

	switch(image->representation)
	{
	case IMG_REPRESENTATION_N8:
	{
		#if 0
		for(i32 y = 0; y < image->height; ++y)
		{
			for(i32 x = 0; x < image->width; ++x)
			{
				n32 *pixel_pointer = (n32 *)image->data + (image->width * y) + x;
				Vec4 pixel = vec4_from_n32(*pixel_pointer);
				pixel = VEC4(pixel.y, pixel.z, pixel.w, pixel.x);
				*pixel_pointer = n32_from_vec4(pixel);
			}
		}
		#endif
	} break;
	case IMG_REPRESENTATION_R32:
	{
		for(i32 y = 0; y < image->height; ++y)
		{
			for(i32 x = 0; x < image->width; ++x)
			{
				Vec4 *pixel_pointer = (Vec4 *)image->data + ((i32)image->width * y) + x;
				Vec4 pixel = *pixel_pointer;
				pixel = VEC4(pixel.z, pixel.y, pixel.x, pixel.w);
				*pixel_pointer = pixel;
			}
		}
	} break;
	}

	image->format = IMG_FORMAT_RGBA;
}

/* Representation */
void
img_representation_r32_from_n8_out(r32 *dst_data, n8 *src_data,
								   n32 width, n32 height,
								   n32 channel_count, n32 channel_padding)
{
	n64 i = 0;
	for(i32 h = 0; h < height; ++h)
	{
		for(i32 w = 0; w < width; ++w)
		{
			for(i32 c = 0; c < channel_count; ++c)
			{
				n8 *src = src_data + i;
				r32 *dst = dst_data + i;
				*dst = (r32)((r32)*src / 255.0f);
				i += 1;
			}
			i += channel_padding;
		}
	}
}

/* Colorspace */
void
img_colorspace_hsv_from_rgb(struct Image *image)
{
	if(image->representation != IMG_REPRESENTATION_R32) return;

	if(image->colorspace != IMG_COLORSPACE_RGB) return;
	if(image->colorspace == IMG_COLORSPACE_HSV) return;

	for(i32 x = 0; x < image->width; ++x)
	{
		for(i32 y = 0; y < image->height; ++y)
		{
			//Vec4 *pixel_pointer = (Vec4 *)image->data + (image->width * y) + x;
			Vec4 *pixel_pointer = img_pixel_get(image, x, y);
			Vec4 pixel = *pixel_pointer;

			r64 r = pixel.r;
			r64 g = pixel.g;
			r64 b = pixel.b;
			r64 a = pixel.a;

			r32 h, s, v;

			r32 max = vec3_max(pixel.rgb);
			r32 min = vec3_min(pixel.rgb);
			r32 delta = max - min;
			v = max;

			if(max == 0)
			{
				s = 0;
				h = 0;
			}
			else
			{
				s = delta / max;
				if(r == max)      h = (g - b)/delta;
				else if(g == max) h = 2 + (b - r)/delta;
				else              h = 4 + (r - g)/delta;

				if(h < 0) h += 6;
				h = h/6;
			}

			pixel = VEC4(h, s, v, a);
			*pixel_pointer = pixel;
		}
	}

	image->colorspace = IMG_COLORSPACE_HSV;
}

inline void *
img_pixel_get(struct Image *image, i32 w, i32 h)
{
	if(w < 0 || h < 0 || w >= image->width || h >= image->height) return(NULL);
	void *result = (b8 *)image->data + (h * image->size_line) + (w * image->size_block);
	return(result);
}

inline void *
img_pixel_channel_get(struct Image *image, i32 w, i32 h, i32 c)
{
	if(w < 0 || h < 0 || w >= image->width || h >= image->height) return(NULL);
	void *result = (b8 *)image->data + (h * image->size_line) + (w * image->size_block) + (c * image->size_channel);
	return(result);
}


void
img_kernel_apply(struct Image *image_src, struct Image *image_dst, struct Kernel *kernel)
{
	DBG_ASSERT(kernel->width % 2 != 0);
	i32 skip = (kernel->width - 1) / 2;

	n32 block = image_src->channel_count + image_src->channel_padding;
	for(i32 ih = 0; ih < image_src->height; ++ih)
	{
		for(i32 iw = 0; iw < image_src->width; ++iw)
		{
			Vec4 *pixel_dst = img_pixel_get(image_dst, iw, ih);

			if(iw < skip || ih < skip || iw >= image_src->width-skip || ih >= image_src->height-skip)
			{
				Vec4 *pixel_src = img_pixel_get(image_src, iw, ih);
				*pixel_dst = *pixel_src;
			}
			else {
				Vec4 sum = VEC4_ZERO;
				for(i32 kh = 0; kh < kernel->height; ++kh)
				{
					for(i32 kw = 0; kw < kernel->width; ++kw)
					{
						r32 *kp = kernel->data + (kh * kernel->height) + kw;
						i32 pw = kw - (kernel->width / 2);
						i32 ph = kh - (kernel->height / 2);

						Vec4 *pixel_src = img_pixel_get(image_src, iw+pw, ih+ph);
						sum = vec4_a(sum, vec4_mr(*pixel_src, *kp));
					}
				}
				*pixel_dst = sum;
			}
		}
	}
}

void
img_kernel_apply_with_skip(struct Image *image_src, struct Image *image_dst, struct Kernel *kernel)
{
	DBG_ASSERT(image_dst->width == image_src->width/kernel->width);
	DBG_ASSERT(image_dst->height == image_src->height/kernel->height);

	for(i32 ih = 0; ih < image_src->height/kernel->height; ++ih)
	{
		for(i32 iw = 0; iw < image_src->width/kernel->width; ++iw)
		{
			Vec4 *pixel_dst = img_pixel_get(image_dst, iw, ih);

			i32 w = iw*kernel->width;
			i32 h = ih*kernel->height;

			Vec4 sum = VEC4_ZERO;
			for(i32 kh = 0; kh < kernel->height; ++kh)
			{
				for(i32 kw = 0; kw < kernel->width; ++kw)
				{
					Vec4 *pixel_src = img_pixel_get(image_src, w+kw, h+kh);

					r32 *kp = kernel->data + (kh * kernel->height) + kw;
					sum = vec4_a(sum, vec4_mr(*pixel_src, *kp));
				}
			}
			*pixel_dst = sum;
		}
	}
}

void
img_difference(struct Image *image_new, struct Image *image_old, struct Image *image_dst)
{
	DBG_ASSERT(image_new->width == image_old->width);
	DBG_ASSERT(image_new->height == image_old->height);
	DBG_ASSERT(image_new->size_block == image_old->size_block);

	DBG_ASSERT(image_new->width == image_dst->width);
	DBG_ASSERT(image_new->height == image_dst->height);
	DBG_ASSERT(image_new->size_block == image_dst->size_block);

	for(i32 h = 0; h < image_dst->height; ++h)
	{
		for(i32 w = 0; w < image_dst->width; ++w)
		{
			Vec4 *pixel_new = img_pixel_get(image_new, w, h);
			Vec4 *pixel_old = img_pixel_get(image_old, w, h);
			Vec4 *pixel_dst = img_pixel_get(image_dst, w, h);

			/* ((new - old) + 1) / 2 */
			//*pixel_dst = vec4_dr(vec4_ar(vec4_s(*pixel_new, *pixel_old), 1.0), 2.0);
			*pixel_dst = vec4_abs(vec4_s(*pixel_new, *pixel_old));
		}
	}
}
