#ifndef POINT_HPP
#define POINT_HPP
#include <cmath>
// x,y is 2d coordinate calculated by Mercator Projection
// https://en.wikipedia.org/wiki/Mercator_projection
const double RADIUS = 6371393;

class Point{
    public:
        double longitude,latitude,t;
        double x,y;
    Point(){

    }
    Point(double x_,double y_):x{x_},y{y_}{

        longitude = x / (2 * acos(-1) * RADIUS) * 360;
        latitude = ((atan(exp(y / RADIUS))) - acos(-1) / 4 ) / acos(-1) * 360;
       
    }
    Point(double longitude_,double latitude_,double t_)
        :longitude{longitude_},latitude{latitude_},t{t_}{

            x = RADIUS * (longitude / 360.0) * 2.0 * acos(-1.0);
            double theta = acos(-1.0) / 4.0 + abs(latitude / 2.0) / 360.0 * 2.0 * acos(-1.0);          
            y = RADIUS * log(tan(theta));
             x =  ((20037508.3427892 *2.0 /360.0) * (180 + longitude));
             y =  ((20037508.3427892 * 2.0/180.0) * (90 - latitude));
    }

    double distance(const Point& rhs){
        return sqrt( (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
    }
};


#endif