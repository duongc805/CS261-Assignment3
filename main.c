
#include "linkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>




int main() {


	struct LinkedList* list = linkedListCreate();

	int n;
	int val;

	do {
		printf("\n1. Add to front \n2. Remove from front \n3. Add to back \n4. Remove from back");
		printf("\n5. Empty? \n6. Print All: \n7. Contains: \n8. Remove Value: \n9. Quit \n");
		scanf_s("%d", &n);

		if (n == 1) {
			printf("  Add Front:");
			scanf_s("%d", &val);
			linkedListAddFront(list, val);
			printf("\n Item Added: %d\n", linkedListFront(list));

		}
		else if (n == 2) {
			printf("  Remove Front");
			linkedListRemoveFront(list);

			if (!linkedListIsEmpty(list)) {
				printf(" \nNew front: %d\n", linkedListFront(list));
			}
		}
		else if (n == 3) {
			printf("  Add Back:");
			scanf_s("%d", &val);
			linkedListAddBack(list, val);
			printf("\n Item Added: %d\n", linkedListBack(list));
		}
		else if (n == 4) {
			printf("  Remove Back");
			linkedListRemoveBack(list);
			
			if (!linkedListIsEmpty(list)) {
				printf(" \nNew back: %d\n", linkedListBack(list));
			}
		}
		else if (n == 5) {
			printf(" Empty: %d\n", linkedListIsEmpty(list));
		}
		else if (n == 6) {
			linkedListPrint(list);
		}
		else if (n == 7) {
			printf("Check if link list contains: ");
			scanf_s("%d", &val);
			printf("%d\n", linkedListContains(list, val));

		}
		else if (n == 8) {
			printf("Remove Value: ");
			scanf_s("%d", &val);
			linkedListRemove(list, val);
			if (!linkedListIsEmpty(list)) {
				printf("\nNow link list contains: ");
				linkedListPrint(list);
			}



		}

	} while (n != 9);




	linkedListDestroy(list);

	return 0;
}