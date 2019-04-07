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
        Trajectory<Line>* res = new Trajectory<Line>();
        if(traj->size() == 1){
            return res;
        }
        else if(traj->size() == 2){
            res->push(Line{(*traj)[0],(*traj)[1]});
            return res;
        }
        else if(traj->size() > 2){
            int start = 0;
            int end = 1;
            std::vector<int> buffer;
            while(end < traj->size()){
                
            //    std::cout << start << " " << end << std::endl;
                if( (*traj)[start].distance((*traj)[end]) < bound || buffer.size() == 0){
               //     std::cout << "Case 1" << std::endl;
                    buffer.push_back(end);
                } 
                else{
              //      std::cout << "Case 2" << std::endl;
                    auto d = get_bounds(buffer,start,end,traj);
               //     std::cout << "Get bound successfully" << std::endl;

                    if(d.second < bound){
             //           std::cout << "Case 2:1" << std::endl;
                        buffer.push_back(end);
                    }
                    else if(d.first > bound){
                  //      std::cout << "Case 2:2" << std::endl;
                        
                        Point stp = (*traj)[start];
                    
                        Point enp = (*traj)[end-1];
                
                        res->push(Line{stp,enp});
                       
                //        std::cout << "Push successfully" << std::endl;
                        start = end - 1;
                        buffer.clear();
                 //       std::cout << "Clear successfully" << std::endl;
                        
                        continue;
                    } 
                    else{
                //        std::cout << "Case 2:3" << std::endl;
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
              //  std::cout << "Loop over" << std::endl;
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
                
                for(int j = 0 ; j < 4; j++){
                    d_corner_max = std::max(d_corner_max,l.calculate_distance(c[j]));
                    d_corner_min = std::min(d_corner_min,l.calculate_distance(c[j]));
                }
                Point l1 = min_ang_line.end_point(),u1 = max_ang_line.start_point();
                Point l2,u2;
                //depends on corrdinate
                switch(i){
                    case 0: 
                        l2 = Point{min_ang_line.get_x(c[3].y),c[3].y};break;
                    case 1: 
                        l2 = Point{c[2].x,min_ang_line.get_y(c[2].x)};break;
                    case 2: 
                        l2 = Point{min_ang_line.get_x(c[1].x),c[1].y};break;
                    case 3: 
                        l2 = Point{c[3].x,min_ang_line.get_y(c[3].x)};break;
                }

                switch(i){
                    case 0: 
                        u2 = Point{c[3].x,max_ang_line.get_y(c[3].x)};break;
                    case 1: 
                        u2 = Point{max_ang_line.get_x(c[3].y),c[3].y};break;
                    case 2: 
                        u2 = Point{c[2].x,max_ang_line.get_y(c[2].x)};break;
                    case 3: 
                        u2 = Point{max_ang_line.get_x(c[1].y),c[1].y};break;
                }

                double max_u = std::max(l.calculate_distance(u1),l.calculate_distance(u2));
                double min_u = std::min(l.calculate_distance(u1),l.calculate_distance(u2));

                double max_l = std::max(l.calculate_distance(l1),l.calculate_distance(l2));
                double min_l = std::min(l.calculate_distance(l1),l.calculate_distance(l2));

                double max_corner = std::max(d_corner_max,d_corner_min);


                d_max = std::max(d_max,std::max(max_u,max_l));
                d_min = std::max(d_min,std::min(min_u,min_l));
                d_min = std::max(d_min,max_corner);
            }
        }


        return {d_min,d_max};
    }
};


#endif