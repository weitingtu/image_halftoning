/* --------------------------------------------------------------------- */
/*  CSCI 3280, Introduction to Multimedia Systems                        */
/*  Spring 2018                                                          */
/*                                                                       */
/*  Assignment 01 Skeleton :    inverse.cpp                              */
/* --------------------------------------------------------------------- */

#define _USE_MATH_DEFINES
#include "utils.h"
#include <math.h>

//! NOTICE! ******** PUT ALL YOUR CODE INSIDE inverse() ********

void inverse( int n, char* file_path, char* save_path )
{
    printf( "Running Halftoning Inverse.\n" );

    if ( ( n % 2 ) == 0 )
    {
        printf( "error: n %d is even\n", n );
        return;
    }

    double** gaunssian_filter = ( double** )malloc( sizeof( double* ) * n );
    for ( int i = 0; i < n; ++i )
    {
        gaunssian_filter[i] = ( double* )malloc( sizeof( double ) * n );
    }

    {
        int origin_x = n / 2;
        int origin_y = n / 2;
        double sigma = n / 4;
        double coef  = 1 / ( 2 * sigma * sigma * M_PI );
        for ( int row = 0; row < n; ++row )
        {
            for ( int column = 0; column < n; ++column )
            {
                double x = abs( column - origin_x );
                double y = abs( row - origin_y );
                gaunssian_filter[row][column] = coef * exp( -( ( x * x + y * y ) / ( 2 * sigma * sigma ) ) );
            }
        }
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
            for ( int row = 0; row < n; ++row )
            {
                for ( int column = 0; column < n; ++column )
                {
                    unsigned char gf_r = 255;
                    unsigned char gf_g = 255;
                    unsigned char gf_b = 255;
                    int gf_x = x - n / 2 + column;
                    int gf_y = y - n / 2 + row;
                    if ( gf_x >= 0 && gf_x < bmp.getWidth() && gf_y >= 0 && gf_y < bmp.getHeight() )
                    {
                        bmp.getColor( gf_x, gf_y, gf_r, gf_g, gf_b );
                    }
                    r += ( unsigned char )( gf_r * gaunssian_filter[row][column] );
                    g += ( unsigned char )( gf_g * gaunssian_filter[row][column] );
                    b += ( unsigned char )( gf_b * gaunssian_filter[row][column] );
                }
            }
            bmp.setColor( x, y, r, g, b );
        }
    }
    bmp.save( save_path );

    for ( int i = 0; i < n; ++i )
    {
        free ( gaunssian_filter[i] );
        gaunssian_filter[i] = NULL;
    }
    free( gaunssian_filter );
    gaunssian_filter = NULL;
}
