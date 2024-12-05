#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
	int value = 5;

	Thing thing = init_Thing(&value);

	Link new_link = init_Link(thing);

	Linked_List linked_list = init_Linked_List(new_link);

	printf("Size of linked list:\t%d\n", get_length(linked_list));
	int value2 = 8;
	Link newer_link = init_Link(&value2);
	push_back(linked_list, newer_link);
	printf("Size of linked list:\t%d\n", get_length(linked_list));

	for (int i = 0; i < get_length(linked_list); i++) {
		printf("[%d]:\t%d", i, *value_at(linked_list, i));
	}

	// Don't forget to free the allocated memory
	free(new_link);
	free(linked_list);


	return 0;
}
