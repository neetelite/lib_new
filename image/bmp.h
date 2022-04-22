#ifndef _image_bmp
#define _image_bmp

/* Structures */
#pragma pack(push, 1)
#pragma pack(1)
struct BMP_FileHeader
{
	n16 signature;
	n32 size;
	n16 reserved_1;
	n16 reserved_2;
	n32 offset;
};

struct BMP_InfoHeader
{
	n32 size;
	n32 width;
	n32 height;
	n16 planes;
	n16 bpp;
	n32 compression;
	n32 image_size;

	n32 x_res;
	n32 y_res;

	n32 color_count;
	n32 color_important;

	//n32 mask_red;
	//n32 mask_green;
	//n32 mask_blue;
};

struct BMP_Header
{
	struct BMP_FileHeader file;
	struct BMP_InfoHeader info;
};
#pragma pack(pop)

/* Functions */
void img_bmp_read(struct Image *image, struct File *file);
void img_bmp_write(struct Image *image, struct File *file);
void bmp_header_print(struct BMP_Header *header);

#endif /* _image_bmp */
