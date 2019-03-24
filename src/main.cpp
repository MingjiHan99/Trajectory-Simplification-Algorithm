#include <iostream>
#include <cstdio>
#include <string>
#include "../inc/trajectory.hpp"
#include "../inc/dp.hpp"
#pragma comment(linker, "/STACK:1024000000,1024000000") 
Trajectory<Point> traj;
int main(int argc,char *argv[]){
    if(argc == 1){
        return 0;
    }
    
    for(int i = 0 ; i < 101; i++){
        
    }

    std::cout << "Testing..." << std::endl;
    DP dp{std::stod(argv[1])};
   
    freopen("../dataset/taxi_clean/A0000","r",stdin);
    double tx,ty,tt;
    while(scanf("%lf %lf %lf",&tt,&ty,&tx) == 3){
        traj.push(Point{tx,ty,tt});
    }

    std::cout << "Trajectory size:" << traj.size() << std::endl;

    auto result = dp.compress(traj,0,traj.size() - 1);
    std::cout << "Compressed trajectory size:" << result.size() << std::endl;
    std::cout << "Compression rate:" << (double) (traj.size() - result.size())/ traj.size() << std::endl;

    return 0;
}