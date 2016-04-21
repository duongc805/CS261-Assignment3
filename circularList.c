
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinel's next and prev should point to the sentinel itself.
*/
static void init(struct CircularList* list)
{
	list->sentinel = (struct Link *)malloc(sizeof(struct Link));
	assert(list->sentinel != 0);

	// Assign pointers
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->sentinel->value = -1;

	// Assign size = 0
	list->size = 0;

}

/**
* Creates a link with the given value and NULL next and prev pointers.
*/
static struct Link* createLink(TYPE value)
{
	// Create link
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));

	// Create null pointers
	newLink->next = NULL;
	newLink->prev = NULL;
	
	// Save value in link
	newLink->value = value;

	// Return link
	return newLink;
}

/**
* Adds a new link with the given value after the given link and
* increments the list's size.
*/
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link * addMe = createLink(value);

	// Assign addMe pointers
	addMe->next = link->next;
	addMe->prev = link;
	
	// Assign pointers to links flanking addMe
	(addMe->next)->prev = addMe;
	(addMe->prev)->next = addMe;

	// Increment list size
	list->size++;


}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct CircularList* list, struct Link* link)
{
	printf("Link to be deleted: %g\n", link->value);

	// Point flanking links to each other
	link->prev->next = link->next;
	link->next->prev = link->prev;

	// Null link pointers and delete link
	link->next = NULL;
	link->prev = NULL;
	free(link);
	link = NULL;

	// Decrement list size 
	list->size--;

}

/**
* Allocates and initializes a list.
*/
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
* Deallocates every link in the list and frees the list pointer.
*/
void circularListDestroy(struct CircularList* list)
{


	while (!circularListIsEmpty(list)) {
		struct Link * temp = list->sentinel->next;
		removeLink(list, temp);
	}

	free(list->sentinel);
	free(list);

}

/**
* Adds a new link with the given value to the front of the deque.
*/
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value);
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE circularListFront(struct CircularList* list)
{
	return ((list->sentinel)->next)->value;
	
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE circularListBack(struct CircularList* list)
{
	return ((list->sentinel)->prev)->value;
}

/**
* Removes the link at the front of the deque.
*/
void circularListRemoveFront(struct CircularList* list)
{
	removeLink(list, (list->sentinel)->next);
}

/**
* Removes the link at the back of the deque.
*/
void circularListRemoveBack(struct CircularList* list)
{
	removeLink(list, (list->sentinel)->prev);
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int circularListIsEmpty(struct CircularList* list)
{
	if (list->size == 0) {
		return 1;
	}
	return 0;
}

/**
* Prints the values of the links in the deque from front to back.
*/
void circularListPrint(struct CircularList* list)
{
	int size = list->size;
	struct Link * itr = list->sentinel->next;
	printf("List front to back: ");

	while (size) {
		printf("%g, ", itr->value);
		//printf("\tValue:%lf, Address:%p, Address next:%p, Address before:%p, value next: %lf\n", itr->value, itr, itr->next, itr->prev, itr->next->value);
		itr = itr->next;
		size--;
	}
	printf("\n");
}

/**
* Reverses the deque.
*/
void circularListReverse(struct CircularList* list)
{
	struct Link * itr = list->sentinel;
	
	// Traverse all size + 1 links (data links + sentinel)

	for (int i = 0; i < list->size + 1; i++) {
		// Save current node
		struct Link * temp = itr->next;

		// Set current node next to previous
		itr->next = itr->prev;

		// Set current node prev to next
		itr->prev = temp;

		// Traverse to *new* next node
		itr = itr->next;
	}

}
