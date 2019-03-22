#ifndef POINT_HPP
#define POINT_HPP
// t is time stamp
// x is longitude
// y is latitude 

class Point{
    public:
        double x,y,t;
    
    Point(double x_,double y_,double t_)
        :x{x_},y{y_},t{t_}{

    }
};


#endif