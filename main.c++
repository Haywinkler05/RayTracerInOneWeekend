

#include "Classes/rtweekend.h"
#include "Classes/camera.h"
#include "Classes/hittable.h"
#include "Classes/hittableList.h"
#include "Classes/sphere.h"


int main(){
   hittableList world;
   world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
   world.add(make_shared<sphere>(point3(0,-100.5,-1),100));

   camera cam;

   cam.aspectRatio = 16.0 / 9.0;   
   cam.imageWidth = 400;
   cam.samplesPerPixel = 100;

   cam.render(world);


}