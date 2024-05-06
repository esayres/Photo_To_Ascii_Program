#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include <cstdio>
#include <cstdlib>

using namespace std;
#define CONST 500 // for file path size
#define PNG 0 // return value for png file type
#define JPG 1 // return value for jpeg/jpg file type

// consts that for greyscale conver.
#define redConst 0.2126
#define greenConst 0.7152
#define blueConst 0.0722

void pathToFile(char path[]);
void printPath(char array[]);
int determineFileType(char path[]);
char asciiConverter(int greyscaleValue);
int openOutputFileToScreen();


/*
    TODO
    1. Resize every image to 200 x 200 so it can be properly displayed without error (A SOFT FIX FOR THIS IS CREATED)

    BUGS:
    for some pngs and i think jpgs During memory allocation and greyscale algo
        1. px * array is not able to access memory and pixels so it causes a segmentation fault at greyscale algo [ Since px values arent being accessed]
*/


void pathToFile(char path[]){
    cout << "Input Path To (Png, Jpg) Here: ";
    cin.getline(path, CONST);
}


void printPath(char array[]){
    for(int i = 0; array[i] != '\0'; i++){
        cout << array[i];
    }
    cout << endl;
}


int determineFileType(char path[]){
    // [CHANGE THIS TO FILE* INSTEAD FOR FILE/NAMING CONVECTIONS]
    ifstream file;
    file.open(path);
    if(!file){
        cerr << "File Failed To Open!" << endl;
        exit(0);
    }
    char fileSignature[8]; // all png files start with 8 bytes that are the same the tell you the file is a png
    for(int i = 0; i < 8; i++){
        file >> fileSignature[i];
    }
    file.close();

    // check if this char array has the word PNG
    char const *png = "PNG";
    if(strstr(fileSignature, png)){
        cout << "File is a PNG!" << endl;
        return 0;
    } else if(fileSignature[0] == (char)0xFF && fileSignature[1] == (char)0xD8){
        cout << "File is a JPG!" << endl; // techincally should also check for JPG but thats a later problem
        return 1;
    }   else{
        return -1;
    }
}


// Main GreyScale to Ascii Convert
char asciiConverter(int greyscaleValue){
    char asciiChars[11] = {'.', ',', ':', ';', '+', '*', '?', '%','S', '#','@'};
    float value = 0.0f;
    value = round((greyscaleValue / 25.0f));
    if(value > 10){
        value = 10;
    }
    return asciiChars[int(value)];
}


int openOutputFileToScreen(){
    int checker;
    cout << "Would you Like to Open Output File?: 1 - yes, 0 - no: ";
    cin >> checker;
    if(checker > 1 || checker < 0){
        cout << "INVAILD INPUT! DEFAULT: Wont Open Output File\n";
        return -1;
    }
    if(checker == 1){
    const char* path = "start output.txt";
    system(path);
    }
    return 0;
}
