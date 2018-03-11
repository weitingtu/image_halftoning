/* --------------------------------------------------------------------- */
/*  CSCI 3280, Introduction to Multimedia Systems                        */
/*  Spring 2018                                                          */
/*                                                                       */
/*  Assignment 01 Skeleton :    dither.cpp                               */
/* --------------------------------------------------------------------- */

#include "utils.h"

//! NOTICE! ******** PUT ALL YOUR CODE INSIDE dither() ********

void dither( int n, char* file_path, char* save_path )
{
    printf( "Running Order Dithering.\n" );

    int x_pos = n / 2;
    int y_pos = n / 2;
    if ( n % 2 == 0 )
    {
        --y_pos;
    }

    char** screening_matrix = ( char** )malloc( sizeof( char* ) * n );
    for ( int i = 0; i < n; ++i )
    {
        screening_matrix[i] = ( char* )malloc( sizeof( char ) * n );
    }

    int x_dir  = -1;
    int y_dir  = 1;
    int x_step = 1;
    int y_step = 1;
    int size = n * n;

    int* seq = ( int* ) malloc( sizeof( int ) * size );
    {
        int index = 0;
        for ( int i = 1; i <= size; i += 2 )
        {
            seq[index++] = i;
        }
        for ( int i = 2; i <= size; i += 2 )
        {
            seq[index++] = i;
        }
        if ( index != size )
        {
            printf( "seq size mismatch %zu %d", index, size );
            return;
        }
    }

    int index = 0;
    screening_matrix[x_pos][y_pos] = seq[index++];
    while ( index < size )
    {
        int y_count = abs( y_dir * y_step );
        y_count = min( y_count, size - index );
        while ( y_count > 0 )
        {
            --y_count;
            y_pos += y_dir > 0 ? 1 : -1;
            screening_matrix[x_pos][y_pos] = seq[index++];
        }

        int x_count = abs( x_dir * x_step );
        x_count = min( x_count, size - index );
        while ( x_count > 0 )
        {
            --x_count;
            x_pos += x_dir > 0 ? 1 : -1;
            screening_matrix[x_pos][y_pos] = seq[index++];
        }

        x_dir *= -1;
        y_dir *= -1;
        ++x_step;
        ++y_step;
    }

    Bitmap bmp;
    if ( !bmp.create( file_path ) )
    {
        printf( "failed to open %s\n", file_path );
        return;
    }
    for ( int y = 0; y < bmp.getHeight(); ++y )
    {
        for ( int x = 0; x < bmp.getWidth(); ++x )
        {
            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
            bmp.getColor( x, y, r, g, b );
            r = ( ( double )r / 256 ) > ( double )screening_matrix[x % n][y % n] / ( size + 1 ) ? 255 : 0;
            g = ( ( double )g / 256 ) > ( double )screening_matrix[x % n][y % n] / ( size + 1 ) ? 255 : 0;
            b = ( ( double )b / 256 ) > ( double )screening_matrix[x % n][y % n] / ( size + 1 ) ? 255 : 0;
            bmp.setColor( x, y, r, g, b );
        }
    }
    bmp.save( save_path );

    for ( int i = 0; i < n; ++i )
    {
        free ( screening_matrix[i] );
        screening_matrix[i] = NULL;
    }
    free( screening_matrix );
    screening_matrix = NULL;

    free( seq );
    seq = NULL;
}
