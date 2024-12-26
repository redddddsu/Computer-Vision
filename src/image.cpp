#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {

    //create our own image
    ofstream image;
    image.open("image.ppm");

    srand(time(0));

    if(!(image.is_open())) {
        throw runtime_error("Image not open");
    }

    /*
    place header info
    using p3 for our ppm
    */
    image << "P3" << endl; //header type
    image << "250 250" << endl; //x and y limit
    image << "255" << endl; //rgb limit

    for (int y = 0; y < 250; y++) {
        for (int x = 0; x < 250; x++) {
            image << 255 << " " << 0 << " " << 0 << endl;
        }
    }

    image.close();

    return 0;
}
