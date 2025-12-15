#include <iostream>


int main(){
    //Image
    int imageWidth = 256;
    int imageHeight = 256;

    //render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    //Generating pixel coords
    for(int j = 0; j <imageHeight; j++){
        for(int i = 0; i < imageWidth; i++){
            auto r = double(i) /(imageWidth -1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0;

            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }



}