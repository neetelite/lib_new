#ifndef _file_h
#define _file_h

#include <stdio.h>

#include "./time.h"
#include "./string.h"

#include "./scalar/natural.h"
#include "./scalar/boolean.h"

enum File_SeekMode
{
	FILE_SEEK_SET = SEEK_SET,
	FILE_SEEK_CUR = SEEK_CUR,
	FILE_SEEK_END = SEEK_END,
};

enum File_OpenMode
{
	FILE_OPEN_MODE_NULL,

	FILE_OPEN_MODE_READ,
	FILE_OPEN_MODE_WRITE,
	FILE_OPEN_MODE_READ_AND_WRITE,
	FILE_OPEN_MODE_APPEND,

	FILE_OPEN_MODE_BYTE_READ,
	FILE_OPEN_MODE_BYTE_WRITE,
	FILE_OPEN_MODE_BYTE_READ_AND_WRITE,
	FILE_OPEN_MODE_BYTE_APPEND,
};

struct File_Info
{
	struct Date date_creation;
	struct Date date_access;
	struct Date date_write;
};

struct File
{
	String path;
	String name;
	String extension;
	n64 size;

	/* Open */
	Bool is_open;
	enum File_OpenMode open_mode;
	FILE *descriptor;

	struct File_Info info;
};

/* Functions */
i32 file_open(struct File *file, enum File_OpenMode mode);
i32 file_close(struct File *file);

void file_info_update(struct File *file);
n64 file_size(struct File *file);
String file_data(struct File *file);

struct File file_init(String *path);
n64 file_init_size(struct File *file);

void file_seek(struct File *file, i32 offset, enum File_SeekMode mode);
n64 file_tell(struct File *file);

void file_read(struct File *file, void *pointer, n64 size);
void file_write(struct File *file, void *pointer, n64 size);

#endif /* _file_h */
