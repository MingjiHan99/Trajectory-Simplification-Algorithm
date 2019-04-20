#ifndef FBQS_HPP
#define FBQS_HPP
#include "algorithm.hpp"
#include "line.hpp"
#include <limits>
class FBQS:public Algorithm{
public:
    FBQS(double bound_):Algorithm{bound_},need_new_qurant{true}{
        for(int i = 0 ; i < 4 ; i++){
            quarter[i] = nullptr;
        }
    }    

    Trajectory<Line>* compress(const Trajectory<Point>* traj) {
        need_new_qurant = true;
         first[0] = first[1] = first[2] = first[3] = true;
        for(int i = 0 ; i < 4 ; i++){
            quarter[i] = new int[traj->size()+1];
        }
        int buffer_start = 1 ,buffer_end = 1;
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
            buffer_start = buffer_end = end;
            while(end < traj->size()){

                if( (*traj)[start].distance((*traj)[end]) < bound){
                    buffer_start = buffer_end = end;
                } 
                else{
         
                    auto d = get_bounds(buffer_start,buffer_end,start,end,traj);
           //         std::cout << "bound get " << d.first <<" " << d.second<< std::endl;
                    if(d.second < bound){
             //           std::cout << "Case 1" << std::endl;
                        buffer_end++;
             
                    }
                    else if(d.first > bound){
                 //       std::cout << "Case 2" << std::endl;
                        Point stp = (*traj)[start];
                    
                        Point enp = (*traj)[end-1];
                
                        res->push(Line{stp,enp});
                
                        start = end - 1;
                        buffer_start = buffer_end = end;
                        need_new_qurant = true;
                        first[0] = first[1] = first[2] = first[3] = true;
                        continue;
                    } 
                    else{
                      //  std::cout << "Case 3" << std::endl;
                        res->push(Line{(*traj)[start],(*traj)[end-1]});
                        start = end - 1;
                        buffer_start = buffer_end = end;
                        need_new_qurant = true;
                         first[0] = first[1] = first[2] = first[3] = true;
                        continue;
                        

                    }
                }

                end++;
            }

        }
        for(int i = 0 ; i < 4 ; i++){
            delete[] quarter[i];
        }
        return res;
        
    }
private:
    int *quarter[4];
    bool first[4];  
    bool need_new_qurant;
    std::pair<double,double> get_bounds(int buffer_start,int buffer_end,
                                int start,int end,const Trajectory<Point>* traj){
        
        
        Point st = (*traj)[start],en = (*traj)[end];
        Line l{st,en};
        
        int i = buffer_end - 1;
        if(need_new_qurant){
            i = buffer_start;
            for(int i = 0 ; i < 4; i++){
                quarter[i][0] = 0;
            }
            
        }
     //   std::cout << "Buffer size:" << buffer_end - buffer_start + 1 << std::endl;
        int pos = 0;
        for(; i < buffer_end; i++){
       //     std::cout << "start loop : " << i-1 << std::endl;
            Point buf_pt = (*traj)[i-1];
      //      std::cout << buf_pt.x << " " << buf_pt.y << " " << st.x  << " "  << st.y << std::endl;
            if( buf_pt.x > st.x && buf_pt.y > st.y ){
                quarter[0][++quarter[0][0]] = i;
                pos = 0;
         //       std::cout << "Get pos" << pos << std::endl;
            }
            else if( buf_pt.x < st.x && buf_pt.y > st.y){
                quarter[1][++quarter[1][0]] = i;
                pos = 1;
           //     std::cout << "Get pos" << pos << std::endl;
            }
            else if( buf_pt.x < st.x && buf_pt.y < st.y){
                quarter[2][++quarter[2][0]] = i;
                pos = 2;
             //   std::cout << "Get pos" << pos << std::endl;
            }
            else if( buf_pt.x > st.x && buf_pt.y < st.y){
                quarter[3][++quarter[3][0]] = i;
                pos = 3;
         //       std::cout << "Get pos" << pos << std::endl;
                }     
                
                
            }
    
        double d_min = std::numeric_limits<double>::max();
        double d_max = -1;
        i = 0;
        int end_loop = 4;
        if(!need_new_qurant){
            i = pos;
            end_loop = pos + 1;
        }
  //      std::cout << "Pos" << pos << " " << quarter[pos][0] << std::endl; 
       
        for(; i < end_loop ; i++){

            if(quarter[i][0] == 0){
               
                continue;
            }
            else if(quarter[i][0] == 1){
                double dis = l.calculate_distance((*traj)[quarter[i][0]]);
                d_min = std::min(d_min,dis);
                d_max = std::max(d_max,dis);
            }
            else if(quarter[i][0] >= 1) {
              
                double min_x = std::numeric_limits<double>::max(),min_y = std::numeric_limits<double>::max();
                double max_x = -1,max_y = -1;
                Line min_ang_line,max_ang_line;
                int k = 1;
                if(!first[pos]){
                    k = quarter[i][0];
                }

                for(; k <= quarter[i][0]; k++){

                    Point pt = (*traj)[quarter[i][k]];
                    min_x = std::min(min_x,pt.x);
                    min_y = std::min(min_y,pt.y);
                    max_x = std::max(max_x,pt.x);
                    max_y = std::max(max_y,pt.y);
                    if(first[pos]){
                        min_ang_line = Line{(*traj)[start],(*traj)[quarter[i][k]]};
                        max_ang_line = Line{(*traj)[start],(*traj)[quarter[i][k]]};
                        first[pos] = false;
                    }
                    else{
                        Line temp_line = Line{(*traj)[start],(*traj)[quarter[i][k]]};

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
        if(need_new_qurant)
            need_new_qurant = false;

        return {d_min,d_max};
    }
};


#endif