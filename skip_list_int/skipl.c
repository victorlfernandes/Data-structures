#include "skipl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node_t;

struct node {
    element_t value;
    int level;
    node_t *next;
    node_t *down;
};

struct skip_list {
    int max_level;
    int n_levels;
    node_t *start;
};

node_t *create_node(element_t value, int level, node_t *next, node_t *down) {

    // allocating and checking errors
    node_t *new_node = malloc(sizeof(node_t));
    assert(new_node != NULL);

    // assigning values
    new_node->value = value;
    new_node->level = level;
    new_node->next  = next;
    new_node->down  = down;

    return new_node;
}

skipl_t *create_sl() {

    // allocating and checking errors
    skipl_t *sl = malloc(sizeof(skipl_t));
    assert(sl != NULL);

    // assigning values
    sl->max_level = MAX_LEVEL;
    sl->n_levels  = 1;
    node_t *first_header = create_node(-1, 0, NULL, NULL);
    sl->start = first_header;

    return sl;
}

void delete_sl(skipl_t *sl) {

    assert(sl != NULL);

    node_t *level_start = sl->start;
    int level_counter = 0;

    while (level_counter < sl->n_levels) {
    
        node_t *node = level_start;
        node_t *next_level_start = node->down;

        while (node != NULL) {
            node_t *aux = node;
            node = node->next;
            free(aux);
        }

        level_start = next_level_start;
        level_counter++;
    }

    free(sl);
}

int randomize_level() {

    int level = 0;

    while (rand() % 2 == 0 && level < MAX_LEVEL)
        level++;

    return level;
}

void insert_sl(skipl_t *sl, element_t element) {

    assert(sl != NULL);

    // checking if the value is already on the list
    bool repeated = search_sl(sl, element);
    if (repeated) {
        print_error(1, NONE_CHAR);
        return;
    }

    // to insert the element, we must find the correct position of it on 
    // each level 
    // we can store these positions into an array
    // array[0] keeps the previous node of the insertion on level 0
    // array[1] keeps the previous node of the insertion on level 1
    // ...
    // the size of this array corresponds to the number of levels
    node_t **insertion_pos = malloc(MAX_LEVEL * sizeof(node_t *));

    // calculating the level of the new node
    int newnode_level = randomize_level();

    // sentinel node to go through the list
    node_t *node = sl->start;

    // going through the list to find the positions
    // this fist while controls vertical movement
    while (node != NULL && node->level != 0) {

        // this second while controls horizontal movement
        while (node->next != NULL && node->next->value < element) 
            node = node->next;

        // when the second while finishes, we found the insertion position
        // at the current level
        // we must store this value and go to the next one
        insertion_pos[node->level] = node;
        node = node->down;

    }

    // searching at level 0
    while (node->next != NULL && node->next->value < element) 
        node = node->next;
    insertion_pos[node->level] = node;

    // as we know the positions, its possible to insert
    // inserting into existing levels
    int cur_level = 0;
    while (cur_level < sl->n_levels && cur_level <= newnode_level) {

        // creating the node
        node_t *new_node = create_node(element, cur_level, NULL, NULL);

        // establishing the relation between the new node and the list
        new_node->next = insertion_pos[cur_level]->next;
        if (cur_level == 0) 
            new_node->down = NULL;
        else 
            new_node->down = insertion_pos[cur_level - 1]->next;

        insertion_pos[cur_level]->next = new_node;
        cur_level++;
    }

    // creating new levels, if necessary
    for (int cur_level = sl->n_levels; cur_level <= newnode_level; cur_level++) {

        // creating a new node
        node_t *new_node = create_node(element, cur_level, NULL, insertion_pos[cur_level - 1]->next);
        // creating a new header
        node_t *new_header = create_node(-1, cur_level, new_node, sl->start);

        sl->start = new_header;
        insertion_pos[cur_level] = new_header;

        sl->n_levels++;
    }

    free(insertion_pos);
}

void remove_sl(skipl_t *sl, element_t key) {
    
    assert(sl != NULL);

    // checking if the key exists
    bool key_presence = search_sl(sl, key);
    if (!key_presence) {
        print_error(1, NONE_CHAR);
        return;
    }

    // to remove an element, we must find the previous node of the key on
    // each level, so we can update its pointer to the next of the key
    // and then delete the desired node without breaking the list logic
    // just like in the insertion, we can keep these positons in an array
    node_t **remove_pos = malloc(MAX_LEVEL * sizeof(node_t *));

    // sentinel node to go through the list
    node_t *node = sl->start;

    // going through the list to find the positions
    // this fist while controls vertical movement
    while (node != NULL && node->level != 0) {

        // this second while controls horizontal movement
        while (node->next != NULL && node->next->value < key) 
            node = node->next;

        // when the second while finishes, we found the remove position
        // at the current level
        // we must store this value and go to the next one
        remove_pos[node->level] = node;
        node = node->down;

    }

    // searching at level 0
    while (node->next != NULL && node->next->value < key) 
        node = node->next;
    remove_pos[node->level] = node;

    // as we know the positions, its possible to remove
    // removing the key from every level it belongs
    int cur_level = 0;
    while (cur_level < sl->n_levels) {

        if (remove_pos[cur_level]->next != NULL) {
            node_t *rmv_node = remove_pos[cur_level]->next;
            remove_pos[cur_level]->next = rmv_node->next;
            free(rmv_node);
        }

        cur_level++;
    }

    // deleting the level, if necessary
    while (sl->start->next == NULL) {

        node_t *rmv_node = sl->start;
        sl->start = sl->start->down;
        free(rmv_node);

        sl->n_levels--;
    }

    free(remove_pos);
}

/*
void print_node(node_t *node) {
    
    printf("%d\r\n", node->value);

}
*/
void print_error(int code, char ch) {

    if (code)
        printf("OPERACAO INVALIDA\r\n");
    else
        printf("NAO HA PALAVRAS INICIADAS POR %c\r\n", ch);

}

bool search_sl(skipl_t *sl, element_t key) {

    assert(sl != NULL);

    // sentinel node to go through the list
    node_t *node = sl->start;

    // searching at levels above 0
    // this fist while controls the vertical movement
    while (node != NULL && node->level != 0) {

        // this second while controls horizontal movement
        while (node->next != NULL && node->next->value < key) 
            node = node->next;

        // when the second while finishes, the sentinel must down a level
        node = node->down;

    }

    // searching at level 0
    while (node->next != NULL && node->next->value < key) 
        node = node->next;

    // checking if we found the key
    if (node->next != NULL && node->next->value == key) 
        return true;
    else
        return false;

}

void print_sl(skipl_t *sl) {

    node_t *level_start = sl->start;
    node_t *node = level_start;
    int level_counter = sl->n_levels - 1;

    while (level_start != NULL) {

        printf("Level %d: ", level_counter);

        while (node != NULL) {
            printf("%d ", node->value);
            node = node->next;
        }

        printf("\n");
        node = level_start->down;
        level_start = level_start->down;
        level_counter--;
    }

}
