#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include "../inc/trajectory.hpp"
#include "../inc/operb.hpp"
#include "../inc/algorithm.hpp"
#include "../inc/dp.hpp"
#include "../inc/fbqs.hpp"
#pragma comment(linker, "/STACK:1024000000,1024000000") 

std::string algorithm_type[4] = {"dp","operb","operba","fbqs"};
int main(int argc,char *argv[]){
    
    if(argc < 4){
        return 0;
    }

    double error_bound = std::stod(argv[1]);
    int size = std::stoi(argv[2]);
    int total_point = 0;
    Algorithm* pta = nullptr;
    double average_second = 0.0;
  
    if(argv[3] == algorithm_type[0] ){
        pta = new DP{error_bound};
     
    }
    else if(argv[3] == algorithm_type[1]){
         pta = new OPERB{error_bound};
    }
    else if(argv[3] == algorithm_type[2]){
        pta = new OPERBA{error_bound};
    }
    else if(argv[3] == algorithm_type[3]){
        pta = new FBQS{error_bound};
    }
    
    //int traj_size = std::stoi(argv[4]);

    double tx,ty,tt;
    double averge_rate,temp_rate;
  

    double start_time = clock();

    for(int i = 0 ; i < size; i++){
        Trajectory<Point>* traj = new Trajectory<Point>;

        std::string file_name = "../dataset/taxi_clean/A000" + std::to_string(i);
        freopen(file_name.c_str(),"r",stdin);
        int count = 0;
        while(scanf("%lf %lf %lf",&tt,&ty,&tx) == 3){
            traj->push(Point{tx,ty,tt});
            count += 1;
        }
        total_point += traj->size();
        
        std::cout << "Running on No." << i << " trajectory..." << std::endl;
        std::cout << "Trajectory size:" << traj->size() << std::endl;

        double start_time = clock();
        auto result = pta->compress(traj);
        double end_time = clock();

        average_second += (double)(end_time - start_time) / CLOCKS_PER_SEC;

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
    std::cout << "Average Compression Ratio: " << 100.0 - averge_rate * 100 << "\%" << std::endl;
    std::cout << "Running time " << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s"<< std::endl;
    std::cout << "Average Second:" << average_second / (double)size << std::endl;
    fclose(stdout);
    
    return 0;
}