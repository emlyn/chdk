#ifndef DUMPUTIL_H
#define DUMPUTIL_H
#define MIN_DUMP_SIZE (1024*1024)
typedef struct {
	union {
		const uint8_t *pb;
		const uint32_t *pw;
	};
	size_t size;
	unsigned words;
	unsigned base;
} dump_t;
unsigned ptr_to_offset(dump_t *dump,unsigned ptr);
unsigned offset_to_ptr(dump_t *dump,unsigned off);
int find_cstring(dump_t *dump, unsigned *pos, const char *string);
int find_word_aligned(dump_t *dump, unsigned *index, uint32_t word);
uint32_t get_word(dump_t *dump,unsigned off);
uint32_t deref_word_ptr(dump_t *dump,unsigned off);
uint8_t deref_byte_ptr(dump_t *dump,unsigned off);
const char* deref_string_ptr(dump_t *dump,unsigned off);
int load_dump(const char *dumpname,const char *base, dump_t *dump);
#endif

