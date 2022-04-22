#include "../memory.h"
#include "../image.h"
#include "./bmp.h"

/* Read and Write */
void
img_bmp_read(struct Image *image, struct File *file)
{
	struct BMP_Header header;
	file_read(file, &header, sizeof(header));

	image->format = IMG_FORMAT_BGRA;
	image->colorspace = IMG_COLORSPACE_RGB;
	image->separation = IMG_SEPARATION_PIXEL;
	image->representation = IMG_REPRESENTATION_N8;

	image->width = header.info.width;
	image->height = header.info.height;
	image->channel_count = header.info.bpp / 8;

	image->size_line = image->width * image->channel_count;
	image->size = header.info.image_size;

	image->data = mem_alloc(image->size, FALSE);

	file_seek(file, header.file.offset, FILE_SEEK_SET);
	file_read(file, image->data, image->size);
}

void
img_bmp_write(struct Image *image, struct File *file)
{
	struct BMP_Header header = {0};
	/* TODO: Endian */
	header.file.signature = 0x4d42;
	header.file.size = sizeof(header.file) + image->size;
	header.file.offset = sizeof(header);

	header.info.size = sizeof(header);
	header.info.width = image->width;
	header.info.height = image->height;
	header.info.planes = 1;
	header.info.bpp = image->channel_count * 8;
	header.info.compression = 0;
	header.info.image_size = image->width * image->height;

	header.info.color_count = 256;

	file_write(file, &header, sizeof(header));
	file_seek(file, header.file.offset, FILE_SEEK_SET);
	file_write(file, image->data, image->size);
}

/* Printing */
void
bmp_header_print(struct BMP_Header *header)
{
	printf("file.sig: %d\n", header->file.signature);
	printf("file.size: %d\n", header->file.size);
	printf("file.offset: %d\n", header->file.offset);

	printf("\n");
	printf("info.size: %d\n", header->info.size);
	printf("info.width: %d\n", header->info.width);
	printf("info.height: %d\n", header->info.height);
	printf("info.planes: %d\n", header->info.planes);
	printf("info.bpp: %d\n", header->info.bpp);
	printf("info.compression: %d\n", header->info.compression);
	printf("info.image_size: %d\n", header->info.image_size);

	printf("info.x_res: %d\n", header->info.x_res);
	printf("info.y_res: %d\n", header->info.y_res);

	printf("info.color_count: %d\n", header->info.color_count);
	printf("info.color_important: %d\n", header->info.color_important);

	//printf("info.mask_red: %d\n", header->info.mask_red);
	//printf("info.mask_green: %d\n", header->info.mask_green);
	//printf("info.mask_blue: %d\n", header->info.mask_blue);
}
