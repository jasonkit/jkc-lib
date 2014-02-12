#include <stdlib.h>
#include <string.h>
#include "dstr.h"

// create a new dstr, buffer size of dstr will be multiple of chunk_size
dstr* dstr_create(const char* s, size_t chunk_size)
{
	dstr* ds = (dstr*)malloc(sizeof(dstr));
	if (!ds || !chunk_size)
		return NULL;

	size_t len = strlen(s);
	size_t alloc_size = chunk_size;

	if (len >= chunk_size) {
		alloc_size = chunk_size*((len/chunk_size)+1);
	}

	ds->data = malloc(alloc_size);
	if (!ds->data) {
		free(ds);
		return NULL;
	}

	ds->max_len = chunk_size-1;
	ds->len = strlen(s);
	ds->chunk_size = chunk_size;

	memcpy(ds->data, s, len);
	ds->data[ds->len] = 0;

	return ds;
}

// delete a dstr
void dstr_delete(dstr* ds)
{
	free(ds->data);
	free(ds);
}

// append new content to existing dstr
dstr* dstr_append(dstr* ds, const char* s)
{
	size_t len = strlen(s);
	if ((ds->len + len) > ds->max_len) {
		size_t diff = (ds->len + len) - ds->max_len;
		size_t new_size = ds->max_len + ds->chunk_size*((diff / ds->chunk_size) + 1);
		
		void* new_buf = realloc(ds->data, new_size);
		
		if (!new_buf) {
			ds->error = 1;
			return ds;
		}
	
		ds->data = new_buf;
		ds->max_len = new_size;
	}
	
	memcpy(&(ds->data[ds->len]),s,len);
	ds->len += len;
	ds->data[ds->len] = 0;
	return ds;
}

// clone a new copy of dstr
dstr* dstr_copy(const dstr* ds)
{
	dstr* copy_ds = dstr_create((const char*)ds->data, ds->chunk_size);
	return copy_ds;
}

// create a new dstr by concatenate a dstr and a C string
dstr* dstr_concat(dstr* ds, const char* s)
{
	dstr* new_ds = dstr_copy(ds);
	return dstr_append(new_ds, s);
}

// set new content for a dstr
dstr* dstr_set(dstr* ds, const char* s)
{
	size_t len = strlen(s);
	if (ds->max_len <= len) {
		memcpy(ds->data, s, ds->max_len);
		ds->data[ds->max_len] = 0;
		ds->len = ds->max_len;
		dstr_append(ds, &s[ds->max_len]);	
	}else{
		memcpy(ds->data, s, len);
		ds->len = len;
	}

	return ds; 
}

