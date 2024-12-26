#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"



using namespace std;

int main() {
    int width, height, channel;
    unsigned char *image = stbi_load("../image/CAT.jpg", &width, &height, &channel, 3);
    unsigned char *output = new unsigned char[width * height * channel];


    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            int index = (h * width + w) * channel;
            //r
            output[index] = image[index] ; 
            
            //g
            if (100 + image[index + 1] > 255)
                output[index + 1] = 255;
            else
                output[index + 1] = 100 + image[index + 1];
            
            //b
            output[index + 2] = image[index + 2]; 

        }
    }

    stbi_write_jpg("../image/output.jpg", width, height, channel, output, width * channel);

    stbi_image_free(image);

    return 0;
}