#define LONG_MAX     2147483647L

//-------------------------------------------------------------------
static long int quotient  = LONG_MAX / 16807L;
static long int remainder = LONG_MAX % 16807L;

static long int seed_val = 1L;

//-------------------------------------------------------------------
long rand_set_seed(long int sd) {
    return seed_val = sd;
}

//-------------------------------------------------------------------
long rand_get_seed() {
    return seed_val;
}

//-------------------------------------------------------------------
unsigned long int rand() {
    if ( seed_val <= quotient )
        seed_val = (seed_val * 16807L) % LONG_MAX;
    else {
        long int high_part = seed_val / quotient;
        long int low_part  = seed_val % quotient;

        long int test = 16807L * low_part - remainder * high_part;

        if ( test > 0 )
            seed_val = test;
        else
            seed_val = test + LONG_MAX;
    }

    return seed_val;
}

//-------------------------------------------------------------------
