

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
   
   for(int a = -11; a < 11; a++){
      for (int b = -11; b < 11; b++){
         auto chooseMat = randomDouble();
         point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

         if((center - point3(4,0.2,0)).length() > 0.9){
            shared_ptr<material> sphereMaterial;

            if(chooseMat < 0.8){
               //diffuse

               auto albedo = color::random() * color::random();
               sphereMaterial = make_shared<lambertian>(albedo);
               world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
            } else if(chooseMat < 0.95){
               //Metal

               auto albedo = color::random(0.5,1);
               auto fuzz = randomDouble(0, 0.5);
               sphereMaterial = make_shared<metal>(albedo, fuzz);
            }else{
               sphereMaterial = make_shared<dielectric>(1.5);
               world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
            }
         }
      }
   }

   auto material1 = make_shared<dielectric>(1.5); 
   world.add(make_shared<sphere>(point3(0,1,0), 1.0, material1));

   auto material2 = make_shared<lambertian>(color(0.4,0.2,0.1));
   world.add(make_shared<sphere>(point3(-4,1,0), 1.0, material2));

   auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
   world.add(make_shared<sphere>(point3(4,1,0), 1.0, material3));
    
    

   camera cam;

   cam.aspectRatio = 16.0 / 9.0;   
   cam.imageWidth = 1200;
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