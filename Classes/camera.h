#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera{
    public:
    double aspectRatio = 1.0;
    int imageWidth = 100;
    void render(const hittable& world){
        initialize();
        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    //Generating pixel coords
    for(int j = 0; j <imageHeight; j++){
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush; //progress bar for render
        for(int i = 0; i < imageWidth; i++){
            auto pixelCenter = pixel00Loc + (i * deltaU ) + (j * deltaV);
            auto rayDirection = pixelCenter - center;
            ray r(center, rayDirection);

            color pixelColor = rayColor(r,world);
            writeColor(std::cout, pixelColor);
        }
    }
     std::clog << "\rDone.                 \n"; 


    }
    private:
    int imageHeight;
    point3 center;
    point3 pixel00Loc;
    vec3 deltaU;
    vec3 deltaV;
    void initialize(){
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ?  1 : imageHeight;
        center = point3(0,0,0);
        auto focalLength = 1.0;
        auto viewportHeight  = 2.0;
        auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
        

        //Finding our u and v rays
        auto u = vec3(viewportWidth, 0, 0);
        auto v = vec3(0, -viewportHeight, 0);

        //Calculating the delta u and v vectors
        deltaU = u / imageWidth;
        deltaV = v / imageHeight;

        //Calucating upper left pixel
        auto viewportUpperLeft = center - vec3(0,0,focalLength) - u/2 - v/2;
        pixel00Loc = viewportUpperLeft + 0.5 * (deltaU + deltaV);
    }
    color rayColor(const ray& r, const hittable& world) const {
        hitRecord rec;
        if(world.hit(r, interval(0, infinity), rec)){
            return 0.5 * (rec.normal + color(1,1,1));

        }
        
        vec3 unit_direction = unitVector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif