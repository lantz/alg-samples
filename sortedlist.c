/* Sorted singly-linked string lists in C
 * Back to (very basic) basics!!
 * Bob Lantz, October 2017
 * Dedicated to: S. Skiena
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
  char *item;
  struct node *next;
} node;

typedef struct list {
  node *head;
  node *sentinel; /* end of list marker */
} list;

/* Return an empty sorted list: O(1) */
list *newlist() {
  list *l = (list *) malloc(sizeof(list));
  l->head = l->sentinel = (node *) malloc(sizeof(list));
  l->sentinel->item = NULL;
  l->sentinel->next = NULL;
  return l;
}

/* Find node containing item in sorted list l: O(n) */
node *find(list *l, char *item) {
  for (node *n = l->head; n != l->sentinel; n = n->next) {
    int cmp = strcmp(n->item, item);
    if (cmp == 0) return n;
    if (cmp > 0) break;
  }
  return NULL;
}

/* Insert item in sorted list l: O(n)
 * Duplicates an existing node and stuffs item into it. */
void insert(list *l, char *item) {
  node *n;
  for (n = l->head; n != l->sentinel; n = n->next)
    if (strcmp(n->item, item) >= 0) break;
  node *new = (node *) malloc(sizeof(node));
  *new = *n;
  if (n == l->sentinel) l->sentinel = new;
  n->item = item;
  n->next = new;
 }

/* "Delete" node n in sorted list l: O(1)
 * Actually updates n and frees n's successor */
void delete(list *l, node *n) {
  node *next = n->next;
  *n = *next;
  if (next == l->sentinel) l->sentinel = n;
  free(next);
}

/* Print out list l: O(n) */
void dump(list *l) {
  printf("{");
  for (node *n = l->head; n != l->sentinel; n = n->next) {
    printf("%s", n->item);
    if (n->next != l->sentinel) printf(", ");
  }
  printf("}\n");
}

/* Simple test */
void test() {
  list *l = newlist();
  char *items[] = { "this", "is", "a", "test", "foo", "bar", "baz" };
  size_t nitems = sizeof(items)/sizeof(items[0]);
  for (int i = 0; i < nitems; i++) {
    printf("Inserting %s: ", items[i]);
    insert(l, items[i]);
    dump(l);
    assert(find(l, items[i]) != NULL);
  }
  for (int i = 0; i < nitems; i++) {
    printf("Deleting %s: ", items[i]);
    delete(l, find(l, items[i]));
    dump(l);
    assert(find(l, items[i]) == NULL);
  }
  printf("Done.\n");
}

int main() {
  test();
}
