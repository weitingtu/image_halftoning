#pragma once
#include "stdio.h"
#include "malloc.h"
#include "memory.h"
#include "math.h"
#include "bmp.h"        //  Simple .bmp library

#define max(x,y)  ( x>y?x:y )
#define min(x,y)  ( x<y?x:y )

void dither(int n, char* file_path, char* save_path);

void inverse(int n, char* file_path, char* save_path);
