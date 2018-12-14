//
//  main.c
//  BMP-Processor
//
//  Created by Adenike Adeyemi on 10/25/17.
//  Copyright © 2017 Adenike Adeyemi. All rights reserved.
//

//#include <stdio.h>
//#include <stdlib.h>
#include "BMP.h"



BMP bmp;

int main(int argc, const char * argv[]) {
    
    bmp = parseBMPFile("test2.bmp");
   // unsigned char* test = bmpBGRA(bmp);
    
    printf("The signiture of the BMP file is '%c%c'.\n", bmp.bitMapFileHeader.signiture[0], bmp.bitMapFileHeader.signiture[1]);
    printf("The imagesize of the BMP file is %d bytes. \n", bmp.bitMapFileHeader.fileSize);
    printf("The imageOffset of the BMP file is %x. \n",bmp.bitMapFileHeader.imgOffset); //for opengl check for this
    
    printf("Header Size: %d bytes\n", bmp.imageInfoHeader.V3.headerSize);
    printf("Header Height: %d bytes\n", bmp.imageInfoHeader.V3.height);//for opengl check for this
    printf("Header Width: %d bytes\n", bmp.imageInfoHeader.V3.width);//for opengl check for this
    printf("bpp: %d\n", bmp.imageInfoHeader.V1.bpp);
    printf("Image map size: %d\n", bmp.imageInfoHeader.V1.imageSize); //for open gl check for this
 
    
    printf("Alpha mask: %d\n", bmp.imageInfoHeader.V3.alphaMask); //for opengl check for this
    printf("Red mask: %d\n", bmp.imageInfoHeader.V3.redMask);
    printf("Blue mask: %d\n", bmp.imageInfoHeader.V3.blueMask);
    printf("Green mask: %d\n", bmp.imageInfoHeader.V3.greenMask);
    /*
    for(int i = 0; i < bmp.imageInfoHeader.V1.imageSize; i++){
        if(i%16 == 0) printf("\n");
        printf("%x ", test[i]);
        
    }*/
    
    printf("\n");
    printf("\n");
    
    for(int i = 0; i < bmp.imageInfoHeader.V1.imageSize; i++){
        if(i%16 == 0) printf("\n");
        printf("%x ", bmp.imageData[i]);
        
    }
    printf("\n");
    

    decontructBMPPixelArray(bmp);
    //free(test);
    
    return 0;
}
