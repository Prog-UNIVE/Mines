#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

typedef Slist Queue;

/* INTERFACE FUNCTION DECLARATIONS */

/**
*
* Initiate the queue.
*
* @return A reference - to a new, empty queue - if dynamic memory
* allocation for the ADT was successful - or NULL otherwise. Take really
* good care of this return value, since it will be needed as a parameter
* in subsequent calls - to the majority of other queue handling functions
* in this queue function interface - i.e. a sort of "handle" to the queue.
* @see QUEUEdestroy()
**/
Queue QUEUE_init();

/**
* Destroy the queue.
*
* The queue is destroyed - that is, all memory occupied by the
* elements is deallocated. The user-defined callback function
* @a destroy, given as an argument to @b QUEUEinit(), is responsible
* for freeing dynamically allocated element data, when this function
* is called. When all elements and data have been deallocated - the
* queue header is deallocated, too.
*
* @param[in] queue - a reference to current queue.
* @return Nothing.
* @see QUEUEinit()
**/
void QUEUE_destroy(Queue queue);

/**
* Insert(=enqueue) a new element - at the end of the queue.
*
* This function inserts an new element - with a reference to
* its corresponding data, given by parameter @a data - at the
* end of the queue.
*
* @param[in] queue - reference to current queue
* @param[in] data - reference to data to be stored in the new
* element, which is to be inserted at the end of the queue.
*
* @return Value 0 - if everything went OK - or value -1 otherwise.
**/
int QUEUE_enqueue(Queue queue, const void *data);

/**
* Remove(=dequeue) the head element.
*
* When called, the 2nd parameter of this function, @a data,
* should reference an (external, user-defined) pointer.
* After the call - this referenced, external pointer has been
* redirected, to point to the data of the removed element -
* if the call was succesful. The caller is responsible for
* the future  of this memory - deallocating it, if needed,
* for example.
*
* @param[in] queue - reference to current queue.
* @param[out] data - reference to a pointer. After the call,
* this referenced pointer has been redirected to point to
* the data of the removed element - if the call was
* successful. The caller is responsible for the future  of
* this memory - deallocating it, for example.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int QUEUE_dequeue(Queue queue, void **data);

/**
* Peek at the head of the queue.
*
* @param[in] queue - reference to the current queue.
*
* @return NULL if the queue is empty - or a reference
* to data of the head element, otherwise.
*
**/
void *QUEUE_peek(Queue queue);

/**
* Determine if the queue is empty - or not.
*
* @param[in] queue - a reference to the current queue.
* @return Value 1 - if the queue is indeed empty -
* or 0 otherwise.
**/
int QUEUE_is_empty(Queue queue);

/**
* Get the queue size.
*
* @param[in] queue - a reference to the current queue.
*
* @return The size, that is, the number of elements in the queue.
**/
int QUEUE_size(Queue queue);

#endif /* _QUEUE_H_ */