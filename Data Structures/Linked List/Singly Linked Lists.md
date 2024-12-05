# Singly Linked Lists

A linked list is a collection of variables that are linked together through pointers. There are many types of linked list but this will go over the implementation of a singly linked list.

## Basic structure

A singly linked list consists of individual `links`.

Each `link` contains the following:
* `next` pointer which points to the link after it in the list. It is initialized to `NULL`.
* `thing` variable, which contains pointers to a data type you define. The default data type is `int`.

Once a link is created, it can be added to the linked list. The structure of the linked list is as follows:
* `head` pointer which points to the first element in the linked list. It is initialized to `NULL`.
* `length` integer which keeps track of how many elements are in the list. It is initialized to `0`.

## Methods

### Initialization

Before manipulating any data, we need to initialize our `things`, `links` and `linked list`. To do that, we do the following:
1. Set `thing` to the address of some thing.

```C
int value = 0;
Thing thing = init_Thing(&value);
```

2. Create an instance of a `link`.

```C
Link new_link = init_Link(thing);
```

3. Create an instance of a `linked list`.

```C
Linked_List linked_list = init_Linked_List(new_link);
```

### Length of list

We get the length of the list using the `get_length()` method which accepts `linked list` as an argument and returns the length member.

### Push back

We can add onto the list by calling `push_back()` which accepts `linked list` and `link` as an argument. If the list is empty, we set the head to `link`, else we traverse to the end of the link and set the last elements' `next` pointer to `link`.