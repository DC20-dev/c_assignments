#include "zlib.h"
#include "png_decoder.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

unsigned char* decode(const char* filepath)
{
    FILE *file = fopen(filepath, "rb");
    if(!file)
    {
        return NULL;
    }
    // get raw file length, remove if not needed
    if(fseek(file, 0, SEEK_END))
    {
        fclose(file);
        return NULL;
    }
    const long filesize = ftell(file);
    //
    const unsigned char png_signature[9] = "\x89PNG\r\n\x1a\n";
    const int signature_len = strlen((const char*)png_signature);
    // allocates 8 bytes + 1 for string termination
    unsigned char file_signature[9];
    file_signature[signature_len] = 0;  // terminating the signature with 0 like a string

    // reset to start, remove if not getting length
    if(fseek(file, 0, SEEK_SET))
    {
        fclose(file);
        return NULL;
    }
    //
    int ret = fread(file_signature, 1, signature_len, file);
    if(ret != signature_len || strcmp((const char*)file_signature, (const char*)png_signature))
    {
        perror("Error while reading signature!");
        printf("signature is: %s\n, expected: %s", file_signature, png_signature);
        fclose(file);
        return NULL;
    }
    // ================ signature is valid, let's read the supported chunks ================

    list_t *chunks_data = list_new(10);
    list_t *chunks_type = list_new(10);
    list_t *chunks_len = list_new(10);

    for(;;)
    {
        unsigned char *data;
        unsigned char *type;
        uint32_t len;
        _read_chunk(file, &data, &type, &len);
        list_append(&chunks_data, data, len);
        list_append(&chunks_type, type, 5);
        list_append(&chunks_len, &len, sizeof(uint32_t));

        if(!strcmp((const char*)type, "IEND"))
        {
            break;
        }
        // FREE READ INFO!!!!!
        free(data);
        free(type);
    }
    
    list_t *IDAT_data;
    _process_chunks(file, &chunks_data, &chunks_type, &chunks_len, &IDAT_data);

    for (size_t i = 0; i < list_len(IDAT_data); i++)
    {
        printf("%x ", TO_(unsigned char)list_get(&IDAT_data, i));
    }
    
    
    // close file before exiting
    fclose(file);
    // FREE MEMORY!!!!
    return NULL;
}

static int _read_chunk(FILE *file, unsigned char **out_data, unsigned char **out_type, uint32_t *out_len)
{
    // IMPORTANT! ASSUMING THAT THE FILE IS A VALID PNG
    unsigned char chunk_length_bytes[4];
    // BIG ENDIAN VALUE
    fread(chunk_length_bytes, 1, 4, file);
    const uint32_t chunk_length = _convert_endianness_uint32(chunk_length_bytes);

    unsigned char *chunk_type = malloc(5);
    fread(chunk_type, 1, 4, file);
    chunk_type[4] = 0;  // string termination

    unsigned char *chunk_data = calloc(chunk_length,1);
    if(chunk_length > 0)
    {
        fread(chunk_data, 1, chunk_length, file);
    }

    unsigned char chunk_crc_bytes[4];
    fread(chunk_crc_bytes, 1, 4, file);
    uint32_t expected_crc = _convert_endianness_uint32(chunk_crc_bytes);
    // calculate the crc from data now
    const unsigned int file_crc = crc32(
        crc32(0, (unsigned char*)chunk_type, 4),
        (unsigned char*)chunk_data,
        chunk_length);
    if(file_crc != expected_crc)
    {
        free(chunk_data);
        free(chunk_type);
        return -1;
    }
    *out_data = chunk_data;
    *out_type = chunk_type;
    *out_len = chunk_length;
    return 0;
}

static int _process_chunks(FILE *file, list_t **data, list_t **type, list_t **len, list_t **out_list)
{   // IHDR is always the first chunk
    uint32_t width, height;
    const int IHDR_Error = _process_IHDR(file, data, &width, &height);  // might fail, stop on error
    if(IHDR_Error)
    {
        printf("IHDR ERROR!\n");
        return -1;
    }
    //IDAT next
    const int IDAT_Error = _process_IDAT(file, data, len, type, out_list);
    if(IDAT_Error)
    {
        printf("IDAT ERROR!\n");
    }
    return 0;
}

static int _process_IHDR(FILE *file, list_t **data, uint32_t *out_width, uint32_t *out_height)
{
    unsigned char *IHDR_data = list_get(data, 0);

    unsigned char width_bytes[4];
    memcpy(width_bytes, IHDR_data, 4);  // copy first 4 bytes to width_bytes to correctly convert them
    const uint32_t width = _convert_endianness_uint32(width_bytes);
    unsigned char height_bytes[4];
    memcpy(height_bytes, IHDR_data + 4, 4);  // same as above
    const uint32_t height = _convert_endianness_uint32(height_bytes);
    const uint8_t bit_depth = IHDR_data[8];
    const uint8_t color_type = IHDR_data[9];
    const uint8_t compression_m = IHDR_data[10];
    const uint8_t filter_m = IHDR_data[11];
    const uint8_t interlace_m = IHDR_data[12];
    // FILTER UNSUPPORTED STUFF HERE AND EVENTUALLY STOP EXECUTION WITH ERROR

    *out_width = width;
    *out_height = height;
    return 0;
}

static int _process_IDAT(FILE *file, list_t **data, list_t **len, list_t **type, list_t **out_data)
{
    const size_t data_list_len = list_len(*data);
    list_t *pixel_data_bytes = list_new(100); // it is going to be big anyway
    for(size_t i = 1; i < data_list_len; i++)
    {
        unsigned char *current_type = list_get(type, i);
        if(!current_type)
        {
            return -1;
        }
        if(strcmp("IDAT", (const char*)current_type) != 0)
        {
            continue;
        }
        // get corresponding data
        unsigned char *IDAT_data = list_get(data, i);
        if(!IDAT_data)
        {
            return -1;
        }
        // get data length
        const uint32_t data_len = TO_(uint32_t)list_get(len, i);
        // append the single bytes to the out list
        // not using memcpy because I can't tell how many bytesiIt will 
        // contain and the list already takes care of reallocation when needed
        // also, it is easier to follow
        for (size_t j = 0; j < data_len; j++)
        {
            list_append(&pixel_data_bytes, &IDAT_data[j], 1);
        }
    }
    // pass out the resulting pixel data
    *out_data = pixel_data_bytes;
    return 0;
}

static uint32_t _convert_endianness_uint32(unsigned char *bytes)
{
    const uint32_t val = bytes[3] +
    (bytes[2] << 8) +
    (bytes[1] << 16) +
    (bytes[0] << 24);
    return val;
}

static uint32_t _bytes_to_uint32(unsigned char *bytes)
{
    const uint32_t val = bytes[0] +
    (bytes[1] << 8) +
    (bytes[2] << 16) +
    (bytes[3] << 24);
    return val;
}

static int _paeth_predictor()
{
    return 0;
}