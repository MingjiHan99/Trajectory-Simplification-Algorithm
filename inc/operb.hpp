#ifndef OPERB_HPP
#define OPERB_HPP
#include "algorithm.hpp"
#include "trajectory.hpp"
class OPERB:public Algorithm{

public:
    OPERB(double bound_):Algorithm{bound_}{

    }

    Trajectory<Line>* compress(Trajectory<Point>* traj){

        Trajectory<Line>* res = new Trajectory<Line>;
        //when trajectory size is too small, we return result directly
        if(traj->size() < 2){
            return nullptr;
        }
        if(traj->size() == 2){
            res->push(Line{(*traj)[0],(*traj)[1]});
            return res;
        }
        else{
            //intialization
            int s_index = 0,e_index = 0;


            FitLine initial_line{(*traj)[s_index]};
            //get first active point

            auto first_point = get_active_point(traj,0,0,initial_line);
        
            while (first_point.first != -1){
                  
                  s_index = e_index;
                  
                  FitLine fit_line{(*traj)[s_index]};
                
                  fit_line.fit((*traj)[first_point.first],bound);
                  
                  auto next_point = get_active_point(traj,s_index,first_point.first,fit_line);
                  //next_point  -- a index

                  while( next_point.first != -1 && next_point.second){

                      fit_line.fit((*traj)[next_point.first],bound);

                      e_index = next_point.first;

                      next_point = get_active_point(traj,s_index,first_point.first,fit_line);
                  }

                  res->push(Line{(*traj)[s_index],(*traj)[e_index]});
                
            }


        }
        
        return res;
    }


    std::pair<int,bool> get_active_point(Trajectory<Point>* traj, int s_index,int a_index, FitLine L){
        
        int i = a_index + 1;                                                                                                                                                                                                                                                                                                                                                                                            
        bool flag = true;
        Line R{(*traj)[s_index],(*traj)[a_index]};

        while ( i - s_index <= magic_number && i < traj->size() && R.length() - L.length() <= bound / 4){
            
            if( L.calculate_distance((*traj)[i]) > bound / 2 && R.calculate_distance((*traj)[i]) > bound){
                flag = false;
                break;
            }
            R = Line{(*traj)[s_index],(*traj)[a_index]};
            i++;
        }

        if(L.calculate_distance((*traj)[i]) > bound / 2 && fabs(L.length()) > 1e-2 ){
            flag = false;
        }
    
        if(i == traj->size() ){
            i = -1;
        }

        return {i,flag};

    }

private:
    const int magic_number = 400000;

};


#endif