#ifndef TRAJECTORY_HPP
#define TRAJECTORY_HPP

#include "point.hpp"
#include "line.hpp"
#include <vector>

template <typename T>
class Trajectory {
     
    public:
        Trajectory();

        void push(const T& rhs){
            trajectory.push_back(rhs);
        }

        void insert(const T& rhs,std::vector<T>::iterator position){
            trajectory.insert(position,rhs);
        }

        void remove(std::vector<T>::iterator rhs){
            trajectory.erase(rhs);
        }

        std::size_t size(){
            return trajectory.size();
        }

        T operator[](std::size_t position){
            return trajectory[position];
        }
    private:
        std::vector<T> trajectory;  
   

};


#endif