#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

//C++ std usings
using std::make_shared;
using std::shared_ptr;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility Functions
inline double degreesToRadians(double degrees){
    return degrees * pi / 180;
}

inline double randomDouble(){
    return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max){
    return min + (max-min) * randomDouble();
}

//Common 

#include "color.h"
#include "vec3.h"
#include "interval.h"
#include "ray.h"


#endif