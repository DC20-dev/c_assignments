#include <stdio.h>
#include <stdint.h>
#include "collections.h"

#define ZLIB_BUFF_SIZE 16 * 1024
unsigned char* decode(const char* filepath);
static int _read_chunk(FILE *file, unsigned char **out_data, unsigned char **out_type, uint32_t *out_len);
static uint32_t _convert_endianness_uint32(unsigned char *bytes);
static uint32_t _bytes_to_uint32(unsigned char *bytes);
static int _process_chunks(FILE *file, list_t **data, list_t **type, list_t **len, list_t **out_list);
static int _process_IHDR(FILE *file, list_t **data, uint32_t *out_width, uint32_t *out_height);
static int _process_IDAT(FILE *file, list_t **data, list_t **len, list_t **type, list_t **out_data);
