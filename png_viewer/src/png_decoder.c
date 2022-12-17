#include "zlib.h"
#include "png_decoder.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
// PNG decoder based off Pyokagan's implementation: https://pyokagan.name/blog/2019-10-14-png/
// It only supports 8 bit truecolor with alpha

// decodes a png file; supported formats are: rgba32
//
// returns 0 if the decoding process didn't encounter errors, other values if there was an error
int decode(const char* filepath, unsigned char **out_data, uint32_t *out_data_len, uint32_t *out_width, uint32_t *out_height)
{
    FILE *file = fopen(filepath, "rb");
    if(!file)
    {
        return -1;
    }
    const unsigned char png_signature[9] = "\x89PNG\r\n\x1a\n";
    const int signature_len = strlen((const char*)png_signature);
    // allocates 8 bytes + 1 for string termination
    unsigned char file_signature[9];
    file_signature[signature_len] = 0;  // terminating the signature with 0 like a string

    const int ret = fread(file_signature, 1, signature_len, file);
    if(ret != signature_len || strcmp((const char*)file_signature, (const char*)png_signature))
    {
        perror("Error while reading signature!");
        printf("signature is: %s\n, expected: %s", file_signature, png_signature);
        fclose(file);
        return -1;
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
    // ====================== data gathered, now let's process it ==========================
    
    uint32_t width;
    uint32_t height;
    list_t *IDAT_data;
    int exit_code = _process_chunks(file, &chunks_data, &chunks_type,
     &chunks_len, &IDAT_data, &width, &height);
    // FREE LISTS THAT ARE NO LONGER NEEDED
    list_delete(&chunks_data);
    list_delete(&chunks_type);
    list_delete(&chunks_len);
    // close file
    fclose(file);
    if(exit_code != 0)
    {
        return exit_code;
    }
    // ===== before using it, the pixel data has to be decompressed and reconstructed =========
    unsigned char *reconstructed_pixels;
    exit_code = _reconstruct_pixel_data(&IDAT_data, width, height, &reconstructed_pixels, out_data_len);
    list_delete(&IDAT_data);
    if(exit_code != 0)
    {
        return exit_code;
    }
    *out_data = reconstructed_pixels;
    *out_width = width;
    *out_height = height;
    return 0;
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
    const uint32_t expected_crc = _convert_endianness_uint32(chunk_crc_bytes);
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

static int _process_chunks(FILE *file, list_t **chunks_data, list_t **chunks_type,
 list_t **chunks_len, list_t **out_list, uint32_t *width, uint32_t *height)
{   // IHDR is always the first chunk
    const int IHDR_Error = _process_IHDR(file, chunks_data, width, height);  // might fail, stop on error
    if(IHDR_Error)
    {
        printf("IHDR ERROR!\n");
        return -1;
    }
    //IDAT next
    const int IDAT_Error = _process_IDAT(file, chunks_data, chunks_len, chunks_type, out_list);
    if(IDAT_Error)
    {
        printf("IDAT ERROR!\n");
    }
    return 0;
}

static int _process_IHDR(FILE *file, list_t **chunks_data, uint32_t *out_width, uint32_t *out_height)
{
    unsigned char *IHDR_data = list_get(chunks_data, 0);

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
    if(compression_m != 0)
    {
        return -1;
    }
    if(filter_m != 0)
    {
        return -1;
    }
    if(color_type != 6)
    {
        return -1;
    }
    if(bit_depth != 8)
    {
        return -1;
    }
    if(interlace_m != 0)
    {
        return -1;
    }
    // export data

    *out_width = width;
    *out_height = height;
    return 0;
}

static int _process_IDAT(FILE *file, list_t **chunks_data, list_t **chunks_len, list_t **chunks_type, list_t **out_data)
{
    const size_t data_list_len = list_len(*chunks_data);
    list_t *pixel_data_bytes = list_new(100); // it is going to be big anyway
    for(size_t i = 1; i < data_list_len; i++)
    {
        unsigned char *current_type = list_get(chunks_type, i);
        if(!current_type)
        {
            return -1;
        }
        if(strcmp("IDAT", (const char*)current_type) != 0)
        {
            continue;
        }
        // get corresponding data
        unsigned char *IDAT_data = list_get(chunks_data, i);
        if(!IDAT_data)
        {
            return -1;
        }
        // get data length
        const uint32_t data_len = TO_(uint32_t)list_get(chunks_len, i);
        // append the single bytes to the out list
        // not using malloc+memcpy because I can't tell how many bytes it will 
        // contain and the list already takes care of reallocation when needed
        // also, it is easier to follow and the first approach woul make things 
        // more complicated than what is required
        for (size_t j = 0; j < data_len; j++)
        {
            list_append(&pixel_data_bytes, &IDAT_data[j], 1);
        }
    }
    // pass out the resulting pixel data
    *out_data = pixel_data_bytes;
    return 0;
}

static int _reconstruct_pixel_data(list_t **compressed_data, uint32_t width, uint32_t height, unsigned char **out_data, uint32_t *out_data_len)
{
    // convert the byte list to a byte array first
    unsigned long comp_len = (unsigned long)list_len(*compressed_data);
    unsigned char *compressed_data_array = malloc(comp_len);
    if(!compressed_data_array)
    {
        return -1;
    }
    for (size_t i = 0; i < comp_len; i++)
    {
        compressed_data_array[i] = TO_(unsigned char)list_get(compressed_data, i); 
    }
    
    // every scanline has 4 bytes per pixel + 1 that tells the filtering type
    unsigned long uncompressed_data_length = height * (1 + width * 4);
    unsigned char *uncompressed_data = malloc(uncompressed_data_length);
    if(!uncompressed_data)
    {
        return -1;
    }
    uncompress2(uncompressed_data, &uncompressed_data_length, compressed_data_array, &comp_len);
    free(compressed_data_array);
    // ======================= data uncompressed, now let's process it =========================

    const int bytes_per_pixel = 4;
    const int stride = width * bytes_per_pixel;
    unsigned char *reconstructed_data = malloc(stride * height);

    int index = 0;
    int appended_count = 0;
    for (uint32_t r = 0; r < height; r++) // for each scanline
    {
        const unsigned char filter_type = uncompressed_data[index]; // first byte in scanline
        index++;
        for (int c = 0; c < stride; c++) // for each byte in scanline
        {
            const unsigned char filtered_x = uncompressed_data[index];
            index++;
            unsigned char reconstructed_x;
            if(filter_type == 0) // none
            {
                reconstructed_x = filtered_x;
            }
            else if(filter_type == 1) // sub
            {
                reconstructed_x = filtered_x + _recon_a(reconstructed_data, r, c, stride);
            }
            else if(filter_type == 2) // up
            {
                reconstructed_x = filtered_x + _recon_b(reconstructed_data, r, c, stride);
            }
            else if(filter_type == 3) // average
            {
                reconstructed_x = filtered_x + 
                (
                    (_recon_a(reconstructed_data, r, c, stride) +
                    _recon_b(reconstructed_data, r, c, stride)) / 2
                );
            }
            else if(filter_type == 4) // Paeth
            {
                reconstructed_x = filtered_x +
                _paeth_predictor(
                    _recon_a(reconstructed_data, r, c, stride),
                    _recon_b(reconstructed_data, r, c, stride),
                    _recon_c(reconstructed_data, r, c, stride)
                );
            }
            else
            {
                return -1;
            }
            reconstructed_data[appended_count] = reconstructed_x;
            appended_count++;
        }
    }
    // ============== data reconstructed, now it is ready to be passed out ======================
    
    free(uncompressed_data);
    *out_data = reconstructed_data;
    *out_data_len = stride * height;
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

// a is the byte corresponding to x in the pixel immediately before the pixel containing x
// (or zero if such pixel is out of bounds)
//
// b is the byte corresponding to x in the previous scanline 
// (or 0 if such a scanline is out of bounds of the image)
//
// c is the byte corresponding to b in the pixel immediately before the pixel containing b
// (or 0 if such a pixel is out of bounds of the image)
static unsigned char _paeth_predictor(unsigned char a, unsigned char b, unsigned char c)
{
    const unsigned char p = a + b - c;
    const unsigned char pa = abs(p-a);
    const unsigned char pb = abs(p-b);
    const unsigned char pc = abs(p-c);
    unsigned char pr;

    if(pa <= pb && pa <= pc)
    {
        pr = a;
    }
    else if (pb <= pc)
    {
        pr = b;
    }
    else
    {
        pr = c;
    }

    return pr;
}

// Sub pixel filtering type
static unsigned char _recon_a(unsigned char *reconstructed_data, int r, int c, int stride)
{
    unsigned char res;
    if(c >= 4)
    {
        return reconstructed_data[(unsigned int)r * (unsigned int)stride + (unsigned int)c - 4];
    }
    else
    {
        return 0;
    }
}

// Up pixel filtering type
static unsigned char _recon_b(unsigned char *reconstructed_data, int r, int c, int stride)
{
    unsigned char res;
    if(r > 0)
    {
        return reconstructed_data[((unsigned int)r-1) * (unsigned int)stride + (unsigned int)c];
    }
    else
    {
        return 0;
    }
}

// Average pixel filtering type
static unsigned char _recon_c(unsigned char *reconstructed_data, int r, int c, int stride)
{
    unsigned char res;
    if(r > 0 && c >= 4)
    {
        return reconstructed_data[((unsigned int)r-1) * (unsigned int)stride + (unsigned int)c - 4];
    }
    else
    {
        return 0;
    }
}