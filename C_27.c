#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

// Function to create a new term
struct Term* createTerm(int coefficient, int exponent) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    if (newTerm == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term at the end of a polynomial
void insertTerm(struct Term** poly, int coefficient, int exponent) {
    struct Term* newTerm = createTerm(coefficient, exponent);
    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        struct Term* current = *poly;
        while (current->next != NULL)
            current = current->next;
        current->next = newTerm;
    }
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coefficient + poly2->coefficient;
            if (sum != 0)
                insertTerm(&result, sum, poly1->exponent);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    // If there are remaining terms in either polynomial, add them to the result
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertTerm(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }
    return result;
}

// Function to display a polynomial
void displayPolynomial(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    while (poly != NULL) {
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    // Create first polynomial: 3x^3 + 4x^2 + 2x^1
    struct Term* poly1 = NULL;
    insertTerm(&poly1, 3, 3);
    insertTerm(&poly1, 4, 2);
    insertTerm(&poly1, 2, 1);
    printf("First polynomial: ");
    displayPolynomial(poly1);

    // Create second polynomial: 5x^4 + 2x^2 + 1x^0
    struct Term* poly2 = NULL;
    insertTerm(&poly2, 5, 4);
    insertTerm(&poly2, 2, 2);
    insertTerm(&poly2, 1, 0);
    printf("Second polynomial: ");
    displayPolynomial(poly2);

    // Add the two polynomials
    struct Term* sum = addPolynomials(poly1, poly2);
    printf("Sum of polynomials: ");
    displayPolynomial(sum);

    return 0;
}
27