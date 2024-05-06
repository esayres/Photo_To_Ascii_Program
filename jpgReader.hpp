#pragma once
#include "main.hpp"
#include "libjpeg-turbo/jpeglib.h"

void readJpgFile(char path[], int checker);
void rbgOverError(unsigned char &red, unsigned char &green, unsigned char &blue);


void readJpgFile(char path[], int checker){
    // open file
    std::FILE *jpgFile = fopen(path, "rb");
    if(!jpgFile){
        cerr << "JPG FILE FAILED TO OPEN" << endl;
        exit(1);
    }

    std::FILE *outputFile = fopen("output.txt", "w");
    if(!outputFile){
        cerr << "OUTPUT FILE FAILED TO OPEN/CREATE" << endl;
        exit(1);
    }

    // libjpg init
    struct jpeg_decompress_struct jpgInfo;
    struct jpeg_error_mgr jpgError;
    jpgInfo.err = jpeg_std_error(&jpgError);
    jpeg_create_decompress(&jpgInfo);

    // file and reading
    jpeg_stdio_src(&jpgInfo, jpgFile);
    jpeg_read_header(&jpgInfo, TRUE);

    jpeg_start_decompress(&jpgInfo);

    // here is where the image reading goes
    int width = jpgInfo.output_width;
    int height = jpgInfo.output_height;
    int numChannels = jpgInfo.output_components;
    int rowStride = width * numChannels;

    //allocate
    cout << "ALLOCATING IMG TO MEMORY (jpg)" << endl;
    JSAMPARRAY buffer = new JSAMPROW[height];
    for(int y = 0; y < height; y++){
        buffer[y] = new JSAMPLE[rowStride];
    }
    while(jpgInfo.output_scanline < jpgInfo.output_height){
        jpeg_read_scanlines(&jpgInfo, &buffer[jpgInfo.output_scanline], height - jpgInfo.output_scanline);
    }

    // access pixel (grey scale algorithmn in here)
    cout << "ACCESSING PIXEL DATA (jpg)" << endl;
    for(int y = 0; y < height; y++){
        if(checker == 1 && height > 1500){
            y += floor(height / 1500);
            if( y >= height){
                break;
            }
        }
        JSAMPROW row = buffer[y];
        for(int x = 0; x < width; x++){
            if(checker == 1 && width > 1000){
                x += floor(width / 1000);
                if(x >= width){
                    break;
                }
            }

            int px = x * numChannels;
            unsigned char red, green, blue;
            red = row[px];
            green = row[px + 1];
            blue = row[px + 2];
            rbgOverError(red, green, blue);

            int greyscaleValue = (red * redConst) + (green * greenConst) + (blue * blueConst);
            char charPrint[2] = {asciiConverter(greyscaleValue)};
            charPrint[1] = '\0';
            fprintf(outputFile, "%s", charPrint);
        }
        fprintf(outputFile, "\n");
    }

    // freeing memory
    cout << "\nFREEING MEMORY (jpg)" << endl;
    for(int i = 0; i < height; i++){
        delete[] buffer[i];
    }
    delete[] buffer;

    // cleanup
    jpeg_finish_decompress(&jpgInfo);
    jpeg_destroy_decompress(&jpgInfo);
    fclose(jpgFile);
    fclose(outputFile);
    cout << "CLOSED FILE (jpg)" << endl;
}

void rbgOverError(unsigned char &red, unsigned char &green, unsigned char &blue){
    if(red > 255 || green > 255 || blue > 255){ // Error handling
                red = 0;
                green = 0;
                blue = 0;
            }
}