#ifndef POINT_HPP
#define POINT_HPP
#include <cmath>
// x,y is 2d coordinate calculated by Mercator Projection
const double RADIUS = 6371393;

class Point{
    public:
        double longitude,latitude,t;
        double x,y;
    Point(double longitude_,double latitude_,double t_)
        :longitude{longitude_},latitude{latitude_},t{t_}{

            x = RADIUS * (longitude / 360.0) * 2.0 * acos(-1.0);
            double theta = acos(-1.0) / 4.0 + (latitude / 2.0) / 360.0 * 2.0 * acos(-1.0);          
            y = RADIUS * log(tan(theta));
    }
};


#endif