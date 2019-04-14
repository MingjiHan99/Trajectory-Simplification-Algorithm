#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include "trajectory.hpp"
class Algorithm{
protected:
    //error boundary (meters)
    double bound;
public:
    Algorithm(double bound_):bound{bound_}{

    }

    double get_bound(){
        return bound;
    }

    double set_bound(double bound){
        this->bound = bound;
    }

    virtual Trajectory<Line>* compress(const Trajectory<Point>* traj) = 0;

};



#endif 