//
//  BMP.c
//  BMP-Processor
//
//  Created by Adenike Adeyemi on 10/25/17.
//  Copyright © 2017 Adenike Adeyemi. All rights reserved.
//

#include "BMP.h"
#include <string.h>

unsigned char* bmpBGRA(BMP input){
    //check if bmp file has an alpha mask
    if(input.version != 3 && input.imageInfoHeader.V3.alphaMask != 0xff){
        printf("image does not contain Alpha Mask\n");
        return input.imageData;
    }
    unsigned char *output = malloc(sizeof(*output)*input.imageInfoHeader.V3.imageSize);
    
    memcpy(output, input.imageData, input.imageInfoHeader.V3.imageSize);
    unsigned char temp;
    for(int i = 1; i < input.imageInfoHeader.V3.imageSize; i++){
        if(i%4 == 0)
            continue;
        temp = output[i];
        output[i] = output[i-1];
        output[i-1] = temp;
    }
    
    return output;
}
/*
unsigned char* bmpBGRA(){
    unsigned char *temp;
    
    return temp;
}*/

BMP parseBMPFile(char * filename){
    
    //initialize variables
    BMP out;
    FILE *fp;
    char buffer[14];
    char *infobuffer;
    
    //open file
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Something is wrong with file\n");
        exit(1);
    }
    
    //bring pointer to the start
    fseek(fp, 0, SEEK_SET);
    
    //read data into buffer
    if(fread(buffer, 1, 14, fp) != 14){
        printf("Something is wrong with the file\n");
        exit(1);
    }
    
    //check if file is correct BMP file
    if(buffer[0] != 'B' || buffer[1] != 'M'){
        printf("Something is wrong with the BMP file\n");
        exit(1);
    }
    
    //parse out BMP File header
    out.bitMapFileHeader.signiture[0] = buffer[0];
    out.bitMapFileHeader.signiture[1] = buffer[1];
    out.bitMapFileHeader.fileSize = *(int *)&buffer[0x02];
    out.bitMapFileHeader.reserved1 = *(char *)&buffer[0x06];
    out.bitMapFileHeader.reserved2 = *(char *)&buffer[0x08];
    out.bitMapFileHeader.imgOffset = *(int *)&buffer[0x0A];
    
    //allocate space for temporary buffer
    infobuffer = malloc(sizeof(*infobuffer) * (out.bitMapFileHeader.imgOffset-14));
    if(infobuffer == NULL){
        printf("Out of memory\n");
        exit(1);
    }
    
    //read data into info buffer
    if(fread(infobuffer, 1, out.bitMapFileHeader.imgOffset-14, fp) != out.bitMapFileHeader.imgOffset-14){
        printf("Something is wrong with the file");
        exit(1);
    }
    //get header size
    out.imageInfoHeader.V1.headerSize = *(int*)&infobuffer[0];
    
    //get version number (Version 3 - 5 is under version 3)
    if( out.imageInfoHeader.V1.headerSize >= 56){
        out.version = 3;
    }
    else if(out.imageInfoHeader.V1.headerSize == 54){
        out.version = 2;
    }
    else{
        out.version = 1;
    }
    
    //parse out data
    switch (out.version) {
        case 3:
            out.imageInfoHeader.V3.alphaMask = *(int*)&infobuffer[0x42 - 0x0E];
            
        case 2:
            out.imageInfoHeader.V2.blueMask = *(int*)&infobuffer[0x3E - 0x0E];
            out.imageInfoHeader.V2.greenMask = *(int*)&infobuffer[0x3A - 0x0E];
            out.imageInfoHeader.V2.redMask = *(int*)&infobuffer[0x36 - 0x0E];
            
        case 1:
            out.imageInfoHeader.V1.numImportantColors = *(int*)&infobuffer[0x32 - 0x0E];
            out.imageInfoHeader.V1.numColors = *(int*)&infobuffer[0x2E - 0x0E];
            out.imageInfoHeader.V1.verticalRes = *(int*)&infobuffer[0x2A - 0x0E];
            out.imageInfoHeader.V1.horizontalRes = *(int*)&infobuffer[0x26 - 0x0E];
            out.imageInfoHeader.V1.imageSize = *(int*)&infobuffer[0x22 - 0x0E];
            out.imageInfoHeader.V1.compression = *(int*)&infobuffer[0x1E - 0x0E];
            out.imageInfoHeader.V1.bpp = *(char*)&infobuffer[0x1C - 0x0E];
            out.imageInfoHeader.V1.planes = *(char*)&infobuffer[0x1A - 0x0E];
            out.imageInfoHeader.V1.height = *(int*)&infobuffer[0x16 - 0x0E];
            out.imageInfoHeader.V1.width = *(int*)&infobuffer[0x12 - 0x0E];
            
            //make sure image size exists
            if(out.imageInfoHeader.V1.imageSize == 0){
                out.imageInfoHeader.V1.imageSize = (((out.imageInfoHeader.V1.bpp*out.imageInfoHeader.V1.width+31)/32)*4)*(out.imageInfoHeader.V1.height);
            }
            break;
            
        default:
            break;
    }
    
    //allocate data for imageData
    out.imageData = malloc(sizeof(out.imageInfoHeader.V1.imageSize));
    
    if(fread(out.imageData, 1, out.imageInfoHeader.V1.imageSize, fp) != out.imageInfoHeader.V1.imageSize){
        printf("Something is wrong with this file\n");
        exit(1);
    }
    
    //free temporary buffer
    free(infobuffer);
    
    //close file
    fclose(fp);
    
    
    return out;
}

void decontructBMPPixelArray(BMP bmp){
    free(bmp.imageData);
    printf("Image data has been freed.\n");
}
