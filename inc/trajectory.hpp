#ifndef TRAJECTORY_HPP
#define TRAJECTORY_HPP

#include "point.hpp"
#include "line.hpp"
#include <vector>

template <typename T>
class Trajectory {
     
    public:
        Trajectory(){

        }

        void push(const T& rhs){
            trajectory.push_back(rhs);
        }

       

        void insert(const T& rhs,std::size_t position){
            trajectory.insert(trajectory.begin() + position,rhs);
        }

        void remove(std::size_t position){
            trajectory.erase(trajectory.begin() + position);
        }

        std::size_t size() const{
            return trajectory.size();
        }

        T operator[](std::size_t position) const{
            return trajectory[position];
        }
    private:
        std::vector<T> trajectory;  
   

};


#endif