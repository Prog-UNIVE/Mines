#ifndef _SLIST_H_
#define _SLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

/**
* Use a @b typedef - to hide the interior of @b SList_ - in the
* implementation file. This is how @a data @a hiding can be done in C.
*
**/
typedef struct SList_ *Slist;

/**
* Another @b typedef - for hiding the interior of @b SListElmt_  -
* in the implementation file.
*
**/
typedef struct SListElmt_ *SlistNode;

/**
*
* Initiate the list.
*
* @param[in] destroy - A reference to a user-made function, reponsible
* for freeing node data, when the list is deleted. If @a destroy is
* NULL - then node data will be left untouched when the list is
* destroyed.
* @return A reference - to a new, empty list - if dynamic memory
* allocation for the ADT was successful - or NULL otherwise. Take
* really good care  of this return value, since it will be needed as
* a parameter in subsequent calls - to the majority of other list
* handling functions in this function interface - i.e. a sort of
* "handle" to the list.
* @see SLISTdestroy()
**/
Slist SLIST_init();

/**
* Destroy the list.
*
* The list is destroyed - that is, all the memory occupied by the nodes
* is deallocated. Single node data isn't deallocated, after freeing nodes
* the list header is deallocated, too.
*
* @param[in] list - a reference to current list.
* @return Nothing.
**/
void SLIST_destroy(Slist list);

/**
* Insert a new node - after parameter @a node - into the list.
*
* This function inserts an new node, with a reference to node data
* given by parameter @a data - @b after the node referenced by
* parameter @a node - into @a list.
* If you want to insert the new node at the beginning, the
* parameter @a node should be set to NULL.
*
* @param[in] list - reference to current list
* @param[in] node - the node after which the new node is to be
* inserted. If set to @b NULL - the new node is inserted at the
* beginning.
* @param[in] data - reference to data to be stored in the new node,
* that is inserted into the list.
*
* @return Value 0 - if everything went OK - or value -1 otherwise.
**/
int SLIST_ins_next(Slist list, SlistNode node, const void *data);

/**
* Remove the node - directly @b after - parameter @a node.
*
* After the call - an (external) pointer referenced by parameter
* @a data, has been redirected to point to data of the removed
* node - if the call was succesful. If parameter @a node
* is set to NULL, then the first node in @a list will be removed.
* The caller is responsible for the future of this memory -
* deallocating it, for example.
*
* @param[in] list - reference to current list.
* @param[in] node - the node just @b before the node to be removed.
* @param[out] data - reference to a pointer, that will point to data
* of the removed node after the call - if successful.
*
* @return Value 0 - if everything went OK - or value -1
* otherwise.
**/
int SLIST_rem_next(Slist list, SlistNode node, void **data);

/**
* Get the list size.
*
* @param[in] list - a reference to the current list.
*
* @return The size, that is, the number of nodes in the list.
**/
int SLIST_size(Slist list);

/**
* Get a reference to the head node of the list.
*
* @param[in] list - a reference to the current list.
* @return A reference to the @b first node in the list.
**/
SlistNode SLIST_head(Slist list);

/**
* Get a reference to the tail node of the list.
*
* @param[in] list - a reference to the current list.
* @return A reference to the @b last node in the list.
**/
SlistNode SLIST_tail(Slist list);

/**
* Determine if a certain node is the head node of
* the list - or not.
*
* @param[in] list - a reference to the current list.
* @param[in] node - a reference to the node to be tested.
* @return Value 1 - if @a node indeed is the first node
* of the list - or 0 otherwise.
**/
int SLIST_is_head(Slist list, SlistNode node);

/**
* Determine if a certain node is the tail node
* of the list - or not.
*
* @param[in] list - a reference to the current list.
* @param[in] node - a reference to the node to be tested.
* @return Value 1 - if @a node indeed is the last node
* of the list - or 0 otherwise.
**/
int SLIST_is_tail(Slist list, SlistNode node);

/**
* Get a reference to data stored in a node.
*
* @param[in] node - a reference to the current node.
* @return Generic reference to data - stored in parameter @a node.
**/
void *SLIST_data_of_node(SlistNode node);

/**
* Get a reference to the next node in the list.
*
* @param[in] node - a reference to @b current node.
* @return A reference to the @b next node - following
* parameter @a node - in the list.
**/
SlistNode SLIST_next(SlistNode node);

#endif /* _SLIST_H_ */