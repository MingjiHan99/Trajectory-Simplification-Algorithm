# Trajectory-Compression-Algorithm

### Overview
This is a research project on trajectory compression. We will implement three trajectory simplication algorithms (DP,FBQS,OPERB) in this repository.

### Prerequisite
+ python3
+ unrar
+ g++
+ make
+ Ubuntu 16.04

### Test Douglas-Peucker algorithm on Taxi dataset

#### About the dataset
The taxi dataset on http://mashuai.buaa.edu.cn/traj.html includes 100 trajectories collected by sensors on taxi. A trajectory has 39,100 data points on average. The size of the dataset is 36.3M

#### Get the Repository
```
git clone https://github.com/Hannnnnn/Trajectory-Compression-Algorithm.git
cd Trajectory-Compression-Algorithm
```
#### Download and Preprocess the Dataset
```
chmod 777 taxi_dataset.sh
./taxi_dataset.sh
```

#### Generate the Executable File and Get Result

```
cd src
make
./prog error_bound size algorithm_type
```
Note: error_bound means the error boundary(meters).  
You can set error boundary when you run the program.  
Size means the number of trajectory the program will compress.  
Example: ./prog 10.0 100 operb
This means the program will compress 100 trajectories with error bound 10 meters by OPERB algorithm.  
You can also enter prameter "dp" or "operba" to use DP or OPERB-A algorithm.
You will get result.txt in src folder after the program is done.  
It includes the average compress ratio and running time of program. 

### Result

![image](https://github.com/Hannnnnn/Trajectory-Compression-Algorithm/blob/dev/image/1.png)
![image](https://github.com/Hannnnnn/Trajectory-Compression-Algorithm/blob/dev/image/2.png)
![image](https://github.com/Hannnnnn/Trajectory-Compression-Algorithm/blob/dev/image/3.png)
