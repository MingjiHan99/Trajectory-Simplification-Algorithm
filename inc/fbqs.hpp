#ifndef FBQS_HPP
#define FBQS_HPP
#include "algorithm.hpp"
#include "line.hpp"
#include <limits>
class FBQS:public Algorithm{
public:
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
                if( (*traj)[start].distance((*traj)[end]) < bound || buffer.size() == 0){
                    buffer.push_back(end);
                } 
                else{
                    auto d = get_bounds(buffer,start,end,traj);
                    if(d.second < bound){
                        buffer.push_back(end);
                    }
                    else if(d.first > bound){
                        res->push(Line{(*traj)[start],(*traj)[end-1]});
                        start = end - 1;
                        buffer.clear();
                        continue;
                    } 
                    else{
                        Line l{(*traj)[start],(*traj)[end]};
                        double dis = l.calculate_distance((*traj)[end]);
                        if( dis < bound ){
                            buffer.push_back(end);
                        }
                        else{
                            res->push(Line{(*traj)[start],(*traj)[end-1]});
                            start = end - 1;
                            buffer.clear();
                            continue;
                        }
                    }
                }
                end++;
            }

        }
        return res;
        
    }
private:
    std::pair<double,double> get_bounds(std::vector<int>& buffer,int start,int end,const Trajectory<Point>* traj){
        std::vector<int> quarter[4];
        Point st = (*traj)[start],en = (*traj)[end];
        Line l{st,en};
        

        for(auto item:buffer){
            Point buf_pt = (*traj)[item];
            if( buf_pt.x > st.x && buf_pt.y > st.y ){
                quarter[0].push_back(item);
            }
            else if( buf_pt.x < st.x && buf_pt.y > st.y){
                quarter[1].push_back(item);
            }
            else if( buf_pt.x < st.x && buf_pt.y < st.y){
                quarter[2].push_back(item);
            }
            else if( buf_pt.x > st.x && buf_pt.y < st.y){
                quarter[3].push_back(item);
            }       
        }

        double d_min = std::numeric_limits<double>::max();
        double d_max = -1;

        for(int i = 0 ; i < 4 ; i++){

            if(quarter[i].size() == 0){
                continue;
            }
            else if(quarter[i].size() == 1){
                double dis = l.calculate_distance((*traj)[quarter[i][0]]);
                d_min = std::min(d_min,dis);
                d_max = std::max(d_max,dis);
            }
            else if(quarter[i].size() > 1) {

                double min_x = std::numeric_limits<double>::max(),min_y = std::numeric_limits<double>::max();
                double max_x = -1,max_y = -1;
                Line min_ang_line,max_ang_line;
                bool first = true;

                for(auto item:quarter[i]){

                    Point pt = (*traj)[item];
                    min_x = std::min(min_x,pt.x);
                    min_y = std::min(min_y,pt.y);
                    max_x = std::max(max_x,pt.x);
                    max_y = std::max(max_y,pt.y);
                    if(first){
                        min_ang_line = Line{(*traj)[start],(*traj)[item]};
                        max_ang_line = Line{(*traj)[start],(*traj)[item]};
                        first = false;
                    }
                    else{
                        Line temp_line = Line{(*traj)[start],(*traj)[item]};

                        if(temp_line.angle() > max_ang_line.angle()){
                            max_ang_line = temp_line;
                        }
                        else if (temp_line.angle() < min_ang_line.angle()){
                            min_ang_line = temp_line;
                        }

                    }

                }

                Point c[4]{{min_x,max_y},{max_x,max_y},{max_x,min_y},{min_x,min_y}};

                double  d_corner_max = -1,d_corner_min = std::numeric_limits<double>::max();
                
                for(int i = 0 ; i < 4; i++){
                    d_corner_max = std::max(d_corner_max,l.calculate_distance(c[i]));
                    d_corner_min = std::min(d_corner_min,l.calculate_distance(c[i]));
                }
                Point l1 = min_ang_line.end_point(),u1 = max_ang_line.start_point();
                Point l2,u2;
                //depends on corrdinate
                

            }
        }


        return {0.0,0.0};
    }
};


#endif