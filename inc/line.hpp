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
            // as the range of acos is [0,PI]
            // we need to check the angle on our own
            if( v.y > u.y) 
                return ang;
            else 
                return 2 * acos(-1) - ang;
        }


    private:
        Point u,v;
        double A,B,C;
};

class FitLine{
    public:
        FitLine(Point s_):s{s_},j{0},theta{0},A{0},B{0},C{0},len{0}{
            
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
        void update_line_parmeters(){
            A = y - s.y;
            B = s.x - x;
            C = x * s.y - s.x * y;
        }
        // fit new line
        void fit(const Point& rhs,double bound){
            
            Line l{s,rhs};
       
            if( l.length() - this->length()  < bound / 4){
   
            }
            else if( l.length() - this->length()  > bound / 4 && is_first()){
    
                j = ceil( l.length() * 2 / bound - 0.5);
                this->len = j * bound / 2;
                this->theta = l.angle();
                x = s.x + this->len * cos(this->theta);
                y = s.y + this->len * sin(this->theta);
                update_line_parmeters();
            }
            else{
            
                j = ceil( l.length() * 2 / bound - 0.5);
                this->len = j * bound / 2;
             
                this->theta += f(l) * asin(this->calculate_distance(rhs) / (j * bound * 2))/ j;
                x = s.x + this->len * cos(this->theta);
                y = s.y + this->len * sin(this->theta);
                update_line_parmeters();
            }
            
            
           
        }
        double length(){
            return this->len;
        }

        double angle(){
            return this->theta;
        }

        bool is_first(){
            return j == 0;
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