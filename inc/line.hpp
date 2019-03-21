#ifndef LINE_HPP
#define LINE_HPP
#include "point.hpp"
#include <cmath>
/** Line class based on point
 **/
class Line{
    public:
        Line(Point& u_,Point& v_):u{u_},v{v_}{
            A = v.y - u.y;
            B = u.x - v.x;
            C = v.x * u.y - u.x * v.y;
        }
        //calculate the distance from a point to the line
        double calculate_distance(const Point& rhs){
            return fabs( A * rhs.x + B * rhs.y + C) / sqrt( A * A + B * B );
        }

    private:
        Point u,v;
        double A,B,C;
};


#endif