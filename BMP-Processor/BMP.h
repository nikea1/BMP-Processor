//
//  BMP.h
//  BMP-Processor
//
//  Created by Adenike Adeyemi on 10/25/17.
//  Copyright © 2017 Adenike Adeyemi. All rights reserved.
//

#ifndef BMP_h
#define BMP_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char signiture[2];
    int fileSize;
    char reserved1;
    char reserved2;
    int imgOffset;
} BitmapFileHeader;

//bases on BITMAPINFOHEADER and up
typedef struct{
    int headerSize;
    int width;
    int height;
    unsigned char planes;
    unsigned char bpp;
    int compression;
    int imageSize;
    int horizontalRes;
    int verticalRes;
    int numColors;
    int numImportantColors;
} BITMAPINFOHEADER;

typedef struct{
    int headerSize;
    int width;
    int height;
    unsigned char planes;
    unsigned char bpp;
    int compression;
    int imageSize;
    int horizontalRes;
    int verticalRes;
    int numColors;
    int numImportantColors;
    int redMask;
    int greenMask;
    int blueMask;
} BITMAPV2INFOHEADER;

typedef struct{
    int headerSize;
    int width;
    int height;
    unsigned char planes;
    unsigned char bpp;
    int compression;
    int imageSize;
    int horizontalRes;
    int verticalRes;
    int numColors;
    int numImportantColors;
    int redMask;
    int greenMask;
    int blueMask;
    int alphaMask;
} BITMAPV3INFOHEADER;

typedef union{

        BITMAPINFOHEADER V1;
        BITMAPV2INFOHEADER V2;
        BITMAPV3INFOHEADER V3;
}ImageInfoHeader;

typedef struct {
    int version;
    BitmapFileHeader bitMapFileHeader;
    ImageInfoHeader imageInfoHeader;
    unsigned char *imageData;
    //void (*convertToRGBA)(void);
    //void (*convertToBGRA)(void);
} BMP;

BMP parseBMPFile(char*);
void decontructBMPPixelArray(BMP);
unsigned char* bmpBGRA(BMP);
#endif /* BMP_h */
