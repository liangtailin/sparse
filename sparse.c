
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
    ele *ele_nz;
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

#define ele_nz(a) ((a).ele_nz)
#define index(a) ((a).col_index)
#define offset(a) ((a).offset)

#define col(a) ((a).pos.col)
#define col(a) ((a).pos.col)

//functions

// bool add_el(spa_mat *m, ele e)
// {
//     unsigned long int num_nzd = 0;
//     int max_row;
//     if (val(e) != 0)
//     {
//         ele_nz(*m)[num_nzd] = e;
//         index(*m)[num_nzd] = e.p.col;
//         if (e.p.row < max_row)
//             offset(*m)[num_nzd] = e.p.row;
//         else
//             offset(*m)
//     }
//     else
//     {
//         return false;
//     }
// }

static unsigned long compress(spa_mat *m, double vals[],unsigned long num_val)
{
    unsigned long row_dens[height_sparse(m)];
    unsigned long compressed_len, max_offset;
    int i, row;
    unsigned long num_nzd = 0;
    for (int i = 0; i < num_val; i++)
    {
        if (vals[i] != 0)
        {
            ele_nz(*m)[num_nzd].val = vals[i];
            index(*m)[num_nzd] = e.p.col;
            if (e.p.row < max_row)
                offset(*m)[num_nzd] = e.p.row;
            else
                offset(*m)
        }
        else
            ;
    }

        compressed_len = 0;
    for (i = 0; i < 2 * nelem(m); i++)
    {
        vals[i] = zero(m);
        rows[i] = 0;
    }

    max_offset = 0;

    /* fills the row_dens vector with row indices by the order in which they
   * should be inserted in the compressed vectors */
    list_rows_by_density(m, row_dens);

    for (i = 0; i < height_sparse(m); i++)
    {
        row = row_dens[i];
        offsets[row - row(min(m))] = find_slot(m, vals, rows, compressed_len, row);
        max_offset = max_int(max_offset, offsets[row - row(min(m))]);
        compressed_len = max_offset + width_sparse(m);
    }

    return compressed_len;
}

void print_compress_sparse(spa_mat m)
{
    double vals[nelem(m) * 2];
    unsigned long rows[nelem(m) * 2];
    unsigned long offsets[height_sparse(m)];
    unsigned long compressed_len;
    unsigned long i;

    if (density_sparse(m) > 0.5)
    {
        printf("dense matrix\n");
        return;
    }

    compressed_len = compress(m, vals, rows, offsets);

    printf("value =");
    for (i = 0; i < compressed_len; i++)
        printf(" %.3f", vals[i]);
    printf("\n");

    printf("index =");
    for (i = 0; i < compressed_len; i++)
        printf(" %lu", rows[i]);
    printf("\n");

    printf("offset =");
    for (i = 0; i < height_sparse(m); i++)
        printf(" %lu", offsets[i]);
    printf("\n");
}