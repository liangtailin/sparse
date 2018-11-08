#ifndef SPARSE_H
#define SPARSE_H

typedef unsigned long index_t;
typedef unsigned long offset_t;
typedef unsigned long count_t;
typedef unsigned long pos_t;
typedef float val_t;

typedef struct position
{
    pos_t col;
    pos_t row;
} pos;

typedef struct element
{
    val_t val;
    pos p;
} ele;

typedef struct sparse_matrix
{
    val_t *val;
    index_t *col_index;
    offset_t *offset;
    count_t num_nzd, num_zd;        //num of elements
    count_t num_col, num_row;       //shape
} spa_mat;


//functions
bool add_el(spa_mat *m, ele e);
void put_into_ele(val_t *a, count_t max_row, count_t max_col, ele *e);
void compress(ele *e, count_t max_row, count_t max_col, spa_mat *m);
void decompress(spa_mat *m, ele *e);
void print_compress_sparse(spa_mat *m);

#endif