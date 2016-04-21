
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinels' next and prev should point to eachother or NULL
* as appropriate.
*/
static void init(struct LinkedList* list) {

	struct Link * front = (struct Link*)malloc(sizeof(struct Link));
	assert(front != 0);

	struct Link * back = (struct Link*)malloc(sizeof(struct Link));
	assert(back != 0);

	front->prev = back;
	front->next = NULL;

	back->prev = NULL;
	back->next = front;

	list->frontSentinel = front;
	list->backSentinel = back;
	list->size = 0;
	
}

/**
* Adds a new link with the given value before the given link and
* increments the list's size.
*/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	
	// Create new link
	struct Link * newLink = (struct Link*)malloc(sizeof(struct Link));

	// Save previous link
	struct Link * behindNewLink;
	behindNewLink = link->prev;

	// Assign pointer to newLink
	link->prev = newLink;
	behindNewLink->next = newLink;

	// Assign pointers from newLink
	newLink->prev = behindNewLink;
	newLink->next = link;

	// Add value to newLink
	newLink->value = value;

	// Increment size
	list->size++;

	
}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list->size != 0);

	struct Link * deleteMe = link;
	struct Link * beforeDeleteMe = link->prev;
	struct Link * afterDeleteMe = link->next;
	
	// Reassign pointers of links before and after deleteMe
	beforeDeleteMe->next = afterDeleteMe;
	afterDeleteMe->prev = beforeDeleteMe;

	// Clear pointers and delete link
	deleteMe->next = NULL;
	deleteMe->prev = NULL;
	free(deleteMe);

	// Decrement size
	list->size--;
}

/**
* Allocates and initializes a list.
*/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
* Deallocates every link in the list and frees the list pointer.
*/
void linkedListDestroy(struct LinkedList* list)
{
	
	while (!linkedListIsEmpty(list)) {
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// Checked!
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
	struct Link * prevFront;
	prevFront = (list->frontSentinel)->prev;

	// Assign prev of front sentinel && next of link before front sentinel
	prevFront->next = newLink;
	(list->frontSentinel)->prev = newLink;

	// Assign front and prev of newLink
	newLink->next = list->frontSentinel;
	newLink->prev = prevFront;

	// Assign value to new link
	newLink->value = value;

	// Increment size of linked list
	list->size++;
	
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
	struct Link * prevBack;
	prevBack = (list->backSentinel)->next;

	// Assign next of back sentinel && prev of link after back sentinel
	prevBack->prev = newLink;
	(list->backSentinel)->next = newLink;

	// Assign front and prev of newLink
	newLink->prev = list->backSentinel;
	newLink->next = prevBack;

	// Assign value to new link
	newLink->value = value;

	// Increment size of linked list
	list->size++;

}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list->size != 0);
	return list->frontSentinel->prev->value;
	
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list->size != 0);
	return list->backSentinel->next->value;
}

/**
* Removes the link at the front of the deque.
*/
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list->size != 0);

	// Link to Delete
	struct Link * deleteMe;
	deleteMe = list->frontSentinel->prev;
	
	// New link at front
	struct Link * newFront;
	newFront = list->frontSentinel->prev->prev;

	// Reassign front-sentinel prev and newFront next to each other
	newFront->next = list->frontSentinel;
	list->frontSentinel->prev = newFront;

	// Deallocate memory for delete node
	deleteMe->prev = NULL;
	deleteMe->next = NULL;
	free(deleteMe);
	deleteMe = NULL;

	// Decrement size of linked list
	list->size--;


}

/**
* Removes the link at the back of the deque.
*/
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list->size != 0);
	
	// Link to Delete 
	struct Link * deleteMe;
	deleteMe = list->backSentinel->next;

	// New link in back
	struct Link * newBack;
	newBack = list->backSentinel->next->next;

	// Reassign back-sentinel next and newBack prev to each other
	newBack->prev = list->backSentinel;
	list->backSentinel->next = newBack;

	// Remove pointers and delete link
	deleteMe->next = NULL;
	deleteMe->prev = NULL;
	free(deleteMe);
	deleteMe = NULL;

	// Decrement size of linked list
	list->size--;

}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list->size == 0) {
		return 1;
	}

	else {
		return 0;
	}
}

/**
* Prints the values of the links in the deque from front to back.
*/
void linkedListPrint(struct LinkedList* list)
{
	assert(list->size != 0);
	struct Link * printVal = list->frontSentinel->prev;

	do {
		printf(" %d ", printVal->value);
		printVal = printVal->prev;

	}
	while (printVal->prev != 0);
}

/**
* Adds a link with the given value to the bag.
*/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	linkedListAddBack(list, value);
}

/**
* Returns 1 if a link with the value is in the bag and 0 otherwise.
*/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list->size != 0);
	struct Link * currLink = list->frontSentinel->prev;

	do {
		if (currLink->value == value) {
			return 1;
		}
		currLink = currLink->prev;

	} while (currLink->prev != 0);
	return 0;
}

/**
* Removes the first occurrence of a link with the given value.
*/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	
	assert(list->size != 0);
	assert(linkedListContains(list, value));

	struct Link * currLink = list->frontSentinel->prev;

	do {

		if (currLink->value == value) {

			currLink->next->prev = currLink->prev;
			currLink->prev->next = currLink->next;

			currLink->next = NULL;
			currLink->prev = NULL;
			free(currLink);

			//Decrement size
			list->size--;

			return;

		}
		currLink = currLink->prev;
	} while (currLink != 0);

	
}