

#include "Classes/rtweekend.h"

#include "Classes/hittable.h"
#include "Classes/hittableList.h"
#include "Classes/sphere.h"

color rayColor(const ray& r, const hittable& world){
    hitRecord rec;
    if(world.hit(r, interval(0, infinity), rec)){
        return 0.5 * (rec.normal + color(1,1,1));

    }
    
    vec3 unit_direction = unitVector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main(){
    //Image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    //Calculating image height and making sure its at least 1
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ?  1 : imageHeight;

    //World
     hittableList world;
     world.add(make_shared<sphere>(point3(0,0,-1),0.5));
     world.add(make_shared<sphere>(point3(0,-100.5,-1),100));
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

            color pixelColor = rayColor(r,world);
            writeColor(std::cout, pixelColor);
        }
    }
     std::clog << "\rDone.                 \n"; 


}