#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"



class sphere : public hittable{
    public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)){}
        
        bool hit(const ray& r, interval ray_t, hitRecord& rec) const override{
            vec3 oc = center - r.origin();
            auto a = r.direction().lengthSquared();
            auto h = dot(r.direction(), oc);
            auto c = oc.lengthSquared() - radius * radius;

            auto discrim = h * h - a * c;
            if(discrim < 0){
                return false;
            }

            auto sqrtd = std::sqrt(discrim);

            auto root = (h - sqrtd) / a;
            if(!ray_t.surrounds(root)){
                root = (h + sqrtd) / a;
                if(!ray_t.surrounds(root)){
                    return false;
                }
            }
            rec.t = root;
            rec.p = r.at(rec.t);
           vec3 outwardNormal = (rec.p - center) / radius;
           rec.setFrontFace(r, outwardNormal);
            return true;
                                                                                    
        }

    private:
        point3 center;
        double radius;
};
#endif