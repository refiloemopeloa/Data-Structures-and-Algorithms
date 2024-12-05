#include <stddef.h>

typedef struct {
    //change the data type of thing here
    int* value;
} Thing;


// Link datatype, which represents a node in list
typedef struct {
    struct Link *next;
    Thing thing;
} *Link;

/**
 * This function initializes a thing.
 * @param value The value you want the thing to point to
 * @return A thing that points to the value passed to the function
 */
Thing init_Thing(int *value) {
    Thing new_thing = {value};
    return new_thing;
}

/**
    This function initializes a link.

    @param thing: A thing that you'd like the link to be associated with.
    @return A link with next being null and thing being the thing passed via argument.
*/
Link init_Link(Thing thing) {

    Link new_link = malloc(sizeof(*new_link));

    if (new_link == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_link);
        return NULL;
    }

    new_link->next = NULL,
    new_link->thing = thing;

    return new_link;
}

//Linked list datatype.
typedef struct {
    Link head;
    int length;
} *Linked_List;

/**
 * This function initializes a linked list.
 * @param new_link A link which will be set as the head of the linked list.
 * @return A linked list with one thing in it, and the link associated with thing being the head of the linked list.
 */
Linked_List init_Linked_List(Link new_link) {
    Linked_List linked_list = malloc(sizeof(*linked_list));

    if (linked_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_link);
        return NULL;
    }

    linked_list->head = new_link;
    linked_list->length = ((new_link) ? (1) : (0));

    return linked_list;
}

/**
 * This function returns the length of a linked list
 * @param linked_list A linked list who's length you want.
 * @return The length of the passed linked list.
 */
int get_length(Linked_List linked_list) {
    if (linked_list->head && linked_list->length == 0) {
        linked_list->length++;
        return linked_list->length;
    }
    return linked_list->length;
}


//function for adding link to linked list
void push_back(Linked_List linked_list, Link link) {
    if (get_length(linked_list) == 0) {
        set_head(linked_list, link);
        linked_list->length++;
        printf("Push back successful!\n");
    } else {
        Link curr = linked_list->head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = link;
        linked_list->length++;
        printf("Push back successful!\n");
    }

    return;
}

Thing value_at(Linked_List linked_list, int index) {
    if (index > get_length(linked_list) - 1) {
        perror("index out of range!");
        Thing thing = {.void_thing = NULL};
        return thing;
    }
    Link curr = linked_list->head;
    int i = 0;
    while (curr->next && i < index) {
        curr = curr->next;
        i++;
    }
    return curr->thing;
}
