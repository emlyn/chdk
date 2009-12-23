#include <stdlib.h>
/* various test cases for callfunc.S, not built or used by default */
int test_callfunc4(char *dest, int n_args, int a1, int a2)
{
	sprintf(dest,"%d %d %d",n_args, a1, a2);
	return n_args;
}

int test_callfunc5(char *dest, int n_args, int a1, int a2, int a3)
{
	sprintf(dest,"%d %d %d %d",n_args, a1, a2, a3);
	return n_args;
}

int test_callfunc8(char *dest, int n_args, int a1, int a2, int a3, int a4, int a5, int a6)
{
	sprintf(dest,"%d %d %d %d %d %d %d",n_args, a1, a2, a3, a4, a5, a6);
	return n_args;
}

int test_callfunc8v(char *dest, int n_args, int a1, int a2, int a3, int a4, int a5, int a6,...)
{
	sprintf(dest,"%d %d %d %d %d %d %d",n_args, a1, a2, a3, a4, a5, a6);
	return n_args;
}

int test_callfunc_va(char *dest, int n_args, ...)
{
	char *p=dest;
	int i;
    __builtin_va_list va;
    __builtin_va_start(va, n_args);
	for( i=0; i<n_args; i++) {
		p+=sprintf(p,"%d ",__builtin_va_arg(va,int));
	}
    __builtin_va_end(va);
	return n_args;
}

int test_ptrs[]={
	(int)test_callfunc4,
	(int)test_callfunc5,
	(int)test_callfunc8,
	(int)test_callfunc_va,
};
