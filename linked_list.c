#include "linked_list.h"

void insert_end(Node **head, int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->link = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    Node *temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new_node;
}

void insert_start(Node **head, int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->link = NULL;
    if ((*head) == NULL)
    {
        (*head) = new_node;
        return;
    }
    new_node->link = (*head);
    (*head) = new_node;
}

void insert_sorted(Node **head, int data)
{

    Node *temp = *head;
    if (temp == NULL || temp->data > data)
    {
        insert_start(head, data);
        return;
    }
    while (temp->link != NULL && temp->link->data < data)
    {
        temp = temp->link;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->link = temp->link;
    temp->link = new_node;
}

void delete_end(Node **head)
{
    if ((*head) == NULL)
    {
        return;
    }
    Node *ptr = *head;
    if (ptr->link == NULL)
    {
        free(ptr);
        *head = NULL;
        return;
    }

    while (ptr->link->link != NULL)
    {
        ptr = ptr->link;
    }
    free(ptr->link);
    ptr->link = NULL;
}

void delete_start(Node **head)
{

    if (*head == NULL)
    {
        return;
    }

    Node *temp = *head;

    *head = (*head)->link;
    free(temp);
}
void delete_element(Node **head, int data)
{

    if (*head == NULL)
    {
        printf("List Empty\n");
        return;
    }
    // If the element is at the start
    if ((*head)->data == data)
    {
        delete_start(head);
        return;
    }

    // If only one element and it is not the element to be deleted
    if ((*head)->link == NULL)
    {
        printf("Element not found\n");
        return;
    }

    Node *temp = *head;

    while (temp->link->data != data)
    {
        temp = temp->link;
        if (temp->link == NULL)
        {
            printf("Element not found\n");
            return;
        }
    }
    Node *ptr = temp->link;
    temp->link = temp->link->link;
    free(ptr);
}

void search(Node **head, int data)
{
    int pos = 1;

    DNode *temp = *head;
    while (temp != NULL && temp->data != data)
    {
        temp = temp->next;
        pos++;
    }

    if (temp == NULL)
    {
        printf("Element not found\n");
    }
    else
    {
        printf("Element found at position %d\n", pos);
    }
}

void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}

void reverse(Node **head)
{

    if (*head == NULL)
    {
        printf("List Empty\n");
        return;
    }

    // One element
    if ((*head)->link == NULL)
    {
        return;
    }
    Node *temp = *head;
    Node *next;
    Node *prev = NULL;
    while (temp != NULL)
    {
        next = temp->link;
        temp->link = prev;
        prev = temp;
        temp = next;
    }
    *head = prev;
}

// * POLYNOMIAL

void insert_sorted_p(term **poly, float coeff, int exp)
{
    term *temp = *poly;

    term *new_term = (term *)malloc(sizeof(term));
    new_term->coeff = coeff;
    new_term->exp = exp;
    new_term->link = NULL;

    if ((*poly) == NULL || (*poly)->exp < exp)
    {
        new_term->link = *poly;
        *poly = new_term;
        return;
    }

    while (temp->link != NULL && temp->link->exp > exp)
    {
        temp = temp->link;
    }
    if (temp->link != NULL && temp->link->exp == exp)
    {
        temp->link->coeff += coeff;
        free(new_term);
    }
    else
    {
        new_term->link = temp->link;
        temp->link = new_term;
    }
}

void delete_exp(term **poly, int exp)
{

    term *temp = *poly;
    if (temp == NULL)
    {
        printf("List Empty\n");
        return;
    }

    // If the element is at the start
    if (temp->exp == exp)
    {
        term *temp2 = temp;
        temp = temp->link;
        free(temp2);
        return;
    }

    // If only one element and it is not the element to be deleted
    if (temp->link == NULL)
    {
        printf("Term with given Exponent is not found\n");
        return;
    }

    while (temp->link->exp != exp)
    {
        temp = temp->link;
        if (temp->link == NULL)
        {
            printf("Element not found\n");
            return;
        }
    }
    term *ptr = temp->link;
    temp->link = temp->link->link;
    free(ptr);
}

void print_poly(term *poly)
{
    while (poly != NULL)
    {
        printf("%.1f x^%d", poly->coeff, poly->exp);
        poly = poly->link;
        if (poly != NULL)
        {
            printf(" + ");
        }
    }
}

term *add_poly(term **poly1, term **poly2)
{
    term *new_poly = NULL;
    term *temp1 = *poly1;
    term *temp2 = *poly2;
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->exp > temp2->exp)
        {
            insert_sorted_p(&new_poly, temp1->coeff, temp1->exp);
            temp1 = temp1->link;
        }
        else if (temp1->exp < temp2->exp)
        {
            insert_sorted_p(&new_poly, temp2->coeff, temp2->exp);
            temp2 = temp2->link;
        }
        else
        {
            insert_sorted_p(&new_poly, temp1->coeff + temp2->coeff, temp1->exp);
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
    }
    if (temp1 == NULL)
    {
        while (temp2 != NULL)
        {
            insert_sorted_p(&new_poly, temp2->coeff, temp2->exp);
            temp2 = temp2->link;
        }
    }

    if (temp2 == NULL)
    {
        while (temp1 != NULL)
        {
            insert_sorted_p(&new_poly, temp1->coeff, temp1->exp);
            temp1 = temp1->link;
        }
    }

    return new_poly;
}

term *multiply_poly(term **poly1, term **poly2)
{
    term *new_poly = NULL;
    term *temp1 = *poly1;
    term *temp2 = *poly2;

    while (temp1 != NULL)
    {
        while (temp2 != NULL)
        {
            insert_sorted_p(&new_poly, temp1->coeff * temp2->coeff, temp1->exp + temp2->exp);
            temp2 = temp2->link;
        }
        temp2 = *poly2;
        temp1 = temp1->link;
    }
    return new_poly;
}

void d_insert_end(DNode **head, int data)
{
    DNode *new_node = (DNode *)malloc(sizeof(DNode));

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    DNode *temp = (*head);

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}

void d_insert_start(DNode **head, int data)
{
    DNode *new_node = (DNode *)malloc(sizeof(DNode));

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    new_node->next = *head;
    (*head)->prev = new_node;
    (*head) = new_node;
}
void d_insert_sorted(DNode **head, int data)
{

    DNode *temp = *head;
    if (temp == NULL || temp->data > data)
    {
        d_insert_start(head, data);
        return;
    }
    while (temp->next != NULL && temp->next->data < data)
    {
        temp = temp->next;
    }

    DNode *new_node = (DNode *)malloc(sizeof(DNode));
    new_node->data = data;

    new_node->next = temp->next;
    if (temp->next != NULL)
    {
        temp->next->prev = new_node;
    }

    new_node->prev = temp;
    temp->next = new_node;
}

// Deletions
void d_delete_end(DNode **head)
{
    if (*head == NULL)
    {
        return;
    }
    DNode *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    if (temp->prev != NULL)
    {
        temp->prev->next = NULL;
    }
    else
    {
        (*head) = NULL;
    }

    free(temp);
}
void d_delete_start(DNode **head)
{
    if (*head == NULL)
    {
        return;
    }
    DNode *temp = *head;
    if (temp->next != NULL)
    {
        temp->next->prev = NULL;
    }
    
    (*head) = temp->next;
    free(temp);
}
void d_delete_element(DNode **head, int data)
{
    if (*head == NULL)
    {
        return;
    }
    if ((*head)->data == data)
    {
        d_delete_start(head);
        return;
    }
    DNode *temp = *head;
    while (temp->next != NULL && temp->next->data != data)
    {
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        printf("Element not found\n");
        return;
    }
    if (temp->next->next == NULL)
    {
        d_delete_end(head);
        return;
    }
    DNode *ptr = temp->next;
    ptr->next->prev = temp;
    temp->next = ptr->next;
    free(ptr);
}

// Search
void d_search(DNode **head, int data);

// Display
void d_print_list(DNode *head)
{
    if (head == NULL)
    {
        printf("Empty List\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Reverse
void d_reverse(DNode **head);
