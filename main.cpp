#include "main.hpp"
#include "pngReader.hpp"
#include "jpgReader.hpp"

int main(){
    char path[CONST];
        
    pathToFile(path);
    printPath(path);


    int checker = 0;
    cout << "Image Reducer: 1 - on , 0 - None: ";
    cin >> checker;
    if(checker > 1 || checker < 0){
        cout << "INVAILD INPUT: Defaulting to No Image Reducer (0)" << endl;
    }


    // read and determine photo type
    int type;
    type = determineFileType(path);


    // reads the Photo based of type
    switch (type){
    case PNG:
        // preform png
        cout << "READING PNG FILE" << endl;
        readPngFile(path, checker);
        cout << "file finished reading" << endl;
        break;

    case JPG:
        // preform jpg
        cout << "READING JPG FILE" << endl;
        readJpgFile(path, checker);
        break;

    default:
        cerr << "File Type is not Supported!" << endl;
        printPath(path);
        exit(0);
        break;
    }
        
    openOutputFileToScreen();
}