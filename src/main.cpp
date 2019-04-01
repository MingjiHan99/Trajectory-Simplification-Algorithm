#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include "../inc/trajectory.hpp"
#include "../inc/operb.hpp"
#include "../inc/algorithm.hpp"
#include "../inc/dp.hpp"
#pragma comment(linker, "/STACK:1024000000,1024000000") 

std::string algorithm_type[3] = {"dp","operb","operba"};
int main(int argc,char *argv[]){
    
    if(argc < 4){
        return 0;
    }

    double error_bound = std::stod(argv[1]);
    int size = std::stoi(argv[2]);

    Algorithm* pta = nullptr;
  
    if(argv[3] == algorithm_type[0] ){
        pta = new DP{error_bound};
     
    }
    else if(argv[3] == algorithm_type[1]){
         pta = new OPERB{error_bound};
    }
    else if(argv[3] == algorithm_type[2]){
        pta = new OPERBA{error_bound};
    }
    

    double tx,ty,tt;
    double averge_rate,temp_rate;
  

    double start_time = clock();

    for(int i = 0 ; i < size; i++){
        Trajectory<Point>* traj = new Trajectory<Point>;

        std::string file_name = "../dataset/taxi_clean/A000" + std::to_string(i);
        freopen(file_name.c_str(),"r",stdin);

        while(scanf("%lf %lf %lf",&tt,&ty,&tx) == 3){
            traj->push(Point{tx,ty,tt});
        }

        std::cout << "Running on No." << i << " trajectory..." << std::endl;
        std::cout << "Trajectory size:" << traj->size() << std::endl;

        auto result = pta->compress(traj);
        temp_rate = (double) (traj->size() - result->size() - 1)/ traj->size();
        averge_rate += temp_rate;

        std::cout << "Compressed trajectory size:" << result->size() + 1 << std::endl;
        std::cout << "Compression rate:" << temp_rate << std::endl;
        
        delete traj;
        fclose(stdin);
    
    }

    double end_time = clock();

    averge_rate /= size;
    freopen("result.txt","w",stdout);
    std::cout << "Error Bound: " << error_bound << "m" << std::endl;
    std::cout << "Average Compression Ratio: " << averge_rate * 100 << "\%" << std::endl;
    std::cout << "Running time " << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s"<< std::endl;

    fclose(stdout);
    
    return 0;
}