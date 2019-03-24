#ifndef DP_HPP
#define DP_HPP
//Douglas-Peucker algorithm
#include "trajectory.hpp"
#include <limits>
class DP{
    public:
        DP(double bound_):bound{bound_}{

        }
        
        void set_bound(double bound_){
            this->bound = bound_;
        }

        int get_bound(){
            return bound;
        }
        Trajectory<Line>* compress(const Trajectory<Point>* t,int left,int right){
            Trajectory<Line>* traj = new Trajectory<Line>();
            int length = right - left + 1;

            if(length < 2){
              
                return traj;
            }
            else if(length == 2){
                //If trajectory has only two points, return the line directly
             
                traj->push(Line{(*t)[left],(*t)[right]});
                return traj;

            }
            else if(length > 2){
              
                Line line{(*t)[left],(*t)[right]};

                double max_distance = -1.0;
                int max_index = 0;

                for(int i = left ; i <= right ; i++){
                    double distance = line.calculate_distance((*t)[i]);
                    if(distance > max_distance){
                        max_distance = distance;
                        max_index = i;
                    }
                }

                if(max_distance < bound){
                    traj->push(line);
                }
                else{
                    Trajectory<Line>* left_traj = compress(t,left,max_index);
                    Trajectory<Line>* right_traj = compress(t,max_index,right);

                    for(int i = 0 ; i < left_traj->size() ; i++){
                        traj->push( (*left_traj)[i]);
                    }
                    for(int j = 0; j < right_traj->size() ; j++){
                        traj->push( (*right_traj)[j]);
                    }
                    
                    delete left_traj;
                    delete right_traj;
                }

               

                return traj;

            }

        }

        Trajectory<Line> compress(const Trajectory<Point>& t,int left,int right){
            Trajectory<Line> traj;
            int length = right - left + 1;

            if(length < 2){
              
                return traj;
            }
            else if(length == 2){
                //If trajectory has only two points, return the line directly
             
                traj.push(Line{t[left],t[right]});
                return traj;

            }
            else if(length > 2){
              
                Line line{t[left],t[right]};

                double max_distance = -1.0;
                int max_index = 0;

                for(int i = left ; i <= right ; i++){
                    double distance = line.calculate_distance(t[i]);
                    if(distance > max_distance){
                        max_distance = distance;
                        max_index = i;
                    }
                }

                if(max_distance < bound){
                    traj.push(line);
                }
                else{
                    Trajectory<Line> left_traj = compress(t,left,max_index);
                    Trajectory<Line> right_traj = compress(t,max_index,right);

                    for(int i = 0 ; i < left_traj.size() ; i++){
                        traj.push(left_traj[i]);
                    }
                    for(int j = 0; j < right_traj.size() ; j++){
                        traj.push(right_traj[j]);
                    }
                }
                return traj;

            }

        }

    private:
    double bound;
};


#endif