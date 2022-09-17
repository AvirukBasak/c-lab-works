/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   C program to add two polynomials using singly linked lists
 * @date    7-9-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct termnode {
    int coeff;
    int exp;
    struct termnode *next;
} *termnode;

termnode poly_newterm(int coeff, int exp);
termnode poly_add(termnode head1, termnode head2);
void poly_print(termnode head);
void poly_free(termnode *head);

termnode poly_newterm(int coeff, int exp)
{
    termnode node = malloc(sizeof(struct termnode));
    if (!node) abort();
    node->coeff = coeff;
    node->exp = exp;
    node->next = NULL;
    return node;
}

termnode poly_add(termnode head1, termnode head2)
{
    if (!head1) abort();
    if (!head2) abort();
    termnode head3 = poly_newterm(0,0);
    termnode p1 = head1->next,
             p2 = head2->next,
             p3 = head3;
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            p3->next = poly_newterm(p1->coeff, p1->exp);
            p3 = p3->next;
            p1 = p1->next;
        } else if (p2->exp > p1->exp) {
            p3->next = poly_newterm(p2->coeff, p2->exp);
            p3 = p3->next;
            p2 = p2->next;
        } else {
            p3->next = poly_newterm(p1->coeff + p2->coeff, p1->exp);
            p3 = p3->next;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1 != NULL) {
        p3->next = poly_newterm(p1->coeff, p1->exp);
        p3 = p3->next;
        p1 = p1->next;
    }
    while (p2 != NULL) {
        p3->next = poly_newterm(p2->coeff, p2->exp);
        p3 = p3->next;
        p2 = p2->next;
    }
    return head3;
}

void poly_print(termnode head)
{
    if (!head) abort();
    termnode p = head->next;
    while (p != NULL) {
        printf("%d (x^%d)%s", p->coeff, p->exp, p->next ? " + " : "");
        p = p->next;
    }
    printf("\n");
}

void poly_free(termnode *head)
{
    if (!*head) return;
    termnode p = *head;
    while (p != NULL) {
        termnode tmp = p->next;
        free(p);
        p = tmp;
    }
    *head = NULL;
}

int main()
{
    // first polunomial
    printf("polynomial 1, coeff = 0 to accept:\n");
    termnode polyhead1 = poly_newterm(0,0);
    termnode ptr1 = polyhead1;
    do {
        int coeff, exp;
        printf("    enter coeff and exp: ");
        scanf("%d", &coeff);
        scanf("%d", &exp);
        if (!coeff) break;
        termnode node = poly_newterm(coeff, exp);
        ptr1->next = node;
        ptr1 = node;
    } while(true);

    // second polynomial
    printf("\npolynomial 2, coeff = 0 to accept:\n");
    termnode polyhead2 = poly_newterm(0,0);
    termnode ptr2 = polyhead2;
    do {
        int coeff, exp;
        printf("    enter coeff and exp: ");
        scanf("%d", &coeff);
        scanf("%d", &exp);
        if (!coeff) break;
        termnode node = poly_newterm(coeff, exp);
        ptr2->next = node;
        ptr2 = node;
    } while(true);

    printf("\npoly1 = ");
    poly_print(polyhead1);

    printf("\npoly2 = ");
    poly_print(polyhead2);

    termnode result = poly_add(polyhead1, polyhead2);

    poly_free(&polyhead1);
    poly_free(&polyhead2);

    printf("\nresult = ");
    poly_print(result);
    poly_free(&result);
    return 0;
}

/* OUTPUT:

polynomial 1, coeff = 0 to accept:
    enter coeff and exp: 12 9
    enter coeff and exp: 234 5
    enter coeff and exp: 32 4
    enter coeff and exp: 12 2
    enter coeff and exp: 6 1
    enter coeff and exp: 7 0
    enter coeff and exp: 0 1

polynomial 2, coeff = 0 to accept:
    enter coeff and exp: 23 9
    enter coeff and exp: 23 7
    enter coeff and exp: 12 4
    enter coeff and exp: 89 2
    enter coeff and exp: 1 1
    enter coeff and exp: 0 0

poly1 = 12 (x^9) + 234 (x^5) + 32 (x^4) + 12 (x^2) + 6 (x^1) + 7 (x^0)

poly2 = 23 (x^9) + 23 (x^7) + 12 (x^4) + 89 (x^2) + 1 (x^1)

result = 35 (x^9) + 23 (x^7) + 234 (x^5) + 44 (x^4) + 101 (x^2) + 7 (x^1) + 7 (x^0)

*/
