#include "png_decoder.h"

int main(int argc, char **argv)
{
    unsigned char *pixel_bytes;
    int exit_code = decode("assets/basn6a08.png", &pixel_bytes);
    return exit_code;
}