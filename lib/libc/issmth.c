#include "stdlib.h"

int isdigit(int c)
{
    return (c>='0') && (c<='9');
}

int isspace(int c)
{
    if ((c >= '\t') && (c <= '\r')) return 1;
    if (c == ' ')  return 1;
    return 0;
}

int isalpha(int c)
{
    return (c>='A' && c<='Z') || (c>='a' && c<='z');
}

int isupper(int c)
{
    return (c>='A' && c<='Z');
}

