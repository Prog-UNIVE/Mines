#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack STACK_init()
{
	return SLIST_init();
}

void STACK_destroy(Stack stk)
{
	SLIST_destroy(stk);
}

int STACK_push(Stack stk, const void *data)
{
	return SLIST_ins_next(stk, NULL, data);
}

int STACK_pop(Stack stk, void **data)
{
	return SLIST_rem_next(stk, NULL, data);
}

void *STACK_peek(Stack stk)
{
	return SLIST_size(stk) == 0 ? NULL : SLIST_data_of_node(SLIST_head(stk));
}

int STACK_is_empty(Stack stk)
{
	return SLIST_size(stk) == 0 ? 1 : 0;
}

int STACK_size(Stack stk)
{
	return SLIST_size(stk);
}