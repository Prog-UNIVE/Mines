#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

typedef Slist Stack;

/* INTERFACE FUNCTION DECLARATIONS */
/**
*
* Initiate the stack.
*
* @return A reference - to a new, empty stack - if dynamic memory
* allocation for the ADT was successful - or NULL otherwise. Take really
* good care of this return value, since it will be needed as a parameter in
* subsequent calls - to the majority of other stack handling functions
* in this stack function interface - i.e. a sort of "handle" to the stack.
* @see STACK_destroy()
**/
Stack STACK_init();

/**
* Destroy the stack.
*
* The stack is destroyed - that is, all memory occupied by the
* elements is deallocated. The user-defined callback function
* @a destroy, given as an argument to @b STACKinit(), is responsible
* for freeing dynamically allocated element data, when this function
* is called. When all elements and data have been deallocated - the
* stack header is deallocated, too.
*
* @param[in] stk - a reference to current stack.
* @return Nothing.
* @see STACK_init()
**/
void STACK_destroy(Stack stk);

/**
* Insert(=push) a new element - at the top of the stack.
*
* This function inserts an new element - with a reference to
* its corresponding data, given by parameter @a data - at the
* top of the stack.
*
* @param[in] stk - reference to current stack
* @param[in] data - reference to data to be stored in the new
* element, which is to be inserted at the top of the stack.
*
* @return Value 0 - if everything went OK - or value -1 otherwise.
**/
int STACK_push(Stack stk, const void *data);

/**
* Remove(=pop) the top element.
*
* When called, the 2nd parameter of this function, @a data,
* should reference an (external, user-defined) pointer.
* After the call - this referenced, external pointer has been
* redirected, to point to the data of the removed element -
* if the call was succesful. The caller is responsible for
* the future  of this memory - deallocating it, if needed,
* for example.
*
* @param[in] stk - reference to current stack.
* @param[out] data - reference to a pointer. After the call,
* this referenced pointer has been redirected to point to
* the data of the removed element - if the call was
* successful. The caller is responsible for the future  of
* this memory - deallocating it, for example.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int STACK_pop(Stack stk, void **data);

/**
* Peek at the top of the stack.
*
* @param[in] stk - reference to the current stack.
*
* @return NULL if the stack is empty - or a reference
* to data of the top element, otherwise.
*
**/
void *STACK_peek(Stack stk);

/**
* Determine if the stack is empty - or not.
*
* @param[in] stk - a reference to the current stack.
* @return Value 1 - if the stack is indeed empty -
* or 0 otherwise.
**/
int STACK_is_empty(Stack stk);

/**
* Get the stack size.
*
* @param[in] stk - a reference to the current stack.
*
* @return The size, that is, the number of elements in the stack.
**/
int STACK_size(Stack stk);

#endif /* _STACK_H_ */
