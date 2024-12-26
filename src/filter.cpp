#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {

    ifstream image;
    ofstream newImage;

    image.open("monument.ppm");
    newImage.open("newImage");

    //copy over information
    string type;
    string width;
    string height;
    string RGB;

    image >> type;
    image >> width;
    image >> height;
    image >> RGB;

    newImage << type << endl;
    newImage << width << " " << height << endl;
    newImage << RGB << endl;

    string red;
    string green;
    string blue;

    int r;
    int g;
    int b;

    while (!image.eof()) {
        image >> red;
        image >> green;
        image >> blue;

        stringstream redstream(red);
        redstream >> r;
        stringstream greenstream(green);
        greenstream >> g;
        stringstream bluestream(blue);
        bluestream >> b;

        if (b + 50 >= 255) 
            b = 255;
        else 
            b += 50;

        newImage << r << " " << g << " " << b << " " << endl;
    }

    newImage.close();
    image.close();


    return 0;
}