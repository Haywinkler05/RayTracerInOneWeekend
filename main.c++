

#include "Classes/rtweekend.h"
#include "Classes/camera.h"
#include "Classes/hittable.h"
#include "Classes/hittableList.h"
#include "Classes/material.h"
#include "Classes/sphere.h"


int main(){
   hittableList world;

   auto R = std::cos(pi/4);

    auto material_left  = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));

    world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));

   camera cam;

   cam.aspectRatio = 16.0 / 9.0;   
   cam.imageWidth = 400;
   cam.samplesPerPixel = 100;
   cam.maxDepth = 50;


   cam.vfov = 90;

   cam.render(world);


}