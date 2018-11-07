#ifndef SPARSE_H
#define SPARSE_H

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
    unsigned long int num; //num of elements
    pos min, max;          //max of col or
} spa_mat;

// selectors

#define zero(a) ((a).zero)

// functions

bool add_el(spa_mat *m, ele e);

void print_spa_mat(spa_mat m);

void print_charact_spa_mat(spa_mat m);

void change_zero(spa_mat *m, double new_zero);

void print_row_i(spa_mat m, unsigned long row_i);

void print_col_j(spa_mat m, unsigned long col_j);

void print_all_over_diag(spa_mat m);

void print_n_diff_vals(spa_mat m);

#endif