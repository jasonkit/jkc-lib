#include <stdio.h>
#include <dstr.h>
#include <assert.h>
#include <string.h>

int main (int argc, char** argv)
{
	dstr* ds;
	ds = dstr_create("Hello World", 16);
	assert(strcmp(ds->data, "Hello World") == 0);
	
	dstr_append(ds, ", this is ds.");
	assert(strcmp(ds->data, "Hello World, this is ds.") == 0);
	assert(ds->len == strlen("Hello World, this is ds."));
	
	size_t prev_len = ds->len;
	size_t prev_max_len = ds->max_len;
	dstr_append(ds, "");
	assert(ds->len == prev_len);
	assert(ds->max_len == prev_max_len);
	
	dstr_append(ds, " apple");
	assert(ds->len == (prev_len+6));
	assert(ds->max_len == prev_max_len);

	dstr_append(ds, "\n");
	assert(ds->len == (prev_len+7));
	assert(ds->max_len == prev_max_len);
	
	dstr_append(ds, "i go to school by bus!");
	assert(ds->max_len == prev_max_len+32);
	
	int i;
	char* msg = "i go to school by bus!\n";
	size_t msg_len = strlen(msg);
	size_t exp_len = ds->len + msg_len*100;
	for(i=0; i< 100; i++) {
		dstr_append(ds, msg);
	}
	
	assert(ds->len == exp_len);

	dstr_delete(ds);

	ds = dstr_create("Hello World", 16);
	dstr* ds2 = dstr_copy(ds);

	assert(ds->len == ds2->len);
	assert(ds->max_len == ds2->max_len);
	assert(strcmp(ds->data,ds2->data) == 0);

	dstr* ds3 = dstr_concat(dstr_append(ds," "),ds2->data);
	assert(strcmp(ds3->data,"Hello World Hello World") == 0);

	dstr_set(ds2, "i go to school by bus");
	assert(strcmp(ds2->data,"i go to school by bus") == 0);

	printf("PASSED\n");

	return 0;
}
