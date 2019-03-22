#include <iostream>
#include "../inc/trajectory.hpp"
#include "../inc/dp.hpp"

int main(){

    std::cout << "Testing..." << std::endl;
    DP dp{1.0};
    Trajectory<Point> traj;
    traj.push({0,0,1});
    traj.push({3,4,2});
    traj.push({6,0,3});
    

    std::cout << traj.size() << std::endl;
    auto result = dp.compress(traj,0,traj.size() - 1);
    std::cout << result.size() << std::endl;

    return 0;
}