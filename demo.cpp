#include "stdio.h"
#include "utils.h"
#include "stdlib.h"
#include "string.h"

/* -------------------- CALL YOUR FUNCTIONS IN main() -------------------- */

int main( int argc, char** argv )
{
    if (argc != 6)
    {
        printf("USAGE: %s -dither/-reverse -n [size] [src.bmp] [result.bmp.", argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "-dither") == 0)
    {
        int n = atoi(argv[3]);
        dither(n, argv[4], argv[5]);
        printf("Completed!\n");
    }
    else if (strcmp(argv[1], "-inverse") == 0)
    {
        int n = atoi(argv[3]);
        inverse(n, argv[4], argv[5]);
        printf("Completed!\n");
    }
    else
    {
        printf("Unidentifiable arguments!\n");
        printf("USAGE: %s -dither/-reverse -n [size] [src.bmp] [result.bmp.", argv[0]);
        return 0;
    }
}
