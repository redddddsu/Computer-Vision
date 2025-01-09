#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"

#include <vector>


using namespace std;

int main() {
    int w, h, c;
    unsigned char *image = stbi_load("../image/flower.jpg", &w, &h, &c, 3);
    unsigned char *flowerOutput = new unsigned char[w * h * c];

    int index;

    // creates the histogram of the original image
    vector<int> histogramR(256, 0);  
    vector<int> histogramG(256, 0);  
    vector<int> histogramB(256, 0);  

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            index = (i * w + j) * c;
            histogramR[image[index]]++;
            histogramG[image[index + 1]]++;
            histogramB[image[index + 2]]++;
        }
    }

    //cumulative distribution function
    vector<int> cdfR(256, 0);
    vector<int> cdfG(256, 0);
    vector<int> cdfB(256, 0);

    cdfR[0] = histogramR[0];
    cdfG[0] = histogramG[0];
    cdfB[0] = histogramB[0];

    for (int i = 1; i < 256; i++) {
        cdfR[i] = cdfR[i - 1] + histogramR[i];
        cdfG[i] = cdfG[i - 1] + histogramG[i];
        cdfB[i] = cdfB[i - 1] + histogramB[i];
    }

    //Normalize the cdf
    int totalPixel = w * h; //dont need channel

    for (int i = 0; i < 256; i++) {
        cdfR[i] = (cdfR[i] * 255) / totalPixel;
        if (cdfR[i] > 255)
            cdfR[i] > 255;

        cdfG[i] = (cdfG[i] * 255) / totalPixel;
        if (cdfG[i] > 255)
            cdfG[i] > 255;

        cdfB[i] = (cdfB[i] * 255) / totalPixel;
        if (cdfB[i] > 255)
            cdfB[i] > 255;

    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            index = (i * w + j) * c;

            int r = image[index]; 
            int g = image[index + 1];
            int b = image[index + 2];

            flowerOutput[index] = cdfR[r];
            flowerOutput[index + 1] = cdfG[g];
            flowerOutput[index + 2] = cdfB[b];
        }
    }


    stbi_write_jpg("../image/flowerOutput.jpg", w, h, c, flowerOutput, w * c);
    
    stbi_image_free(image);

    return 0;
}