#ifndef FBQS_HPP
#define FBQS_HPP
#include "algorithm.hpp"
class FBQS:public Algorithm{

    FBQS(double bound_):Algorithm{bound_}{

    }    

    Trajectory<Line>* compress(const Trajectory<Point>* traj) {
        Trajectory<Line>* res;
        if(traj->size() == 1){
            return res;
        }
        else if(traj->size() == 2){
            res->push(Line{(*traj)[0],(*traj)[1]});
        }
        else if(traj->size() > 2){
            int start = 0;
            int end = 1;
            std::vector<int> buffer;
            while(end < traj->size()){
                if( (*traj)[start].distance((*traj)[end]) < bound){
                    buffer.push_back(end);
                }
                else{
                    
                }


                end++;
            }

        }
        return res;
        
    }

    std::pair<double,double> get_bounds(){
        return {0.0,0.0};
    }
};


#endif