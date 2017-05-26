#include "slist.h"

struct SListElmt_
{
	void               *data;
	struct SListElmt_  *next;
};

struct SList_
{
	int                 size;
	struct SListElmt_    *head;
	struct SListElmt_    *tail;
};

Slist SLIST_init()
{
	Slist list;

	if ((list = (Slist)malloc(sizeof(struct SList_))) == NULL)
		return NULL;

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

void SLIST_destroy(Slist list)
{
	void *data;

	while (SLIST_size(list) > 0)
	{

		if (SLIST_rem_next(list, NULL, (void **)&data) == 0)
			free(data);
	}
	free(list);
}

int SLIST_ins_next(Slist list, SlistNode node, const void *data)
{
	SlistNode newelement;

	if ((newelement = (SlistNode)malloc(sizeof(struct SListElmt_))) == NULL)
		return -1;

	newelement->data = (void *)data;

	if (node == NULL)
	{
		if (list->size == 0)
			list->tail = newelement;

		newelement->next = list->head;
		list->head = newelement;
	}

	else
	{
		if (node->next == NULL)
			list->tail = newelement;

		newelement->next = node->next;
		node->next = newelement;
	}

	list->size++;

	return 0;
}

int SLIST_rem_next(Slist list, SlistNode node, void **data)
{

	SlistNode oldelement;

	if (list->size == 0)
		return -1;

	if (node == NULL)
	{
		*data = list->head->data;
		oldelement = list->head;
		list->head = list->head->next;

		if (list->size == 1)
			list->tail = NULL;
	}
	else
	{
		if (node->next == NULL)
			return -1;

		*data = node->next->data;
		oldelement = node->next;
		node->next = node->next->next;

		if (node->next == NULL)
			list->tail = node;
	}

	free(oldelement);

	list->size--;

	return 0;
}

int SLIST_size(Slist list)
{
	return list->size;
}

SlistNode SLIST_head(Slist list)
{
	return list->head;
}

SlistNode SLIST_tail(Slist list)
{
	return list->tail;
}

int  SLIST_is_head(Slist list, SlistNode node)
{
	return list->head == node ? 1 : 0;
}

int  SLIST_is_tail(Slist list, SlistNode node)
{
	return list->tail == node ? 1 : 0;
}

void *SLIST_data_of_node(SlistNode node)
{
	return node->data;
}

SlistNode SLIST_next(SlistNode node)
{
	return node->next;
}
