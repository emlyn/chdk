/* unwrappers for thumb functions                  */
/* this file SHOULD be compiled in native ARM mode */

extern int fselect_sort(const void* v1, const void* v2);
int fselect_sort_nothumb(const void* v1, const void* v2) {
    return fselect_sort(v1, v2);
}
