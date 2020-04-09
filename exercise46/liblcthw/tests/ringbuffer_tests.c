#include "minunit.h"
#include <ringbuffer.h>
#include <assert.h>
#include <string.h>

#define BUF_LEN 15


static RingBuffer *buffer	= NULL;
char *tests[]				= {"abcd", "e", "fghijklmnop"};



char *test_create()
{
	buffer					= RingBuffer_create(BUF_LEN);
	mu_assert(buffer != NULL, "Failed to create buffer.");

	return NULL;
}



char *test_destroy()
{
	mu_assert(buffer != NULL, "Failed to make buffer #2.");
	RingBuffer_destroy(buffer);

	return NULL;
}



char *test_write_read()
{
	int rc					= 0;
	char result[16]			= "\0";

	RingBuffer *invalidbuf	= RingBuffer_create(0);
	mu_assert(invalidbuf == NULL ,"Should not be able to create 0 size buffer.");


	fprintf(stderr, "\nbuf->end: %d\tbuf->len: %d\tbuf->sta: %d\n\n", buffer->end, buffer->length, buffer->start);
	// testing initial values
	mu_assert(RingBuffer_available_data(buffer) == 0, "Buffer should have no data.");
	mu_assert(RingBuffer_available_space(buffer) == 15, "Buffer should have all space remaining.");
	mu_assert(RingBuffer_empty(buffer) == 1, "Buffer should be empty.");
	mu_assert(RingBuffer_full(buffer) != 1, "Buffer should not be full.");


	// testing write error checks
	rc						= RingBuffer_write(invalidbuf, "hello" , 5);
	mu_assert(rc == -1, "Should not be able to write to a NULL buffer.");

	rc						= RingBuffer_write(buffer, NULL, 5);
	mu_assert(rc == -1, "Should not be able to write NULL data to buffer.");

	rc						= RingBuffer_write(buffer, "goodbye", 0);
	mu_assert(rc == -1, "Should not be able to write to buffer using 0 length.");


	// testing read error checks
	rc						= RingBuffer_read(invalidbuf, result, 3);
	mu_assert(rc == -1, "Should not be able to read from a NULL buffer.");

	rc						= RingBuffer_read(buffer, NULL, 5);
	mu_assert(rc == -1, "Should not be able to write NULL data to buffer.");

	rc						= RingBuffer_read(buffer, result, 0);
	mu_assert(rc == -1, "Should not be able to write to buffer using 0 length.");


	// testing RingBuffer_write and RingBuffer_read
	// writing some characters
	rc						= RingBuffer_write(buffer, tests[0], 4);
	mu_assert(rc == 4, "RingBuffer_write should not return an error after test0.");
	mu_assert(RingBuffer_available_data(buffer) == 4, "Buffer should have 4 data.");
	mu_assert(RingBuffer_available_space(buffer) == 11, "Buffer should have 11 space remaining.");
	mu_assert(RingBuffer_empty(buffer) != 1, "Buffer should be empty.");

	// writing 1 character
	rc						= RingBuffer_write(buffer, tests[1], 1);
	mu_assert(rc == 1, "RingBuffer_write should not return an error after test1.");
	mu_assert(RingBuffer_available_data(buffer) == 5, "Buffer should have 5 data.");
	mu_assert(RingBuffer_available_space(buffer) == 10, "Buffer should have 10 space remaining.");

	// testing writing more than available space
	rc						= RingBuffer_write(buffer, tests[2], 11);
	mu_assert(rc == -1, "RingBuffer_write should not be able to write more data than available space to buffer during test2.");

	// reading 1 character
	rc						= RingBuffer_read(buffer, result, 1);
	mu_assert(rc == 1, "RingBuffer_read should not return an error after reading 1 character.");
	mu_assert(strcmp(result, "a") == 0, "result should be 'a'.");
	mu_assert(RingBuffer_available_data(buffer) == 4, "Buffer should have 4 data after RingBuffer_read.");
	mu_assert(RingBuffer_available_space(buffer) == 11, "Buffer should have 11 space remaining after RingBuffer_read.");
	memset(result, '\0', sizeof(result));

	// filling the buffer
	rc						= RingBuffer_write(buffer, tests[2], 11);
	mu_assert(rc == 11, "RingBuffer_write should not return an error after test2.");
	//fprintf(stderr, "\navailable space:%d\n\n", RingBuffer_available_space(buffer));
	//fprintf(stderr, "\navailable data:%d\n\n", RingBuffer_available_data(buffer));
	//fprintf(stderr, "\nbuf->end: %d\tbuf->len: %d\tbuf->sta: %d\n\n", buffer->end, buffer->length, buffer->start);
	mu_assert(RingBuffer_available_data(buffer) == 15, "Buffer should have 15 data.");
	mu_assert(RingBuffer_available_space(buffer) == 0, "Buffer should have no space remaining.");
	mu_assert(RingBuffer_full(buffer) == 1, "Buffer should be full.");

	// reading some characters
	rc						= RingBuffer_read(buffer, result, 10);
	mu_assert(rc == 10, "RingBuffer_read should not return an error after reading 10 characters.");
	mu_assert(strcmp(result, "bcdefghijk") == 0, "result should be 'bcdefghijk'.");
	mu_assert(RingBuffer_available_data(buffer) == 5, "Buffer should have 5 data after RingBuffer_read.");
	mu_assert(RingBuffer_available_space(buffer) == 10, "Buffer should have 10 space remaining after RingBuffer_read.");
	memset(result, '\0', sizeof(result));

	// testing reading more than available data
	rc						= RingBuffer_read(buffer, result, 8);
	mu_assert(rc == -1, "RingBuffer_read should not be able to read more data than is available in buffer.");
	
	// emptying the buffer
	rc						= RingBuffer_read(buffer, result, 5);
	fprintf(stderr, "\nresult:%s\n\n", result);
	mu_assert(rc == 5, "RingBuffer_read should not return an error after reading 5 characters.");
	mu_assert(strcmp(result, "lmnop") == 0, "result should be 'lmnop'.")
	mu_assert(RingBuffer_available_data(buffer) == 0, "Buffer should have 0 data after RingBuffer_read.");
	mu_assert(RingBuffer_available_space(buffer) == 15, "Buffer should have 15 space remaining after RingBuffer_read.");
	mu_assert(RingBuffer_empty(buffer) == 1, "Buffer should be empty after RingBuffer_read.");

	return NULL;
}



char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_write_read);
	mu_run_test(test_destroy);

	return NULL;
}



RUN_TESTS(all_tests);
