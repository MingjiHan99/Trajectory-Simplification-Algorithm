#ifndef OPERB_HPP
#define OPERB_HPP
#include "algorithm.hpp"
#include "trajectory.hpp"
class OPERB:public Algorithm{

public:
    OPERB(double bound_):Algorithm{bound_}{

    }

    Line fitting_function(Line l){
        return l;
    }

    Trajectory<Line>* compress(Trajectory<Point>* traj){
        return nullptr;
    }


    std::pair<Point,bool> get_active_point(Trajectory<Point>* traj, int s_index,int a_index, Line L){
        int i = a_index + 1;
        bool flag = true;
        Line R{(*traj)[s_index],(*traj)[i]};

        while ( i - s_index <= magic_number && i < traj->size() && R.length() - L.length() <= bound){
            
            i++;
        }


    }

private:
    const int magic_number = 400000;

};


#endif