#ifndef __JKC_LIB_DSTR_H__
#define __JKC_LIB_DSTR_H__

// Simple dynamic C string
// This implementation is not aim for high performance string
// operation. dstr is just a wrapper for normal C String, plus
// function for string concatenation. With those function, 
// user need to worry about growing the buffer size for the
// C String.

typedef struct
{
	char* data;
	size_t len;
	size_t max_len;
	size_t chunk_size;
	char error;
} dstr;

dstr* dstr_create(const char* s, size_t chunk_size);
dstr* dstr_concat(dstr* ds, const char* s);
dstr* dstr_append(dstr* ds, const char* s);
dstr* dstr_set(dstr* ds, const char* s);
dstr* dstr_copy(const dstr* ds);
void dstr_delete(dstr* ds);
#endif
