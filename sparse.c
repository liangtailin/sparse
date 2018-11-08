
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sparse.h"

/* for sparse mat */

#define index(a) ((a).col_index)
#define offset(a) ((a).offset)

/* for ele */
#define val(a) ((a).val)
#define col(a) ((a).p.col)
#define row(a) ((a).p.row)

void put_into_ele(val_t *a, count_t max_row, count_t max_col, ele *e)
{
    count_t k = 0;
    for (count_t i = 0; i < max_row; i++)
    {
        for (count_t j = 0; j < max_col; j++)
        {
            col(e[k]) = j;
            row(e[k]) = i;
            val(e[k]) = a[k];
            printf("%f\t", val(e[k]));
            k += 1;
        }
    }
}

void compress(ele *e, size_t max_row, size_t max_col, spa_mat *m)
{
    size_t num_nz = 0, num_z = 0;
    size_t ofst = 0;
    size_t last_nzd = 0;

    /* put into CSR */
    for (int i = 0; i < max_row * max_col; i++)
    {
        if (val(e[i]) != 0)
        {

            if (row(e[i]) > row(e[last_nzd]) || !num_nz && !last_nzd)
            {
                offset(*m)[ofst] = num_nz;
                ofst += 1;
            }
            val(*m)[num_nz] = val(e[i]);
            index(*m)[num_nz] = col(e[i]);
            num_nz += 1;
            last_nzd = i;
        }
        else
            num_z += 1;
    }
    //finish offset val
    offset(*m)[ofst] = num_nz;
    m->num_zd = num_z;
    m->num_nzd = num_nz;
    m->num_row = max_row;
    m->num_col = max_col;
    printf("nzd = %ld, zd = %ld\n", num_nz, num_z);
}

void decompress(spa_mat *m, size_t max_row, size_t max_col, ele *e)
{
    int k = 0;
    int row = 0;
    for (int i = 0; i < max_col * max_row; i++)
    {
        for (int j = 0; j < offset(*m)[k]; j++)
        {
            val(e[i]) = val(*m)[i];
            col(e[i]) = index(*m)[i];
            row(e[i]) = row;
        }
        row++;

        // else val(e[i]) = 0;
    }
}

void print_compress_sparse(spa_mat *m)
{
    printf("\nvalue =");
    for (unsigned long i = 0; i < m->num_nzd; i++)
        printf(" %f", val(*m)[i]);
    printf("\n");

    printf("index =");
    for (unsigned long i = 0; i < m->num_nzd; i++)
        printf(" %lu", index(*m)[i]);
    printf("\n");

    printf("ofset =");
    for (unsigned long i = 0; i < m->num_row + 1; i++)
        printf(" %lu", offset(*m)[i]);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    float a[] = {
        1, 7, 0, 0, 0, 0,
        0, 2, 8, 0, 0, 5,
        5, 0, 3, 9, 0, 6,
        0, 6, 0, 4, 0, 0,
        0, 0, 0, 0, 1, 1,
        1, 0, 1, 0, 0, 0};
    float b[] = {
        1, 7, 0, 0,
        0, 2, 8, 0,
        5, 0, 3, 9,
        0, 6, 0, 4};
    // number of ele
    size_t max_row = 6, max_col = 6;
    // size_t max_row = 4, max_col = 4;

    ele *ele_test = calloc(max_row * max_col, sizeof(ele));

    //ele,index -> num of ele; offset -> number of row
    spa_mat spmat_test = {};
    spmat_test.val = calloc(max_row * max_col, sizeof(val_t));
    spmat_test.col_index = calloc(max_row * max_col, sizeof(index_t));
    spmat_test.offset = calloc(max_row + 1, sizeof(offset_t));

    put_into_ele(a, max_row, max_col, ele_test);
    // put_into_ele(b, max_row, max_col, ele_test);

    compress(ele_test, max_row, max_col, &spmat_test);
    free(ele_test);
    // printf("%f\t", spmat_test.ele_nz[0].val);
    print_compress_sparse(&spmat_test);
    return 0;
}
