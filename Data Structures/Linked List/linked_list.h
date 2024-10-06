#include <stddef.h>

//bool structure
typedef enum {
    false,
    true
} bool;

//Thing pointer, which points to any data-type
typedef void *Thing;

Thing init_Thing(Thing thing) {
    Thing new_thing = malloc(sizeof(typeof(*thing)));
    //i left of here. i'm tryng to create a Thing type and not have to account for each type
}


//Link datatype, which represents a node in list
typedef struct {
    struct Link *next;
    Thing thing;
} *Link;

//function for initializing link. call function to initialize link. when calling, place link name in place of `link` argument
Link init_Link(Thing thing) {
    Link new_link = malloc(sizeof(*new_link));
    if (new_link == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    new_link->next = NULL;
    new_link->thing = thing;
    return new_link;
}

//Linked list datatype.
typedef struct {
    Link head;
    int length;
} *Linked_List;

//function for initializing linked list. call function to initialize linked list. when calling, place linked list name in place of `linked_list` argument
// #define init_Linked_List(linked_list, head) Linked_List linked_list = { linked_list->head = head, linked_list->length = ((head) ? (0) : (1)) }
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

//function to get length of linked list
int get_length(Linked_List linked_list) {
    if (linked_list->head && linked_list->length == 0) {
        linked_list->length++;
        return linked_list->length;
    }
    return linked_list->length;
}

void set_head(Linked_List linked_list, Link link) {
    linked_list->head = link;
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
        return NULL;
    }
    Link curr = linked_list->head;
    int i = 0;
    while (curr->next && i < index) {
        curr = curr->next;
        i++;
    }
    return curr->thing;
}
