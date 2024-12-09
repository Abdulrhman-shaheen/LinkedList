#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>

// * LINKED NODES
typedef struct node
{
    int data;
    struct node *link;

} Node;

// Insertions
void insert_end(Node **head, int data);
void insert_start(Node **head, int data);
void insert_sorted(Node **head, int data);

// Deletions
void delete_end(Node **head);
void delete_start(Node **head);
void delete_element(Node **head, int data);

// Search
void search(Node **head, int data);

// Display
void print_list(Node *head);

// Reverse
void reverse(Node **head);

// * LINKED POLYNOMIAL
typedef struct term
{
    float coeff;
    int exp;
    struct term *link;

} term;

void insert_sorted_p(term **poly, float coeff, int exp);

void delete_exp(term **poly, int exp);

void print_poly(term *poly);

term *add_poly(term **poly1, term **poly2);
term *multiply_poly(term **poly1, term **poly2);

// * Doubly Linked List

typedef struct d_node
{
    struct d_node *prev;
    int data;
    struct d_node *next;

} DNode;

// Insertions
void d_insert_end(DNode **head, int data);
void d_insert_start(DNode **head, int data);
void d_insert_sorted(DNode **head, int data);

// Deletions
void d_delete_end(DNode **head);
void d_delete_start(DNode **head);
void d_delete_element(DNode **head, int data);

// Search
void d_search(DNode **head, int data);

// Display
void d_print_list(DNode *head);

// Reverse
void d_reverse(DNode **head);

#endif 