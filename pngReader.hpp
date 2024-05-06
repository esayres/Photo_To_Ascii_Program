#pragma once
#include "main.hpp"
#include "libpng\png.h"

void readPngFile(char path[], int checker);


// use libPng to read the png file and then perform Gray Scale average to Ascii
void readPngFile(char path[], int checker){
    std::FILE *pngFile = fopen(path, "rb");
    if(!pngFile){
        cerr << "File Failed To Open!" << endl;
        exit(1);
    }

    std::FILE *outputFile = fopen("output.txt", "w");
    if(!outputFile){
        cerr << "Output File Failed to Create/Write!" << endl;
        exit(1);
    }

    png_voidp userErrorPtr = NULL;
    png_error_ptr userErrorFn = NULL, userWarningFn = NULL;
    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)userErrorPtr, userErrorFn, userWarningFn);
    if(!pngPtr){
        cerr << "png Read Structure Ptr Failed To Init" << endl;
        exit(1);
    }
    png_infop pngInfoPtr = png_create_info_struct(pngPtr);
    if(!pngInfoPtr){
        png_destroy_read_struct(&pngPtr, (png_infopp)NULL, (png_infopp)NULL);
        cerr << "Png Info Structure Ptr Failed To Init" << endl;
        exit(1);
    }
    png_init_io(pngPtr, pngFile);
    
    png_read_info(pngPtr, pngInfoPtr);
    
    int width = png_get_image_width(pngPtr, pngInfoPtr);
    int height = png_get_image_height(pngPtr, pngInfoPtr);
    png_byte color_type = png_get_color_type(pngPtr,pngInfoPtr);
    png_byte bit_depth = png_get_bit_depth(pngPtr,pngInfoPtr);

    // allocate memory for img
    cout << "ALLOCATING IMG TO MEMORY" << endl;
    png_bytep rowPointers[height];
    for(int y = 0; y < height; y++){
        rowPointers[y] = new png_byte[png_get_rowbytes(pngPtr,pngInfoPtr)];
    }
    png_read_image(pngPtr, rowPointers);

    // acces pixel data
    cout << "ACCESSING PIXEL DATA" << endl;
    for(int y = 0; y < height; y++){
        if(checker == 1 && height > 1500){
            y += floor(height / 1500);
            if( y >= height){
                    break;
                }
        }
        png_bytep row = rowPointers[y];
        for(int x = 0; x < width; x++){ 
            if(checker == 1 && width > 1000){
                x += floor(width / 1000);
                if(x >= width){
                    break;
                }
            }
            // px[0] - red , px[1] - green, px[2] - blue, px[3] - Alpha
            png_bytep px = &(row[x * 4]);
            if(px[0] > 255 || px[1] > 255 || px[2] > 255){
                px[0] = 0; // Set red component to 0
                px[1] = 0; // Set green component to 0
                px[2] = 0; // Set blue component to 0
            }

            int greyscaleValue = (px[0] * redConst) + (px[1] * greenConst) + (px[2] * blueConst);
            char charPrint[2] = {asciiConverter(greyscaleValue)};
            charPrint[1] = '\0';
            fprintf(outputFile, "%s", charPrint);
        }
        fprintf(outputFile, "\n"); // 
    }

    // frees the memory and closes the file
    cout << "\nFREEING MEMORY" << endl;
    for(int i = 0; i < height; i++){
        delete rowPointers[i];
    }
    fclose(pngFile);
    fclose(outputFile);
    png_destroy_read_struct(&pngPtr, &pngInfoPtr, (png_infopp)NULL);
    cout << "CLOSED FILE" << endl;
}
