#ifndef BITVECTOR_H
#define BITVECTOR_H

typedef struct _bit_vector
{
    int nBits;
    char* ptr;
    int ptrLen;
    int nElem;
} bit_vector_t;

bit_vector_t* bv_create(int len, int nbits);
void bv_set(bit_vector_t* bm, int pos, int val);
void bv_set2(bit_vector_t* bm, int pos, int val);
void bv_set4(bit_vector_t* bm, int pos, int val);
int bv_get(bit_vector_t* bm, int pos);
void bv_free(bit_vector_t* bm);

#endif

