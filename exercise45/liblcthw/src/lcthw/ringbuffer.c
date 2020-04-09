#undef NDEBUG
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <dbg.h>
#include <ringbuffer.h>



RingBuffer *RingBuffer_create(int length)
{
	RingBuffer *buffer		= calloc(1, sizeof(RingBuffer));
	check_mem(buffer);
	
	check(length > 0, "Need more than 0 to create buffer. You gave: %d ", length);

	//buffer->length			= length + 1;
	buffer->length			= length;
	buffer->start			= 0;
	buffer->end				= 0;
	buffer->full			= 0;
	buffer->buffer			= calloc(buffer->length, 1);
	check_mem(buffer->buffer);

	return buffer;

error:
	if (buffer) free (buffer);
	return NULL;
}


void RingBuffer_destroy(RingBuffer *buffer)
{
	if (buffer) {
		free (buffer->buffer);
		free (buffer);
	}
}


/* NOTE: Does not return a '\0' terminated string.*/
int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
	check(buffer != NULL, "Can't use a NULL buffer in RingBuffer_read.");
	check(target != NULL, "Can't use a NULL target in RingBuffer_read.");
	check(amount > 0, " Can't use an amount less than 1 in RingBuffer_read.");
	check_debug(amount <= RingBuffer_available_data(buffer), 
				"Not enough data in the buffer: has %d, needs %d",
				RingBuffer_available_data(buffer), amount);

	// unset full flag when reading
	if (buffer->full == 1){
		buffer->full =			0;
	}

/*	void *result			= memcpy(target, RingBuffer_starts_at(buffer), amount);
	check(result != NULL, "Failed to read data from buffer into target.");
*/	int i					= 0;
	for (i = 0; i < amount; i++){
		if (i + buffer->start < buffer->length){
			target[i]	= buffer->buffer[i + buffer->start];
		} else {
			target[i]	= buffer->buffer[(i + buffer->start) % buffer->length];
		}
	}

	RingBuffer_commit_read(buffer, amount);

   	if (buffer->end == buffer->start) {
		buffer->start = buffer->end = 0;
	}

	return amount;

error:
	return -1;
}


int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
	check(buffer != NULL, "Can't use a NULL buffer in RingBuffer_write.");
	check(data != NULL, "Can't use a NULL data in RingBuffer_write.");
	check(length > 0, " Can't use a less than 1 in RingBuffer_write.");
	if (RingBuffer_available_data(buffer) == 0) {
		buffer->start = buffer->end = 0;
	}

	check(length <= RingBuffer_available_space(buffer), 
				"Not enough space in the buffer: %d requested, %d available",
				length, RingBuffer_available_space(buffer));

/*	void * result			= memcpy(RingBuffer_ends_at(buffer), data, length);
	check(result != NULL, "Failed to write data into buffer.");
*/	int i					= 0;
	for (i = 0; i < length; i++){
		if (i + buffer->end < buffer->length){
			buffer->buffer[i + buffer->end] = data[i];
		} else {
			buffer->buffer[(i + buffer->end) % buffer->length] = data[i];
		}
	}

	// set full flag if buffer is full
	if (buffer->length == length + RingBuffer_available_data(buffer)){
		buffer->full			= 1;
	}

	RingBuffer_commit_write(buffer, length);

	return length;

error:
	return -1;
	
}


bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
	check(buffer != NULL, "Can't use a NULL buffer in RingBuffer_gets.");
	check(amount > 0, "Need more than 0 for gets. You gave: %d ", amount);
	check_debug(amount <= RingBuffer_available_data(buffer), "Not enough data in the buffer.");

	bstring result			= blk2bstr(RingBuffer_starts_at(buffer), amount);
	check(result != NULL, "Failed to create gets result");
	check(blength(result) == amount, "Wrong result length.");

	RingBuffer_commit_read(buffer, amount);
	assert(RingBuffer_available_data(buffer) >= 0 && "Error in read commit.");

	return result;

error:
	return NULL;
}


int RingBuffer_available_data(RingBuffer *buffer)
{
	if (buffer->full == 1){
		return buffer->length;
	} else {
		return ((buffer->length - buffer->start + buffer->end) % buffer->length);
	}
}

int RingBuffer_available_space(RingBuffer *buffer)
{
	return (buffer->length - RingBuffer_available_data(buffer));
}

