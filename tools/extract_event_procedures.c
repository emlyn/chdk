
#include <stdio.h>



#define DUMP_SIZE 0x400000

#define HOST_ADDR(addr) ((addr)-baseaddr+dump)

#define PEEKW(addr)  (*(int*)HOST_ADDR(addr))

#define ADDR(idx) (baseaddr+(idx))

#define IS_METHOD(addr) (addr > baseaddr && addr < baseaddr+DUMP_SIZE && PEEKW(addr) != 0 && isString(HOST_ADDR(addr)) < 4)

//#define MATCH_FOUND(s, addr) printf("STUB(0x%x, %s)\n", addr, s)


#define MATCH_POSTFIX() printf("};\n") 
#define MATCH_PREFIX() printf("#include <idc.idc>\nstatic main(){\n") 

#define MATCH_FOUND(s, addr) printf("MakeNameEx(0x%x, \"%s\", SN_PUBLIC);\n", addr, s) 

//#define DEBUG printf
#define DEBUG(...)


int isIdentifies(char *str) {

    char * start = str;
    
    while (*str >= 'a' && *str <= 'z' || *str >= 'A' && *str <= 'Z' || *str == '_')
    {
        str++;
        if (str - start > 50) return 0;
        if (*str == 0) return (str-start);
    }

    return 0;

}

int isString(char *str) {

    char * start = str;
    
    while (*str >= 0x20 && *str < 0x7F || *str == 0x0A)
    {
        str++;
        if (str - start > 500) return 0;
        if (*str == 0) return (str-start);
    }

    return 0;

}

int main(int argc, char**argv){

	int baseaddr;

	if (argc < 2) {
		printf("usage: <input dump file> <base address>\n");
		return 1;
	}

	sscanf(argv[2], "%x", &baseaddr);

	FILE *fd = fopen(argv[1], "r");
	fseek(fd, 0, SEEK_SET);

	char *dump = malloc(DUMP_SIZE);

	fread(dump, 1, DUMP_SIZE, fd);

	
	// Search for strings
	int sidx;
	for(sidx = 0; sidx < DUMP_SIZE; sidx +=1) {

	    int idlen = isIdentifies(dump+sidx);
	    
	    if ( idlen <= 3) {
                sidx += idlen;
	        continue;
	    }
	    
	    DEBUG("Searching for: %08x : %s\n", ADDR(sidx), HOST_ADDR(ADDR(sidx)));

	    int tidx;
	    for(tidx = 0; tidx < DUMP_SIZE; tidx +=4) {
	        
	        if (PEEKW(ADDR(tidx)) == ADDR(sidx)) {
	        
                    DEBUG("Found ref:%x\n", baseaddr+tidx);
                    // Trying method address as the next entry in a table:
                    if ( IS_METHOD(PEEKW(ADDR(tidx+4)))  ) {
                        MATCH_FOUND(dump+sidx, PEEKW(ADDR(tidx+4)) );
                    }
                }

	    }

            
            sidx += idlen;
	}


	free(dump);
	fclose(fd);

}
