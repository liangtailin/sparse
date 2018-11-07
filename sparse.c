
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// #include "sparse.h"
/*
 * input: ptr to sparse, element to add
 *
 * adds a new element to the matrix
 *
 * if the value is 'zero', removes the value in that position
 * if the position has a value, replace it.
 * 
 * Return codes:
 *   true: Successful operation
 *   false: Space limit reached
 */

typedef struct position
{
    unsigned long int col, row;
} pos;

typedef struct element
{
    float val;
    pos p;
} ele;

typedef struct sparse_matrix
{
    ele *list;
    unsigned long int *col_index;
    unsigned long int *offset;
    unsigned long int num_nzd;          //num of elements
    unsigned long int num_row, num_row; //max of col
} spa_mat;

// selectors

#define zero(a) ((a).zero)

// functions

bool add_el(spa_mat *m, ele e);

// void print_spa_mat(spa_mat m);

// void print_charact_spa_mat(spa_mat m);

// void change_zero(spa_mat *m, double new_zero);

// void print_row_i(spa_mat m, unsigned long row_i);

// void print_col_j(spa_mat m, unsigned long col_j);

// void print_all_over_diag(spa_mat m);

// void print_n_diff_vals(spa_mat m);

#define val(a) (a.val)

#define list(a) ((a).list)
#define index(a) ((a).col_index)
#define offset(a) (a.offset)

//functions

bool add_el(spa_mat *m, ele e)
{
    unsigned long int num_nzd = 0;
    if (val(e) != 0)
    {
        list(*m)[num_nzd] = e;
        index(*m)[num_nzd] = e.p.col;
        if (e.p.row < max_row_last)
            offset(*m) = ;
    }
    else
    {
        return false;
    }
}
