

#include "Classes/vec3.h"
#include "Classes/color.h"
#include "Classes/ray.h"
#include <iostream>
bool hitSphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc,oc) - radius * radius;
    auto discrim = b*b - 4 * a * c;
    return(discrim >= 0);
}
color rayColor(const ray& r){
    if(hitSphere(point3(0,0,-1), 0.5, r)){
        return color(1,0,0);
    }
    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main(){
    //Image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    //Calculating image height and making sure its at least 1
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ?  1 : imageHeight;

    //Camera
    auto focalLength = 1.0;
    auto viewportHeight  = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = point3(0,0,0);

    //Finding our u and v rays
    auto u = vec3(viewportWidth, 0, 0);
    auto v = vec3(0, -viewportHeight, 0);

    //Calculating the delta u and v vectors
    auto deltaU = u / imageWidth;
    auto deltaV = v / imageHeight;

    //Calucating upper left pixel
    auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - u/2 - v/2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (deltaU + deltaV);

    //render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    //Generating pixel coords
    for(int j = 0; j <imageHeight; j++){
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush; //progress bar for render
        for(int i = 0; i < imageWidth; i++){
            auto pixelCenter = pixel00Loc + (i * deltaU ) + (j * deltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
     std::clog << "\rDone.                 \n"; 


}