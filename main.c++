

#include "Classes/rtweekend.h"
#include "Classes/camera.h"
#include "Classes/hittable.h"
#include "Classes/hittableList.h"
#include "Classes/material.h"
#include "Classes/sphere.h"


int main(){
   hittableList world;

   auto groundMaterial = make_shared<lambertian>(color(0.5,0.5,0.5));
   world.add(make_shared<sphere>(point3(0,-1000,0), 1000, groundMaterial));
   
    
    

   camera cam;

   cam.aspectRatio = 16.0 / 9.0;   
   cam.imageWidth = 400;
   cam.samplesPerPixel = 100;
   cam.maxDepth = 50;


   cam.vfov = 20;
   cam.lookfrom = point3(-2,2,1);
   cam.lookat = point3(0,0,-1);
   cam.vup = vec3(0,1,0);

   cam.defocusAngle = 10.0;
   cam.focusDist = 3.4;
   cam.render(world);


}