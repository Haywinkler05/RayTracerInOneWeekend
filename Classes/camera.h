#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera{
    public:
    double aspectRatio = 1.0;
    int imageWidth = 100;
    int samplesPerPixel = 10;
    int maxDepth = 10;

    double vfov = 90;
    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);
    double defocusAngle = 0;
    double focusDist = 10;
    void render(const hittable& world){
        initialize();
        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    //Generating pixel coords
    for(int j = 0; j <imageHeight; j++){
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush; //progress bar for render
        for(int i = 0; i < imageWidth; i++){
            color pixelColor(0,0,0);
            for(int sample = 0; sample < samplesPerPixel; sample++){
                ray r = getRay(i,j);
                pixelColor += rayColor(r,maxDepth, world);
            }
            writeColor(std::cout, pixelSamplesScale * pixelColor);
        }
    }
     std::clog << "\rDone.                 \n"; 


    }
    private:
    int imageHeight;
    double pixelSamplesScale;
    point3 center;
    point3 pixel00Loc;
    vec3 deltaU;
    vec3 deltaV;
    vec3 u,v,w;
    vec3 defocusDiskU;
    vec3 defocusDiskV;
    void initialize(){
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ?  1 : imageHeight;
        pixelSamplesScale = 1.0 / samplesPerPixel;
        center = lookfrom;
        auto theta = degreesToRadians(vfov);
        auto h = std::tan(theta/2);
        auto viewportHeight  = 2.0 * h * focusDist;
        auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
        
        w = unitVector(lookfrom - lookat);
        u = unitVector(cross(vup, w));
        v = cross(w,u);

        vec3 viewportU = viewportWidth * u;
        vec3 viewportV = viewportHeight * -v;
        //Finding our u and v rays
        

        //Calculating the delta u and v vectors
        deltaU = viewportU / imageWidth;
        deltaV = viewportV / imageHeight;

        //Calucating upper left pixel
        auto viewportUpperLeft = center - (focusDist * w) - viewportU/2 - viewportV/2;
        pixel00Loc = viewportUpperLeft + 0.5 * (deltaU + deltaV);

        auto defocusRadius = focusDist * std::tan(degreesToRadians(defocusAngle / 2));
        defocusDiskU = u * defocusRadius;
        defocusDiskV = v * defocusRadius;
    }
    
    ray getRay(int i, int j) const {
        auto offset = sampleSquare();
        auto pixelSample = pixel00Loc + ((i + offset.x()) * deltaU) + (j + offset.y()) * deltaV;

        auto rayOrigin = (defocusAngle <= 0) ? center : defocusDiskSample();
        auto rayDirection = pixelSample - rayOrigin;

        return ray(rayOrigin, rayDirection);
    }

    vec3 sampleSquare() const{
        return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }
    point3 defocusDiskSample() const {
        auto p = randomInUnitDisk();
        return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
    }
    color rayColor(const ray& r, int depth, const hittable& world) const {
        if(depth <= 0) return color(0,0,0);
        hitRecord rec;
        if(world.hit(r, interval(0.001, infinity), rec)){
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r, rec, attenuation, scattered)) return attenuation * rayColor(scattered, depth-1, world);
            return color(0,0,0);
        }
        
        vec3 unit_direction = unitVector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif