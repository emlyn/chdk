#include <stdlib.h>
#include <stdio.h>
 
void usage()
{
    printf("Usage: hexdmplt <input_file> <output_file>\n");
    exit(1);
}
 
int main(int argc, char **argv)
{
    FILE *fi, *fo;
    unsigned int data;
    int n=0;
 
    if (argc != 3) {
        printf("ERROR: Incorrect number of arguments.\n");
        usage();
    }
 
    fi = fopen(argv[1], "rb");
    if (fi == NULL) {
        printf("ERROR: Cannot open input file '%s'.\n", argv[1]);
        usage();
    }
 
    fo = fopen(argv[2], "wb");
    if (fo == NULL) {
        fclose(fi);
        printf("ERROR: Cannot open ouput file '%s'.\n", argv[2]);
        usage();
    }
 
    while (!feof(fi) && fread(&data, 4, 1, fi)) {
        fprintf(fo, "0x%08x,%c", data, (!((++n)&3))?'\n':' ');
    }
    if ((n&3)) {
        fputc('\n', fo);
    }
 
    fclose(fi);
    fclose(fo);
 
    return 0;
}
