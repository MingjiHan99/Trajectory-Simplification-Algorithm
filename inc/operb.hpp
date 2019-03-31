#ifndef OPERB_HPP
#define OPERB_HPP
#include "algorithm.hpp"
#include "trajectory.hpp"
#include <cmath>
class OPERB:public Algorithm{

public:
    OPERB(double bound_):Algorithm{bound_}{

    }

    Trajectory<Line>* compress(const Trajectory<Point>* traj){

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

            auto next_point  = get_active_point(traj,0,0,initial_line);
            
            //done

            while (next_point.first != -1){
               
                  
                  s_index = e_index;
                  
                  FitLine fit_line{(*traj)[s_index]};
                  
                  fit_line.fit((*traj)[next_point.first],bound);
               
                  next_point = get_active_point(traj,s_index,next_point.first,fit_line);
                  //next_point  -- acitve point index
                  if(next_point.second == false && next_point.second != -1){
                      e_index = next_point.first;
                  }
                  // next_point.second is flag
                  // when flag is false but active point is not null
                  // we need to create new segments
                  while(next_point.first != -1 && next_point.second == true){
               
                      fit_line.fit((*traj)[next_point.first],bound);
                  
                      e_index = next_point.first;
                      
                      next_point = get_active_point(traj,s_index,next_point.first,fit_line);
                

                  }
                 
                  if(e_index != -1)
                        res->push(Line{(*traj)[s_index],(*traj)[e_index]});
         
            }


        }
        
        return res;
    }


    std::pair<int,bool> get_active_point(const Trajectory<Point>* traj, int s_index,int a_index, FitLine L){
        
        int i = a_index + 1;                                                                                                                                                                                                                                                                                                                                                                                            
        bool flag = true;
        Line R{(*traj)[s_index],(*traj)[i]};

        while ( i - s_index <= magic_number && i < traj->size() && R.length() - L.length() < bound / 4){
       
            if( L.calculate_distance((*traj)[i]) > bound / 2 && R.calculate_distance((*traj)[i]) > bound){
                flag = false;
                break;
            }
            i++;
            R = Line{(*traj)[s_index],(*traj)[i]};
           
        }

        if(L.calculate_distance((*traj)[i]) > bound / 2 && !L.is_first()){
            flag = false;
        }
    
        if(i >= traj->size() ){
            i = -1;
        }
      
        return {i,flag};

    }

private:
    const int magic_number = 400000;

};

class OPERBA:public Algorithm{

public:
    OPERBA(double bound_,double gamma_y_ = acos(-1) / 3.0):Algorithm{bound_},gamma_y{gamma_y_}{

    }

    Trajectory<Line>* compress(const Trajectory<Point>* traj){

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
            Line R_pre,R_ano;
            bool R_pre_null = true,R_ano_null = true; // to identify whether they are null or not.
            int R_ano_s = 0,R_ano_e = 0;
            FitLine initial_line{(*traj)[s_index]};
            //get first active point

            auto next_point  = get_active_point(traj,0,0,initial_line);
            
            //done

            while (next_point.first != -1){
               
                  
                  s_index = e_index;
                  
                  FitLine fit_line{(*traj)[s_index]};
                  
                  fit_line.fit((*traj)[next_point.first],bound);
               
                  next_point = get_active_point(traj,s_index,next_point.first,fit_line);
                  //next_point  -- acitve point index
                  if(next_point.second == false && next_point.second != -1){
                      e_index = next_point.first;
                  }
                  // next_point.second is flag
                  // when flag is false but active point is not null
                  // we need to create new segments
                  while(next_point.first != -1 && next_point.second == true){
               
                      fit_line.fit((*traj)[next_point.first],bound);
                  
                      e_index = next_point.first;
                      
                      next_point = get_active_point(traj,s_index,next_point.first,fit_line);
                   }

                   if(next_point.first != -1 && R_ano_null == true 
                        && s_index + 1 == e_index){
                            R_ano = Line{(*traj)[s_index],(*traj)[e_index]};
                            R_ano_s = s_index;
                            R_ano_e = e_index;
                            R_ano_null = false;
                        }

                      if(next_point.first != -1 &&  R_ano_null == false
                         && R_ano_s != s_index && R_ano_e != e_index){
                            bool is_patch = false;
                            Line R_a,R_b;
                            if(R_pre_null != true){
                                auto patch_result = patch(R_pre,R_ano,Line{(*traj)[s_index],(*traj)[e_index]});
                                if(patch_result.second == true){
                                     is_patch = true;
                                     R_a = patch_result.first.first;
                                     R_b = patch_result.first.second;
                                }
                            }

                            if(is_patch == true){
                                res->push(R_a);
                                R_pre = R_b;
                                R_pre_null = false;
                            }
                            else{
                                if(R_pre_null == false)
                                     res->push(R_pre);
                                
                                res->push(R_ano);
                                R_ano_null = true;

                                R_pre = Line{(*traj)[s_index],(*traj)[e_index]};
                                R_pre_null = false;
                            }
                         
                            R_ano_null = true;
                        }
                       else if(next_point.first != -1 && R_ano_null == true){
                           res->push(R_pre);
                           R_pre = Line{(*traj)[s_index],(*traj)[e_index]};
                           R_pre_null = false;
                       }
                        

                  }
                 
                  if(R_pre_null == false)
                        res->push(R_pre);
                  if(R_ano_null == false)
                        res->push(R_ano);


        }
        
        return res;
    }


    std::pair<int,bool> get_active_point(const Trajectory<Point>* traj, int s_index,int a_index, FitLine L){
        
        int i = a_index + 1;                                                                                                                                                                                                                                                                                                                                                                                            
        bool flag = true;
        Line R{(*traj)[s_index],(*traj)[i]};

        while ( i - s_index <= magic_number && i < traj->size() && R.length() - L.length() < bound / 4){
       
            if( L.calculate_distance((*traj)[i]) > bound / 2 && R.calculate_distance((*traj)[i]) > bound){
                flag = false;
                break;
            }
            i++;
            R = Line{(*traj)[s_index],(*traj)[i]};
           
        }

        if(L.calculate_distance((*traj)[i]) > bound / 2 && !L.is_first()){
            flag = false;
        }
    
        if(i >= traj->size() ){
            i = -1;
        }
      
        return {i,flag};

    }

    std::pair<std::pair<Line,Line>,bool> patch(Line R_pre,Line R_ano,Line R_suc){
        
       
        Point G = R_pre.intersection(R_suc);
        double angle_difference = R_pre.angle() - R_suc.angle();
        Line L_a{R_pre.start_point(),G},L_b{G,R_ano.end_point()};

        if( R_pre.length() - L_a.length() < bound / 2  && ( -acos(-1) * 2.0 < angle_difference && angle_difference <= -acos(-1) - gamma_y 
            || gamma_y - acos(-1) <= angle_difference && angle_difference <= acos(-1) - gamma_y
            || acos(-1) + gamma_y <= angle_difference && angle_difference < 2 * acos(-1) )){
            return {{L_a,L_b},true};
        }
        else 
            return {{Line{},Line{}},false};
    }

private:
    const int magic_number = 400000;
    double gamma_y; // the limit of patching function Unit: radian

};

#endif