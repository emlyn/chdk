#include "bitvector.h"
#include <stddef.h>
#include <stdlib.h>

bit_vector_t* bv_create(int len, int nbits)
{
    bit_vector_t* bm = (bit_vector_t*)malloc(sizeof(bit_vector_t));
    if (bm == NULL)
        return NULL;

    bm->ptrLen = len * nbits / 8 + 1;
    bm->nElem = len;
    bm->nBits = nbits;
    bm->ptr = malloc(bm->ptrLen);
    if (bm->ptr == NULL)
    {
        free(bm);
        return NULL;
    }

    return bm;
}

// Utility function. Use bv_set instead.
static inline void bv_setbit(bit_vector_t* bm, int pos, int val)
{
    int bp = pos - ((pos >> 3) << 3);
    if (val == 0)
        bm->ptr[pos >> 3] &= ~(1 << bp);
    else
        bm->ptr[pos >> 3] |=  (1 << bp);

// Following ASM code is bad. It crashes the camera, but why?
// It'd be very nice to replace this function with an inline
// assembly macro in the future (the same for bv_getbit()).
// The compiler seems to generate suboptimal ASM for me,
// but this is performance critical code.
//
//    char t = bm->ptr[pos >> 3];
//    asm volatile (
//                 ".syntax unified\n"
//                 "MOV     %[pos], %[pos], lsr #3\n"           // r1 = pos >> 3
//                 "SUB     %[pos], %[pos], %[pos], lsl #3\n"        // pos -= pos<<3
//                 "MOV     r2, #1\n"                    // r2 = 1
//                 "MOV     r2, r2, lsl %[pos]\n"         // r2 <<= pos
//                 "CMP     %[val], #0\n"                    // val == 0
//                 "ITE     EQ\n"                             // if
//                 "BICEQ     %[t], %[t], r2\n"        // &= ~(1 << bp)
//                 "ORRNE     %[t], %[t], r2\n"      // |=  (1 << bp)
//                 ".syntax divided"
//                 : [t]"+r"(t)
//                 : [val]"r"(val), [pos]"r"(pos)
//                 : "r2", "cc"
//                 );
//    bm->ptr[pos >> 3] = t;

}

// Utility function. Use bv_get instead.
static inline int bv_getbit(bit_vector_t* bm, int pos)
{
    // Note: bv_get() and other code rely on this
    // method returning '1' if the bit is set.
    // If you are interested only in the truth value,
    // you can use bv_testbit().

    int bp = pos - ((pos >> 3) << 3);
    return ((bm->ptr[pos >> 3] & (1 << bp)) > 0) ? 1 : 0;
}

void bv_set(bit_vector_t* bm, int pos, int val)
{
    int i;
    int bitpos = pos * bm->nBits;
    for (i = 0; i < bm->nBits; ++i)
    {
        bv_setbit(bm, bitpos + i, val & (1<<i));
    }
}

// Same as bv_set, but sets val to two consecutive elements
// instead of just one.
void bv_set2(bit_vector_t* bm, int pos, int val)
{
    int i;
    int bitpos = pos * bm->nBits;
    for (i = 0; i < bm->nBits; ++i)
    {
        int t = val & (1<<i);
        bv_setbit(bm, bitpos + i, t);
        bv_setbit(bm, bitpos + i + bm->nBits, t);
    }
}

// Same as bv_set, but sets val to four consecutive elements
// instead of just one.
void bv_set4(bit_vector_t* bm, int pos, int val)
{
    int i;
    int bitpos = pos * bm->nBits;
    for (i = 0; i < bm->nBits; ++i)
    {
        int t = val & (1 << i);
        bv_setbit(bm, bitpos + i, t);
        bv_setbit(bm, bitpos + i + bm->nBits, t);
        bv_setbit(bm, bitpos + i + bm->nBits * 2, t);
        bv_setbit(bm, bitpos + i + bm->nBits * 3, t);
    }
}

int bv_get(bit_vector_t* bm, int pos)
{
    int i;
    int ret = 0;
    int bitpos = pos * bm->nBits;
    for (i = 0; i < bm->nBits; ++i)
    {
        ret |= (bv_getbit(bm, bitpos + i) << i);
    }

    return ret;
}


void bv_free(bit_vector_t* bm)
{
    if (bm)
    {
        if (bm->ptr)
        {
            free(bm->ptr);
            bm->ptr = NULL;
        }

        free(bm);
    }
}

/*
// Utility function. Not sure what for, but might
// be useful in the future.
static int bv_testbit(bit_vector_t* bm, int pos)
{
    int bp = pos - ((pos >> 3) << 3);
    return bm->ptr[pos >> 3] & (1 << bp);
}


// This method is designed to be used for blitting the contents of the
// bit_vector into the framebuffer. The value of each element is used to
// look up a color value based on the lookup-table (last parameter).
// Not used currently. Never will be probably.
static void bv_expand(bit_vector_t* bm, unsigned char* dst, int len, color* lookup)
{
    int i;
    int k;

    for (i = 0; i < len; ++i)
    {
        int elem = 0;
        int bitpos = i * bm->nBits;
        for (k = 0; k < bm->nBits; ++k)
        {
            int pos = bitpos + k;
            int bp = pos - ((pos >> 3) << 3);
            if (bm->ptr[pos >> 3] & (1 << bp))
                elem |= (1 << k);
        }
        dst[i] = lookup[elem];
        dst[i+screen_buffer_size] = lookup[elem];
    }
}
*/
