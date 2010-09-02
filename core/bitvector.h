#ifndef BITVECTOR_H
#define BITVECTOR_H

typedef struct _bit_vector
{
    int nBits;
    unsigned char* ptr;
    int ptrLen;
    int nElem;
} bit_vector_t;

bit_vector_t* bv_create(int len, int nbits);
void bv_set(const bit_vector_t* bm, int pos, int val);
void bv_set2(const bit_vector_t* bm, int pos, int val);
void bv_set4(const bit_vector_t* bm, int pos, int val);
int bv_get(const bit_vector_t* bm, int pos) __attribute__((pure));
void bv_free(bit_vector_t* bm);

#endif

