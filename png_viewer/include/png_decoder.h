#include <stdio.h>
#include <stdint.h>
#include "collections.h"

#define ZLIB_BUFF_SIZE 16 * 1024
int decode(const char* filepath, unsigned char **out_data, uint32_t *out_data_len, uint32_t *out_width, uint32_t *out_height);
static int _read_chunk(FILE *file, unsigned char **out_data, unsigned char **out_type, uint32_t *out_len);
static uint32_t _convert_endianness_uint32(unsigned char *bytes);
static int _process_chunks(FILE *file, list_t **chunks_data, list_t **chunks_type, list_t **chunks_len,
 list_t **out_list, uint32_t *width, uint32_t *height);
static int _process_IHDR(FILE *file, list_t **chunks_data, uint32_t *out_width, uint32_t *out_height);
static int _process_IDAT(FILE *file, list_t **chunks_data, list_t **chunks_len, list_t **chunks_type, list_t **out_data);
static int _reconstruct_pixel_data(list_t **compressed_data, uint32_t width, uint32_t height, unsigned char **out_data, uint32_t *out_data_len);
static unsigned char _paeth_predictor(unsigned char a, unsigned char b, unsigned char c);
static unsigned char _recon_a(unsigned char *reconstructed_data, int r, int c, int stride);
static unsigned char _recon_b(unsigned char *reconstructed_data, int r, int c, int stride);
static unsigned char _recon_c(unsigned char *reconstructed_data, int r, int c, int stride);
