#include "./file.h"
#include "./cstring.h"
#include "debug.h"

#define PATH_MAX 4096

void
file_open_mode_cstr(enum File_OpenMode mode, CString cstr, n64 cstr_size)
{
	switch(mode)
	{
	case FILE_OPEN_MODE_READ:
	{
		snprintf(cstr, cstr_size, "r");
	} break;
	case FILE_OPEN_MODE_WRITE:
	{
		snprintf(cstr, cstr_size, "w");
	} break;
	case FILE_OPEN_MODE_READ_AND_WRITE:
	{
		snprintf(cstr, cstr_size, "rw");
	} break;
	case FILE_OPEN_MODE_APPEND:
	{
		snprintf(cstr, cstr_size, "a");
	} break;
	case FILE_OPEN_MODE_BYTE_READ:
	{
		snprintf(cstr, cstr_size, "rb");
	} break;
	case FILE_OPEN_MODE_BYTE_WRITE:
	{
		snprintf(cstr, cstr_size, "wb");
	} break;
	case FILE_OPEN_MODE_BYTE_READ_AND_WRITE:
	{
		snprintf(cstr, cstr_size, "rwb");
	} break;
	case FILE_OPEN_MODE_BYTE_APPEND:
	{
		snprintf(cstr, cstr_size, "ab");
	} break;
	case FILE_OPEN_MODE_NULL:
	{
		DBG_INVALID_PATH;
	} break;
	}
}

i32
file_open(struct File *file, enum File_OpenMode mode)
{
	if(file->is_open) return(-1);

	char mode_cstr[256];
	file_open_mode_cstr(mode, mode_cstr, 256);

	char file_cstr[PATH_MAX];
	cstr_cpy_n(file_cstr, file->path.data, file->path.len);
	file_cstr[file->path.len] = '\0';
	file->descriptor = fopen(file_cstr, mode_cstr);

	if(!file->descriptor)
	{
		file->is_open = FALSE;
		DBG_ERROR("Failed to open file '%s' with mode '%s'.", file->path.data, mode_cstr);
		return(-2);
	}

	file->is_open = TRUE;
	file->size = file_init_size(file);
	file->open_mode = mode;

	return(0);
}

i32
file_close(struct File *file)
{
	if(!file->is_open) return(-1);

	file->is_open = FALSE;
	//mem_free(file->path);

	fclose(file->descriptor);
	return(0);
}

void
file_seek(struct File *file, i32 offset, enum File_SeekMode mode)
{
	fseek(file->descriptor, offset, mode);
}

n64
file_tell(struct File *file)
{
	n64 result = 0;
	result = ftell(file->descriptor);
	return(result);
}

void
file_read(struct File *file, void *pointer, n64 size)
{
	fread(pointer, size, 1, file->descriptor);
	fseek(file->descriptor, -size, FILE_SEEK_CUR);
}

void
file_write(struct File *file, void *pointer, n64 size)
{
	fwrite(pointer, size, 1, file->descriptor);

	switch(file->open_mode)
	{
		case FILE_OPEN_MODE_WRITE:
		case FILE_OPEN_MODE_READ_AND_WRITE:
		case FILE_OPEN_MODE_BYTE_WRITE:
		case FILE_OPEN_MODE_BYTE_READ_AND_WRITE:
		{
			/* Do nothing */
		} break;
		case FILE_OPEN_MODE_APPEND:
		case FILE_OPEN_MODE_BYTE_APPEND:
		{
			fseek(file->descriptor, -size, FILE_SEEK_CUR);
		} break;
		case FILE_OPEN_MODE_NULL:
		case FILE_OPEN_MODE_READ:
		case FILE_OPEN_MODE_BYTE_READ:
		{
			DBG_INVALID_PATH;
		} break;
	}
}

void
file_push(struct File *file, void *pointer, n64 size)
{
	fwrite(pointer, size, 1, file->descriptor);

	switch(file->open_mode)
	{
		case FILE_OPEN_MODE_WRITE:
		case FILE_OPEN_MODE_READ_AND_WRITE:
		case FILE_OPEN_MODE_BYTE_WRITE:
		case FILE_OPEN_MODE_BYTE_READ_AND_WRITE:
		{
			fseek(file->descriptor, size, FILE_SEEK_CUR);
		} break;
		case FILE_OPEN_MODE_APPEND:
		case FILE_OPEN_MODE_BYTE_APPEND:
		{
			/* Do nothing */
		} break;
		case FILE_OPEN_MODE_NULL:
		case FILE_OPEN_MODE_READ:
		case FILE_OPEN_MODE_BYTE_READ:
		{
			DBG_INVALID_PATH;
		} break;
	}
}

void
file_pop(struct File *file, void *pointer, n64 size)
{
	fread(pointer, size, 1, file->descriptor);
}

void
file_info_update(struct File *file)
{
	/* TODO: */
}

n64
file_size(struct File *file)
{
	/* TODO - Find another way to get the file without opening it */
	n64 result = 0;

	if(file->is_open == FALSE)
	{
		DBG_ERROR("File is closed\n");
		return(0);
	}

	file_seek(file, 0, FILE_SEEK_END);
	result = file_tell(file);
	file_seek(file, 0, FILE_SEEK_SET);

	return(result);
}

String
file_data(struct File *file)
{
	String result = {0};

	n64 size = file_size(file);
	result = str_alloc_n(size+1);
	result.len = result.max;

	file_read(file, result.data, result.len);
	result.data[result.len] = '\0';

	return(result);
}

struct File
file_init(String *path)
{
	struct File result = {0};

	result.path = str_dup(path);
	result.name = str_path_filename(&result.path);
	result.extension = str_path_extension(&result.path);
	result.size = 0;

	result.is_open = FALSE;
	result.open_mode = FILE_OPEN_MODE_NULL;
	result.descriptor = NULL;

	file_info_update(&result); /* TODO: Maybe we dont' want this */

	return(result);
};

n64
file_init_size(struct File *file)
{
	/* TODO: */
	n64 result = 0;
	return(result);
}
