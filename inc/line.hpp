#ifndef LINE_HPP
#define LINE_HPP
#include "point.hpp"
#include <cmath>
/** Line class based on point
 **/
class Line{
    public:
        Line(Point u_,Point v_):u{u_},v{v_}{
            A = v.y - u.y;
            B = u.x - v.x;
            C = v.x * u.y - u.x * v.y;
        }
        //calculate the distance from a point to the line
        double calculate_distance(const Point& rhs){
            return fabs( A * rhs.x + B * rhs.y + C) / sqrt( A * A + B * B );
        }
        double length() const{
            return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
        }
        double angle() const{
            double ang = acos( (v.x - u.x) / length());
            if( v.y < u.y) 
                return -ang;
            return -ang;
        }


    private:
        Point u,v;
        double A,B,C;
};

class FitLine{
    public:
        FitLine(Point s_):s{s_},j{0},theta{0},A{0},B{0},C{0}{
            
        }
        //calculate the distance from a point to the line
        double calculate_distance(const Point& rhs){
            return fabs( A * rhs.x + B * rhs.y + C) / sqrt( A * A + B * B );
        }

        double f(const Line& rhs){
            double differ = rhs.angle() - this->theta;
            if( 0 < differ && differ < acos(-1) / 2.0 || -acos(-1) < differ && differ < -acos(-1) / 2.0 ){
                return 1.0;
            }
            else{
                return -1.0;
            }
        }
        // fit new line
        void fit(const Point& rhs,double bound){
            Line l{s,rhs};
            j = ceil( l.length() * 2 / bound - 0.5);
            if( l.length() - this->length()  < bound / 4){
                return ;
            }
            else if( l.length() - this->length()  < bound / 4 && fabs(this->length()) < 1e-2){
                this->len = j * bound / 2;
                this->theta = l.angle();
            }
            else{
                this->len = j * bound / 2;
                this->theta += f(l) * asin(this->calculate_distance(rhs) / (j * bound * 2))/ j;
            }
        }
        double length(){
            return this->len;
        }

        double angle(){
            return this->theta;
        }

    private:
        Point s;
        int j;
        double x,y; // virtual point
        double len;
        double theta;
        double A,B,C;
};

#endif