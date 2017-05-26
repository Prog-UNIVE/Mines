
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

Queue QUEUE_init()
{
	return SLIST_init();
}

void QUEUE_destroy(Queue que)
{
	SLIST_destroy(que);
}

int QUEUE_enqueue(Queue que, const void *data)
{
	return SLIST_ins_next(que, SLIST_tail(que), data);
}

int QUEUE_dequeue(Queue que, void **data)
{
	return SLIST_rem_next(que, NULL, data);
}

void *QUEUE_peek(Queue que)
{
	return SLIST_size(que) == 0 ? NULL : SLIST_data_of_node(SLIST_head(que));
}

int QUEUE_is_empty(Queue que)
{
	return SLIST_size(que) == 0 ? 1 : 0;
}

int QUEUE_size(Queue que)
{
	return SLIST_size(que);
}